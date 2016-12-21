#ifndef URLDATAPARSER_H
#define URLDATAPARSER_H

#include <QObject>
#include <QString>
#include <QXmlStreamReader>
#include <QStringList>
#include <QFile>

////////////
///  类、结构、枚举、typedef等定义语句都需要 分号 界面， 许久未用，仍需谨记
///


class Xml_Parser_Playurl: public QObject{
    Q_OBJECT
public:
    Xml_Parser_Playurl(QString parserText);
    Xml_Parser_Playurl(QFile &f);
    ~Xml_Parser_Playurl();
    
    void parser();
    QStringList getFiles();
    bool isValid();


private:
    bool mIsvalid;
    QStringList mFiles;

    QXmlStreamReader *mReader;
};

#endif // URLDATAPARSER_H
