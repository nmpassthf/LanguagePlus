#include <QCoreApplication>
#include <QDebug>
#include <QElapsedTimer>
#include <QString>
#include <algorithm>
#include <format>
#include <iostream>
#include <ranges>
#include <regex>
#include <sstream>
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

    pl::lex::Lex lex{data};
    auto l = lex.start();

    qInfo() << "输入数据为->\n" << data.c_str();
    size_t tokenCount{0};
    qInfo() << "输出token为->";
    for_each(l.cbegin(), l.cend(), [&](pl::types::Token token) {
        cout << "\t" << format("token{0} -> {1}", tokenCount++, token.data)
             << endl;
    });

    // 解析失败， 末尾元素返回ERROR类型
    if (!lex.good()) {
        // qInfo() << QString("词法解析失败，错误于：%1行%2列")
        //                .arg(l.back().row + 1)
        //                .arg(l.back().column + 1)
        //                .toStdString()
        //                .c_str();

        // stringstream ss(data, ios::in);
        // string lineString;
        // for (size_t line = 0; line < l.back().row + 1; ++line)
        //     getline(ss, lineString);
        // qInfo() << lineString.c_str();

        // qInfo() << (QString(' ').repeated(l.back().column) + "^~~~~非法字符")
        //                .toStdString()
        //                .c_str();

        qInfo() << lex.getErrorInfo().c_str();
    }

    // QElapsedTimer tm;
    // size_t loopTimes{10'0000};

    // tm.start();
    // while (loopTimes--) {
    //     lex.start();
    // }
    // auto elapse = tm.elapsed();
    // QString s = QString(
    //                 "测试10,0000次长度为%1字符的数据，总长度为%2字节。用时：%3
    //                 " "毫秒，单次解析%4 毫秒") .arg(int(data.size()))
    //                 .arg(10'0000 * data.size())
    //                 .arg(elapse)
    //                 .arg(elapse / 10'0000.0);
    // qInfo() << s.toStdString().c_str();
    // qInfo() << "解析速度为：" << 10'0000.0 * data.size() / elapse <<
    // "byte/s";
}

int main(int argc, char* argv[]) {
    test();
    return 0;
}