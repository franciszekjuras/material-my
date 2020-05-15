#ifndef QTMATERIALDROPDOWN_P_H
#define QTMATERIALDROPDOWN_P_H

#include <QStringList>

class QWidget;
class QVBoxLayout;
class QtMaterialDropdownOverlay;
class QtMaterialDropdownStateMachine;
class QtMaterialDropdown;

class QtMaterialDropdownPrivate
{
    Q_DISABLE_COPY(QtMaterialDropdownPrivate)
    Q_DECLARE_PUBLIC(QtMaterialDropdown)

public:
    QtMaterialDropdownPrivate(QtMaterialDropdown *q);
    virtual ~QtMaterialDropdownPrivate();

    void init();

    QtMaterialDropdown                *const q_ptr;
    QWidget                            *dropdown;
    QWidget                            *frame;
    QtMaterialDropdownStateMachine *stateMachine;
    QVBoxLayout                        *dropdownLayout;
    QStringList                         dataSource;
    int                                 maxWidth;
};

#endif // QTMATERIALDROPDOWN_P_H
