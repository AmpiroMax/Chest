cmake_minimum_required(VERSION 3.10)

option(EDITOR_BUILD "Build map-editor executable" OFF)

# Проверка целевой системы
if(NOT DEFINED TARGET_SYSTEM)
    message(FATAL_ERROR "TARGET_SYSTEM is not defined. Please specify -DTARGET_SYSTEM=WIN or -DTARGET_SYSTEM=MAC.")
endif()

project(chest)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути к исходникам
file(GLOB_RECURSE CORE_SOURCES "core/*.cpp")
file(GLOB_RECURSE SYSTEMS_SOURCES "systems/*.cpp")
file(GLOB_RECURSE ADAPTERS_SOURCES "adapters/*.cpp")
file(GLOB_RECURSE FACTORIES_SOURCES "factories/*.cpp")
file(GLOB_RECURSE UTILS_SOURCES "utils/*.cpp")
file(GLOB_RECURSE MANAGERS_SOURCES "managers/*.cpp")
file(GLOB_RECURSE APPLICATION_SOURCES "applications/*.cpp")
file(GLOB_RECURSE SERVICES_SOURCES "services/*.cpp")

set(SOURCE_FILES
    main.cpp
    ${CORE_SOURCES}
    ${SYSTEMS_SOURCES}
    ${ADAPTERS_SOURCES}
    ${FACTORIES_SOURCES}
    ${UTILS_SOURCES}
    ${MANAGERS_SOURCES}
    ${APPLICATION_SOURCES}
    ${SERVICES_SOURCES}
)

# Пути к инклудам (можно добавить свои директории)
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/core
    ${CMAKE_SOURCE_DIR}/core/Components
    ${CMAKE_SOURCE_DIR}/systems
    ${CMAKE_SOURCE_DIR}/adapters
    ${CMAKE_SOURCE_DIR}/factories
    ${CMAKE_SOURCE_DIR}/utils
    ${CMAKE_SOURCE_DIR}/managers
    ${CMAKE_SOURCE_DIR}/applications
    /Users/ampiro/programs/libs/SFML/include
    /Users/ampiro/programs/libs/box2d/include
    /opt/homebrew/include
)

# set(IMGUI_SFML_FIND_SFML OFF CACHE BOOL "ImGui-SFML will not search SFML")  # <-- добавлено
# set(IMGUI_DIR ${CMAKE_SOURCE_DIR}/libs/imgui CACHE PATH "Path to Dear ImGui")
# add_subdirectory(libs/imgui-sfml)    # binding к SFML
# get_target_property(_defs ImGui-SFML COMPILE_DEFINITIONS)
# list(REMOVE_ITEM _defs IMGUI_DISABLE_OBSOLETE_NAV_INPUTS)
# set_target_properties(ImGui-SFML PROPERTIES COMPILE_DEFINITIONS "${_defs}")


# Системные параметры и линковка
if(TARGET_SYSTEM STREQUAL "WIN")
    set(CMAKE_SYSTEM_NAME Windows)
    set(CMAKE_C_COMPILER /opt/homebrew/bin/x86_64-w64-mingw32-gcc)
    set(CMAKE_CXX_COMPILER /opt/homebrew/bin/x86_64-w64-mingw32-g++)
    set(CMAKE_AR /opt/homebrew/bin/x86_64-w64-mingw32-ar)
    set(CMAKE_RANLIB /opt/homebrew/bin/x86_64-w64-mingw32-ranlib)
    set(CMAKE_LINKER /opt/homebrew/bin/x86_64-w64-mingw32-ld)
    set(CMAKE_NM /opt/homebrew/bin/x86_64-w64-mingw32-nm)
    set(CMAKE_STRIP /opt/homebrew/bin/x86_64-w64-mingw32-strip)
    set(CMAKE_RC_COMPILER /opt/homebrew/bin/x86_64-w64-mingw32-windres)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static")
    add_definitions(-DSFML_STATIC)

    link_directories(
        /Users/ampiro/programs/libs/build-win-sfml/lib
        /Users/ampiro/programs/libs/build-win-box2d/bin
        /Users/ampiro/programs/libs/SFML/extlibs/libs-mingw/x64
        /Users/ampiro/build-zlib/lib
    )

    set(LIBRARIES
        sfml-graphics-s
        sfml-window-s
        sfml-system-s
        sfml-audio-s
        sfml-network-s
        box2d
        glad
        glfw
        sajson
        freetype
        flac
        ogg
        vorbis
        vorbisenc
        vorbisfile
        z
        winmm
        gdi32
        opengl32
        dsound
        kernel32
        user32
        advapi32
        shell32
        ole32
        ws2_32
    )

elseif(TARGET_SYSTEM STREQUAL "MAC")
    set(CMAKE_SYSTEM_NAME Darwin)

    link_directories(
        /Users/ampiro/programs/libs/build-mac-sfml/lib
        /Users/ampiro/programs/libs/build-mac-box2d/bin
    )

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

    set(LIBRARIES
        sfml-graphics
        sfml-window
        sfml-system
        sfml-audio
        sfml-network
        box2d
        glad
        glfw
        sajson
    )

else()
    message(FATAL_ERROR "Unknown TARGET_SYSTEM: ${TARGET_SYSTEM}. Please specify WIN or MAC.")
endif()

message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message("LIBRARIES: ${LIBRARIES}")

# ───────── исполняемый файл «игры» ─────────
add_executable(chest ${SOURCE_FILES})
target_link_libraries(chest PRIVATE ${LIBRARIES})
# target_link_libraries(chest PRIVATE ${LIBRARIES} ImGui-SFML::ImGui-SFML)

# ───────── исполняемый файл «редактора» ─────────
if(EDITOR_BUILD)
    add_executable(chest_editor ${SOURCE_FILES})
    target_compile_definitions(chest_editor PRIVATE EDITOR_BUILD)
    target_link_libraries(chest_editor PRIVATE ${LIBRARIES})
    # target_link_libraries(chest_editor PRIVATE ${LIBRARIES} ImGui-SFML::ImGui-SFML)
endif()

message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message(STATUS "LIBRARIES: ${LIBRARIES}")
