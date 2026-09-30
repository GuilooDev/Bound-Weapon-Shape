#pragma once



namespace ShapeChange {

    void InitWeaponsLists();

    std::vector<std::string_view> GetCategoryNames();
    std::vector<RE::TESObjectWEAP*>& GetWeaponsList(std::string_view categoryName);
    RE::FormID GetWeaponFormID(std::string_view categoryName, int index);
    std::string_view GetWeaponFileName(std::string_view categoryName, int index);
    void SetSelectedShape(std::string_view categoryName, int index);
    
}

