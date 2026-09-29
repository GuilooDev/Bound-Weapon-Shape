#pragma once



namespace ShapeChange {

    void initWeaponsLists();
    std::vector<RE::TESObjectWEAP*>& GetOneHSwordsList();
    RE::FormID GetSwordEditorID(int index);
    std::string_view GetSwordFileName(int index);
    bool CheckWeapon(RE::TESObjectWEAP* object);
}