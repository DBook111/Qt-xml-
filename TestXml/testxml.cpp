#include "testxml.h"
#include "ui_testxml.h"

TestXml::TestXml(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestXml)
{
    ui->setupUi(this);

    QDir dir;
    currFilePath = "D:/Qt/Code/PostGraduate/TestXml";//根据自己的目录来写
    currFileName = "/TestXml.xml";//文件名
}

TestXml::~TestXml()
{
    delete ui;
}

//读入xml文件
void TestXml::on_pushButton_rXml_clicked()
{
    m_file.setFileName(currFilePath + currFileName);        //没有则创建文件
    if(! m_file.open(QIODevice::ReadOnly | QFile::Text))
    {
        qDebug() << " Read Open false";
        return;
    }

    QDomDocument doc;
    if(!doc.setContent(&m_file))
    {
        m_file.close();
        qDebug() << " Read Open Xml false";
        return;
    }

    int rowNum=  ui->tableWidget->rowCount();
    for(int i = 0 ; i < rowNum ; i++)//清空列表
    {
        ui->tableWidget->removeRow(0);
    }

    QDomElement root = doc.documentElement();           //读取根节点
    QDomNode node = root.firstChild();                  //读取第一个父节点

    while(!node.isNull())
    {
        QDomNodeList sonList = node.childNodes();       //读取子结点集合
        QString rootName = node.toElement().tagName();  //读取父节点名字
        if(rootName.compare("people") == 0) //读取子结点数据
        {
            int row=ui->tableWidget->rowCount();//表格行数
            ui->tableWidget->insertRow(row);
            for(int sonNode = 0;sonNode < sonList.size();sonNode++)
            {
                QDomElement sonElement = sonList.at(sonNode).toElement();       //获取子结点
                if(sonElement.toElement().tagName().compare("Id") == 0)          //与取出子结点进行对比
                {
                    ui->tableWidget->setItem(row,0,new QTableWidgetItem(sonElement.text()));
                }
                else if(sonElement.toElement().tagName().compare("Name") == 0)
                {
                    ui->tableWidget->setItem(row,1,new QTableWidgetItem(sonElement.text()));
                }
                else if(sonElement.toElement().tagName().compare("Sex") == 0)
                {
                    ui->tableWidget->setItem(row,2,new QTableWidgetItem(sonElement.text()));
                }
            }
            QPushButton *btn=new QPushButton;
            btn->setText("删除");
            btn->setStyleSheet("QPushButton{border:none;background:transparent;}");

            ui->tableWidget->setCellWidget(row,3,btn);

            connect(btn,SIGNAL(clicked()),this,SLOT(on_deleteBtn_slot()));
        }
        node = node.nextSibling();                      //读取下一父节点
    }
    m_file.close();
}

//读取xml数据
void TestXml::on_pushButton_wXml_clicked()
{
    m_file.setFileName(currFilePath + currFileName);        //没有则创建文件
    if(!m_file.open(QIODevice::ReadWrite | QIODevice::Truncate | QFile::Text))
    {
        qDebug() << " Write Open false";
        return;
    }

    QDomDocument doc;
    QDomProcessingInstruction version;
    version = doc.createProcessingInstruction("xml","version = \"1.0\" encoding = \"GB2312\"");
    doc.appendChild(version);

    QDomElement root = doc.createElement("data");   //创建顶节点
    doc.appendChild(root);

    for(int i=0;i<ui->tableWidget->rowCount();i++)
    {
        QDomElement itemRootElement = doc.createElement("people"); //创建父节点
        {
            QDomElement node1 = doc.createElement("Id");           //创建子结点
            QDomText domText1 = doc.createTextNode("Id");
            domText1.setData(ui->tableWidget->item(i,0)->text());  //设置子结点数据
            node1.appendChild(domText1);                           //将子节点数据绑定
            itemRootElement.appendChild(node1);                    //将子节点绑定到父节点

            QDomElement node2 = doc.createElement("Name");
            QDomText domText2 = doc.createTextNode("Name");
            domText2.setData(ui->tableWidget->item(i,1)->text());
            node2.appendChild(domText2);
            itemRootElement.appendChild(node2);

            QDomElement node3 = doc.createElement("Sex");
            QDomText domText3 = doc.createTextNode("Sex");
            domText3.setData(ui->tableWidget->item(i,2)->text());
            node3.appendChild(domText3);
            itemRootElement.appendChild(node3);
        }
         root.appendChild(itemRootElement);                        //绑定到顶结点
    }

    m_file.write(doc.toString().toLocal8Bit().data());
    m_file.close();
}

//插入
void TestXml::on_pushButton_insert_clicked()
{
    if(ui->lineEdit_id->text().isEmpty() || ui->lineEdit_name->text().isEmpty())
    {
        qDebug()<<"输入内容为空";
        return;
    }

    QPushButton *btn=new QPushButton;
    btn->setText("删除");
    btn->setStyleSheet("QPushButton{border:none;background:transparent;}");

    int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);
    ui->tableWidget->setItem(row,0,new QTableWidgetItem(ui->lineEdit_id->text()));
    ui->tableWidget->setItem(row,1,new QTableWidgetItem(ui->lineEdit_name->text()));
    ui->tableWidget->setItem(row,2,new QTableWidgetItem(ui->comboBox_sex->currentText()));
    ui->tableWidget->setCellWidget(row,3,btn);

    connect(btn,SIGNAL(clicked()),this,SLOT(on_deleteBtn_slot()));

    ui->lineEdit_id->clear();//清除输入框
    ui->lineEdit_name->clear();
}

//删除
void TestXml::on_deleteBtn_slot()
{
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}
