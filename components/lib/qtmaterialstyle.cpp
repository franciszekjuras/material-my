#include "lib/qtmaterialstyle.h"
#include "lib/qtmaterialstyle_p.h"
#include <QFontDatabase>
#include "lib/qtmaterialtheme.h"

/*!
 *  \class QtMaterialStylePrivate
 *  \internal
 */

int QtMaterialStylePrivate::themeIdx = 0;

QtMaterialStylePrivate::QtMaterialStylePrivate(QtMaterialStyle *q)
    : q_ptr(q)
{
}

QtMaterialStylePrivate::~QtMaterialStylePrivate()
{
}

void QtMaterialStylePrivate::init()
{
    Q_Q(QtMaterialStyle);

    QFontDatabase::addApplicationFont(":/fonts/roboto_regular");
    QFontDatabase::addApplicationFont(":/fonts/roboto_medium");
    QFontDatabase::addApplicationFont(":/fonts/roboto_bold");

    q->setTheme(new QtMaterialTheme);
}

/*!
 *  \class QtMaterialStyle
 *  \internal
 */



void QtMaterialStyle::setTheme(QtMaterialTheme *theme)
{
    Q_D(QtMaterialStyle);

    d->theme = theme;
    d->themeIdx += 1;
    theme->setParent(this);
}

int QtMaterialStyle::themeIdx()
{
    Q_D(QtMaterialStyle);

    return d->themeIdx;
}

QFont QtMaterialStyle::themeFont(const QString &key) const
{
    Q_D(const QtMaterialStyle);

    Q_ASSERT(d->theme);

    return d->theme->getFont(key);
}

QColor QtMaterialStyle::themeColor(const QString &key) const
{
    Q_D(const QtMaterialStyle);

    Q_ASSERT(d->theme);

    return d->theme->getColor(key);
}

QColor QtMaterialStyle::themeColor(const QString &key, double alpha_mult) const
{
    Q_D(const QtMaterialStyle);

    Q_ASSERT(d->theme);

    return d->theme->getColor(key, alpha_mult);
}

QtMaterialStyle::QtMaterialStyle()
    : QCommonStyle(),
      d_ptr(new QtMaterialStylePrivate(this))
{
    d_func()->init();
}

QtMaterialStyle::~QtMaterialStyle()
{
}
