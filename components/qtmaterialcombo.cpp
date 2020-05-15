#include "qtmaterialcombo.h"
#include "qtmaterialcombo_p.h"
#include "qtmaterialdropdown_internal.h"
#include <QtWidgets/QVBoxLayout>
#include <QDebug>
#include <QKeyEvent>
#include "qtmaterialflatbutton.h"
#include "qtmaterialtextfield.h"

/*!
 *  \class QtMaterialComboPrivate
 *  \internal
 */

/*!
 *  \internal
 */
QtMaterialComboPrivate::QtMaterialComboPrivate(QtMaterialCombo *q)
    : QtMaterialDropdownPrivate(q)
{
}

/*!
 *  \internal
 */
QtMaterialComboPrivate::~QtMaterialComboPrivate()
{
}

/*!
 *  \internal
 */
void QtMaterialComboPrivate::init()
{
    Q_Q(QtMaterialCombo);

    masterLayout = new QVBoxLayout;
    q->setLayout(masterLayout);
    masterButton = new QtMaterialTextField;
    masterButton->setLabel("State");
    masterButton->setReadOnly(true);
    masterLayout->addWidget(masterButton);
    masterButton->installEventFilter(q);

    masterLayout->setContentsMargins(0, 0, 0, 0);
    masterLayout->setSpacing(0);


    dropdownLayout  = new QVBoxLayout;
    dropdown->setLayout(dropdownLayout);

    dropdownLayout->setContentsMargins(0, 0, 0, 0);
    dropdownLayout->setSpacing(0);

//    QObject::connect(masterButton, &QtMaterialFlatButton::clicked, q,
//        [=](bool v){
//            Q_UNUSED(v)
//            if(this->frame->isVisible())
//                this->stateMachine->shouldClose();
//            else{
//                this->stateMachine->shouldOpen();
//            }
//        });

}

/*!
 *  \class QtMaterialCombo
 */

QtMaterialCombo::QtMaterialCombo(QWidget *parent)
    : QtMaterialDropdown(*new QtMaterialComboPrivate(this), parent)
{
    d_func()->init();
}


QtMaterialCombo::~QtMaterialCombo()
{
}

bool QtMaterialCombo::eventFilter(QObject *watched, QEvent *event)
{
    Q_D(QtMaterialCombo);
    if(d->masterButton == watched){
        switch (event->type())
        {
        case QEvent::KeyPress:{
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if(keyEvent->key() == Qt::Key_Space){
                toggleDeffered();
            }
            break;
        }
        case QEvent::MouseButtonPress:
            toggleDeffered();
            break;
        default:;
        }
    }
    return QtMaterialDropdown::eventFilter(watched, event);
}

void QtMaterialCombo::setItemsTexts(const QStringList &data)
{
    Q_D(QtMaterialCombo);

    d->dataSource = data;

    const int diff = data.length() - d->dropdownLayout->count();

    if (diff > 0) {
        for (int c = 0; c < diff; c++) {
            QtMaterialFlatButton *item = new QtMaterialFlatButton;
            item->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            item->setTextAlignment(Qt::AlignLeft);
            item->setCornerRadius(0);
            item->setHaloVisible(true);
            item->setOverlayStyle(Material::TintedOverlay);
            item->setRole(Material::Primary);
            item->setTextual(true);
            //item->setBackgroundMode(Qt::OpaqueMode);
            d->dropdownLayout->addWidget(item);
            QObject::connect(item, &QtMaterialFlatButton::clicked, this, &QtMaterialCombo::itemSelected);
            //item->installEventFilter(this);
        }
    } else if (diff < 0) {
        for (int c = 0; c < -diff; c++) {
            QWidget *widget = d->dropdownLayout->itemAt(0)->widget();
            if (widget) {
                d->dropdownLayout->removeWidget(widget);
                delete widget;
            }
        }
    }

    for (int i = 0; i < data.count(); ++i) {
        QWidget *widget = d->dropdownLayout->itemAt(i)->widget();
        QtMaterialFlatButton *item;
        if ((item = static_cast<QtMaterialFlatButton *>(widget))) {
            QFontMetrics fm(item->mainFont());
            QString text = data.at(i);
            QRect rect = fm.boundingRect(text);
            item->setText(text);
        }
    }

//    if (!data.count()) {
//        emit d->stateMachine->shouldClose();
//    } else {
//        emit d->stateMachine->shouldOpen();
//    }

//    d->dropdown->setFixedHeight(data.length()*50);
//    d->dropdown->setFixedWidth(width());

    d->dropdown->update();
}

void QtMaterialCombo::itemSelected(bool dummy){
    Q_D(QtMaterialCombo);
    Q_UNUSED(dummy)

    QtMaterialFlatButton* item;
    if (( item = static_cast<QtMaterialFlatButton *>(QObject::sender()))){
        qDebug() << "selected:" << d->dropdownLayout->indexOf(item) << item->text();
        d->masterButton->setText(item->text());
        emit selectedText(item->text());
        emit selectedIndex(d->dropdownLayout->indexOf(item));
        d->stateMachine->shouldFade();
        d->masterButton->setFocus();
    }
    else{
        qWarning() << "selection error";
    }

}

QSize QtMaterialCombo::sizeHint() const{
    Q_D(const QtMaterialCombo);

    QSize masterSize = d->masterButton->sizeHint();
    QSize dropdownSize = d->dropdown->sizeHint();

    return QSize(qMax(masterSize.width(), dropdownSize.width()), masterSize.height());
}

QtMaterialCombo::QtMaterialCombo(QtMaterialComboPrivate &d, QWidget *parent)
    : QtMaterialDropdown(d, parent)
{
    d_func()->init();
}

