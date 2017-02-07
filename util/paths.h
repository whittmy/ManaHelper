/****************************************************************************************
** paths.h is part of yoDownet
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

#ifndef PATHS_H
#define PATHS_H

#define STRINGIFY2(x) #x
#define STRINGIFY(x) STRINGIFY2(x)

#include <QString>
#include <QHash>
class Paths
{
public:
    static void init();
    static QString translationPath();
    static QString docPath();
    static QString mvCachePath();
    static QString dbPath();
    static void writeTxtFile(QString file, QString txt);
    static QString devicePath(QString txt);
    static QString  filter(QString strTest);
    static void writeFileFromQrc(QString qrcpath, QString dest);
private:
    static QHash<QString, QString> mDevPathHash;
};

#endif // PATHS_H
