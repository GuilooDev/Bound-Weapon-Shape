#include "SKSEMenuFramework.h"
#include "UI.h"
#include "logger.h" 
#include "ShapeChange.h"


bool bCheck;

int selectedSword = 0;
const char* swordMenuArray[]{"Sword1", "Sword2"};

void __stdcall RenderSettingsMenuFunction() {
    if (ImGuiMCP::Checkbox("Checkbox", &bCheck)) {
        logger::info("Checkbox is {}", bCheck);
    }

    if (ImGuiMCP::Combo("Sword List", &selectedSword, swordMenuArray, std::size(swordMenuArray))) {
        logger::info("Sword Selected is {}", swordMenuArray[selectedSword]);
    }

    
}

void RegisterMenu() { 
	SKSEMenuFramework::SetSection("Bound Weapon Shape"); 
	SKSEMenuFramework::AddSectionItem("Settings", RenderSettingsMenuFunction);
}