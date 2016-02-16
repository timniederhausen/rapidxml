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
#define RAPIDXML_STATIC_POOL_SIZE 48
#include "../../rapidxml.hpp"
#include "../../rapidxml_print.hpp"
#include "../../rapidxml_utils.hpp"
//#include "../../rapidxml_print.hpp"
//#include "../../rapidxml_iterators.hpp"
//#include <cstdio>
//#include <cstring>
//#include <string>
//#include <fstream>
#include <iostream>
//#include <vector>
//#include <algorithm>

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
    memory_pool<> pool;
    pool.allocate_node(node_element);
    pool.allocate_node(node_element);
    pool.clear();
    */

    /*
    using namespace rapidxml;
    using namespace std;
    xml_document<char> doc;
    doc.append_node(doc.allocate_element("1"));
    doc.append_node(doc.allocate_element("2"));
    doc.append_node(doc.allocate_element("3"));
    doc.append_attribute(doc.allocate_attribute("a1"));
    doc.append_attribute(doc.allocate_attribute("a2"));
    doc.append_attribute(doc.allocate_attribute("a3"));
    node_iterator<char> it(&doc);
    for (node_iterator<char> it(&doc); it != node_iterator<char>(); ++it)
    {
        cout << it->name() << "\n";
        cout << (*it).name() << "\n";
    }
    for (attribute_iterator<char> it(&doc); it != attribute_iterator<char>(); ++it)
    {
        cout << it->name() << "\n";
        cout << (*it).name() << "\n";
    }
    //stable_sort(node_iterator<char>(&doc), node_iterator<char>());

    struct cmp
    {
        cmp(const char *name)
            : name(name)
        {
        }
        bool operator()(xml_node<char> &n)
        {
            return strcmp(n.name(), name) == 0;
        }
        const char *name;
    };
    node_iterator<char> it2 = find_if(node_iterator<char>(&doc), node_iterator<char>(), cmp("2"));
    */
    /*
    using namespace rapidxml;
    using namespace std;
    xml_document<char> doc;
    doc.append_node(doc.allocate_element("ABCDEFGHIJKLMNOPQRSTUVWXYZ"));
    doc.append_node(doc.allocate_element("abcdefghijklmnopqrstuvwxyz"));
    xml_node<char> *r = doc.first_node("abcdefghijklmnopqrstuvwxyz", 0, false);
    return (int)r;
    */

    xml_document<> doc;
    file<> f("test.xml");
    doc.parse<parse_trim_whitespace | parse_normalize_whitespace>(f.data());
    print(cout, doc);


}
