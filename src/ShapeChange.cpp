#include "ShapeChange.h"
#include "logger.h"

namespace ShapeChange {

    namespace {
        struct WeaponStruct {
            RE::BGSKeyword* keyword = nullptr;
            std::vector<RE::TESObjectWEAP*> weapons;
            std::vector<RE::TESObjectWEAP*> boundWeapons;
        };


        // On rajoute simplement les types d'armes ici!
        std::unordered_map<std::string_view, WeaponStruct> categories;
        constexpr std::array<std::pair<std::string_view, std::string_view>, 2> categoryDefinitions{
            {{"OneHandSword", "WeapTypeSword"}, {"BattleAxe", "WeapTypeBattleaxe"}
        }};


        bool CheckWeapon(RE::TESObjectWEAP* object) {
            std::string_view name = object->GetFullName();
            if (name.empty()) return false;
            if (object->formEnchanting) return false;
            if (object->numKeywords == 0) return false;

            return true;
        }


        void SortWeaponsAlphabetically(std::vector<RE::TESObjectWEAP*>& weaponList) {
            std::sort(weaponList.begin(), weaponList.end(), [](RE::TESObjectWEAP* a, RE::TESObjectWEAP* b) {
                std::string_view nameA = a->GetFullName();
                std::string_view nameB = b->GetFullName();
                //On enlève les espaces blancs
                nameA.remove_prefix(std::min(nameA.find_first_not_of(' '), nameA.size()));
                nameB.remove_prefix(std::min(nameB.find_first_not_of(' '), nameB.size()));

                return nameA < nameB;
            });
        }
    }

    void InitWeaponsLists() { 
        auto* dataHandler = RE::TESDataHandler::GetSingleton();

        if (!dataHandler) {
            logger::error("No data handler found!");
            return;
        
        }
        logger::info("Initialisation started");

        auto& weapons = dataHandler->GetFormArray<RE::TESObjectWEAP>();
       

        for (const auto& [categoryName, keywordEditorID] : categoryDefinitions) {
            auto* keyword = RE::TESForm::LookupByEditorID<RE::BGSKeyword>(keywordEditorID);
            if (!keyword) {
                logger::error("Could not find keyword {}", keywordEditorID);
                continue;
            }
            categories[categoryName].keyword = keyword;
        }


        for (auto* weapon : weapons) {
            if (!weapon) continue;

            for (auto& [name, category] : categories) {
                if (!category.keyword || !weapon->HasKeyword(category.keyword)) continue;

                if (weapon->IsBound()) {
                    category.boundWeapons.push_back(weapon);
                } else if (CheckWeapon(weapon)) {
                    category.weapons.push_back(weapon);
                }
                break;  
            }
        }

        // Ordre Alphabétique
        for (auto& [name, category] : categories) {
            SortWeaponsAlphabetically(category.weapons);
            logger::info("{} list contains {} entries", name, category.weapons.size());
            logger::info("Bound{} list contains {} entries", name, category.boundWeapons.size());
        }
    }

    std::vector<std::string_view> GetCategoryNames() {
        std::vector<std::string_view> names;
        names.reserve(categoryDefinitions.size());
        for (const auto& [categoryName, keywordEditorID] : categoryDefinitions) {
            names.push_back(categoryName);
        }
        return names;
    }

    std::vector<RE::TESObjectWEAP*>& GetWeaponsList(std::string_view categoryName) {
        return categories[categoryName].weapons;
    }

    RE::FormID GetWeaponFormID(std::string_view categoryName, int index) {
        return categories[categoryName].weapons[index]->GetFormID();
    }

    std::string_view GetWeaponFileName(std::string_view categoryName, int index) {
        auto filename = categories[categoryName].weapons[index]->GetFile(0);
        return filename->GetFilename();
    }

    
}

