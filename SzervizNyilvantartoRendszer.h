#ifndef SZERVIZNYILVANTARTORENDSZER_H
#define SZERVIZNYILVANTARTORENDSZER_H

/**
*   \file SzervizNyilvantartoRendszer.h
*   A SzervizNyilvantartoRendszer adatait leíró osztály.
*
*   Az osztály az autókhoz kapcsolódó szervizmûveletek nyilvántartására szolgál.
*   Felelõs az autók adatainak kezeléséért, új szervizmûveletek rögzítéséért,
*   meglévõ adatok lekérdezéséért és módosításáért.
*/

#include <string>

#include "Vector.hpp"
#include "Auto.h"
#include "Ugyfel.h"

class SzervizNyilvantartoRendszer {
	Vector<Auto> autok;			///< Az autók listája
	Vector<Ugyfel> ugyfelek;	///< Az ügyfelek listája
public:
	/*-------------------------------------------
			Konstruktorok és destruktor
	-------------------------------------------*/
	/// Alapértelmezett konstruktor.
	/// Üres vektort hoz létre, elõre lefoglalt kapacitással.
	SzervizNyilvantartoRendszer();

	/// Paraméteres konstruktor
	/// @param a - Az autó példány
	/// @param u - Az ügyfél példány
	SzervizNyilvantartoRendszer(const Auto& a, const Ugyfel& u);

	/// Másoló konstruktor.
	/// @param v - Másolandó SzervizNyilvantartoRendszer példány
	SzervizNyilvantartoRendszer(const SzervizNyilvantartoRendszer& v);

	/// Destruktor.
	/// Ez jelzi, hogy nem kell semmi egyedi a destruktorba, mert a tagok destruktora magától elintézi.
	~SzervizNyilvantartoRendszer();



	/*-------------------------------------------
					Getter
	-------------------------------------------*/
	/// Visszaadja az összes autó objektumot.
	/// @return - Egy Vector<Auto> példány, amely az összes jelenleg nyilvántartott autót tartalmazza.
	Vector<Auto>& getAutok();

	/// Visszaadja az összes auto objektumot (const változat).
	/// @return - Egy const Vector<Auto> példány, amely az összes jelenleg nyilvántartott autott tartalmazza.
	const Vector<Auto>& getAutok() const;

	/// Visszaadja az összes ügyfél objektumot.
	/// @return - Egy Vector<Ugyfel> példány, amely az összes jelenleg nyilvántartott ügyfelet tartalmazza.
	Vector<Ugyfel>& getUgyfelek();

	/// Visszaadja az összes ügyfél objektumot (const változat).
	/// @return - Egy const Vector<Ugyfel> példány, amely az összes jelenleg nyilvántartott ügyfelet tartalmazza.
	const Vector<Ugyfel>& getUgyfelek() const;



	/*-------------------------------------------
				Bõvítõ tagfüggvények
	-------------------------------------------*/
	/// Új autó hozzáadása az adatbázishoz.
	/// @param a - Az új autó példány.
	/// @return - True, ha az autó sikeresen hozzáadva, false, ha már létezik.
	bool ujAuto(const Auto& a);

	/// Új ügyfél hozzáadása az adatbázishoz.
	/// @param u - Az új ügyfél példány.
	/// @return - True, ha az ügyfél sikeresen hozzáadva, false, ha már létezik.
	bool ujUgyfel(const Ugyfel& u);



	/*-------------------------------------------
				Frissítõ tagfüggvények
	-------------------------------------------*/
	/// Egy autó adatainak frissítése a rendszeren belül.
	/// Ha a rendszeren belül már létezik az autó (rendszám alapján), akkor az adatai frissülnek.
	/// @param a - Az autó új adatai.
	/// @return - True, ha az autó sikeresen frissítve lett, false, ha nem található.
	bool frissitAuto(const Auto& a);

	/// Egy ügyfél adatainak frissítése a rendszeren belül.
	/// Ha a rendszeren belül már létezik az ügyfél (név alapján), akkor az adatai frissülnek.
	/// @param u - Az ügyfél új adatai.
	/// @return - True, ha az ügyfél sikeresen frissítve lett, false, ha nem található.
	bool frissitUgyfel(const Ugyfel& u);



	/*-------------------------------------------
				Törlõ tagfüggvények
	-------------------------------------------*/
	/// Egy autó törlése rendszám alapján.
	/// @param r - A törlendõ autó rendszáma.
	/// @return - True, ha az autó törölve lett, false, ha nem található.
	bool torolAuto(const std::string& r);

	/// Egy ügyfél törlése név alapján.
	/// @param n - A törlendõ ügyfél neve.
	/// @return - True, ha az ügyfél törölve lett, false, ha nem található.
	bool torolUgyfel(const std::string& n);

	/// Egy adott rendszámú autóhoz tartozó szervizmûvelet törlése a megadott dátum alapján.
	/// @param r - Az autó rendszáma.
	/// @param d - A törlendõ mûvelet dátuma.
	/// @return - True, ha a mûvelet sikeresen törölve lett, false, ha az autó vagy a megadott dátumú mûvelet nem található.
	bool torolMuvelet(const std::string& r, const Datum& d);



	/*-------------------------------------------
			  Keresõ tagfüggvények
	-------------------------------------------*/
	// Autó keresése rendszám alapján.
	/// @param r - A keresett autó rendszáma (teljes egyezés).
	/// @return - Az autó referenciája, ha megtalálta.
	/// @throw - Hibát dob ha nem talált meg a kerest rendszámu autot
	Auto& keresAuto(const std::string& r);

	/// Ügyfél keresése név alapján.
	/// @param n - A keresett ügyfél neve (teljes egyezés).
	/// @return - Az ügyfél referenciája, ha megtalálta.
	/// @throw - Hibát dob ha nem talált meg a kerest nevû embert
	Ugyfel& keresUgyfel(const std::string& n);

	/// Auto létezésének ellenõrzése név alapján.
	/// @param r - A keresett autó rendszáma (teljes egyezés).
	/// @return - True, ha az auto megtalálható a rendszerben, false egyébként.
	bool vanAuto(const std::string& r) const;

	/// Ügyfél létezésének ellenõrzése név alapján.
	/// @param n - A keresett ügyfél neve (teljes egyezés).
	/// @return - True, ha az ügyfél megtalálható a rendszerben, false egyébként.
	bool vanUgyfel(const std::string& n) const;



	/*-------------------------------------------
				Fontos tagmûveletek
	-------------------------------------------*/
	/// Egy végzett szervizmûvelet rögzítése adott autóhoz.
	/// @param r - Az autó rendszáma.
	/// @param m - A végzett szervizmûvelet.
	/// @return - True, ha a mûvelet sikeresen rögzítve lett, false, ha az autó nem található.
	bool rogzitesVegzettMuvelet(const std::string& r, const VegzettMuvelet& m);

	/// Lekérdezi az adott autóhoz tartozó szervizmûveleteket.û
	/// @param os - A kimeneti adatfolyam.
	/// @param r - Az autó rendszáma.
	void lekeroVegzettMuvelet(std::ostream& os, const std::string& r) const;

	/// Figyelmeztetéseket generál az autó állapota alapján.
	/// @param os - A kimeneti adatfolyam.
	/// @param a - Az autó példány.
	void figyelmeztetesek(std::ostream& os, const Auto& a) const;



	/*-------------------------------------------
			 Fájlkezelõ tagfüggvények
	-------------------------------------------*/
	/// Az aktuális rendszeradatok mentése fájlba.
	/// @param f - A célfájl neve.
	void mentesFajlba(const std::string& f) const;

	/// Rendszeradatok betöltése fájlból.
	/// @param f - A forrásfájl neve.
	void betoltesFajlbol(const std::string& f);

	/**
	 * Fontos tudnivalók a fájlkezelõ függvények mûködésérõl:
	 *
	 * A fájlokban tárolt adatoknak pontosan meg kell felelniük az elõre definiált szabályoknak, melyek a következõk:
	 *
	 * Fájlnevek:
	 *   - Ügyfél típusú fájl esetén a fájlnévnek tartalmaznia kell az "_ufl.txt" végzõdést.
	 *   - Autó típusú fájl esetén a fájlnévnek "_auo.txt" végzõdést kell tartalmaznia.
	 *
	 * Fájlstruktúra:
	 *   - Ügyfelek esetén a sorok formátuma: "ugyfel_neve-telefonszam-email"
	 *   - Autók esetén a formátum: "rendszam-marka-tipus-kmora-uzembe_helyezes_datuma-szervizmuveletek-tulajdonos_neve"
	 *
	 * Megjegyzések az autós adatokhoz:
	 *   - A "szervizmuveletek" mezõben szerepelhet:
	 *     - a "nincs" szó, ha nem történt szervizelés,
	 *     - vagy egy felsorolás az elvégzett mûveletekrõl, az alábbi formátumban:
	 *       "tipus,leiras,datum,ar,kmora,extra;"
	 *       ahol:
	 *         - tipus: 'J' (javítás), 'K' (karbantartás), vagy 'V' (vizsga),
	 *         - az "extra" mezõ kizárólag vizsga esetén tartalmazza a „sikeres” vagy „sikertelen” értéket.
	 *		   - a mezõk közötti elválasztó karakter a vesszõ (,) és a végén pontosvesszõ (;) ha van további szervizmuvelet.
	 *		   - azt is elvárjuk, hogy a kmora értékek mindig pozitív egész számok legyenek amik minden esettben <= mint az azt megelõzõ "szervizmuvelet kmora" értéke
	 *
	 * További szabály:
	 *   - Amennyiben az autóhoz tartozó tulajdonos még nem szerepel a rendszerben, az új ügyfelet automatikusan felvesszük, viszont a telefonszám és e-mail mezõi üresen maradnak.
	 */
};

#endif // SZERVIZNYILVANTARTORENDSZER_H