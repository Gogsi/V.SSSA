#include "natives.h"
#include "types.h"
#include "enums.h"
#include <set>
#include <string>
#include <format>
#include <Windows.h>
#include <Psapi.h>
#include "VehicleManager.h"
#include "utils.h"

void main()
{
	VehicleManager& vehicleManager = VehicleManager::getInstance();
	Hash lastFrameVehicleModel = 0;

	while (CAM::IS_SCREEN_FADED_OUT()) { WAIT(10); }
	ShowTheFeedNotification(std::format("Welcome to SSSA! There are {} vehicles to deliver", vehicleManager.getAvailableVehiclesCount()).c_str());

	//TODO: Load delivered vehicles data from savefile
	//TODO: Hook savefile serialization and save delivered vehicle data, likely in an unused MF_MISSION_STRUCT slot (96-99)

	while (true)
	{
		Player player = PLAYER::PLAYER_ID();
		Ped playerPed = PLAYER::PLAYER_PED_ID();

		Vehicle playerVehicle = PED::GET_VEHICLE_PED_IS_IN(playerPed, false);
		if (playerVehicle)
		{
			Hash vehicleModel = ENTITY::GET_ENTITY_MODEL(playerVehicle);

			if (vehicleModel != lastFrameVehicleModel) {
				ShowHelpText("This vehicle hasn't been delivered yet.",  "Bring it to ~y~Vespucci Beach Lifeguard Station~s~ or the ~y~Lighthouse~s~ to deliver it!");
			}

			// TODO: Add lighthouse as a delivery location. Extend/make more locations for planes and boats.
			if (ENTITY::IS_ENTITY_IN_AREA(playerVehicle, -1221.87, -1820.12, 0.0, -1190, -1742.88, 25.0, true, true, 0)) // Vespucci HQ
			{
				ENTITY::SET_ENTITY_AS_MISSION_ENTITY(playerVehicle, true, true);
				VEHICLE::DELETE_VEHICLE(&playerVehicle);

				if (!vehicleManager.deliverVehicle(vehicleModel)) continue;

				std::string vehicleName = std::string(HUD::_GET_LABEL_TEXT(VEHICLE::GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(vehicleModel)));

				std::string notification = std::format("You have delivered {}! {} / {} vehicles delivered.", vehicleName, vehicleManager.getDeliveredVehiclesCount(), vehicleManager.getAvailableVehiclesCount());
				ShowTheFeedNotification(notification.c_str());
			}

			lastFrameVehicleModel = vehicleModel;
		}
		else {
			lastFrameVehicleModel = 0;
		}

		WAIT(100);
	}
}

void ScriptMain()
{
	main();
}


BOOL APIENTRY DllMain(HMODULE hInstance, DWORD reason, LPVOID lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
		scriptRegister(hInstance, ScriptMain);
		break;
	case DLL_PROCESS_DETACH:
		scriptUnregister(hInstance);
		break;
	}
	return TRUE;
}
