#ifndef TESZT_H
#define TESZT_H

/**
*	\file Teszt.cpp
*   Ez a f�jl a program alapvet� funkci�inak tesztel�s�t v�gzi.
*	A modul ellen�rzi, hogy a rendszer f�bb k�pess�gei helyesen m�k�dnek, �s seg�t a hib�k kisz�r�s�ben a fejleszt�s sor�n.
*/

/// Ellen�rzi, hogy a megadott f�jl l�tezik-e.
/// @param f - A vizsg�lt f�jl neve (el�r�si �tvonal is lehet).
/// @return - true, ha a f�jl l�tezik, k�l�nben false.
bool tesztDBLetrehozas(SzervizNyilvantartoRendszer& aDB);

/// A tesztel�si funkci�k futtat�s�ra szolg�l� f�ggv�ny.
void tesztek();

#endif // !TESZT_H