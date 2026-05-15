cmake_minimum_required(VERSION 3.15)
project(ChronoBloom_TD)

# 你的代码里用到了 std::any，这要求必须使用 C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 搜集当前目录下所有的 .cpp 和 .h 文件
file(GLOB SOURCES "*.cpp" "*.h")

# 生成可执行文件
add_executable(${PROJECT_NAME} ${SOURCES}
        DatabaseHelper.h)

# 寻找本地安装的 SFML 库
find_package(SFML COMPONENTS Graphics Window System REQUIRED)

# 将 SFML 链接到你的游戏程序上
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Window SFML::System)

# 每次编译时，自动将 Assets 文件夹复制到可执行文件所在的输出目录
file(COPY Assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# 在 find_package(SFML ...) 下面加上这行
find_package(SQLite3 REQUIRED)

# 在 target_link_libraries 里把 SQLite::SQLite3 加上
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Window SFML::System SQLite::SQLite3)