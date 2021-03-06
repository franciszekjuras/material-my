#include "qtmaterialtextfield.h"
#include "qtmaterialtextfield_p.h"
#include <QtWidgets/QApplication>
#include <QPainter>
#include "qtmaterialtextfield_internal.h"
#include "lib/qtmaterialstyle.h"
#include <QDebug>

/*!
 *  \class QtMaterialTextFieldPrivate
 *  \internal
 */

QtMaterialTextFieldPrivate::QtMaterialTextFieldPrivate(QtMaterialTextField *q)
    : q_ptr(q)
{
}

QtMaterialTextFieldPrivate::~QtMaterialTextFieldPrivate()
{
}

void QtMaterialTextFieldPrivate::init()
{
    Q_Q(QtMaterialTextField);

    stateMachine   = new QtMaterialTextFieldStateMachine(q);
    label          = nullptr;
    labelFontSize  = 9.5;
    showLabel      = false;
    showInputLine  = true;
    useThemeColors = true;
    useThemeFont   = true;

    q->setFrame(false);
    q->setStyle(&QtMaterialStyle::instance());
    q->setAttribute(Qt::WA_Hover);
    q->setMouseTracking(true);
    q->setTextMargins(0, 2, 0, 4);

    q->setupTheme();

    stateMachine->start();

    QCoreApplication::processEvents();
}

/*!
 *  \class QtMaterialTextField
 */

QtMaterialTextField::QtMaterialTextField(QWidget *parent)
    : QLineEdit(parent),
      d_ptr(new QtMaterialTextFieldPrivate(this))
{
    d_func()->init();
}

QtMaterialTextField::~QtMaterialTextField()
{
}

void QtMaterialTextField::setUseThemeColors(bool value)
{
    Q_D(QtMaterialTextField);

    if (d->useThemeColors == value) {
        return;
    }

    d->useThemeColors = value;
    d->stateMachine->setupProperties();
}

bool QtMaterialTextField::useThemeColors() const
{
    Q_D(const QtMaterialTextField);

    return d->useThemeColors;
}

void QtMaterialTextField::setUseThemeFont(bool value)
{
    Q_D(QtMaterialTextField);

    if (d->useThemeFont == value) {
        return;
    }
    d->useThemeFont = value;
    setupTheme();
}

bool QtMaterialTextField::useThemeFont() const
{
    Q_D(const QtMaterialTextField);

    return d->useThemeFont;
}


void QtMaterialTextField::setMainFont(const QFont &font){
    Q_D(QtMaterialTextField);

    d->mainFont = font;
    d->useThemeFont = false;
    updateTypeset();
}

void QtMaterialTextField::setLabelFont(const QFont &font){
    Q_D(QtMaterialTextField);

    d->labelFont = font;
    d->useThemeFont = false;
    updateTypeset();
}

void QtMaterialTextField::setShowLabel(bool value)
{
    Q_D(QtMaterialTextField);

    if (d->showLabel == value) {
        return;
    }

    d->showLabel = value;

    if (!d->label && value) {
        d->label = new QtMaterialTextFieldLabel(this);
        d->stateMachine->setLabel(d->label);
    }

    updateTypeset();

    if (value) {
        int labelHeight = d->label->fontMetrics().height();
        setContentsMargins(10, labelHeight+5, 10, 5);
    } else {
        setContentsMargins(10, 5, 10, 5);
    }
}

bool QtMaterialTextField::hasLabel() const
{
    Q_D(const QtMaterialTextField);

    return d->showLabel;
}

//void QtMaterialTextField::setLabelFontSize(qreal size)
//{
//    Q_D(QtMaterialTextField);

//    d->labelFontSize = size;

//    if (d->label)
//    {
//        QFont font(d->label->font());
//        font.setPointSizeF(size);
//        d->label->setFont(font);
//        d->label->update();
//    }
//}


void QtMaterialTextField::setLabel(const QString &label)
{
    Q_D(QtMaterialTextField);

    d->labelString = label;
    setShowLabel(true);
    d->label->update();
}

QString QtMaterialTextField::label() const
{
    Q_D(const QtMaterialTextField);

    return d->labelString;
}

qreal QtMaterialTextField::labelFontSize() const
{
    Q_D(const QtMaterialTextField);

    return d->labelFont.pointSizeF();
}

void QtMaterialTextField::setTextColor(const QColor &color)
{
    Q_D(QtMaterialTextField);

    d->textColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->stateMachine->setupProperties();
}

QColor QtMaterialTextField::textColor() const
{
    Q_D(const QtMaterialTextField);

    if (d->useThemeColors || !d->textColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("text");
    } else {
        return d->textColor;
    }
}

void QtMaterialTextField::setBackgroundColor(const QColor &color)
{
    Q_D(QtMaterialTextField);

    d->backgroundColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->stateMachine->setupProperties();
}

QColor QtMaterialTextField::backgroundColor() const
{
    Q_D(const QtMaterialTextField);

    if (d->useThemeColors || !d->backgroundColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("flatElevation");
    } else {
        return d->backgroundColor;
    }
}

void QtMaterialTextField::setLabelColor(const QColor &color)
{
    Q_D(QtMaterialTextField);

    d->labelColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->stateMachine->setupProperties();
}

QColor QtMaterialTextField::labelColor() const
{
    Q_D(const QtMaterialTextField);

    if (d->useThemeColors || !d->labelColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("primary3");
    } else {
        return d->labelColor;
    }
}

void QtMaterialTextField::setInkColor(const QColor &color)
{
    Q_D(QtMaterialTextField);

    d->inkColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->stateMachine->setupProperties();
}

QColor QtMaterialTextField::inkColor() const
{
    Q_D(const QtMaterialTextField);

    if (d->useThemeColors || !d->inkColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("primary1");
    } else {
        return d->inkColor;
    }
}

void QtMaterialTextField::setInputLineColor(const QColor &color)
{
    Q_D(QtMaterialTextField);

    d->inputLineColor = color;

    MATERIAL_DISABLE_THEME_COLORS
    d->stateMachine->setupProperties();
}

QColor QtMaterialTextField::inputLineColor() const
{
    Q_D(const QtMaterialTextField);

    if (d->useThemeColors || !d->inputLineColor.isValid()) {
        return QtMaterialStyle::instance().themeColor("border");
    } else {
        return d->inputLineColor;
    }
}

void QtMaterialTextField::setShowInputLine(bool value)
{
    Q_D(QtMaterialTextField);

    if (d->showInputLine == value) {
        return;
    }

    d->showInputLine = value;
    update();
}

bool QtMaterialTextField::hasInputLine() const
{
    Q_D(const QtMaterialTextField);

    return d->showInputLine;
}

void QtMaterialTextField::setHighlightBuddy(QWidget *buddy){
    Q_D(QtMaterialTextField);
    d->stateMachine->setHighlightBuddy(buddy);
}

QtMaterialTextField::QtMaterialTextField(QtMaterialTextFieldPrivate &d, QWidget *parent)
    : QLineEdit(parent),
      d_ptr(&d)
{
    d_func()->init();
}

void QtMaterialTextField::checkThemeChange(){
    Q_D(QtMaterialTextField);

    if(QtMaterialStyle::instance().themeIdx() == d->themeIdx)
        return;
    d->themeIdx = QtMaterialStyle::instance().themeIdx();

    setupTheme();
}

void QtMaterialTextField::setupTheme(){
    Q_D(QtMaterialTextField);

    if(useThemeFont()){
        d->mainFont = QtMaterialStyle::instance().themeFont("Subtitle1");
        d->labelFont = QtMaterialStyle::instance().themeFont("Caption");
    }

    updateTypeset();

    d->stateMachine->setupProperties();
}

void QtMaterialTextField::updateTypeset(){
    Q_D(QtMaterialTextField);

    this->setFont(d->mainFont);
    if(d->label)
        d->label->setFont(d->labelFont);
}

/*!
 *  \reimp
 */
bool QtMaterialTextField::event(QEvent *event)
{
    Q_D(QtMaterialTextField);

    switch (event->type())
    {
    case QEvent::Resize:
    case QEvent::Move: {
        if (d->label) {
            d->label->setGeometry(rect());//.translated(10,-3));
        }
    }
    default:
        break;
    }
    return QLineEdit::event(event);
}

/*!
 *  \reimp
 */
void QtMaterialTextField::paintEvent(QPaintEvent *event)
{
    Q_D(QtMaterialTextField);

    checkThemeChange();

    if(d->lastTextColor != textColor()){
        d->lastTextColor = textColor();
        setStyleSheet(QString("QLineEdit { background-color: #00000000; color:%1}").arg(textColor().name()));
        //rgba(0,0,0,0)
    }

    {
        QPainter painter(this);

        QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(backgroundColor());
        painter.setBrush(brush);
        painter.setPen(Qt::NoPen);
        painter.drawRect(rect());
    }

    QLineEdit::paintEvent(event);

    const qreal progress = d->stateMachine->progress();

//    if (text().isEmpty() && progress < 1)
//    {
//        painter.setOpacity(1-progress);
//        painter.fillRect(rect(), parentWidget()->palette().color(backgroundRole()));
//    }

    QPainter painter(this);
    QBrush brush;

    const int y = height()-1;
    const int wd = width()-5;

    if (d->showInputLine)
    {
        QPen pen;
        pen.setWidth(1);
        pen.setColor(inputLineColor());

        if (!isEnabled()) 
            pen.setStyle(Qt::DashLine);

        painter.setPen(pen);
        //painter.setOpacity(1.);
        painter.drawLine(QLineF(2.5, y, wd, y));

        //QBrush brush;
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(inkColor());

        if (progress > 0)
        {
            painter.setPen(Qt::NoPen);
            painter.setBrush(brush);
            const int w = (1-progress)*static_cast<qreal>(wd/2);
            painter.drawRect(w+2.5, height()-2, wd-w*2, 2);
        }
    }
}
