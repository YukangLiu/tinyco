cmake_minimum_required(VERSION 2.8)
#在项目中显示所有源码
file(GLOB files ./*.cc ./*.h)
add_custom_target(files SOURCES ${files})
 
#g++编译参数
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -std=c++11 -fPIC ")
set(CMAKE_BUILD_TYPE "Release")
#第三方库库文件目录，相当于gcc的-L参数。似乎只能绝对路径
#link_directories("/root/soft/boost_1_67_0/lib" "/usr/lib64/mysql"
#    "/mnt/hgfs/D/qtproj/dist/lib" "/root/dll_ln/")
#头文件的搜索路径，相当于指定gcc的-I参数。可以相对路径
include_directories(".")
 
#项目名称
project(tinyco)
#编译项目所需源码
AUX_SOURCE_DIRECTORY(. SRC1)
 
set(SRC ${SRC1} )
 
#list(APPEND <list><element> [<element> ...])
#list(REMOVE_ITEM SRC "./websocket//socket.io-client-cpp_test.cpp"
   # "./websocket//singleton_test_class1.cpp" "./async.cpp" "./client.cpp"
   # "./test.cpp")
list(SORT SRC)
message(${SRC})
 
#将module_service中所有源文件（不包括头文件）保存到变量SRC_MODULE中（不包括子目录）
#AUX_SOURCE_DIRECTORY(kikichatroom SRC_MODULE)
#set(SRC_MODULE
#    "module_service/module_i_thread.cpp"
#    "module_service/module_singleton_base.cpp"
#    )
 
add_executable(${PROJECT_NAME} "main.cc" ${SRC} )
 
#添加链接库,相同于指定-l参数
target_link_libraries (${PROJECT_NAME}  pthread)