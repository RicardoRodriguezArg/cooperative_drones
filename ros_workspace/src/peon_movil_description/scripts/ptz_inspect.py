"""
Inspecciona la zona del pan-tilt (PTZ) en coordenadas GLOBALES y vuelca cada
solido (centro, tamano, volumen) ordenado por altura, para disenar el reparto
pan/tilt/camara. Reglas iguales a export_stl: las 6 ruedas se excluyen; de lo
que queda, lo que tenga centro z > Z_MIN se considera PTZ.

Ejecutar:  freecad.cmd ptz_inspect.py
Salida:    scripts/ptz_inspect.log
"""
import os, traceback, math

HERE = os.path.dirname(os.path.abspath(__file__))
STEP = os.path.join(HERE, "..", "urdf", "meshes", "UGV Rover PT AI Kit v9.step")
LOG = os.path.join(HERE, "ptz_inspect.log")

WHEELS = [("fl",85.5,87.31),("fr",85.5,-87.31),("ml",0.0,88.31),
          ("mr",0.0,-88.31),("rl",-85.5,87.31),("rr",-85.5,-87.31)]
WHEEL_XY_TOL = 45.0
WHEEL_ZMAX = -20.0
Z_MIN = 40.0   # mm: por encima de esto = candidato PTZ

log = open(LOG, "w")
def L(m): log.write(m+"\n"); log.flush()

try:
    import FreeCAD as App, Part, Import
    L("Cargando STEP...")
    doc = App.newDocument("kit"); Import.insert(STEP, "kit")
    roots = [o for o in doc.Objects if not o.InList]
    world = Part.makeCompound([Part.getShape(r, transform=True) for r in roots])
    solids = world.Solids
    L("Solidos: %d" % len(solids))

    ptz = []
    for s in solids:
        bb = s.BoundBox
        cx, cy, cz = bb.Center.x, bb.Center.y, bb.Center.z
        # excluir ruedas
        if cz < WHEEL_ZMAX:
            if min(math.hypot(cx-wx, cy-wy) for _, wx, wy in WHEELS) <= WHEEL_XY_TOL:
                continue
        if cz > Z_MIN:
            ptz.append((s, cx, cy, cz, bb.XLength, bb.YLength, bb.ZLength, s.Volume))

    L("Solidos PTZ (z_centro > %.0f): %d" % (Z_MIN, len(ptz)))
    if ptz:
        xs = [p[1] for p in ptz]; ys = [p[2] for p in ptz]; zs = [p[3] for p in ptz]
        L("PTZ extension global mm: x[%.1f,%.1f] y[%.1f,%.1f] z[%.1f,%.1f]"
          % (min(xs), max(xs), min(ys), max(ys), min(zs), max(zs)))
    L("\n  %3s %8s %8s %8s | %7s %7s %7s | %9s" %
      ("#","cx","cy","cz","dx","dy","dz","vol_cm3"))
    for i, (s, cx, cy, cz, dx, dy, dz, V) in enumerate(sorted(ptz, key=lambda p: p[3])):
        L("  %3d %8.1f %8.1f %8.1f | %7.1f %7.1f %7.1f | %9.2f"
          % (i, cx, cy, cz, dx, dy, dz, V*1e-3))
    L("OK")
except Exception:
    L("ERROR:\n"+traceback.format_exc())
finally:
    log.close()
