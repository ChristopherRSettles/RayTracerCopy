cmake_minimum_required(VERSION 3.9)
project(RayTracerCopy)

set(CMAKE_CXX_STANDARD 11)

add_executable(RayTracerCopy main.cpp Shapes/Shape.h Shapes/Sphere.cpp Shapes/Sphere.h Control/Ray.cpp Control/Ray.h Control/Color.cpp Control/Color.h Control/vec3.h Control/GlobalConstants.h)