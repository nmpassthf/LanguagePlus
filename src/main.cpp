/**
 * @file main.cpp
 * @author nmpassthf (nmpassthf@gmail.com)
 * @brief
 * @date 2022-10-02
 *
 * @copyright Copyright (c) nmpassthf 2022
 *
 */

#include <QApplication>

#include "mqwindow.hpp"
#include "pluslanguage.hpp"
#include "qtest.hpp"

using namespace std;
using namespace pl;

int main(int argc, char* argv[]) {
    // test();
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    // string src = "a = 1\necho a+1";
    // lex::Lex lex(src);
    // auto lexResult = lex.start();
    // if (!lex.good()) {
    //     qDebug() << QString::fromStdString(lex.getErrorInfo());
    // }

    // parser::Parser par(lexResult);
    // auto parserResult = par.parseAndGenCode();
    // if (!par.good()) {
    //     qDebug() << QString::fromStdString(par.getErrorInfo(src));
    // }
    // qDebug() << par.getFormattedSource().c_str();

    // executer::Executer exec;
    // auto finalResult = exec.exec(parserResult);
    // qDebug() << QString::fromStdString(finalResult);
    return app.exec();
}