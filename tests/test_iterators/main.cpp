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
void test_node_iterators(rapidxml::xml_document<char>& doc)
{
    CHECK(node_iterator<>() == node_iterator<>());

    iterator_range<node_iterator<>> n1 = nodes(&doc, "root");
    CHECK(1 == std::distance(n1.begin(), n1.end()));
    CHECK(--n1.end() == n1.begin());
    CHECK(++n1.begin() == n1.end());
    CHECK(++(--n1.end()) == n1.end());
    CHECK(node_iterator<>() == n1.end());

    node_iterator<> nit1 = n1.begin();
    CHECK(nit1++ == n1.begin());
    CHECK(nit1-- == n1.end());
    CHECK(nit1 == n1.begin());

    iterator_range<node_iterator<>> n2 = nodes(&doc, "invalid");
    CHECK(0 == std::distance(n2.begin(), n2.end()));

    iterator_range<node_iterator<>> n3 = nodes(*n1.begin(), "attributes");
    CHECK(1 == std::distance(n3.begin(), n3.end()));
    CHECK(--n3.end() == n3.begin());
    CHECK(++n3.begin() == n3.end());
}

template<int Flags>
void test_attr_iterators(rapidxml::xml_document<char>& doc)
{
    xml_node<>* root = doc.first_node("root");
    CHECK(root);

    CHECK(attribute_iterator<>() == attribute_iterator<>());

    iterator_range<attribute_iterator<>> a1 = attributes(root);
    CHECK(1 == std::distance(a1.begin(), a1.end()));
    CHECK(name<Flags>(*a1.begin()) == "entities");

    xml_node<>* attrs = root->first_node("attributes");
    CHECK(attrs);

    iterator_range<attribute_iterator<>> a2 = attributes(attrs);
    CHECK(2 == std::distance(a2.begin(), a2.end()));

    attribute_iterator<> ait1 = a2.begin();
    CHECK(ait1++ == a2.begin());
    CHECK(--ait1 == a2.begin());
    CHECK(name<Flags>(*ait1) == "att1");
    CHECK(name<Flags>(*++ait1) == "att2");
    CHECK(++ait1 == attribute_iterator<>());
    CHECK(ait1 == a2.end());
    CHECK(name<Flags>(*--ait1) == "att2");
    CHECK(name<Flags>(*--ait1) == "att1");

    std::size_t iterations = 0;
    for (xml_attribute<char>* n : a2)
      ++iterations;
    CHECK(iterations == 2);

    iterator_range<attribute_iterator<>> a3 = attributes(attrs, "att1");
    CHECK(1 == std::distance(a3.begin(), a3.end()));
    CHECK(--a3.end() == a3.begin());
    CHECK(++a3.begin() == a3.end());
    CHECK(++(--a3.end()) == a3.end());

    attribute_iterator<> ait2 = a3.begin();
    CHECK(name<Flags>(*ait2++) == "att1");
    CHECK(ait2-- == a3.end());
    CHECK(ait2 == a3.begin());

    iterator_range<attribute_iterator<>> a4 = attributes(attrs, "attNONEXISTENT");
    CHECK(0 == std::distance(a4.begin(), a4.end()));
}

template<int Flags>
void test_all()
{
    file<> f("../xml_files/simple_all.xml");

    rapidxml::xml_document<char> doc;
    doc.parse<Flags>(f.data());

    test_node_iterators<Flags>(doc);
    test_attr_iterators<Flags>(doc);
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
