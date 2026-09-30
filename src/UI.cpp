#include "SKSEMenuFramework.h"
#include "UI.h"
#include "logger.h" 
#include "ShapeChange.h"

namespace UI {
    bool bCheck;

    std::vector<std::string_view> categoryOrder;
    std::unordered_map<std::string_view, int> selectedIndexByCategory;
    std::unordered_map<std::string_view, std::vector<const char*>> menuArrayByCategory;

    void __stdcall RenderSettingsMenuFunction() {
        if (ImGuiMCP::Checkbox("Checkbox", &bCheck)) {
            logger::info("Checkbox is {}", bCheck);
        }

        for (auto& categoryName : categoryOrder) {
            auto& menuArray = menuArrayByCategory[categoryName];
            int& selectedIndex = selectedIndexByCategory[categoryName];

            if (ImGuiMCP::Combo(categoryName.data(), &selectedIndex, menuArray.data(), std::size(menuArray))) {
                logger::info("Selected {} in category {}, FID is {:08X}, plugin is {}", menuArray[selectedIndex],
                             categoryName, ShapeChange::GetWeaponFormID(categoryName, selectedIndex),
                             ShapeChange::GetWeaponFileName(categoryName, selectedIndex));
            }
        }
    }

    void PopulateItemsLists() {
        categoryOrder = ShapeChange::GetCategoryNames();
        for (auto& categoryName : categoryOrder) {
            auto& menuArray = menuArrayByCategory[categoryName];
            for (auto* weapon : ShapeChange::GetWeaponsList(categoryName)) {
                menuArray.push_back(weapon->GetFullName());
            }
        }
    }

    void RegisterMenu() {
        SKSEMenuFramework::SetSection("Bound Weapon Shape");
        SKSEMenuFramework::AddSectionItem("Settings", RenderSettingsMenuFunction);
    }
}