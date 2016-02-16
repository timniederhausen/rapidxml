#include "../test_utils.hpp"
#include "../../rapidxml.hpp"
#include <iostream>

using namespace std;
using namespace rapidxml;

void test_parent()
{
    cout << "Test parent()...\n";
    
    xml_document<char> doc;
    xml_node<char> *node = doc.allocate_node(node_element);
    CHECK(node->parent() == 0);

    doc.append_child(node);
    CHECK(node->parent() == &doc);
}

void test_name()
{
    cout << "Test name()...\n";
    
    xml_document<char> doc;
    CHECK(*doc.name() == 0);
    CHECK(doc.name_size() == 0);
    
    doc.name(0, 0);
    CHECK(*doc.name() == 0);
    CHECK(doc.name_size() == 0);

    char *foobar = "foobar";
    doc.name(foobar, 6);
    CHECK(doc.name() == foobar);
    CHECK(doc.name_size() == 6);

    char *gozo = "gozo";
    doc.name(gozo);
    CHECK(doc.name() == gozo);
    CHECK(doc.name_size() == 4);
}

void test_value()
{
    cout << "Test value()...\n";
    
    xml_document<char> doc;
    CHECK(*doc.value() == 0);
    CHECK(doc.value_size() == 0);
    
    doc.value(0, 0);
    CHECK(*doc.value() == 0);
    CHECK(doc.value_size() == 0);

    char *foobar = "foobar";
    doc.value(foobar, 6);
    CHECK(doc.value() == foobar);
    CHECK(doc.value_size() == 6);

    char *gozo = "gozo";
    doc.value(gozo);
    CHECK(doc.value() == gozo);
    CHECK(doc.value_size() == 4);
}

void test_clear()
{
    cout << "Test clear()...\n";
    
    xml_document<char> doc;
    xml_node<char> *node1 = doc.allocate_node(node_element);
    xml_node<char> *node2 = doc.allocate_node(node_element);
    xml_attribute<char> *attr1 = doc.allocate_attribute();
    xml_attribute<char> *attr2 = doc.allocate_attribute();
    doc.append_child(node1);
    doc.append_child(node2);
    node1->append_attribute(attr1);
    node1->append_attribute(attr2);

    doc.clear();
    CHECK(doc.first_child() == 0);
}

void test_node_constructor()
{
    cout << "Test node_constructor()...\n";
    
    xml_document<char> doc;
    CHECK(doc.parent() == 0);
    CHECK(doc.first_child() == 0);
    CHECK(doc.first_attribute() == 0);
    CHECK(*doc.name() == 0);
    CHECK(*doc.value() == 0);
}

void test_prepend_child()
{
    cout << "Test prepend_child()...\n";
    
    xml_document<char> doc;
    
    xml_node<char> *node1 = doc.allocate_node(node_element);
    doc.prepend_child(node1);
    CHECK(doc.first_child() == node1);
    CHECK(doc.last_child() == node1);
    CHECK(node1->parent() == &doc);
    CHECK(node1->previous_sibling() == 0);
    CHECK(node1->next_sibling() == 0);

    xml_node<char> *node2 = doc.allocate_node(node_element);
    doc.prepend_child(node2);
    CHECK(doc.first_child() == node2);
    CHECK(doc.last_child() == node1);
    CHECK(node1->parent() == &doc);
    CHECK(node1->previous_sibling() == node2);
    CHECK(node1->next_sibling() == 0);
    CHECK(node2->parent() == &doc);
    CHECK(node2->previous_sibling() == 0);
    CHECK(node2->next_sibling() == node1);
}

void test_append_child()
{
    cout << "Test append_child()...\n";
    
    xml_document<char> doc;
    
    xml_node<char> *node1 = doc.allocate_node(node_element);
    doc.append_child(node1);
    CHECK(doc.first_child() == node1);
    CHECK(doc.last_child() == node1);
    CHECK(node1->parent() == &doc);
    CHECK(node1->previous_sibling() == 0);
    CHECK(node1->next_sibling() == 0);

    xml_node<char> *node2 = doc.allocate_node(node_element);
    doc.append_child(node2);
    CHECK(doc.first_child() == node1);
    CHECK(doc.last_child() == node2);
    CHECK(node1->parent() == &doc);
    CHECK(node1->previous_sibling() == 0);
    CHECK(node1->next_sibling() == node2);
    CHECK(node2->parent() == &doc);
    CHECK(node2->previous_sibling() == node1);
    CHECK(node2->next_sibling() == 0);
}

void test_insert_child()
{
    cout << "Test insert_child()...\n";
    
    xml_document<char> doc;
    
    // Insert to empty node
    xml_node<char> *node1 = doc.allocate_node(node_element);
    doc.insert_child(0, node1);
    CHECK(doc.first_child() == node1);
    CHECK(doc.last_child() == node1);
    CHECK(node1->parent() == &doc);
    CHECK(node1->previous_sibling() == 0);
    CHECK(node1->next_sibling() == 0);

    // Insert to front of non-empty node
    xml_node<char> *node2 = doc.allocate_node(node_element);
    doc.insert_child(node1, node2);
    CHECK(doc.first_child() == node2);
    CHECK(doc.last_child() == node1);
    CHECK(node1->parent() == &doc);
    CHECK(node1->previous_sibling() == node2);
    CHECK(node1->next_sibling() == 0);
    CHECK(node2->parent() == &doc);
    CHECK(node2->previous_sibling() == 0);
    CHECK(node2->next_sibling() == node1);

    // Insert to back of non-empty node
    xml_node<char> *node3 = doc.allocate_node(node_element);
    doc.insert_child(0, node3);
    CHECK(doc.first_child() == node2);
    CHECK(doc.first_child()->next_sibling() == node1);
    CHECK(doc.last_child() == node3);
    CHECK(node1->parent() == &doc);
    CHECK(node1->previous_sibling() == node2);
    CHECK(node1->next_sibling() == node3);
    CHECK(node2->parent() == &doc);
    CHECK(node2->previous_sibling() == 0);
    CHECK(node2->next_sibling() == node1);
    CHECK(node3->parent() == &doc);
    CHECK(node3->previous_sibling() == node1);
    CHECK(node3->next_sibling() == 0);

    // Insert to middle of non-empty node
    xml_node<char> *node4 = doc.allocate_node(node_element);
    doc.insert_child(node1, node4);
    CHECK(doc.first_child() == node2);
    CHECK(doc.first_child()->next_sibling() == node4);
    CHECK(doc.first_child()->next_sibling()->next_sibling() == node1);
    CHECK(doc.last_child() == node3);
    CHECK(node1->parent() == &doc);
    CHECK(node1->previous_sibling() == node4);
    CHECK(node1->next_sibling() == node3);
    CHECK(node2->parent() == &doc);
    CHECK(node2->previous_sibling() == 0);
    CHECK(node2->next_sibling() == node4);
    CHECK(node3->parent() == &doc);
    CHECK(node3->previous_sibling() == node1);
    CHECK(node3->next_sibling() == 0);
    CHECK(node4->parent() == &doc);
    CHECK(node4->previous_sibling() == node2);
    CHECK(node4->next_sibling() == node1);
}

void test_remove_first_child()
{
    cout << "Test remove_first_child()...\n";
    
    xml_document<char> doc;
    xml_node<char> *node1 = doc.allocate_node(node_element);
    xml_node<char> *node2 = doc.allocate_node(node_element);
    doc.append_child(node1);
    doc.append_child(node2);

    doc.remove_first_child();
    CHECK(doc.first_child() == node2);
    CHECK(node1->parent() == 0);
    CHECK(node2->parent() == &doc);
    CHECK(node2->previous_sibling() == 0);
    CHECK(node2->next_sibling() == 0);
    
    doc.remove_first_child();
    CHECK(doc.first_child() == 0);
    CHECK(node2->parent() == 0);
}

void test_remove_last_child()
{
    cout << "Test remove_last_child()...\n";
    
    xml_document<char> doc;
    xml_node<char> *node1 = doc.allocate_node(node_element);
    xml_node<char> *node2 = doc.allocate_node(node_element);
    doc.append_child(node1);
    doc.append_child(node2);

    doc.remove_last_child();
    CHECK(doc.last_child() == node1);
    CHECK(node1->parent() == &doc);
    CHECK(node1->previous_sibling() == 0);
    CHECK(node1->next_sibling() == 0);
    CHECK(node2->parent() == 0);

    doc.remove_last_child();
    CHECK(doc.first_child() == 0);
    CHECK(node1->parent() == 0);
}

void test_remove_child()
{
    cout << "Test remove_child()...\n";
    
    xml_document<char> doc;
    xml_node<char> *node1 = doc.allocate_node(node_element);
    xml_node<char> *node2 = doc.allocate_node(node_element);
    xml_node<char> *node3 = doc.allocate_node(node_element);
    xml_node<char> *node4 = doc.allocate_node(node_element);
    doc.append_child(node1);
    doc.append_child(node2);
    doc.append_child(node3);
    doc.append_child(node4);

    // Verify contents
    CHECK(doc.first_child() == node1);
    CHECK(doc.first_child()->next_sibling() == node2);
    CHECK(doc.first_child()->next_sibling()->next_sibling() == node3);
    CHECK(doc.last_child() == node4);

    // Remove from middle
    doc.remove_child(node2);
    CHECK(doc.first_child() == node1);
    CHECK(doc.first_child()->next_sibling() == node3);
    CHECK(doc.last_child() == node4);
    CHECK(node1->parent() == &doc);
    CHECK(node1->previous_sibling() == 0);
    CHECK(node1->next_sibling() == node3);
    CHECK(node2->parent() == 0);
    CHECK(node3->parent() == &doc);
    CHECK(node3->previous_sibling() == node1);
    CHECK(node3->next_sibling() == node4);
    CHECK(node4->parent() == &doc);
    CHECK(node4->previous_sibling() == node3);
    CHECK(node4->next_sibling() == 0);

    // Remove from front
    doc.remove_child(node1);
    CHECK(doc.first_child() == node3);
    CHECK(doc.last_child() == node4);
    CHECK(node1->parent() == 0);
    CHECK(node3->parent() == &doc);
    CHECK(node3->previous_sibling() == 0);
    CHECK(node3->next_sibling() == node4);
    CHECK(node4->parent() == &doc);
    CHECK(node4->previous_sibling() == node3);
    CHECK(node4->next_sibling() == 0);
    
    // Remove from back
    doc.remove_child(node4);
    CHECK(doc.first_child() == node3);
    CHECK(node3->parent() == &doc);
    CHECK(node3->previous_sibling() == 0);
    CHECK(node3->next_sibling() == 0);
    CHECK(node4->parent() == 0);

    // Remove last
    doc.remove_child(node3);
    CHECK(doc.first_child() == 0);
    CHECK(node3->parent() == 0);
}

void test_remove_all_children()
{
    cout << "Test remove_all_children()...\n";
    
    xml_document<char> doc;
    xml_node<char> *node1 = doc.allocate_node(node_element);
    xml_node<char> *node2 = doc.allocate_node(node_element);
    xml_node<char> *node3 = doc.allocate_node(node_element);
    doc.append_child(node1);
    doc.append_child(node2);
    doc.append_child(node3);

    doc.remove_all_children();
    CHECK(doc.first_child() == 0);
    CHECK(node1->parent() == 0);
    CHECK(node2->parent() == 0);
    CHECK(node3->parent() == 0);
}

void test_attribute_constructor()
{
    cout << "Test attribute_constructor()...\n";
    
    xml_document<char> doc;
    xml_attribute<char> *attr = doc.allocate_attribute();
    CHECK(attr->parent() == 0);
    CHECK(*attr->name() == 0);
    CHECK(*attr->value() == 0);
}

void test_prepend_attribute()
{
    cout << "Test prepend_attribute()...\n";
    
    xml_document<char> doc;
    
    xml_attribute<char> *attr1 = doc.allocate_attribute();
    doc.prepend_attribute(attr1);
    CHECK(doc.first_attribute() == attr1);
    CHECK(doc.last_attribute() == attr1);
    CHECK(attr1->parent() == &doc);
    CHECK(attr1->previous_attribute() == 0);
    CHECK(attr1->next_attribute() == 0);

    xml_attribute<char> *attr2 = doc.allocate_attribute();
    doc.prepend_attribute(attr2);
    CHECK(doc.first_attribute() == attr2);
    CHECK(doc.last_attribute() == attr1);
    CHECK(attr1->parent() == &doc);
    CHECK(attr1->previous_attribute() == attr2);
    CHECK(attr1->next_attribute() == 0);
    CHECK(attr2->parent() == &doc);
    CHECK(attr2->previous_attribute() == 0);
    CHECK(attr2->next_attribute() == attr1);
}

void test_append_attribute()
{
    cout << "Test append_attribute()...\n";
    
    xml_document<char> doc;
    
    xml_attribute<char> *attr1 = doc.allocate_attribute();
    doc.append_attribute(attr1);
    CHECK(doc.first_attribute() == attr1);
    CHECK(doc.last_attribute() == attr1);
    CHECK(attr1->parent() == &doc);
    CHECK(attr1->previous_attribute() == 0);
    CHECK(attr1->next_attribute() == 0);

    xml_attribute<char> *attr2 = doc.allocate_attribute();
    doc.append_attribute(attr2);
    CHECK(doc.first_attribute() == attr1);
    CHECK(doc.last_attribute() == attr2);
    CHECK(attr1->parent() == &doc);
    CHECK(attr1->previous_attribute() == 0);
    CHECK(attr1->next_attribute() == attr2);
    CHECK(attr2->parent() == &doc);
    CHECK(attr2->previous_attribute() == attr1);
    CHECK(attr2->next_attribute() == 0);
}

void test_insert_attribute()
{
    cout << "Test insert_attribute()...\n";
    
    xml_document<char> doc;
    
    // Insert to empty attr
    xml_attribute<char> *attr1 = doc.allocate_attribute();
    doc.insert_attribute(0, attr1);
    CHECK(doc.first_attribute() == attr1);
    CHECK(doc.last_attribute() == attr1);
    CHECK(attr1->parent() == &doc);
    CHECK(attr1->previous_attribute() == 0);
    CHECK(attr1->next_attribute() == 0);

    // Insert to front of non-empty attr
    xml_attribute<char> *attr2 = doc.allocate_attribute();
    doc.insert_attribute(attr1, attr2);
    CHECK(doc.first_attribute() == attr2);
    CHECK(doc.last_attribute() == attr1);
    CHECK(attr1->parent() == &doc);
    CHECK(attr1->previous_attribute() == attr2);
    CHECK(attr1->next_attribute() == 0);
    CHECK(attr2->parent() == &doc);
    CHECK(attr2->previous_attribute() == 0);
    CHECK(attr2->next_attribute() == attr1);

    // Insert to back of non-empty attr
    xml_attribute<char> *attr3 = doc.allocate_attribute();
    doc.insert_attribute(0, attr3);
    CHECK(doc.first_attribute() == attr2);
    CHECK(doc.first_attribute()->next_attribute() == attr1);
    CHECK(doc.last_attribute() == attr3);
    CHECK(attr1->parent() == &doc);
    CHECK(attr1->previous_attribute() == attr2);
    CHECK(attr1->next_attribute() == attr3);
    CHECK(attr2->parent() == &doc);
    CHECK(attr2->previous_attribute() == 0);
    CHECK(attr2->next_attribute() == attr1);
    CHECK(attr3->parent() == &doc);
    CHECK(attr3->previous_attribute() == attr1);
    CHECK(attr3->next_attribute() == 0);

    // Insert to middle of non-empty attr
    xml_attribute<char> *attr4 = doc.allocate_attribute();
    doc.insert_attribute(attr1, attr4);
    CHECK(doc.first_attribute() == attr2);
    CHECK(doc.first_attribute()->next_attribute() == attr4);
    CHECK(doc.first_attribute()->next_attribute()->next_attribute() == attr1);
    CHECK(doc.last_attribute() == attr3);
    CHECK(attr1->parent() == &doc);
    CHECK(attr1->previous_attribute() == attr4);
    CHECK(attr1->next_attribute() == attr3);
    CHECK(attr2->parent() == &doc);
    CHECK(attr2->previous_attribute() == 0);
    CHECK(attr2->next_attribute() == attr4);
    CHECK(attr3->parent() == &doc);
    CHECK(attr3->previous_attribute() == attr1);
    CHECK(attr3->next_attribute() == 0);
    CHECK(attr4->parent() == &doc);
    CHECK(attr4->previous_attribute() == attr2);
    CHECK(attr4->next_attribute() == attr1);
}

void test_remove_first_attribute()
{
    cout << "Test remove_first_attribute()...\n";
    
    xml_document<char> doc;
    xml_attribute<char> *attr1 = doc.allocate_attribute();
    xml_attribute<char> *attr2 = doc.allocate_attribute();
    doc.append_attribute(attr1);
    doc.append_attribute(attr2);

    doc.remove_first_attribute();
    CHECK(doc.first_attribute() == attr2);
    CHECK(attr1->parent() == 0);
    CHECK(attr2->parent() == &doc);
    CHECK(attr2->previous_attribute() == 0);
    CHECK(attr2->next_attribute() == 0);
    
    doc.remove_first_attribute();
    CHECK(doc.first_attribute() == 0);
    CHECK(attr2->parent() == 0);
}

void test_remove_last_attribute()
{
    cout << "Test remove_last_attribute()...\n";
    
    xml_document<char> doc;
    xml_attribute<char> *attr1 = doc.allocate_attribute();
    xml_attribute<char> *attr2 = doc.allocate_attribute();
    doc.append_attribute(attr1);
    doc.append_attribute(attr2);

    doc.remove_last_attribute();
    CHECK(doc.last_attribute() == attr1);
    CHECK(attr1->parent() == &doc);
    CHECK(attr1->previous_attribute() == 0);
    CHECK(attr1->next_attribute() == 0);
    CHECK(attr2->parent() == 0);

    doc.remove_last_attribute();
    CHECK(doc.first_attribute() == 0);
    CHECK(attr1->parent() == 0);
}

void test_remove_attribute()
{
    cout << "Test remove_attribute()...\n";
    
    xml_document<char> doc;
    xml_attribute<char> *attr1 = doc.allocate_attribute();
    xml_attribute<char> *attr2 = doc.allocate_attribute();
    xml_attribute<char> *attr3 = doc.allocate_attribute();
    xml_attribute<char> *attr4 = doc.allocate_attribute();
    doc.append_attribute(attr1);
    doc.append_attribute(attr2);
    doc.append_attribute(attr3);
    doc.append_attribute(attr4);

    // Verify contents
    CHECK(doc.first_attribute() == attr1);
    CHECK(doc.first_attribute()->next_attribute() == attr2);
    CHECK(doc.first_attribute()->next_attribute()->next_attribute() == attr3);
    CHECK(doc.last_attribute() == attr4);

    // Remove from middle
    doc.remove_attribute(attr2);
    CHECK(doc.first_attribute() == attr1);
    CHECK(doc.first_attribute()->next_attribute() == attr3);
    CHECK(doc.last_attribute() == attr4);
    CHECK(attr1->parent() == &doc);
    CHECK(attr1->previous_attribute() == 0);
    CHECK(attr1->next_attribute() == attr3);
    CHECK(attr2->parent() == 0);
    CHECK(attr3->parent() == &doc);
    CHECK(attr3->previous_attribute() == attr1);
    CHECK(attr3->next_attribute() == attr4);
    CHECK(attr4->parent() == &doc);
    CHECK(attr4->previous_attribute() == attr3);
    CHECK(attr4->next_attribute() == 0);

    // Remove from front
    doc.remove_attribute(attr1);
    CHECK(doc.first_attribute() == attr3);
    CHECK(doc.last_attribute() == attr4);
    CHECK(attr1->parent() == 0);
    CHECK(attr3->parent() == &doc);
    CHECK(attr3->previous_attribute() == 0);
    CHECK(attr3->next_attribute() == attr4);
    CHECK(attr4->parent() == &doc);
    CHECK(attr4->previous_attribute() == attr3);
    CHECK(attr4->next_attribute() == 0);
    
    // Remove from back
    doc.remove_attribute(attr4);
    CHECK(doc.first_attribute() == attr3);
    CHECK(attr3->parent() == &doc);
    CHECK(attr3->previous_attribute() == 0);
    CHECK(attr3->next_attribute() == 0);
    CHECK(attr4->parent() == 0);

    // Remove last
    doc.remove_attribute(attr3);
    CHECK(doc.first_attribute() == 0);
    CHECK(attr3->parent() == 0);
}

void test_remove_all_attributes()
{
    cout << "Test remove_all_attributes()...\n";
    
    xml_document<char> doc;
    xml_attribute<char> *attr1 = doc.allocate_attribute();
    xml_attribute<char> *attr2 = doc.allocate_attribute();
    xml_attribute<char> *attr3 = doc.allocate_attribute();
    doc.append_attribute(attr1);
    doc.append_attribute(attr2);
    doc.append_attribute(attr3);

    doc.remove_all_attributes();
    CHECK(doc.first_attribute() == 0);
    CHECK(attr1->parent() == 0);
    CHECK(attr2->parent() == 0);
    CHECK(attr3->parent() == 0);
}

void test_search_first_child()
{
    cout << "Test first_child(name)...\n";

    xml_document<char> doc;
    xml_node<char> *node1 = doc.allocate_node(node_element);
    xml_node<char> *node2 = doc.allocate_node(node_element);
    xml_node<char> *node3 = doc.allocate_node(node_element);
    node1->name("foo", 3);
    node2->name(0, 0);
    node3->name("bar", 3);
    doc.append_child(node1);
    doc.append_child(node2);
    doc.append_child(node3);

    xml_node<char> *node = doc.first_child("non-existing");
    CHECK(!node);
    node = doc.first_child("foo");
    CHECK(node == node1);
    node = doc.first_child("bar");
    CHECK(node == node3);
}

void test_search_last_child()
{
    cout << "Test last_child(name)...\n";

    xml_document<char> doc;
    xml_node<char> *node1 = doc.allocate_node(node_element);
    xml_node<char> *node2 = doc.allocate_node(node_element);
    xml_node<char> *node3 = doc.allocate_node(node_element);
    node1->name("foo", 3);
    node2->name(0, 0);
    node3->name("bar", 3);
    doc.append_child(node1);
    doc.append_child(node2);
    doc.append_child(node3);

    xml_node<char> *node = doc.last_child("non-existing");
    CHECK(!node);
    node = doc.last_child("foo");
    CHECK(node == node1);
    node = doc.last_child("bar");
    CHECK(node == node3);
}

void test_search_previous_sibling()
{
    cout << "Test previous_sibling(name)...\n";

    xml_document<char> doc;
    xml_node<char> *node1 = doc.allocate_node(node_element);
    xml_node<char> *node2 = doc.allocate_node(node_element);
    xml_node<char> *node3 = doc.allocate_node(node_element);
    node1->name("foo", 3);
    node2->name(0, 0);
    node3->name("bar", 3);
    doc.append_child(node1);
    doc.append_child(node2);
    doc.append_child(node3);

    xml_node<char> *last = doc.last_child();
    xml_node<char> *node = last->previous_sibling("non-existing");
    CHECK(!node);
    node = last->previous_sibling("foo");
    CHECK(node == node1);
    node = last->previous_sibling("bar");
    CHECK(!node);
}

void test_search_next_sibling()
{
    cout << "Test next_sibling(name)...\n";

    xml_document<char> doc;
    xml_node<char> *node1 = doc.allocate_node(node_element);
    xml_node<char> *node2 = doc.allocate_node(node_element);
    xml_node<char> *node3 = doc.allocate_node(node_element);
    node1->name("foo", 3);
    node2->name(0, 0);
    node3->name("bar", 3);
    doc.append_child(node1);
    doc.append_child(node2);
    doc.append_child(node3);

    xml_node<char> *first = doc.first_child();
    xml_node<char> *node = first->next_sibling("non-existing");
    CHECK(!node);
    node = first->next_sibling("foo");
    CHECK(!node);
    node = first->next_sibling("bar");
    CHECK(node == node3);
}

void test_search_first_attribute()
{
    cout << "Test first_attribute(name)...\n";

    xml_document<char> doc;
    xml_attribute<char> *a1 = doc.allocate_attribute();
    xml_attribute<char> *a2 = doc.allocate_attribute();
    xml_attribute<char> *a3 = doc.allocate_attribute();
    a1->name("foo", 3);
    a2->name(0, 0);
    a3->name("bar", 3);
    doc.append_attribute(a1);
    doc.append_attribute(a2);
    doc.append_attribute(a3);

    xml_attribute<char> *a = doc.first_attribute("non-existing");
    CHECK(!a);
    a = doc.first_attribute("foo");
    CHECK(a == a1);
    a = doc.first_attribute("bar");
    CHECK(a == a3);
}

void test_search_last_attribute()
{
    cout << "Test last_attribute(name)...\n";

    xml_document<char> doc;
    xml_attribute<char> *a1 = doc.allocate_attribute();
    xml_attribute<char> *a2 = doc.allocate_attribute();
    xml_attribute<char> *a3 = doc.allocate_attribute();
    a1->name("foo", 3);
    a2->name(0, 0);
    a3->name("bar", 3);
    doc.append_attribute(a1);
    doc.append_attribute(a2);
    doc.append_attribute(a3);

    xml_attribute<char> *a = doc.last_attribute("non-existing");
    CHECK(!a);
    a = doc.last_attribute("foo");
    CHECK(a == a1);
    a = doc.last_attribute("bar");
    CHECK(a == a3);
}

void test_search_previous_attribute()
{
    cout << "Test previous_attribute(name)...\n";

    xml_document<char> doc;
    xml_attribute<char> *a1 = doc.allocate_attribute();
    xml_attribute<char> *a2 = doc.allocate_attribute();
    xml_attribute<char> *a3 = doc.allocate_attribute();
    a1->name("foo", 3);
    a2->name(0, 0);
    a3->name("bar", 3);
    doc.append_attribute(a1);
    doc.append_attribute(a2);
    doc.append_attribute(a3);

    xml_attribute<char> *last = doc.last_attribute();
    xml_attribute<char> *a = last->previous_attribute("non-existing");
    CHECK(!a);
    a = last->previous_attribute("foo");
    CHECK(a == a1);
    a = last->previous_attribute("bar");
    CHECK(!a);
}

void test_search_next_attribute()
{
    cout << "Test next_attribute(name)...\n";

    xml_document<char> doc;
    xml_attribute<char> *a1 = doc.allocate_attribute();
    xml_attribute<char> *a2 = doc.allocate_attribute();
    xml_attribute<char> *a3 = doc.allocate_attribute();
    a1->name("foo", 3);
    a2->name(0, 0);
    a3->name("bar", 3);
    doc.append_attribute(a1);
    doc.append_attribute(a2);
    doc.append_attribute(a3);

    xml_attribute<char> *first = doc.first_attribute();
    xml_attribute<char> *a = first->next_attribute("non-existing");
    CHECK(!a);
    a = first->next_attribute("foo");
    CHECK(!a);
    a = first->next_attribute("bar");
    CHECK(a == a3);
}

int main()
{
    // Base
    test_name();
    test_value();
    test_parent();

    // Document
    test_clear();

    // Node
    test_node_constructor();
    test_append_child();
    test_prepend_child();
    test_insert_child();
    test_remove_first_child();
    test_remove_last_child();
    test_remove_child();
    test_remove_all_children();
    
    // Attribute
    test_attribute_constructor();
    test_prepend_attribute();
    test_append_attribute();
    test_insert_attribute();
    test_remove_first_attribute();
    test_remove_last_attribute();
    test_remove_attribute();
    test_remove_all_attributes();

    // Searching
    test_search_first_child();
    test_search_last_child();
    test_search_previous_sibling();
    test_search_next_sibling();
    test_search_first_attribute();
    test_search_last_attribute();
    test_search_previous_attribute();
    test_search_next_attribute();
    
    // Print final result
    return test::final_results();
}
