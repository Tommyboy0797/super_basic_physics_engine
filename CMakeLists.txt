cmake_minimum_required(VERSION 3.28)
project(PhysicsEngine LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Fetch SFML 3.0 from GitHub
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
    GRAPHICS)
FetchContent_MakeAvailable(SFML)

# Add the executable and compile features
add_executable(PhysicsEngine main.cpp)  # Update this if your main.cpp is elsewhere
set_target_properties(PhysicsEngine PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
target_compile_features(PhysicsEngine PRIVATE cxx_std_17)

# Link the SFML graphics, window, and system modules
target_link_libraries(PhysicsEngine PRIVATE SFML::Graphics SFML::Window SFML::System)


