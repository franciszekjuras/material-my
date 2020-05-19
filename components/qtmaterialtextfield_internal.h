#ifndef QTMATERIALTEXTFIELD_INTERNAL_H
#define QTMATERIALTEXTFIELD_INTERNAL_H

#include <QStateMachine>
#include <QtWidgets/QWidget>
#include <QDebug>
#include "qtmaterialtextfield.h"

class QPropertyAnimation;
class QtMaterialTextFieldLabel;
class QEventTransition;

class QtMaterialTextFieldStateMachine : public QStateMachine
{
    Q_OBJECT

    Q_PROPERTY(qreal progress WRITE setProgress READ progress)

public:
    QtMaterialTextFieldStateMachine(QtMaterialTextField *parent);
    ~QtMaterialTextFieldStateMachine();

    void setLabel(QtMaterialTextFieldLabel *label);

    inline void setProgress(qreal progress);
    inline qreal progress() const;

    void setHighlightBuddy(QWidget *buddy);

public slots:
    void setupProperties();

private:
    Q_DISABLE_COPY(QtMaterialTextFieldStateMachine)

    QtMaterialTextField *const m_textField;
    QState              *const m_normalState;
    QState              *const m_focusedState;
    QtMaterialTextFieldLabel  *m_label;
    QPropertyAnimation        *m_offsetAnimation;
    QPropertyAnimation        *m_colorAnimation;
    QPropertyAnimation        *m_fontSizeAnimation;
    qreal                      m_progress;

    QEventTransition          *m_buddyTransitionIn;
    QEventTransition          *m_buddyTransitionOut;
};

inline void QtMaterialTextFieldStateMachine::setProgress(qreal progress)
{
    m_progress = progress;
    m_textField->update();
}

inline qreal QtMaterialTextFieldStateMachine::progress() const
{
    return m_progress;
}

class QtMaterialTextFieldLabel : public QWidget
{
    Q_OBJECT

    Q_PROPERTY(qreal scale WRITE setScale READ scale)
    Q_PROPERTY(qreal fontSize WRITE setFontSize READ fontSize)
    Q_PROPERTY(QPointF offset WRITE setOffset READ offset)
    Q_PROPERTY(QColor color WRITE setColor READ color)

public:
    QtMaterialTextFieldLabel(QtMaterialTextField *parent);
    ~QtMaterialTextFieldLabel();

    inline void setScale(qreal scale);
    inline qreal scale() const;

    inline void setFontSize(qreal size);
    inline qreal fontSize() const;

    inline void setOffset(const QPointF &pos);
    inline QPointF offset() const;

    inline void setColor(const QColor &color);
    inline QColor color() const;

protected:
    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;

private:
    Q_DISABLE_COPY(QtMaterialTextFieldLabel)

    QtMaterialTextField *const m_textField;
    qreal                      m_scale;
    qreal                      m_posX;
    qreal                      m_posY;
    QColor                     m_color;
};

inline void QtMaterialTextFieldLabel::setScale(qreal scale)
{
    m_scale = scale;
    update();
}

inline qreal QtMaterialTextFieldLabel::scale() const
{
    return m_scale;
}

inline void QtMaterialTextFieldLabel::setFontSize(qreal size)
{
    QFont f = font();
    f.setPointSizeF(size);
    setFont(f);
    update();
}

inline qreal QtMaterialTextFieldLabel::fontSize() const
{
    return font().pointSizeF();
}


inline void QtMaterialTextFieldLabel::setOffset(const QPointF &pos)
{
    m_posX = pos.x();
    m_posY = pos.y();
    update();
}

inline QPointF QtMaterialTextFieldLabel::offset() const
{
    return QPointF(m_posX, m_posY);
}

inline void QtMaterialTextFieldLabel::setColor(const QColor &color)
{
    m_color = color;
    update();
}

inline QColor QtMaterialTextFieldLabel::color() const
{
    return m_color;
}

#endif // QTMATERIALTEXTFIELD_INTERNAL_H
