#ifndef MYTREEVIEW_H
#define MYTREEVIEW_H
#include <QObject>
#include <QString>
#include <QTreeView>
#include <QStandardItemModel>
#include <QEvent>

//两个类
//model中 inline函数
class MyTreeModel :public QStandardItemModel{
public:
    MyTreeModel(QTreeView *parent);
    ~MyTreeModel();

    //让所有目录都前面都显示 小三角
    bool hasChildren(const QModelIndex &parent) const;

};



class MyTreeView: public QTreeView{
    Q_OBJECT        //！！！添加Q_OBJECT总是链接不通过， 只需重新qmake一下

public:
    MyTreeView(QWidget *parent);
    ~MyTreeView();

signals:
    void expanded(QModelIndex &index); //展开
    void folded(QModelIndex &index); //折叠
    void clicked(QModelIndex &index);

protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // PATHS_H
