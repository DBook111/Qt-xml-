#ifndef TESTXML_H
#define TESTXML_H

#include <QMainWindow>
#include <QDomComment>//QDomNodeList头文件
#include <QDir>
#include <QFile>
#include <QDebug>
#include <QPushButton>

namespace Ui {
class TestXml;
}

class TestXml : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestXml(QWidget *parent = nullptr);
    ~TestXml();


private slots:
    void on_pushButton_wXml_clicked();//写入xml数据

    void on_pushButton_rXml_clicked();//读取xml数据

    void on_pushButton_insert_clicked();//插入

    void on_deleteBtn_slot();//删除

private:
    Ui::TestXml *ui;

    QFile m_file;

    QString currFilePath;   //当前文件路径

    QString currFileName;   //当前文件名字
};

#endif // TESTXML_H
