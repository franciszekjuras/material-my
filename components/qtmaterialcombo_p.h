#ifndef QTMATERIALCOMBO_P_H
#define QTMATERIALCOMBO_P_H

#include "qtmaterialdropdown_p.h"

class QtMaterialCombo;
class QtMaterialTextField;
class QVBoxLayout;

class QtMaterialComboPrivate : public QtMaterialDropdownPrivate
{
    Q_DISABLE_COPY(QtMaterialComboPrivate)
    Q_DECLARE_PUBLIC(QtMaterialCombo)

public:
    QtMaterialComboPrivate(QtMaterialCombo *q);
    ~QtMaterialComboPrivate();

    void init();

    QtMaterialTextField    *masterButton;
    QVBoxLayout            *masterLayout;

};

#endif // QTMATERIALCOMBO_P_H
