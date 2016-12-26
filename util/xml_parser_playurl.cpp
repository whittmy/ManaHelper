#include "xml_parser_playurl.h"
#include <QTextStream>

Xml_Parser_Playurl::Xml_Parser_Playurl(QString parserText)
    :QObject(NULL)
{
    mReader = new QXmlStreamReader(parserText);
    mIsvalid = false;
}

Xml_Parser_Playurl::Xml_Parser_Playurl(QFile &f)
    :QObject(NULL)
{
    QString str;
    if(f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream txtInput(&f);
        while(!txtInput.atEnd())
        {
            str += txtInput.readLine();
        }
        f.close();
    }
    mReader = new QXmlStreamReader(str);
    mIsvalid = false;
}

Xml_Parser_Playurl::~Xml_Parser_Playurl(){
    delete mReader;
}

void Xml_Parser_Playurl::parser(){
    while(!mReader->atEnd() && !mReader->hasError()){
        QXmlStreamReader::TokenType token = mReader->readNext();
        if(token == QXmlStreamReader::StartDocument)
            continue;

        if(mReader->isStartElement()){
            if(mReader->name() == "State"){
                if(mReader->readElementText() != "normal"){
                    mIsvalid = false;
                    return;
                }
            }
            if(mReader->name() == "file"){
                QString url  = mReader->readElementText();
                if(!url.isEmpty())
                    mFiles.append(url);
            }
        }
    }

    mIsvalid = true;
}

bool Xml_Parser_Playurl::isValid(){
    return mIsvalid;
}


QStringList Xml_Parser_Playurl::getFiles(){
    return mFiles;
}
