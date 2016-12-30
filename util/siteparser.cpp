#include "siteparser.h"

SiteParser::SiteParser(){
    
}
SiteParser::~SiteParser(){
    
}

bool SiteParser::bSupport(QString url){
    if(url.indexOf(QRegExp("56.com/[a-zA-Z][0-9]{2}/v_")) >=0 )
        return true;
    if(url.contains("v.youku.com/v_show/id"))
        return true;
    if(url.indexOf(QRegExp("acfun\.[a-z]*/v/")) >= 0)
        return true;
    return false;
}
