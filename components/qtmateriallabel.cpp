#include "qtmateriallabel.h"
#include <QPainter>
#include <QPalette>
#include "lib/qtmaterialstyle.h"

QtMaterialLabel::QtMaterialLabel(const QString &text, QWidget *parent) : QLabel(text, parent){
    _useThemeColors = true;
    _useThemeFont = true;
    _themeFont = "Subtitle1";
    _themeColor = "text";
}

void QtMaterialLabel::setUseThemeColors(bool value){
    if (_useThemeColors == value) {
        return;
    }
    _useThemeColors = value;
    setupTheme();
}
bool QtMaterialLabel::useThemeColors() const{
    return _useThemeColors;
}

void QtMaterialLabel::setUseThemeFont(bool value)
{
    if (_useThemeFont == value) {
        return;
    }
    _useThemeFont = value;
    setupTheme();
}

bool QtMaterialLabel::useThemeFont() const
{
    return _useThemeFont;
}

void QtMaterialLabel::setThemeFont(const QString &themeFont)
{
    _themeFont = themeFont;
    setupTheme();
}

void QtMaterialLabel::setThemeColor(const QString &themeColor)
{
    _themeColor = themeColor;
    setupTheme();
}


void QtMaterialLabel::setMainFont(const QFont &font)
{
    _mainFont = font;
    _useThemeFont = false;
    setupTheme();
}


void QtMaterialLabel::setTextColor(const QColor &color)
{
    _textColor = color;
    _useThemeColors = false;
    setupTheme();
}


void QtMaterialLabel::checkThemeChange()
{
    if(QtMaterialStyle::instance().themeIdx() == _themeIdx)
        return;
    _themeIdx = QtMaterialStyle::instance().themeIdx();

    setupTheme();
}

void QtMaterialLabel::setupTheme()
{
    if(useThemeFont()){
        _mainFont = QtMaterialStyle::instance().themeFont(_themeFont);
    }
    if(useThemeColors()){
        _textColor = QtMaterialStyle::instance().themeColor(_themeColor);
    }

    updateTypeset();
    updateColorset();
}

void QtMaterialLabel::updateTypeset()
{
    this->setFont(_mainFont);
    update();
}

void QtMaterialLabel::updateColorset()
{
    QPalette pal;
    pal.setColor(this->foregroundRole(), _textColor);
    pal.setColor(this->backgroundRole(), QColor(0,0,0,0));
    this->setPalette(pal);
    update();
}

void QtMaterialLabel::paintEvent(QPaintEvent *event){
    checkThemeChange();
    QLabel::paintEvent(event);
}
