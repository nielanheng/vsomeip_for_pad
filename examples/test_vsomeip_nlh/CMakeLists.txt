# Copyright (C) 2015-2017 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

cmake_minimum_required (VERSION 2.8.7) # cmake的最低版本
project(vSomeIPServiceExample)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")    # 设置编译选项 ，如果编译器支持 -std=c++11，则没有理由使用 -std=c++0x。

# 查找到指定的预编译库，并将它的路径存储在变量中。默认的搜索路径为 cmake 包含的系统库，因此如果是 NDK 的公共库只需要指定库的 name 即可
find_package (Threads REQUIRED)
include_directories("/home/nlh/vsomeip-3.1.20.3")
link_directories("/usr/local/lib")
include_directories(${VSOMEIP_INCLUDE_DIRS})
include_directories(${Boost_INCLUDE_DIR})
find_package(vsomeip3 REQUIRED)
# 生成可执行文件
add_executable(service_example ./service_example.cpp)
# request和非request共用一个service
# 设置 target 需要链接的库
target_link_libraries(service_example vsomeip3 pthread)

add_executable (client_example ./client_example.cpp)
target_link_libraries(client_example vsomeip3 ${Boost_LIBRARIES})

add_executable(request_example ./request_example.cpp)
target_link_libraries(request_example vsomeip3 ${Boost_LIBRARIES} pthread)

add_executable(service_example_sn ./service_example_sn.cpp)
target_link_libraries(service_example_sn vsomeip3 pthread)

add_executable(client_example_sn ./client_example_sn.cpp)
target_link_libraries(client_example_sn vsomeip3 ${Boost_LIBRARIES} pthread)

# 设置包含的目录
include_directories (

    ${Boost_INCLUDE_DIR}

    ${VSOMEIP_INCLUDE_DIRS}

)
