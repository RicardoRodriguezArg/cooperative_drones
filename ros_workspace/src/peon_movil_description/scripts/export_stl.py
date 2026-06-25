"""
Exporta TODAS las mallas STL por link desde el STEP, en una sola carga.
Estrategia (independiente de nombres, todo en coordenadas globales):
  1. Part.getShape(transform=True) sobre la raiz -> todos los solidos en mundo.
  2. Clasifica cada solido por la posicion de su centro de caja:
        - cerca de un centro de rueda (XY) y z bajo   -> esa rueda
        - z en banda pan / tilt / camara              -> pan / tilt / camera
        - resto                                       -> base
  3. Exporta un STL por grupo, recentrado en el origen de su junta para que
     la articulacion sea correcta. Imprime los origenes para el URDF.

Ejecutar:  freecad.cmd export_stl.py     (tarda varios minutos)
Salida:    urdf/meshes_stl/*.stl  y  scripts/export_stl.log
"""
import os, traceback, math

HERE = os.path.dirname(os.path.abspath(__file__))
STEP = os.path.join(HERE, "..", "urdf", "meshes", "UGV Rover PT AI Kit v9.step")
OUTDIR = os.path.join(HERE, "..", "urdf", "meshes_stl")
LOG = os.path.join(HERE, "export_stl.log")

# Ruedas: (nombre, x, y) en mm  (eje real del neumatico)
WHEELS = [
    ("wheel_fl",  85.5,  87.31),
    ("wheel_fr",  85.5, -87.31),
    ("wheel_ml",   0.0,  88.31),
    ("wheel_mr",   0.0, -88.31),
    ("wheel_rl", -85.5,  87.31),
    ("wheel_rr", -85.5, -87.31),
]
WHEEL_XY_TOL = 45.0
WHEEL_ZMAX = -20.0

# Pan-tilt: bandas en z (mm) del centro del solido, y origen de junta (mm, mundo)
PTZ_ZMIN   = 40.0
PAN_ZMAX   = 100.0     # pan:    40 < z <= 100
TILT_ZMAX  = 134.0     # tilt:  100 < z <= 134 ; camera: z > 134
PAN_ORIGIN  = (8.7,  0.0, 47.5)    # eje pan (Z) en la base de la plataforma
TILT_ORIGIN = (-3.7, 0.0, 131.0)   # eje tilt (Y) en el servo de tilt
CAM_ORIGIN  = (-30.0, 0.0, 152.0)  # centro optico aprox de la camara

log = open(LOG, "w")
def L(m): log.write(m+"\n"); log.flush()

try:
    import FreeCAD as App, Part, Import, Mesh, MeshPart
    if not os.path.isdir(OUTDIR):
        os.makedirs(OUTDIR)

    L("Cargando STEP (varios minutos)...")
    doc = App.newDocument("kit"); Import.insert(STEP, "kit")
    L("Cargado. Objetos: %d" % len(doc.Objects))

    roots = [o for o in doc.Objects if not o.InList]
    world = Part.makeCompound([Part.getShape(r, transform=True) for r in roots])
    solids = world.Solids
    L("Solidos en mundo: %d" % len(solids))

    groups = {w[0]: [] for w in WHEELS}
    groups.update({"base": [], "pan": [], "tilt": [], "camera": []})

    for sol in solids:
        bb = sol.BoundBox
        cx, cy, cz = bb.Center.x, bb.Center.y, bb.Center.z
        # ruedas
        if cz < WHEEL_ZMAX:
            best, bestd = None, 1e9
            for name, wx, wy in WHEELS:
                d = math.hypot(cx-wx, cy-wy)
                if d < bestd: bestd, best = d, name
            if bestd <= WHEEL_XY_TOL:
                groups[best].append(sol); continue
        # pan-tilt-camara por bandas de z
        if cz > PTZ_ZMIN:
            if cz <= PAN_ZMAX:    groups["pan"].append(sol);    continue
            if cz <= TILT_ZMAX:   groups["tilt"].append(sol);   continue
            groups["camera"].append(sol); continue
        groups["base"].append(sol)

    for k in ["base"] + [w[0] for w in WHEELS] + ["pan", "tilt", "camera"]:
        L("  grupo %-9s : %d solidos" % (k, len(groups[k])))

    def export_group(name, sols, recenter=None, deflection=0.6):
        if not sols:
            L("  [skip] %s sin solidos" % name); return None
        comp = Part.makeCompound([s.copy() for s in sols])
        if recenter is not None:
            comp.translate(App.Vector(-recenter[0], -recenter[1], -recenter[2]))
        m = MeshPart.meshFromShape(Shape=comp, LinearDeflection=deflection,
                                   AngularDeflection=0.5)
        path = os.path.join(OUTDIR, name + ".stl")
        m.write(path)
        L("  exportado %-9s -> %s (%.0f KB)" % (
            name, os.path.basename(path), os.path.getsize(path)/1024.0))
        return recenter

    L("Exportando...")
    export_group("base", groups["base"], recenter=None, deflection=1.0)
    for name, wx, wy in WHEELS:
        if groups[name]:
            zc = Part.makeCompound([s.copy() for s in groups[name]]).BoundBox.Center.z
            export_group(name, groups[name], recenter=(wx, wy, zc), deflection=0.3)
    export_group("pan",    groups["pan"],    recenter=PAN_ORIGIN,  deflection=0.3)
    export_group("tilt",   groups["tilt"],   recenter=TILT_ORIGIN, deflection=0.3)
    export_group("camera", groups["camera"], recenter=CAM_ORIGIN,  deflection=0.3)

    L("\n=== ORIGENES DE JUNTA (m) ===")
    L("  pan_joint  (base->pan)  xyz = %.4f %.4f %.4f" %
      tuple(v/1000 for v in PAN_ORIGIN))
    L("  tilt_joint (pan->tilt)  xyz = %.4f %.4f %.4f" %
      tuple((TILT_ORIGIN[i]-PAN_ORIGIN[i])/1000 for i in range(3)))
    L("  cam_joint  (tilt->cam)  xyz = %.4f %.4f %.4f" %
      tuple((CAM_ORIGIN[i]-TILT_ORIGIN[i])/1000 for i in range(3)))
    L("OK")
except Exception:
    L("ERROR:\n"+traceback.format_exc())
finally:
    log.close()
