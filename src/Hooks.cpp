#include "Hooks.h"
#include "logger.h"
#include "ShapeChange.h"


namespace Hooks {
    namespace {
        using LoadPart_t = RE::NiAVObject* (*)(RE::TESModel*, std::int32_t, RE::TESObjectREFR*,
                                               RE::BSTSmartPointer<RE::BipedAnim>*, RE::NiAVObject*);

        REL::Relocation<LoadPart_t> _Original;

        
        RE::NiAVObject* LoadPart_Hook(RE::TESModel* a_model, std::int32_t a_slot, RE::TESObjectREFR* a_refr,
                                      RE::BSTSmartPointer<RE::BipedAnim>* a_biped, RE::NiAVObject* a_root) {
            RE::TESModel* model = a_model;

            auto* biped = a_biped ? a_biped->get() : nullptr;
            if (biped && a_slot >= 0) {
                
                auto* realForm = biped->objects[a_slot].item;
                auto* weapon = realForm ? realForm->As<RE::TESObjectWEAP>() : nullptr;

                if (weapon && weapon->IsBound()) {
                    if (auto* shape = ShapeChange::GetSelectedShapeForWeapon(weapon)) {
                        model = static_cast<RE::TESModelTextureSwap*>(shape);
                        logger::info("Bound weapon {:08X} (slot {}): substituting model with {}",
                                     weapon->GetFormID(), a_slot, shape->GetFullName());
                    }
                }
            }

            return _Original(model, a_slot, a_refr, a_biped, a_root);
        }
    }

    void Install() {
        REL::Relocation<std::uintptr_t> functionBase{REL::RelocationID(15506, 15683)};

        // AE and SE have the call site at different offsets inside the same function
        std::size_t callOffset = REL::Module::IsAE() ? 0x2B1 : 0x17F;
        REL::Relocation<std::uintptr_t> callSite{functionBase.address() + callOffset};

        _Original = SKSE::GetTrampoline().write_call<5>(callSite.address(), LoadPart_Hook);
        logger::info("LoadPart hook installed at {:X}", callSite.address());
    }
}