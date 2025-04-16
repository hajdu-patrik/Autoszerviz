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
                // Az ugyfel/auto tarolok listazasa
                for (size_t i = 0; i < autoszervizAdatbazis.getAutok().size(); i++) {
                    std::cout << autoszervizAdatbazis.getAutok().at(i);
                }

                for (size_t i = 0; i < autoszervizAdatbazis.getUgyfelek().size(); i++) {
                    std::cout << autoszervizAdatbazis.getUgyfelek().at(i);
                }
                break;

            case 2: {
                // Uj ugyfel/auto felvetele
                break;
            }

		    case 3: {
			    // Ugyfel keresese nev alapjan
			    break;
            }

            case 4: {
                // Auto keresese rendszam alapjan
                break;
            }

            case 5: {
                // Uj szerviz muvelet rogzitese
                break;
            }

            case 6: {
                if (!fajlNevHelyessegBiztosito(true, autoszervizAdatbazis)) {
                    // visszalépés (exit) történt
                    torolKonzol();
                    break;
                }
                torolKonzol();
                std::cout << "\t === Sikeres fajlba iras! ===";
                break;
            }

            case 7: {
                if (!fajlNevHelyessegBiztosito(false, autoszervizAdatbazis)) {
                    // visszalépés (exit) történt
                    torolKonzol();
                    break;
                }
                torolKonzol();
                std::cout << "\t === Sikeres fajlbol olvasas! ===";
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