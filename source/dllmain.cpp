#include <Windows.h>
#include <sstream>
#include <string>

#include "detours.h"
#include "Helpers.h"
#include "Signature.h"
#include "toml.hpp"

int modifiers = 0;
int difficulty = 0;
int hitEffect;

bool noSlides;
bool biggerPercentage;
bool modifiersFix;
bool xBarRank;
bool enValue;
bool judgementsValue;
bool altFailed;

toml::table config;

//1.0.1 0x14040B6C0
//1.0.2 0x1406F2820
SIG_SCAN ( sigStartSong, "\x41\x54\x41\x55\x41\x57\x48\x83\xEC\x30\x4C\x8B\xFA\x45\x0F\xB6\xE8\x48\x63\x51\x08\x4C\x8B\xE1\x83\xFA\x04\x0F\x8D\x00\x00\x00\x00\x48\x89\x5C\x24\x00\x48\x8D\x0D\x00\x00\x00\x00\x48\x89\x6C\x24\x00\x48\x89\x74\x24\x00\x48\x89\x7C\x24\x00\x4C\x89\x74\x24\x00\xE8\x00\x00\x00\x00\x48\x69\xEA\x00\x00\x00\x00\x48\x89\x44\x24\x00\x49\x03\xEC\x8B\x75\x48\x48\x8D\x4D\x30\x8B\x7D\x50\x4C\x8D\x75\x5C\x8B\x5D\x58\xE8\x00\x00\x00\x00\x89\x75\x48\x4C\x8D\x15\x00\x00\x00\x00\x48\x8B\x74\x24\x00\x89\x7D\x50\x48\x8B\x7C\x24\x00\x89\x5D\x58\x49\x63\x44\x24\x00\x49\x63\x0C\x24\x48\x8B\x6C\x24\x00\x48\x8D\x0C\x88\x41\x8B\x07\x45\x8B\x8C\x8A\x00\x00\x00\x00\x45\x8B\x84\x8A\x00\x00\x00\x00\x41\x8B\x94\x8A\x00\x00\x00\x00\x41\x89\x06\x41\x8B\x47\x04\x41\x89\x46\x04\x41\x8B\x47\x08\x41\x89\x46\x08\x41\x8B\x47\x0C\x41\x89\x46\x0C\x41\x8B\x47\x10\x41\x89\x46\x10\x41\x8B\x04\x24\x41\x89\x46\x14\x41\x8B\x44\x24\x00\x41\x89\x46\x18\x41\x0F\xB6\x47\x00\x41\x88\x46\x1C\x41\x6B\xC1\x64\x45\x89\x46\x24\x41\x89\x56\x28\x41\x89\x46\x20\x49\x63\x4F\x1C\x41\x89\x4E\x2C\x41\x0F\xB6\x47\x00\x41\x88\x46\x30\x84\xC0\x74\x1C\x49\x63\x04\x24\x49\x63\x84\x82\x00\x00\x00\x00\x41\x8B\x8C\x84\x00\x00\x00\x00\x33\xC0\x41\x89\x4E\x34\xEB\x38\x83\xF9\xFF\x74\x2D\x49\x63\x04\x24\x48\x8B\xD1\x4D\x63\x84\x82\x00\x00\x00\x00\x4A\x8D\x04\x81\x41\x8B\x8C\xC4\x00\x00\x00\x00\x4A\x8D\x04\x82\x41\x89\x4E\x34\x41\x8B\x84\xC4\x00\x00\x00\x00\xEB\x06\x33\xC0\x41\x89\x46\x34\x41\x89\x46\x38\x49\x8D\x56\x7C\x48\x8B\x44\x24\x00\x41\xB9\x00\x00\x00\x00\x0F\xB6\x80\x00\x00\x00\x00\x41\x88\x46\x3C\x41\x0F\xB6\x47\x00\x41\x88\x46\x3D\x41\x8B\x47\x24\x41\x89\x46\x40\x41\x0F\xB6\x47\x00\x41\x88\x46\x48\x41\x8B\x07\x41\x89\x44\x24\x00\x41\x8B\x47\x18\x41\x89\x44\x24\x00\x41\x8B\x47\x2C\x41\x89\x44\x24\x00\x41\x8B\x47\x2C\x41\x89\x46\x44\x41\x8B\x47\x30\x41\x89\x46\x4C\x41\x8B\x47\x48\x41\x89\x46\x64\x41\x8B\x47\x34\x41\x89\x46\x50\x41\x8B\x47\x4C\x41\x89\x46\x68\x41\x8B\x47\x38\x41\x89\x46\x54\x41\x8B\x47\x50\x41\x89\x46\x6C\x41\x8B\x47\x3C\x41\x89\x46\x58\x41\x8B\x47\x54\x41\x89\x46\x70\x41\x8B\x47\x40\x41\x89\x46\x5C\x41\x8B\x47\x58\x41\x89\x46\x74\x41\x8B\x47\x44\x41\x89\x46\x60\x41\x8B\x47\x5C\x4D\x2B\xFE\x41\x89\x46\x78\x49\x8D\x86\x00\x00\x00\x00\x0F\x1F\x40\x00\x48\x8D\x40\x05\x41\x0F\x10\x44\x17\x00\x48\x8D\x52\x14\x0F\x11\x42\xEC\x41\x8B\x4C\x17\x00\x89\x4A\xFC\x41\x0F\xB6\x4C\x07\x00\x88\x48\xFB\x41\x0F\xB6\x4C\x07\x00\x88\x48\xFC\x41\x0F\xB6\x4C\x07\x00\x88\x48\xFD\x41\x0F\xB6\x4C\x07\x00\x88\x48\xFE\x41\x0F\xB6\x4C\x07\x00\x88\x48\xFF\x49\x83\xE9\x01\x75\xB3\x48\x8B\x5C\x24\x00\x45\x84\xED\x74\x09\x41\x8B\x4E\x08\xE8\x00\x00\x00\x00\x4C\x8B\x74\x24\x00\x48\x83\xC4\x30\x41\x5F\x41\x5D\x41\x5C\xC3\x48\x8B\xC4\x48\x89\x58\x18\x55\x56\x57\x41\x54\x41\x55\x41\x56\x41\x57\x48\x8D\x68\x98\x48\x81\xEC\x00\x00\x00\x00\x0F\x29\x70\xB8\x0F\x29\x78\xA8\x48\x8B\x05\x00\x00\x00\x00\x48\x33\xC4\x48\x89\x45\x00\x48\x8B\xD9\x48\x63\x41\x08\x83\xF8\x04\x0F\x8D\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxx?xxx????xxxx?xxxx?xxxx?xxxx?x????xxx????xxxx?xxxxxxxxxxxxxxxxxxxxx????xxxxxx????xxxx?xxxxxxx?xxxxxxx?xxxxxxxx?xxxxxxxxxxx????xxxx????xxxx????xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx?xxxxxxxx?xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx?xxxxxxxxxxxxxxxx????xxxx????xxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxx????xxxxxxxxxxxx????xxxxxxxxxxxxxxxxxxxx?xx????xxx????xxxxxxxx?xxxxxxxxxxxxxxxx?xxxxxxxxxxx?xxxxxxxx?xxxxxxxx?xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxxxx?xxxxxxxxxxxx?xxxxxxxx?xxxxxxxx?xxxxxxxx?xxxxxxxx?xxxxxxxx?xxxxxxxxxxxxx?xxxxxxxxxx????xxxx?xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx????xxxxxxxxxxx????xxxxxxxxxxxxxxxxxxx????" )


//Hit Values

SIG_SCAN ( sigHitEff00, "\x68\x69\x74\x5F\x65\x66\x66\x30\x30\x00\x00\x00\x00\x00\x00\x00", "xxxxxxxxx???????" )

SIG_SCAN ( sigHitEff01, "\x68\x69\x74\x5F\x65\x66\x66\x30\x31\x00\x00\x00\x00\x00\x00\x00", "xxxxxxxxx???????" )

SIG_SCAN ( sigHitEff02, "\x68\x69\x74\x5F\x65\x66\x66\x30\x32\x00\x00\x00\x00\x00\x00\x00", "xxxxxxxxx???????" )

SIG_SCAN ( sigHitEff03, "\x68\x69\x74\x5F\x65\x66\x66\x30\x33\x00\x00\x00\x00\x00\x00\x00", "xxxxxxxxx???????" )

SIG_SCAN ( sigHitEff04, "\x68\x69\x74\x5F\x65\x66\x66\x30\x34\x00\x00\x00\x00\x00\x00\x00", "xxxxxxxxx???????" )

SIG_SCAN ( sigHitEff00L, "\x68\x69\x74\x5F\x65\x66\x66\x30\x30\x5F\x6C\x00\x00\x00\x00\x00\x68\x69\x74", "xxxxxxxxx???????xxx" )

SIG_SCAN ( sigHitEff01L, "\x68\x69\x74\x5F\x65\x66\x66\x30\x31\x5F\x6C\x00\x00\x00\x00\x00", "xxxxxxxxxxx?????" )

SIG_SCAN ( sigHitEff00R, "\x68\x69\x74\x5F\x65\x66\x66\x30\x30\x5F\x72\x00\x00\x00\x00\x00", "xxxxxxxxxxx?????" )

SIG_SCAN ( sigHitEff01R, "\x68\x69\x74\x5F\x65\x66\x66\x30\x31\x5F\x72\x00\x00\x00\x00\x00", "xxxxxxxxxxx?????" )

SIG_SCAN ( sigHitEffSlide01L, "\x68\x69\x74\x5F\x65\x66\x66\x5F\x73\x6C\x69\x64\x65\x30\x31\x5F\x6C\x00\x00\x00\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxx???????" )

SIG_SCAN ( sigHitEffSlide01R, "\x68\x69\x74\x5F\x65\x66\x66\x5F\x73\x6C\x69\x64\x65\x30\x31\x5F\x72\x00\x00\x00\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxx???????" )


//Percentage

SIG_SCAN ( sigPEnergyNum01C, "\x70\x5F\x65\x6E\x65\x72\x67\x79\x5F\x6E\x75\x6D\x30\x31\x5F\x63\x00\x00\x00\x00\x00\x00\x00\x00", "xxxxxxxxxxxxxxxx????????" )

SIG_SCAN ( sigPEnergyNum02C, "\x70\x5F\x65\x6E\x65\x72\x67\x79\x5F\x6E\x75\x6D\x30\x32\x5F\x63\x00\x00\x00\x00\x00\x00\x00\x00", "xxxxxxxxxxxxxxxx????????" )

SIG_SCAN ( sigPEnergyNum03C, "\x70\x5F\x65\x6E\x65\x72\x67\x79\x5F\x6E\x75\x6D\x30\x33\x5F\x63\x00\x00\x00\x00\x00\x00\x00\x00", "xxxxxxxxxxxxxxxx????????" )

SIG_SCAN ( sigPEnergyNum04C, "\x70\x5F\x65\x6E\x65\x72\x67\x79\x5F\x6E\x75\x6D\x30\x34\x5F\x63\x00\x00\x00\x00\x00\x00\x00\x00", "xxxxxxxxxxxxxxxx????????" )

SIG_SCAN ( sigPEnergyNum05C, "\x70\x5F\x65\x6E\x65\x72\x67\x79\x5F\x6E\x75\x6D\x30\x35\x5F\x63\x00\x00\x00\x00\x00\x00\x00\x00", "xxxxxxxxxxxxxxxx????????" )

SIG_SCAN ( sigPEnergyNum06C, "\x70\x5F\x65\x6E\x65\x72\x67\x79\x5F\x6E\x75\x6D\x30\x36\x5F\x63\x00\x00\x00\x00\x00\x00\x00\x00", "xxxxxxxxxxxxxxxx????????" )

SIG_SCAN ( sigPEnergyNum07C, "\x70\x5F\x65\x6E\x65\x72\x67\x79\x5F\x6E\x75\x6D\x30\x37\x5F\x63\x00\x00\x00\x00\x00\x00\x00\x00", "xxxxxxxxxxxxxxxx????????" )


//English Values and Judgements Values

SIG_SCAN ( sigValueTextFine01, "\x76\x61\x6C\x75\x65\x5F\x74\x65\x78\x74\x5F\x66\x69\x6E\x65\x30\x31\x00\x00\x00\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxx???????" )

SIG_SCAN ( sigValueTextFine03, "\x76\x61\x6C\x75\x65\x5F\x74\x65\x78\x74\x5F\x66\x69\x6E\x65\x30\x33\x00\x00\x00\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxx???????" )

SIG_SCAN ( sigValueTextSad, "\x76\x61\x6C\x75\x65\x5F\x74\x65\x78\x74\x5F\x73\x61\x64\x00\x00", "xxxxxxxxxxxxxx??" )

SIG_SCAN( sigValueTextWrong01, "\x76\x61\x6C\x75\x65\x5F\x74\x65\x78\x74\x5F\x77\x72\x6F\x6E\x67\x30\x31\x00\x00\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxxx??????" )

SIG_SCAN( sigValueTextWrong02, "\x76\x61\x6C\x75\x65\x5F\x74\x65\x78\x74\x5F\x77\x72\x6F\x6E\x67\x30\x32\x00\x00\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxxx??????" )

SIG_SCAN( sigValueTextWrong03, "\x76\x61\x6C\x75\x65\x5F\x74\x65\x78\x74\x5F\x77\x72\x6F\x6E\x67\x30\x33\x00\x00\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxxx??????" )

SIG_SCAN( sigValueTextWrong04, "\x76\x61\x6C\x75\x65\x5F\x74\x65\x78\x74\x5F\x77\x72\x6F\x6E\x67\x30\x34\x00\x00\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxxx??????" )

SIG_SCAN( sigComboTempoFine001, "\x63\x6F\x6D\x62\x6F\x5F\x74\x65\x6D\x70\x6F\x5F\x66\x69\x6E\x65\x30\x30\x31\x00\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxxxx?????" )

SIG_SCAN( sigComboTempoFine010, "\x63\x6F\x6D\x62\x6F\x5F\x74\x65\x6D\x70\x6F\x5F\x66\x69\x6E\x65\x30\x31\x30\x00\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxxxx?????" )

SIG_SCAN( sigComboTempoFine100, "\x63\x6F\x6D\x62\x6F\x5F\x74\x65\x6D\x70\x6F\x5F\x66\x69\x6E\x65\x31\x30\x30\x00\x00\x00\x00\x00\x63\x6F\x6D\x62\x6F\x5F\x74\x65\x6D\x70\x6F\x5F\x63\x6F\x6F\x6C\x31\x30\x30\x30", "xxxxxxxxxxxxxxxxxxx?????xxxxxxxxxxxxxxxxxxxx" )

SIG_SCAN( sigComboTempoFine100B, "\x63\x6F\x6D\x62\x6F\x5F\x74\x65\x6D\x70\x6F\x5F\x66\x69\x6E\x65\x31\x30\x30\x5F\x62\x00\x00\x00", "xxxxxxxxxxxxxxxxxxxxx???" )

SIG_SCAN( sigComboTempoFine1000, "\x63\x6F\x6D\x62\x6F\x5F\x74\x65\x6D\x70\x6F\x5F\x66\x69\x6E\x65\x31\x30\x30\x30\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxxxxx????" )

SIG_SCAN( sigComboFine001, "\x63\x6F\x6D\x62\x6F\x5F\x66\x69\x6E\x65\x30\x30\x31\x00\x00\x00", "xxxxxxxxxxxxx???" )

SIG_SCAN( sigComboFine010, "\x63\x6F\x6D\x62\x6F\x5F\x66\x69\x6E\x65\x30\x31\x30\x00\x00\x00", "xxxxxxxxxxxxx???" )

SIG_SCAN( sigComboFine100, "\x63\x6F\x6D\x62\x6F\x5F\x66\x69\x6E\x65\x31\x30\x30\x00\x00\x00", "xxxxxxxxxxxxx???" )

SIG_SCAN( sigComboFine100B, "\x63\x6F\x6D\x62\x6F\x5F\x66\x69\x6E\x65\x31\x30\x30\x5F\x62\x00", "xxxxxxxxxxxxxxx?" )

SIG_SCAN( sigComboFine1000, "\x63\x6F\x6D\x62\x6F\x5F\x66\x69\x6E\x65\x31\x30\x30\x30\x00\x00", "xxxxxxxxxxxxxx??" )

SIG_SCAN( sigValueTextCool01, "\x76\x61\x6C\x75\x65\x5F\x74\x65\x78\x74\x5F\x63\x6F\x6F\x6C\x30\x31\x00\x00\x00\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxx???????" )

SIG_SCAN( sigValueTextCool03, "\x76\x61\x6C\x75\x65\x5F\x74\x65\x78\x74\x5F\x63\x6F\x6F\x6C\x30\x33\x00\x00\x00\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxx???????" )

SIG_SCAN( sigComboCool001, "\x63\x6F\x6D\x62\x6F\x5F\x63\x6F\x6F\x6C\x30\x30\x31\x00\x00\x00", "xxxxxxxxxxxxx???" )

SIG_SCAN( sigComboCool010, "\x63\x6F\x6D\x62\x6F\x5F\x63\x6F\x6F\x6C\x30\x31\x30\x00\x00\x00", "xxxxxxxxxxxxx???" )

SIG_SCAN( sigComboCool100, "\x63\x6F\x6D\x62\x6F\x5F\x63\x6F\x6F\x6C\x31\x30\x30\x00\x00\x00\x63\x6F\x6D\x62\x6F\x5F\x66", "xxxxxxxxxxxxx???xxxxxxx" )

SIG_SCAN( sigComboCool100B, "\x63\x6F\x6D\x62\x6F\x5F\x63\x6F\x6F\x6C\x31\x30\x30\x5F\x62\x00", "xxxxxxxxxxxxxxx?" )

SIG_SCAN( sigComboCool1000, "\x63\x6F\x6D\x62\x6F\x5F\x63\x6F\x6F\x6C\x31\x30\x30\x30\x00\x00", "xxxxxxxxxxxxxx??" )

SIG_SCAN( sigComboTempoCool001, "\x63\x6F\x6D\x62\x6F\x5F\x74\x65\x6D\x70\x6F\x5F\x63\x6F\x6F\x6C\x30\x30\x31\x00\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxxxx?????" )

SIG_SCAN( sigComboTempoCool010, "\x63\x6F\x6D\x62\x6F\x5F\x74\x65\x6D\x70\x6F\x5F\x63\x6F\x6F\x6C\x30\x31\x30\x00\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxxxx?????" )

SIG_SCAN( sigComboTempoCool100, "\x63\x6F\x6D\x62\x6F\x5F\x74\x65\x6D\x70\x6F\x5F\x63\x6F\x6F\x6C\x31\x30\x30\x00\x00\x00\x00\x00\x63\x6F\x6D\x62\x6F\x5F\x74\x65\x6D\x70\x6F\x5F\x63\x6F\x6F\x6C", "xxxxxxxxxxxxxxxxxxx?????xxxxxxxxxxxxxxxx" )

SIG_SCAN( sigComboTempoCool100B, "\x63\x6F\x6D\x62\x6F\x5F\x74\x65\x6D\x70\x6F\x5F\x63\x6F\x6F\x6C\x31\x30\x30\x5F\x62\x00\x00\x00", "xxxxxxxxxxxxxxxxxxxxx???" )

SIG_SCAN( sigComboTempoCool1000, "\x63\x6F\x6D\x62\x6F\x5F\x74\x65\x6D\x70\x6F\x5F\x63\x6F\x6F\x6C\x31\x30\x30\x30\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxxxxx????" )

//Layers to hide for X Bar Rank

SIG_SCAN ( sigSongEnergyBorderExcellent, "\x73\x6F\x6E\x67\x5F\x65\x6E\x65\x72\x67\x79\x5F\x62\x6F\x72\x64\x65\x72\x5F\x65\x78\x63\x65\x6C\x6C\x65\x6E\x74\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxxxxxxxxxxxxx????" )

SIG_SCAN ( sigSongEnergyBorderGreat, "\x73\x6F\x6E\x67\x5F\x65\x6E\x65\x72\x67\x79\x5F\x62\x6F\x72\x64\x65\x72\x5F\x67\x72\x65\x61\x74\x00\x00\x00\x00\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxxxxxxxxx????????" )

SIG_SCAN( sigSongEnergyEffReach, "\x73\x6F\x6E\x67\x5F\x65\x6E\x65\x72\x67\x79\x5F\x65\x66\x66\x5F\x72\x65\x61\x63\x68\x00\x00\x00", "xxxxxxxxxxxxxxxxxxxxx???" )


//Layers to use for X Bar Rank

SIG_SCAN( sigSongEnergyReach, "\x73\x6F\x6E\x67\x5F\x65\x6E\x65\x72\x67\x79\x5F\x72\x65\x61\x63\x68\x00\x00\x00\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxx???????" )

SIG_SCAN( sigSongEnergyBorder, "\x73\x6F\x6E\x67\x5F\x65\x6E\x65\x72\x67\x79\x5F\x62\x6F\x72\x64\x65\x72\x00\x00\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxxx??????" )

//Layers to use for Modifiers Fix

SIG_SCAN( songEnergyClearTxt, "\x73\x6F\x6E\x67\x5F\x65\x6E\x65\x72\x67\x79\x5F\x63\x6C\x65\x61\x72\x5F\x74\x78\x74\x00\x00\x00", "xxxxxxxxxxxxxxxxxxxxx???" )

SIG_SCAN( sigPrcGaugeBaseArcade, "\x70\x72\x63\x5F\x67\x61\x75\x67\x65\x5F\x62\x61\x73\x65\x5F\x61\x72\x63\x61\x64\x65\x00\x00\x00", "xxxxxxxxxxxxxxxxxxxxx???" )


//Layers to hide for Modifiers Fix

SIG_SCAN( sigOptionInfoHiddenA, "\x6F\x70\x74\x69\x6F\x6E\x5F\x69\x6E\x66\x6F\x5F\x68\x69\x64\x64\x65\x6E\x5F\x61\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxxxxx????" )

SIG_SCAN( sigOptionInfoHispeedA, "\x6F\x70\x74\x69\x6F\x6E\x5F\x69\x6E\x66\x6F\x5F\x68\x69\x73\x70\x65\x65\x64\x5F\x61\x00\x00\x00", "xxxxxxxxxxxxxxxxxxxxx???" )

SIG_SCAN( sigOptionInfoSuddenA, "\x6F\x70\x74\x69\x6F\x6E\x5F\x69\x6E\x66\x6F\x5F\x73\x75\x64\x64\x65\x6E\x5F\x61\x00\x00\x00\x00", "xxxxxxxxxxxxxxxxxxxx????" )

SIG_SCAN( sigOptionInfoBase, "\x6F\x70\x74\x69\x6F\x6E\x5F\x69\x6E\x66\x6F\x5F\x62\x61\x73\x65\x00\x00\x00\x00\x00\x00\x00\x00", "xxxxxxxxxxxxxxxx????????" )


//Alternative failed

SIG_SCAN( sigFailedInfo, "\x66\x61\x69\x6C\x65\x64\x5F\x69\x6E\x66\x6F\x00\x00\x00\x00\x00", "xxxxxxxxxxx?????" )


HOOK(void, __fastcall, _StartSong, sigStartSong(), int* a1, __int64 a2, char a3)
{
	original_StartSong(a1, a2, a3);
	
	//1.0.1
	//modifiers 0x1416E3A68
	//difficulty 0x1416E3AA4
	
	//1.0.2
	modifiers = *reinterpret_cast<int*>(0x1416E2BB8); //wasn't able to sigscan this address
	difficulty = *reinterpret_cast<int*>(0x1416E2B90); //this one either

	if (modifiersFix)
	{
		if (modifiers == 1) //his
		{
			WRITE_MEMORY(songEnergyClearTxt(), uint8_t, 0x73, 0x6F, 0x6E, 0x67, 0x5F, 0x65, 0x6E, 0x65, 0x72, 0x67, 0x79, 0x5F, 0x63, 0x6C, 0x65, 0x61, 0x72, 0x5F, 0x68, 0x69, 0x73, 0x00, 0x00, 0x00);
			WRITE_MEMORY(sigPrcGaugeBaseArcade(), uint8_t, 0x68, 0x69, 0x73);
		}
		else if (modifiers == 2) //hid
		{
			WRITE_MEMORY(songEnergyClearTxt(), uint8_t, 0x73, 0x6F, 0x6E, 0x67, 0x5F, 0x65, 0x6E, 0x65, 0x72, 0x67, 0x79, 0x5F, 0x63, 0x6C, 0x65, 0x61, 0x72, 0x5F, 0x68, 0x69, 0x64, 0x00, 0x00, 0x00);
			WRITE_MEMORY(sigPrcGaugeBaseArcade(), uint8_t, 0x68, 0x69, 0x64);
		}
		else if (modifiers == 3) //sud
		{
			WRITE_MEMORY(songEnergyClearTxt(), uint8_t, 0x73, 0x6F, 0x6E, 0x67, 0x5F, 0x65, 0x6E, 0x65, 0x72, 0x67, 0x79, 0x5F, 0x63, 0x6C, 0x65, 0x61, 0x72, 0x5F, 0x73, 0x75, 0x64, 0x00, 0x00, 0x00);
			WRITE_MEMORY(sigPrcGaugeBaseArcade(), uint8_t, 0x73, 0x75, 0x64);
		}
		else //txt and prc
		{
			WRITE_MEMORY(songEnergyClearTxt(), uint8_t, 0x73, 0x6F, 0x6E, 0x67, 0x5F, 0x65, 0x6E, 0x65, 0x72, 0x67, 0x79, 0x5F, 0x63, 0x6C, 0x65, 0x61, 0x72, 0x5F, 0x74, 0x78, 0x74, 0x00, 0x00, 0x00);
			WRITE_MEMORY(sigPrcGaugeBaseArcade(), uint8_t, 0x70, 0x72, 0x63);
		}
	}
	
	if (xBarRank)
	{
		if (difficulty == 1) //normal
		{
			WRITE_MEMORY(sigSongEnergyReach(), uint8_t, 0x6E, 0x6F, 0x72, 0x6D);
			WRITE_MEMORY(sigSongEnergyBorder(), uint8_t, 0x6E, 0x6F, 0x72, 0x6D);
		}
		else if (difficulty == 2) //hard
		{
			WRITE_MEMORY(sigSongEnergyReach(), uint8_t, 0x68, 0x61, 0x72, 0x64);
			WRITE_MEMORY(sigSongEnergyBorder(), uint8_t, 0x68, 0x61, 0x72, 0x64);
		}
		else if (difficulty == 3) //extreme or ex-extreme
		{
			WRITE_MEMORY(sigSongEnergyReach(), uint8_t, 0x65, 0x78, 0x74, 0x72);
			WRITE_MEMORY(sigSongEnergyBorder(), uint8_t, 0x65, 0x78, 0x74, 0x72);
		}
		else //easy or tutorial
		{
			WRITE_MEMORY(sigSongEnergyReach(), uint8_t, 0x65, 0x61, 0x73, 0x79);
			WRITE_MEMORY(sigSongEnergyBorder(), uint8_t, 0x65, 0x61, 0x73, 0x79);
		}
	}
}

extern "C" __declspec(dllexport) void Init()
{
	printf("[X UI for MM+] Initializing...\n");
	try
	{
		config = toml::parse_file("config.toml");
		try
		{
			noSlides = config["No_Sliders_Effect"].value_or(false);
			biggerPercentage = config["Bigger_Percentage"].value_or(false);
			modifiersFix = config["Fix_Modifiers"].value_or(false);
			xBarRank = config["X_Ranking_Bar"].value_or(false);
			hitEffect = config["Hit_Effect"].value_or(0);
			enValue = config["English_Values"].value_or(false);
			judgementsValue = config["Judgements_Values"].value_or(false);
			altFailed = config["Alternative_Fail"].value_or(false);
		}
		catch (std::exception& exception)
		{
			char text[1024];
			sprintf_s(text, "Failed to parse config.toml:\n%s", exception.what());
			MessageBoxA(nullptr, text, "X UI for MM+", MB_OK | MB_ICONERROR);
		}
	}
	catch (std::exception& exception)
	{
		char text[1024];
		sprintf_s(text, "Failed to parse config.toml:\n%s", exception.what());
		MessageBoxA(nullptr, text, "X UI for MM+", MB_OK | MB_ICONERROR);
	}

	if (modifiersFix || xBarRank)
	{
		INSTALL_HOOK(_StartSong);
	}

	if (modifiersFix)
	{
		//hide original layers
		WRITE_MEMORY(sigOptionInfoHiddenA(), uint8_t, 0x00);
		WRITE_MEMORY(sigOptionInfoHispeedA(), uint8_t, 0x00);
		WRITE_MEMORY(sigOptionInfoSuddenA(), uint8_t, 0x00);
		WRITE_MEMORY(sigOptionInfoBase(), uint8_t, 0x00);
	}

	if (xBarRank)
	{
		//hide original layers
		WRITE_MEMORY(sigSongEnergyBorderExcellent(), uint8_t, 0x00);
		WRITE_MEMORY(sigSongEnergyBorderGreat(), uint8_t, 0x00);
		WRITE_MEMORY(sigSongEnergyEffReach(), uint8_t, 0x00);
	}

	if (enValue)
	{
		WRITE_MEMORY(sigValueTextFine01(), uint8_t, 0x76,0x61,0x6C,0x65,0x6E);
		WRITE_MEMORY(sigValueTextFine03(), uint8_t, 0x76,0x61,0x6C,0x65,0x6E);
		WRITE_MEMORY(sigValueTextSad(), uint8_t, 0x76,0x61,0x6C,0x65,0x6E);
		WRITE_MEMORY(sigValueTextWrong01(), uint8_t, 0x76,0x61,0x6C,0x65,0x6E);
		WRITE_MEMORY(sigValueTextWrong02(), uint8_t, 0x76,0x61,0x6C,0x65,0x6E);
		WRITE_MEMORY(sigValueTextWrong03(), uint8_t, 0x76,0x61,0x6C,0x65,0x6E);
		WRITE_MEMORY(sigValueTextWrong04(), uint8_t, 0x76,0x61,0x6C,0x65,0x6E);

		WRITE_MEMORY(sigComboTempoFine001(), uint8_t, 0x63,0x6F,0x6D,0x65,0x6E);
		WRITE_MEMORY(sigComboTempoFine010(), uint8_t, 0x63,0x6F,0x6D,0x65,0x6E);
		WRITE_MEMORY(sigComboTempoFine100(), uint8_t, 0x63,0x6F,0x6D,0x65,0x6E);
		WRITE_MEMORY(sigComboTempoFine100B(), uint8_t, 0x63,0x6F,0x6D,0x65,0x6E);
		WRITE_MEMORY(sigComboTempoFine1000(), uint8_t, 0x63,0x6F,0x6D,0x65,0x6E);

		WRITE_MEMORY(sigComboFine001(), uint8_t, 0x63,0x6F,0x6D,0x65,0x6E);
		WRITE_MEMORY(sigComboFine010(), uint8_t, 0x63,0x6F,0x6D,0x65,0x6E);
		WRITE_MEMORY(sigComboFine100(), uint8_t, 0x63,0x6F,0x6D,0x65,0x6E);
		WRITE_MEMORY(sigComboFine100B(), uint8_t, 0x63,0x6F,0x6D,0x65,0x6E);
		WRITE_MEMORY(sigComboFine1000(), uint8_t, 0x63,0x6F,0x6D,0x65,0x6E);
	}

	if (judgementsValue)
	{
		WRITE_MEMORY(sigValueTextFine01(), uint8_t, 0x61, 0x6C, 0x74);
		WRITE_MEMORY(sigValueTextFine03(), uint8_t, 0x61, 0x6C, 0x74);
		
		WRITE_MEMORY(sigComboTempoFine001(), uint8_t, 0x61, 0x6C, 0x74);
		WRITE_MEMORY(sigComboTempoFine010(), uint8_t, 0x61, 0x6C, 0x74);
		WRITE_MEMORY(sigComboTempoFine100(), uint8_t, 0x61, 0x6C, 0x74);
		WRITE_MEMORY(sigComboTempoFine100B(), uint8_t, 0x61, 0x6C, 0x74);
		WRITE_MEMORY(sigComboTempoFine1000(), uint8_t, 0x61, 0x6C, 0x74);

		WRITE_MEMORY(sigComboFine001(), uint8_t, 0x61, 0x6C, 0x74);
		WRITE_MEMORY(sigComboFine010(), uint8_t, 0x61, 0x6C, 0x74);
		WRITE_MEMORY(sigComboFine100(), uint8_t, 0x61, 0x6C, 0x74);
		WRITE_MEMORY(sigComboFine100B(), uint8_t, 0x61, 0x6C, 0x74);
		WRITE_MEMORY(sigComboFine1000(), uint8_t, 0x61, 0x6C, 0x74);

		WRITE_MEMORY(sigValueTextCool01(), uint8_t, 0x61, 0x6C, 0x74);
		WRITE_MEMORY(sigValueTextCool03(), uint8_t, 0x61, 0x6C, 0x74);

		WRITE_MEMORY(sigComboTempoCool001(), uint8_t, 0x61, 0x6C, 0x74);
		WRITE_MEMORY(sigComboTempoCool010(), uint8_t, 0x61, 0x6C, 0x74);
		WRITE_MEMORY(sigComboTempoCool100(), uint8_t, 0x61, 0x6C, 0x74);
		WRITE_MEMORY(sigComboTempoCool100B(), uint8_t, 0x61, 0x6C, 0x74);
		WRITE_MEMORY(sigComboTempoCool1000(), uint8_t, 0x61, 0x6C, 0x74);

		WRITE_MEMORY(sigComboCool001(), uint8_t, 0x61, 0x6C, 0x74);
		WRITE_MEMORY(sigComboCool010(), uint8_t, 0x61, 0x6C, 0x74);
		WRITE_MEMORY(sigComboCool100(), uint8_t, 0x61, 0x6C, 0x74);
		WRITE_MEMORY(sigComboCool100B(), uint8_t, 0x61, 0x6C, 0x74);
		WRITE_MEMORY(sigComboCool1000(), uint8_t, 0x61, 0x6C, 0x74);
	}

	if (noSlides)
	{
		WRITE_MEMORY(sigHitEff00L(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x65, 0x66, 0x66, 0x30, 0x30, 0x00, 0x00);
		WRITE_MEMORY(sigHitEff00R(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x65, 0x66, 0x66, 0x30, 0x30, 0x00, 0x00);
		WRITE_MEMORY(sigHitEff01L(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x65, 0x66, 0x66, 0x30, 0x31, 0x00, 0x00);
		WRITE_MEMORY(sigHitEff01R(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x65, 0x66, 0x66, 0x30, 0x31, 0x00, 0x00);
	}

	if (biggerPercentage)
	{
		WRITE_MEMORY(sigPEnergyNum01C(), uint8_t, 0x62);
		WRITE_MEMORY(sigPEnergyNum02C(), uint8_t, 0x62);
		WRITE_MEMORY(sigPEnergyNum03C(), uint8_t, 0x62);
		WRITE_MEMORY(sigPEnergyNum04C(), uint8_t, 0x62);
		WRITE_MEMORY(sigPEnergyNum05C(), uint8_t, 0x62);
		WRITE_MEMORY(sigPEnergyNum06C(), uint8_t, 0x62);
		WRITE_MEMORY(sigPEnergyNum07C(), uint8_t, 0x62);
	}

	if (hitEffect!=0)
	{
		switch (hitEffect) {
		case 1: //Cute
			WRITE_MEMORY(sigHitEff00(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x63, 0x63, 0x63);
			WRITE_MEMORY(sigHitEff01(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x63, 0x63, 0x63);
			WRITE_MEMORY(sigHitEff02(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x63, 0x63, 0x63);
			WRITE_MEMORY(sigHitEff03(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x63, 0x63, 0x63);
			WRITE_MEMORY(sigHitEff04(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x63, 0x63, 0x63);
			WRITE_MEMORY(sigHitEff00L(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x63, 0x63, 0x63);
			WRITE_MEMORY(sigHitEff00R(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x63, 0x63, 0x63);
			WRITE_MEMORY(sigHitEff01L(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x63, 0x63, 0x63);
			WRITE_MEMORY(sigHitEff01R(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x63, 0x63, 0x63);
			WRITE_MEMORY(sigHitEffSlide01L(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x63, 0x63, 0x63);
			WRITE_MEMORY(sigHitEffSlide01R(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x63, 0x63, 0x63);
			break;

		case 2: //Cool
			WRITE_MEMORY(sigHitEff00(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x63, 0x72, 0x63);
			WRITE_MEMORY(sigHitEff01(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x63, 0x72, 0x63);
			WRITE_MEMORY(sigHitEff02(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x63, 0x72, 0x63);
			WRITE_MEMORY(sigHitEff03(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x63, 0x72, 0x63);
			WRITE_MEMORY(sigHitEff04(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x63, 0x72, 0x63);
			WRITE_MEMORY(sigHitEff00L(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x63, 0x72, 0x63);
			WRITE_MEMORY(sigHitEff00R(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x63, 0x72, 0x63);
			WRITE_MEMORY(sigHitEff01L(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x63, 0x72, 0x63);
			WRITE_MEMORY(sigHitEff01R(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x63, 0x72, 0x63);
			WRITE_MEMORY(sigHitEffSlide01L(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x63, 0x72, 0x63);
			WRITE_MEMORY(sigHitEffSlide01R(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x63, 0x72, 0x63);
			break;

		case 3: //Elegant
			WRITE_MEMORY(sigHitEff00(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x73, 0x62, 0x63);
			WRITE_MEMORY(sigHitEff01(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x73, 0x62, 0x63);
			WRITE_MEMORY(sigHitEff02(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x73, 0x62, 0x63);
			WRITE_MEMORY(sigHitEff03(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x73, 0x62, 0x63);
			WRITE_MEMORY(sigHitEff04(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x73, 0x62, 0x63);
			WRITE_MEMORY(sigHitEff00L(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x73, 0x62, 0x63);
			WRITE_MEMORY(sigHitEff00R(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x73, 0x62, 0x63);
			WRITE_MEMORY(sigHitEff01L(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x73, 0x62, 0x63);
			WRITE_MEMORY(sigHitEff01R(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x73, 0x62, 0x63);
			WRITE_MEMORY(sigHitEffSlide01L(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x73, 0x62, 0x63);
			WRITE_MEMORY(sigHitEffSlide01R(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x73, 0x62, 0x63);
			break;

		case 4: //Classic
			WRITE_MEMORY(sigHitEff00(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x6E, 0x74, 0x63);
			WRITE_MEMORY(sigHitEff01(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x6E, 0x74, 0x63);
			WRITE_MEMORY(sigHitEff02(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x6E, 0x74, 0x63);
			WRITE_MEMORY(sigHitEff03(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x6E, 0x74, 0x63);
			WRITE_MEMORY(sigHitEff04(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x6E, 0x74, 0x63);
			WRITE_MEMORY(sigHitEff00L(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x6E, 0x74, 0x63);
			WRITE_MEMORY(sigHitEff00R(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x6E, 0x74, 0x63);
			WRITE_MEMORY(sigHitEff01L(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x6E, 0x74, 0x63);
			WRITE_MEMORY(sigHitEff01R(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x6E, 0x74, 0x63);
			WRITE_MEMORY(sigHitEffSlide01L(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x6E, 0x74, 0x63);
			WRITE_MEMORY(sigHitEffSlide01R(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x6E, 0x74, 0x63);
			break;

		case 5: //Quirky
			WRITE_MEMORY(sigHitEff00(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x75, 0x63, 0x63);
			WRITE_MEMORY(sigHitEff01(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x75, 0x63, 0x63);
			WRITE_MEMORY(sigHitEff02(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x75, 0x63, 0x63);
			WRITE_MEMORY(sigHitEff03(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x75, 0x63, 0x63);
			WRITE_MEMORY(sigHitEff04(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x75, 0x63, 0x63);
			WRITE_MEMORY(sigHitEff00L(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x75, 0x63, 0x63);
			WRITE_MEMORY(sigHitEff00R(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x75, 0x63, 0x63);
			WRITE_MEMORY(sigHitEff01L(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x75, 0x63, 0x63);
			WRITE_MEMORY(sigHitEff01R(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x75, 0x63, 0x63);
			WRITE_MEMORY(sigHitEffSlide01L(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x75, 0x63, 0x63);
			WRITE_MEMORY(sigHitEffSlide01R(), uint8_t, 0x68, 0x69, 0x74, 0x5F, 0x75, 0x63, 0x63);
			break;

		default:
			break;
		}
	}

	if (altFailed)
	{
		WRITE_MEMORY(sigFailedInfo(), uint8_t, 0x61, 0x6C, 0x74, 0x65, 0x72, 0x6E);
	}
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}