CC=g++
CFLAGS=-I ../../boost -D TIXML_USE_STL -O3 -Wall -march=i686

all: run

run: build
	cd test_speed && test_speed.exe
	cd test_non_comparative && test_non_comparative.exe
	cd test_comparative && test_comparative.exe
	cd test_interface && test_interface.exe
	cd test_multimodule && test_multimodule.exe
	cd test_invalid && test_invalid.exe
	cd test_no_exceptions && test_no_exceptions.exe
	cd test_nodes && test_nodes.exe
	cd test_size && test_size.exe
	cd test_wchar && test_wchar.exe

build: \
test_speed/test_speed.exe \
test_non_comparative/test_non_comparative.exe \
test_comparative/test_comparative.exe \
test_interface/test_interface.exe \
test_multimodule/test_multimodule.exe \
test_invalid/test_invalid.exe \
test_no_exceptions/test_no_exceptions.exe \
test_nodes/test_nodes.exe \
test_size/test_size.exe \
test_wchar/test_wchar.exe

test_speed/test_speed.exe: test_speed/main.cpp other_parsers/pugixml/pugixml.cpp other_parsers/tinyxml/tinystr.cpp other_parsers/tinyxml/tinyxml.cpp other_parsers/tinyxml/tinyxmlerror.cpp other_parsers/tinyxml/tinyxmlparser.cpp
	$(CC) $(CFLAGS) -o $@ $^

test_non_comparative/test_non_comparative.exe: test_non_comparative/main.cpp
	$(CC) $(CFLAGS) -o $@ $^

test_comparative/test_comparative.exe: test_comparative/main.cpp other_parsers/tinyxml/tinystr.cpp other_parsers/tinyxml/tinyxml.cpp other_parsers/tinyxml/tinyxmlerror.cpp other_parsers/tinyxml/tinyxmlparser.cpp
	$(CC) $(CFLAGS) -o $@ $^

test_interface/test_interface.exe: test_interface/main.cpp
	$(CC) $(CFLAGS) -o $@ $^

test_multimodule/test_multimodule.exe: test_multimodule/main1.cpp test_multimodule/main2.cpp
	$(CC) $(CFLAGS) -o $@ $^

test_invalid/test_invalid.exe: test_invalid/main.cpp
	$(CC) $(CFLAGS) -o $@ $^

test_no_exceptions/test_no_exceptions.exe: test_no_exceptions/main.cpp
	$(CC) $(CFLAGS) -o $@ $^

test_nodes/test_nodes.exe: test_nodes/main.cpp
	$(CC) $(CFLAGS) -o $@ $^

test_size/test_size.exe: test_size/main.cpp
	$(CC) $(CFLAGS) -o $@ $^

test_wchar/test_wchar.exe: test_wchar/main.cpp
	$(CC) $(CFLAGS) -o $@ $^
