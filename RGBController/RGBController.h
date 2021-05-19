/*
 *  Defintions and types for generic RGB lighiting controller interface
*/


#pragma once

#include <atomic>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>

typedef unsigned int RGBColor;

#define RGBGetRValue(rgb)    (rgb & 0x000000FF)
#define RGBGetGValue(rgb)    ((rgb >> 8) & 0x000000FF)
#define RGBGetBValue(rgb)    ((rgb >> 16) & 0x000000FF)

#define ToRGBColor(r, g, b) ((b << 16) | (g << 8) | (r))

// Mode Flags

enum
{
    MODE_FLAG_HAS_SPEED                 = (1 << 0),     // 모드가 속도 변수를 가짐
    MODE_FLAG_HAS_DIRECTION_LR          = (1 << 1),     // 모드가 좌우 변수를 가짐
    MODE_FLAG_HAS_DIRECTION_UD          = (1 << 2),     // 모드가 상하 변수를 가짐
    MODE_FLAG_HAS_DIRECTION_HV          = (1 << 3),     // 모드가 수평, 수직 변수를 가짐
    MODE_FLAG_HAS_BRIGHTNESS            = (1 << 4),     // 모드가 밝기 변수를 가짐
    MODE_FLAG_HAS_PER_LED_COLOR         = (1 << 5),     // 모드가 개별의 LED 색을 가짐
    MODE_FLAG_HAS_MODE_SPECIFIC_COLOR   = (1 << 6),     // 모드가 특정 색 모드를 가짐
    MODE_FLAG_HAS_RANDOM_COLOR          = (1 << 7),     // 모드가 무작위 색 설정을 가짐
};

// Mode Direction

enum
{
    MODE_DIRECTON_LEFT          = 0,                    // 모드 방향 좌
    MODE_DIRECTION_RIGHT        = 1,                    // 모드 방향 우
    MODE_DIRECTION_UP           = 2,                    // 모드 방향 상
    MODE_DIRECTION_DOWN         = 3,                    // 모드 방향 하
    MODE_DIRECTION_HORIZONITAL  = 4,                    // 모드 방향 수평
    MODE_DIRECTION_VERTICAL     = 5,                    // 모드 방향 수직
};

// Mode Type

typedef struct
{
    // Mode Information
    std::string         name;           // 모드 이름
    int                 value;          // 기기의 모드 값
    unsigned int        flags;          // 모드 플레그의 비트필드
    unsigned int        speed_min;      // 속도 최소값
    unsigned int        speed_max;      // 속도 최대값
    unsigned int        colors_min;     // 모드 색의 최소
    unsigned int        colors_max;     // 모드 색의 최대

    // Mode Settings
    unsigned int        speed;          // 모드 속도 값
    unsigned int        direction;      // 모드 방향 값
    unsigned int        color_mode;     // 모드 색 선택
    std::vector<RGBColor> colors;       // 모드의 특정 색들
} mode;

typedef struct
{
    std::string         name;           // LED의 이름
    unsigned int        value;          // 기기의 LED 값
} led;

typedef int zone_type;

enum
{
    ZONE_TYPE_SINGLE,
    ZONE_TYPE_LINEAR,
    ZONE_TYPE_MATRIX,
};

typedef int device_type;

enum
{
    DEVICE_TYPE_MOTHERBOARD,
    DEVICE_TYPE_DRAM,
    DEVICE_TYPE_MOUSE,
    DEVICE_TYPE_UNKOWN,
};

std::string device_type_to_str(device_type type);

typedef struct
{
    unsigned int        height;
    unsigned int        width;
    unsigned int *      map;
} matrix_map_type;

typedef struct
{
    std::string name;
    zone_type type;
    led * leds;
    RGBColor * colors;
    unsigned int start_idx;
    unsigned int leds_min;
    unsigned int leds_max;
    unsigned int leds_count;
    matrix_map_type * matrix_map;
} zone;

typedef void (*RGBControllerCallback) (void *);

class RGBController
{
public:
    std::string             name;           // 컨트롤러 이름
    std::string             vendor;         // 컨트롤러 회사
    std::string             description;    // 컨트롤러 설명
    std::string             version;        // 컨트롤러 버전
    std::string             serial;         // 컨트롤러 시리얼 넘버
    std::string             location;       // 컨트롤러 위치
    std::vector<led>        leds;           // LED
    std::vector<zone>       zones;          // Zone
    std::vector<mode>       modes;          // 모드
    std::vector<RGBColor>   colors;         // 색 버퍼
    device_type             type;           // 기기 타입
    int                     active_mode = 0;// 활성화된 모드

    RGBController();
    virtual ~RGBController();

    void SetupColors();

    RGBColor GetLED(unsigned int led);
    void SetLED(unsigned int led, RGBColor color);
    void SetAllLEDs(RGBColor color);
    void SetAllZoneLEDs(int zone, RGBColor color);

    int GetMode();
    void SetMode(int mode);

    unsigned char * GetDeviceDescription(unsigned int protocol_version);
    void ReadDeviceDescription(unsigned char* data_buf, unsigned int protocol_version);

    unsigned char * GetModeDescription(int mode);
    void SetModeDescription(unsigned char* data_buf);

    unsigned char * GetColorDescription();
    void SetColorDescription(unsigned char* data_buf);

    unsigned char * GetZoneColorDescription(int zone);
    void SetZoneColorDescription(unsigned char* data_buf);

    unsigned char * GetSingleLEDColorDescription(int led);
    void SetSingleLEDColorDescription(unsigned char* data_buf);
    void RegisterUpdateCallBack(RGBControllerCallback new_callback, void* new_callback_arg);
    void UnregisterUpdateCallback(void* callback_arg);
    void SignalUpdate();

    void UpdateLEDs();
    void UpdateMode();
    void DeviceCallThreadFunction();

    virtual void SetupZones() = 0;
    virtual void ResizeZone(int zone, int new_size) = 0;
    virtual void DeviceUpdateLEDs() = 0;
    virtual void UpdateZoneLEDs(int zone) = 0;
    virtual void DeviceSingleLED(int led) = 0;
    virtual void DeviceUpdateMode() = 0;
    virtual void SetCustomMode() = 0;
private:
    std::thread* DeviceCallThread;
    std::atomic<bool> CallFlag_UpdateLEDs;
    std::atomic<bool> CallFalg_UpdateMode;
    std::atomic<bool> DeviceThreadRunning;

    std::mutex UpdateMutex;
    std::vector<RGBControllerCallback> UpdateCallbacks;
    std::vector<void *> UpdateCallbackArgs;
};
