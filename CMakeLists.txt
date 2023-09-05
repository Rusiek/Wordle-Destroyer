cmake_minimum_required(VERSION 3.16.3)

# set(CMAKE_AUTOMOC ON)
# set(CMAKE_INCLUDE_CURRENT_DIR ON)

project(WordleSolver C CXX)

add_executable(${PROJECT_NAME} 
    main.cpp
    engine/algorithm.cpp
    engine/baseline.cpp
    engine/randomAccess.cpp)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
target_compile_options(${PROJECT_NAME} PRIVATE -O3 -march=native)

find_program(CLANG_TIDY_EXE NAMES "clang-tidy" REQUIRED)
set(CLANG_TIDY_COMMAND ${CLANG_TIDY_EXE}
    -checks=engine/*,clang-analyzer-*,cppcoreguidelines-*,google-*,misc-*,modernize-*,performance-*,portability-*,readability-*
    -warnings-as-errors=*
    -header-filter=.*
    -fix
    -format-style=file
    -quiet
    -p=${CMAKE_BINARY_DIR}
    -extra-arg=-Wno-unknown-warning-option
    -extra-arg=-Wno-unknown-cuda-version
    -extra-arg=-Wno-unknown-attribute
    -extra-arg=-Wno-ignored-attributes
    -extra-arg=-Wno-deprecated-declarations
    -extra-arg=-Wno-unused-command-line)
add_executable(WordleSolver::clang-tidy ALIAS ${PROJECT_NAME})
set_target_properties(WordleSolver PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_COMMAND}")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(${PROJECT_NAME} Threads::Threads)
