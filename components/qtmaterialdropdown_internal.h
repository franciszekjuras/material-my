#ifndef QTMATERIALDROPDOWNSTATEMACHINE_H
#define QTMATERIALDROPDOWNSTATEMACHINE_H

#include <QStateMachine>
#include "qtmaterialdropdown.h"

class QtMaterialDropdownStateMachine : public QStateMachine
{
    Q_OBJECT

public:
    explicit QtMaterialDropdownStateMachine(QWidget *dropdown);
    ~QtMaterialDropdownStateMachine();

signals:
    void shouldOpen();
    void shouldClose();
    void shouldFade();

private:
    Q_DISABLE_COPY(QtMaterialDropdownStateMachine)

    QWidget *const m_dropdown;
    QState  *const m_closedState;
    QState  *const m_openState;
    QState  *const m_closingState;
};

#endif // QTMATERIALDROPDOWNSTATEMACHINE_H
