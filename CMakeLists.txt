cmake_minimum_required(VERSION 3.16)

project(ls)
set(CMAKE_CXX_CLANG_FORMAT "clang-format -style=clang-format.json -fallback-style=Google")

set(CMAKE_CXX_STANDARD 20)
file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(ls ${SRC_FILES})


target_link_libraries(ls PRIVATE ${CMAKE_CXX_STANDARD_LIBRARIES})
target_link_libraries(ls PRIVATE pthread)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -ggdb -fsanitize=leak -fno-omit-frame-pointer")
set(CMAKE_LINKER_FLAGS_DEBUG "${CMAKE_LINKER_FLAGS_DEBUG} -fsanitize=address -fsanitize=leak -ggdb -fno-omit-frame-pointer")


install(TARGETS ls RUNTIME DESTINATION bin)
