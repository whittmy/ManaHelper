/****************************************************************************************
** paths.cpp is part of yoDownet
**
** Copyright 2012 Alireza Savand <alireza.savand@gmail.com>
**
** yoDownet is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 3 of the License, or
** (at your option) any later version.
**
** yoDownet is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************************/

#include "paths.h"
#include <QSettings>
#include <QDir>
#include <QMessageBox>
#include <QTextStream>
#include <QDebug>

#define TRANSLATION_PATH "c:/"
#define DOC_PATH "c:/"

QHash<QString, QString> Paths::mDevPathHash;

void Paths::init(){
    mDevPathHash.insert("drawcourse", QStringLiteral("艺术培养/小小画家/绘画课堂"));
    mDevPathHash.insert("classic baby", QStringLiteral("艺术培养/我是歌手/经典儿歌"));
    mDevPathHash.insert("pop baby", QStringLiteral("艺术培养/我是歌手/流行儿歌"));
    mDevPathHash.insert("pop music", QStringLiteral("艺术培养/我是歌手/流行音乐"));
    mDevPathHash.insert("happy dance", QStringLiteral("艺术培养/快乐舞蹈"));
    mDevPathHash.insert("do it", QStringLiteral("艺术培养/动手实践"));
    mDevPathHash.insert("guo xue qi meng", QStringLiteral("传统教育/国学启蒙"));
    mDevPathHash.insert("cheng yu gu shi", QStringLiteral("传统教育/成语故事"));
    mDevPathHash.insert("shu li luo ji", QStringLiteral("传统教育/数理逻辑"));
    mDevPathHash.insert("bai ke zhi shi", QStringLiteral("传统教育/百科知识"));
    mDevPathHash.insert("tang shi song ci", QStringLiteral("传统教育/唐诗宋词"));
    mDevPathHash.insert("dong hua pian", QStringLiteral("娱乐天地/动画"));
    mDevPathHash.insert("shi pin gu shi", QStringLiteral("娱乐天地/故事"));
    mDevPathHash.insert("shi pin ying yu", QStringLiteral("英语教学/快乐英语"));


}

QString Paths::translationPath()
{
    return  STRINGIFY(TRANSLATION_PATH);
}

QString Paths::docPath()
{
    return  STRINGIFY(DOC_PATH);
}


QString Paths::cacheDirPath()
{
//    QSettings settings;
//    settings.beginGroup("PreferencesDialog");
//    settings.beginGroup("PrefDownloadersWidget");
//    QString savePath = settings.value("saveDir", QDir::homePath()).toString() + QDir::toNativeSeparators("/");
//    settings.endGroup();
//    settings.endGroup();
    QString savePath = "c:\\qt_test\\";
    return savePath;
}


void Paths::writeTxtFile(QString filepath, QString txt){
    QFile file(filepath);
    //方式：Append为追加，WriteOnly，ReadOnly
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text)) {
        QMessageBox::critical(NULL, "提示", "无法创建文件");
        return;
    }
    QTextStream out(&file);
    out << txt;
    out.flush();
    file.close();
    //注意写入方式的选择，注意写完后的关闭操作！
}


QString Paths::devicePath(QString txt){
     return mDevPathHash.find(txt).value();
}

QString Paths::filter(QString strTest){
    strTest = strTest .replace("\n", "");
    strTest = strTest.replace("\t", "");
    strTest = strTest.replace("\\","");
    strTest = strTest.simplified(); //去掉前后空格
    QRegExp exp("[</:>*?|]");    //无法包括\\,\t, \n不得不单独处理
    strTest = strTest.replace(exp, "");

    //  \x00-\x1f是不可见的控制字符，\x7f是delete，也不可见，所以替换掉
    QRegExp exp1("[\x01-0x1f]");
    strTest = strTest.replace(exp1, "");
    qDebug() << "strTest========1=======" << strTest;

    QRegExp exp2("[\x7f]");
    strTest = strTest.replace(exp2, "");
    return strTest;
}
