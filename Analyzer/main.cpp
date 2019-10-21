#include "mainwindow.h"
#include <QApplication>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextBrowser>
#include <QVector>


bool in(QString s, QVector<QString> l)
{
    for(auto &a: l)
    {
        if (a == s)
            return true;
    }

    return false;
}

QString vec_to_str(QVector <QString> s)
{
    QString temp;

    for (auto &a: s)
    {
        temp += a + '\n';
    }

    return temp;
}

void processing(QString &con, QString &inp, QVector<QString> &const_arr, QVector<QString> &comm_arr, QVector<QString> &var_arr)
{
    QVector <QString> consts_arr;
    QString temp = "";

    int i = 0;


    while (i < con.size())
    {
        if (con[i] == ' ')
        {
             i++;

             if (temp.length() != 0)
             {
                consts_arr.append(temp);
                temp = "";
            }
        }
        else if(con[i] == "'")
        {
            i++;

            if (temp.length() != 0)
            {
                consts_arr.append(temp);
                temp = "";
            }

            while (con[i] != "'")
            {
                temp += con[i];
                i++;
            }
            i++;

            temp = "'"+temp+"'";

            consts_arr.append(temp);
            temp = "";
        }
        else
        {
            temp += con[i];
            i++;
        }
    }
    if (temp.length() >0)
    {
        consts_arr.append(temp);
        temp = "";
    }

    i = 0;

    while (i < inp.length())
    {
        if (inp[i] == ' ')
        {
             i++;

             if (temp.length() != 0)
             {
                if (in(temp, consts_arr))
                {
                    const_arr.append(temp);
                }
                else
                {
                    var_arr.append(temp);
                }

                temp = "";
            }
        }
        else if (inp[i] == "/" && inp[i+1] == "*")
        {
            i += 2;

            if (temp.length() != 0)
            {
                if (in(temp, consts_arr))
                {
                    const_arr.append(temp);
                }
                else
                {
                    var_arr.append(temp);
                }

                temp = "";
            }

            while (inp[i] != '*' && inp[i] != '/')
            {
                temp += inp[i];
                i++;
            }

            i+=2;

            comm_arr.append(temp);
            temp = "";

        }
        else if(inp[i] == "'")
        {
            i++;

            if (temp.length() != 0)
            {
                if (in(temp, consts_arr))
                {
                    const_arr.append(temp);
                }
                else
                {
                    var_arr.append(temp);
                }

                temp = "";
            }

            while (inp[i] != "'")
            {
                temp += inp[i];
                i++;
            }
            i++;
            temp = "'"+temp+"'";

            if (in(temp, consts_arr))
            {
                const_arr.append(temp);
            }
            else
            {
                var_arr.append(temp);
            }

            temp = "";
        }
        else if(inp[i] == '/' && inp[i+1] == '/')
        {
            i += 2;

            if (temp.length() != 0)
            {
                if (in(temp, consts_arr))
                {
                    const_arr.append(temp);
                }
                else
                {
                    var_arr.append(temp);
                }

                temp = "";
            }

            while (i < inp.length())
            {
                temp += inp[i];
                i++;
            }

            i++;

            comm_arr.append(temp);
            temp = "";
        }
        else
        {
            temp += inp[i];
            i++;
        }
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    QString inp = "";
    QString con = "";

    QLineEdit *constants = new QLineEdit(&w);
    QLineEdit *inputLine = new QLineEdit(&w);
    QVector <QString> comments;
    QVector <QString> var;
    QVector <QString> constant;

    QPushButton *processButton = new QPushButton("Обработать", &w);
    QTextBrowser *commentOut = new QTextBrowser(&w);
    QTextBrowser *constOut = new QTextBrowser(&w);
    QTextBrowser *varOut = new QTextBrowser(&w);
    QPushButton *cleanButton = new QPushButton("Очистить", &w);
    QLabel *cl = new QLabel("Комментарии:", &w);
    QLabel *cnl = new QLabel("Константы:", &w);
    QLabel *vl = new QLabel("Переменные:", &w);


    constants->setGeometry(10, 30, 371, 21);
    inputLine->setGeometry(10, 80, 371, 21);
    processButton->setGeometry(150, 110, 80, 21);
    commentOut->setGeometry(10, 180, 111, 70);
    constOut->setGeometry(140, 180, 111, 70);
    varOut->setGeometry(270, 180, 111, 70);
    cleanButton->setGeometry(150, 260, 80, 21);
    cl->setGeometry(10, 160, 71, 16);
    cnl->setGeometry(140, 160, 71, 16);
    vl->setGeometry(270, 160, 71, 16);

    constants->show();
    inputLine->show();
    processButton->show();


    QObject::connect(processButton, &QPushButton::clicked, [&]{
        inp = inputLine->text();
        con = constants->text();

        processing(con, inp, constant, comments, var);

        varOut->setText(vec_to_str(var));
        constOut->setText(vec_to_str(constant));
        commentOut->setText(vec_to_str(comments));

        commentOut->show();
        constOut->show();
        varOut->show();
        cleanButton->show();
        cl->show();
        cnl->show();
        vl->show();
    });

    QObject::connect(cleanButton, &QPushButton::clicked, [&]{
        commentOut->hide();
        constOut->hide();
        varOut->hide();
        cleanButton->hide();
        cl->hide();
        cnl->hide();
        vl->hide();
        constants->clear();
        inputLine->clear();
        comments.clear();
        var.clear();
        constant.clear();
    });

    return a.exec();
}
