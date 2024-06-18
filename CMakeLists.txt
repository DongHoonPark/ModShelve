cmake_minimum_required(VERSION 3.11)

project(ModShelve VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
  catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.6.0  # 해당 버전에 맞는 태그를 지정
)

FetchContent_MakeAvailable(catch2)

add_library(ModShelve src/ModShelve.cpp)
target_include_directories(ModShelve PUBLIC include)

enable_testing()

add_executable(ModShelveTest test/ModShelveTest.cpp)
target_link_libraries(ModShelveTest PRIVATE ModShelve Catch2::Catch2WithMain)

add_test(NAME ModShelveUnitTest COMMAND ModShelveTest)
