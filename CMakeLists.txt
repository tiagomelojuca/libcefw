cmake_minimum_required(VERSION 3.24)
include(FetchContent)

project(libcefw)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        703bd9caab50b139428cea1aaff9974ebee5742e
)
FetchContent_MakeAvailable(googletest) # Fills googletest_SOURCE_DIR, since it calls FetchContent_Populate

set(libcefw_SOURCE_DIR "src")
set(libcefw_TESTS_DIR "tests")

add_library(
  libcefw
  STATIC
  "${libcefw_SOURCE_DIR}/cestring.c"
)

add_executable(
  RunTests
  ${libcefw_TESTS_DIR}/main.cpp
  ${libcefw_TESTS_DIR}/CeStringTest.cpp
)

target_include_directories(
  RunTests
  PRIVATE
  "${googletest_libcefw_SOURCE_DIR}/googletest/include"
  "${libcefw_SOURCE_DIR}"
)

target_link_libraries(
  RunTests
  PRIVATE
  gtest
  libcefw
)
