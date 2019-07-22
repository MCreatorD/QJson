#include "myjson.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QStringList>
MyJson::MyJson(QWidget *parent) : QWidget(parent)
{
    //定义 JSON 的测试
    QJsonObject obj;
    obj.insert("user_name",QString ("Jwang"));
    obj.insert("passwd",QString("qwe12315"));

    QJsonDocument doc(obj);

    qDebug()<<doc.toJson();


    // 以读写方式打开主目录下的1.json文件，若该文件不存在则会自动创建
    QFile file(QDir::homePath() + "/2.json");
    //qDebug()<<QDir::homePath();

    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error";
        //return -1;
    } else {
        qDebug() << "File open!";
    }

    QByteArray allData = file.readAll();
    file.close();

    QJsonParseError json_error;
    QJsonDocument jsonDoc(QJsonDocument::fromJson(allData, &json_error));

    if(json_error.error != QJsonParseError::NoError)
    {
        qDebug("json error[%d]!",json_error.error);
        //return;
    }

    QJsonObject rootObj = jsonDoc.object();

    QStringList keys = rootObj.keys();
    for(int i = 0; i < keys.size(); i++)
    {
        qDebug() << "key" << i << " is:" << keys.at(i);
        qDebug() << rootObj.value(QString(keys.at(i)));
    }


//rootObj

//    // 将json以文本形式写入文件并关闭文件。
//    file.write(doc.toJson());
//    file.close();

//    qDebug() << "Write to file";

}
