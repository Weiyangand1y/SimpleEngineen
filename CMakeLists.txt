cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")

cmake_host_system_information(RESULT CPU_NUMBER_OF_LOGICAL_CORES QUERY NUMBER_OF_LOGICAL_CORES)
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP${CPU_NUMBER_OF_LOGICAL_CORES}>)


set(CMAKE_BUILD_TYPE "Debug")
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DDEBUG)
    set(BOX2D_PATH D:/a_folder/box2d-main/box2d-main/build/bin/Debug)
    # 这里可以添加一些只在Debug模式下需要的代码
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(BOX2D_PATH D:/a_folder/box2d-main/box2d-main/build/bin/Release)
    add_definitions(-DNO_CONSOLE)
    # 这里可以添加一些只在Release模式下需要的代码
endif()
# -----
file(GLOB IMGUI_FILE D:/又一个文件夹/imgui_in_use/*.cpp)
file(GLOB_RECURSE L1_SRC ./L1/*.cpp)
file(GLOB_RECURSE L2_SRC ./L2/*.cpp)
file(GLOB_RECURSE L3_SRC ./L3/*.cpp)
file(GLOB_RECURSE L4_SRC ./L4/*.cpp)
file(GLOB_RECURSE L3_5_SRC ./L3.5/*.cpp)

set(ASSIMP_PATH D:/a_folder/Assimp/)

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
    D:/a_folder/sol2-develop/sol2-develop/single/single/include
    D:/a_folder/fmt-master/fmt-master/include
    D:/a_folder/box2d-main/box2d-main/include
    ${ASSIMP_PATH}/include
)

if(MSVC)
    
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
    add_compile_options(/wd26451)
    add_compile_options(/wd4312)
    add_compile_options("/utf-8")
endif()


add_executable(test01 
                ./Test/test01.cpp
                D:/一个文件夹/aLib/glad/src/glad.c
                ${L1_SRC}
                ${L2_SRC}
                ${L4_SRC}
                ${IMGUI_FILE}
                )

target_compile_options(test01 PRIVATE /D_CRT_SECURE_NO_WARNINGS )

#-----

# add_executable(test02
#                 ./Test/test02.cpp
# )

# find_package(Poco COMPONENTS Foundation Net REQUIRED)
# target_link_libraries(test02 PRIVATE Poco::Foundation Poco::Net)

add_executable(test03
                ./Test/test03.cpp
)


add_executable(test04
                ./Test/test04.cpp
)

add_executable(test05
                ./Test/test05.cpp
                ./L1/Object/SignalObject.cpp
)



target_link_directories(test04 PRIVATE D:/a_folder/box2d-main/box2d-main/build/bin/Debug)
target_link_libraries(test04 PRIVATE box2d)


target_link_directories(test01 PRIVATE
    D:/一个文件夹/aLib/glfw-3.3.8.bin.WIN64/lib-vc2022
    D:/一个文件夹/aLib/lua
)
target_link_libraries(test01 PRIVATE glfw3 LuaLib)

#------------------------------------------------------
add_executable(test06
                ./Test/test06.cpp
                D:/一个文件夹/aLib/glad/src/glad.c
                ${L1_SRC}
                # ${L2_SRC}
                ${L3_SRC}
                # ${IMGUI_FILE}
)
target_link_directories(test06 PRIVATE
    D:/一个文件夹/aLib/glfw-3.3.8.bin.WIN64/lib-vc2022
    D:/一个文件夹/aLib/lua
    
)


target_link_libraries(test06 PRIVATE 
                        glfw3 
                        LuaLib           
                        )
# -----------------------------------
add_executable(test07
                ./Test/test07.cpp
                D:/一个文件夹/aLib/glad/src/glad.c
                ${L1_SRC}
                # ${L2_SRC}
                ${L3_SRC}
                # ${IMGUI_FILE}
)
target_link_directories(test07 PRIVATE
    D:/一个文件夹/aLib/glfw-3.3.8.bin.WIN64/lib-vc2022
    D:/一个文件夹/aLib/lua
    D:/a_folder/box2d-main/box2d-main/build/bin/Debug
)


target_link_libraries(test07 PRIVATE 
                        glfw3 
                        LuaLib
                        box2d            
                        )
# -------------------------------------------------------




add_executable(test08
                # WIN32
                ./Test/test08.cpp
                D:/一个文件夹/aLib/glad/src/glad.c
                ${L1_SRC}
                 ${L2_SRC}
                ${L3_SRC}
                 ${IMGUI_FILE}
)

target_link_directories(test08 PRIVATE
    D:/一个文件夹/aLib/glfw-3.3.8.bin.WIN64/lib-vc2022
    D:/一个文件夹/aLib/lua
    ${BOX2D_PATH}
)


target_link_libraries(test08 PRIVATE 
                        glfw3 
                        LuaLib
                        box2d            
                        )
# ------------------------------------------
add_executable(test09
                # WIN32
                ./Test/test09.cpp
                D:/一个文件夹/aLib/glad/src/glad.c
                ${L1_SRC}
                ${L2_SRC}
                ${IMGUI_FILE}
                ${L3_5_SRC}
)
target_link_directories(test09 PRIVATE
    D:/一个文件夹/aLib/glfw-3.3.8.bin.WIN64/lib-vc2022
    D:/一个文件夹/aLib/lua
    ${ASSIMP_PATH}/lib/x64
)


target_link_libraries(test09 PRIVATE 
                        glfw3 
                        LuaLib   
                        assimp-vc143-mt.lib       
                        )