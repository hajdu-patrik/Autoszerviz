#ifndef MAINSEGEDFUGGVENYEK_H  
#define MAINSEGEDFUGGVENYEK_H  

/**
*	\file MainSegedFuggvenyek.h
*   Ez a f�jl a program alapvet� funkci�inak tesztel�s�t v�gzi.
*	A modul ellen�rzi, hogy a rendszer f�bb k�pess�gei helyesen m�k�dnek, �s seg�t a hib�k kisz�r�s�ben a fejleszt�s sor�n.
*/

#include <string>

#include "SzervizNyilvantartoRendszer.h"

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
/// �ltal�ban hiba�zenetek vagy inform�ci�k megjelen�t�se ut�n haszn�latos, hogy a felhaszn�l�nak legyen ideje elolvasni azokat.
/// @param o - A ki�rand� �zenet.
void varakozasEnterre(const std::string& o);

/// T�rli a konzol k�perny�t
void torolKonzol();

/// Megh�vja a torolKonzol-t majd ki�rja a "Szerviz Nyilv�ntart� Rendszer" feliratot ASCII art form�tumban
void toroloMajdCim();

/// Varakozik az Enter billenty� lenyom�s�ra, majd t�rli a konzolt
void varakozasTorol();



/*-------------------------------------------
               Seg�d
-------------------------------------------*/
/// Ellen�rzi, hogy a megadott rendsz�m form�tuma helyes-e.
/// @param rendszam - A vizsg�lt rendsz�m.
/// @return - true, ha a form�tum helytelen, false, ha helyes.
bool helyesRendszamFormatum(const std::string& rendszam);

/// Ellen�rzi, hogy a megadott f�jl l�tezik-e.
/// @param f - A vizsg�lt f�jl neve (el�r�si �tvonal is lehet).
/// @return - true, ha a f�jl l�tezik, k�l�nben false.
bool letezikAFajl(const std::string& f);

/// Bek�ri a felhaszn�l�t�l egy d�tum (�v, h�nap, nap) �rt�keit.
/// Addig ism�tli a bek�r�st, am�g helyes form�tum� (�rv�nyes tartom�nyban l�v�) d�tumot nem kap.
/// @return - A bek�rt d�tum `Datum` t�pusban.
Datum bekerDatum();

/// Bek�r egy sort a felhaszn�l�t�l, miut�n ki�r egy megadott �zenetet.
/// @param t - A felhaszn�l�nak megjelen�tend� �zenet.
/// @return - A felhaszn�l� �ltal be�rt sor.
std::string sorBeker(const std::string& t);

/// A m�velet v�grehajt�s�nak �llapot�t jelz� enum.
enum class MuveletAllapot {
    Siker,
    Kilepes,
    Hiba
};

/// Lefuttat egy adott m�veletet, majd a visszat�r�si �rt�kt�l f�gg�en ki�rja a megfelel� �zenetet.
/// @param muvelet - A v�grehajtand� f�ggv�ny.
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @param sikerUzenet - Az �zenet, ha a m�velet sikeres.
void muveletFuttato(MuveletAllapot(*muvelet)(SzervizNyilvantartoRendszer&), SzervizNyilvantartoRendszer& aDB, const std::string& sikerUzenet);

/// Lefuttatja a f�jlkezel�shez sz�ks�ges m�veletet, majd a visszat�r�si �rt�kt�l f�gg�en ki�rja a megfelel� �zenetet.
/// @param muvelet - A v�grehajtand� f�ggv�ny, amely f�jlm�veletet v�gez.
/// @param aDB - A szerviz nyilv�ntart� rendszer.
/// @param tipus - Igaz (true) ha ment�s, hamis (false) ha beolvas�s.
/// @param sikerUzenet - Az �zenet, ha a m�velet sikeres.
void fajlMuveletFuttato(MuveletAllapot(*muvelet)(bool, SzervizNyilvantartoRendszer&), SzervizNyilvantartoRendszer& aDB, bool tipus, const std::string& sikerUzenet);



/*-------------------------------------------
           1. men�ponthoz
-------------------------------------------*/
/// List�zza az �gyfeleket vagy az aut�kat a megadott adatb�zisb�l.
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @return - MuveletAllapot �rt�k a m�velet eredm�nye szerint.
MuveletAllapot kiListazo(SzervizNyilvantartoRendszer& aDB);



/*-------------------------------------------
           2. men�ponthoz
-------------------------------------------*/
/// �j �gyf�l vagy aut� r�gz�t�se.
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @return - MuveletAllapot �rt�k a m�velet eredm�nye szerint.
MuveletAllapot ugyfelAutoAdd(SzervizNyilvantartoRendszer& aDB);



/*-------------------------------------------
           3. men�ponthoz
-------------------------------------------*/
/// Megl�v� �gyf�l vagy aut� frissit�se.
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @return - MuveletAllapot �rt�k a m�velet eredm�nye szerint.
MuveletAllapot ugyfelAutoFrissit(SzervizNyilvantartoRendszer& aDB);



/*-------------------------------------------
           4. men�ponthoz
-------------------------------------------*/
/// A rendszerben l�v� �gyf�l vagy aut� t�rl�s�re szolg�l.
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @return - MuveletAllapot �rt�k a m�velet eredm�nye szerint.
MuveletAllapot ugyfelAutoTorlo(SzervizNyilvantartoRendszer& aDB);



/*-------------------------------------------
           5. men�ponthoz
-------------------------------------------*/
/// Keres egy �gyfelet a megadott n�v alapj�n.
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @return - MuveletAllapot �rt�k a m�velet eredm�nye szerint.
MuveletAllapot ugyfelKereses(SzervizNyilvantartoRendszer& aDB);



/*-------------------------------------------
           6. men�ponthoz
-------------------------------------------*/
/// Keres egy aut�t a megadott rendsz�m alapj�n.
/// @param rendszer - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @return - MuveletAllapot �rt�k a m�velet eredm�nye szerint.
MuveletAllapot autoKereses(SzervizNyilvantartoRendszer& aDB);



/*-------------------------------------------
           7. men�ponthoz
-------------------------------------------*/
/// �j szerviz m�velet r�gz�t�se egy aut�hoz.
/// @param rendszer - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @return - MuveletAllapot �rt�k a m�velet eredm�nye szerint.
MuveletAllapot ujSzervizMuvelet(SzervizNyilvantartoRendszer& aDB);



/*-------------------------------------------
           8.-9. men�ponthoz
-------------------------------------------*/
/// F�jln�v bek�r�se, form�tum�nak �s l�tez�s�nek ellen�rz�se.
/// Elfogadja az "exit" sz�t is, ami visszal�p�st jelent a f�men�be.
/// @param mentesE - A f�ggv�ny c�lj�t jelz� kapcsol� (ment�s vagy bet�lt�s)
/// @param aDB - A szerviz adatb�zis objektum referenci�ja
/// @return - MuveletAllapot �rt�k a m�velet eredm�nye szerint.
MuveletAllapot fajlHelyessegBiztosito(bool mentesE, SzervizNyilvantartoRendszer& aDB);

#endif // MAINSEGEDFUGGVENYEK_H