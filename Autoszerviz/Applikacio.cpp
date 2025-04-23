/**
 *  \file Applikacio.cpp
 *  Ez a f�jl az aut�szerviz nyilv�ntart� rendszer bel�p�si pontja, amely bemutatja a rendszer alapvet� m�k�d�s�t �s f� funkci�it.
 */


#include "Memtrace.h"
#include "Gtest_lite.h"

#include <sstream>

#include "MainSegedFuggvenyek.h"
#include "SzervizNyilvantartoRendszer.h"
#include "Teszt.h"

int main() {
    SzervizNyilvantartoRendszer autoszervizAdatbazis;
    
	// F�jlok bet�lt�se, hogy teszt adatokkal induljon a program amely el�seg�ti a tesztel�st �s a hibakeres�st
    if (!tesztDBLetrehozas(autoszervizAdatbazis)) return 1;

    int valasztottMenu;
    std::string input;
    do {
        menuOpciok();
        std::getline(std::cin, input);

        std::stringstream ss(input);
        if (!(ss >> valasztottMenu)) {
            torolKonzol();
            std::cout << "\t>>> Ervenytelen bemenet! Szamot adj meg! <<<";
            continue;
        }
        torolKonzol();

        switch (valasztottMenu) {
            case 0:
                tesztek();
                break;

            case 1:
                muveletFuttato(kiListazo, autoszervizAdatbazis, "Sikeres listazas!");
                break;

            case 2:
                muveletFuttato(ugyfelAutoAdd, autoszervizAdatbazis, "Sikeres felvetel!");
                break;

            case 3:
                muveletFuttato(ugyfelAutoFrissit, autoszervizAdatbazis, "Sikeres frissites!");
                break;

            case 4:
                muveletFuttato(ugyfelAutoTorlo, autoszervizAdatbazis, "Sikeres torles!");
                break;

            case 5:
                muveletFuttato(ugyfelKereses, autoszervizAdatbazis, "Sikeres kereses!");
                break;

            case 6:
                muveletFuttato(autoKereses, autoszervizAdatbazis, "Sikeres kereses!");
                break;

            case 7:
                muveletFuttato(ujSzervizMuvelet, autoszervizAdatbazis, "Sikeres szerviz muvelet rogzitese!");
                break;

            case 8:
                fajlMuveletFuttato(fajlHelyessegBiztosito, autoszervizAdatbazis, true, "Mentes sikeres!");
                break;

            case 9:
                fajlMuveletFuttato(fajlHelyessegBiztosito, autoszervizAdatbazis, false, "Beolvasas sikeres!");
                break;

            case 10:
                kiirASCII2();
                break;

            default:
                std::cout << "\t>>> Ilyen menupont nem letezik! Adj meg egy letezot! <<<";
                break;
        }
    } while (valasztottMenu != 10);

    return 0;
}