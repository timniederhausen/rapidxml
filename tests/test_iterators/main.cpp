#include "../test_utils.hpp"
#include "../../rapidxml.hpp"
#include "../../rapidxml_iterators.hpp"
#include <string>
#include <stdexcept>
#include <iterator>
#include <algorithm>
#include <iostream>

using namespace rapidxml;
using namespace std;

template<int Flags>
void test_all()
{
    file<> f("../xml_files/simple_all.xml");

    rapidxml::xml_document<char> doc;
    doc.parse<Flags>(f.data());

    CHECK(node_iterator<>() == node_iterator<>());

    iterator_range<node_iterator<>> n1 = nodes(&doc, "root");
    CHECK(1 == std::distance(n1.begin(), n1.end()));

    iterator_range<node_iterator<>> n2 = nodes(&doc, "invalid");
    CHECK(0 == std::distance(n2.begin(), n2.end()));

    xml_node<>* root = doc.first_node("root");
    CHECK(root);

    iterator_range<attribute_iterator<>> n3 = attributes(root);
    CHECK(1 == std::distance(n1.begin(), n1.end()));
    CHECK(name<Flags>(*n3.begin()) == "entities");
}

int main()
{
    try {
        test_all<parse_fastest>();
        test_all<parse_non_destructive>();
        test_all<0>();
        test_all<parse_trim_whitespace>();
        test_all<parse_normalize_whitespace>();
        test_all<parse_trim_whitespace | parse_normalize_whitespace>();
        test_all<parse_full>();
    } catch (std::exception& e) {
        std::cout << e.what() << "\n";
    }

    return test::final_results();
}
