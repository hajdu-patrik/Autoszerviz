#ifndef MAINSEGEDFUGGVENYEK_H  
#define MAINSEGEDFUGGVENYEK_H  

/**
*	\file MainSegedFuggvenyek.h
*   Ez a fájl a program alapvetõ funkcióinak tesztelését végzi.
*	A modul ellenõrzi, hogy a rendszer fõbb képességei helyesen mûködnek, és segít a hibák kiszûrésében a fejlesztés során.
*/

#include <string>

#include "SzervizNyilvantartoRendszer.h"

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
/// Általában hibaüzenetek vagy információk megjelenítése után használatos, hogy a felhasználónak legyen ideje elolvasni azokat.
/// @param o - A kiírandó üzenet.
void varakozasEnterre(const std::string& o);

/// Törli a konzol képernyõt
void torolKonzol();

/// Meghívja a torolKonzol-t majd kiírja a "Szerviz Nyilvántartó Rendszer" feliratot ASCII art formátumban
void toroloMajdCim();

/// Varakozik az Enter billentyû lenyomására, majd törli a konzolt
void varakozasTorol();



/*-------------------------------------------
               Segéd
-------------------------------------------*/
/// Ellenõrzi, hogy a megadott rendszám formátuma helyes-e.
/// @param rendszam - A vizsgált rendszám.
/// @return - true, ha a formátum helytelen, false, ha helyes.
bool helyesRendszamFormatum(const std::string& rendszam);

/// Ellenõrzi, hogy a megadott fájl létezik-e.
/// @param f - A vizsgált fájl neve (elérési útvonal is lehet).
/// @return - true, ha a fájl létezik, különben false.
bool letezikAFajl(const std::string& f);

/// Bekéri a felhasználótól egy dátum (év, hónap, nap) értékeit.
/// Addig ismétli a bekérést, amíg helyes formátumú (érvényes tartományban lévõ) dátumot nem kap.
/// @return - A bekért dátum `Datum` típusban.
Datum bekerDatum();

/// Bekér egy sort a felhasználótól, miután kiír egy megadott üzenetet.
/// @param t - A felhasználónak megjelenítendõ üzenet.
/// @return - A felhasználó által beírt sor.
std::string sorBeker(const std::string& t);

/// A mûvelet végrehajtásának állapotát jelzõ enum.
enum class MuveletAllapot {
    Siker,
    Kilepes,
    Hiba
};

/// Lefuttat egy adott mûveletet, majd a visszatérési értéktõl függõen kiírja a megfelelõ üzenetet.
/// @param muvelet - A végrehajtandó függvény.
/// @param aDB - A szerviz nyilvántartó rendszer, amely tartalmazza az ügyfeleket és autókat.
/// @param sikerUzenet - Az üzenet, ha a mûvelet sikeres.
void muveletFuttato(MuveletAllapot(*muvelet)(SzervizNyilvantartoRendszer&), SzervizNyilvantartoRendszer& aDB, const std::string& sikerUzenet);

/// Lefuttatja a fájlkezeléshez szükséges mûveletet, majd a visszatérési értéktõl függõen kiírja a megfelelõ üzenetet.
/// @param muvelet - A végrehajtandó függvény, amely fájlmûveletet végez.
/// @param aDB - A szerviz nyilvántartó rendszer.
/// @param tipus - Igaz (true) ha mentés, hamis (false) ha beolvasás.
/// @param sikerUzenet - Az üzenet, ha a mûvelet sikeres.
void fajlMuveletFuttato(MuveletAllapot(*muvelet)(bool, SzervizNyilvantartoRendszer&), SzervizNyilvantartoRendszer& aDB, bool tipus, const std::string& sikerUzenet);



/*-------------------------------------------
           1. menüponthoz
-------------------------------------------*/
/// Listázza az ügyfeleket vagy az autókat a megadott adatbázisból.
/// @param aDB - A szerviz nyilvántartó rendszer, amely tartalmazza az ügyfeleket és autókat.
/// @return - MuveletAllapot érték a mûvelet eredménye szerint.
MuveletAllapot kiListazo(SzervizNyilvantartoRendszer& aDB);



/*-------------------------------------------
           2. menüponthoz
-------------------------------------------*/
/// Új ügyfél vagy autó rögzítése.
/// @param aDB - A szerviz nyilvántartó rendszer, amely tartalmazza az ügyfeleket és autókat.
/// @return - MuveletAllapot érték a mûvelet eredménye szerint.
MuveletAllapot ugyfelAutoAdd(SzervizNyilvantartoRendszer& aDB);



/*-------------------------------------------
           3. menüponthoz
-------------------------------------------*/
/// Meglévõ ügyfél vagy autó frissitése.
/// @param aDB - A szerviz nyilvántartó rendszer, amely tartalmazza az ügyfeleket és autókat.
/// @return - MuveletAllapot érték a mûvelet eredménye szerint.
MuveletAllapot ugyfelAutoFrissit(SzervizNyilvantartoRendszer& aDB);



/*-------------------------------------------
           4. menüponthoz
-------------------------------------------*/
/// A rendszerben lévõ ügyfél vagy autó törlésére szolgál.
/// @param aDB - A szerviz nyilvántartó rendszer, amely tartalmazza az ügyfeleket és autókat.
/// @return - MuveletAllapot érték a mûvelet eredménye szerint.
MuveletAllapot ugyfelAutoTorlo(SzervizNyilvantartoRendszer& aDB);



/*-------------------------------------------
           5. menüponthoz
-------------------------------------------*/
/// Keres egy ügyfelet a megadott név alapján.
/// @param aDB - A szerviz nyilvántartó rendszer, amely tartalmazza az ügyfeleket és autókat.
/// @return - MuveletAllapot érték a mûvelet eredménye szerint.
MuveletAllapot ugyfelKereses(SzervizNyilvantartoRendszer& aDB);



/*-------------------------------------------
           6. menüponthoz
-------------------------------------------*/
/// Keres egy autót a megadott rendszám alapján.
/// @param rendszer - A szerviz nyilvántartó rendszer, amely tartalmazza az ügyfeleket és autókat.
/// @return - MuveletAllapot érték a mûvelet eredménye szerint.
MuveletAllapot autoKereses(SzervizNyilvantartoRendszer& aDB);



/*-------------------------------------------
           7. menüponthoz
-------------------------------------------*/
/// Új szerviz mûvelet rögzítése egy autóhoz.
/// @param rendszer - A szerviz nyilvántartó rendszer, amely tartalmazza az ügyfeleket és autókat.
/// @return - MuveletAllapot érték a mûvelet eredménye szerint.
MuveletAllapot ujSzervizMuvelet(SzervizNyilvantartoRendszer& aDB);



/*-------------------------------------------
           8.-9. menüponthoz
-------------------------------------------*/
/// Fájlnév bekérése, formátumának és létezésének ellenõrzése.
/// Elfogadja az "exit" szót is, ami visszalépést jelent a fõmenübe.
/// @param mentesE - A függvény célját jelzõ kapcsoló (mentés vagy betöltés)
/// @param aDB - A szerviz adatbázis objektum referenciája
/// @return - MuveletAllapot érték a mûvelet eredménye szerint.
MuveletAllapot fajlHelyessegBiztosito(bool mentesE, SzervizNyilvantartoRendszer& aDB);

#endif // MAINSEGEDFUGGVENYEK_H