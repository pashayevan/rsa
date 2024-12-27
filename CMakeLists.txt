cmake_minimum_required(VERSION 3.10)

project(RSAExample)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(GMP REQUIRED)

add_library(rsa_utils rsa_utils.cpp)

add_executable(main main.cpp)

target_link_libraries(rsa_utils PUBLIC GMP::GMPXX)
target_link_libraries(main PRIVATE rsa_utils GMP::GMPXX)

target_include_directories(rsa_utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
