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
    } catch (const std::exception& e) {
        std::cerr << "Hiba tortent a fajl beolvasasakor: " << e.what() << std::endl;
        return 1;
    }

    do {
        menuOpciok();
        std::cin >> valasztottMenu;
        torolKonzol();

        switch (valasztottMenu) {
            case 0:
                kiirASCII2();
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

            default:
                std::cout << "\t>>> Ervenytelen valasztas! Probald ujra! <<<";
                break;
        }
    } while (valasztottMenu != 0);

    return 0;
}