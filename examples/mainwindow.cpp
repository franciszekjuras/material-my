#include "mainwindow.h"
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QStackedLayout>
#include <QtWidgets/QListWidget>
#include "avatarsettingseditor.h"
#include "badgesettingseditor.h"
#include "checkboxsettingseditor.h"
#include "fabsettingseditor.h"
#include "raisedbuttonsettingseditor.h"
#include "flatbuttonsettingseditor.h"
#include "iconbuttonsettingseditor.h"
#include "progresssettingseditor.h"
#include "circularprogresssettingseditor.h"
#include "slidersettingseditor.h"
#include "radiobuttonsettingseditor.h"
#include "togglesettingseditor.h"
#include "textfieldsettingseditor.h"
#include "tabssettingseditor.h"
#include "snackbarsettingseditor.h"
#include "dialogsettingseditor.h"
#include "drawersettingseditor.h"
#include "scrollbarsettingseditor.h"
#include "appbarsettingseditor.h"
#include "autocompletesettingseditor.h"
#include "menusettingseditor.h"
#include "combosettingseditor.h"
#include "lib/qtmaterialtheme.h"
#include "lib/qtmaterialstyle.h"

#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QtMaterialTheme* theme = new QtMaterialTheme();
    theme->setColor("primary1", Material::cyan300);
    theme->setColor("primary2", Material::cyan700);
    theme->setColor("primary3", Material::grey400);
    theme->setColor("accent1", Material::pinkA200);
    theme->setColor("accent2", Material::grey900);
    theme->setColor("accent3", Material::grey500);
    theme->setColor("text", Material::grey50);
    theme->setColor("alternateText", Material::grey900);
    theme->setColor("canvas", Material::grey900);
    theme->setColor("surface", Material::grey800);
    theme->setColor("flatElevation", Material::white, 0.1);
    theme->setColor("border", Material::grey700);
    theme->setColor("thumb", Material::grey300);
    theme->setColor("raisedElevation", Material::white, 0.13);
    theme->setColor("surfaceOverlay", Material::white, 0.08);
    theme->setColor("primaryOverlay", Material::white, 0.2);
    theme->setColor("disabled", Material::grey600);
    theme->setColor("disabled2", Material::grey700);
    theme->setColor("disabled3", Material::grey800);

    QtMaterialStyle::instance().setTheme(theme);

    QWidget *widget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout;

    widget->setLayout(layout);

    QStackedLayout *stack = new QStackedLayout;
    QListWidget *list = new QListWidget;

    layout->addWidget(list);
    layout->addLayout(stack);

    layout->setStretch(1, 2);

    setCentralWidget(widget);

    AvatarSettingsEditor *avatar = new AvatarSettingsEditor;
    BadgeSettingsEditor *badge = new BadgeSettingsEditor;
    CheckBoxSettingsEditor *checkbox = new CheckBoxSettingsEditor;
    FloatingActionButtonSettingsEditor *fab = new FloatingActionButtonSettingsEditor;
    RaisedButtonSettingsEditor *raisedButton = new RaisedButtonSettingsEditor;
    FlatButtonSettingsEditor *flatButton = new FlatButtonSettingsEditor;
    IconButtonSettingsEditor *iconButton = new IconButtonSettingsEditor;
    ProgressSettingsEditor *progress = new ProgressSettingsEditor;
    CircularProgressSettingsEditor *circularProgress = new CircularProgressSettingsEditor;
    SliderSettingsEditor *slider = new SliderSettingsEditor;
    RadioButtonSettingsEditor *radioButton = new RadioButtonSettingsEditor;
    ToggleSettingsEditor *toggle = new ToggleSettingsEditor;
    TextFieldSettingsEditor *textField = new TextFieldSettingsEditor;
    TabsSettingsEditor *tabs = new TabsSettingsEditor;
    SnackbarSettingsEditor *snackbar = new SnackbarSettingsEditor;
    DialogSettingsEditor *dialog = new DialogSettingsEditor;
    DrawerSettingsEditor *drawer = new DrawerSettingsEditor;
    ScrollBarSettingsEditor *scrollBar = new ScrollBarSettingsEditor;
    AppBarSettingsEditor *appBar = new AppBarSettingsEditor;
    AutoCompleteSettingsEditor *autocomplete = new AutoCompleteSettingsEditor;
    MenuSettingsEditor *menu = new MenuSettingsEditor;
    ComboSettingsEditor *combo = new ComboSettingsEditor;

    stack->addWidget(appBar);
    stack->addWidget(autocomplete);
    stack->addWidget(avatar);
    stack->addWidget(badge);
    stack->addWidget(checkbox);
    stack->addWidget(circularProgress);
    stack->addWidget(combo);
    stack->addWidget(dialog);
    stack->addWidget(drawer);
    stack->addWidget(fab);
    stack->addWidget(flatButton);
    stack->addWidget(iconButton);
    stack->addWidget(menu);
    stack->addWidget(progress);
    stack->addWidget(radioButton);
    stack->addWidget(raisedButton);
    stack->addWidget(scrollBar);
    stack->addWidget(slider);
    stack->addWidget(snackbar);
    stack->addWidget(tabs);
    stack->addWidget(textField);
    stack->addWidget(toggle);

    list->addItem("App Bar");
    list->addItem("Auto Complete");
    list->addItem("Avatar");
    list->addItem("Badge");
    list->addItem("Checkbox");
    list->addItem("Circular Progress");
    list->addItem("Combo");
    list->addItem("Dialog");
    list->addItem("Drawer");
    list->addItem("Floating Action Button");
    list->addItem("Flat Button");
    list->addItem("Icon Button");
    list->addItem("Menu");
    list->addItem("Progress");
    list->addItem("Radio Button");
    list->addItem("Raised Button");
    list->addItem("ScrollBar");
    list->addItem("Slider");
    list->addItem("Snackbar");
    list->addItem("Tabs");
    list->addItem("Text Field");
    list->addItem("Toggle");

    list->setCurrentRow(0);


//    QColor canvasColor = QtMaterialStyle::instance().themeColor("canvas");

    QObject::connect(list,  &QListWidget::currentItemChanged,
        [=](QListWidgetItem *current, QListWidgetItem *previous)
    {
        Q_UNUSED(current)
        Q_UNUSED(previous)
        stack->setCurrentIndex(list->currentRow());
    });
}

void MainWindow::paintEvent(QPaintEvent *event){
    {
        QPainter painter(this);
        painter.fillRect(rect(), QColor(Qt::white));// QtMaterialStyle::instance().themeColor("canvas"));
    }
    QMainWindow::paintEvent(event);
}

MainWindow::~MainWindow()
{
}
