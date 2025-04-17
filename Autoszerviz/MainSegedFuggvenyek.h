#ifndef MAINSEGEDFUGGVENYEK_H
#define MAINSEGEDFUGGVENYEK_H

/**
*	\file MainSegedFuggvenyek.h
*   Ez a f�jl a program alapvet� funkci�inak tesztel�s�t v�gzi.
*	A modul ellen�rzi, hogy a rendszer f�bb k�pess�gei helyesen m�k�dnek, �s seg�t a hib�k kisz�r�s�ben a fejleszt�s sor�n.
*/

#include "SzervizNyilvantartoRendszer.h"
#include <string>

/*-------------------------------------------
             Men� rendszerhez
-------------------------------------------*/
/// "Autoszerviz" felirat ASCII art ki�r�sa a konzolra, tabul�torral beh�zva
void kiirASCII1();

/// "Arrivederci" felirat ASCII art ki�r�sa a konzolra, tabul�torral beh�zva
void kiirASCII2();

/// A program �ltal biztos�tott funkci�k haszn�lat�hoz sz�ks�ges men� opci�k ki�r�sa
void menuOpciok();



/*-------------------------------------------
               UI �lm�nyhez
-------------------------------------------*/
/// Megv�rja, am�g a felhaszn�l� lenyomja az Enter billenty�t.
/// �ltal�ban hiba�zenetek vagy inform�ci�k megjelen�t�se ut�n haszn�latos, 
/// hogy a felhaszn�l�nak legyen ideje elolvasni azokat.
void varakozasEnterre();

/// T�rli a konzol k�perny�t
void torolKonzol();

/// Megh�vja a torolKonzol-t majd ki�rja a "Szerviz Nyilv�ntart� Rendszer" feliratot ASCII art form�tumban
void toroloMajdCim();

/// Varakozik az Enter billenty� lenyom�s�ra, majd t�rli a konzolt
void varakozasTorol();



/*-------------------------------------------
            1. men�ponthoz
-------------------------------------------*/
/// List�zza az �gyfeleket vagy az aut�kat a megadott adatb�zisb�l.
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @return - true, ha a kiir�s sikeres volt, false, ha a felhaszn�l� kil�pett.
bool kiListazo(SzervizNyilvantartoRendszer& aDB);



/*-------------------------------------------
            2. men�ponthoz
-------------------------------------------*/
/// �j �gyf�l vagy aut� r�gz�t�se.
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
void ujUgyfelAuto(SzervizNyilvantartoRendszer& aDB);



/*-------------------------------------------
            3. men�ponthoz
-------------------------------------------*/
/// Keres egy �gyfelet a megadott n�v alapj�n.
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
void ugyfelKereses(SzervizNyilvantartoRendszer& rendszer);



/*-------------------------------------------
            4. men�ponthoz
-------------------------------------------*/
/// Keres egy aut�t a megadott rendsz�m alapj�n.
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
void autoKereses(SzervizNyilvantartoRendszer& rendszer);



/*-------------------------------------------
            5. men�ponthoz
-------------------------------------------*/
/// �j szerviz m�velet r�gz�t�se egy aut�hoz.
/// @param rendszer - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @return - true, ha a m�velet sikeresen r�gz�tve lett, false, ha a felhaszn�l� kil�pett.
bool ujSzervizMuvelet(SzervizNyilvantartoRendszer& rendszer);



/*-------------------------------------------
            6-7. men�ponthoz
-------------------------------------------*/
/// Ellen�rzi, hogy a megadott f�jl l�tezik-e.
/// @param f - A vizsg�lt f�jl neve (el�r�si �tvonal is lehet).
/// @return - true, ha a f�jl l�tezik, k�l�nben false.
bool letezikAFajl(const std::string& f);

/// F�jln�v bek�r�se, form�tum�nak �s l�tez�s�nek ellen�rz�se.
/// Elfogadja az "exit" sz�t is, ami visszal�p�st jelent a f�men�be.
/// @param mentesE - A f�ggv�ny c�lj�t jelz� kapcsol� (ment�s vagy bet�lt�s)
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @return true, ha sikeres volt a m�velet, false, ha a felhaszn�l� kil�pett.
bool fajlNevHelyessegBiztosito(bool mentesE, SzervizNyilvantartoRendszer& aDB);

#endif // !MAINSEGEDFUGGVENYEK_H