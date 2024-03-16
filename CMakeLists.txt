cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")

cmake_host_system_information(RESULT CPU_NUMBER_OF_LOGICAL_CORES QUERY NUMBER_OF_LOGICAL_CORES)
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP${CPU_NUMBER_OF_LOGICAL_CORES}>)

add_definitions(-DDEBUG)
file(GLOB IMGUI_FILE D:/又一个文件夹/imgui_in_use/*.cpp)
file(GLOB_RECURSE L1_SRC ./L1/*.cpp)
file(GLOB_RECURSE L2_SRC ./L2/*.cpp)
file(GLOB_RECURSE L3_SRC ./L3/*.cpp)

project(SimpleEngineen)

include_directories(
    .
    D:/a_folder/spdlog-1.x/spdlog-1.x/include
    D:/a_folder/cpp_header_only_lib
    D:/一个文件夹/aLib/glfw-3.3.8.bin.WIN64/include
    D:/一个文件夹/aLib/glad/include
    D:/又一个文件夹/glm
    D:/又一个文件夹/stb-master
    D:/a_folder/lua/lua-5.4.6/src
    D:/又一个文件夹/imgui_in_use
)

add_executable(test01 
                ./Test/test01.cpp
                D:/一个文件夹/aLib/glad/src/glad.c
                ${L1_SRC}
                )


if(MSVC)
    target_compile_options(test01 PRIVATE /D_CRT_SECURE_NO_WARNINGS )
endif()


target_link_directories(test01 PRIVATE
    D:/一个文件夹/aLib/glfw-3.3.8.bin.WIN64/lib-vc2022
    D:/一个文件夹/aLib/lua
)


target_link_libraries(test01 PRIVATE glfw3 LuaLib)