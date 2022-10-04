/**
 * @file mqwindow.cpp
 * @author nmpassthf (nmpassthf@gmail.com)
 * @brief
 * @date 2022-10-03
 *
 * @copyright Copyright (c) nmpassthf 2022
 *
 */

#include "mqwindow.hpp"

#include <QString>
#include <string>

#include "config.h"
#include "pluslanguage.hpp"

using namespace std;
using namespace pl;

MainWindow::MainWindow(QWidget* parent)
    : QWidget(parent),
      titleLabel(new QLabel(QString("Language+ 语言解释器"), this)),
      textBrowser(new QTextBrowser(this)),
      showedLabel(new QTextEdit(this)),
      okBtn(new QPushButton("执行", this)) {
    setWindowTitle(QString("Language+  v") + VERSION);

    setWindowIcon(QIcon("://amamiya.ico"));

    setLayout(new QVBoxLayout(this));

    layout()->addWidget(titleLabel);
    layout()->addWidget(showedLabel);
    layout()->addWidget(textBrowser);
    layout()->addWidget(okBtn);

    ((QVBoxLayout*)(layout()))->setStretch(1, 1);
    ((QVBoxLayout*)(layout()))->setStretch(2, 3);

    titleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    textBrowser->setReadOnly(false);
    showedLabel->setMinimumHeight(50);
    showedLabel->setFrameShape(QFrame::StyledPanel);
    showedLabel->setReadOnly(true);

    connect(okBtn, &QPushButton::clicked, this, &MainWindow::runCode);
    connect(textBrowser, &QTextBrowser::textChanged, this,
            &MainWindow::runCode);
}
MainWindow::~MainWindow() {}

void MainWindow::runCode() {
    try {
        string src = textBrowser->toPlainText().toStdString();
        lex::Lex lex(src);
        auto lexResult = lex.start();
        if (!lex.good()) {
            showedLabel->setText(QString::fromStdString(lex.getErrorInfo()));
            return;
        }

        parser::Parser par(lexResult);
        auto parserResult = par.parseAndGenCode();
        if (!par.good()) {
            showedLabel->setText(QString::fromStdString(par.getErrorInfo(src)));
            return;
        }

        executer::Executer exec;
        auto finalResult = exec.exec(parserResult);
        showedLabel->setText(QString::fromStdString(finalResult));

    } catch (const std::exception& e) {
        showedLabel->setText("catch std::exception! what()->" +
                             QString::fromLocal8Bit(e.what()));

        qDebug() << e.what();
    } catch (...) {
        showedLabel->setText("catch unhandled Error!");
    }
}