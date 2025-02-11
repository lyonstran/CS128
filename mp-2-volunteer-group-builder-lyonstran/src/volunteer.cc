#include "volunteer.hpp"
Volunteer(const std::string& name, int building_experience, int physical_stamina, bool returning) {
        name_ = name;

        if (building_experience < kMinBuildingExp) {
            buildExp_ = kMinBuildingExp;
        } else if (building_experience > kMaxBuildingExp) {
            buildExp_ = kMaxBuildingExp;
        } else {
            buildExp_ = building_experience;
        }

        
        if (physical_stamina < kMinStamina) {
            staminaExp_ = kMinStamina;
        } else if (physical_stamina > kMaxStamina) {
            staminaExp_ = kMaxStamina;
        } else {
            staminaExp_ = physical_stamina;
        }

        
        if (returning) {
            ret_status_ = 1;
        } else {
            ret_status_ = 0;
        }
}

std::string Volunteer::GetName() const {
    return name_;
}
int Volunteer::GetBuildingExperience() const {
    return buildExp_;
}

int Volunteer::GetPhysicalStamina() const {
    return staminaExp_;
}

bool Volunteer::IsReturning() const {
    return ret_status_ != 0;
}