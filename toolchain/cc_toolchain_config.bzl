"""Regla custom de configuracion de cc_toolchain.

Define explicitamente, sin autodeteccion de Bazel, los flags de compilacion
y linkeo por defecto de un toolchain de C++ (gcc o clang), mas los flags
especificos de los modos `-c dbg` / `-c opt`.
"""

load(
    "@bazel_tools//tools/build_defs/cc:action_names.bzl",
    "ACTION_NAMES",
)
load(
    "@bazel_tools//tools/cpp:cc_toolchain_config_lib.bzl",
    "feature",
    "flag_group",
    "flag_set",
    "tool_path",
)

_ALL_COMPILE_ACTIONS = [
    ACTION_NAMES.c_compile,
    ACTION_NAMES.cpp_compile,
    ACTION_NAMES.linkstamp_compile,
    ACTION_NAMES.assemble,
    ACTION_NAMES.preprocess_assemble,
    ACTION_NAMES.cpp_header_parsing,
    ACTION_NAMES.cpp_module_compile,
    ACTION_NAMES.cpp_module_codegen,
]

_ALL_CPP_COMPILE_ACTIONS = [
    ACTION_NAMES.cpp_compile,
    ACTION_NAMES.linkstamp_compile,
    ACTION_NAMES.cpp_header_parsing,
    ACTION_NAMES.cpp_module_compile,
    ACTION_NAMES.cpp_module_codegen,
]

_ALL_LINK_ACTIONS = [
    ACTION_NAMES.cpp_link_executable,
    ACTION_NAMES.cpp_link_dynamic_library,
    ACTION_NAMES.cpp_link_nodeps_dynamic_library,
]

def _impl(ctx):
    tool_paths = [
        tool_path(name = name, path = path)
        for name, path in ctx.attr.tool_paths.items()
    ]

    features = [
        feature(
            name = "default_compile_flags",
            enabled = True,
            flag_sets = [
                flag_set(
                    actions = _ALL_COMPILE_ACTIONS,
                    flag_groups = [flag_group(flags = ctx.attr.compile_flags)],
                ),
            ],
        ),
        feature(
            name = "cpp_standard",
            enabled = True,
            flag_sets = [
                flag_set(
                    actions = _ALL_CPP_COMPILE_ACTIONS,
                    flag_groups = [flag_group(flags = ctx.attr.cxx_flags)],
                ),
            ],
        ),
        feature(
            name = "default_link_flags",
            enabled = True,
            flag_sets = [
                flag_set(
                    actions = _ALL_LINK_ACTIONS,
                    flag_groups = [flag_group(flags = ctx.attr.link_flags)],
                ),
            ],
        ),
        # "dbg" y "opt" son nombres reservados: Bazel los activa solo segun
        # --compilation_mode (-c dbg / -c opt), sin que haya que seleccionarlos
        # a mano.
        feature(
            name = "dbg",
            flag_sets = [
                flag_set(
                    actions = _ALL_COMPILE_ACTIONS,
                    flag_groups = [flag_group(flags = ctx.attr.dbg_compile_flags)],
                ),
            ],
        ),
        feature(
            name = "opt",
            flag_sets = [
                flag_set(
                    actions = _ALL_COMPILE_ACTIONS,
                    flag_groups = [flag_group(flags = ctx.attr.opt_compile_flags)],
                ),
            ],
        ),
    ]

    return cc_common.create_cc_toolchain_config_info(
        ctx = ctx,
        toolchain_identifier = ctx.attr.toolchain_identifier,
        host_system_name = "local",
        target_system_name = "local",
        target_cpu = ctx.attr.target_cpu,
        target_libc = "local",
        compiler = ctx.attr.compiler,
        abi_version = "local",
        abi_libc_version = "local",
        tool_paths = tool_paths,
        cxx_builtin_include_directories = ctx.attr.builtin_include_directories,
        features = features,
    )

cc_toolchain_config = rule(
    implementation = _impl,
    attrs = {
        "toolchain_identifier": attr.string(mandatory = True),
        "compiler": attr.string(mandatory = True),
        "target_cpu": attr.string(mandatory = True),
        "tool_paths": attr.string_dict(mandatory = True),
        "builtin_include_directories": attr.string_list(default = []),
        "compile_flags": attr.string_list(default = []),
        "cxx_flags": attr.string_list(default = []),
        "link_flags": attr.string_list(default = []),
        "dbg_compile_flags": attr.string_list(default = []),
        "opt_compile_flags": attr.string_list(default = []),
    },
    provides = [CcToolchainConfigInfo],
)
