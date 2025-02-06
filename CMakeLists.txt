cmake_minimum_required(VERSION 3.22 FATAL_ERROR)
project(darkstar LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_library(darkstar)

set(DARKSTAR_DIRECTORY ${CMAKE_CURRENT_LIST_DIR} CACHE INTERNAL "")

###########
# VERSION #
###########

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

#######################
# CONFIGURATION TYPE #
#######################

set_target_properties(darkstar PROPERTIES
    CMAKE_CXX_FLAGS_RELWITHDEBUG "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -DDEBUG"
    CMAKE_C_FLAGS_RELWITHDEBUG "${CMAKE_C_FLAGS_RELWITHDEBINFO} -DDEBUG"
    CMAKE_EXE_LINKER_FLAGS_RELWITHDEBUG "${CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO}"
    CMAKE_CXX_FLAGS_RELTEST "${CMAKE_CXX_FLAGS_RELEASE}"
    CMAKE_C_FLAGS_RELTEST "${CMAKE_C_FLAGS_RELEASE}"
    CMAKE_EXE_LINKER_FLAGS_RELTEST "${CMAKE_EXE_LINKER_FLAGS_RELEASE}"
)

foreach(CONFIG RelWithDebug RelTest)
    target_compile_definitions(darkstar PRIVATE $<$<CONFIG:${CONFIG}>:${CMAKE_C_FLAGS_${CONFIG}}>)
    target_link_options(darkstar PRIVATE $<$<CONFIG:${CONFIG}>:${CMAKE_EXE_LINKER_FLAGS_${CONFIG}}>)
endforeach()

#############################
# CONFIGURATION DEFINITION #
#############################

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

########################
# PLATFORM DEFINITION #
########################

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        message(STATUS "Configurating for Linux")
        target_compile_definitions(
            darkstar
            PUBLIC
            "___DARK_LINUX"
        )
	target_link_libraries(darkstar PRIVATE m)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        message(STATUS "Configurating for Darwin")
        target_compile_definitions(
            darkstar
            PUBLIC
            "___DARK_DARWIN"
        )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
        message(STATUS "Configurating for Windows")
        target_compile_definitions(
            darkstar
            PUBLIC
            "___DARK_WINDOWS"
        )
else()
       message(SEND_ERROR "Failed to detect platform")
endif()

############
# TESTING #
############

if(DARK_TEST_ENABLE)
  enable_testing()
  add_subdirectory(test)
endif()

############
# DOCUMENT #
############

if(DARK_DOC_GENERATE)
  configure_file(document/Doxyfile.in ${CMAKE_BINARY_DIR}/Doxyfile @ONLY)
endif()

################
# SUBDIRECTORY #
################

add_subdirectory(include)
add_subdirectory(library)
add_subdirectory(source)
