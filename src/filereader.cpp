/**
 * @file filereader.cpp
 * @author nmpassthf (nmpassthf@gmail.com)
 * @brief impl of pl::io
 * @date 2022-09-29
 *
 * @copyright Copyright (c) nmpassthf 2022
 *
 */
#include "filereader.hpp"

#include <algorithm>
#include <fstream>

using namespace std;
namespace pl::io {

FileReader::FileReader(const string& filePath) : _filePath{filePath} {};
FileReader::~FileReader() {}

void FileReader::_readFromFile(string& data) {
    ifstream fs{_filePath, ios::in};
    char buf;

    if (!fs.is_open()) {
        _good = false;
        return;
    } else if (fs.eof()) {
        _good = false;
        fs.close();
        return;
    }

    // read file here.
    while ((buf = fs.get()) != EOF) {
        data.push_back(buf);
    };
    _good = true;

    fs.close();
}

}  // namespace pl::io
