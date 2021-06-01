#include "RGBController.h"
#include <cstring>

unsigned char * RGBController::GetDeviceDescription()
{
    unsigned int data_ptr = 0;
    unsigned int data_size = 0;

    // 데이터 크기 계산
    unsigned short name_len         = strlen(name.c_str())          + 1;
    unsigned short description_len  = strlen(description.c_str())   + 1;
    unsigned short version_len      = strlen(version.c_str())       + 1;
    unsigned short serial_len       = strlen(serial.c_str())        + 1;
    unsigned short location_len     = strlen(location.c_str())      + 1;
    unsigned short num_modes        = modes.size();
    unsigned short num_zones        = zones.size();
    unsigned short num_leds         = leds.size();
    unsigned short num_colors       = colors.size();

    unsigned short *mode_name_len   = new unsigned short[num_modes];
    unsigned short *zone_name_len   = new unsigned short[num_zones];
    unsigned short *led_name_len    = new unsigned short[num_leds];

    unsigned short *mode_num_colors = new unsigned short[num_modes];

    data_size += sizeof(data_size);
    data_size += sizeof(device_type);
    data_size += name_len           + sizeof(name_len);
    data_size += description_len    + sizeof(description_len);
    data_size += version_len        + sizeof(version_len);
    data_size += serial_len         + sizeof(serial_len);
    data_size += location_len       + sizeof(location_len);

    data_size += sizeof(num_modes);
    data_size += sizeof(active_mode);

    for(int mode_index = 0; mode_index < num_modes; mode_index++)
    {
        mode_name_len[mode_index]   = strlen(modes[mode_index].name.c_str()) + 1;
        mode_num_colors[mode_index] = modes[mode_index].colors.size();

        data_size += mode_name_len[mode_index] + sizeof(mode_name_len[mode_index]);
        data_size += sizeof(modes[mode_index].value);
        data_size += sizeof(modes[mode_index].flags);
        data_size += sizeof(modes[mode_index].speed_min);
        data_size += sizeof(modes[mode_index].speed_max);
        data_size += sizeof(modes[mode_index].colors_min);
        data_size += sizeof(modes[mode_index].colors_max);
        data_size += sizeof(modes[mode_index].speed);
        data_size += sizeof(modes[mode_index].direction);
        data_size += sizeof(modes[mode_index].color_mode);
        data_size += sizeof(mode_num_colors[mode_index]);
        data_size += (mode_num_colors[mode_index] * sizeof(RGBColor));
    }

    data_size += sizeof(num_zones);

    for(int zone_index = 0; zone_index < num_zones; zone_index++)
    {
        zone_name_len[zone_index]   = strlen(zones[zone_index].name.c_str()) + 1;

        data_size += zone_name_len[zone_index] + sizeof(zone_name_len[zone_index]);
        data_size += sizeof(zones[zone_index].type);
        data_size += sizeof(zones[zone_index].leds_min);
        data_size += sizeof(zones[zone_index].leds_max);
        data_size += sizeof(zones[zone_index].leds_count);
    }

    data_size += sizeof(num_leds);

    for(int led_index = 0; led_index < num_leds; led_index++)
    {
        led_name_len[led_index] = strlen(leds[led_index].name.c_str()) + 1;

        data_size += led_name_len[led_index] + sizeof(led_name_len[led_index]);

        data_size += sizeof(leds[led_index].value);
    }

    data_size += sizeof(num_colors);
    data_size += num_colors * sizeof(RGBColor);

    // 데이터 버퍼 생성
    unsigned char *data_buf = new unsigned char[data_size];

    // 데이터 크기 복사
    memcpy(&data_buf[data_ptr], &data_size, sizeof(data_size));
    data_ptr += sizeof(data_size);

    // 기기 타입 복사
    memcpy(&data_buf[data_ptr], &type, sizeof(device_type));
    data_ptr += sizeof(device_type);

    // 이름 복사 (size + data)
    memcpy(&data_buf[data_ptr], &name_len, sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    strcpy((char *)&data_buf[data_ptr], name.c_str());
    data_ptr += name_len;

    // 설명 복사 (size + data)
    memcpy(&data_buf[data_ptr], &description_len, sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    strcpy((char *)&data_buf[data_ptr], description.c_str());
    data_ptr += description_len;

    // 버전 복사 (size + data)
    memcpy(&data_buf[data_ptr], &version_len, sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    strcpy((char *)&data_buf[data_ptr], version.c_str());
    data_ptr += version_len;

    // 시리얼 번호 복사 (size + data)
    memcpy(&data_buf[data_ptr], &serial_len, sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    strcpy((char *)&data_buf[data_ptr], serial.c_str());
    data_ptr += serial_len;

    // 위치 복사 (size + data)
    memcpy(&data_buf[data_ptr], &location_len, sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    strcpy((char *)&data_buf[data_ptr], location.c_str());
    data_ptr += location_len;

    // 모드 복사
    memcpy(&data_buf[data_ptr], &num_modes, sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    // 활성화된 모드 복사
    memcpy(&data_buf[data_ptr], &active_mode, sizeof(active_mode));
    data_ptr += sizeof(active_mode);

    // 2개 이상의 모드 복사
    for(int mode_index = 0; mode_index < num_modes; mode_index++)
    {
        // 모드 이름 복사 (size + data)
        memcpy(&data_buf[data_ptr], &mode_name_len[mode_index], sizeof(unsigned short));
        data_ptr += sizeof(unsigned short);

        strcpy((char *)&data_buf[data_ptr], modes[mode_index].name.c_str());
        data_ptr += mode_name_len[mode_index];

        // 모드 값 복사
        memcpy(&data_buf[data_ptr], &modes[mode_index].value, sizeof(modes[mode_index].value));
        data_ptr += sizeof(modes[mode_index].value);

        // 모드 플래그 복사
        memcpy(&data_buf[data_ptr], &modes[mode_index].flags, sizeof(modes[mode_index].flags));
        data_ptr += sizeof(modes[mode_index].flags);

        // 모드 속도 최솟값 복사
        memcpy(&data_buf[data_ptr], &modes[mode_index].speed_min, sizeof(modes[mode_index].speed_min));
        data_ptr += sizeof(modes[mode_index].speed_min);

        // 모드 최댓값 복사
        memcpy(&data_buf[data_ptr], &modes[mode_index].speed_max, sizeof(modes[mode_index].speed_max));
        data_ptr += sizeof(modes[mode_index].speed_max);

        // 모드 색 최솟값 복사
        memcpy(&data_buf[data_ptr], &modes[mode_index].colors_min, sizeof(modes[mode_index].colors_min));
        data_ptr += sizeof(modes[mode_index].colors_min);

        // 모드 색 최댓값 복사
        memcpy(&data_buf[data_ptr], &modes[mode_index].colors_max, sizeof(modes[mode_index].colors_max));
        data_ptr += sizeof(modes[mode_index].colors_max);

        // 모드 속도 복사
        memcpy(&data_buf[data_ptr], &modes[mode_index].speed, sizeof(modes[mode_index].speed));
        data_ptr += sizeof(modes[mode_index].speed);

        // 모드 방향 복사
        memcpy(&data_buf[data_ptr], &modes[mode_index].direction, sizeof(modes[mode_index].direction));
        data_ptr += sizeof(modes[mode_index].direction);

        // 모드 색 모드 복사
        memcpy(&data_buf[data_ptr], &modes[mode_index].color_mode, sizeof(modes[mode_index].color_mode));
        data_ptr += sizeof(modes[mode_index].color_mode);

        // 모드 색의 수 복사
        memcpy(&data_buf[data_ptr], &mode_num_colors[mode_index], sizeof(unsigned short));
        data_ptr += sizeof(unsigned short);

        // 모드 색 복사
        for(int color_index = 0; color_index < mode_num_colors[mode_index]; color_index++)
        {            
            memcpy(&data_buf[data_ptr], &modes[mode_index].colors[color_index], sizeof(modes[mode_index].colors[color_index]));
            data_ptr += sizeof(modes[mode_index].colors[color_index]);
        }
    }

    // zone 개수 복사
    memcpy(&data_buf[data_ptr], &num_zones, sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    // zone 복사
    for(int zone_index = 0; zone_index < num_zones; zone_index++)
    {
        // zone 이름 복사 (size + data)
        memcpy(&data_buf[data_ptr], &zone_name_len[zone_index], sizeof(unsigned short));
        data_ptr += sizeof(unsigned short);

        strcpy((char *)&data_buf[data_ptr], zones[zone_index].name.c_str());
        data_ptr += zone_name_len[zone_index];

        // zone 타입 복사
        memcpy(&data_buf[data_ptr], &zones[zone_index].type, sizeof(zones[zone_index].type));
        data_ptr += sizeof(zones[zone_index].type);

        // zone LED 최소 개수
        memcpy(&data_buf[data_ptr], &zones[zone_index].leds_min, sizeof(zones[zone_index].leds_min));
        data_ptr += sizeof(zones[zone_index].leds_min);

        // zone LED 최대 개수
        memcpy(&data_buf[data_ptr], &zones[zone_index].leds_max, sizeof(zones[zone_index].leds_max));
        data_ptr += sizeof(zones[zone_index].leds_max);

        // zone LED 개수
        memcpy(&data_buf[data_ptr], &zones[zone_index].leds_count, sizeof(zones[zone_index].leds_count));
        data_ptr += sizeof(zones[zone_index].leds_count);
    }

    // LED 개수 복사
    memcpy(&data_buf[data_ptr], &num_leds, sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    // LED 복사
    for(int led_index = 0; led_index < num_leds; led_index++)
    {
        // LED 이름 복사 (size + data)
        unsigned short ledname_len = strlen(leds[led_index].name.c_str()) + 1;
        memcpy(&data_buf[data_ptr], &ledname_len, sizeof(unsigned short));
        data_ptr += sizeof(unsigned short);

        strcpy((char *)&data_buf[data_ptr], leds[led_index].name.c_str());
        data_ptr += ledname_len;

        // LED 값 복사
        memcpy(&data_buf[data_ptr], &leds[led_index].value, sizeof(leds[led_index].value));
        data_ptr += sizeof(leds[led_index].value);
    }

    // 색 개수 복사
    memcpy(&data_buf[data_ptr], &num_colors, sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    // 색 복사
    for(int color_index = 0; color_index < num_colors; color_index++)
    {
        memcpy(&data_buf[data_ptr], &colors[color_index], sizeof(colors[color_index]));
        data_ptr += sizeof(colors[color_index]);
    }


    delete[] mode_name_len;
    delete[] zone_name_len;
    delete[] led_name_len;

    delete[] mode_num_colors;

    return(data_buf);
}

void RGBController::ReadDeviceDescription(unsigned char* data_buf)
{
    unsigned int data_ptr = 0;

    data_ptr += sizeof(unsigned int);

    // 기기 타입 복사
    memcpy(&type, &data_buf[data_ptr], sizeof(device_type));
    data_ptr += sizeof(device_type);

    // 이름 복사 (size + data)
    unsigned short name_len;
    memcpy(&name_len, &data_buf[data_ptr], sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    name = (char *)&data_buf[data_ptr];
    data_ptr += name_len;

    // 설명 복사 (size + data)
    unsigned short description_len;
    memcpy(&description_len, &data_buf[data_ptr], sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    description = (char *)&data_buf[data_ptr];
    data_ptr += description_len;

    // 버전 복사 (size + data)
    unsigned short version_len;
    memcpy(&version_len, &data_buf[data_ptr], sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    version = (char *)&data_buf[data_ptr];
    data_ptr += version_len;

    // 시리얼 번호 복사 (size + data)
    unsigned short serial_len;
    memcpy(&serial_len, &data_buf[data_ptr], sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    serial = (char *)&data_buf[data_ptr];
    data_ptr += serial_len;

    // 위치 복사 (size + data)
    unsigned short location_len;
    memcpy(&location_len, &data_buf[data_ptr], sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    location = (char *)&data_buf[data_ptr];
    data_ptr += location_len;
    // 모드 개수 복사
    unsigned short num_modes;
    memcpy(&num_modes, &data_buf[data_ptr], sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    // 활성화 모드 복사
    memcpy(&active_mode, &data_buf[data_ptr], sizeof(active_mode));
    data_ptr += sizeof(active_mode);

    // 모드 복사
    for(int mode_index = 0; mode_index < num_modes; mode_index++)
    {
        mode new_mode;

        // 모드 이름 복사 (size + data)
        unsigned short modename_len;
        memcpy(&modename_len, &data_buf[data_ptr], sizeof(unsigned short));
        data_ptr += sizeof(unsigned short);

        new_mode.name = (char *)&data_buf[data_ptr];
        data_ptr += modename_len;

        // 모드 값 복사
        memcpy(&new_mode.value, &data_buf[data_ptr], sizeof(new_mode.value));
        data_ptr += sizeof(new_mode.value);

        // 모드 플래그
        memcpy(&new_mode.flags, &data_buf[data_ptr], sizeof(new_mode.flags));
        data_ptr += sizeof(new_mode.flags);

        // 모드 속도 최솟값 복사
        memcpy(&new_mode.speed_min, &data_buf[data_ptr], sizeof(new_mode.speed_min));
        data_ptr += sizeof(new_mode.speed_min);

        // 모드 속도 최댓값 복사
        memcpy(&new_mode.speed_max, &data_buf[data_ptr], sizeof(new_mode.speed_max));
        data_ptr += sizeof(new_mode.speed_max);

        // 모드 색 최솟값 복사
        memcpy(&new_mode.colors_min, &data_buf[data_ptr], sizeof(new_mode.colors_min));
        data_ptr += sizeof(new_mode.colors_min);

        // 모드 색 최댓값 복사
        memcpy(&new_mode.colors_max, &data_buf[data_ptr], sizeof(new_mode.colors_max));
        data_ptr += sizeof(new_mode.colors_max);

        // 모드 속도 복사
        memcpy(&new_mode.speed, &data_buf[data_ptr], sizeof(new_mode.speed));
        data_ptr += sizeof(new_mode.speed);

        // 모드 방향 복사
        memcpy(&new_mode.direction, &data_buf[data_ptr], sizeof(new_mode.direction));
        data_ptr += sizeof(new_mode.direction);

        // 모드 색 모드 복사
        memcpy(&new_mode.color_mode, &data_buf[data_ptr], sizeof(new_mode.color_mode));
        data_ptr += sizeof(new_mode.color_mode);

        // 모드 색 개수 복사
        unsigned short mode_num_colors;
        memcpy(&mode_num_colors, &data_buf[data_ptr], sizeof(unsigned short));
        data_ptr += sizeof(unsigned short);

        // 모드 모드 색 복사
        for(int color_index = 0; color_index < mode_num_colors; color_index++)
        {
            RGBColor new_color;
            memcpy(&new_color, &data_buf[data_ptr], sizeof(RGBColor));
            data_ptr += sizeof(modes[mode_index].colors[color_index]);

            new_mode.colors.push_back(new_color);
        }

        modes.push_back(new_mode);
    }

    // zone의 개수 복사
    unsigned short num_zones;
    memcpy(&num_zones, &data_buf[data_ptr], sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    // zone 복사
    for(int zone_index = 0; zone_index < num_zones; zone_index++)
    {
        zone new_zone;

        // zone 이름 복사 (size + data)
        unsigned short zonename_len;
        memcpy(&zonename_len, &data_buf[data_ptr], sizeof(unsigned short));
        data_ptr += sizeof(unsigned short);

        new_zone.name = (char *)&data_buf[data_ptr];
        data_ptr += zonename_len;

        // zone 타입 복사
        memcpy(&new_zone.type, &data_buf[data_ptr], sizeof(new_zone.type));
        data_ptr += sizeof(new_zone.type);

        // zone LED 최솟값 복사
        memcpy(&new_zone.leds_min, &data_buf[data_ptr], sizeof(new_zone.leds_min));
        data_ptr += sizeof(new_zone.leds_min);

        // zone LED 최댓값 복사
        memcpy(&new_zone.leds_max, &data_buf[data_ptr], sizeof(new_zone.leds_max));
        data_ptr += sizeof(new_zone.leds_max);

        // zone LED 개수 복사
        memcpy(&new_zone.leds_count, &data_buf[data_ptr], sizeof(new_zone.leds_count));
        data_ptr += sizeof(new_zone.leds_count);

        zones.push_back(new_zone);
    }

    // LED 개수 복사
    unsigned short num_leds;
    memcpy(&num_leds, &data_buf[data_ptr], sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    // LED 복사
    for(int led_index = 0; led_index < num_leds; led_index++)
    {
        led new_led;

        // LED 이름 복사 (size + data)
        unsigned short ledname_len;
        memcpy(&ledname_len, &data_buf[data_ptr], sizeof(unsigned short));
        data_ptr += sizeof(unsigned short);

        new_led.name = (char *)&data_buf[data_ptr];
        data_ptr += ledname_len;

        // LED 값 복사
        memcpy(&new_led.value, &data_buf[data_ptr], sizeof(new_led.value));
        data_ptr += sizeof(new_led.value);

        leds.push_back(new_led);
    }

    // 색 개수 복사
    unsigned short num_colors;
    memcpy(&num_colors, &data_buf[data_ptr], sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    // 색 복사
    for(int color_index = 0; color_index < num_colors; color_index++)
    {
        RGBColor new_color;

        memcpy(&new_color, &data_buf[data_ptr], sizeof(RGBColor));
        data_ptr += sizeof(RGBColor);

        colors.push_back(new_color);
    }
}

void RGBController::SetupColors()
{
    unsigned int total_led_count;

    // 기기의 LED 총 개수 결정
    total_led_count = 0;

    for(std::size_t zone_idx = 0; zone_idx < zones.size(); zone_idx++)
    {
        total_led_count += zones[zone_idx].leds_count;
    }

    // LED 수에 따른 색 버퍼 크기 설정
    colors.resize(total_led_count);

    // 각 zone에 따른 색 버퍼 포인터 지정
    total_led_count = 0;

    for(std::size_t zone_idx = 0; zone_idx < zones.size(); zone_idx++)
    {
        zones[zone_idx].start_idx=total_led_count;

        if((colors.size() > 0) && (zones[zone_idx].leds_count > 0))
        {
            zones[zone_idx].colors = &colors[total_led_count];
        }
        else
        {
            zones[zone_idx].colors = NULL;
        }

        if((leds.size() > 0) && (zones[zone_idx].leds_count > 0))
        {
            zones[zone_idx].leds   = &leds[total_led_count];
        }
        else
        {
            zones[zone_idx].leds    = NULL;
        }


        total_led_count += zones[zone_idx].leds_count;
    }
}

RGBColor RGBController::GetLED(unsigned int led)
{
    if(led < colors.size())
    {
        return(colors[led]);
    }
    else
    {
        return(0x00000000);
    }
}

void RGBController::SetLED(unsigned int led, RGBColor color)
{
    if(led < colors.size())
    {
        colors[led] = color;

        UpdateSingleLED(led);
    }
}

void RGBController::SetAllLEDs(RGBColor color)
{
    for(std::size_t zone_idx = 0; zone_idx < zones.size(); zone_idx++)
    {
        SetAllZoneLEDs(zone_idx, color);
    }

    UpdateLEDs();
}

void RGBController::SetAllZoneLEDs(int zone, RGBColor color)
{
    for (std::size_t color_idx = 0; color_idx < zones[zone].leds_count; color_idx++)
    {
        zones[zone].colors[color_idx] = color;
    }

    UpdateZoneLEDs(zone);
}

int RGBController::GetMode()
{
    return(active_mode);
}

void RGBController::SetMode(int mode)
{
    active_mode = mode;

    UpdateMode();
}

std::string device_type_to_str(device_type type)
{
    switch(type)
    {
    case DEVICE_TYPE_MOTHERBOARD:
        return "Motherboard";
    case DEVICE_TYPE_DRAM:
        return "DRAM";
    case DEVICE_TYPE_GPU:
        return "GPU";
    case DEVICE_TYPE_COOLER:
        return "Cooler";
    case DEVICE_TYPE_LEDSTRIP:
        return "LED Strip";
    case DEVICE_TYPE_KEYBOARD:
        return "Keyboard";
    case DEVICE_TYPE_MOUSE:
        return "Mouse";
    case DEVICE_TYPE_MOUSEMAT:
        return "Mousemat";
    case DEVICE_TYPE_HEADSET:
        return "Headset";
    default:
        return "Unknown";
    }
}
