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



    return (data_buf);
}
