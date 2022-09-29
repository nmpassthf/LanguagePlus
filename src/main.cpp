#include <QCoreApplication>
#include <QDebug>
#include <QElapsedTimer>
#include <QString>
#include <algorithm>
#include <format>
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

    pl::lex::Lex lex{data};
    auto l = lex.start();

    cout << "输入数据为->\n" << data << endl;
    size_t tokenCount{0};
    cout << "输出token为->" << endl;
    for_each(l.cbegin(), l.cend(), [&](pl::types::Token token) {
        cout << "\t" << format("token{0} -> {1}", tokenCount++, token.data)
             << endl;
    });

    QElapsedTimer tm;
    size_t loopTimes{10'0000};

    tm.start();
    while (loopTimes--) {
        lex.start();
    }
    auto elapse = tm.elapsed();
    QString s = QString(
                    "测试10,0000次长度为%1字符的数据，总长度为%2字节。用时：%3 "
                    "毫秒，单次解析%4 毫秒")
                    .arg(int(data.size()))
                    .arg(10'0000 * data.size())
                    .arg(elapse)
                    .arg(elapse / 10'0000.0);
    qInfo() << s.toStdString().c_str();
    qInfo() << "解析速度为：" << 10'0000.0 * data.size() / elapse << "byte/s";
}

int main(int argc, char *argv[]) {
    test();
    return 0;
}