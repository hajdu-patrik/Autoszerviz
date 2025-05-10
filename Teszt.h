#ifndef TESZT_H
#define TESZT_H

/**
*   \file Teszt.cpp
*   Ez a fajl a program alapveto funkcioinak teszteleset vegzi.
*   A modul ellenorzi, hogy a rendszer fobb kepessegei helyesen mukodnek, es segit a hibak kiszureseben a fejlesztes soran.
*/

/// Ellenorzi, hogy a megadott fajl letezik-e.
/// @param f - A vizsg�lt f�jl neve (el�r�si �tvonal is lehet).
/// @return - true, ha a f�jl l�tezik, k�l�nben false.
bool tesztDBLetrehozas(SzervizNyilvantartoRendszer& aDB);

/// A tesztelesi funkciok futtatasara szolgalo fuggveny.
void tesztek();

#endif // !TESZT_H