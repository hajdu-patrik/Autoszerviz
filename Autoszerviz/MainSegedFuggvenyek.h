#ifndef MAINSEGEDFUGGVENYEK_H
#define MAINSEGEDFUGGVENYEK_H

/**
*	\file MainSegedFuggvenyek.h
*   Ez a fájl a program alapvetõ funkcióinak tesztelését végzi.
*	A modul ellenõrzi, hogy a rendszer fõbb képességei helyesen mûködnek, és segít a hibák kiszûrésében a fejlesztés során.
*/

#include "SzervizNyilvantartoRendszer.h"
#include <string>

/// "Autoszerviz" felirat ASCII art kiírása a konzolra, tabulátorral behúzva
void kiirASCII1();

/// "Arrivederci" felirat ASCII art kiírása a konzolra, tabulátorral behúzva
void kiirASCII2();

/// A program által biztosított funkciók használatához szükséges menü opciók kiírása
void menuOpciok();

/// Megvárja, amíg a felhasználó lenyomja az Enter billentyût.
/// Általában hibaüzenetek vagy információk megjelenítése után használatos, 
/// hogy a felhasználónak legyen ideje elolvasni azokat.
void varakozasEnterre();

/// Törli a konzol képernyõt
void torolKonzol();

/// Ellenõrzi, hogy a megadott fájl létezik-e.
/// @param f - A vizsgált fájl neve (elérési útvonal is lehet).
/// @return - true, ha a fájl létezik, különben false.
bool letezikAFajl(const std::string& f);

/// Fájlnév bekérése, formátumának és létezésének ellenõrzése.
/// Elfogadja az "exit" szót is, ami visszalépést jelent a fõmenübe.
/// @param mentesE - A függvény célját jelzõ kapcsoló (mentés vagy betöltés)
/// @param aDB - A szerviz adatbázis objektum referenciája
/// @return true, ha sikeres volt a mûvelet, false ha "exit"-tel kiléptünk
bool fajlNevHelyessegBiztosito(bool mentesE, SzervizNyilvantartoRendszer& aDB);

#endif // !MAINSEGEDFUGGVENYEK_H