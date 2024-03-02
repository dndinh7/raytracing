# CMakeList.txt : CMake project for raytracing, include source and define
# project specific logic here.
#
set(SDL2_PATH "${PROJECT_SOURCE_DIR}/external/SDL2")

# Get SDL paths based on system
if(CMAKE_SIZEOF_VOID_P EQUAL 8) # 64 bits
    set(SDL2_LIBRARY "${SDL2_PATH}/lib/x64")
else() # 32 bits
    set(SDL2_LIBRARY "${SDL2_PATH}/lib/x86")
endif()


# SDL2 header
include_directories("${SDL2_PATH}/include")

# Link library
link_directories(${SDL2_LIBRARY})


# Add source to this project's executable.
add_executable (${PROJECT_NAME} "raytracing.cpp" "raytracing.h" "vec3.h" "vec3.cpp" "color.h" "ray.h" "ray.cpp" "SDLApp.h" "SDLApp.cpp" "shape.h" "sphere.h"  "hittable.h" "hittable_list.h" "rt_util.h" "interval.h" "camera.h" "image.h")
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY}/SDL2main.lib ${SDL2_LIBRARY}/SDL2.lib)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET raytracing PROPERTY CXX_STANDARD 20)
endif()

# Copy SDL2.dll to the output directory after building
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${SDL2_LIBRARY}/SDL2.dll" $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# TODO: Add tests and install targets if needed.
