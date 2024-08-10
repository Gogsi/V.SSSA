#pragma once

#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include "natives.h"
#include "VehicleList.h"
#include "utils.h"

class VehicleManager {
    std::vector<const char*> availableVehicleModels;

    std::set<Hash> deliveredVehicleModels;
public:
    static VehicleManager& getInstance()
    {
        static VehicleManager    instance;
        return instance;
    }
private:
    VehicleManager() {
        availableVehicleModels = std::vector<const char*>(50);

        std::copy_if(
            std::begin(allVehicleModels), 
            std::end(allVehicleModels), 
            std::back_inserter(availableVehicleModels), 
            [](const char* modelName) {
                bool isVehicle = STREAMING::IS_MODEL_A_VEHICLE(joaat(modelName)) != 0;
                return isVehicle;
            }
        );   
    }  

public:
    VehicleManager(VehicleManager const&) = delete;
    void operator=(VehicleManager const&) = delete;

    uint32_t getDeliveredVehiclesCount() {
        return deliveredVehicleModels.size();
    }

    uint32_t getAvailableVehiclesCount() {
        return availableVehicleModels.size();
    }

    bool deliverVehicle(Hash model) {
        if (deliveredVehicleModels.find(model) != deliveredVehicleModels.end()) return false;

        deliveredVehicleModels.insert(model);
        return true;
    }
};