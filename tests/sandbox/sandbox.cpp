#if defined(_MSC_VER)

typedef __int64 tick_t;
inline tick_t ticks()
{
    __asm __emit 0fh __asm __emit 031h   // RDTSC
}

#elif defined(__GNUC__)

typedef long long tick_t;
inline tick_t ticks()
{
    tick_t result;
    __asm__ __volatile__ ("rdtsc" : "=A"(result));
    return result;
}

#endif

#define _SCL_SECURE_NO_DEPRECATE
//#define RAPIDXML_NO_EXCEPTIONS
#include "../../rapidxml.hpp"
#include "../../rapidxml_print.hpp"
//#include <cstdio>
//#include <cstring>
//#include <string>
//#include <fstream>
#include <iostream>
//#include <vector>

//#define CHAR wchar_t
//#define T(x) L##x
#define CHAR char
#define T(x) x

namespace rapidxml
{
    void parse_error_handler(const char *, void *)
    {
    }
}

int main()
{

    using namespace rapidxml;
    using namespace std;

    /*
    xml_document<char> doc;
    xml_node<char> *node1 = doc.allocate_node(node_element);
    xml_node<char> *node2 = doc.allocate_node(node_data);
    xml_attribute<char> *node3 = doc.allocate_attribute();
    char *q = node2->value();
    const char *q2 = nullstr<char>();
    node1->name("gogo", 4);
    node1->append_child(node2);
    node1->append_attribute(node3);
    node2->value("bobo<>'&\"", 9);
    node3->name("foobar", 6);
    node3->value("bobo<>&", 7);
    doc.append_child(node1);

    cout << doc;
    */

    /*
    ifstream stream("hamlet.xml", ios::binary);
    stream.unsetf(ios::skipws);
    vector<char> v;
    v.assign(istream_iterator<char>(stream), istream_iterator<char>());
    v.push_back(0);
    char *ch = &v.front();

    //char data[] = "<ala>&#169;</ala>";
    //char *ch = data;

    try
    {
        xml_document<CHAR, f_non_destructive> doc;
        doc.parse(ch);
        //doc.print(ostream_iterator<char>(cout));
    }
    catch (parse_error &e)
    {
        CHAR *pos = e.where<CHAR>() - 10;
        if (pos < ch)
            pos = ch;
        int len = std::min(int(strlen(pos)), 30);
        int pre = static_cast<int>(e.where<CHAR>() - pos);
        printf("%s\n%s^\n%s\n ", std::string(pos, pos + len).c_str(), std::string(pre, ' ').c_str(), e.what());
    }

    //using namespace boost::profiler;
    //BOOST_PROFILER_DUMP_ALL_EX(std::cout, c_short, c_exclusive, 1000);
    */

}
