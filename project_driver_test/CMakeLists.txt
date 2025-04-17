cmake_minimum_required(VERSION 3.10)
project(driver_test)

# 指定头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/ui)
# set(LV_CONF_INCLUDE_SIMPLE OFF)
# 将指定目录下的 CMakeLists.txt 纳入当前构建流程。
add_subdirectory(${PROJECT_SOURCE_DIR}/ui/lvgl)
add_subdirectory(${PROJECT_SOURCE_DIR}/ui/lv_drivers)

# 指定编译器
set(CMAKE_C_COMPILER "/home/book/myself_exercise/100ask_imx6ull-sdk/ToolChain/arm-buildroot-linux-gnueabihf_sdk-buildroot/bin/arm-buildroot-linux-gnueabihf-gcc" CACHE STRING "Updated variable" FORCE)
# 指定路径宏
set(PATH_TO_SYS ${PROJECT_SOURCE_DIR}/sys/)
set(PATH_TO_UI ${PROJECT_SOURCE_DIR}/ui/)
# 指定链接库宏
set(GCC_USER_LINK_FLAGS "-lm")

# 设置输出文件
add_executable(${PROJECT_NAME} ${PATH_TO_SYS}/main.c ${PATH_TO_UI}/ui.c)

# 指定链接库
target_link_libraries(${PROJECT_NAME} PRIVATE ${GCC_USER_LINK_FLAGS})
target_link_libraries(${PROJECT_NAME} PRIVATE lvgl lvgl::examples lvgl::drivers)