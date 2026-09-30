#include "logger.h"
#include "UI.h"
#include "ShapeChange.h"


/*
Visual vient de boundswordencheffects pour une épée
Il faut retirer le mesh de la sword dans le nif et le remplacer par celui voulu
Il faut changer opacité et émissive pour un meilleur effet

OU

On peut enlever le shape d'épée de boundswordencheffects et changer le nif dans 
WEAPON Record

*/

void OnDataLoadedMessage(SKSE::MessagingInterface::Message* message) { 
    
    if (message->type == SKSE::MessagingInterface::kDataLoaded) {
        ShapeChange::InitWeaponsLists();
        UI::PopulateItemsLists();
    }

}


SKSEPluginLoad(const SKSE::LoadInterface *skse) {
    SKSE::Init(skse);
    SetupLog();
    UI::RegisterMenu();
    
    SKSE::GetMessagingInterface()->RegisterListener(OnDataLoadedMessage);
   
    return true;
}