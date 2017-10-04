// Revision $DateTime: 2007/02/25 13:06:01 $
//! \file test_utils.hpp This file contains rapidxml testing utilities

#ifndef TEST_UTILS_HPP_INCLUDED
#define TEST_UTILS_HPP_INCLUDED

#include "../rapidxml.hpp"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cstdlib>

//! Represents data loaded from a file
template<class Ch = char>
class file
{
public:
    //! Loads file into the memory. Data will be automatically destroyed by the destructor.
    //! \param filename Filename to load.
    file(const char *filename)
    {
        using namespace std;

        // Open stream
        basic_ifstream<Ch> stream(filename, ios::binary);
        if (!stream)
            throw runtime_error(string("cannot open file ") + filename);
        stream.unsetf(ios::skipws);

        // Determine stream size
        stream.seekg(0, ios::end);
        m_size = static_cast<std::size_t>(stream.tellg());
        stream.seekg(0);

        // Load data and add terminating 0
        m_data.resize(m_size + 1);
        stream.read(&m_data.front(), static_cast<streamsize>(m_size));
        m_data[m_size] = 0;
    }

    //! Loads file into the memory. Data will be automatically destroyed by the destructor
    //! \param stream Stream to load from
    file(std::basic_istream<Ch> &stream)
    {
        using namespace std;

        // Load data and add terminating 0
        stream.unsetf(ios::skipws);
        m_data.assign(istreambuf_iterator<Ch>(stream), istreambuf_iterator<Ch>());
        if (stream.fail() || stream.bad())
            throw runtime_error("error reading stream");
        m_data.push_back(0);
    }

    std::vector<Ch>& get()
    {
        return m_data;
    }

    //! Gets file data.
    //! \return Pointer to data of file.
    Ch *data()
    {
        return &m_data.front();
    }

    //! Gets file data.
    //! \return Pointer to data of file.
    const Ch *data() const
    {
        return &m_data.front();
    }

    //! Gets file data size.
    //! \return Size of file data, in characters.
    std::size_t size() const
    {
        return m_size;
    }

private:
    std::vector<Ch> m_data;   // File data
    std::size_t m_size;
};

class test
{
public:
    static int &succeeded()
    {
        static int n;
        return n;
    }

    static int &failed()
    {
        static int n;
        return n;
    }

    static int final_results()
    {
        if (failed() + succeeded() > 0)
        {
            std::cout << "\n"
                      << (failed() ? "*** Failure (" : "*** Success (")
                      << succeeded() << "/" << failed() + succeeded() << " checks succeeded)\n";
        }
        else
        {
            std::cout << "*** Success\n";
        }
        return (failed() == 0) ? 0 : 1;
    }
};

#define CHECK(c)                                        \
    if (!(c))                                           \
    {                                                   \
        std::cout << "Check " << #c << " failed.\n";    \
        ++test::failed();                               \
    }                                                   \
    else                                                \
        ++test::succeeded();

#define REQUIRE(c)                                                              \
    if (!(c))                                                                   \
    {                                                                           \
        std::cout << "Requirement " << #c << " failed, aborting test.\n";       \
        ++test::failed();                                                       \
        std::exit(test::final_results());                                       \
    }                                                                           \
    else                                                                        \
        ++test::succeeded();

template<int Flags>
std::string name(rapidxml::xml_base<char> *node)
{
    if (Flags & rapidxml::parse_no_string_terminators)
        return std::string(node->name(), node->name_size());
    else
        return std::string(node->name());
}

template<int Flags>
std::string value(rapidxml::xml_base<char> *node)
{
    if (Flags & rapidxml::parse_no_string_terminators)
        return std::string(node->value(), node->value_size());
    else
        return std::string(node->value());
}

#endif
