/**
 *  \file Applikacio.cpp
 *  Ez a fájl az autószerviz nyilvántartó rendszer belépési pontja, amely bemutatja a rendszer alapvetõ mûködését és fõ funkcióit.
 */


#include "Memtrace.h"
#include "Gtest_lite.h"

#include "MainSegedFuggvenyek.h"
#include "SzervizNyilvantartoRendszer.h"
#include "Teszt.h"

int main() {
    SzervizNyilvantartoRendszer autoszervizAdatbazis;
    
	// Fájlok betöltése, hogy teszt adatokkal induljon a program amely elõsegíti a tesztelést és a hibakeresést
    if (!tesztDBLetrehozas(autoszervizAdatbazis)) return 1;

    int valasztottMenu;
    do {
        menuOpciok();
        std::cin >> valasztottMenu;
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
                std::cout << "\t>>> Ervenytelen valasztas! Probald ujra! <<<";
                break;
        }
    } while (valasztottMenu != 10);

    return 0;
}