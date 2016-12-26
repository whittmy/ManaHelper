#ifndef SITEPARSER_H
#define SITEPARSER_H
 
#include <QObject>
#include <QString>

class SiteParser: public QObject
{
    Q_OBJECT

public:
    SiteParser();
    ~SiteParser();
 
    bool bSupport(QString url);
private:
 

};

#endif // SITEPARSER_H
