#include "xml_parser_upgrade.h"


Xml_Parser_Upgrade::Xml_Parser_Upgrade(QString parserText)
    :QObject(NULL)
{
    mReader = new QXmlStreamReader(parserText);
    mIsvalid = false;
}

Xml_Parser_Upgrade::~Xml_Parser_Upgrade(){
    delete mReader;
}

void Xml_Parser_Upgrade::parser(){
    while(!mReader->atEnd() && !mReader->hasError()){
        QXmlStreamReader::TokenType token = mReader->readNext();
        if(token == QXmlStreamReader::StartDocument)
            continue;

        if(mReader->isStartElement()){
            if(mReader->name() == "status"){
                if(mReader->readElementText() != "success"){
                    mIsvalid = false;
                    return;
                }
            }
            if(mReader->name() == "url"){
                mUrl = mReader->readElementText();
            }
            else if(mReader->name() == "md5"){
                mMd5 = mReader->readElementText();
            }
            else if(mReader->name() == "description"){
                mIntro = mReader->readElementText();
            }

        }
    }

    mIsvalid = true;
}

bool Xml_Parser_Upgrade::isValid(){
    return mIsvalid;
}

QString Xml_Parser_Upgrade::getUrl(){
    return mUrl;
}

QString Xml_Parser_Upgrade::getMd5(){
    return mMd5;
}

QString Xml_Parser_Upgrade::getDescription(){
    return mIntro;
}
