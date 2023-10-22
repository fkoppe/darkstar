cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
project(darkstar LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(darkstar)

enable_testing()

set(DARK_VERSION_MAJOR 0 CACHE INTERNAL "")
set(DARK_VERSION_MINOR 1 CACHE INTERNAL "")
set(DARK_VERSION_PATCH 0 CACHE INTERNAL "")
set(DARK_VERSION_TWEAK 0 CACHE INTERNAL "")

target_compile_definitions(
    darkstar
    PUBLIC
    ___DARK_VERSION_MAJOR=${DARK_VERSION_MAJOR}
    ___DARK_VERSION_MINOR=${DARK_VERSION_MINOR}
    ___DARK_VERSION_STAGE=${DARK_VERSION_PATCH}
    ___DARK_VERSION_PATCH=${DARK_VERSION_TWEAK}
)

target_compile_definitions(
    darkstar
    PUBLIC
    $<$<CONFIG:Debug>:
    ___DARK_CONFIGURATION="Debug"
    ___DARK_DEBUG
    ___DARK_DEBINFO
    >
)
target_compile_definitions(
    darkstar
    PUBLIC
    $<$<CONFIG:RelWithDebug>:
    ___DARK_CONFIGURATION="RelWithDebug"
    ___DARK_DEBUG
    ___DARK_DEBINFO
    ___DARK_RELEASE
    >
)
target_compile_definitions(
    darkstar
    PUBLIC
    $<$<CONFIG:RelWithDebInfo>:
    ___DARK_CONFIGURATION="RelWithDebInfo"
    ___DARK_DEBINFO
    ___DARK_RELEASE
    >
)
target_compile_definitions(
    darkstar
    PUBLIC
    $<$<CONFIG:RelTest>:
    ___DARK_CONFIGURATION="RelTest"
    ___DARK_DEBUG
    ___DARK_DEBINFO
    ___DARK_RELEASE
    >
)
target_compile_definitions(
    darkstar
    PUBLIC
    $<$<CONFIG:Release>:
    ___DARK_CONFIGURATION="Release"
    ___DARK_RELEASE
    >
)
target_compile_definitions(
    darkstar
    PUBLIC
    $<$<CONFIG:MinSizeRel>:
    ___DARK_CONFIGURATION="MinSizeRel"
    ___DARK_RELEASE
    ___DARK_MINSIZE
    >
)

add_subdirectory(include)
add_subdirectory(source)
add_subdirectory(test)
