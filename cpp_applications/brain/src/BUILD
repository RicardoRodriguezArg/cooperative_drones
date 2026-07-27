# Robot Router: agente que traduce comandos en lenguaje natural a comandos de
# robot via un LLM servido con OpenVINO GenAI. Migrado desde CMake (ver
# historial) preservando exactamente las mismas dependencias del sistema:
#
#   - OpenVINO runtime: instalado en el sistema (headers en /usr/include,
#     libopenvino.so en /usr/lib), ya visibles para el toolchain custom del
#     repo sin flags extra.
#   - tinyxml2: idem, paquete del sistema (libtinyxml2-dev).
#   - openvino_genai / openvino_tokenizers: NO se compilan desde
#     resources/openvino.genai-2026.1.0.0 (eso es el codigo fuente vendored,
#     usado solo por sus headers); se linkea directo contra los .so
#     preconstruidos de un virtualenv Python, igual que hacia el CMake
#     original via IMPORTED_LOCATION.
#
# executive/, features/ y commands/ quedan fuera de este BUILD a proposito:
# no estan wireados a ningun target hoy (sus CMakeLists.txt estaban vacios),
# tienen includes rotos a una ruta que ya no existe y dependen de piezas que
# no estan en el repo (p.ej. behaviortree_cpp). No se migran ni se inventan.

package(default_visibility = ["//visibility:private"])

_GENAI_ROOT = "resources/openvino.genai-2026.1.0.0"
_GENAI_INCLUDE = _GENAI_ROOT + "/src/cpp/include"

# Rutas del virtualenv donde viven los .so precompilados de OpenVINO GenAI.
# No son parte del repo ni del workspace de Bazel: son un dependencia externa
# de este host, igual que ya lo eran para el CMakeLists.txt original (que las
# referenciaba via $ENV{HOME}). Se linkean por ruta absoluta (cc_import no
# puede apuntar fuera del workspace).
_VENV_SITE_PACKAGES = "/home/operador/virtual_enviroments/kamerdyner/lib/python3.12/site-packages"
_OPENVINO_GENAI_SO = _VENV_SITE_PACKAGES + "/openvino_genai/libopenvino_genai.so.2610"
_OPENVINO_TOKENIZERS_DIR = _VENV_SITE_PACKAGES + "/openvino_tokenizers/lib"
_OPENVINO_LIBS_DIR = _VENV_SITE_PACKAGES + "/openvino/libs"

# Headers vendored de OpenVINO GenAI (solo headers: la libreria es la .so
# precompilada de arriba, no se compila este arbol).
cc_library(
    name = "openvino_genai_headers",
    hdrs = glob([_GENAI_INCLUDE + "/**/*.hpp", _GENAI_INCLUDE + "/**/*.h"]),
    includes = [_GENAI_INCLUDE],
)

# openvino::runtime + tinyxml2 ya son visibles sin flags extra: headers en
# /usr/include (builtin_include_directories del toolchain) y libs en rutas
# default del linker (verificado con g++ -lopenvino / -ltinyxml2 sin -L).
cc_library(
    name = "openvino_genai",
    deps = [":openvino_genai_headers"],
    linkopts = [
        _OPENVINO_GENAI_SO,
        "-lopenvino",
    ],
)

cc_library(
    name = "agent_lib",
    hdrs = glob(["inference/**/*.h"]),
    includes = ["."],
    linkopts = ["-ltinyxml2"],
    deps = [":openvino_genai"],
)

cc_library(
    name = "frontend_lib",
    hdrs = glob(["frontend/**/*.h"]),
    includes = ["."],
    deps = [":agent_lib"],
)

# Sanitizers de UB, mismo interruptor que en //memory_management (--config
# asan/ubsan en .bazelrc, ver //config:BUILD.bazel). Antes de perfilar/
# optimizar nada de este binario hay que confirmar que esta libre de UB,
# incluso mezclado con la .so de terceros (openvino_genai) sin instrumentar.
_SANITIZER_COPTS = select({
    "//config:asan": ["-fsanitize=address", "-fno-omit-frame-pointer"],
    "//conditions:default": [],
}) + select({
    "//config:ubsan": ["-fsanitize=undefined", "-fno-sanitize-recover=undefined"],
    "//conditions:default": [],
})

_SANITIZER_LINKOPTS = select({
    "//config:asan": ["-fsanitize=address"],
    "//conditions:default": [],
}) + select({
    "//config:ubsan": ["-fsanitize=undefined"],
    "//conditions:default": [],
})

cc_binary(
    name = "robot_router",
    srcs = ["main.cpp", "definitions.h"] + glob([
        "settings/**/*.h",
        "utils/**/*.h",
        "robot_state_expert/**/*.h",
    ]),
    includes = ["."],
    copts = [
        # El resto del repo fija -std=c++20 (ver .bazelrc); este binario
        # necesita C++23 (std::is_scoped_enum_v, etc.), como especificaba
        # el CMakeLists.txt original (CMAKE_CXX_STANDARD 23). El ultimo
        # -std= en la linea de comandos gana, asi que esto override-ea el
        # -std=c++20 global sin tocarlo para el resto de los packages.
        "-std=c++23",
        # Ruta absoluta directa al XML en el arbol fuente (el CMakeLists
        # original dependia de un `install()` a CMAKE_INSTALL_PREFIX que
        # nunca corria automaticamente); asi funciona out-of-the-box con
        # bazel run, sin paso de instalacion.
        "-DMODEL_INFERENCE_CONFIG_PATH=\\\"/home/operador/Documents/cooperative_drones/cpp_applications/brain/src/config/inference/model_inference_config.xml\\\"",
    ] + _SANITIZER_COPTS,
    linkopts = [
        "-Wl,-rpath," + _VENV_SITE_PACKAGES + "/openvino_genai",
        "-Wl,-rpath," + _OPENVINO_TOKENIZERS_DIR,
        "-Wl,-rpath," + _OPENVINO_LIBS_DIR,
        "-L" + _OPENVINO_TOKENIZERS_DIR,
        "-lopenvino_tokenizers",
    ] + _SANITIZER_LINKOPTS,
    deps = [":frontend_lib"],
)
