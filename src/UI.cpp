#include "SKSEMenuFramework.h"
#include "UI.h"
#include "logger.h" 
#include "ShapeChange.h"

namespace UI {
    bool bCheck;

    int selectedSword = 0;
    std::vector<const char*> swordMenuArray;

    void __stdcall RenderSettingsMenuFunction() {
        if (ImGuiMCP::Checkbox("Checkbox", &bCheck)) {
            logger::info("Checkbox is {}", bCheck);
        }

        if (ImGuiMCP::Combo("Sword List", &selectedSword, swordMenuArray.data(), std::size(swordMenuArray))) {
            logger::info("Sword Selected is {}, FID is {:08X}, plugin name is {}", swordMenuArray[selectedSword], ShapeChange::GetSwordEditorID(selectedSword), ShapeChange::GetSwordFileName(selectedSword));
        }
    }

    void PopulateItemsLists() {
        // For 1H Swords
        for (auto* sword : ShapeChange::GetOneHSwordsList()) {
            swordMenuArray.push_back(sword->GetFullName());
        }
    }

    void RegisterMenu() {
        SKSEMenuFramework::SetSection("Bound Weapon Shape");
        SKSEMenuFramework::AddSectionItem("Settings", RenderSettingsMenuFunction);
    }
}