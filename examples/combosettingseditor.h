#ifndef COMBOSETTINGSEDITOR_H
#define COMBOSETTINGSEDITOR_H

#include <QWidget>
//#include "ui_autocompletesettingsform.h"

#include "lib/qtmaterialoverlaywidget.h"

class QtMaterialCombo;

class ComboSettingsEditor : public QWidget
{
    Q_OBJECT

public:
    explicit ComboSettingsEditor(QWidget *parent = 0);
    ~ComboSettingsEditor();

private:
    //Ui::AutoCompleteSettingsForm *const ui;
    QtMaterialCombo       *const m_combo;
};

#endif // COMBOSETTINGSEDITOR_H
