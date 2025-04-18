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
                    std::cout << "\t=== Sikeres kilepes! ===";
                    break;
                }
                torolKonzol();
                std::cout << "\t=== Sikeres listazas! ===";
                break;
            }

            case 2: {
                if (!ugyfelAutoAdd(autoszervizAdatbazis)) {
                    torolKonzol();
                    std::cout << "\t=== Sikeres kilepes! ===";
                    break;
                }
                torolKonzol();
                std::cout << "\t=== Sikeres felvetel! ===";
                break;
            }

            case 3: {
                if (!ugyfelAutoFrissit(autoszervizAdatbazis)) {
                    torolKonzol();
                    std::cout << "\t=== Sikeres kilepes! ===";
                    break;
                }
                torolKonzol();
                std::cout << "\t=== Sikeres frissites! ===";
                break;
            }
            
            case 4: {
                if (!ugyfelAutoTorlo(autoszervizAdatbazis)) {
                    torolKonzol();
                    std::cout << "\t=== Sikeres kilepes! ===";
                    break;
                }
                torolKonzol();
                std::cout << "\t=== Sikeres torles! ===";
                break;
            }

            case 5: {
                if (!ugyfelKereses(autoszervizAdatbazis)) {
                    torolKonzol();
                    std::cout << "\t=== Sikeres kilepes! ===";
                    break;
                }
                torolKonzol();
                std::cout << "\t=== Sikeres kereses! ===";
                break;
            }

            case 6: {
                if (!autoKereses(autoszervizAdatbazis)) {
                    torolKonzol();
                    std::cout << "\t=== Sikeres kilepes! ===";
                    break;
                }
                torolKonzol();
                std::cout << "\t=== Sikeres kereses! ===";
                break;
            }

            case 7: {
                if (!ujSzervizMuvelet(autoszervizAdatbazis)) {
                    torolKonzol();
                    std::cout << "\t=== Sikeres kilepes! ===";
                    break;
                }
                torolKonzol();
                std::cout << "\t=== Sikeres szerviz muvelet rogzitese! ===";
                break;
            }

            case 8: {
				SzervizNyilvantartoRendszer tempBeolvasottAdatbazis;
                // Kell egy merge fuggveny es jo lesz!
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
                SzervizNyilvantartoRendszer tempBeolvasottAdatbazis;
                // Kell egy merge fuggveny es jo lesz!
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