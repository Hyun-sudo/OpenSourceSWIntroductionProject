#include "rgbdialog01.h"


RGBDialog01::RGBDialog01(std::vector<i2c_smbus_interface *>& bus, std::vector<RGBController *>& control, QWidget *parent) :
    QMainWindow(parent),
    busses(bus),
    controllers(control),
    ui(new Ui::RGBDialog01Ui)
{
    ui->setupUi(this);

    QIcon icon(":RGBSync.png");
    setWindowIcon(icon);

    QPalette pal;

    pal = ui->ButtonRed->palette();
    pal.setColor(QPalette::Button, QColor(255, 0, 0));
    ui->ButtonRed->setAutoFillBackground(true);
    ui->ButtonRed->setPalette(pal);
    ui->ButtonRed->setFlat(true);
    ui->ButtonRed->update();

    pal = ui->ButtonYellow->palette();
    pal.setColor(QPalette::Button, QColor(255, 255, 0));
    ui->ButtonYellow->setAutoFillBackground(true);
    ui->ButtonYellow->setPalette(pal);
    ui->ButtonYellow->setFlat(true);
    ui->ButtonYellow->update();

    pal = ui->ButtonGreen->palette();
    pal.setColor(QPalette::Button, QColor(0, 255, 0));
    ui->ButtonGreen->setAutoFillBackground(true);
    ui->ButtonGreen->setPalette(pal);
    ui->ButtonGreen->setFlat(true);
    ui->ButtonGreen->update();

    pal = ui->ButtonCyan->palette();
    pal.setColor(QPalette::Button, QColor(0, 255, 255));
    ui->ButtonCyan->setAutoFillBackground(true);
    ui->ButtonCyan->setPalette(pal);
    ui->ButtonCyan->setFlat(true);
    ui->ButtonCyan->update();

    pal = ui->ButtonBlue->palette();
    pal.setColor(QPalette::Button, QColor(0, 0, 255));
    ui->ButtonBlue->setAutoFillBackground(true);
    ui->ButtonBlue->setPalette(pal);
    ui->ButtonBlue->setFlat(true);
    ui->ButtonBlue->update();

    pal = ui->ButtonMagenta->palette();
    pal.setColor(QPalette::Button, QColor(255, 0, 255));
    ui->ButtonMagenta->setAutoFillBackground(true);
    ui->ButtonMagenta->setPalette(pal);
    ui->ButtonMagenta->setFlat(true);
    ui->ButtonMagenta->update();

    for (std::size_t i = 0; i < controllers.size(); i++)
    {
        ui->ComboDevices->addItem(controllers[i]->name.c_str());
    }

    ui->ComboDevices->setCurrentIndex(0);
}

RGBDialog01::~RGBDialog01()
{
    delete ui;
}

void RGBDialog01::show()
{
    QMainWindow::show();
}

void RGBDialog01::on_ButtonRed_clicked()
{
    ui->EditLED0R->setText("255");
    ui->EditLED0G->setText("0");
    ui->EditLED0B->setText("0");
}

void RGBDialog01::on_ButtonYellow_clicked()
{
    ui->EditLED0R->setText("255");
    ui->EditLED0G->setText("255");
    ui->EditLED0B->setText("0");
}

void RGBDialog01::on_ButtonGreen_clicked()
{
    ui->EditLED0R->setText("0");
    ui->EditLED0G->setText("255");
    ui->EditLED0B->setText("0");
}

void RGBDialog01::on_ButtonCyan_clicked()
{
    ui->EditLED0R->setText("0");
    ui->EditLED0G->setText("255");
    ui->EditLED0B->setText("255");
}

void RGBDialog01::on_ButtonBlue_clicked()
{
    ui->EditLED0R->setText("0");
    ui->EditLED0G->setText("0");
    ui->EditLED0B->setText("255");
}

void RGBDialog01::on_ButtonMagenta_clicked()
{
    ui->EditLED0R->setText("255");
    ui->EditLED0G->setText("0");
    ui->EditLED0B->setText("255");
}

void RGBDialog01::on_ButtonSetAll_clicked()
{
    RGBColor color = ToRGBColor(
        ui->EditLED0R->text().toInt(),
        ui->EditLED0G->text().toInt(),
        ui->EditLED0B->text().toInt()
    );

    for (std::size_t i = 0; i < controllers.size(); i++)
    {
        controllers[i]->SetCustomMode();
        controllers[i]->SetAllLEDs(color);
    }
}

void RGBDialog01::on_ButtonSetDevice_clicked()
{
    RGBColor color = ToRGBColor(
        ui->EditLED0R->text().toInt(),
        ui->EditLED0G->text().toInt(),
        ui->EditLED0B->text().toInt()
    );

    controllers[ui->ComboDevices->currentIndex()]->SetAllLEDs(color);
}

void RGBDialog01::on_ButtonSetZone_clicked()
{
    RGBColor color = ToRGBColor(
        ui->EditLED0R->text().toInt(),
        ui->EditLED0G->text().toInt(),
        ui->EditLED0B->text().toInt()
    );

    controllers[ui->ComboDevices->currentIndex()]->SetAllZoneLEDs(ui->ComboZones->currentIndex(), color);
}

void RGBDialog01::on_ButtonSetLED_clicked()
{
    RGBColor color = ToRGBColor(
        ui->EditLED0R->text().toInt(),
        ui->EditLED0G->text().toInt(),
        ui->EditLED0B->text().toInt()
    );

    controllers[ui->ComboDevices->currentIndex()]->SetLED(ui->ComboLEDs->currentIndex(), color);
}

void RGBDialog01::on_ComboDevices_currentIndexChanged()
{
    ui->ComboModes->clear();

    for (std::size_t i = 0; i < controllers[ui->ComboDevices->currentIndex()]->modes.size(); i++)
    {
        ui->ComboModes->addItem(controllers[ui->ComboDevices->currentIndex()]->modes[i].name.c_str());
    }

    ui->ComboModes->setCurrentIndex(controllers[ui->ComboDevices->currentIndex()]->GetMode());

    ui->ComboZones->clear();

    for (std::size_t i = 0; i < controllers[ui->ComboDevices->currentIndex()]->zones.size(); i++)
    {
        ui->ComboZones->addItem(controllers[ui->ComboDevices->currentIndex()]->zones[i].name.c_str());
    }

    ui->ComboZones->setCurrentIndex(0);

    ui->ComboLEDs->clear();

    for (std::size_t i = 0; i < controllers[ui->ComboDevices->currentIndex()]->leds.size(); i++)
    {
        ui->ComboLEDs->addItem(controllers[ui->ComboDevices->currentIndex()]->leds[i].name.c_str());
    }

    ui->ComboLEDs->setCurrentIndex(0);
}

void RGBDialog01::on_ComboModes_currentIndexChanged()
{
    controllers[ui->ComboDevices->currentIndex()]->SetMode(ui->ComboModes->currentIndex());
}
