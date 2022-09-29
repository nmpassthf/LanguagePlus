#include <algorithm>
#include <iostream>
#include <string>

#include "pluslanguage.hpp"

using namespace std;
void test() {
    pl::io::FileReader fr{"D:\\Code\\C++\\PlusLangParse\\test\\data\\src.pl"s};
    string data;
    fr >> data;

    cout << data.size() << endl;
    cout << data << endl;

    pl::container::KeyValContainer container;
    container.insert(pl::container::makePair("a", 50));
    container.insert(pl::container::makePair("c", "a"));

    bool isContains = container.contains("b");
    pl::container::ValueType value = container["a"];
    auto index = value.index();
}

int main(int argc, char const *argv[]) {
    test();
    return 0;
}