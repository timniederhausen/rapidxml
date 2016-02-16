#define RAPIDXML_STATIC_POOL_SIZE 64 * 1024
#define RAPIDXML_DYNAMIC_POOL_SIZE 1 * 1024

#include "../test_utils.hpp"
#include "../../rapidxml.hpp"
#include <string>
#include <vector>
#include <fstream>

using namespace std;
using namespace rapidxml;

#define MAGIC "Dead beef!"

void test_small_dynamic()
{
    // Load file
    string filename("../xml_files/simple_all.xml");
    ifstream stream(filename.c_str(), ios::binary);
    if (!stream)
        throw runtime_error(string("cannot open file ") + filename);
    stream.unsetf(ios::skipws);
    stream.seekg(0, ios::end);
    size_t size = stream.tellg();
    stream.seekg(0);   
    vector<char> original(size + 1);
    stream.read(&original.front(), static_cast<streamsize>(size));

    xml_document<> doc;
    char magic[] = MAGIC;       // Static pool memory corruption detection

    // Verify no memory corruption
    CHECK(strcmp(magic, MAGIC) == 0);

    // Parse multiple times
    for (int i = 0; i < 100; ++i)
        doc.parse<parse_non_destructive>(&original.front());
    
    // Verify no memory corruption
    CHECK(strcmp(magic, MAGIC) == 0);

    doc.clear();
    
    // Verify no memory corruption
    CHECK(strcmp(magic, MAGIC) == 0);

    // Parse multiple times
    for (int i = 0; i < 100; ++i)
        doc.parse<parse_non_destructive>(&original.front());

    // Verify no memory corruption
    CHECK(strcmp(magic, MAGIC) == 0);
}
