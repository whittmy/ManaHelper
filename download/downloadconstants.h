/****************************************************************************************
** downloadconstants.h is part of yoDownet
**
** Copyright 2013 Alireza Savand <alireza.savand@gmail.com>
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

#ifndef DOWNLOADCONSTANTS_H
#define DOWNLOADCONSTANTS_H

namespace DownloadConstants {
    namespace Attributes {
        enum Attributes{
            ID,
            FileName,
            URL,
            Size,
            Progress,
            Speed,
            ElapseTime,
            RemainingTime,
            SavePath,
            Queue,
            Status,
            AddedDate,
            Downloaded,
            LastTryDate,
            Description,
            Referer,
            Type,
            Pieces,
            Uuid
        };
    }
}


#endif // DOWNLOADCONSTANTS_H
