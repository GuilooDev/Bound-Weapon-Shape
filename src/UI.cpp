#include "SKSEMenuFramework.h"
#include "UI.h"

void __stdcall RenderMenuFunction() {
	ImGuiMCP::Text("Test");
}

void RegisterMenu() { 
	SKSEMenuFramework::SetSection("Bound Weapon Shape"); 
	SKSEMenuFramework::AddSectionItem("Settings", RenderMenuFunction);
}