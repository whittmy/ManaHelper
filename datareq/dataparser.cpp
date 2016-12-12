#include "dataparser.h"


DataParser::DataParser(QString parserText)
    :QObject(NULL)
{
    mReader = new QXmlStreamReader(parserText);
    mIsvalid = false;
}

DataParser::~DataParser(){
    delete mReader;
}

void DataParser::parser(){
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

bool DataParser::isValid(){
    return mIsvalid;
}

QString DataParser::getUrl(){
    return mUrl;
}

QString DataParser::getMd5(){
    return mMd5;
}

QString DataParser::getDescription(){
    return mIntro;
}
