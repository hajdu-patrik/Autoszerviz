/**
 *  \file Applikacio.cpp
 *  Ez a f�jl az aut�szerviz nyilv�ntart� rendszer bel�p�si pontja, amely bemutatja a rendszer alapvet� m�k�d�s�t �s f� funkci�it.
 */

#include "Teszt.h"
#include "MainSegedFuggvenyek.h"
#include "SzervizNyilvantartoRendszer.h"

#include <iostream>
#include <string>

int main() {
    SzervizNyilvantartoRendszer autoszervizAdatbazis;
    int valasztottMenu;

    
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
            //autoszervizAdatbazis.ujUgyfel();
            break;
        case 2:
            //autoszervizAdatbazis.keresAuto();
            break;
        case 3:
        case 4:  // �sszevonva, mivel mindkett� ugyanazt csin�lta
            //autoszervizAdatbazis.rogzitesVegzettMuvelet();
            break;
        case 5: {
            if (!fajlNevHelyessegBiztosito(true, autoszervizAdatbazis)) {
                // visszal�p�s (exit) t�rt�nt
                torolKonzol();
                break;
            }
            torolKonzol();
            std::cout << "\t === Sikeres fajlba iras! ===";
            break;
        }
        case 6: {
            if (!fajlNevHelyessegBiztosito(false, autoszervizAdatbazis)) {
                // visszal�p�s (exit) t�rt�nt
                torolKonzol();
                break;
            }
            torolKonzol();
            std::cout << "\t === Sikeres fajlbol olvasas! ===";
            break;
        }

        case 0:
            kiirASCII2();
            break;
        default:
            std::cout << "\t>>> Ervenytelen valasztas! Probald ujra! <<<";
        }
    } while (valasztottMenu != 0);

    return 0;
}