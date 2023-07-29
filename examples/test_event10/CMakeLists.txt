# Copyright (C) 2015-2017 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

cmake_minimum_required (VERSION 2.8.7)
project (vSomeIPHelloWorld)

find_package(Threads REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(${VSOMEIP_INCLUDE_DIRS})

add_library(test_event_service10 INTERFACE)
#target_sources(test_event_service10 INTERFACE
#    "${CMAKE_CURRENT_SOURCE_DIR}/test_event_service.hpp"
#)
target_include_directories(test_event_service10 INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

add_library(test_event_client10 INTERFACE)
target_include_directories(test_event_client10 INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}"
)

if (NOT ${CMAKE_SYSTEM_NAME} MATCHES "Android")
    # This will get us acces to
    #   VSOMEIP_INCLUDE_DIRS - include directories for vSomeIP
    #   VSOMEIP_LIBRARIES    - libraries to link against
    find_package(${VSOMEIP_NAME})
    if (NOT ${VSOMEIP_NAME}_FOUND)
        message("${VSOMEIP_NAME} was not found. Please specify vsomeip_DIR")
    endif()

    add_executable (test_event_service10_1 test_event_service.cpp)
    target_link_libraries(test_event_service10_1 test_event_service10 ${VSOMEIP_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
    add_executable (test_event_client10_1 test_event_client.cpp)
    target_link_libraries(test_event_client10_1 test_event_client10 ${VSOMEIP_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

endif()
