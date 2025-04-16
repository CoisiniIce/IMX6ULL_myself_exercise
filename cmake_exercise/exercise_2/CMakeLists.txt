cmake_minimum_required(VERSION 3.10.2)
project(TestProject LANGUAGES C)

# 设置输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
# 设置库文件输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
# 设置静态库路径
link_directories(${PROJECT_SOURCE_DIR}/lib)
# 设置头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)
# 自动搜索源文件
file(GLOB C_FILES_LIST ${PROJECT_SOURCE_DIR}/src/*.c)
# 制作库文件
add_library(calc SHARED ${C_FILES_LIST})
# 设置源文件和目标文件
add_executable(App ${PROJECT_SOURCE_DIR}/main.c)
# 链接静态库
target_link_libraries(App calc)