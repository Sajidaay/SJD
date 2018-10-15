#include "mainwindow.h"
#include <QApplication>
#include <qDebug>
#include <QFile>
#include <QString>
#include <QVector>

class stu{

    QString name;
    QString num;
    QVector <stu> list;


};


int main(int argc, char *argv[])

{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    { //写入-------------------------------------

        QString fileName=("Date.txt");
        QFile file(fileName);
        QTextStream date(&fileName);
        date.setCodec("UTF-8");

        if (!file.open(QFile::WriteOnly | QIODevice::Text))
        {
            qDebug()<<QString(" 打开失败").arg(fileName);
            return 1;
        }
    qDebug().noquote().nospace()<<"开始录入"<<fileName;

    QTextStream out(&file);
     out << "The magic number is: " << 49 << "\n";


    qDebug().noquote().nospace()<<"录入完成"<<fileName;
    file.close();
    }
    //-------------------------------------------------------
    QString fileName=("date.txt");
    QFile file(fileName);
    QTextStream in(&fileName);
    in.setCodec("UTF-8");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<QString("%1 打开失败").arg(fileName);
        return 1;
    }
    qDebug().noquote().nospace()<<"开始读取"<<fileName;

    while(!in.atEnd())
    {
        QString line=in.readLine();
        QStringList in=line.split("M");
        qDebug()<<line;
    }

    file.close();
    qDebug().noquote().nospace()<<"录入完成"<<fileName;


    return 0;
}








