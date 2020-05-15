#include "combosettingseditor.h"
#include <QVBoxLayout>
#include <QDebug>
#include <qtmaterialcombo.h>
#include <qtmaterialflatbutton.h>
#include <lib/qtmaterialstyle.h>
#include <qtmaterialframe.h>

ComboSettingsEditor::ComboSettingsEditor(QWidget *parent)
    : QWidget(parent),
      //ui(new Ui::AutoCompleteSettingsForm),
      m_combo(new QtMaterialCombo)
{

    QVBoxLayout *mainlayout = new QVBoxLayout;
    setLayout(mainlayout);

    QWidget *frame = new QtMaterialFrame;
    mainlayout->addWidget(frame);

    frame->setMinimumHeight(300); //

    //ui->setupUi(widget);
    mainlayout->setContentsMargins(20, 20, 20, 20);

    QVBoxLayout *layout = new QVBoxLayout;
    frame->setLayout(layout);

    m_combo->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

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

    m_combo->setItemsTexts(states);

    states.append("Lubię placki");
    m_combo->setItemsTexts(states);

//    QtMaterialFrame *frm = new QtMaterialFrame;

//    layout->addWidget(frm);

//    QVBoxLayout *frmlayout = new QVBoxLayout;
//    frm->setLayout(frmlayout);

    layout->addWidget(m_combo);

    for(int i = 0; i < 10; ++i){
        layout->addWidget(new QtMaterialFlatButton("Sfag Yolo"));
    }

    layout->addSpacing(600);
    //layout->setAlignment(m_combo, Qt::AlignCenter);

}

ComboSettingsEditor::~ComboSettingsEditor()
{
    //delete ui;
}
