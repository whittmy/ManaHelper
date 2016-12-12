#ifndef DATAPARSER_H
#define DATAPARSER_H

#include <QObject>
#include <QString>
#include <QXmlStreamReader>

////////////
///  类、结构、枚举、typedef等定义语句都需要 分号 界面， 许久未用，仍需谨记
///


class DataParser: public QObject{
    Q_OBJECT
public:
    DataParser(QString parserText);
    ~DataParser();
    
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

#endif // DATAPARSER_H
