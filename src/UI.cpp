#include "UI.h"

#include "SKSEMenuFramework.h"
#include "ShapeChange.h"
#include "logger.h"

namespace UI {
    bool bCheck;

    std::vector<std::string_view> categoryOrder;
    std::unordered_map<std::string_view, int> selectedIndexByCategory;
    std::unordered_map<std::string_view, std::vector<const char*>> menuArrayByCategory;

    void RenderCategoryDropdown(std::string_view categoryName) {
        auto& menuArray = menuArrayByCategory[categoryName];
        int& selectedIndex = selectedIndexByCategory[categoryName];

        if (ImGuiMCP::Combo(categoryName.data(), &selectedIndex, menuArray.data(), std::size(menuArray))) {
            ShapeChange::SetSelectedShape(categoryName, selectedIndex);
            logger::info("Selected {} in category {}, FID is {:08X}, plugin is {}", menuArray[selectedIndex],
                         categoryName, ShapeChange::GetWeaponFormID(categoryName, selectedIndex),
                         ShapeChange::GetWeaponFileName(categoryName, selectedIndex));
        }
    }

    void __stdcall RenderOneHandSwordSection() { RenderCategoryDropdown("OneHandSword"); }

    void __stdcall RenderBattleAxeSection() { RenderCategoryDropdown("BattleAxe"); }

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
        SKSEMenuFramework::AddSectionItem("One Hand Sword", RenderOneHandSwordSection);
        SKSEMenuFramework::AddSectionItem("Battle Axe", RenderBattleAxeSection);
    }
}