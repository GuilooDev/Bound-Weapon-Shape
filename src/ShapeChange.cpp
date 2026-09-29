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
            if (!CheckWeapon(weapon)) continue;
            
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

    RE::FormID GetSwordEditorID(int index) { 
        return oneHSwordsList[index]->GetFormID();
    }

    std::string_view GetSwordFileName(int index) { 
        auto filename = oneHSwordsList[index]->GetFile(0);
        return filename->GetFilename();
    }

    bool CheckWeapon(RE::TESObjectWEAP* object) {
        if (object->formEnchanting) return false;
        if (object->numKeywords == 0) return false;
        //Check weapon keywords

        return true;
    }
}
