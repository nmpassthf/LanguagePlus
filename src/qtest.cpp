// #include "qtest.hpp"

// #include <QCoreApplication>
// #include <QDebug>
// #include <QElapsedTimer>
// #include <QString>
// #include <algorithm>
// #include <format>
// #include <iostream>
// #include <ranges>
// #include <sstream>
// #include <string>

// #include "pluslanguage.hpp"

// using namespace std;
// void test() {
//     pl::io::FileReader fr{"D:\\Code\\C++\\PlusLangParse\\test\\data\\src.pl"s};
//     string data;
//     fr >> data;

//     cout << data.size() << endl;
//     cout << data << endl;

//     pl::container::KeyValContainer container;
//     container.insert(pl::container::makePair("a", 50));
//     container.insert(pl::container::makePair("c", "a"));

//     bool isContains = container.contains("b");
//     pl::container::ValueType value = container["a"];
//     auto index = value.index();

//     pl::lex::Lex lex{data};
//     auto l = lex.start();

//     qInfo() << "输入数据为->" << ("\n" + data).c_str();
//     size_t tokenCount{0};
//     qInfo() << "输出token为->";
//     for_each(l.cbegin(), l.cend(), [&](pl::types::Token token) {
//         cout << "\t" << format("token{0} -> {1}", tokenCount++, token.data)
//              << " type is:" << static_cast<int>(token.type) << endl;
//     });

//     // 解析失败， 末尾元素返回ERROR类型
//     if (!lex.good()) {
//         qInfo() << lex.getErrorInfo().c_str();
//         return;
//     }

//     pl::parser::Parser parser(l);
//     auto asmCode = parser.parseAndGenCode();
//     for_each(asmCode.cbegin(), asmCode.cend(),
//              [&](const pl::types::Command& codeLine) {
//                  qInfo() << codeLine.toString().c_str();
//              });

//     if (!parser.good()) {
//         qInfo() << parser.getErrorInfo(data).c_str();
//         return;
//     }

//     pl::executer::Executer exec;
//     exec.exec(asmCode);
// }