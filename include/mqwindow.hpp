#pragma once

#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QTextBrowser>
#include <QWidget>

class MainWindow : public QWidget {
    Q_OBJECT
   public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

   private slots:
    void runCode();

   private:
    QLabel* titleLabel;
    QTextBrowser* textBrowser;
    QTextEdit* showedLabel;
    QPushButton* okBtn;
};