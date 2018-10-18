#include <QCoreApplication>
#include <QDebug>
#include <QTextStream>
#include <QFile>
//信息存储------------------------------------------------
using namespace std;

#define N 4     //选择想排序的列

namespace SK {
enum SortKind{
    col01    =   0x00000001<<0,         //!< 第1列
    col02    =   0x00000001<<1,         //!< 第2列
    col03    =   0x00000001<<2,         //!< 第3列
    col04    =   0x00000001<<3,         //!< 第4列
    col05    =   0x00000001<<4,         //!< 第5列
    col06    =   0x00000001<<5,         //!< 第6列
    col07    =   0x00000001<<6,         //!< 第7列
    col08    =   0x00000001<<7,         //!< 第8列
    col09    =   0x00000001<<8,         //!< 第9列
    col10    =   0x00000001<<9,         //!< 第10列
    col11    =   0x00000001<<10,        //!< 第11列
    col12    =   0x00000001<<11,        //!< 第12列
    col13    =   0x00000001<<12,        //!< 第13列
    col14    =   0x00000001<<13,        //!< 第14列
    col15    =   0x00000001<<14,        //!< 第15列
    col16    =   0x00000001<<15,        //!< 第16列
    col17    =   0x00000001<<16,        //!< 第17列
    col18    =   0x00000001<<17,        //!< 第18列
    col19    =   0x00000001<<18,        //!< 第19列
    col20    =   0x00000001<<19,        //!< 第20列
    col21    =   0x00000001<<20,        //!< 第21列
    col22    =   0x00000001<<21,        //!< 第22列
    col23    =   0x00000001<<22,        //!< 第23列
    col24    =   0x00000001<<23,        //!< 第24列
    col25    =   0x00000001<<24,        //!< 第25列
    col26    =   0x00000001<<25,        //!< 第26列
    col27    =   0x00000001<<26,        //!< 第27列
    col28    =   0x00000001<<27,        //!< 第28列
    col29    =   0x00000001<<28,        //!< 第29列
    col30    =   0x00000001<<29,        //!< 第30列
    col31    =   0x00000001<<30,        //!< 第31列
    col32    =   0x00000001<<31,        //!< 第32列
};
}
typedef struct{//定义数据结构
     QStringList stu;
} stuData;

/*输出学生数据--------------------------------------------------
QDebug operator << (QDebug d, const stuData &data) {
    for(int i=0;i<data.stu.size();i++)
        d.noquote().nospace()<<QString(data.stu.at(i))<<"\t" ;

    return d;
}*/
QDebug operator<< (QDebug d, const stuData &data) {
    for(int i=0;i<data.stu.size();i++)
    {
        d.noquote()<<data.stu.at(i);
    }
    qDebug()<<"";
    return d;
}

//比较---------------------------------------------------------
class Cmp {
public:
    Cmp(int selectedColumn)
    { this->currentColumn = selectedColumn; }
    bool operator() (const stuData& d1,const stuData& d2);
private:
    int currentColumn;
};
bool Cmp::operator()(const stuData &d1, const stuData &d2)
{
    bool result = false;
    quint32 sortedColumn = 0x00000001<<currentColumn;
    switch (sortedColumn) {
    default: result=(d1.stu.at(currentColumn+1)>=d2.stu.at(currentColumn+1));
        break;
    }
    return result;
}

//排序，执行------------------------------------------------------
class ScoreSorter
{
public:
    ScoreSorter(QString dfile);
    void readFile();
    void doSort();
private:
    QString Filepath;
    QList<stuData > data;
    stuData listtitle;
    void out2file(quint8 lie);
};
//应用scoresorter-----------------------------------------------------
ScoreSorter::ScoreSorter(QString data)
{
    this->Filepath=data;
}
void ScoreSorter::readFile()
{
    QFile dfile(this->Filepath);   //只读方式打开文件
    if(!dfile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"读取失败"<<endl;
    }
    //读取表头并按空格 ---------------------
    QString titile(dfile.readLine());
    this->listtitle.stu = titile.split(" ", QString::SkipEmptyParts);//spilit，分割

    // 按行读取---------------------------
    stuData perdata;
    while(!dfile.atEnd())
    {
        QByteArray line = dfile.readLine();
        QString str(line);
        perdata.stu = str.split(" ", QString::SkipEmptyParts);
        //去末尾'\n'  如果是空则摒弃,否则添加到 data
        if(perdata.stu.size()==0) continue;
        this->data.append(perdata);
    }
}

void ScoreSorter::doSort()
{
    for(int i=1;i<this->listtitle.stu.size();i++)
    {
       //  声明比较规则类
        Cmp thiscmp(i-1);
        //初始化对象
        std::sort(this->data.begin() , this->data.end() , thiscmp );
        //排序
        qDebug()<<"排序后输出，当前排序第 "<<i+1 <<" 列：";
        qDebug() << '\t'<< (this->listtitle);
        //qDebug重载输出
        for(int i=0;i<this->data.size();i++)  qDebug() << this->data.at(i);
        qDebug()<<"-----------------------------------------------------------------------\n";
        this->out2file(i+1);
        //data 输出到文件
    }
}
//输出到文件
void ScoreSorter::out2file(quint8 lie)
{
    // 读写、追加
    QFile file("sorted_"+this->Filepath);
    file.open(QIODevice::ReadWrite | QIODevice::Append);
    QTextStream stream(&file);

    stream.setCodec("UTF-8");  //编码方式
    stream<<QString("当前排序第 ")<<lie <<QString(" 列：")<<"\r\n";
    stream<<"\t";  //输出表头
    for(int j=0;j<this->listtitle.stu.size();j++)
        stream<<this->listtitle.stu.at(j)<<"\t";
    stream<<"\r\n";
    for(int i=0;i<this->data.size();i++)
    {   //输出内容
        for(int j=0;j<this->listtitle.stu.size();j++)
            stream<<this->data.at(i).stu.at(j)<<"\t";
        stream<<"\r\n";
    }
    stream<<"----------------------------------------------------------------------------------------"<<"\r\n\r\n";
    file.close();
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString datafile = "D:/data.txt";
    // 删除已存在的
    QFile f("sorted_"+datafile);
    if (f.exists())  f.remove();
    ScoreSorter s(datafile);   //read datafile
    s.readFile();     //读取data
    s.doSort();       //排序和导出
    return a.exec();
}
