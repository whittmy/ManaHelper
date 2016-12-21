#ifndef UPDATAPARSER_H
#define UPDATAPARSER_H

#include <QObject>
#include <QString>
#include <QXmlStreamReader>

////////////
///  类、结构、枚举、typedef等定义语句都需要 分号 界面， 许久未用，仍需谨记
///


class Xml_Parser_Upgrade: public QObject{
    Q_OBJECT
public:
    Xml_Parser_Upgrade(QString parserText);
    ~Xml_Parser_Upgrade();
    
    void parser();
    QString getUrl();
    QString getMd5();
    QString getDescription();
    bool isValid();


private:
    bool mIsvalid;
    QString mUrl;
    QString mMd5;
    QString mIntro;
    QXmlStreamReader *mReader;
};

#endif // UPDATAPARSER_H
