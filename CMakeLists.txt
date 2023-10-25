cmake_minimum_required(VERSION 3.10)

#set(CMAKE_BUILD_TYPE Debug)

project(Steering_Behavior VERSION 1.0)

#only build for windows
IF (WIN32)
    #include sdl
    find_package(SDL2 QUIET)
    if(SDL2_FOUND)
        message(STATUS "Using SDL2 via find_package")
    endif()
    
    #add project files
    set (Project_SOURCES
            ${SOURCE_DIR}Main.cpp
            ${SOURCE_DIR}Bot.cpp
            ${SOURCE_DIR}CollisionDetection.cpp
            ${SOURCE_DIR}Entity.cpp
            ${SOURCE_DIR}Params.cpp
            ${SOURCE_DIR}Matrix.cpp
            ${SOURCE_DIR}SteeringController.cpp
        )
    
    add_executable( Steering_Behavior ${Project_SOURCES} )
    
    #link sdl
    target_link_libraries(Steering_Behavior PRIVATE SDL2::SDL2)
    target_link_libraries(Steering_Behavior PRIVATE SDL2::SDL2main)
ENDIF()

#add tests
enable_testing()
add_subdirectory(tests)
