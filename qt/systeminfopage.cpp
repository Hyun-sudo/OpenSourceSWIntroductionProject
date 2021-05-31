#include "systeminfopage.h"
#include "i2c_tools.h"

SystemInfoPage::SystemInfoPage(std::vector<i2c_smbus_interface *>& bus, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::SystemInfoPageUi),
    busses(bus)
{
    ui->setupUi(this);

    // 폰트 설정
    QFont MonoFont("monospace");
    MonoFont.setStyleHint(QFont::Monospace);
    ui->SMBusDataText->setFont(MonoFont);

    // 콤보 박스를 기기 정보로 채움
    ui->SMBusAdaptersBox->clear();

    for (std::size_t i = 0; i < busses.size(); i++)
    {
        ui->SMBusAdaptersBox->addItem(busses[i]->device_name);
    }

    ui->SMBusAdaptersBox->setCurrentIndex(0);
}

SystemInfoPage::~SystemInfoPage()
{
    delete ui;
}

void SystemInfoPage::on_DetectButton_clicked()
{
    i2c_smbus_interface* bus = busses[ui->SMBusAdaptersBox->currentIndex()];

    ui->SMBusDataText->setPlainText(i2c_detect(bus, MODE_QUICK).c_str());
}

void SystemInfoPage::on_DumpButton_clicked()
{
    i2c_smbus_interface* bus = busses[ui->SMBusAdaptersBox->currentIndex()];
    unsigned char address = ui->DumpAddressBox->value();

    ui->SMBusDataText->setPlainText(i2c_dump(bus, address).c_str());
}
