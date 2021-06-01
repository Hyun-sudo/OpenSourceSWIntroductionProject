#include "ProfileManager.h"
#include "RGBController_Dummy.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <cstring>

namespace fs = std::filesystem;

ProfileManager::ProfileManager(std::vector<RGBController *>& control) : controllers(control)
{
    UpdateProfileList();
}

ProfileManager::~ProfileManager()
{

}

bool ProfileManager::SaveProfile(std::string profile_name)
{
    // 이름이 입력되면 프로필 파일을 저장함
    if(profile_name != "")
    {
        // 아웃풋 파일을 바이너리 모드로 열기
        std::ofstream controller_file(profile_name, std::ios::out | std::ios::binary);

        // 헤더 작성
        // 16 bytes - "RGBSYNC_PROFILE"
        // 4 bytes - Version, unsigned int
        unsigned int profile_version = 1;
        controller_file.write("RGBSYNC_PROFILE", 16);
        controller_file.write((char *)&profile_version, sizeof(unsigned int));

        // 각 컨트롤러 당 컨트롤러 데이터 쓰기
        for(std::size_t controller_index = 0; controller_index < controllers.size(); controller_index++)
        {
            unsigned char *controller_data = controllers[controller_index]->GetDeviceDescription();
            unsigned int controller_size;

            memcpy(&controller_size, controller_data, sizeof(controller_size));

            controller_file.write((const char *)controller_data, controller_size);
        }

        // 완료되면 파일 닫기
        controller_file.close();

        // 프로필 리스트 업데이트
        UpdateProfileList();

        return(true);
    }
    else
    {
        return(false);
    }
}

bool ProfileManager::LoadProfile(std::string profile_name)
{
    return(LoadProfileWithOptions(profile_name, false, true));
}

bool ProfileManager::LoadSizeFromProfile(std::string profile_name)
{
    return(LoadProfileWithOptions(profile_name, true, false));
}

bool ProfileManager::LoadProfileWithOptions
    (
    std::string     profile_name,
    bool            load_size,
    bool            load_settings
    )
{
    std::vector<RGBController*> temp_controllers;
    std::vector<bool>           temp_controller_used;
    unsigned int                controller_size;
    unsigned int                controller_offset = 0;
    bool                        ret_val = false;

    std::string filename = profile_name;

    // 인풋 파일을 바이너리 모드로 열기
    std::ifstream controller_file(filename, std::ios::in | std::ios::binary);

    // 파일 헤더 읽기 및 확인
    char            header_string[16];
    unsigned int    header_version;

    controller_file.read(header_string, 16);
    controller_file.read((char *)&header_version, sizeof(unsigned int));

    controller_offset += 16 + sizeof(unsigned int);
    controller_file.seekg(controller_offset);

    if(strcmp(header_string, "RGBSYNC_PROFILE") == 0)
    {
        if(header_version == 1)
        {
            // 컨트롤러 데이터를 EOF까지 읽기
            while(!(controller_file.peek() == EOF))
            {
                controller_file.read((char *)&controller_size, sizeof(controller_size));

                unsigned char *controller_data = new unsigned char[controller_size];

                controller_file.seekg(controller_offset);

                controller_file.read((char *)controller_data, controller_size);

                RGBController_Dummy *temp_controller = new RGBController_Dummy();

                temp_controller->ReadDeviceDescription(controller_data);

                temp_controllers.push_back(temp_controller);
                temp_controller_used.push_back(false);

                delete[] controller_data;

                controller_offset += controller_size;
                controller_file.seekg(controller_offset);

                ret_val = true;
            }

            // 저장된 모든 컨트롤러를 루프하면서 일치하는 것을 찾음
            for(std::size_t controller_index = 0; controller_index < controllers.size(); controller_index++)
            {
                RGBController *controller_ptr = controllers[controller_index];

                for(std::size_t temp_index = 0; temp_index < temp_controllers.size(); temp_index++)
                {
                    RGBController *temp_controller = temp_controllers[temp_index];

                    // 저장된 컨트롤러 데이터가 이 컨트롤러가 맞는지 확인
                    if((temp_controller_used[temp_index] == false                  )
                     &&(temp_controller->type        == controller_ptr->type       )
                     &&(temp_controller->name        == controller_ptr->name       )
                     &&(temp_controller->description == controller_ptr->description)
                     &&(temp_controller->version     == controller_ptr->version    )
                     &&(temp_controller->serial      == controller_ptr->serial     )
                     &&(temp_controller->location    == controller_ptr->location   ))
                    {
                        // 필요하면 zone 크기 업데이트
                        if(load_size)
                        {
                            if(temp_controller->zones.size() == controller_ptr->zones.size())
                            {
                                for(std::size_t zone_idx = 0; zone_idx < temp_controller->zones.size(); zone_idx++)
                                {
                                    if((temp_controller->zones[zone_idx].name       == controller_ptr->zones[zone_idx].name      )
                                     &&(temp_controller->zones[zone_idx].type       == controller_ptr->zones[zone_idx].type      )
                                     &&(temp_controller->zones[zone_idx].leds_min   == controller_ptr->zones[zone_idx].leds_min  )
                                     &&(temp_controller->zones[zone_idx].leds_max   == controller_ptr->zones[zone_idx].leds_max  )
                                     &&(temp_controller->zones[zone_idx].leds_count != controller_ptr->zones[zone_idx].leds_count))
                                    {
                                        controller_ptr->ResizeZone(zone_idx, temp_controller->zones[zone_idx].leds_count);
                                    }
                                }
                            }
                        }

                        // 필요하면 설정 업데이트
                        if(load_settings)
                        {
                            // 모든 모드 업데이트
                            if(temp_controller->modes.size() == controller_ptr->modes.size())
                            {
                                for(std::size_t mode_index = 0; mode_index < temp_controller->modes.size(); mode_index++)
                                {
                                    if((temp_controller->modes[mode_index].name       == controller_ptr->modes[mode_index].name      )
                                     &&(temp_controller->modes[mode_index].value      == controller_ptr->modes[mode_index].value     )
                                     &&(temp_controller->modes[mode_index].flags      == controller_ptr->modes[mode_index].flags     )
                                     &&(temp_controller->modes[mode_index].speed_min  == controller_ptr->modes[mode_index].speed_min )
                                     &&(temp_controller->modes[mode_index].speed_max  == controller_ptr->modes[mode_index].speed_max )
                                     &&(temp_controller->modes[mode_index].colors_min == controller_ptr->modes[mode_index].colors_min)
                                     &&(temp_controller->modes[mode_index].colors_max == controller_ptr->modes[mode_index].colors_max))
                                    {
                                        controller_ptr->modes[mode_index].speed      = temp_controller->modes[mode_index].speed;
                                        controller_ptr->modes[mode_index].direction  = temp_controller->modes[mode_index].direction;
                                        controller_ptr->modes[mode_index].color_mode = temp_controller->modes[mode_index].color_mode;

                                        controller_ptr->modes[mode_index].colors.resize(temp_controller->modes[mode_index].colors.size());

                                        for(std::size_t mode_color_index = 0; mode_color_index < temp_controller->modes[mode_index].colors.size(); mode_color_index++)
                                        {
                                            controller_ptr->modes[mode_index].colors[mode_color_index] = temp_controller->modes[mode_index].colors[mode_color_index];
                                        }
                                    }

                                }

                                controller_ptr->active_mode = temp_controller->active_mode;
                            }
                            // 모든 색 업데이트
                            if(temp_controller->colors.size() == controller_ptr->colors.size())
                            {
                                for(std::size_t color_index = 0; color_index < temp_controller->colors.size(); color_index++)
                                {
                                    controller_ptr->colors[color_index] = temp_controller->colors[color_index];
                                }
                            }

                            temp_controller_used[temp_index] = true;

                            break;
                        }
                    }
                }
            }
        }
    }

    return(ret_val);
}

void ProfileManager::DeleteProfile(std::string profile_name)
{
    remove(profile_name.c_str());

    UpdateProfileList();
}

void ProfileManager::UpdateProfileList()
{
    profile_list.clear();

    // 현재 디렉토리에서 확장자를 찾아서 프로필 로드
    for(const auto & entry : fs::directory_iterator("."))
    {
        std::string filename = entry.path().filename().string();

        if(filename.find(".orp") != std::string::npos)
        {
            // 인풋 파일을 바이너리 모드로 열기
            std::ifstream profile_file(filename, std::ios::in | std::ios::binary);

            // 헤더 파일 읽기 및 확인
            char            header_string[16];
            unsigned int    header_version;

            profile_file.read(header_string, 16);
            profile_file.read((char *)&header_version, sizeof(unsigned int));

            if(strcmp(header_string, "RGBSYNC_PROFILE") == 0)
            {
                if(header_version == 1)
                {
                    // 프로필을 리스트에 추가
                    profile_list.push_back(filename);
                }
            }

            profile_file.close();
        }
    }
}
