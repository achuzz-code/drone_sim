cmake_minimum_required(VERSION 3.10)

# Define your project name and language
project(drone_sim LANGUAGES CXX)

add_executable(my_program config.hpp main.cpp)
find_package(Bullet REQUIRED)#chnge to bulletphy

# Add the main source file to create the executable

# Specify the include directories for the executable
# The "PUBLIC" keyword means that these include directories
# will also be available to any other targets that link to "my_program"
target_include_directories(my_program PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/classes
    /usr/include
    /usr/include/bullet
)
target_link_libraries(
  my_program
  PRIVATE
  raylib
  BulletDynamics
  BulletCollision
  LinearMath
)
