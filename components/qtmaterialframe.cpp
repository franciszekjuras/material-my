#include "qtmaterialframe.h"
#include <QPainter>
#include "lib/qtmaterialstyle.h"

QtMaterialFrame::QtMaterialFrame(QWidget *parent) : QWidget(parent){
    _cornerRadius = 0.;
    _useThemeColors = true;
}

void QtMaterialFrame::setUseThemeColors(bool value){
    _useThemeColors = true;
}
bool QtMaterialFrame::useThemeColors() const{
    return _useThemeColors;
}

void QtMaterialFrame::setBackgroundColor(const QColor &color){
    _backgroundColor = color;
    _useThemeColors = false;
}

QColor QtMaterialFrame::backgroundColor() const{
    if (_useThemeColors || !_backgroundColor.isValid())
    {
        return QtMaterialStyle::instance().themeColor("surface");
    }
    return _backgroundColor;
}

void QtMaterialFrame::setCornerRadius(qreal radius){
    _cornerRadius = qMax(0.,radius);
}

qreal QtMaterialFrame::cornerRadius() const{
    return  _cornerRadius;
}

void QtMaterialFrame::paintEvent(QPaintEvent *event){
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QPainterPath path;
    path.addRoundedRect(rect(), _cornerRadius, _cornerRadius);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(backgroundColor());
    painter.setOpacity(1.);
    painter.setBrush(brush);
    painter.setPen(Qt::NoPen);

    painter.fillPath(path, brush);
    painter.drawPath(path);
}
