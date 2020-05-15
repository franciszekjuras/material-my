#include "qtmaterialdropdown.h"
#include "qtmaterialdropdown_p.h"
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QPainter>
#include <QDebug>
#include <QtWidgets/QApplication>
#include "lib/qtmaterialstyle.h"
#include "qtmaterialdropdown_internal.h"
#include "qtmaterialframe.h"

/*!
 *  \class QtMaterialDropdownPrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialDropdownPrivate::QtMaterialDropdownPrivate(QtMaterialDropdown *q)
    : q_ptr(q)
{
}

/*!
 *  \internal
 */
QtMaterialDropdownPrivate::~QtMaterialDropdownPrivate()
{
}

/*!
 *  \internal
 */
void QtMaterialDropdownPrivate::init()
{
    Q_Q(QtMaterialDropdown);

    dropdown        = new QWidget;
    frame           = new QWidget;
    stateMachine    = new QtMaterialDropdownStateMachine(dropdown);

    dropdown->setParent(q);
    frame->setParent(q);

    dropdown->installEventFilter(q);
    frame->installEventFilter(q);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(11);
    effect->setColor(QColor(0, 0, 0, 50));
    effect->setOffset(0, 3);

    frame->setGraphicsEffect(effect);
    frame->setVisible(false);

    dropdown->setVisible(false);

    stateMachine->start();
}

/*!
 *  \class QtMaterialDropdown
 */

QtMaterialDropdown::QtMaterialDropdown(QWidget *parent)
    : QtMaterialDropdown(*new QtMaterialDropdownPrivate(this), parent)
{
    d_func()->init();
}

QtMaterialDropdown::~QtMaterialDropdown()
{
}

//bool QtMaterialDropdown::QtMaterialDropdown::event(QEvent *event)
//{
//    Q_D(QtMaterialDropdown);

//    switch (event->type())
//    {
//    case QEvent::Move:
//    case QEvent::Resize: {
//        d->dropdown->move(pos() + QPoint(0, height() + 6));
//        break;
//    }
//    case QEvent::ParentChange: {
////        d->dropdown->setParent(nullptr);
////        d->frame->setParent(nullptr);
//        break;
//    }
//    default:
//        break;
//    }
//    return QWidget::event(event);
//}

void QtMaterialDropdown::toggleDeffered(){
    Q_D(QtMaterialDropdown);
    if(d->frame->isVisible()){
        QTimer::singleShot(0,d->stateMachine, &QtMaterialDropdownStateMachine::shouldClose);
    }
    else{
        QTimer::singleShot(0,d->stateMachine, &QtMaterialDropdownStateMachine::shouldOpen);
    }
}

bool QtMaterialDropdown::eventFilter(QObject *watched, QEvent *event)
{
    Q_D(QtMaterialDropdown);

//    if(event->type()!=QEvent::Timer){
//        qDebug() << event->type() << watched;
//    }

    if (d->frame->parent() == watched){
//        qDebug() << event->type();


        switch (event->type())
        {
        case QEvent::WindowDeactivate:
        case QEvent::NonClientAreaMouseButtonPress:
            //qDebug() << d->frame->parent();
            d->stateMachine->shouldClose();
            break;
        case QEvent::MouseButtonPress:

            break;
        default:
            break;
        }
    }

    if(QEvent::MouseButtonPress == event->type()){
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        qDebug() << mouseEvent->globalPos() << watched;
        if(!rect().contains(mapFromGlobal(mouseEvent->globalPos())) &&
                !d->dropdown->rect().contains(d->frame->mapFromGlobal(mouseEvent->globalPos()))){
            qDebug() << "pressed outside";
            QTimer::singleShot(0,d->stateMachine, &QtMaterialDropdownStateMachine::shouldClose);
        }
    }

    if (d->frame == watched)
    {
        switch (event->type())
        {
        case QEvent::Paint: {
            QPainter painter(d->frame);
            painter.fillRect(d->frame->rect(), QtMaterialStyle::instance().themeColor("surface"));
            painter.fillRect(d->frame->rect(), QtMaterialStyle::instance().themeColor("raisedElevation"));
            break;
        }
        default:
            break;
        }
    }
    else if (d->dropdown == watched)
    {
        switch (event->type())
        {
        case QEvent::Resize:
        case QEvent::Move: {
            qDebug() << "move | resize";
            qDebug() << d->dropdown->isVisible();
            d->frame->setGeometry(d->dropdown->geometry());
            break;
        }
        case QEvent::Show: {
            qApp->installEventFilter(this);
            d->dropdown->removeEventFilter(this);
            d->frame->removeEventFilter(this);
            if(d->dropdown->parent() == this){
                QWidget *widget = static_cast<QWidget *>(this);
                while (widget->parentWidget() != nullptr) widget = widget->parentWidget();
                d->dropdown->setParent(widget);
                d->frame->setParent(widget);
                d->dropdown->show();
            }
            d->dropdown->setFixedSize(d->dropdown->sizeHint());
            d->dropdown->move(d->dropdown->parentWidget()->mapFromGlobal(mapToGlobal(QPoint(0,height()+5))));
            d->frame->setGeometry(d->dropdown->geometry());
            d->frame->show();
            d->frame->raise();
            d->dropdown->raise();
            break;
        }
        case QEvent::Hide: {
            qApp->removeEventFilter(this);
            d->dropdown->installEventFilter(this);
            d->frame->installEventFilter(this);
            d->frame->hide();
            break;
        }
        default:
            break;
        }
    }
   /*else
    {
        switch (event->type())
        {
        case QEvent::MouseButtonPress: {
            emit d->stateMachine->shouldFade();
            //QtMaterialFlatButton *widget;
//            if ((widget = static_cast<QtMaterialFlatButton *>(watched))) {
//                QString text(widget->text());
//                setText(text);
//                emit itemSelected(text);
//            }
            break;
        }
        default:
            break;
        }
    }*/
    //return QWidget::eventFilter(watched, event);
    return false;
}

QtMaterialDropdown::QtMaterialDropdown(QtMaterialDropdownPrivate &d, QWidget *parent)
    : QWidget(parent),
      d_ptr(&d)
{
    d_func()->init();
}
