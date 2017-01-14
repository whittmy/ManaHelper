#include "siteparser.h"
#include <QDebug>

SiteParser::SiteParser(){
    
}
SiteParser::~SiteParser(){
    
}

bool SiteParser::bSupport(QString url){
    if(url.indexOf(QRegExp("56.com/[a-zA-Z][0-9]{2}/v_")) >=0
            || url.indexOf(QRegExp("56.com/[a-zA-Z][0-9]{2}/play_album")) >= 0){
        qDebug() << "56.com";
        return true;
    }

    if(url.indexOf(QRegExp("acfun.[a-z]{1,}/v/")) >= 0){
        qDebug() << "acfun.";
        return true;
    }

    if(url.contains("baofeng.com/play")
            || url.contains("baofeng.com/micv")
            || url.contains("baofeng.com/video/")){
        qDebug() << "baofeng";
        return true;
    }

    if(url.contains("baomihua.com/v/")
            || url.contains("baomihua.com/user/")){
        qDebug() << "baomihua";
        return true;
    }

    if(url.contains("open.163.com/movie/")){
        qDebug() << "163";
        return true;
    }

    if(url.contains("bilibili.com/video/")
            || url.contains("bangumi.bilibili.com/anime")){
        qDebug() << "bilibili";
        return true;
    }
    if(url.contains("v.ku6.com/show/")){
        qDebug() << "ku6";
        return true;
    }

    if(url.contains("le.com/ptv/vplay/")){
        qDebug() << "le.com";
        return true;
    }
    if(url.indexOf(QRegExp("mgtv.com/[a-z]{1,2}/")) >= 0){
        qDebug() << "mgtv";
        return true;
    }

    if(url.contains("v.pptv.com/show/")){
        qDebug() << "pptv";
        return true;
    }
    if(url.contains(QRegExp("v.ifeng.com/[a-z]{1,14}/[a-z]{1,10}/[0-9]{6}"))){
        qDebug() << "ifeng";
        return true;
    }

    if(url.contains("v.qq.com/x/cover/")){
        qDebug() << "qq";
        return true;
    }

    if(url.contains("shenqu.yy.com/play/id")){
        qDebug() << "yy-mv";
        return true;
    }

    if(url.indexOf(QRegExp("my.tv.sohu.com/[a-z]{1,3}/[0-9]{3,}")) >= 0
            ||url.indexOf(QRegExp("tv.sohu.com/[0-9]{7,}")) >= 0){
        qDebug() << "sohu";
        return true;
    }

    if(url.indexOf(QRegExp("tangdou.com/v88/")) >= 0
            || url.indexOf(QRegExp("tangdou.com/html/playlist/[0-9]{2,}/")) >= 0){
        qDebug() << "tangdou";
        return true;
    }

    if(url.contains("v.yinyuetai.com/video/")){
        qDebug() << "yinyuetai";
        return true;
    }

    if(url.contains("v.youku.com/v_show/id")){
        qDebug() << "youku";
        return true;
    }



    return false;
}
