/**
 *  \file Applikacio.cpp
 *  Ez a fájl amely bemutatja a rendszer alapvetõ mûködését és fõ funkcióit.
 */

#define MEMTRACE
#include "Memtrace.h"

#include "Gtest_lite.h"

#include <sstream>

#include "Applikacio.h"
#include "MainSegedFuggvenyek.h"
#include "SzervizNyilvantartoRendszer.h"
#include "Teszt.h"

void Applikacio::applikacio() {
    SzervizNyilvantartoRendszer autoszervizAdatbazis;

    // Fájlok betöltése, hogy teszt adatokkal induljon a program amely elõsegíti a tesztelést és a hibakeresést
    if (!tesztDBLetrehozas(autoszervizAdatbazis)) return;

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
}