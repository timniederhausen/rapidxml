# Copyright (c) 2015 Tim Niederhausen (tim@rnc-ag.de)
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

rapidxml_add_test(test_comparative
	main.cpp

	../other_parsers/tinyxml/tinystr.cpp
	../other_parsers/tinyxml/tinyxml.cpp
	../other_parsers/tinyxml/tinyxmlerror.cpp
	../other_parsers/tinyxml/tinyxmlparser.cpp
)
