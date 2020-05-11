#include "autocompletesettingseditor.h"
#include <QVBoxLayout>
#include <QDebug>
#include <qtmaterialautocomplete.h>
#include <qtmaterialflatbutton.h>
#include <lib/qtmaterialstyle.h>
#include <qtmaterialframe.h>

AutoCompleteSettingsEditor::AutoCompleteSettingsEditor(QWidget *parent)
    : QWidget(parent),
      //ui(new Ui::AutoCompleteSettingsForm),
      m_autocomplete(new QtMaterialAutoComplete)
{

    QVBoxLayout *layout = new QVBoxLayout;
    setLayout(layout);

    QWidget *widget = new QWidget;
    layout->addWidget(widget);

    QWidget *canvas = new QWidget;
    QColor canvasColor = QtMaterialStyle::instance().themeColor("canvas");
    canvas->setStyleSheet(QString("QWidget { background: ") + canvasColor.name() + "; }");
    layout->addWidget(canvas);

    canvas->setMinimumHeight(300); //

    //ui->setupUi(widget);
    layout->setContentsMargins(20, 20, 20, 20);

    layout = new QVBoxLayout;
    canvas->setLayout(layout);

    m_autocomplete->setFixedWidth(300);
    m_autocomplete->setUseThemeColors(true);

    QStringList states =
      {  "Arizona"
        , "Arkansas"
        , "California"
        ,"Kotałson wchodzi na sucho"
        , "Alaska"
//         , "Arkdfdfansas"
//         , "Calidffornia"
//         ,"Alabfdama"
//         , "Aladfska"
//      , "American Samoa"
//         , "Arkdfdddfansas"
//         , "Calddidffornia"
//         ,"Aladbfdama"
//         , "Aladdfska"
//         , "Arkdfsddfansas"
//         , "Cddlidffornia"
//         ,"Alfdfabfdama"
//         , "Aaladfska"
//      , "Ameridcan Samoa"
      , "American Samoa"
    };

    m_autocomplete->setDataSource(states);

//    QtMaterialFrame *frm = new QtMaterialFrame;

//    layout->addWidget(frm);

//    QVBoxLayout *frmlayout = new QVBoxLayout;
//    frm->setLayout(frmlayout);

    layout->addWidget(m_autocomplete);

    for(int i = 0; i < 10; ++i){
        layout->addWidget(new QtMaterialFlatButton("Sfag Yolo"));
    }

    layout->addSpacing(600);
    layout->setAlignment(m_autocomplete, Qt::AlignCenter);

    setupForm();
}

AutoCompleteSettingsEditor::~AutoCompleteSettingsEditor()
{
    //delete ui;
}

void AutoCompleteSettingsEditor::setupForm()
{
}

void AutoCompleteSettingsEditor::updateWidget()
{
}

void AutoCompleteSettingsEditor::selectColor()
{
}
