#ifndef MAINSEGEDFUGGVENYEK_H
#define MAINSEGEDFUGGVENYEK_H

/**
*	\file MainSegedFuggvenyek.h
*   Ez a fájl a program alapvetõ funkcióinak tesztelését végzi.
*	A modul ellenõrzi, hogy a rendszer fõbb képességei helyesen mûködnek, és segít a hibák kiszûrésében a fejlesztés során.
*/

#include "SzervizNyilvantartoRendszer.h"
#include <string>

/*-------------------------------------------
             Menü rendszerhez
-------------------------------------------*/
/// "Autoszerviz" felirat ASCII art kiírása a konzolra, tabulátorral behúzva
void kiirASCII1();

/// "Arrivederci" felirat ASCII art kiírása a konzolra, tabulátorral behúzva
void kiirASCII2();

/// A program által biztosított funkciók használatához szükséges menü opciók kiírása
void menuOpciok();



/*-------------------------------------------
               UI élményhez
-------------------------------------------*/
/// Megvárja, amíg a felhasználó lenyomja az Enter billentyût.
/// Általában hibaüzenetek vagy információk megjelenítése után használatos, 
/// hogy a felhasználónak legyen ideje elolvasni azokat.
void varakozasEnterre();

/// Törli a konzol képernyõt
void torolKonzol();

/// Meghívja a torolKonzol-t majd kiírja a "Szerviz Nyilvántartó Rendszer" feliratot ASCII art formátumban
void toroloMajdCim();

/// Varakozik az Enter billentyû lenyomására, majd törli a konzolt
void varakozasTorol();



/*-------------------------------------------
            1. menüponthoz
-------------------------------------------*/
/// Listázza az ügyfeleket vagy az autókat a megadott adatbázisból.
/// @param aDB - A szerviz nyilvántartó rendszer, amely tartalmazza az ügyfeleket és autókat.
/// @return - true, ha a kiirás sikeres volt, false, ha a felhasználó kilépett.
bool kiListazo(SzervizNyilvantartoRendszer& aDB);



/*-------------------------------------------
            2. menüponthoz
-------------------------------------------*/
/// Új ügyfél vagy autó rögzítése.
/// @param aDB - A szerviz nyilvántartó rendszer, amely tartalmazza az ügyfeleket és autókat.
void ujUgyfelAuto(SzervizNyilvantartoRendszer& aDB);



/*-------------------------------------------
            3. menüponthoz
-------------------------------------------*/
/// Keres egy ügyfelet a megadott név alapján.
/// @param aDB - A szerviz nyilvántartó rendszer, amely tartalmazza az ügyfeleket és autókat.
void ugyfelKereses(SzervizNyilvantartoRendszer& rendszer);



/*-------------------------------------------
            4. menüponthoz
-------------------------------------------*/
/// Keres egy autót a megadott rendszám alapján.
/// @param aDB - A szerviz nyilvántartó rendszer, amely tartalmazza az ügyfeleket és autókat.
void autoKereses(SzervizNyilvantartoRendszer& rendszer);



/*-------------------------------------------
            5. menüponthoz
-------------------------------------------*/
/// Új szerviz mûvelet rögzítése egy autóhoz.
/// @param rendszer - A szerviz nyilvántartó rendszer, amely tartalmazza az ügyfeleket és autókat.
/// @return - true, ha a mûvelet sikeresen rögzítve lett, false, ha a felhasználó kilépett.
bool ujSzervizMuvelet(SzervizNyilvantartoRendszer& rendszer);



/*-------------------------------------------
            6-7. menüponthoz
-------------------------------------------*/
/// Ellenõrzi, hogy a megadott fájl létezik-e.
/// @param f - A vizsgált fájl neve (elérési útvonal is lehet).
/// @return - true, ha a fájl létezik, különben false.
bool letezikAFajl(const std::string& f);

/// Fájlnév bekérése, formátumának és létezésének ellenõrzése.
/// Elfogadja az "exit" szót is, ami visszalépést jelent a fõmenübe.
/// @param mentesE - A függvény célját jelzõ kapcsoló (mentés vagy betöltés)
/// @param aDB - A szerviz nyilvántartó rendszer, amely tartalmazza az ügyfeleket és autókat.
/// @return true, ha sikeres volt a mûvelet, false, ha a felhasználó kilépett.
bool fajlNevHelyessegBiztosito(bool mentesE, SzervizNyilvantartoRendszer& aDB);

#endif // !MAINSEGEDFUGGVENYEK_H