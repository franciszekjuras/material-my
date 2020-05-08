#ifndef QTMATERIALAUTOCOMPLETE_P_H
#define QTMATERIALAUTOCOMPLETE_P_H

#include "qtmaterialflatbutton_p.h"

class QWidget;
class QVBoxLayout;
class QtMaterialAutoCompleteOverlay;
class QtMaterialAutoCompleteStateMachine;

class QtMaterialAutoCompletePrivate : public QtMaterialFlatButtonPrivate
{
    Q_DISABLE_COPY(QtMaterialAutoCompletePrivate)
    Q_DECLARE_PUBLIC(QtMaterialAutoComplete)

public:
    QtMaterialAutoCompletePrivate(QtMaterialAutoComplete *q);
    virtual ~QtMaterialAutoCompletePrivate();

    void init();

    QWidget                            *menu;
    QWidget                            *frame;
    QtMaterialAutoCompleteStateMachine *stateMachine;
    QVBoxLayout                        *menuLayout;
    QStringList                         dataSource;
    int                                 maxWidth;
    bool                                toggle;
};

#endif // QTMATERIALAUTOCOMPLETE_P_H
