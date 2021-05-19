#include "RGBController.h"
#include <cstring>

using namespace std::chrono_literals;

RGBController::RGBController()
{
    DeviceThreadRunning = true;
    DeviceCallThread = new std::thread(&RGBController::DeviceCallThreadFunction, this);
}

RGBController::~RGBController()
{
    DeviceThreadRunning = false;
    DeviceCallThread->join();
    delete DeviceCallThread;
}

unsigned char * RGBController::GetDeviceDescription(unsigned int protocol_version)
{
    unsigned int data_ptr = 0;
    unsigned int data_size = 0;

    // 데이터 사이즈 계산
    unsigned short name_len = strlen(name.c_str()) + 1;
    unsigned short vendor_len = strlen(vendor.c_str()) + 1;
    unsigned short description_len = strlen(description.c_str()) + 1;
    unsigned short version_len = strlen(version.c_str()) + 1;
    unsigned short serial_len = strlen(serial.c_str()) + 1;
    unsigned short location_len = strlen(location.c_str()) + 1;
    unsigned short num_modes = modes.size();
    unsigned short num_zones = zones.size();
    unsigned short num_leds = leds.size();
    unsigned short num_colors = colors.size();

    unsigned short * mode_name_len = new unsigned short[num_modes];
    unsigned short * zone_name_len = new unsigned short[num_zones];
    unsigned short * led_name_len = new unsigned short[num_leds];

    unsigned short * zone_matrix_len = new unsigned short[num_zones];
    unsigned short * mode_num_colors = new unsigned short[num_modes];

    data_size += sizeof(data_size);
    data_size += sizeof(device_type);
    data_size += name_len + sizeof(name_len);

    if (protocol_version >= 1)
    {
        data_size += vendor_len + sizeof(vendor_len);
    }

    data_size += description_len + sizeof(description_len);
    data_size += version_len + sizeof(version_len);
    data_size += serial_len + sizeof(serial_len);
    data_size += location_len + sizeof(location_len);

    data_size += sizeof(num_modes);
    data_size += sizeof(active_mode);

    for (int mode_index = 0; mode_index < num_modes; mode_index++)
    {
        mode_name_len[mode_index] = strlen(modes[mode_index].name.c_str()) + 1;
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

    for (int zone_index = 0; zone_index < num_zones; zone_index++)
    {
        zone_name_len[zone_index] = strlen(zones[zone_index].name.c_str()) + 1;

        data_size += zone_name_len[zone_index] + sizeof(zone_name_len[zone_index]);
        data_size += sizeof(zones[zone_index].type);
        data_size += sizeof(zones[zone_index].leds_min);
        data_size += sizeof(zones[zone_index].leds_max);
        data_size += sizeof(zones[zone_index].leds_count);

        if (zones[zone_index].matrix_map == nullptr)
        {
            zone_matrix_len[zone_index] = 0;
        }
        else
        {
            zone_matrix_len[zone_index] = (2 * sizeof(unsigned int)) + (zones[zone_index].matrix_map->height * zones[zone_index].matrix_map->width * sizeof(unsigned int));
        }

        data_size += sizeof(zone_matrix_len[zone_index]);
        data_size += zone_matrix_len[zone_index];
    }

    data_size += sizeof(num_leds);

    for (int led_index = 0; led_index < num_leds; led_index++)
    {
        led_name_len[led_index] = strlen(leds[led_index].name.c_str()) + 1;

        data_size += led_name_len[led_index] + sizeof(led_name_len[led_index]);

        data_size += sizeof(leds[led_index].value);
    }

    data_size += sizeof(num_colors);
    data_size += num_colors * sizeof(RGBColor);

    // 데이터 버퍼 생성
    unsigned char * data_buf = new unsigned char[data_size];

    // 데이터 크기 복사
    memcpy(&data_buf[data_ptr], &data_size, sizeof(data_size));
    data_ptr += sizeof(data_size);

    // 타입 복사
    memcpy(&data_buf[data_ptr], &type, sizeof(device_type));
    data_ptr += sizeof(device_type);

    // 이름 복사 (size + data)
    memcpy(&data_buf[data_ptr], &name_len, sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    strcpy((char *)&data_buf[data_ptr], name.c_str());
    data_ptr += name_len;

    // 프로토콜이 1 이상이면, 회사 복사 (size + data)
    if (protocol_version >= 1)
    {
        memcpy(&data_buf[data_ptr], &vendor_len, sizeof(unsigned short));
        data_ptr += sizeof(unsigned short);

        strcpy((char *)&data_buf[data_ptr], vendor.c_str());
        data_ptr += vendor_len;
    }

    // 기기 설명 복사 (size + data)
    memcpy(&data_buf[data_ptr], &description_len, sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    strcpy((char *)&data_buf[data_ptr], description.c_str());
    data_ptr += description_len;

    // 기기 버전 복사 (size + data)
    memcpy(&data_buf[data_ptr], &version_len, sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    strcpy((char *)&data_buf[data_ptr], version.c_str());
    data_ptr += version_len;

    // 기기 시리얼 복사 (size + data)
    memcpy(&data_buf[data_ptr], &serial_len, sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    strcpy((char *)&data_buf[data_ptr], serial.c_str());
    data_ptr += serial_len;

    // 기기 위치 복사 (size + data)
    memcpy(&data_buf[data_ptr], &location_len, sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    strcpy((char *)&data_buf[data_ptr], location.c_str());
    data_ptr += location_len;

    // 기기 모드의 수 복사
    memcpy(&data_buf[data_ptr], &num_modes, sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    // 기기 활성화된 모드 복사
    memcpy(&data_buf[data_ptr], &active_mode, sizeof(active_mode));
    data_ptr += sizeof(active_mode);

    // 모드 복사
    for (int mode_index = 0; mode_index < num_modes; mode_index++)
    {
        // 모드 이름 복사 (size + data)
        memcpy(&data_buf[data_ptr], & mode_name_len[mode_index], sizeof(unsigned short));
        data_ptr += sizeof(unsigned short);

        strcpy((char * )&data_buf[data_ptr], modes[mode_index].name.c_str());
        data_ptr += mode_name_len[mode_index];

        // 모드 값 복사
        memcpy(&data_buf[data_ptr], &modes[mode_index].value, sizeof(modes[mode_index].value));
        data_ptr += sizeof(modes[mode_index].value);

        // 모드 플래그 복사
        memcpy(&data_buf[data_ptr], &modes[mode_index].flags, sizeof(modes[mode_index].flags));
        data_ptr += sizeof(modes[mode_index].flags);

        // 모드 스피드 최소값 복사
        memcpy(&data_buf[data_ptr], &modes[mode_index].speed_min, sizeof(modes[mode_index].speed_min));
        data_ptr += sizeof(modes[mode_index]).speed_min;

        //모드 스피드 최대값 복사
        memcpy(&data_buf[data_ptr], &modes[mode_index].speed_max, sizeof(modes[mode_index].speed_max));
        data_ptr += sizeof(modes[mode_index].speed_max);

        // 색 최소값 복사
        memcpy(&data_buf[data_ptr], &modes[mode_index].colors_min, sizeof(modes[mode_index].colors_min));
        data_ptr += sizeof(modes[mode_index].colors_min);

        // 색 최대값 복사
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

        // 색의 수 복사
        memcpy(&data_buf[data_ptr], &mode_num_colors[mode_index], sizeof(unsigned short));
        data_ptr += sizeof(unsigned short);

        // 모드의 모드 색 복사
        for (int color_index = 0; color_index < mode_num_colors[mode_index]; color_index++)
        {
            // 색 복사
            memcpy(&data_buf[data_ptr], &modes[mode_index].colors[color_index], sizeof(modes[mode_index].colors[color_index]));
            data_ptr += sizeof(modes[mode_index].colors[color_index]);
        }
    }

    // zone의 수 복사
    memcpy(&data_buf[data_ptr], &num_zones, sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    // zone 복사
    for (int zone_index = 0; zone_index < num_zones; zone_index++)
    {
        // zone 이름 복사 (size + data)
        memcpy(&data_buf[data_ptr], &zone_name_len[zone_index], sizeof(unsigned short));
        data_ptr += sizeof(unsigned short);

        strcpy((char *)&data_buf[data_ptr], zones[zone_index].name.c_str());
        data_ptr += zone_name_len[zone_index];

        // zone type 복사
        memcpy(&data_buf[data_ptr], &zones[zone_index].type, sizeof(zones[zone_index].type));
        data_ptr += sizeof(zones[zone_index].type);

        // zone의 최소 LED 수 복사
        memcpy(&data_buf[data_ptr], &zones[zone_index].leds_min, sizeof(zones[zone_index].leds_min));
        data_ptr += sizeof(zones[zone_index].leds_min);

        // zone의 최대 LED 수 복사
        memcpy(&data_buf[data_ptr], &zones[zone_index].leds_max, sizeof(zones[zone_index].leds_max));
        data_ptr += sizeof(zones[zone_index].leds_max);

        // zone의 LED 수 복사
        memcpy(&data_buf[data_ptr], &zones[zone_index].leds_count, sizeof(zones[zone_index].leds_count));
        data_ptr += sizeof(zones[zone_index].leds_count);

        // zone matrix 복사
        memcpy(&data_buf[data_ptr], &zone_matrix_len[zone_index], sizeof(zone_matrix_len[zone_index]));
        data_ptr += sizeof(zone_matrix_len[zone_index]);

        // matrix의 데이터의 크기가 0 초과일 때 복사
        if (zone_matrix_len[zone_index] > 0)
        {
            // matrix height 복사
            memcpy(&data_buf[data_ptr], &zones[zone_index].matrix_map->height, sizeof(zones[zone_index].matrix_map->height));
            data_ptr += sizeof(zones[zone_index].matrix_map->height);

            // matrix widght 복사
            memcpy(&data_buf[data_ptr], &zones[zone_index].matrix_map->width, sizeof(zones[zone_index].matrix_map->width));
            data_ptr += sizeof(zones[zone_index].matrix_map->width);

            // matrix map 복사
            for(unsigned int matrix_idx = 0; matrix_idx < (zones[zone_index].matrix_map->height * zones[zone_index].matrix_map->width); matrix_idx++)
            {
                memcpy(&data_buf[data_ptr], &zones[zone_index].matrix_map->map[matrix_idx], sizeof(zones[zone_index].matrix_map->map[matrix_idx]));
                data_ptr += sizeof(zones[zone_index].matrix_map->map[matrix_idx]);
            }
        }
    }
    // LED 수 복사
    memcpy(&data_buf[data_ptr], &num_leds, sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    // LED 복사
    for (int led_index = 0; led_index < num_leds; led_index++)
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

    // 색의 수 복사
    memcpy(&data_buf[data_ptr], &num_colors, sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    // 색 복사
    for(int color_index = 0; color_index < num_colors; color_index++)
    {
        // 색 복사
        memcpy(&data_buf[data_ptr], &colors[color_index], sizeof(colors[color_index]));
        data_ptr += sizeof(colors[color_index]);
    }

    delete[] mode_name_len;
    delete[] zone_name_len;
    delete[] led_name_len;

    delete[] zone_matrix_len;
    delete[] mode_num_colors;

    return (data_buf);
}

void RGBController::ReadDeviceDescription(unsigned char *data_buf, unsigned int protocol_version)
{
    unsigned int data_ptr = 0;
    data_ptr += sizeof(unsigned int);

    // 타입 복사
    memcpy(&type, &data_buf[data_ptr], sizeof(device_type));
    data_ptr += sizeof(device_type);

    // 이름 복사
    unsigned short name_len;
    memcpy(&name_len, &data_buf[data_ptr], sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    name = (char *)&data_buf[data_ptr];
    data_ptr += name_len;

    // 프로필의 버전이 1이상이면 회사 복사
    if(protocol_version >= 1)
    {
        unsigned short vendor_len;
        memcpy(&vendor_len, &data_buf[data_ptr], sizeof(unsigned short));
        data_ptr += sizeof(unsigned short);

        vendor = (char *)&data_buf[data_ptr];
        data_ptr += vendor_len;
    }

    // 기기 설명 복사
    unsigned short description_len;
    memcpy(&description_len, &data_buf[data_ptr], sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    description = (char *)&data_buf[data_ptr];
    data_ptr += description_len;

    // 버전 복사
    unsigned short version_len;
    memcpy(&version_len, &data_buf[data_ptr], sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    version = (char *)&data_buf[data_ptr];
    data_ptr += version_len;

    // 시리얼 복사
    unsigned short serial_len;
    memcpy(&serial_len, &data_buf[data_ptr], sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    serial = (char *)&data_buf[data_ptr];
    data_ptr += serial_len;

    // 위치 복사
    unsigned short location_len;
    memcpy(&location_len, &data_buf[data_ptr], sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    location = (char *)&data_buf[data_ptr];
    data_ptr += location_len;

    // 모드의 수 복사
    unsigned short num_modes;
    memcpy(&num_modes, &data_buf[data_ptr], sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    // 활성화된 모드 복사
    memcpy(&active_mode, &data_buf[data_ptr], sizeof(active_mode));
    data_ptr += sizeof(active_mode);

    // 모드 복사
    for(int mode_index = 0; mode_index < num_modes; mode_index++)
    {
        mode new_mode;

        // 모드 이름 복사
        unsigned short modename_len;
        memcpy(&modename_len, &data_buf[data_ptr], sizeof(unsigned short));
        data_ptr += sizeof(unsigned short);

        new_mode.name = (char *)&data_buf[data_ptr];
        data_ptr += modename_len;

        // 모드 값 복사
        memcpy(&new_mode.value, &data_buf[data_ptr], sizeof(new_mode.value));
        data_ptr += sizeof(new_mode.value);

        // 모드 플래그 복사
        memcpy(&new_mode.flags, &data_buf[data_ptr], sizeof(new_mode.flags));
        data_ptr += sizeof(new_mode.flags);

        // 모드 속도 최소값 복사
        memcpy(&new_mode.speed_min, &data_buf[data_ptr], sizeof(new_mode.speed_min));
        data_ptr += sizeof(new_mode.speed_min);

        // 모드 속도 최대값 복사
        memcpy(&new_mode.speed_max, &data_buf[data_ptr], sizeof(new_mode.speed_max));
        data_ptr += sizeof(new_mode.speed_max);

        // 모드 색의 수 최소값 복사
        memcpy(&new_mode.colors_min, &data_buf[data_ptr], sizeof(new_mode.colors_min));
        data_ptr += sizeof(new_mode.colors_min);

        // 모드 색의 수 최대값 복사
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

        // 모드 색의 수 복사
        unsigned short mode_num_colors;
        memcpy(&mode_num_colors, &data_buf[data_ptr], sizeof(unsigned short));
        data_ptr += sizeof(unsigned short);

        // 모드 모드 색 복사
        for(int color_index = 0; color_index < mode_num_colors; color_index++)
        {
            // 색 복사
            RGBColor new_color;
            memcpy(&new_color, &data_buf[data_ptr], sizeof(RGBColor));
            data_ptr += sizeof(modes[mode_index].colors[color_index]);

            new_mode.colors.push_back(new_color);
        }

        modes.push_back(new_mode);
    }

    // zone의 수 복사
    unsigned short num_zones;
    memcpy(&num_zones, &data_buf[data_ptr], sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);


    for(int zone_index = 0; zone_index < num_zones; zone_index++)
    {
        zone new_zone;

       // zone 이름 복사
        unsigned short zonename_len;
        memcpy(&zonename_len, &data_buf[data_ptr], sizeof(unsigned short));
        data_ptr += sizeof(unsigned short);

        new_zone.name = (char *)&data_buf[data_ptr];
        data_ptr += zonename_len;

        // zone type 복사
        memcpy(&new_zone.type, &data_buf[data_ptr], sizeof(new_zone.type));
        data_ptr += sizeof(new_zone.type);

        // 최소 LED 수 복사
        memcpy(&new_zone.leds_min, &data_buf[data_ptr], sizeof(new_zone.leds_min));
        data_ptr += sizeof(new_zone.leds_min);

       // 최대 LED 수 복사
        memcpy(&new_zone.leds_max, &data_buf[data_ptr], sizeof(new_zone.leds_max));
        data_ptr += sizeof(new_zone.leds_max);

        // LED 수 복사
        memcpy(&new_zone.leds_count, &data_buf[data_ptr], sizeof(new_zone.leds_count));
        data_ptr += sizeof(new_zone.leds_count);

        // zone matrix 복사
        unsigned short zone_matrix_len;
        memcpy(&zone_matrix_len, &data_buf[data_ptr], sizeof(zone_matrix_len));
        data_ptr += sizeof(zone_matrix_len);

        // matrix의 데이터 사이즈가 0 보다 크면 복사
        if(zone_matrix_len > 0)
        {
            // 새로운 zone에 붙일 map 데이터 구조를 만듦
            matrix_map_type * new_map = new matrix_map_type;

            new_zone.matrix_map = new_map;

            // matrix height 복사
            memcpy(&new_map->height, &data_buf[data_ptr], sizeof(new_map->height));
            data_ptr += sizeof(new_map->height);

            // matrix width 복사
            memcpy(&new_map->width, &data_buf[data_ptr], sizeof(new_map->width));
            data_ptr += sizeof(new_map->width);

            // matrix map 복사
            new_map->map = new unsigned int[new_map->height * new_map->width];

            for(unsigned int matrix_idx = 0; matrix_idx < (new_map->height * new_map->width); matrix_idx++)
            {
                memcpy(&new_map->map[matrix_idx], &data_buf[data_ptr], sizeof(new_map->map[matrix_idx]));
                data_ptr += sizeof(new_map->map[matrix_idx]);
            }
        }
        else
        {
            new_zone.matrix_map = NULL;
        }

        zones.push_back(new_zone);
    }

    // LED 수 복사
    unsigned short num_leds;
    memcpy(&num_leds, &data_buf[data_ptr], sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    // LED 복사
    for(int led_index = 0; led_index < num_leds; led_index++)
    {
        led new_led;

        // LED 이름 복사
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

    // 색의 수 복사
    unsigned short num_colors;
    memcpy(&num_colors, &data_buf[data_ptr], sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    // 색 복사
    for(int color_index = 0; color_index < num_colors; color_index++)
    {
        RGBColor new_color;

        // 색 복사
        memcpy(&new_color, &data_buf[data_ptr], sizeof(RGBColor));
        data_ptr += sizeof(RGBColor);

        colors.push_back(new_color);
    }

    // 색 설정
    SetupColors();
}

unsigned char * RGBController::GetModeDescription(int mode)
{
    unsigned int data_ptr = 0;
    unsigned int data_size = 0;

    unsigned short mode_name_len;
    unsigned short mode_num_colors;

    // 데이터 크기 계산
    mode_name_len   = strlen(modes[mode].name.c_str()) + 1;
    mode_num_colors = modes[mode].colors.size();

    data_size += sizeof(data_size);
    data_size += sizeof(mode);
    data_size += sizeof(mode_name_len);
    data_size += mode_name_len;
    data_size += sizeof(modes[mode].value);
    data_size += sizeof(modes[mode].flags);
    data_size += sizeof(modes[mode].speed_min);
    data_size += sizeof(modes[mode].speed_max);
    data_size += sizeof(modes[mode].colors_min);
    data_size += sizeof(modes[mode].colors_max);
    data_size += sizeof(modes[mode].speed);
    data_size += sizeof(modes[mode].direction);
    data_size += sizeof(modes[mode].color_mode);
    data_size += sizeof(mode_num_colors);
    data_size += (mode_num_colors * sizeof(RGBColor));

    // 데이터 버퍼 생성
    unsigned char *data_buf = new unsigned char[data_size];

    // 데이터 크기 복사
    memcpy(&data_buf[data_ptr], &data_size, sizeof(data_size));
    data_ptr += sizeof(data_size);

    // 모드 인덱스 복사
    memcpy(&data_buf[data_ptr], &mode, sizeof(int));
    data_ptr += sizeof(int);

    // 모드 이름 복사 (size + data)
    memcpy(&data_buf[data_ptr], &mode_name_len, sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    strcpy((char *)&data_buf[data_ptr], modes[mode].name.c_str());
    data_ptr += mode_name_len;

    // 모드 값 복사
    memcpy(&data_buf[data_ptr], &modes[mode].value, sizeof(modes[mode].value));
    data_ptr += sizeof(modes[mode].value);

    // 모드 플래그 복사
    memcpy(&data_buf[data_ptr], &modes[mode].flags, sizeof(modes[mode].flags));
    data_ptr += sizeof(modes[mode].flags);

    // 모드 속도 최소값 복사
    memcpy(&data_buf[data_ptr], &modes[mode].speed_min, sizeof(modes[mode].speed_min));
    data_ptr += sizeof(modes[mode].speed_min);

    // 모드 속도 최대값 복사
    memcpy(&data_buf[data_ptr], &modes[mode].speed_max, sizeof(modes[mode].speed_max));
    data_ptr += sizeof(modes[mode].speed_max);

    // 모드 색 최소값 복사
    memcpy(&data_buf[data_ptr], &modes[mode].colors_min, sizeof(modes[mode].colors_min));
    data_ptr += sizeof(modes[mode].colors_min);

    // 모드 색 최대값 복사
    memcpy(&data_buf[data_ptr], &modes[mode].colors_max, sizeof(modes[mode].colors_max));
    data_ptr += sizeof(modes[mode].colors_max);

    // 모드 속도 복사
    memcpy(&data_buf[data_ptr], &modes[mode].speed, sizeof(modes[mode].speed));
    data_ptr += sizeof(modes[mode].speed);

    // 모드 방향 복사
    memcpy(&data_buf[data_ptr], &modes[mode].direction, sizeof(modes[mode].direction));
    data_ptr += sizeof(modes[mode].direction);

    // 모드 색 모드 복사
    memcpy(&data_buf[data_ptr], &modes[mode].color_mode, sizeof(modes[mode].color_mode));
    data_ptr += sizeof(modes[mode].color_mode);

    // 모드 색의 수 복사
    memcpy(&data_buf[data_ptr], &mode_num_colors, sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    // 모드 색 복사
    for(int color_index = 0; color_index < mode_num_colors; color_index++)
    {
        // 모드 색 복사
        memcpy(&data_buf[data_ptr], &modes[mode].colors[color_index], sizeof(modes[mode].colors[color_index]));
        data_ptr += sizeof(modes[mode].colors[color_index]);
    }

    return(data_buf);
}


void RGBController::SetModeDescription(unsigned char* data_buf)
{
    int mode_idx;
    unsigned int data_ptr = sizeof(unsigned int);

    /*---------------------------------------------------------*\
    | Copy in mode index                                        |
    \*---------------------------------------------------------*/
    memcpy(&mode_idx, &data_buf[data_ptr], sizeof(int));
    data_ptr += sizeof(int);

    /*---------------------------------------------------------*\
    | Check if we aren't reading beyond the list of modes.      |
    \*---------------------------------------------------------*/
    if(((size_t) mode_idx) >  modes.size())
    {
        return;
    }

    /*---------------------------------------------------------*\
    | Get pointer to target mode                                |
    \*---------------------------------------------------------*/
    mode * new_mode = &modes[mode_idx];

    /*---------------------------------------------------------*\
    | Set active mode to the new mode                           |
    \*---------------------------------------------------------*/
    active_mode = mode_idx;

    /*---------------------------------------------------------*\
    | Copy in mode name (size+data)                             |
    \*---------------------------------------------------------*/
    unsigned short modename_len;
    memcpy(&modename_len, &data_buf[data_ptr], sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    new_mode->name = (char *)&data_buf[data_ptr];
    data_ptr += modename_len;

    /*---------------------------------------------------------*\
    | Copy in mode value (data)                                 |
    \*---------------------------------------------------------*/
    memcpy(&new_mode->value, &data_buf[data_ptr], sizeof(new_mode->value));
    data_ptr += sizeof(new_mode->value);

    /*---------------------------------------------------------*\
    | Copy in mode flags (data)                                 |
    \*---------------------------------------------------------*/
    memcpy(&new_mode->flags, &data_buf[data_ptr], sizeof(new_mode->flags));
    data_ptr += sizeof(new_mode->flags);

    /*---------------------------------------------------------*\
    | Copy in mode speed_min (data)                             |
    \*---------------------------------------------------------*/
    memcpy(&new_mode->speed_min, &data_buf[data_ptr], sizeof(new_mode->speed_min));
    data_ptr += sizeof(new_mode->speed_min);

    /*---------------------------------------------------------*\
    | Copy in mode speed_max (data)                             |
    \*---------------------------------------------------------*/
    memcpy(&new_mode->speed_max, &data_buf[data_ptr], sizeof(new_mode->speed_max));
    data_ptr += sizeof(new_mode->speed_max);

    /*---------------------------------------------------------*\
    | Copy in mode colors_min (data)                            |
    \*---------------------------------------------------------*/
    memcpy(&new_mode->colors_min, &data_buf[data_ptr], sizeof(new_mode->colors_min));
    data_ptr += sizeof(new_mode->colors_min);

    /*---------------------------------------------------------*\
    | Copy in mode colors_max (data)                            |
    \*---------------------------------------------------------*/
    memcpy(&new_mode->colors_max, &data_buf[data_ptr], sizeof(new_mode->colors_max));
    data_ptr += sizeof(new_mode->colors_max);

    /*---------------------------------------------------------*\
    | Copy in mode speed (data)                                 |
    \*---------------------------------------------------------*/
    memcpy(&new_mode->speed, &data_buf[data_ptr], sizeof(new_mode->speed));
    data_ptr += sizeof(new_mode->speed);

    /*---------------------------------------------------------*\
    | Copy in mode direction (data)                             |
    \*---------------------------------------------------------*/
    memcpy(&new_mode->direction, &data_buf[data_ptr], sizeof(new_mode->direction));
    data_ptr += sizeof(new_mode->direction);

    /*---------------------------------------------------------*\
    | Copy in mode color_mode (data)                            |
    \*---------------------------------------------------------*/
    memcpy(&new_mode->color_mode, &data_buf[data_ptr], sizeof(new_mode->color_mode));
    data_ptr += sizeof(new_mode->color_mode);

    /*---------------------------------------------------------*\
    | Copy in mode number of colors                             |
    \*---------------------------------------------------------*/
    unsigned short mode_num_colors;
    memcpy(&mode_num_colors, &data_buf[data_ptr], sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    /*---------------------------------------------------------*\
    | Copy in mode mode colors                                  |
    \*---------------------------------------------------------*/
    new_mode->colors.clear();
    for(int color_index = 0; color_index < mode_num_colors; color_index++)
    {
        /*---------------------------------------------------------*\
        | Copy in color (data)                                      |
        \*---------------------------------------------------------*/
        RGBColor new_color;
        memcpy(&new_color, &data_buf[data_ptr], sizeof(RGBColor));
        data_ptr += sizeof(RGBColor);

        new_mode->colors.push_back(new_color);
    }
}

unsigned char * RGBController::GetColorDescription()
{
    unsigned int data_ptr = 0;
    unsigned int data_size = 0;

    unsigned short num_colors = colors.size();

    /*---------------------------------------------------------*\
    | Calculate data size                                       |
    \*---------------------------------------------------------*/
    data_size += sizeof(data_size);
    data_size += sizeof(num_colors);
    data_size += num_colors * sizeof(RGBColor);

    /*---------------------------------------------------------*\
    | Create data buffer                                        |
    \*---------------------------------------------------------*/
    unsigned char *data_buf = new unsigned char[data_size];

    /*---------------------------------------------------------*\
    | Copy in data size                                         |
    \*---------------------------------------------------------*/
    memcpy(&data_buf[data_ptr], &data_size, sizeof(data_size));
    data_ptr += sizeof(data_size);

    /*---------------------------------------------------------*\
    | Copy in number of colors (data)                           |
    \*---------------------------------------------------------*/
    memcpy(&data_buf[data_ptr], &num_colors, sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    /*---------------------------------------------------------*\
    | Copy in colors                                            |
    \*---------------------------------------------------------*/
    for(int color_index = 0; color_index < num_colors; color_index++)
    {
        /*---------------------------------------------------------*\
        | Copy in color (data)                                      |
        \*---------------------------------------------------------*/
        memcpy(&data_buf[data_ptr], &colors[color_index], sizeof(colors[color_index]));
        data_ptr += sizeof(colors[color_index]);
    }

    return(data_buf);
}

void RGBController::SetColorDescription(unsigned char* data_buf)
{
    unsigned int data_ptr = sizeof(unsigned int);

    /*---------------------------------------------------------*\
    | Copy in number of colors (data)                           |
    \*---------------------------------------------------------*/
    unsigned short num_colors;
    memcpy(&num_colors, &data_buf[data_ptr], sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    /*---------------------------------------------------------*\
    | Check if we aren't reading beyond the list of colors.     |
    \*---------------------------------------------------------*/
    if(((size_t) num_colors) > colors.size())
    {
        return;
    }

    /*---------------------------------------------------------*\
    | Copy in colors                                            |
    \*---------------------------------------------------------*/
    for(int color_index = 0; color_index < num_colors; color_index++)
    {
        RGBColor new_color;

        /*---------------------------------------------------------*\
        | Copy in color (data)                                      |
        \*---------------------------------------------------------*/
        memcpy(&new_color, &data_buf[data_ptr], sizeof(RGBColor));
        data_ptr += sizeof(RGBColor);

        colors[color_index] = new_color;
    }
}

unsigned char * RGBController::GetZoneColorDescription(int zone)
{
    unsigned int data_ptr = 0;
    unsigned int data_size = 0;

    unsigned short num_colors = zones[zone].leds_count;

    /*---------------------------------------------------------*\
    | Calculate data size                                       |
    \*---------------------------------------------------------*/
    data_size += sizeof(data_size);
    data_size += sizeof(zone);
    data_size += sizeof(num_colors);
    data_size += num_colors * sizeof(RGBColor);

    /*---------------------------------------------------------*\
    | Create data buffer                                        |
    \*---------------------------------------------------------*/
    unsigned char *data_buf = new unsigned char[data_size];

    /*---------------------------------------------------------*\
    | Copy in data size                                         |
    \*---------------------------------------------------------*/
    memcpy(&data_buf[data_ptr], &data_size, sizeof(data_size));
    data_ptr += sizeof(data_size);

    /*---------------------------------------------------------*\
    | Copy in zone index                                        |
    \*---------------------------------------------------------*/
    memcpy(&data_buf[data_ptr], &zone, sizeof(zone));
    data_ptr += sizeof(zone);

    /*---------------------------------------------------------*\
    | Copy in number of colors (data)                           |
    \*---------------------------------------------------------*/
    memcpy(&data_buf[data_ptr], &num_colors, sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    /*---------------------------------------------------------*\
    | Copy in colors                                            |
    \*---------------------------------------------------------*/
    for(int color_index = 0; color_index < num_colors; color_index++)
    {
        /*---------------------------------------------------------*\
        | Copy in color (data)                                      |
        \*---------------------------------------------------------*/
        memcpy(&data_buf[data_ptr], &zones[zone].colors[color_index], sizeof(zones[zone].colors[color_index]));
        data_ptr += sizeof(zones[zone].colors[color_index]);
    }

    return(data_buf);
}

void RGBController::SetZoneColorDescription(unsigned char *data_buf)
{
    unsigned int data_ptr = sizeof(unsigned int);
    unsigned int zone_idx;

    /*---------------------------------------------------------*\
    | Copy in zone index                                        |
    \*---------------------------------------------------------*/
    memcpy(&zone_idx, &data_buf[data_ptr], sizeof(zone_idx));
    data_ptr += sizeof(zone_idx);

    /*---------------------------------------------------------*\
    | Check if we aren't reading beyond the list of zones.      |
    \*---------------------------------------------------------*/
    if(((size_t) zone_idx) > zones.size())
    {
        return;
    }

    /*---------------------------------------------------------*\
    | Copy in number of colors (data)                           |
    \*---------------------------------------------------------*/
    unsigned short num_colors;
    memcpy(&num_colors, &data_buf[data_ptr], sizeof(unsigned short));
    data_ptr += sizeof(unsigned short);

    /*---------------------------------------------------------*\
    | Copy in colors                                            |
    \*---------------------------------------------------------*/
    for(int color_index = 0; color_index < num_colors; color_index++)
    {
        RGBColor new_color;

        /*---------------------------------------------------------*\
        | Copy in color (data)                                      |
        \*---------------------------------------------------------*/
        memcpy(&new_color, &data_buf[data_ptr], sizeof(RGBColor));
        data_ptr += sizeof(RGBColor);

        zones[zone_idx].colors[color_index] = new_color;
    }
}

unsigned char * RGBController::GetSingleLEDColorDescription(int led)
{
    /*---------------------------------------------------------*\
    | Fixed size descrption:                                    |
    |       int:      LED index                                 |
    |       RGBColor: LED color                                 |
    \*---------------------------------------------------------*/
    unsigned char *data_buf = new unsigned char[sizeof(int) + sizeof(RGBColor)];

    /*---------------------------------------------------------*\
    | Copy in LED index                                         |
    \*---------------------------------------------------------*/
    memcpy(&data_buf[0], &led, sizeof(int));

    /*---------------------------------------------------------*\
    | Copy in LED color                                         |
    \*---------------------------------------------------------*/
    memcpy(&data_buf[sizeof(led)], &colors[led], sizeof(RGBColor));

    return(data_buf);
}

void RGBController::SetSingleLEDColorDescription(unsigned char* data_buf)
{
    /*---------------------------------------------------------*\
    | Fixed size descrption:                                    |
    |       int:      LED index                                 |
    |       RGBColor: LED color                                 |
    \*---------------------------------------------------------*/
    int led_idx;

    /*---------------------------------------------------------*\
    | Copy in LED index                                         |
    \*---------------------------------------------------------*/
    memcpy(&led_idx, &data_buf[0], sizeof(led_idx));

    /*---------------------------------------------------------*\
    | Check if we aren't reading beyond the list of leds.       |
    \*---------------------------------------------------------*/
    if(((size_t) led_idx) > leds.size())
    {
        return;
    }

    /*---------------------------------------------------------*\
    | Copy in LED color                                         |
    \*---------------------------------------------------------*/
    memcpy(&colors[led_idx], &data_buf[sizeof(led_idx)], sizeof(RGBColor));
}

void RGBController::SetupColors()
{
    unsigned int total_led_count;

    /*---------------------------------------------------------*\
    | Determine total number of LEDs on the device              |
    \*---------------------------------------------------------*/
    total_led_count = 0;

    for(std::size_t zone_idx = 0; zone_idx < zones.size(); zone_idx++)
    {
        total_led_count += zones[zone_idx].leds_count;
    }

    /*---------------------------------------------------------*\
    | Set the size of the color buffer to the number of LEDs    |
    \*---------------------------------------------------------*/
    colors.resize(total_led_count);

    /*---------------------------------------------------------*\
    | Set the color buffer pointers on each zone                |
    \*---------------------------------------------------------*/
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
    }
}

void RGBController::SetAllLEDs(RGBColor color)
{
    for(std::size_t zone_idx = 0; zone_idx < zones.size(); zone_idx++)
    {
        SetAllZoneLEDs(zone_idx, color);
    }
}

void RGBController::SetAllZoneLEDs(int zone, RGBColor color)
{
    for (std::size_t color_idx = 0; color_idx < zones[zone].leds_count; color_idx++)
    {
        zones[zone].colors[color_idx] = color;
    }
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

void RGBController::RegisterUpdateCallBack(RGBControllerCallback new_callback, void *new_callback_arg)
{
    UpdateCallbacks.push_back(new_callback);
    UpdateCallbackArgs.push_back(new_callback_arg);
}

void RGBController::UnregisterUpdateCallback(void * callback_arg)
{
    for(unsigned int callback_idx = 0; callback_idx < UpdateCallbackArgs.size(); callback_idx++ )
    {
        if(UpdateCallbackArgs[callback_idx] == callback_arg)
        {
            UpdateCallbackArgs.erase(UpdateCallbackArgs.begin() + callback_idx);
            UpdateCallbacks.erase(UpdateCallbacks.begin() + callback_idx);

            break;
        }
    }
}

void RGBController::SignalUpdate()
{
    UpdateMutex.lock();

    // 클라이언트 정보가 바뀌면 callback 호출
    for(unsigned int callback_idx = 0; callback_idx < UpdateCallbacks.size(); callback_idx++)
    {
        UpdateCallbacks[callback_idx](UpdateCallbackArgs[callback_idx]);
    }

    UpdateMutex.unlock();
}
void RGBController::UpdateLEDs()
{
    CallFlag_UpdateLEDs = true;

    SignalUpdate();
}

void RGBController::UpdateMode()
{
    CallFalg_UpdateMode = true;
}

void RGBController::DeviceUpdateLEDs()
{

}

void RGBController::DeviceUpdateMode()
{

}

void RGBController::DeviceCallThreadFunction()
{
    CallFlag_UpdateLEDs = false;
    CallFalg_UpdateMode = false;

    while(DeviceThreadRunning.load() == true)
    {
        if(CallFalg_UpdateMode.load() == false)
        {
            DeviceUpdateMode();
            CallFalg_UpdateMode = false;
        }
        if(CallFlag_UpdateLEDs.load() == true)
        {
            DeviceUpdateLEDs();
            CallFlag_UpdateLEDs = false;
        }
        else
        {
           std::this_thread::sleep_for(1ms);
        }
    }
}

std::string device_type_to_str(device_type type)
{
    switch(type)
    {
    case DEVICE_TYPE_MOTHERBOARD:
        return "Motherboard";
    case DEVICE_TYPE_DRAM:
        return "DRAM";
    case DEVICE_TYPE_MOUSE:
        return "Mouse";
    default:
        return "Unknown";
    }
}
