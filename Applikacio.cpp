/**
 *  \file Applikacio.cpp
 *  Ez a fájl amely bemutatja a rendszer alapvetõ mûködését és fõ funkcióit.
 */

#define MEMTRACE
#include "Memtrace.h"

#include "Gtest_lite.h"

#include <sstream>

#include "Applikacio.h"
#include "MainsegedFuggvenyek.h"
#include "SzervizNyilvantartoRendszer.h"
#include "Teszt.h"

void Applikacio::applikacio() {
    SzervizNyilvantartoRendszer autoszervizAdatbazis;

    // Fájlok betöltése, hogy teszt adatokkal induljon a program amely elõsegíti a tesztelést és a hibakeresést
    if (!tesztDBLetrehozas(autoszervizAdatbazis)) return;

    int valasztottMenu;
    std::string input;
    do {
		MainSegedFuggvenyei segedFuggvenyekEleresehez;

        segedFuggvenyekEleresehez.menuOpciok();
        std::getline(std::cin, input);

        std::stringstream ss(input);
        if (!(ss >> valasztottMenu)) {
            segedFuggvenyekEleresehez.torolKonzol();
            std::cout << "\t>>> Ervenytelen bemenet! Szamot adj meg! <<<";
            continue;
        }
        segedFuggvenyekEleresehez.torolKonzol();

        switch (valasztottMenu) {
        case 0:
            tesztek();
            break;

        case 1:
            segedFuggvenyekEleresehez.muveletFuttato(&MainSegedFuggvenyei::kiListazo, autoszervizAdatbazis, "Sikeres listazas!");
            break;

        case 2:
            segedFuggvenyekEleresehez.muveletFuttato(&MainSegedFuggvenyei::ugyfelAutoAdd, autoszervizAdatbazis, "Sikeres felvetel!");
            break;

        case 3:
            segedFuggvenyekEleresehez.muveletFuttato(&MainSegedFuggvenyei::ugyfelAutoFrissit, autoszervizAdatbazis, "Sikeres frissites!");
            break;

        case 4:
            segedFuggvenyekEleresehez.muveletFuttato(&MainSegedFuggvenyei::ugyfelAutoTorlo, autoszervizAdatbazis, "Sikeres torles!");
            break;

        case 5:
            segedFuggvenyekEleresehez.muveletFuttato(&MainSegedFuggvenyei::ugyfelKereses, autoszervizAdatbazis, "Sikeres kereses!");
            break;

        case 6:
            segedFuggvenyekEleresehez.muveletFuttato(&MainSegedFuggvenyei::autoKereses, autoszervizAdatbazis, "Sikeres kereses!");
            break;

        case 7:
            segedFuggvenyekEleresehez.muveletFuttato(&MainSegedFuggvenyei::ujSzervizMuvelet, autoszervizAdatbazis, "Sikeres szerviz muvelet rogzitese!");
            break;

        case 8:
            segedFuggvenyekEleresehez.fajlMuveletFuttato(&MainSegedFuggvenyei::fajlHelyessegBiztosito, autoszervizAdatbazis, true, "Mentes sikeres!");
            break;

        case 9:
            segedFuggvenyekEleresehez.fajlMuveletFuttato(&MainSegedFuggvenyei::fajlHelyessegBiztosito, autoszervizAdatbazis, false, "Beolvasas sikeres!");
            break;

        case 10:
            segedFuggvenyekEleresehez.kiirASCII2();
            break;

        default:
            std::cout << "\t>>> Ilyen menupont nem letezik! Adj meg egy letezot! <<<";
            break;
        }
    } while (valasztottMenu != 10);
}