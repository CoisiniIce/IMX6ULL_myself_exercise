cmake_minimum_required(VERSION 3.10.2)
project(TestProject)

# 头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)
# 自动搜索源文件
file(GLOB MAIN_SRC ${PROJECT_SOURCE_DIR}/src/*.c)
# 设置输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)
# 设置源文件和目标文件
add_executable(App ${MAIN_SRC})