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

/// Lefuttat egy adott m�veletet, majd a visszat�r�si �rt�kt�l f�gg�en ki�rja a megfelel� �zenetet.
/// @param muvelet - A v�grehajtand� f�ggv�ny (pl. egy lambda vagy sima f�ggv�nypointer).
/// @param sikerUzenet - Az �zenet, ha a m�velet sikeres.
/// @param kilepesUzenet - Az �zenet, ha a m�velet f�lbeszakadt vagy nem t�rt�nt meg.
void muveletFuttato(bool (*muvelet)(SzervizNyilvantartoRendszer&), SzervizNyilvantartoRendszer& adatbazis, const std::string& sikerUzenet, const std::string& kilepesUzenet);



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
/// @return - true, ha a m�velet sikeresen r�gz�tve lett, false, ha a felhaszn�l� kil�pett.
bool ugyfelAutoAdd(SzervizNyilvantartoRendszer& aDB);



/*-------------------------------------------
           3. men�ponthoz
-------------------------------------------*/
/// Megl�v� �gyf�l vagy aut� frissit�se.
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @return - true, ha a m�velet sikeresen r�gz�tve lett, false, ha a felhaszn�l� kil�pett.
bool ugyfelAutoFrissit(SzervizNyilvantartoRendszer& aDB);



/*-------------------------------------------
           4. men�ponthoz
-------------------------------------------*/
/// A rendszerben l�v� �gyf�l vagy aut� t�rl�s�re szolg�l.
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @return - true, ha a m�velet sikeresen r�gz�tve lett, false, ha a felhaszn�l� kil�pett.
bool ugyfelAutoTorlo(SzervizNyilvantartoRendszer& aDB);



/*-------------------------------------------
           5. men�ponthoz
-------------------------------------------*/
/// Keres egy �gyfelet a megadott n�v alapj�n.
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @return - true, ha a m�velet sikeresen r�gz�tve lett, false, ha a felhaszn�l� kil�pett.
bool ugyfelKereses(SzervizNyilvantartoRendszer& aDB);



/*-------------------------------------------
           6. men�ponthoz
-------------------------------------------*/
/// Keres egy aut�t a megadott rendsz�m alapj�n.
/// @param rendszer - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @return - true, ha a m�velet sikeresen r�gz�tve lett, false, ha a felhaszn�l� kil�pett.
bool autoKereses(SzervizNyilvantartoRendszer& aDB);



/*-------------------------------------------
           7. men�ponthoz
-------------------------------------------*/
/// �j szerviz m�velet r�gz�t�se egy aut�hoz.
/// @param rendszer - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @return - true, ha a m�velet sikeresen r�gz�tve lett, false, ha a felhaszn�l� kil�pett.
bool ujSzervizMuvelet(SzervizNyilvantartoRendszer& aDB);



/*-------------------------------------------
           8.-9. men�ponthoz
-------------------------------------------*/
/// F�jln�v bek�r�se, form�tum�nak �s l�tez�s�nek ellen�rz�se.
/// Elfogadja az "exit" sz�t is, ami visszal�p�st jelent a f�men�be.
/// @param mentesE - A f�ggv�ny c�lj�t jelz� kapcsol� (ment�s vagy bet�lt�s)
/// @param aDB - A szerviz nyilv�ntart� rendszer, amely tartalmazza az �gyfeleket �s aut�kat.
/// @return true, ha sikeres volt a m�velet, false, ha a felhaszn�l� kil�pett.
bool fajlNevHelyessegBiztosito(bool mentesE, SzervizNyilvantartoRendszer& aDB);

#endif // MAINSEGEDFUGGVENYEK_H