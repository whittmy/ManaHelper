#include "mytreeview.h"
#include <QSettings>
#include <QDir>
#include <QMouseEvent>
#include <QHeaderView>
#include <QMessageBox>
#include <QDebug>

MyTreeModel::MyTreeModel(QTreeView *parent)
    :QStandardItemModel(parent){

}

MyTreeModel::~MyTreeModel(){

}

//让所有目录都前面都显示 小三角
bool MyTreeModel::hasChildren(const QModelIndex &parent) const{
    parent;
    return true;
}




MyTreeView::MyTreeView(QWidget *parent)
    :QTreeView(parent){
    //设置水平、垂直滚动条，当超出显示时有必要显示
    // 默认是支持的。
    //  setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    //   setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    //!!水平的滚动条有些特殊，刷新是需要调用 resizeColumnToContents(调整列)
}

MyTreeView::~MyTreeView(){

}


void MyTreeView::mousePressEvent(QMouseEvent *event){
    QModelIndex indexClicked = indexAt(event->pos()); //根据pos获取index
    if(indexClicked.isValid()){
        //返回对应item的矩形区域,不含前面三角形(但包含图标)
        QRect vrect = visualRect(indexClicked);

        //返回root-item的矩形区域，包括三角形
        QRect rootRect = visualRect(rootIndex());

        //计算 当前被点击item相对于root区域的x偏移
        int itemIndentation = vrect.x() - rootRect.x();
        //qDebug() << "vrect:" << vrect;
        //qDebug() << "rootRect:" << rootRect;
        //qDebug() << "itemIndentation:" << itemIndentation;

        QRect rect = QRect(header()->sectionViewportPosition(0) + itemIndentation, vrect.y(),
                                   style()->pixelMetric(QStyle::PM_IndicatorWidth), vrect.height());
        //qDebug() << "rect:" << rect;
        if( rect.contains(event->pos()) )
        {
             QStandardItem *item = ((QStandardItemModel*)model())->itemFromIndex(indexClicked);
            if( item->checkState() == Qt::Unchecked )
            {
                //mark_subitem(indexClicked);
                qDebug()<< "unchecked";
            }
            else
            {
                //unmark_subitem(indexClicked);
                qDebug()<< "checked";
            }

            emit clicked(indexClicked);
        }
        else if(event->x() < itemIndentation)
        {
            //判断前面那个三角区域的点击事件
            if(isExpanded(indexClicked)){
                //qDebug() << "to close!";
                emit folded(indexClicked);
            }
            else{
                //qDebug() << "to open";
                emit expanded(indexClicked);
            }
        }
        else{
            emit clicked(indexClicked);
        }
    }

    QTreeView::mousePressEvent(event);
}
