#include "i2c_tools.h"

/*
 * i2c_detect
 * 찾을 수 있는 주어진 BUS의 모든 I2C 주소를 출력한다.
 * bus: 스캔하는 i2c_smbus_interface의 포인터
 * mode: 접근할 방법 (AUTO, QUICK, READ, FUNC)
*/
std::string i2c_detect(i2c_smbus_interface * bus, int mode)
{
    int i, j;
    int first = 0x03, last = 0x77;
    int res;
    int slave_addr;
    char line[128];
    std::string text;

    sprintf(line, "     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\r\n");
    text.append(line);

    for (i = 0; i < 128; i += 16)
    {
        sprintf(line, "%02x: ", i);
        text.append(line);

        for (j = 0; j < 16; j++)
        {
            // 필요 없는 주소 건너뛰기
            if (i+j < first || i+j > last)
            {
                sprintf(line, "   ");
                text.append(line);
                continue;
            }

            // slave address 설정
            slave_addr = i + j;

            // 주소 찾기
            switch (mode)
            {
            case MODE_QUICK:
                res = bus->i2c_smbus_write_quick(slave_addr, I2C_SMBUS_WRITE);
                break;
            case MODE_READ:
                res = bus->i2c_smbus_read_byte(slave_addr);
                break;
            default:
                if ((i + j >= 0x30 && i + j <= 0x37)
                 || (i + j >= 0x50 && i + j <= 0x5F))
                    res = bus->i2c_smbus_read_byte(slave_addr);
                else
                    res = bus->i2c_smbus_write_quick(slave_addr, I2C_SMBUS_WRITE);
                break;
            }

            if (res < 0)
            {
                sprintf(line, "-- ");
                text.append(line);
            }
            else
            {
                sprintf(line, "%02x ", i + j);
                text.append(line);
            }
        }
        sprintf(line, "\r\n");
        text.append(line);
    }

    return text;
}

/*
 * i2c_dump
 * 주어진 SMBus 기기의 각 주소값을 출력
 * bus: 스캔할 i2c_smbus_interface의 포인터
 * address: 스캔할 SMBus 기기 주소
*/
std::string i2c_dump(i2c_smbus_interface * bus, unsigned char address)
{
    int i, j;

    int start = 0x0000;

    char line[128];
    std::string text;

    sprintf(line, "       0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\r\n");
    text.append(line);

    for (i = 0; i < 0xFF; i += 16)
    {
        sprintf(line, "%04x: ", i + start);
        text.append(line);

        for (j = 0; j < 16; j++)
        {
            sprintf(line, "%02x ", (unsigned char )bus->i2c_smbus_read_byte_data(address, start + i + j));
            text.append(line);
        }

        sprintf(line, "\r\n");
        text.append(line);
    }

    return text;

}

/*
 * i2c_read
 * 주어진 SMBus 기기의 레지스터 주소 변수 regaddr로부터 크기 값을 읽음
 * bus: 스캔할 i2c_smbus_interface의 포인터
 * address: 스캔할 SMBus 기기 주소
 * regaddr: 읽을 레지스터 주소
 * size: 읽어야할 byte 수
*/
std::string i2c_read(i2c_smbus_interface * bus, unsigned char address, unsigned char regaddr, unsigned char size)
{
    int i;

    bus->i2c_smbus_write_byte(address, regaddr);

    char line[128];
    std::string text;

    for(i = 0; i < size; i++)
    {
        sprintf(line, "%02x ", (unsigned char)bus->i2c_smbus_read_byte(address));
        text.append(line);
    }

    return text;

}
