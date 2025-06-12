// ---------------------------------------------------------------------
// RSDK Project: Sonic Mania
// Object Description: Localization Object
// Object Author: Christian Whitehead/Simon Thomley/Hunter Bridges
// Decompiled by: Rubberduckycooly & RMGRich
// ---------------------------------------------------------------------

#include "Game.h"

ObjectLocalization *Localization;

void Localization_Update(void) {}

void Localization_LateUpdate(void) {}

void Localization_StaticUpdate(void) {}

void Localization_Draw(void) {}

void Localization_Create(void *data) {}

void Localization_StageLoad(void)
{
    OptionsRAM *options = Options_GetOptionsRAM();
    if (globals->optionsLoaded >= STATUS_OK && options->overrideLanguage) {
        Localization->language = options->language;
        Localization_LoadStrings();
    }
    else {
#if PLATFORM_PS3
        int32 ps3Lang = PS3_GetSystemLanguage();
        switch (ps3Lang) {
            case PS3_LANGUAGE_JAPANESE:
                Localization->language = LANGUAGE_JP;
                break;
            case PS3_LANGUAGE_ENGLISH_US:
            case PS3_LANGUAGE_ENGLISH_UK: // Map UK English to the game's generic English
                Localization->language = LANGUAGE_EN;
                break;
            case PS3_LANGUAGE_FRENCH:
                Localization->language = LANGUAGE_FR;
                break;
            case PS3_LANGUAGE_SPANISH:
                Localization->language = LANGUAGE_SP;
                break;
            case PS3_LANGUAGE_GERMAN:
                Localization->language = LANGUAGE_GE;
                break;
            case PS3_LANGUAGE_ITALIAN:
                Localization->language = LANGUAGE_IT;
                break;
            case PS3_LANGUAGE_KOREAN:
#if GAME_VERSION != VER_100 // Korean was added in later versions
                Localization->language = LANGUAGE_KO;
                break;
#else
                Localization->language = sku_language; // Fallback for older versions
                break;
#endif
            case PS3_LANGUAGE_CHINESE_SIMPLIFIED:
#if GAME_VERSION != VER_100 // Simplified Chinese was added in later versions
                Localization->language = LANGUAGE_SC;
                break;
#else
                Localization->language = sku_language; // Fallback for older versions
                break;
#endif
            case PS3_LANGUAGE_CHINESE_TRADITIONAL:
#if GAME_VERSION != VER_100 // Traditional Chinese was added in later versions
                Localization->language = LANGUAGE_TC;
                break;
#else
                Localization->language = sku_language; // Fallback for older versions
                break;
#endif
            // Add other mappings as necessary, e.g., Portuguese, Russian, Dutch if the game supports them
            // For now, unhandled languages will use sku_language
            default:
                Localization->language = sku_language; // Fallback to default SKU language
                break;
        }
#else
        // Original logic for non-PS3 platforms
        Localization->language = sku_language;
#endif
        Localization_LoadStrings();
    }
}

void Localization_LoadStrings(void)
{
    RSDK.InitString(&Localization->text, "", 0);

    switch (Localization->language) {
        case LANGUAGE_EN:
            LogHelpers_Print("Loading EN strings...");
            RSDK.LoadStringList(&Localization->text, "StringsEN.txt", 16);
            break;

        case LANGUAGE_FR:
            LogHelpers_Print("Loading FR strings...");
            RSDK.LoadStringList(&Localization->text, "StringsFR.txt", 16);
            break;

        case LANGUAGE_IT:
            LogHelpers_Print("Loading IT strings...");
            RSDK.LoadStringList(&Localization->text, "StringsIT.txt", 16);
            break;

        case LANGUAGE_GE:
            LogHelpers_Print("Loading GE strings...");
            RSDK.LoadStringList(&Localization->text, "StringsGE.txt", 16);
            break;

        case LANGUAGE_SP:
            LogHelpers_Print("Loading SP strings...");
            RSDK.LoadStringList(&Localization->text, "StringsSP.txt", 16);
            break;

        case LANGUAGE_JP:
            LogHelpers_Print("Loading JP strings...");
            RSDK.LoadStringList(&Localization->text, "StringsJP.txt", 16);
            break;

#if GAME_VERSION != VER_100
        case LANGUAGE_KO:
            LogHelpers_Print("Loading KO strings...");
            RSDK.LoadStringList(&Localization->text, "StringsKO.txt", 16);
            break;

        case LANGUAGE_SC:
            LogHelpers_Print("Loading Simp Chinese strings...");
            RSDK.LoadStringList(&Localization->text, "StringsSC.txt", 16);
            break;

        case LANGUAGE_TC:
            LogHelpers_Print("Loading Trad Chinese strings...");
            RSDK.LoadStringList(&Localization->text, "StringsTC.txt", 16);
            break;
#endif

        default: break;
    }

    RSDK.SplitStringList(Localization->strings, &Localization->text, 0, STR_STRING_COUNT);
    Localization->loaded = true;

#if MANIA_USE_EGS
    if (API.CheckAchievementsEnabled()) {
        String *names[STR_STRING_COUNT - STR_ACHIEVEMENT];
        for (int32 i = 0; i < (STR_STRING_COUNT - STR_ACHIEVEMENT); ++i) {
            names[i] = &Localization->strings[i + STR_ACHIEVEMENT];
        }

        API.SetAchievementNames(names, STR_STRING_COUNT - STR_ACHIEVEMENT);
    }
#endif
}

void Localization_GetString(String *string, uint8 id)
{
    memset(string, 0, sizeof(String));
    RSDK.InitString(string, "", 0);
    RSDK.CopyString(string, &Localization->strings[id]);
    for (int32 c = 0; c < string->length; ++c) {
        if (string->chars[c] == '\\')
            string->chars[c] = '\n';
    }
}

void Localization_GetZoneName(String *string, uint8 zone)
{
    switch (zone) {
        case ZONE_GHZ: RSDK.InitString(string, "GREEN HILL", 0); break;
        case ZONE_CPZ: RSDK.InitString(string, "CHEMICAL PLANT", 0); break;
        case ZONE_SPZ: RSDK.InitString(string, "STUDIOPOLIS", 0); break;
        case ZONE_FBZ: RSDK.InitString(string, "FLYING BATTERY", 0); break;
        case ZONE_PGZ: RSDK.InitString(string, "PRESS GARDEN", 0); break;
        case ZONE_SSZ: RSDK.InitString(string, "STARDUST SPEEDWAY", 0); break;
        case ZONE_HCZ: RSDK.InitString(string, "HYDROCITY", 0); break;
        case ZONE_MSZ: RSDK.InitString(string, "MIRAGE SALOON", 0); break;
        case ZONE_OOZ: RSDK.InitString(string, "OIL OCEAN", 0); break;
        case ZONE_LRZ: RSDK.InitString(string, "LAVA REEF", 0); break;
        case ZONE_MMZ: RSDK.InitString(string, "METALLIC MADNESS", 0); break;
        case ZONE_TMZ: RSDK.InitString(string, "TITANIC MONARCH", 0); break;
        case ZONE_ERZ: RSDK.InitString(string, "???", 0); break;
        default: break;
    }
}
void Localization_GetZoneInitials(String *string, uint8 zone)
{
    switch (zone) {
        case ZONE_GHZ: RSDK.InitString(string, "GHZ", 0); break;
        case ZONE_CPZ: RSDK.InitString(string, "CPZ", 0); break;
        case ZONE_SPZ: RSDK.InitString(string, "SPZ", 0); break;
        case ZONE_FBZ: RSDK.InitString(string, "FBZ", 0); break;
        case ZONE_PGZ: RSDK.InitString(string, "PGZ", 0); break;
        case ZONE_SSZ: RSDK.InitString(string, "SSZ", 0); break;
        case ZONE_HCZ: RSDK.InitString(string, "HCZ", 0); break;
        case ZONE_MSZ: RSDK.InitString(string, "MSZ", 0); break;
        case ZONE_OOZ: RSDK.InitString(string, "OOZ", 0); break;
        case ZONE_LRZ: RSDK.InitString(string, "LRZ", 0); break;
        case ZONE_MMZ: RSDK.InitString(string, "MMZ", 0); break;
        case ZONE_TMZ: RSDK.InitString(string, "TMZ", 0); break;
        case ZONE_ERZ: RSDK.InitString(string, "???", 0); break;
        default: break;
    }
}

#if GAME_INCLUDE_EDITOR
void Localization_EditorDraw(void) {}

void Localization_EditorLoad(void) {}
#endif

void Localization_Serialize(void) {}

#if PLATFORM_PS3
#include <cell/sysmodule.h>
#include <cell/sysutil_sysparam.h> // Ensure this is included if not already via Localization.h (though it should be)

// Function to get the PS3 system language
int32 PS3_GetSystemLanguage(void) {
    int32 language = PS3_LANGUAGE_ENGLISH_US; // Default to English US

    // Load the system utility module for system parameters
    int32 result = cellSysmoduleLoadModule(CELL_SYSMODULE_SYSPARAM);
    if (result == CELL_OK) {
        int sysLanguage;
        // Get the system language
        result = cellSysutilGetSystemLanguage(&sysLanguage);
        if (result == CELL_OK) {
            language = (int32)sysLanguage;
        } else {
            // Failed to get language, RSDK::PrintF(PRINT_ERROR, "Failed to get PS3 system language: 0x%x", result);
            // Keep default language
        }
        // Unload the system utility module
        cellSysmoduleUnloadModule(CELL_SYSMODULE_SYSPARAM);
    } else {
        // Failed to load module, RSDK::PrintF(PRINT_ERROR, "Failed to load CELL_SYSMODULE_SYSPARAM: 0x%x", result);
        // Keep default language
    }
    return language;
}
#endif // PLATFORM_PS3
