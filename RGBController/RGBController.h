/*
 * RGBContoller.h
 * 제네릭 RGB Lighting Controller 인터페이스를 위한 정의와 자료형
*/

#pragma once

#include <vector>
#include <string>

typedef unsigned int RGBColor;

#define RGBGetRValue(rgb)   (rgb & 0x000000FF)
#define RGBGetGValue(rgb)   ((rgb >> 8) & 0x000000FF)
#define RGBGetBValue(rgb)   ((rgb >> 16) & 0x000000FF)

#define ToRGBColor(r, g, b) ((b << 16) | (g << 8) | (r))

// 모드 플래그
enum
{
    MODE_FLAG_HAS_SPEED                 = (1 << 0), // 모드가 속도를 가짐
    MODE_FLAG_HAS_DIRECTION_LR          = (1 << 1), // 모드가 좌우 변수를 가짐
    MODE_FLAG_HAS_DIRECTION_UD          = (1 << 2), // 모드가 상하 변수를 가짐
    MODE_FLAG_HAS_DIRECTION_HV          = (1 << 3), // 모드가 수평, 수직 변수를 가짐
    MODE_FLAG_HAS_BRIGHTNESS            = (1 << 4), // 모드가 밝기 변수를 가짐
    MODE_FLAG_HAS_PER_LED_COLOR         = (1 << 5), // 모드가 개별 LED 변수를 가짐
    MODE_FLAG_HAS_MODE_SPECIFIC_COLOR   = (1 << 6), // 모드가 특정 색을 가짐
    MODE_FLAG_HAS_RANDOM_COLOR          = (1 << 7), // 모드가 무작위 색을 가짐
};

// 모드 방향
enum
{
    MODE_DIRECTION_LEFT         = 0,        // 좌
    MODE_DIRECTION_RIGHT        = 1,        // 우
    MODE_DIRECTION_UP           = 2,        // 상
    MODE_DIRECTION_DOWN         = 3,        // 하
    MODE_DIRECTION_HORIZONTAL   = 4,        // 수평
    MODE_DIRECTION_VERTICAL     = 5,        // 수직
};

enum
{
    MODE_COLORS_NONE            = 0,        // 모드 색 없음
    MODE_COLORS_PER_LED         = 1,        // 개별 LED 설정 가능
    MODE_COLORS_MODE_SPECIFIC   = 2,        // 특정 색 설정
    MODE_COLORS_RANDOM          = 3,        // 무작위 색 설정
};

// 모드 타입
typedef struct
{
    // 모드 정보
    std::string         name;       // 모드 이름
    int                 value;      // 기기 모드 값
    unsigned int        flags;      // 모드 플래그 비트 필드
    unsigned int        speed_min;  // 속도 최소값
    unsigned int        speed_max;  // 모드 최대값
    unsigned int        colors_min; // 모드 색 최소 수
    unsigned int        colors_max; // 모드 색 최대 수

    // 모드 설정
    unsigned int        speed;      // 모드 속도 값
    unsigned int        direction;  // 모드 방향 값
    unsigned int        color_mode; // 모드 색 선택
    std::vector<RGBColor> colors;   // 모드 색
} mode;

typedef struct
{
    std::string         name;   // LED 이름
    unsigned int        value;  // LED 값
} led;

typedef int zone_type;

enum
{
    ZONE_TYPE_SINGLE,
    ZONE_TYPE_LINEAR,
    ZONE_TYPE_MATRIX
};

typedef int device_type;

enum
{
    DEVICE_TYPE_MOTHERBOARD,
    DEVICE_TYPE_DRAM,
    DEVICE_TYPE_GPU,
    DEVICE_TYPE_COOLER,
    DEVICE_TYPE_LEDSTRIP,
    DEVICE_TYPE_KEYBOARD,
    DEVICE_TYPE_MOUSE,
    DEVICE_TYPE_MOUSEMAT,
    DEVICE_TYPE_HEADSET,
    DEVICE_TYPE_UNKNOWN
};

std::string device_type_to_str(device_type type);

typedef struct
{
    std::string             name;           // zone 이름
    zone_type               type;           // zone 타입
    led *                   leds;           // zone의 LED 리스트
    RGBColor *              colors;         // zone의 LED 색
    unsigned int            start_idx;      // LED와 색의 시작 인덱스
    unsigned int            leds_count;     // zone의 LED 수
    unsigned int            leds_min;       // 최소 LED 수
    unsigned int            leds_max;       // 최대 LED 수
} zone;

class RGBController
{
public:
    std::string             name;           // 컨트롤러 이름
    std::string             description;    // 컨트롤러 설명
    std::string             version;        // 컨트롤러 버전
    std::string             serial;         // 컨트롤러 시리얼 번호
    std::string             location;       // 컨트롤러 위치
    std::vector<led>        leds;           // LED
    std::vector<zone>       zones;          // zones
    std::vector<mode>       modes;          // 모드
    std::vector<RGBColor>   colors;         // 색 버퍼
    device_type             type;           // 기기 타입
    int                     active_mode = 0;// 활성화된 모드

    virtual ~RGBController() = default;

    // RGBController.cpp의 함수
    void                    SetupColors();

    RGBColor                GetLED(unsigned int led);
    void                    SetLED(unsigned int led, RGBColor color);
    void                    SetAllLEDs(RGBColor color);
    void                    SetAllZoneLEDs(int zone, RGBColor color);

    int                     GetMode();
    void                    SetMode(int mode);

    unsigned char *         GetDeviceDescription();
    void                    ReadDeviceDescription(unsigned char* data_buf);

    // 기기 적용 함수
    virtual void            SetupZones()                                = 0;

    virtual void            ResizeZone(int zone, int new_size)          = 0;

    virtual void            UpdateLEDs()                                = 0;
    virtual void            UpdateZoneLEDs(int zone)                    = 0;
    virtual void            UpdateSingleLED(int led)                    = 0;

    virtual void            SetCustomMode()                             = 0;
    virtual void            UpdateMode()                                = 0;
};
