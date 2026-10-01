#pragma once


namespace UI {
    
    void RegisterMenu();
    void PopulateItemsLists();
}

namespace {
    void RenderCategoryDropdown(std::string_view categoryName);
    void __stdcall RenderOneHandSwordSection();
    void __stdcall RenderBattleAxeSection();
}