/*
 * i2c_smbus.h
 * SMBus 드라이버 정의와 타입
 * Linux 소스 코드에서 가져옴
 * GNU GPL v2
*/

#ifndef I2C_SMBUS_H
#define I2C_SMBUS_H

typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned int    u32;
typedef int             s32;

#define I2C_SMBUS_BLOCK_MAX     32

union i2c_smbus_data
{
    u8          byte;
    u16         word;
    u8          block[I2C_SMBUS_BLOCK_MAX + 2];
};

// i2c_smbus_xfer 읽기 쓰기 마커
#define I2C_SMBUS_READ  1
#define I2C_SMBUS_WRITE 0

// SMBus transaction 타입
#define I2C_SMBUS_QUICK             0
#define I2C_SMBUS_BYTE              1
#define I2C_SMBUS_BYTE_DATA         2
#define I2C_SMBUS_WORD_DATA         3
#define I2C_SMBUS_PROC_CALL         4
#define I2C_SMBUS_BLOCK_DATA        5
#define I2C_SMBUS_I2C_BLOCK_BROKEN  6
#define I2C_SMBUS_BLOCK_PROC_CALL   7
#define I2C_SMBUS_I2C_BLOCK_DATA    8

class i2c_smbus_interface
{
public:
    char device_name[512];

    virtual ~i2c_smbus_interface() = default;

    s32 i2c_smbus_write_quick(u8 addr, u8 value);
    s32 i2c_smbus_read_byte(u8 addr);
    s32 i2c_smbus_write_byte(u8 addr, u8 value);
    s32 i2c_smbus_read_byte_data(u8 addr, u8 command);
    s32 i2c_smbus_write_byte_data(u8 addr, u8 command, u8 value);
    s32 i2c_smbus_read_word_data(u8 addr, u8 command);
	s32 i2c_smbus_write_word_data(u8 addr, u8 command, u16 value);
    s32 i2c_smbus_read_block_data(u8 addr, u8 command, u8 *values);
	s32 i2c_smbus_write_block_data(u8 addr, u8 command, u8 length, const u8 *values);
    s32 i2c_smbus_read_i2c_block_data(u8 addr, u8 command, u8 length, u8 *values);
    s32 i2c_smbus_write_i2c_block_data(u8 addr, u8 command, u8 length, const u8 *values);

    virtual s32 i2c_smbus_xfer(u8 addr, char read_write, u8 command, int size, i2c_smbus_data* data) = 0;
};

#endif /* I2C_SMBUS_H */
