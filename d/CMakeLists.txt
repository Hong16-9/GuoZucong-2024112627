# 指定CMake的最低版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(no7)

# 设置C++标准为C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
#这个是为了代码的自动补全用的
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 查找第三方的包，这里以第三方的OpenCV为例子（opencv将在后面的课程涉及）
find_package(OpenCV REQUIRED)

# 添加可执行文件
add_executable(no7 no7.cpp)

# 链接OpenCV库
target_link_libraries(no7 ${OpenCV_LIBS})

# 包含OpenCV的头文件目录
target_include_directories(no7 PUBLIC ${OpenCV_INCLUDE_DIRS})

# 如果有多个源文件和头文件，可以这样组织：
# set(SOURCES
#     main.cpp
#     src/file1.cpp
#     src/file2.cpp
# )
# set(HEADERS
#     include/header1.h
#     include/header2.h
# )
# add_executable(cut ${SOURCES} ${HEADERS})

# 如果头文件在多个不同的目录下，可以这样添加：
# target_include_directories(cut PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/include1
#     ${CMAKE_CURRENT_SOURCE_DIR}/include2
# )
