#include "logger.h"
#include "UI.h"


/*
Visual vient de boundswordencheffects pour une épée
Il faut retirer le mesh de la sword dans le nif et le remplacer par celui voulu
Il faut changer opacité et émissive pour un meilleur effet

*/




SKSEPluginLoad(const SKSE::LoadInterface *skse) {
    SKSE::Init(skse);
    SetupLog();
    RegisterMenu();
   
    return true;
}