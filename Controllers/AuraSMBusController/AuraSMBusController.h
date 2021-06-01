/*
 * AuraSMBusContoller.h
 * ASUS Aura RGB lighting 컨트롤러에 대한 정의와 타입
*/

#include <string>
#include "i2c_smbus.h"

#pragma once

typedef unsigned char	aura_dev_id;
typedef unsigned short	aura_register;

#define AURA_APPLY_VAL  0x01               // Apply Change 레지스터

enum
{
    AURA_REG_DEVICE_NAME                = 0x1000,   // 기기 스트링 16 바이트
    AURA_REG_CONFIG_TABLE               = 0x1C00,   // LED 구성 바이트
    AURA_REG_COLORS_DIRECT              = 0x8000,   // 다이렉트 모드 색들 15바이트
    AURA_REG_COLORS_EFFECT              = 0x8010,   // 색 효과 15바이트
    AURA_REG_DIRECT                     = 0x8020,   // 다이렉트 선택 레지스터
    AURA_REG_MODE                       = 0x8021,   // Aura Mode 선택 레지스터
    AURA_REG_APPLY                      = 0x80A0,   // Aura Apply Change 레지스터
    AURA_REG_SLOT_INDEX                 = 0x80F8,   // (RAM) Aura Slot 인덱스 레지스터
    AURA_REG_I2C_ADDRESS                = 0x80F9,   // (RAM) Aura I2C 주소 레지스터
    AURA_REG_COLORS_DIRECT_V2           = 0x8100,   // 다이렉트 모드 색 (v2) 30 바이트
    AURA_REG_COLORS_EFFECT_V2           = 0x8160,   // 색 효과 (v2) 30바이트
};

enum
{
    AURA_MODE_OFF                       = 0,
    AURA_MODE_STATIC                    = 1,
    AURA_MODE_BREATHING                 = 2,
    AURA_MODE_FLASHING                  = 3,
    AURA_MODE_SPECTRUM_CYCLE            = 4,
    AURA_MODE_RAINBOW                   = 5,
    AURA_MODE_SPECTRUM_CYCLE_BREATHING  = 6,
    AURA_MODE_CHASE_FADE                = 7,
    AURA_MODE_SPECTRUM_CYCLE_CHASE_FADE = 8,
    AURA_MODE_CHASE                     = 9,
    AURA_MODE_SPECTRUM_CYCLE_CHASE      = 10,
    AURA_MODE_SPECTRUM_CYCLE_WAVE       = 11,
    AURA_MODE_CHASE_RAINBOW_PULSE       = 12,
    AURA_MODE_RANDOM_FLICKER            = 13,
    AURA_NUMBER_MODES                           // Aura Mode 개수
};

enum
{
    AURA_LED_CHANNEL_DRAM_2             = 0x05,     // DRAM LED 채널 (2)
    AURA_LED_CHANNEL_CENTER_START       = 0x82,     // Center zone의 첫번째 LED 채널
    AURA_LED_CHANNEL_CENTER             = 0x83,     // Center zone LED 채널
    AURA_LED_CHANNEL_AUDIO              = 0x84,     // Audio zone LED 채널
    AURA_LED_CHANNEL_BACK_IO            = 0x85,     // Back I/O zone LED 채널
    AURA_LED_CHANNEL_RGB_HEADER         = 0x86,     // RGB 해더 1 LED 채널
    AURA_LED_CHANNEL_RGB_HEADER_2       = 0x87,     // RGB 해더 2 LED 채널
    AURA_LED_CHANNEL_BACKPLATE          = 0x88,     // 백플레이트 LED 채널
    AURA_LED_CHANNEL_DRAM               = 0x8A,     // DRAM LED 채널 (1)
    AURA_LED_CHANNEL_PCIE               = 0x8B,     // PCIe LED 채널
    AURA_LED_CHANNEL_RGB_HEADER_3       = 0x91,     // RGB 해더 3 LED 채널
};

static const char* aura_channels[] =
{
    "Audio",
    "Backplate",
    "Back I/O",
    "Center",
    "Center",
    "DRAM",
    "PCIe",
    "RGB Header",
    "RGB Header 2",
    "RGB Header",
    "Unknown",
};

enum
{
    AURA_CONFIG_LED_COUNT               = 0x02,     /* LED Count configuration offset       */
    AURA_CONFIG_CHANNEL_V1              = 0x13,     /* LED Channel configuration offset     */
    AURA_CONFIG_CHANNEL_V2              = 0x1B,     /* LED Channel V2 configuration offset  */
};

class AuraSMBusController
{
public:
    AuraSMBusController(i2c_smbus_interface* bus, aura_dev_id dev);
    ~AuraSMBusController();

    std::string   GetDeviceName();
    std::string   GetDeviceLocation();
    unsigned char GetChannel(unsigned int led);
    const char*   GetChannelName(unsigned int led);
    unsigned int  GetLEDCount();
    unsigned char GetLEDRed(unsigned int led);
    unsigned char GetLEDGreen(unsigned int led);
    unsigned char GetLEDBlue(unsigned int led);
    void          SetAllColorsDirect(unsigned char red, unsigned char green, unsigned char blue);
    void          SetAllColorsEffect(unsigned char red, unsigned char green, unsigned char blue);
    void          SetDirect(unsigned char direct);
    void          SetLEDColorDirect(unsigned int led, unsigned char red, unsigned char green, unsigned char blue);
    void          SetLEDColorEffect(unsigned int led, unsigned char red, unsigned char green, unsigned char blue);
    void          SetMode(unsigned char mode);

    void          AuraUpdateDeviceName();

    unsigned char AuraRegisterRead(aura_register reg);
    void          AuraRegisterWrite(aura_register reg, unsigned char val);
    void          AuraRegisterWriteBlock(aura_register reg, unsigned char * data, unsigned char sz);

private:
    char                    device_name[16];
    unsigned char           config_table[64];
    unsigned int            led_count;
    aura_register           direct_reg;
    aura_register           effect_reg;
    unsigned char           channel_cfg;
    i2c_smbus_interface *   bus;
    aura_dev_id             dev;

};
