#ifndef MYJSON_H
#define MYJSON_H

#include <QWidget>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>

#include <QLabel>
#include <QLineEdit>
#include <QCoreApplication>
#include <QPushButton>

class MyJson : public QWidget
{
    Q_OBJECT
public:
    explicit MyJson(QWidget *parent = 0);

signals:

public slots:
    void savejson();
private:
    QFile *m_jsonfile;//操作的文件

    QJsonDocument *m_jsondoc;//JSON文件
    QJsonObject m_jsonobj;//JSON对象
private://界面
    QLabel      *m_powerlabel;
    QLineEdit   *m_poweredit;
    QLabel      *m_frelabel;
    QLineEdit   *m_freedit;
    QPushButton *m_btn;
};

#endif // MYJSON_H
