#include "myjson.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QStringList>

MyJson::MyJson(QWidget *parent) : QWidget(parent)
{
    //依据JSON文件加载对话框初始值
    //1.打开JSON 文件
    m_jsonfile = new QFile(QCoreApplication::applicationDirPath() + "/init.json");
    //qDebug()<<QDir::homePath();

    if(!m_jsonfile->open(QIODevice::ReadWrite)) {
        qDebug() << "File open error";
        //return -1;
    } else {
        qDebug() << "File open!";
    }

    QByteArray jsonfileData = m_jsonfile->readAll();
    m_jsonfile->close();

    //2. 文件内容读入到JSON Document
    QJsonParseError jsonfile_error;
    m_jsondoc = new QJsonDocument(QJsonDocument::fromJson(jsonfileData, &jsonfile_error));


    if(jsonfile_error.error != QJsonParseError::NoError)
    {
        qDebug("json error[%d]!",jsonfile_error.error);
        //return;
    }

    //3. JSON Document 转化成JSON 对象
    m_jsonobj = m_jsondoc->object();
    //JSON 对象读操作
    QString s_power = m_jsonobj.value("功率").toString();
    QString s_fre   = m_jsonobj.value("频率").toString();
    QString s_mode  = m_jsonobj.value("模式").toString();

    qDebug()<<s_power;
    qDebug()<<s_fre;
    qDebug()<<s_mode;

     m_powerlabel = new QLabel(this);
     m_powerlabel->setText("功率");
     m_powerlabel->move(20,24);

     m_poweredit = new QLineEdit(this);
     m_poweredit->setText(s_power);
     m_poweredit->move(50,20);

     m_frelabel = new QLabel(this);
     m_frelabel->setText("频率");
     m_frelabel->move(20,54);

     m_freedit = new QLineEdit(this);
     m_freedit->setText(s_fre);
     m_freedit->move(50,50);

     m_btn=new QPushButton(this);
     m_btn->setText("保存配置");
     m_btn->move(20,100);

     connect(m_btn,&QPushButton::clicked,this,&MyJson::savejson);
}

void MyJson::savejson()
{
    if(!m_jsonfile->open(QIODevice::ReadWrite)) {
        qDebug() << "File open error";
        //return -1;
    } else {
        qDebug() << "File open!";
    }

    //JSON 对象写操作
    //1.    读取界面的数值
    qDebug()<< m_poweredit->text();
    qDebug()<< m_freedit->text();
    //2.    将数据保存到JSON文件
    m_jsonobj.insert("功率",QString (m_poweredit->text()));
    m_jsonobj.insert("频率",QString (m_freedit->text()));

    //3.    obj 转 Doc
    QJsonDocument doc(m_jsonobj);

    //4.    Doc转Json格式文件存储
    qDebug()<<doc.toJson();
    m_jsonfile->write(doc.toJson());
    m_jsonfile->close();
}
