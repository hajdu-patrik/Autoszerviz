#ifndef MAINSEGEDFUGGVENYEK_H
#define MAINSEGEDFUGGVENYEK_H

/**
*	\file MainSegedFuggvenyek.h
*   Ez a f�jl a program alapvet� funkci�inak tesztel�s�t v�gzi.
*	A modul ellen�rzi, hogy a rendszer f�bb k�pess�gei helyesen m�k�dnek, �s seg�t a hib�k kisz�r�s�ben a fejleszt�s sor�n.
*/

#include "SzervizNyilvantartoRendszer.h"
#include <string>

/// "Autoszerviz" felirat ASCII art ki�r�sa a konzolra, tabul�torral beh�zva
void kiirASCII1();

/// "Arrivederci" felirat ASCII art ki�r�sa a konzolra, tabul�torral beh�zva
void kiirASCII2();

/// A program �ltal biztos�tott funkci�k haszn�lat�hoz sz�ks�ges men� opci�k ki�r�sa
void menuOpciok();

/// Megv�rja, am�g a felhaszn�l� lenyomja az Enter billenty�t.
/// �ltal�ban hiba�zenetek vagy inform�ci�k megjelen�t�se ut�n haszn�latos, 
/// hogy a felhaszn�l�nak legyen ideje elolvasni azokat.
void varakozasEnterre();

/// T�rli a konzol k�perny�t
void torolKonzol();

/// Ellen�rzi, hogy a megadott f�jl l�tezik-e.
/// @param f - A vizsg�lt f�jl neve (el�r�si �tvonal is lehet).
/// @return - true, ha a f�jl l�tezik, k�l�nben false.
bool letezikAFajl(const std::string& f);

/// F�jln�v bek�r�se, form�tum�nak �s l�tez�s�nek ellen�rz�se.
/// Elfogadja az "exit" sz�t is, ami visszal�p�st jelent a f�men�be.
/// @param mentesE - A f�ggv�ny c�lj�t jelz� kapcsol� (ment�s vagy bet�lt�s)
/// @param aDB - A szerviz adatb�zis objektum referenci�ja
/// @return true, ha sikeres volt a m�velet, false ha "exit"-tel kil�pt�nk
bool fajlNevHelyessegBiztosito(bool mentesE, SzervizNyilvantartoRendszer& aDB);

#endif // !MAINSEGEDFUGGVENYEK_H