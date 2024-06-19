cmake_minimum_required(VERSION 3.22)

project(pm LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "-Werror")
add_executable(pm main.cpp user_authentication.cpp)
target_link_libraries(pm PRIVATE nlohmann_json::nlohmann_json)
