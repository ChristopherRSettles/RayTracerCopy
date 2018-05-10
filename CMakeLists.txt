cmake_minimum_required(VERSION 3.9)
project(RayTracerCopy)

set(CMAKE_CXX_STANDARD 11)

add_executable(RayTracerCopy
        main.cpp
        Shapes/Box.h Shapes/Box.cpp Shapes/Plane.h Shapes/Plane.cpp Shapes/Shape.h Shapes/Sphere.cpp Shapes/Sphere.h
        Shapes/Capsule.cpp Shapes/Capsule.h
        Control/Ray.cpp Control/Ray.h Control/Color.cpp Control/Color.h Control/vec3.h Control/GlobalConstants.h
        Control/Lighting/DirectionalLight.cpp Control/Lighting/DirectionalLight.h Control/Lighting/Light.h
        Control/BoundingVolume.cpp Control/camera.h
        "Deleted Classes/ToReAdd/nonbvhmain.cpp" Shapes/Triangle.cpp Shapes/Triangle.h
        parser.cpp parser.h
        )

add_executable(parserTesting
        parser.cpp parser.h parserTest.cpp
        Shapes/Triangle.cpp Shapes/Triangle.h
        Shapes/Shape.h
        Control/Ray.cpp Control/Ray.h
        Control/vec3.h)