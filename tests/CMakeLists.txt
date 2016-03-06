# Copyright (c) 2015 Tim Niederhausen (tim@rnc-ag.de)
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

macro(rapidxml_add_test tgt_name)
	add_executable(rapidxml.${tgt_name} ${ARGN})
	target_link_libraries(rapidxml.${tgt_name} rapidxml)

	# TODO(tim): Only set this for tests that use TinyXML
	target_compile_definitions(rapidxml.${tgt_name} PRIVATE TIXML_USE_STL=1)

	set_target_properties(rapidxml.${tgt_name} PROPERTIES
		OUTPUT_NAME ${tgt_name}
	)
endmacro()

add_subdirectory(sandbox)
add_subdirectory(test_alignment)
add_subdirectory(test_allocation_1)
add_subdirectory(test_allocation_2)
add_subdirectory(test_comparative)
add_subdirectory(test_interface)
add_subdirectory(test_invalid)
add_subdirectory(test_iterators)
add_subdirectory(test_multimodule)
add_subdirectory(test_no_exceptions)
add_subdirectory(test_nodes)
add_subdirectory(test_non_comparative)
add_subdirectory(test_size)
add_subdirectory(test_speed)
add_subdirectory(test_wchar)
