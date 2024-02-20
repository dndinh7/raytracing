# CMakeList.txt : CMake project for raytracing, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (raytracing "raytracing.cpp" "raytracing.h" "vec3.h" "vec3.cpp" "color.h" "ray.h" "ray.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET raytracing PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
