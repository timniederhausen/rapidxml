#include "../test_utils.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <iterator>
#include <cstring>
#include <stdexcept>

using namespace rapidxml;
using namespace std;

template<int Flags>
void test_xml_file(const string &filename)
{
    file<> f(filename.c_str());

    // Parse
    try
    {
        rapidxml::xml_document<char> doc;
        doc.parse<Flags>(f.data());
        cout << "Test " << filename << " succeeded.\n";
    }
    catch (...)
    {
        cout << "Test " << filename << " failed.\n";
        throw;
    }

}

int main()
{

    try
    {
        // Load file list
        ifstream stream("filelist.txt");
        if (!stream)
            throw runtime_error("filelist.txt not found");
        vector<string> files;
        string name;
        while (getline(stream, name))
            if (!name.empty() && name[0] != ';')
                files.push_back(name);

        // Test all files in the list
        int count = 0;
        for (vector<string>::iterator it = files.begin(); it != files.end(); ++it, ++count)
        {
            const int Flags = parse_normalize_whitespace;
            test_xml_file<Flags>(string("../") + it->c_str());
        }

        // Success
        cout << "*** Success: " << count << " files parsed without errors.\n";
        return 0;

    }
    catch (rapidxml::parse_error &e)
    {
        cout << "rapidxml::parse_error: " << e.what() << "\n";
        return 1;
    }
    catch (exception &e)
    {
        cout << "Error: " << e.what() << "\n";
        return 1;
    }

}
