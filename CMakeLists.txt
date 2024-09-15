cmake_minimum_required(VERSION 2.8)
project(libcefw)

add_executable(
    RunTests
    tests/main.c
    src/cestring.c
)
