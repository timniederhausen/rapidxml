#include "../../rapidxml.hpp"
#include "../../rapidxml_print.hpp"
#include "../../rapidxml_utils.hpp"
#include <iostream>

int main()
{
    using namespace rapidxml;
    using namespace std;

    xml_document<> doc;
    file<> f("test.xml");
    doc.parse<0>(f.data());
    static char buffer[4096];
    print(buffer, doc);
    cout << buffer;
    //print(cout, doc);
}
