cmake_minimum_required(VERSION 3.09)

# Required C++ standart.
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_RELEASE, "-O2 -Wall -DNDEBUG")
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# A subsystem specification to remove a console window.
if (WIN32)
    set(Subsustem "WIN32")
endif()

# Project name.
set(Name "TestTask_4AGames_AVM")

# Project version.
project(${Name} VERSION 1.0)

# Project files.
set(Base "Base/Object.hpp" "Base/Object.cpp"
    "Base/Wall.hpp" "Base/Wall.cpp"
    "Base/Bullet.hpp" "Base/Bullet.cpp")
set(Controllers "Controllers/ResourceController.hpp" "Controllers/ResourceController.cpp"
    "Controllers/MainController.hpp" "Controllers/MainController.cpp"
    "Controllers/CollisionController.hpp" "Controllers/CollisionController.cpp")
set(Managers "Managers/BulletManager.hpp" "Managers/BulletManager.cpp"
     "Managers/WallManager.hpp" "Managers/WallManager.cpp")
set(Main "main.cpp")

# Target executable.
add_executable(${Name} ${Subsustem} ${Main} ${Base} ${Controllers} ${Managers})

# Source folder and libraries include directories.
target_include_directories(${Name} PUBLIC "External/SFML/Include")
target_include_directories(${Name} PUBLIC "External/ImGui_SFML/Include")
target_include_directories(${Name} PUBLIC "${SOURCE_DIR}")

# Copy necessary resources to the binary folder.
file(COPY "Resources/Wall.jpg" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/Resources")
file(COPY "Resources/Bullet.png" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/Resources")

# Library linkage for debug and release builds.
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(ImGuiLibs "External/ImGui_SFML/Lib/Debug")
    set(SfmlLibs "External/SFML/Lib/Debug")
    #target_link_directories(${Name} PUBLIC ${PROJECT_SOURCE_DIR}/${ImGuiLibs})
    #target_link_directories(${Name} PUBLIC ${PROJECT_SOURCE_DIR}/${SfmlLibs})
    target_link_libraries(${Name} ImGui-SFML)
    target_link_libraries(${Name} sfml-main-d)
    target_link_libraries(${Name} sfml-window-d)
    target_link_libraries(${Name} sfml-system-d)
    target_link_libraries(${Name} sfml-graphics-d)
    # Copy all necessary debug .dll files to the binary folder.
    if (WIN32)
        file(COPY "${ImGuiLibs}/ImGui-SFML.dll" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
        file(COPY "${SfmlLibs}/sfml-window-d-2.dll" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
        file(COPY "${SfmlLibs}/sfml-system-d-2.dll" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
        file(COPY "${SfmlLibs}/sfml-graphics-d-2.dll" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
    endif()
else()
    set(ImGuiLibs "External/ImGui_SFML/Lib/Release")
    set(SfmlLibs "External/SFML/Lib/Release")
    #target_link_directories(${Name} PUBLIC ${PROJECT_SOURCE_DIR}/${ImGuiLibs})
    #target_link_directories(${Name} PUBLIC ${PROJECT_SOURCE_DIR}/${SfmlLibs})
    target_link_libraries(${Name} ImGui-SFML)
    target_link_libraries(${Name} sfml-main)
    target_link_libraries(${Name} sfml-window)
    target_link_libraries(${Name} sfml-system)
    target_link_libraries(${Name} sfml-graphics)
    # Copy all necessary release .dll files to the binary folder.
    if (WIN32)
        file(COPY "${ImGuiLibs}/ImGui-SFML.dll" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
        file(COPY "${SfmlLibs}/sfml-window-2.dll" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
        file(COPY "${SfmlLibs}/sfml-system-2.dll" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
        file(COPY "${SfmlLibs}/sfml-graphics-2.dll" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")
    endif()
endif()
