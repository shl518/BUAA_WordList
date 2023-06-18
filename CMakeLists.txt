cmake_minimum_required(VERSION 3.24)
project(develop)

set(CMAKE_CXX_STANDARD 14)


##google test
#enable_testing()
add_subdirectory(lib)
include_directories(lib/googletest/include googletest)

include_directories(src/include)
add_executable(coretest tests/coretest/coretest.cpp src/core/API.cpp src/include/Word.h src/include/API.h src/core/Graph.cpp src/core/Utils.cpp src/include/Utils.h src/core/Word.cpp src/preprocess/Input.cpp src/HelloWorld.cpp src/include/Const.h src/include/Result.h src/preprocess/Input.h src/postprocess/Output.cpp src/core/Config.cpp src/core/Controller.cpp src/error/Error.cpp src/include/Error.h)
target_link_libraries(coretest gtest gtest_main)

##

add_executable(develop src/preprocess/Input.cpp src/preprocess/Input.h src/postprocess/Output.cpp src/main.cpp)

# add_compile_options(-fprofile-arcs -ftest-coverage)

##生成动态链接库
#add_library(core SHARED src/core/API.h src/core/API.cpp  src/core/Controller.h src/core/Controller.cpp src)
#add_library(core SHARED src/core/API.cpp src/core/Word.h src/core/API.h src/core/Graph.cpp src/core/Utils.cpp src/core/Utils.h src/core/Word.cpp src/core/Const.h src/core/Result.h src/core/Config.cpp src/core/Controller.cpp src/error/Error.cpp src/error/ErrorCode.h src/error/Error.h)
add_library(core SHARED src/core/API.cpp src/core/Graph.cpp src/core/Utils.cpp src/core/Word.cpp src/core/Config.cpp src/core/Controller.cpp src/error/Error.cpp)
target_link_libraries(develop core)

# set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)