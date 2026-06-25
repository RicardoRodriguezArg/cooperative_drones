#!/usr/bin/env python3
"""
Genera urdf/peon_movil.urdf para el UGV Rover PT (6 ruedas + pan-tilt + camara)
con inercia calculada por PRIMITIVAS (caja / cilindro) a partir de masa + dimensiones.

  * No necesita ROS ni FreeCAD, solo python3 (numpy opcional).
  * Dimensiones tomadas del STEP (inventory.csv). Marco ROS REP-103:
        x = adelante, y = izquierda, z = arriba. Unidades: metros, kg, kg*m^2.
  * CALIBRACION: pesa el robot real y ajusta las masas de MASS{} hasta que
    la suma (se imprime al final) coincida con la balanza. La inercia se
    recalcula sola al re-ejecutar:  python3 gen_urdf.py

Convencion de inercia (solido homogeneo, respecto al COM):
  caja (dx,dy,dz):  Ixx=m/12(dy^2+dz^2)  Iyy=m/12(dx^2+dz^2)  Izz=m/12(dx^2+dy^2)
  cilindro r,h, eje Y (rueda):  Iyy=1/2 m r^2 ; Ixx=Izz=1/12 m(3r^2+h^2)
"""
import os

# ----------------------------------------------------------------------------
# MASAS (kg) -- AJUSTA AQUI y re-ejecuta. Valores iniciales ~ kit con bateria.
# ----------------------------------------------------------------------------
MASS = {
    "base":   1.40,   # chasis + placas + RPi4 + UPS + motores + electronica
    "wheel":  0.085,  # cada rueda (neumatico + cubo), x6
    "pan":    0.08,   # plato/yaw del pan-tilt
    "tilt":   0.06,   # soporte/pitch del pan-tilt
    "camera": 0.03,   # camara
}

# ----------------------------------------------------------------------------
# GEOMETRIA (m) -- del STEP. Ajusta si quieres mas fidelidad.
# ----------------------------------------------------------------------------
BASE_BOX   = (0.241, 0.200, 0.100)   # caja envolvente del chasis (x,y,z)
BASE_COM_Z = 0.00                    # COM del chasis respecto al frame base_link

WHEEL_R       = 0.041                # radio rueda (Ø~82mm "80mm")
WHEEL_W       = 0.0425               # ancho rueda
WHEEL_Z       = -0.0412              # z del eje respecto a base_link (medido)
WHEEL_X       = 0.0855               # |x| ruedas delanteras/traseras
WHEEL_Y_CORN  = 0.0873              # |y| ruedas de esquina (medido)
WHEEL_Y_MID   = 0.0883              # |y| ruedas centrales (medido)

# --- Mallas STL reales (exportadas con export_stl.py, en mm) ---
USE_MESH   = True
MESH_PKG   = "package://peon_movil_description/urdf/meshes_stl"
MESH_SCALE = "0.001 0.001 0.001"     # STL en mm -> m

# Pan-tilt sobre el chasis (origenes y cajas MEDIDOS del STEP, ver export_stl.py)
PAN_XYZ    = (0.0087, 0.00, 0.0475)  # junta pan sobre base_link (eje Z)
PAN_BOX    = (0.064, 0.042, 0.053)
TILT_XYZ   = (-0.0124, 0.00, 0.0835) # junta tilt sobre pan_link (eje Y)
TILT_BOX   = (0.075, 0.046, 0.055)
CAM_XYZ    = (-0.0263, 0.00, 0.021)  # camara (fija) sobre tilt_link
CAM_BOX    = (0.080, 0.046, 0.055)

OUT = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "urdf", "peon_movil.urdf")


def box_inertia(m, dx, dy, dz):
    return (m/12.0*(dy*dy+dz*dz), m/12.0*(dx*dx+dz*dz), m/12.0*(dx*dx+dy*dy))


def cyl_inertia_y(m, r, h):
    # eje de giro = Y
    iyy = 0.5*m*r*r
    ixx = izz = (1.0/12.0)*m*(3*r*r + h*h)
    return (ixx, iyy, izz)


def inertial(m, com, I):
    ixx, iyy, izz = I
    return (f'    <inertial>\n'
            f'      <origin xyz="{com[0]:.5f} {com[1]:.5f} {com[2]:.5f}" rpy="0 0 0"/>\n'
            f'      <mass value="{m:.4f}"/>\n'
            f'      <inertia ixx="{ixx:.6e}" ixy="0" ixz="0" '
            f'iyy="{iyy:.6e}" iyz="0" izz="{izz:.6e}"/>\n'
            f'    </inertial>\n')


def box_link(name, box, mass, com_z=0.0, color="0.2 0.2 0.2 1", mesh=None):
    dx, dy, dz = box
    I = box_inertia(mass, dx, dy, dz)
    if USE_MESH and mesh:
        # malla ya en el marco del link (base.stl en origen del ensamblaje)
        vis_geom = f'<mesh filename="{MESH_PKG}/{mesh}" scale="{MESH_SCALE}"/>'
        vis_origin = '0 0 0'
    else:
        vis_geom = f'<box size="{dx} {dy} {dz}"/>'
        vis_origin = f'0 0 {com_z}'
    return (f'  <link name="{name}">\n'
            f'    <visual>\n'
            f'      <origin xyz="{vis_origin}" rpy="0 0 0"/>\n'
            f'      <geometry>{vis_geom}</geometry>\n'
            f'      <material name="{name}_mat"><color rgba="{color}"/></material>\n'
            f'    </visual>\n'
            f'    <collision>\n'
            f'      <origin xyz="0 0 {com_z}" rpy="0 0 0"/>\n'
            f'      <geometry><box size="{dx} {dy} {dz}"/></geometry>\n'
            f'    </collision>\n'
            + inertial(mass, (0, 0, com_z), I) +
            f'  </link>\n')


def wheel_link(name):
    I = cyl_inertia_y(MASS["wheel"], WHEEL_R, WHEEL_W)
    if USE_MESH:
        vis = (f'      <origin xyz="0 0 0" rpy="0 0 0"/>\n'
               f'      <geometry><mesh filename="{MESH_PKG}/{name}.stl" '
               f'scale="{MESH_SCALE}"/></geometry>\n')
    else:
        vis = (f'      <origin xyz="0 0 0" rpy="1.5708 0 0"/>\n'
               f'      <geometry><cylinder radius="{WHEEL_R}" '
               f'length="{WHEEL_W}"/></geometry>\n')
    return (f'  <link name="{name}">\n'
            f'    <visual>\n' + vis +
            f'      <material name="wheel_mat"><color rgba="0.1 0.1 0.1 1"/></material>\n'
            f'    </visual>\n'
            f'    <collision>\n'
            f'      <origin xyz="0 0 0" rpy="1.5708 0 0"/>\n'
            f'      <geometry><cylinder radius="{WHEEL_R}" length="{WHEEL_W}"/></geometry>\n'
            f'    </collision>\n'
            + inertial(MASS["wheel"], (0, 0, 0), I) +
            f'  </link>\n')


def wheel_joint(name, child, x, y):
    return (f'  <joint name="{name}" type="continuous">\n'
            f'    <parent link="base_link"/>\n'
            f'    <child link="{child}"/>\n'
            f'    <origin xyz="{x} {y} {WHEEL_Z}" rpy="0 0 0"/>\n'
            f'    <axis xyz="0 1 0"/>\n'
            f'  </joint>\n')


def main():
    parts = []
    parts.append('<?xml version="1.0"?>\n')
    parts.append('<robot name="peon_movil">\n\n')

    # base
    parts.append(box_link("base_link", BASE_BOX, MASS["base"], BASE_COM_Z,
                          "0.3 0.3 0.35 1", mesh="base.stl"))
    parts.append("\n")

    # 6 ruedas (y medidas: esquinas 0.0873, centrales 0.0883)
    wheels = [
        ("wheel_fl_joint", "wheel_fl",  WHEEL_X,  WHEEL_Y_CORN),
        ("wheel_fr_joint", "wheel_fr",  WHEEL_X, -WHEEL_Y_CORN),
        ("wheel_ml_joint", "wheel_ml",  0.0,      WHEEL_Y_MID),
        ("wheel_mr_joint", "wheel_mr",  0.0,     -WHEEL_Y_MID),
        ("wheel_rl_joint", "wheel_rl", -WHEEL_X,  WHEEL_Y_CORN),
        ("wheel_rr_joint", "wheel_rr", -WHEEL_X, -WHEEL_Y_CORN),
    ]
    for jn, ch, x, y in wheels:
        parts.append(wheel_link(ch))
        parts.append(wheel_joint(jn, ch, x, y))
        parts.append("\n")

    # pan-tilt + camara
    parts.append(box_link("pan_link", PAN_BOX, MASS["pan"], 0.0, "0.5 0.5 0.5 1", mesh="pan.stl"))
    parts.append(f'  <joint name="pan_joint" type="revolute">\n'
                 f'    <parent link="base_link"/>\n    <child link="pan_link"/>\n'
                 f'    <origin xyz="{PAN_XYZ[0]} {PAN_XYZ[1]} {PAN_XYZ[2]}" rpy="0 0 0"/>\n'
                 f'    <axis xyz="0 0 1"/>\n'
                 f'    <limit lower="-3.14159" upper="3.14159" effort="5" velocity="3"/>\n'
                 f'  </joint>\n\n')

    parts.append(box_link("tilt_link", TILT_BOX, MASS["tilt"], 0.0, "0.5 0.5 0.5 1", mesh="tilt.stl"))
    parts.append(f'  <joint name="tilt_joint" type="revolute">\n'
                 f'    <parent link="pan_link"/>\n    <child link="tilt_link"/>\n'
                 f'    <origin xyz="{TILT_XYZ[0]} {TILT_XYZ[1]} {TILT_XYZ[2]}" rpy="0 0 0"/>\n'
                 f'    <axis xyz="0 1 0"/>\n'
                 f'    <limit lower="-1.5708" upper="1.5708" effort="5" velocity="3"/>\n'
                 f'  </joint>\n\n')

    parts.append(box_link("camera_link", CAM_BOX, MASS["camera"], 0.0, "0.05 0.05 0.05 1", mesh="camera.stl"))
    parts.append(f'  <joint name="camera_joint" type="fixed">\n'
                 f'    <parent link="tilt_link"/>\n    <child link="camera_link"/>\n'
                 f'    <origin xyz="{CAM_XYZ[0]} {CAM_XYZ[1]} {CAM_XYZ[2]}" rpy="0 0 0"/>\n'
                 f'  </joint>\n\n')

    # frame optico de la camara (REP-103/104: z adelante, x derecha, y abajo)
    parts.append('  <link name="camera_optical_frame"/>\n')
    parts.append('  <joint name="camera_optical_joint" type="fixed">\n'
                 '    <parent link="camera_link"/>\n    <child link="camera_optical_frame"/>\n'
                 '    <origin xyz="0 0 0" rpy="-1.5708 0 -1.5708"/>\n'
                 '  </joint>\n\n')

    parts.append('</robot>\n')

    with open(OUT, "w") as f:
        f.write("".join(parts))

    total = MASS["base"] + 6*MASS["wheel"] + MASS["pan"] + MASS["tilt"] + MASS["camera"]
    print(f"URDF escrito en: {os.path.normpath(OUT)}")
    print(f"MASA TOTAL del modelo = {total:.3f} kg  (calibra MASS{{}} contra la balanza)")


if __name__ == "__main__":
    main()
