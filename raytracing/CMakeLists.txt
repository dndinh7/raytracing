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


# Find CUDA package
find_package(CUDA 12.6 REQUIRED)

# Include CUDA headers
include_directories(${CUDA_INCLUDE_DIRS})

# Automatically include all header files
file(GLOB_RECURSE HEADER_FILES "headers/*.h")
file(GLOB_RECURSE SOURCE_FILES "headers/*.cpp")

# Add source to this project's executable.
add_executable(${PROJECT_NAME} 
    "raytracing.cpp"
    ${HEADER_FILES}
    ${SOURCE_FILES}
    "cuda/tracer.cu"
)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY}/SDL2main.lib ${SDL2_LIBRARY}/SDL2.lib)

# Set CUDA source properties
set_target_properties(${PROJECT_NAME} PROPERTIES
    CUDA_SEPARABLE_COMPILATION ON
)

target_link_libraries(${PROJECT_NAME} 
    ${SDL2_LIBRARY}/SDL2main.lib 
    ${SDL2_LIBRARY}/SDL2.lib
    ${CUDA_LIBRARIES}
)

# Copy SDL2.dll to the output directory after building
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${SDL2_LIBRARY}/SDL2.dll" $<TARGET_FILE_DIR:${PROJECT_NAME}>)

# TODO: Add tests and install targets if needed.
