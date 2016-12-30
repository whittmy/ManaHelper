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
   mDevPathHash.insert("drawcourse", QStringLiteral(""));
   mDevPathHash.insert("classic baby", QStringLiteral(""));
   mDevPathHash.insert("pop baby", QStringLiteral(""));
   mDevPathHash.insert("pop music", QStringLiteral(""));
   mDevPathHash.insert("happy dance", QStringLiteral(""));
   mDevPathHash.insert("do it", QStringLiteral(""));
   mDevPathHash.insert("guo xue qi meng", QStringLiteral(""));
   mDevPathHash.insert("cheng yu gu shi", QStringLiteral(""));
   mDevPathHash.insert("shu li luo ji", QStringLiteral(""));
   mDevPathHash.insert("bai ke zhi shi", QStringLiteral(""));
   mDevPathHash.insert("tang shi song ci", QStringLiteral(""));
   mDevPathHash.insert("dong hua pian", QStringLiteral(""));
   mDevPathHash.insert("shi pin er ge", QStringLiteral(""));

   mDevPathHash.insert("shi pin gu shi", QStringLiteral(""));
   mDevPathHash.insert("shi pin ying yu", QStringLiteral(""));


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
     return "";
}
