#ifndef TESZT_H
#define TESZT_H

/**
*	\file Teszt.cpp
*   Ez a fájl a program alapvetõ funkcióinak tesztelését végzi.
*	A modul ellenõrzi, hogy a rendszer fõbb képességei helyesen mûködnek, és segít a hibák kiszûrésében a fejlesztés során.
*/

/// Ellenõrzi, hogy a megadott fájl létezik-e.
/// @param f - A vizsgált fájl neve (elérési útvonal is lehet).
/// @return - true, ha a fájl létezik, különben false.
bool tesztDBLetrehozas(SzervizNyilvantartoRendszer& aDB);

/// A tesztelési funkciók futtatására szolgáló függvény.
void tesztek();

#endif // !TESZT_H