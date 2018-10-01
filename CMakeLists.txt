cmake_minimum_required(VERSION 3.12)
project(lexer+pasrser)

set(CMAKE_CXX_STANDARD 11)

add_executable(CSE340-02 task.cc project2.cc lexer.cc inputbuf.cc)