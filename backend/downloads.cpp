#include "downloads.h"

Downloads::Downloads(QObject *parent) :
    QObject(parent)
{
    ///this class will manage all the downloading activities.
    ///it will maintain a progress dialog..
    ///this class will be responsible for sending network request and saving files.
    ///so basically this is the core heart of this app
    ///variables list
    /// *progressdialog  >>> the dialog it will manage
    /// *localmodel >>> the model it will use
    /// modelindex >>> to represent the downloading item from the model
    ///


}
