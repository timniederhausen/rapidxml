# Copyright (c) 2015 Tim Niederhausen (tim@rnc-ag.de)
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 3.0)

project(RapidXML)

set(CMAKE_CXX_STANDARD 11)

option(RAPIDXML_BUILD_TESTS "Build tests as well" ON)

add_library(rapidxml INTERFACE)

target_include_directories(rapidxml
	INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

if (RAPIDXML_BUILD_TESTS)
	add_subdirectory(tests)
endif ()
