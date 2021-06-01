#include "i2c_tools.h"

/*
 * i2c detect
 * 주어진 버스의 감지된 모든 i2c 주소를 리스트로 만든다
 * bus - 스캔한 i2c_smbus_interface 포인터
 * mode - AUTO, QUICKM, RED, FUNC: 접근 방식
 * 리눅스 패키지의 i2cdetect.c의 i2c-tools 참고함
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
            // 필요없는 주소 건너뛰기
			if (i+j < first || i+j > last)
            {
                sprintf(line, "   ");
                text.append(line);
				continue;
			}

            // slave address 설정
            slave_addr = i + j;

            // 해당 주소 찾기
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

}   /* i2c_detect() */

/*
 * i2c_dump
 * 주어진 SMBus 기기의 주소 값을 반환함
 * bus - 스캔한 i2c_smbus_interface 포인터
 * address - 스캔한 SMBus 기기
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

}   /* i2c_dump() */
