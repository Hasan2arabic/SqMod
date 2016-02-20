// ------------------------------------------------------------------------------------------------
#include "Misc/Vehicle.hpp"

// ------------------------------------------------------------------------------------------------
#include <cstring>
#include <algorithm>

// ------------------------------------------------------------------------------------------------
namespace SqMod {

// ------------------------------------------------------------------------------------------------
static String CS_Vehicle_Names[] = {
"Landstalker",         "Idaho",               "Stinger",             "Linerunner",          "Perennial",
"Sentinel",            "Rio",                 "Firetruck",           "Trashmaster",         "Stretch",
"Manana",              "Infernus",            "Voodoo",              "Pony",                "Mule",
"Cheetah",             "Ambulance",           "FBI Washington",      "Moonbeam",            "Esperanto",
"Taxi",                "Washington",          "Bobcat",              "Mr. Whoopee",         "BF Injection",
"Hunter",              "Police",              "Enforcer",            "Securicar",           "Banshee",
"Predator",            "Bus",                 "Rhino",               "Barracks OL",         "Cuban Hermes",
"Helicopter",          "Angel",               "Coach",               "Cabbie",              "Stallion",
"Rumpo",               "RC Bandit",           "Romero's Hearse",     "Packer",              "Sentinel XS",
"Admiral",             "Squalo",              "Sea Sparrow",         "Pizza Boy",           "Gang Burrito",
"Airtrain",            "Deaddodo",            "Speeder",             "Reefer",              "Tropic",
"Flatbed",             "Yankee",              "Caddy",               "Zebra Cab",           "Top Fun",
"Skimmer",             "PCJ-600",             "Faggio",              "Freeway",             "RC Baron",
"RC Raider",           "Glendale",            "Oceanic",             "Sanchez",             "Sparrow",
"Patriot",             "Love Fist",           "Coast Guard",         "Dinghy",              "Hermes",
"Sabre",               "Sabre Turbo",         "Phoenix",             "Walton",              "Regina",
"Comet",               "Deluxo",              "Burrito",             "Spand Express",       "Marquis",
"Baggage Handler",     "Kaufman Cab",         "Maverick",            "VCN Maverick",        "Rancher",
"FBI Rancher",         "Virgo",               "Greenwood",           "Cuban Jetmax",        "Hotring Racer #1",
"Sandking",            "Blista Compact",      "Police Maverick",     "Boxville",            "Benson",
"Mesa Grande",         "RC Goblin",           "Hotring Racer #2",    "Hotring Racer #3",    "Bloodring Banger #1",
"Bloodring Banger #2", "Vice Squad Cheetah",  ""
};

// ------------------------------------------------------------------------------------------------
CCStr GetAutomobileName(Uint32 id)
{
    return (id < 130 || id > 236) ? _SC("") : CS_Vehicle_Names[id-130].c_str();
}

// ------------------------------------------------------------------------------------------------
void SetAutomobileName(Uint32 id, CCStr name)
{
    if (id >= 130 || id <= 236)
        CS_Vehicle_Names[id-130].assign(name);
}

// ------------------------------------------------------------------------------------------------
Int32 GetAutomobileID(CCStr name)
{
    // Clone the string into an editable version
    String str(name);
    // Strip non alphanumeric characters from the name
    str.erase(std::remove_if(str.begin(), str.end(), std::not1(std::ptr_fun(::isalnum))), str.end());
    // Convert the string to lowercase
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    // See if we still have a valid name after the cleanup
    if(str.empty())
        return SQMOD_UNKNOWN;
    // Grab the actual length of the string
    Uint32 len = static_cast< Uint32 >(str.length());
    // Get the most significant characters used to identify a vehicle
    CharT a = str[0], b = 0, c = 0, d = str[len-1];
    // Look for deeper specifiers
    if(str.length() >= 3)
    {
        c = str[2];
        b = str[1];
    }
    else if(str.length() >= 2)
        b = str[1];
    // Search for a pattern in the name
    switch (a)
    {
        // [A]dmiral
        // [A]irtrain
        // [A]mbulance
        // [A]ngel
        case 'a':
            switch (b)
            {
                // [Ad]miral
                case 'd': return SQMOD_VEHICLE_ADMIRAL;
                // [Ai]rtrain
                case 'i': return SQMOD_VEHICLE_AIRTRAIN;
                // [Am]bulance
                case 'm': return SQMOD_VEHICLE_AMBULANCE;
                // [An]gel
                case 'n': return SQMOD_VEHICLE_ANGEL;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }

        // [B]aggage Handler
        // [B]anshee
        // [B]arracks OL
        // [B]enson
        // [B]F Injection
        // [B]lista Compact
        // [B]loodring Banger #1
        // [B]loodring Banger #2
        // [B]obcat
        // [B]oxville
        // [B]urrito
        // [B]us
        case 'b':
            switch (b)
            {
                // [Ba]ggage Handler
                // [Ba]nshee
                // [Ba]rracks OL
                case 'a':
                    // [Bag]gage Handler
                    if (c == 'g') return SQMOD_VEHICLE_BAGGAGEHANDLER;
                    // [Ban]shee
                    else if (c == 'n') return SQMOD_VEHICLE_BANSHEE;
                    // [Bar]racks OL
                    else if (c == 'r') return SQMOD_VEHICLE_BARRACKS;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Be]nson
                case 'e': return SQMOD_VEHICLE_BENSON;
                // [BF] [I]njection
                case 'f':
                case 'i': return SQMOD_VEHICLE_BFINJECTION;
                // [Bl]ista Compact
                // [Bl]oodring Banger #1
                // [Bl]oodring Banger #2
                case 'l':
                    // [Bli]sta [C]ompact
                    if (b == 'c' || c == 'i') return SQMOD_VEHICLE_BLISTACOMPACT;
                    // [Blo]odring [B]anger (#1|A)
                    else if ((b == 'b' || c == 'o') && (d == '1' || d == 'a')) return SQMOD_VEHICLE_BLOODRINGBANGER1;
                    // [Blo]odring [B]anger (#2|B)
                    else if ((b == 'b' || c == 'o') && (d == '2' || d == 'b')) return SQMOD_VEHICLE_BLOODRINGBANGER2;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Bo]bcat
                // [Bo]xville
                case 'o':
                    // [Bob]cat
                    if (c == 'b') return SQMOD_VEHICLE_BOBCAT;
                    // [Box]ville
                    else if (c == 'x') return SQMOD_VEHICLE_BOXVILLE;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Bu]rrito
                // [Bu]s
                case 'u':
                    // [Bur]rito
                    if (c == 'r') return SQMOD_VEHICLE_BURRITO;
                    // [Bus]
                    else if (c == 's') return SQMOD_VEHICLE_BUS;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }
        // [C]abbie
        // [C]addy
        // [C]heetah
        // [C]oach
        // [C]oast Guard
        // [C]omet
        // [C]uban Hermes
        // [C]uban Jetmax
        case 'c':
            switch (b)
            {
                // [Ca]bbie
                // [Ca]ddy
                case 'a':
                    // [Cab]bie
                    if (c == 'b') return SQMOD_VEHICLE_CABBIE;
                    // [Cad]dy
                    else if (c == 'd') return SQMOD_VEHICLE_CADDY;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Ch]eetah
                case 'h': return SQMOD_VEHICLE_CHEETAH;
                // [Co]ach
                // [Co]ast Guard
                // [Co]met
                case 'o':
                    // [Coa]c[h]
                    if (c == 'a' && d == 'h') return SQMOD_VEHICLE_COACH;
                    // [Coa]s[t] Guar[d]
                    else if (c == 'a' && (d == 't' || d == 'd')) return SQMOD_VEHICLE_COASTGUARD;
                    // [Co]met
                    else if (c == 'm') return SQMOD_VEHICLE_COMET;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Cu]ban Hermes
                // [Cu]ban Jetmax
                case 'u':
                    // [Cub]an [H]erme[s]
                    if ((len > 4 && str[5] == 'h') || (d == 's' || d == 'h')) return SQMOD_VEHICLE_CUBANHERMES;
                    // [Cub]an [J]etma[x]
                    if ((len > 4 && str[5] == 'j') || (d == 'x' || d == 'j')) return SQMOD_VEHICLE_CUBANJETMAX;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }
        // [D]eaddodo
        // [D]eluxo
        // [D]inghy
        case 'd':
            switch (b)
            {
                // [De]addodo
                // [De]luxo
                case 'e':
                    // [Dea]ddodo
                    if (c == 'a') return SQMOD_VEHICLE_DEADDODO;
                    // [Del]uxo
                    else if (c == 'l') return SQMOD_VEHICLE_DELUXO;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Di]nghy
                case 'i': return SQMOD_VEHICLE_DINGHY;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }
        // [E]speranto
        // [E]nforcer
        case 'e':
            // [Es]peranto
            if (b && b == 's') return SQMOD_VEHICLE_ESPERANTO;
            // [En]forcer
            else if (b && b == 'n') return SQMOD_VEHICLE_ENFORCER;
            // Default to unknwon
            else return SQMOD_UNKNOWN;
        // [F]aggio
        // [F]BI Rancher
        // [F]BI Washington
        // [F]iretruck
        // [F]latbed
        // [F]reeway
        case 'f':
            switch (b)
            {
                // [Fa]ggio
                case 'a': return SQMOD_VEHICLE_FAGGIO;
                // [FB]I Rancher
                // [FB]I Washington
                case 'b':
                    // [FB]I [R]anche[r]
                    if ((len > 2 && str[3] == 'r') || d == 'r') return SQMOD_VEHICLE_FBIRANCHER;
                    // [FB]I [W]ashingto[n]
                    else if ((len > 2 && str[3] == 'w') || (d == 'n' || d == 'w')) return SQMOD_VEHICLE_FBIWASHINGTON;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Fi]retruck
                case 'i': return SQMOD_VEHICLE_FIRETRUCK;
                // [Fl]atbed
                case 'l': return SQMOD_VEHICLE_FLATBED;
                // [Fr]eeway
                case 'r': return SQMOD_VEHICLE_FREEWAY;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }
        // [G]ang Burrito
        // [G]lendale
        // [G]reenwood
        case 'g':
            switch (b)
            {
                // [Ga]ng Burrito
                case 'a': return SQMOD_VEHICLE_GANGBURRITO;
                // [Gl]endale
                case 'l': return SQMOD_VEHICLE_GLENDALE;
                // [Gr]eenwood
                case 'r': return SQMOD_VEHICLE_GREENWOOD;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }
        // [H]elicopter
        // [H]ermes
        // [H]otring Racer (#1|A)(#2|B)(#3|C)
        // [H]unter
        case 'h':
            switch (b)
            {
                // [He]licopter
                // [He]rmes
                case 'e':
                    // [Hel]icopter
                    if (c == 'l') return SQMOD_VEHICLE_HELICOPTER;
                    // [Her]mes
                    else if (c == 'r') return SQMOD_VEHICLE_HERMES;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Ho]tring Racer (#1|A)(#2|B)(#3|C)
                case 'o':
                    switch (d)
                    {
                        case '1':
                        case 'a': return SQMOD_VEHICLE_HOTRINGRACER1;
                        case '2':
                        case 'b': return SQMOD_VEHICLE_HOTRINGRACER2;
                        case '3':
                        case 'c': return SQMOD_VEHICLE_HOTRINGRACER3;
                        // Default to unknwon
                        default: return SQMOD_UNKNOWN;
                    }
                // [Hu]nter
                case 'u': return SQMOD_VEHICLE_HUNTER;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }
        // [I]daho
        // [I]nfernus
        case 'i':
            // [Id]aho
            if (b && b == 'd') return SQMOD_VEHICLE_IDAHO;
            // [In]fernus
            else if (b && b == 'n') return SQMOD_VEHICLE_INFERNUS;
            // Default to unknwon
            else return SQMOD_UNKNOWN;
        // [K]aufman Cab
        case 'k': return SQMOD_VEHICLE_KAUFMANCAB;
        // [L]andstalker
        // [L]inerunner
        // [L]ove Fist
        case 'l':
            switch (b)
            {
                // [La]ndstalker
                case 'a': return SQMOD_VEHICLE_LANDSTALKER;
                // [Li]nerunner
                case 'i': return SQMOD_VEHICLE_LINERUNNER;
                // [Lo]ve Fist
                case 'o': return SQMOD_VEHICLE_LOVEFIST;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;

            }
        // [M]anana
        // [M]arquis
        // [M]averick
        // [M]esa Grande
        // [M]oonbeam
        // [M]r. Whoopee
        // [M]ule
        case 'm':
            switch (b)
            {
                // [Ma]nana
                // [Ma]rquis
                // [Ma]verick
                case 'a':
                    // [Man]ana
                    if (c == 'n') return SQMOD_VEHICLE_MANANA;
                    // [Mar]quis
                    else if (c == 'r') return SQMOD_VEHICLE_MARQUIS;
                    // [Mav]erick
                    else if (c == 'v') return SQMOD_VEHICLE_MAVERICK;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Me]sa Grande
                case 'e': return SQMOD_VEHICLE_MESAGRANDE;
                // [Mo]onbeam
                case 'o': return SQMOD_VEHICLE_MOONBEAM;
                // [Mr]. Whoopee
                case 'r': return SQMOD_VEHICLE_MRWHOOPEE;
                // [Mu]le
                case 'u': return SQMOD_VEHICLE_MULE;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }
        // [O]ceanic
        case 'o': return SQMOD_VEHICLE_OCEANIC;
        // [P]acker
        // [P]atriot
        // [P]CJ-600
        // [P]erennial
        // [P]hoenix
        // [P]izza Boy
        // [P]olice
        // [P]olice Maverick
        // [P]ony
        // [P]redator
        case 'p':
            switch (b)
            {
                // [Pa]cker
                // [Pa]triot
                case 'a':
                    // [Pac]ker
                    if (c == 'c') return SQMOD_VEHICLE_PACKER;
                    // [Pat]riot
                    else if (c == 't') return SQMOD_VEHICLE_PATRIOT;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [PC]J-600
                case 'c': return SQMOD_VEHICLE_PCJ600;
                // [Pe]rennial
                case 'e': return SQMOD_VEHICLE_PERENNIAL;
                // [Ph]oenix
                case 'h': return SQMOD_VEHICLE_PHOENIX;
                // [Pi]zza Boy
                case 'i':
                // [Po]lice
                // [Po]lice Maverick
                // [Po]ny
                case 'o':
                    // [Po]lice
                    if (d == 'e') return SQMOD_VEHICLE_POLICE;
                    // [Po]lice Maverick
                    else if ((len > 5 && str[6] == 'm') || (d == 'k' || d == 'm')) return SQMOD_VEHICLE_POLICEMAVERICK;
                    // [Po]ny
                    else if (c == 'n') return SQMOD_VEHICLE_PONY;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Pr]edator
                case 'r': return SQMOD_VEHICLE_PREDATOR;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }
        // [R]ancher
        // [R]C Bandit
        // [R]C Baron
        // [R]C Goblin
        // [R]C Raider
        // [R]eefer
        // [R]egina
        // [R]hino
        // [R]io
        // [R]omero's Hearse
        // [R]umpo
        case 'r':
            switch (b)
            {
                // [Ra]ncher
                case 'a': return SQMOD_VEHICLE_RANCHER;
                // [RC] Bandit
                // [RC] Baron
                // [RC] Goblin
                // [RC] Raider
                case 'c':
                    // [RC] [B]andi[t]
                    if (c == 'b' && d == 't') return SQMOD_VEHICLE_RCBANDIT;
                    // [RC] [B]aro[n]
                    else if (c == 'b' && d == 'n') return SQMOD_VEHICLE_RCBARON;
                    // [RC] [G]oblin
                    else if (c == 'g') return SQMOD_VEHICLE_RCGOBLIN;
                    // [RC] [R]aide[r]
                    else if (c == 'r' || d == 'r') return SQMOD_VEHICLE_RCRAIDER;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Re]efer
                // [Re]gina
                case 'e':
                    // [Ree]fer
                    if (c == 'e' || d == 'r') return SQMOD_VEHICLE_REEFER;
                    // [Reg]ina
                    else if (c == 'g' || d == 'a') return SQMOD_VEHICLE_REGINA;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Rh]ino
                case 'h': return SQMOD_VEHICLE_RHINO;
                // [Ri]o
                case 'i': return SQMOD_VEHICLE_RIO;
                // [Ro]mero's Hearse
                case 'o': return SQMOD_VEHICLE_HEARSE;
                // [Ru]mpo
                case 'u': return SQMOD_VEHICLE_RUMPO;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }
        // [S]abre
        // [S]abre Turbo
        // [S]anchez
        // [S]andking
        // [S]ea Sparrow
        // [S]ecuricar
        // [S]entinel
        // [S]entinel XS
        // [S]kimmer
        // [S]pand Express
        // [S]parrow
        // [S]peeder
        // [S]qualo
        // [S]tallion
        // [S]tinger
        // [S]tretch
        case 's':
            switch (b)
            {
                // [Sa]bre
                // [Sa]bre Turbo
                // [Sa]nchez
                // [Sa]ndking
                case 'a':
                    // [Sab]r[e]
                    if (c == 'b' && d == 'e') return SQMOD_VEHICLE_SABRE;
                    // [Sab]re [T]urb[o]
                    else if ((c == 'b' && d == 'o') || (len > 4 && str[5 ]== 't')) return SQMOD_VEHICLE_SABRETURBO;
                    // [Sa]n[c]he[z]
                    else if (d == 'c' || d == 'z') return SQMOD_VEHICLE_SANCHEZ;
                    // [Sa]n[d]kin[g]
                    else if (d == 'd' || d == 'g') return SQMOD_VEHICLE_SANDKING;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Se]a Sparrow
                // [Se]curicar
                // [Se]ntinel
                // [Se]ntinel XS
                case 'e':
                    // [Sea] Sparro[w]
                    if (c == 'e' || d == 'w') return SQMOD_VEHICLE_SEASPARROW;
                    // [Sec]urica[r]
                    else if (c == 'c' || d == 'r') return SQMOD_VEHICLE_SECURICAR;
                    // [Sen]tine[l]
                    else if (c == 'n' && d == 'l') return SQMOD_VEHICLE_SENTINEL;
                    // [Sen]tinel X[S]
                    else if (c == 'n' && d == 's') return SQMOD_VEHICLE_SENTINELXS;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Sk]immer
                case 'k': return SQMOD_VEHICLE_SKIMMER;
                // [Sp]and Express
                // [Sp]arrow
                // [Sp]eeder
                case 'p':
                    // [Spa]nd [E]xpres[s]
                    if (c == 'a' || ((len > 4 && str[5] == 'e') || d == 's')) return SQMOD_VEHICLE_SPANDEXPRESS;
                    // [Spa]rro[w]
                    else if (d == 'w' && (c == 'a' && d == 'w')) return SQMOD_VEHICLE_SPARROW;
                    // [Spe]ede[r]
                    else if (c == 'e' || d == 'r') return SQMOD_VEHICLE_SPEEDER;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Sq]ualo
                case 'q': return SQMOD_VEHICLE_SQUALO;
                // [St]allion
                // [St]inger
                // [St]retch
                case 't':
                    // [Sta]llion
                    if (c == 'a') return SQMOD_VEHICLE_STALLION;
                    // [Sti]nger
                    if (c == 'i') return SQMOD_VEHICLE_STINGER;
                    // [Str]etch
                    if (c == 'r') return SQMOD_VEHICLE_STRETCH;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }
        // [T]axi
        // [T]op Fun
        // [T]rashmaster
        // [T]ropic
        case 't':
            switch (b)
            {
                // [Ta]xi
                case 'a': return SQMOD_VEHICLE_TAXI;
                // [To]p Fun
                case 'o': return SQMOD_VEHICLE_TOPFUN;
                // [Tr]ashmaster
                // [Tr]opic
                case 'r':
                    // [Tr]ashmaster
                    if (c == 'a') return SQMOD_VEHICLE_TRASHMASTER;
                    // [Tr]opic
                    if (c == 'o') return SQMOD_VEHICLE_TROPIC;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }
        // [V]CN Maverick
        // [V]ice Squad Cheetah
        // [V]irgo
        // [V]oodoo
        case 'v':
            switch (b)
            {
                // [VC]N Maverick
                case 'c': return SQMOD_VEHICLE_VCNMAVERICK;
                // [Vi]ce Squad Cheetah
                // [Vi]rgo
                case 'i':
                    // [Vic]e Squad Cheetah
                    if (c == 'a') return SQMOD_VEHICLE_VICECHEE;
                    // [Vir]go
                    if (c == 'o') return SQMOD_VEHICLE_VIRGO;
                    // Default to unknwon
                    else return SQMOD_UNKNOWN;
                // [Vo]odoo
                case 'o': return SQMOD_VEHICLE_VOODOO;
                // Default to unknwon
                default: return SQMOD_UNKNOWN;
            }
        // [W]alton
        // [W]ashington
        case 'w':
            // [Wa]lton
            if (b == 'a' && c == 'l') return SQMOD_VEHICLE_WALTON;
            // [Wa]shington
            else if (b == 'a' && c == 's') return SQMOD_VEHICLE_WASHINGTON;
            // Default to unknwon
            else return SQMOD_UNKNOWN;
        // [Y]ankee
        case 'y': return SQMOD_VEHICLE_YANKEE;
        // [Z]ebra Cab
        case 'z': return SQMOD_VEHICLE_ZEBRACAB;
        // Default to unknwon
        default: return SQMOD_UNKNOWN;
    }
}

// ------------------------------------------------------------------------------------------------
bool IsAutomobileValid(Int32 id)
{
    return (strlen(GetAutomobileName(id)) > 0);
}

// ------------------------------------------------------------------------------------------------
bool IsModelActuallyWeapon(Int32 id)
{
    switch (id)
    {
        case 259:
        case 260:
        case 261:
        case 262:
        case 263:
        case 264:
        case 265:
        case 266:
        case 267:
        case 268:
        case 269:
        case 270:
        case 271:
        case 272:
        case 274:
        case 275:
        case 276:
        case 277:
        case 278:
        case 279:
        case 280:
        case 281:
        case 282:
        case 283:
        case 284:
        case 285:
        case 286:
        case 287:
        case 288:
        case 289:
        case 290:
        case 291:   return true;
        default:    return false;
    }
}

// ------------------------------------------------------------------------------------------------


} // Namespace:: SqMod
