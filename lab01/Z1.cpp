#include <Qvector>
#include <QCoreApplication>
#include <QDebug>
#include <QString>
class stu
{
public:
    int num;
    int subject1;
    int subject2;
    QString name;

};
bool cmp1(const stu&stu1,const stu&stu2)
{
    return stu1.subject1 > stu2.subject1 ;                //课程1递增顺序
}
bool cmp2(const stu&stu1,const stu&stu2)
{
    return stu1.subject2 > stu2.subject2 ;                //课程2递增顺序
}
bool cmp3(const stu&stu1,const stu&stu2)
{
    return stu1.num < stu2.num ;                //学号递增顺序
}
bool cmp4(const stu&stu1,const stu&stu2)
{
    return stu1.name <  stu2.name ;                //姓名递增顺序
}

int main()
{
    stu stu1,stu2,stu3,stu4;
    stu1.num=1403130209;
    stu2.num=1403140101;
    stu3.num=1403140102;
    stu4.num=1403140103;
    stu1.name="l鲁智深";
    stu2.name="l林冲";
    stu3.name="s宋江";
    stu4.name="w武松";
    stu1.subject1=80;
    stu2.subject1=82;
    stu3.subject1=76;
    stu4.subject1=88;
    stu1.subject2=72;
    stu2.subject2=76;
    stu3.subject2=85;
    stu4.subject2=80;
    QVector <stu> stu;                              //定义一个结构体变量的vector容器
    stu<<stu1<<stu2<<stu3<<stu4;
    qDebug()<<"***************************原始记录****************************";
    qDebug()<<"学号"<<"\t\t"<<"姓名"<<"\t"<<"课程1"<<"\t"<<"课程2";
    for(int i=0;i<4;i++)
    {
        qDebug()<<stu.at(i).num<<"\t"<<stu.at(i).name<<"\t"<<stu.at(i).subject1<<"\t"<<stu.at(i).subject2;
    }
        qDebug()<<"*********************按照学号排序输出*************************";
    std::sort(stu.begin(), stu.end() ,cmp3);
    for(int i=0;i<4;i++)
    {
        qDebug()<<stu.at(i).num<<"\t"<<stu.at(i).name<<"\t"<<stu.at(i).subject1<<"\t"<<stu.at(i).subject2;
    }
    qDebug()<<"*********************按照姓名排序输出*************************";
std::sort(stu.begin(), stu.end() ,cmp4);
for(int i=0;i<4;i++)
{
    qDebug()<<stu.at(i).num<<"\t"<<stu.at(i).name<<"\t"<<stu.at(i).subject1<<"\t"<<stu.at(i).subject2;
}
    qDebug()<<"*********************按照课程1排序输出*************************";
std::sort(stu.begin(), stu.end() ,cmp1);
for(int i=0;i<4;i++)
{
qDebug()<<stu.at(i).num<<"\t"<<stu.at(i).name<<"\t"<<stu.at(i).subject1<<"\t"<<stu.at(i).subject2;
}
qDebug()<<"*********************按照课程2排序输出*************************";
std::sort(stu.begin(), stu.end() ,cmp2);
for(int i=0;i<4;i++)
{
qDebug()<<stu.at(i).num<<"\t"<<stu.at(i).name<<"\t"<<stu.at(i).subject1<<"\t"<<stu.at(i).subject2;
}
    return 0;


    }
