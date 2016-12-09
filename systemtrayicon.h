#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H

#include <QSystemTrayIcon>

class SystemTrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit SystemTrayIcon(QObject *parent = 0);
    ~SystemTrayIcon();
    int setBlink(bool);
    QTimer *blinktimer;
    int defaulticon;
    bool blinking;
public slots:
    int blinkicon();
};
#endif // SYSTEMTRAYICON_H
