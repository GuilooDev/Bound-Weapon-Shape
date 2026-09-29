#include "ShapeChange.h"
#include "logger.h"

namespace ShapeChange {

    namespace {
        std::vector<RE::TESObjectWEAP*> oneHSwordsList;
    }

    void initWeaponsLists() { 
        auto* dataHandler = RE::TESDataHandler::GetSingleton();

        if (!dataHandler) {
            logger::error("No data handler found!");
            return;
        
        }
        logger::info("Initialisation started");

        auto& weapons = dataHandler->GetFormArray<RE::TESObjectWEAP>();
        for (auto* weapon : weapons) {
            if (!weapon) continue;
            auto weaponType = weapon->GetWeaponType();

            switch (weaponType) {
                case RE::WEAPON_TYPE::kOneHandSword: {
                    oneHSwordsList.push_back(weapon);
                    break;
                }
                default:
                    break;
            }
        }

        logger::info("Swords list contains {} entries", oneHSwordsList.size());
    }

    std::vector<RE::TESObjectWEAP*>& GetOneHSwordsList() { 
        return oneHSwordsList;
    }
}
