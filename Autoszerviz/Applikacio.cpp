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
        case 1: {
                if (!kiListazo(autoszervizAdatbazis)) {
                    torolKonzol();
                    std::cout << "\t=== Sikeres kilepes! (exit) ===";
                    break;
                }
                break;
            }

            case 2: {
                //ujUgyfelAuto(autoszervizAdatbazis);
                break;
            }

            case 3: {
                //ugyfelKereses(autoszervizAdatbazis);
                break;
            }

            case 4: {
                //autoKereses(autoszervizAdatbazis);
                break;
            }

            case 5: {
                if (!ujSzervizMuvelet(autoszervizAdatbazis)) {
                    torolKonzol();
                    std::cout << "\t=== Sikeres kilepes! (exit) ===";
                    break;
                }
                torolKonzol();
                std::cout << "\t=== Sikeres szerviz muvelet rogzitese! ===";
                break;
            }

            case 6: {
				SzervizNyilvantartoRendszer tempBeolvasottAdatbazis;
                if (!fajlNevHelyessegBiztosito(true, autoszervizAdatbazis)) {
                    torolKonzol();
                    std::cout << "\t=== Sikeres kilepes! (exit) ===";
                    break;
                }
                torolKonzol();
                std::cout << "\t=== Sikeres fajlba iras! ===";
                break;
            }

            case 7: {
                SzervizNyilvantartoRendszer tempBeolvasottAdatbazis;
                if (!fajlNevHelyessegBiztosito(false, autoszervizAdatbazis)) {
                    torolKonzol();
                    std::cout << "\t=== Sikeres kilepes! (exit) ===";
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