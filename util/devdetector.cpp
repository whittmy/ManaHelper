#include "devdetector.h"
#include <QDebug>
#include<QString>
#include <QDir>
#include <QFileInfo>

static const GUID GUID_DEVINTERFACE_LIST[] =
{
// GUID_DEVINTERFACE_USB_DEVICE
{ 0xA5DCBF10, 0x6530, 0x11D2, { 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED } },
// GUID_DEVINTERFACE_DISK
//{ 0x53f56307, 0xb6bf, 0x11d0, { 0x94, 0xf2, 0x00, 0xa0, 0xc9, 0x1e, 0xfb, 0x8b } },
// GUID_DEVINTERFACE_HID,
//{ 0x4D1E55B2, 0xF16F, 0x11CF, { 0x88, 0xCB, 0x00, 0x11, 0x11, 0x00, 0x00, 0x30 } },
// GUID_NDIS_LAN_CLASS
//{ 0xad498944, 0x762f, 0x11d0, { 0x8d, 0xcb, 0x00, 0xc0, 0x4f, 0xc3, 0x35, 0x8c } }
//// GUID_DEVINTERFACE_COMPORT
//{ 0x86e0d1e0, 0x8089, 0x11d0, { 0x9c, 0xe4, 0x08, 0x00, 0x3e, 0x30, 0x1f, 0x73 } },
//// GUID_DEVINTERFACE_SERENUM_BUS_ENUMERATOR
//{ 0x4D36E978, 0xE325, 0x11CE, { 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18 } },
//// GUID_DEVINTERFACE_PARALLEL
//{ 0x97F76EF0, 0xF883, 0x11D0, { 0xAF, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x84, 0x5C } },
//// GUID_DEVINTERFACE_PARCLASS
//{ 0x811FC6A5, 0xF728, 0x11D0, { 0xA5, 0x37, 0x00, 0x00, 0xF8, 0x75, 0x3E, 0xD1 } }
};


DevDetector::DevDetector(HANDLE handle, QObject *parent)
    :QObject(parent), _wnd(handle), _logger(new LogMe(this))
{
    _logger->debug("DevDetector construct");
    registerListener();
    checkDev();
}

DevDetector::~DevDetector(){
    delete _logger;
}


void DevDetector::registerListener(){
    _logger->info("begin registerListener");
#if 1
 //注册插拔事件
   HDEVNOTIFY hDevNotify;
   DEV_BROADCAST_DEVICEINTERFACE NotifacationFiler;
   ZeroMemory(&NotifacationFiler,sizeof(DEV_BROADCAST_DEVICEINTERFACE));
   NotifacationFiler.dbcc_size = sizeof(DEV_BROADCAST_DEVICEINTERFACE);
   NotifacationFiler.dbcc_devicetype = DBT_DEVTYP_DEVICEINTERFACE;

   for(int i=0;i<sizeof(GUID_DEVINTERFACE_LIST)/sizeof(GUID);i++) {
       NotifacationFiler.dbcc_classguid = GUID_DEVINTERFACE_LIST[i];//GetCurrentUSBGUID();//m_usb->GetDriverGUID();

       hDevNotify = RegisterDeviceNotification(/*(HANDLE)this->winId()*/_wnd,&NotifacationFiler,DEVICE_NOTIFY_WINDOW_HANDLE);
       if(!hDevNotify) {
           int Err = GetLastError();
           qDebug() << u8"注册失败" <<endl;
       }
       else{
           qDebug() << u8"注册成功";
       }
   }
 #endif
    _logger->info("end registerListener");
}

QString DevDetector::getDevPath(){
    _logger->info("getDevPath : " + _devPath);
    return _devPath;
}


void DevDetector::checkDev(){
    //遍历所有驱动器
    //适应规则
    _logger->info("begin checkDev");

    QFileInfoList list =  QDir::drives();
    for(QFileInfoList::const_iterator iter = list.end();iter != list.begin();){
        QString drive = (*(--iter)).absolutePath();
        _logger->info(drive);

        if(adaptRules(drive)){
            _devPath = drive;
            emit devConnected(_devPath);
            _logger->info("end checkDev(had dev)");
            return;
        }
    }

    _logger->info("end checkDev(no dev)");
}

bool DevDetector::adaptRules(QString drive){
    _logger->info("begin adaptRules");
    //注意路径分隔符细节
    QString rule1 = QDir::toNativeSeparators(drive + "mmh.ico");
    QString rule2 = QDir::toNativeSeparators(drive + "CFG");
    QString rule3 = QDir::toNativeSeparators(drive + u8"艺术培养\\小小画家\\檬檬爱画画");
    QString rule4 = QDir::toNativeSeparators(drive + u8"娱乐天地\\动画\\EP01-《星际小蚂蚁》_公益大使_防火安全系列_01_H264高清_1280x720.MP4");
    QString rule5 = QDir::toNativeSeparators(drive + u8"工具\\伴眠模式");
    QString rule6 = QDir::toNativeSeparators(drive + u8"工具\\相册");
    _logger->info("end adaptRules");
    return false;
}

bool DevDetector::nativeEvent(const QByteArray &eventType, void *message, long *result){
    _logger->info("begin nativeEvent");
    MSG* msg = reinterpret_cast<MSG*>(message);
    int msgType = msg->message;
    if(msgType==WM_DEVICECHANGE)
    {
        //qDebug() << "Event DEVICECHANGE Happend" << endl;
        PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)msg->lParam;
        switch (msg->wParam) {
        case DBT_DEVICEARRIVAL:
            if(lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
            {
                PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
                if(lpdbv->dbcv_flags ==0)
                {
                    //插入u盘
                    QString USBDisk = QString(this->FirstDriveFromMask(lpdbv ->dbcv_unitmask));
                    qDebug() << "USB_Arrived and The USBDisk is: "<<USBDisk ;
                    //ui->textBrowser->append("USB_Arrived and The USBDisk is " + USBDisk);

                }
            }
            if(lpdb->dbch_devicetype = DBT_DEVTYP_DEVICEINTERFACE)
            {
                PDEV_BROADCAST_DEVICEINTERFACE pDevInf  = (PDEV_BROADCAST_DEVICEINTERFACE)lpdb;

                QString strname = QString::fromWCharArray(pDevInf->dbcc_name,pDevInf->dbcc_size);
                qDebug() << u8"插入设备: " << QString::fromUtf8(strname.toLatin1().data());
               // ui->textBrowser->append("插入设备 ：" + strname);
            }
            break;
        case DBT_DEVICEREMOVECOMPLETE:
            qDebug() << u8"设备移除" <<endl;
            if(lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
            {
                PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
                if(lpdbv->dbcv_flags == 0)
                {
                    qDebug() << "USB_Removed";
                    //ui->textBrowser->append("USB_Remove");

                }
            }
            if(lpdb->dbch_devicetype = DBT_DEVTYP_DEVICEINTERFACE)
            {
                PDEV_BROADCAST_DEVICEINTERFACE pDevInf  = (PDEV_BROADCAST_DEVICEINTERFACE)lpdb;
                qDebug()<< u8"移除设备(name)：" << pDevInf->dbcc_name;
                //qDebug()<< "移除设备(guid)：" << pDevInf->dbcc_classguid;
                qDebug()<< u8"移除设备(size)：" << pDevInf->dbcc_size;

                QString strname = QString::fromWCharArray(pDevInf->dbcc_name,pDevInf->dbcc_size);
                qDebug() << u8"移除设备："+ QString::fromUtf8(strname.toLatin1().data());
                //ui->textBrowser->append("移除设备 " + strname);
            }
            break;
        }
    }
    _logger->info("end nativeEvent");
    return false;

}

char DevDetector::FirstDriveFromMask (ULONG unitmask){
    _logger->info("begin FirstDriveFromMask");
    char i;
    for (i = 0; i < 26; ++i)
    {
        if (unitmask & 0x1)
            break;
        unitmask = unitmask >> 1;
    }
    _logger->info("end FirstDriveFromMask");
    return (i + 'A');
}
