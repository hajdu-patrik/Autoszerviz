/**
 *  \file Applikacio.cpp
 *  Ez a fájl az autószerviz nyilvántartó rendszer belépési pontja, amely bemutatja a rendszer alapvetõ mûködését és fõ funkcióit.
 */

#include "Teszt.h"
#include "MainSegedFuggvenyek.h"
#include "SzervizNyilvantartoRendszer.h"

#include <iostream>
#include <string>

int main() {
    SzervizNyilvantartoRendszer autoszervizAdatbazis;
    int valasztottMenu;

    
	// Fájlok betöltése, hogy ha szûkséges teszt adatokkal induljon a program
    try {
        autoszervizAdatbazis.betoltesFajlbol("init_ugyfel_ufl.txt");
        autoszervizAdatbazis.betoltesFajlbol("init_auto_auo.txt");
    }
    catch (const std::exception& e) {
        std::cerr << "Hiba tortent a fajl beolvasasakor: " << e.what() << std::endl;
        return 1;
    }
    
    do {
        menuOpciok();
        std::cin >> valasztottMenu;
        torolKonzol();

        switch (valasztottMenu) {
            case 1:
                muveletFuttato(kiListazo, autoszervizAdatbazis, "Sikeres listazas!", "Sikeres kilepes!");
                break;

            case 2:
                muveletFuttato(ugyfelAutoAdd, autoszervizAdatbazis, "Sikeres felvetel!", "Sikeres kilepes!");
                break;

            case 3:
                muveletFuttato(ugyfelAutoFrissit, autoszervizAdatbazis, "Sikeres frissites!", "Sikeres kilepes!");
                break;

            case 4:
                muveletFuttato(ugyfelAutoTorlo, autoszervizAdatbazis, "Sikeres torles!", "Sikeres kilepes!");
                break;

            case 5:
                muveletFuttato(ugyfelKereses, autoszervizAdatbazis, "Sikeres kereses!", "Sikeres kilepes!");
                break;

            case 6:
                muveletFuttato(autoKereses, autoszervizAdatbazis, "Sikeres kereses!", "Sikeres kilepes!");
                break;

            case 7:
                muveletFuttato(ujSzervizMuvelet, autoszervizAdatbazis, "Sikeres szerviz muvelet rogzitese!", "Sikeres kilepes!");
                break;


            case 8: {
                if (!fajlNevHelyessegBiztosito(true, autoszervizAdatbazis)) {
                    torolKonzol();
                    std::cout << "\t=== Sikeres kilepes! ===";
                    break;
                }
                torolKonzol();
                std::cout << "\t=== Sikeres fajlba iras! ===";
                break;
            }

            case 9: {
                if (!fajlNevHelyessegBiztosito(false, autoszervizAdatbazis)) {
                    torolKonzol();
                    std::cout << "\t=== Sikeres kilepes! ===";
                    break;
                }
                torolKonzol();
                std::cout << "\t=== Sikeres fajlbol olvasas! ===";
                break;
            }

            case 0:  {
                kiirASCII2();
                break;
            }

            default: {
                std::cout << "\t>>> Ervenytelen valasztas! Probald ujra! <<<";
                break;
            }
        }
    } while (valasztottMenu != 0);

    return 0;
}