cmake_minimum_required(VERSION 3.8)
project(ChessGame)

# less than 13.2 version will not work
if (CMAKE_CXX_COMPILER_VERSION LESS 13.2)
    message(FATAL_ERROR "Insufficient gcc version")
endif()

#where to find CMake modules and extra find packages (if any)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# specify the C++ standard
set(CMAKE_CXX_STANDARD 17)

# set our library and executable destination dirs
set(LIBRARY_OUTPUT_PATH "${CMAKE_BINARY_DIR}/lib")
set(EXECUTABLE_OUTPUT_PATH "${CMAKE_BINARY_DIR}")

# put all source files into a variable
file(GLOB_RECURSE SOURCES "src/*.cpp")

# put all header files invariable
file(GLOB_RECURSE HEADERS "include/*.h")

# put all libraries into a variable
file(GLOB_RECURSE LIBRARIES "lib/*.a" "lib/*.so")

# add your source to the executable
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# link your libraries to your executable
foreach(LIBRARY ${LIBRARIES})
    target_link_libraries(${PROJECT_NAME} "${LIBRARY}")
endforeach(LIBRARY)

# define the installation path for the make install command
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

# Add make format target
add_custom_target(format
    COMMAND ${CMAKE_COMMAND} -E echo "Running clang-format..."
    COMMAND clang-format -i -style=file ${SOURCES} ${HEADERS}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
)

# Set the target format to depend on your project
add_dependencies(format ${PROJECT_NAME})
