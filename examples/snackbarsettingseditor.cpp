#include "snackbarsettingseditor.h"
#include <QVBoxLayout>
#include <QColorDialog>
#include <qtmaterialsnackbar.h>
#include <lib/qtmaterialstyle.h>
#include <qtmaterialframe.h>


SnackbarSettingsEditor::SnackbarSettingsEditor(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::SnackbarSettingsForm),
      m_snackbar(new QtMaterialSnackbar)
{
    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    QWidget *widget = new QWidget;
    layout->addWidget(widget);

    QWidget *canvas = new QtMaterialFrame;
//    QColor canvasColor = QtMaterialStyle::instance().themeColor("canvas");
//    canvas->setStyleSheet(QString("QWidget { background: ") + canvasColor.name() + "; }");
    layout->addWidget(canvas);

    ui->setupUi(widget);
    layout->setContentsMargins(20, 20, 20, 20);

    layout = new QVBoxLayout;
    canvas->setLayout(layout);
    canvas->setMaximumHeight(300);

    m_snackbar->setParent(this);

    setupForm();

    connect(ui->showSnackbarButton, SIGNAL(pressed()), this, SLOT(showSnackbar()));
}

SnackbarSettingsEditor::~SnackbarSettingsEditor()
{
    delete ui;
}

void SnackbarSettingsEditor::setupForm()
{
}

void SnackbarSettingsEditor::updateWidget()
{
}

void SnackbarSettingsEditor::showSnackbar()
{
    m_snackbar->addMessage(QString("Snack attack!"));
}
