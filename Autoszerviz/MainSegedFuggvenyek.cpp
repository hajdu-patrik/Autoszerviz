/**
*	\file MainSegedFuggvenyek.cpp
*	A fõprogram (main) menürendszerének vizuális megjelenítéséhez és mûködéséhez
*	szükséges segédfüggvények implementációját tartalmazza.
*/

#include "MainSegedFuggvenyek.h"
#include "SzervizNyilvantartoRendszer.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>  // system()
#include <limits>   // numeric_limits
#include <cstdio>   // getchar()

/// "Autoszerviz" felirat ASCII art kiírása a konzolra, tabulátorral behúzva
void kiirASCII1() {
    std::cout <<
        "\n\n\t    /\\         | |                                (_)\n"
        "\t   /  \\  _    _| |_ ___    ___ _______ _ ______   ___ ____\n"
        "\t  / /\\ \\| |  | | __/ _ \\ / __ |_  /  _ \\'  __\\ \\ / / |_  /\n"
        "\t / ____ \\ | _| | || (_) \\__   \\/ /   __/  |   \\ V /| |/ /\n"
        "\t/_/    \\_\\__,_ |\\__\\___/ |___ /___\\___ |__|    \\_/ |_/___/\n\n";
}

/// "Arrivederci" felirat ASCII art kiírása a konzolra, tabulátorral behúzva
void kiirASCII2() {
    std::cout <<
        "\n\n\t    /\\             (_)             | |             (_)\n"
        "\t   /  \\   _ __ _ __ ___   _____  __| | ___ _ __ ___ _ \n"
        "\t  / /\\ \\ | '__| '__| \\ \\ / / _ \\/ _` |/ _ \\ '__/ __| |\n"
        "\t / ____ \\| |  | |  | |\\ V /  __/ (_| |  __/ | | (__| |\n"
        "\t/_/    \\_\\_|  |_|  |_| \\_/ \\___|\\__,_|\\___|_|  \\___|_|\n\n";
}

/// A program által biztosított funkciók használatához szükséges menü opciók kiírása
void menuOpciok() {
    kiirASCII1();
    std::cout << "\n\t1. Uj ugyfel es auto felvetele\n";
    std::cout << "\t2. Ugyfel keresese nev alapjan\n";
    std::cout << "\t3. Auto keresese rendszam alapjan\n";
    std::cout << "\t4. Javitas rogzitese\n";
    std::cout << "\t5. Autok vagy Ugyfelek adatainak fajlba irasa\n";
    std::cout << "\t6. Autok vagy Ugyfelek adatainak fajbol beolvasasa\n";
    std::cout << "\t0. Kilepes\n\n";
    std::cout << "\tValassz egy lehetoseget: ";
}

/// Megvárja, amíg a felhasználó lenyomja az Enter billentyût.
/// Általában hibaüzenetek vagy információk megjelenítése után használatos, 
/// hogy a felhasználónak legyen ideje elolvasni azokat.
void varakozasEnterre() {
    std::cout << "\n\tNyomj Entert a folytatashoz...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();  // várakozás
}

/// Törli a konzol képernyõt
void torolKonzol() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/// Ellenõrzi, hogy a megadott fájl létezik-e.
/// @param f - A vizsgált fájl neve (elérési útvonal is lehet).
/// @return - true, ha a fájl létezik, különben false.
bool letezikAFajl(const std::string& f) {
    std::ifstream fajl(f);
    return fajl.good();
}

/// Fájlnév bekérése, formátumának és létezésének ellenõrzése.
/// Elfogadja az "exit" szót is, ami visszalépést jelent a fõmenübe.
/// @param mentesE - A függvény célját jelzõ kapcsoló (mentés vagy betöltés)
/// @param aDB - A szerviz adatbázis objektum referenciája
/// @return true, ha sikeres volt a mûvelet, false ha "exit"-tel kiléptünk
bool fajlNevHelyessegBiztosito(bool mentesE, SzervizNyilvantartoRendszer& aDB) {
    std::string fajlNev;
    while (true) {
        torolKonzol();
        kiirASCII1();
        std::cout << "\tAdd meg a fajl nevet (vagy 'exit' a kilepeshez): ";
        std::cin >> fajlNev;

        if (fajlNev == "exit") {
            return false;  // Jelzi, hogy visszalépett
        }

        bool ugyfelFajl = fajlNev.find("_ufl.txt") != std::string::npos;
        bool autoFajl = fajlNev.find("_auo.txt") != std::string::npos;

        if (!ugyfelFajl && !autoFajl) {
            std::cout << "\n\tIsmeretlen fajlformatum! (Helyes: xxx_auo.txt vagy xxx_ufl.txt)";
        }
        else if (!mentesE && !letezikAFajl(fajlNev)) {
            std::cout << "\n\tA megadott fajl nem letezik!";
        }
        else {
            // fájlnév helyes, mûvelet végezhetõ
            if (mentesE)
                aDB.mentesFajlba(fajlNev);
            else
                aDB.betoltesFajlbol(fajlNev);
            return true;
        }

        varakozasEnterre();
    }
}