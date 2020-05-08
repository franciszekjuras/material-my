#include "qtmaterialautocomplete.h"
#include "qtmaterialautocomplete_p.h"
#include <QtWidgets/QGraphicsDropShadowEffect>
#include <QtWidgets/QVBoxLayout>
#include <QEvent>
#include <QTimer>
#include <QPainter>
#include <QDebug>
#include "lib/qtmaterialstyle.h"
#include "qtmaterialautocomplete_internal.h"
#include "qtmaterialflatbutton.h"

/*!
 *  \class QtMaterialAutoCompletePrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialAutoCompletePrivate::QtMaterialAutoCompletePrivate(QtMaterialAutoComplete *q)
    : QtMaterialFlatButtonPrivate(q)
{
}

/*!
 *  \internal
 */
QtMaterialAutoCompletePrivate::~QtMaterialAutoCompletePrivate()
{
}

/*!
 *  \internal
 */
void QtMaterialAutoCompletePrivate::init()
{
    Q_Q(QtMaterialAutoComplete);

    menu         = new QWidget;
    frame        = new QWidget;
    stateMachine = new QtMaterialAutoCompleteStateMachine(menu);
    menuLayout   = new QVBoxLayout;
    maxWidth     = 0;
    toggle       = false;


//    menu->setParent(q->parentWidget());
//    frame->setParent(q->parentWidget());

    menu->installEventFilter(q);
    frame->installEventFilter(q);

    QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(11);
    effect->setColor(QColor(0, 0, 0, 50));
    effect->setOffset(0, 3);

    frame->setGraphicsEffect(effect);
    frame->setVisible(false);

    menu->setLayout(menuLayout);
    menu->setVisible(false);

    menuLayout->setContentsMargins(0, 0, 0, 0);
    menuLayout->setSpacing(0);

    QObject::connect(q, SIGNAL(clicked()), q, SLOT(updateResults()));

    stateMachine->start();
}

/*!
 *  \class QtMaterialAutoComplete
 */

QtMaterialAutoComplete::QtMaterialAutoComplete(QWidget *parent)
    : QtMaterialFlatButton(*new QtMaterialAutoCompletePrivate(this), parent)
{
    d_func()->init();
//    QFont f(font());
//    f.setWeight(QFont::Normal);
    QFont ft("Roboto", 12, QFont::Normal);
    setFont(ft);

    setTextAlignment(Qt::AlignLeft);
    setCornerRadius(3);
    setHaloVisible(false);
    //setFixedHeight(50);
    setOverlayStyle(Material::GrayOverlay);
    //setOverlayColor(QColor(255,0,0));
    setRole(Material::Default);
    setIconPlacement(Material::RightIcon);
    setIconSize(QSize(28,28));
    setIcon(QtMaterialTheme::icon("navigation", "unfold_more"));
}

QtMaterialAutoComplete::~QtMaterialAutoComplete()
{
}

void QtMaterialAutoComplete::setDataSource(const QStringList &data)
{
    Q_D(QtMaterialAutoComplete);

    d->dataSource = data;
    update();

    QString text(data.at(0));
    setText(text);
    emit itemSelected(text);
}

void QtMaterialAutoComplete::updateResults()
{
    Q_D(QtMaterialAutoComplete);

    if(d->toggle){
        d->toggle = false;
        return;
    }

    if(d->menu->parent() == nullptr){
        QWidget *widget = static_cast<QWidget *>(parent());
        while (widget->parentWidget() != Q_NULLPTR) widget = widget->parentWidget();
        d->menu->setParent(widget);
        d->frame->setParent(widget);
    }
    d->menu->move(d->menu->parentWidget()->mapFromGlobal(mapToGlobal(QPoint(0,height()+5))));

    QStringList results;
    //QString trimmed(text.trimmed());

    //if (!trimmed.isEmpty()) {
       // QString lookup(trimmed.toLower());
        QStringList::iterator i;
        for (i = d->dataSource.begin(); i != d->dataSource.end(); ++i) {
           //if (i->toLower().indexOf(lookup) != -1) {
                results.push_back(*i);
           // }
        }
   // }

    const int diff = results.length() - d->menuLayout->count();
    QFont font("Roboto", 12, QFont::Normal);

    if (diff > 0) {
        for (int c = 0; c < diff; c++) {
            QtMaterialFlatButton *item = new QtMaterialFlatButton;
            item->setFont(font);
            item->setTextAlignment(Qt::AlignLeft);
            item->setCornerRadius(0);
            item->setHaloVisible(false);
            item->setFixedHeight(50);
            item->setOverlayStyle(Material::GrayOverlay);
            item->setRole(Material::Default);
            //item->setBackgroundMode(Qt::OpaqueMode);
            d->menuLayout->addWidget(item);
            item->installEventFilter(this);
        }
    } else if (diff < 0) {
        for (int c = 0; c < -diff; c++) {
            QWidget *widget = d->menuLayout->itemAt(0)->widget();
            if (widget) {
                d->menuLayout->removeWidget(widget);
                delete widget;
            }
        }
    }

    QFontMetrics *fm = new QFontMetrics(font);
    d->maxWidth = 0;

    for (int i = 0; i < results.count(); ++i) {
        QWidget *widget = d->menuLayout->itemAt(i)->widget();
        QtMaterialFlatButton *item;
        if ((item = static_cast<QtMaterialFlatButton *>(widget))) {
            QString text = results.at(i);
            QRect rect = fm->boundingRect(text);
            d->maxWidth = qMax(d->maxWidth, rect.width());
            item->setText(text);
        }
    }

    if (!results.count()) {
        d->toggle = false;
        emit d->stateMachine->shouldClose();
    } else {
        d->toggle = true;
        emit d->stateMachine->shouldOpen();
    }

    d->menu->setFixedHeight(results.length()*50);
    d->menu->setFixedWidth(qMax(d->maxWidth + 24, width()));

    d->menu->update();
}

bool QtMaterialAutoComplete::QtMaterialAutoComplete::event(QEvent *event)
{
    Q_D(QtMaterialAutoComplete);

    if(event->type()==QEvent::FocusOut){
        d->toggle = false;
        emit d->stateMachine->shouldClose();
    }
    if(event->type()==QEvent::MouseButtonPress ){
        emit d->stateMachine->shouldClose();
    }

    switch (event->type())
    {
    case QEvent::Move:
    case QEvent::Resize: {
//        QWidget *widget = static_cast<QWidget *>(parent());
//        while (widget->parentWidget() != Q_NULLPTR) widget = widget->parentWidget();
//        d->menu->setParent(widget);
//        d->frame->setParent(widget);
        d->menu->move(d->menu->parentWidget()->mapFromGlobal(mapToGlobal(QPoint(0,height()+5)))); //- d->menu->parentWidget()->mapToGlobal(QPoint(0,0)));//widget->mapFromGlobal(global));
        break;
    }
//    case QEvent::ParentChange: {
//        QWidget *widget = static_cast<QWidget *>(parent());
//        while (widget->parentWidget() != Q_NULLPTR) widget = widget->parentWidget();
//        if (widget) {
//            d->menu->setParent(widget);
//            d->frame->setParent(widget);
//            qDebug()  << "widget" << widget;
//            qDebug() << "parent" <<d->menu->parentWidget();
//        }
//        break;
//    }
    default:
        break;
    }
    return QtMaterialFlatButton::event(event);
}

bool QtMaterialAutoComplete::eventFilter(QObject *watched, QEvent *event)
{
    Q_D(QtMaterialAutoComplete);

    if (d->frame == watched)
    {
        switch (event->type())
        {
        case QEvent::Paint: {
//            QWidget *widget = static_cast<QWidget *>(parent());
//            while (widget->parentWidget() != Q_NULLPTR) widget = widget->parentWidget();
//            d->menu->setParent(widget);
//            d->frame->setParent(widget);
            d->menu->move(d->menu->parentWidget()->mapFromGlobal(mapToGlobal(QPoint(0,height()+5))));
            QPainter painter(d->frame);
            painter.fillRect(d->frame->rect(), QtMaterialStyle::instance().themeColor("surface"));
            break;
        }
        default:
            break;
        }
    }
    else if (d->menu == watched)
    {
        switch (event->type())
        {
        case QEvent::Resize:
        case QEvent::Move: {
            d->frame->setGeometry(d->menu->geometry());
            break;
        }
        case QEvent::Show: {
            d->frame->show();
            d->menu->raise();
            break;
        }
        case QEvent::Hide: {
            d->frame->hide();
            break;
        }
        default:
            break;
        }
    }
    else
    {
        switch (event->type())
        {
        case QEvent::MouseButtonPress: {
            d->toggle = false;
            emit d->stateMachine->shouldFade();
            QtMaterialFlatButton *widget;
            if ((widget = static_cast<QtMaterialFlatButton *>(watched))) {
                QString text(widget->text());
                setText(text);
                emit itemSelected(text);
            }
            break;
        }
        default:
            break;
        }
    }
    return QtMaterialFlatButton::eventFilter(watched, event);
}
