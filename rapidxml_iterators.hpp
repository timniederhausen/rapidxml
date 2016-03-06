#ifndef RAPIDXML_ITERATORS_HPP_INCLUDED
#define RAPIDXML_ITERATORS_HPP_INCLUDED

// Copyright (C) 2006, 2009 Marcin Kalicinski
// Version 1.13
// Revision $DateTime: 2009/05/15 23:02:39 $
//! \file rapidxml_iterators.hpp This file contains rapidxml iterators

#include "rapidxml.hpp"

namespace rapidxml
{
    const unsigned int iterate_check_name = 1 << 0;
    const unsigned int iterate_case_sensitive = 1 << 1;

    //! Iterator of child nodes of xml_node
    template <class Ch = char>
    class node_iterator
    {
    public:
        typedef xml_node<Ch> value_type;
        typedef xml_node<Ch> &reference;
        typedef xml_node<Ch> *pointer;
        typedef std::ptrdiff_t difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;

        node_iterator()
            : m_node(0)
            , m_flags(0)
        {
        }

        node_iterator(xml_node<Ch>* node, unsigned char flags)
            : m_node(node)
            , m_flags(flags)
        {
        }

        reference operator*() const
        {
            assert(m_node);
            return *m_node;
        }

        pointer operator->() const
        {
            assert(m_node);
            return m_node;
        }

        node_iterator& operator++()
        {
            assert(m_node);
            if (m_flags & iterate_check_name)
                m_node = m_node->next_sibling(m_node->name(),
                                              m_node->name_size(),
                                              !!(m_flags & iterate_case_sensitive));
            else
                m_node = m_node->next_sibling();
            return *this;
        }

        node_iterator operator++(int)
        {
            node_iterator tmp = *this;
            ++this;
            return tmp;
        }

        node_iterator& operator--()
        {
            assert(m_node);
            if (m_flags & iterate_check_name)
                m_node = m_node->previous_sibling(m_node->name(),
                                                  m_node->name_size(),
                                                  !!(m_flags & iterate_case_sensitive));
            else
                m_node = m_node->previous_sibling();
            assert(m_node);
            return *this;
        }

        node_iterator operator--(int)
        {
            node_iterator tmp = *this;
            ++this;
            return tmp;
        }

        bool operator==(const node_iterator<Ch> &rhs)
        {
            return m_node == rhs.m_node;
        }

        bool operator!=(const node_iterator<Ch> &rhs)
        {
            return m_node != rhs.m_node;
        }

    private:
        xml_node<Ch> *m_node;
        unsigned char m_flags;
    };

    //! Iterator of child attributes of xml_node
    template <class Ch = char>
    class attribute_iterator
    {
    public:
        typedef xml_attribute<Ch> value_type;
        typedef xml_attribute<Ch> &reference;
        typedef xml_attribute<Ch> *pointer;
        typedef std::ptrdiff_t difference_type;
        typedef std::bidirectional_iterator_tag iterator_category;

        attribute_iterator()
            : m_attribute(0)
            , m_flags(0)
        {
        }

        attribute_iterator(xml_attribute<Ch>* attr, unsigned char flags)
            : m_attribute(attr)
            , m_flags(flags)
        {
        }

        reference operator*() const
        {
            assert(m_attribute);
            return *m_attribute;
        }

        pointer operator->() const
        {
            assert(m_attribute);
            return m_attribute;
        }

        attribute_iterator& operator++()
        {
            assert(m_attribute);
            if (m_flags & iterate_check_name)
                m_attribute = m_attribute->next_attribute(m_attribute->name(),
                                                          m_attribute->name_size(),
                                                          !!(m_flags & iterate_case_sensitive));
            else
                m_attribute = m_attribute->next_attribute();
            return *this;
        }

        attribute_iterator operator++(int)
        {
            attribute_iterator tmp = *this;
            ++this;
            return tmp;
        }

        attribute_iterator& operator--()
        {
            assert(m_attribute);
            if (m_flags & iterate_check_name)
                m_attribute = m_attribute->previous_attribute(m_attribute->name(),
                                                              m_attribute->name_size(),
                                                              !!(m_flags & iterate_case_sensitive));
            else
                m_attribute = m_attribute->previous_attribute();
            assert(m_attribute);
            return *this;
        }

        attribute_iterator operator--(int)
        {
            attribute_iterator tmp = *this;
            ++this;
            return tmp;
        }

        bool operator==(const attribute_iterator<Ch> &rhs)
        {
            return m_attribute == rhs.m_attribute;
        }

        bool operator!=(const attribute_iterator<Ch> &rhs)
        {
            return m_attribute != rhs.m_attribute;
        }

    private:
        xml_attribute<Ch>* m_attribute;
        unsigned char m_flags;
    };

    // Range-based for loop support
    template <typename Iterator>
    class iterator_range
    {
    public:
        typedef Iterator const_iterator;
        typedef Iterator iterator;

        iterator_range(Iterator first, Iterator last)
            : m_first(first)
            , m_last(last)
        {
        }

        Iterator begin() const { return m_first; }
        Iterator end() const { return m_last; }

    private:
        Iterator m_first;
        Iterator m_last;
    };

    template <class Ch>
    iterator_range<node_iterator<Ch>> nodes(const xml_node<Ch>* node,
                                            const Ch* name = 0,
                                            std::size_t name_size = 0,
                                            bool case_sensitive = true)
    {
        unsigned char flags = 0;
        if (name)
            flags |= iterate_check_name;
        if (case_sensitive)
            flags |= iterate_case_sensitive;

        node_iterator<Ch> first(node->first_node(name, name_size, case_sensitive),
                                flags);
        node_iterator<Ch> last(0, flags);
        return iterator_range<node_iterator<Ch>>(first, last);
    }

    template <class Ch>
    iterator_range<attribute_iterator<Ch>> attributes(const xml_node<Ch>* node,
                                                      const Ch *name = 0,
                                                      std::size_t name_size = 0,
                                                      bool case_sensitive = true)
    {
        unsigned char flags = 0;
        if (name)
            flags |= iterate_check_name;
        if (case_sensitive)
            flags |= iterate_case_sensitive;

        attribute_iterator<Ch> first(node->first_attribute(name, name_size, case_sensitive),
                                     flags);
        attribute_iterator<Ch> last(0, flags);
        return iterator_range<attribute_iterator<Ch>>(first, last);
    }
}

#endif
