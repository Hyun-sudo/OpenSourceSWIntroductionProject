/*
 * Settings Manager는 JSON 포멧으로 어플리케이션의 설정 목록을 관리한다.
 * 다른 요소들이 여기의 클래스를 통해 설정을 등록하고 값을 저장하거나 로드할 수 있다.
*/

#pragma once

#include "json/json.hpp"

using json = nlohmann::json;

class SettingsManager
{
public:
    SettingsManager();
    ~SettingsManager();

    json    GetSettings(std::string settings_key);
    void    SetSettings(std::string settings_key, json new_settings);

    void    LoadSettings(std::string filename);
    void    SaveSettings();


private:
    json        settings_data;
    json        settings_prototype;
    std::string settings_filename;
};
