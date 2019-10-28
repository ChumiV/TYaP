#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextBrowser>
#include <QVector>

int proc(QString s)
{
    int i = 0;

    if (i == s.length()) return 1;

    if (s[i] == "-")
    {
        goto s0;
    }
    else if(s[i] == "a")
    {
        i++;
        goto s1;
    }
    else if(s[i] == "b")
    {
        i++;
        goto s2;
    }
    else if(s[i] == "c")
    {
        i++;
        goto s3;
    }

    s0:
        return false;
    s1:
        if (i == s.length()) return true;
        i++;
        if (s[i-1] == "-")
            goto s4;
        else if(s[i-1] == "a")
            goto s0;
        else if(s[i-1] == "b")
            goto s2;
        else if(s[i-1] == "c")
            goto s3;
        goto s0;
    s2:
        if (i == s.length()) return true;
        i++;
        if (s[i-1] == "-")
            goto s5;
        else if(s[i-1] == "a")
            goto s1;
        else if(s[i-1] == "b")
            goto s0;
        else if(s[i-1] == "c")
            goto s3;
        goto s0;
    s3:
        if (i == s.length()) return true;
        i++;
        if (s[i-1] == "-")
            goto s6;
        else if(s[i-1] == "a")
            goto s1;
        else if(s[i-1] == "b")
            goto s2;
        else if(s[i-1] == "c")
            goto s0;
        goto s0;
    s4:
        if (i == s.length()) return true;
        i++;
        if(s[i-1] == "a")
            goto s1;
        goto s0;
    s5:
        if (i == s.length()) return true;
        i++;
        if(s[i-1] == "b")
            goto s2;
        goto s0;
    s6:
        if (i == s.length()) return true;
        i++;
        if(s[i-1] == "c")
            goto s3;
        goto s0;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QString inp = "";

    QLineEdit *inputLine = new QLineEdit(&w);

    QPushButton *processButton = new QPushButton("Обработать", &w);
    QPushButton *cleanButton = new QPushButton("Очистить", &w);

    inputLine->setGeometry(10, 30, 371, 21);
    processButton->setGeometry(160, 60, 80, 21);
    cleanButton->setGeometry(160, 90, 80, 21);
    inputLine->show();
    processButton->show();

    QObject::connect(processButton, &QPushButton::clicked, [&]{
        cleanButton->show();

        if (proc(inputLine->text()))
            cleanButton->setStyleSheet("background: green");
        else
            cleanButton->setStyleSheet("background: red");
    });

    QObject::connect(cleanButton, &QPushButton::clicked, [&]{
        cleanButton->hide();
        inputLine->clear();
    });

    return a.exec();
}
