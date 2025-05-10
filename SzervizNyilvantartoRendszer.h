#ifndef SZERVIZNYILVANTARTORENDSZER_H
#define SZERVIZNYILVANTARTORENDSZER_H

/**
*   \file SzervizNyilvantartoRendszer.h
*   A SzervizNyilvantartoRendszer adatait le�r� oszt�ly.
*
*   Az oszt�ly az aut�khoz kapcsol�d� szervizm�veletek nyilv�ntart�s�ra szolg�l.
*   Felel�s az aut�k adatainak kezel�s��rt, �j szervizm�veletek r�gz�t�s��rt,
*   megl�v� adatok lek�rdez�s��rt �s m�dos�t�s��rt.
*/

#include <string>

#include "Vector.hpp"
#include "Auto.h"
#include "Ugyfel.h"

class SzervizNyilvantartoRendszer {
	Vector<Auto> autok;			///< Az aut�k list�ja
	Vector<Ugyfel> ugyfelek;	///< Az �gyfelek list�ja
public:
	/*-------------------------------------------
			Konstruktorok �s destruktor
	-------------------------------------------*/
	/// Alap�rtelmezett konstruktor.
	/// �res vektort hoz l�tre, el�re lefoglalt kapacit�ssal.
	SzervizNyilvantartoRendszer();

	/// Param�teres konstruktor
	/// @param a - Az aut� p�ld�ny
	/// @param u - Az �gyf�l p�ld�ny
	SzervizNyilvantartoRendszer(const Auto& a, const Ugyfel& u);

	/// M�sol� konstruktor.
	/// @param v - M�soland� SzervizNyilvantartoRendszer p�ld�ny
	SzervizNyilvantartoRendszer(const SzervizNyilvantartoRendszer& v);

	/// Destruktor.
	/// Ez jelzi, hogy nem kell semmi egyedi a destruktorba, mert a tagok destruktora mag�t�l elint�zi.
	~SzervizNyilvantartoRendszer();



	/*-------------------------------------------
					Getter
	-------------------------------------------*/
	/// Visszaadja az �sszes aut� objektumot.
	/// @return - Egy Vector<Auto> p�ld�ny, amely az �sszes jelenleg nyilv�ntartott aut�t tartalmazza.
	Vector<Auto>& getAutok();

	/// Visszaadja az �sszes auto objektumot (const v�ltozat).
	/// @return - Egy const Vector<Auto> p�ld�ny, amely az �sszes jelenleg nyilv�ntartott autott tartalmazza.
	const Vector<Auto>& getAutok() const;

	/// Visszaadja az �sszes �gyf�l objektumot.
	/// @return - Egy Vector<Ugyfel> p�ld�ny, amely az �sszes jelenleg nyilv�ntartott �gyfelet tartalmazza.
	Vector<Ugyfel>& getUgyfelek();

	/// Visszaadja az �sszes �gyf�l objektumot (const v�ltozat).
	/// @return - Egy const Vector<Ugyfel> p�ld�ny, amely az �sszes jelenleg nyilv�ntartott �gyfelet tartalmazza.
	const Vector<Ugyfel>& getUgyfelek() const;



	/*-------------------------------------------
				B�v�t� tagf�ggv�nyek
	-------------------------------------------*/
	/// �j aut� hozz�ad�sa az adatb�zishoz.
	/// @param a - Az �j aut� p�ld�ny.
	/// @return - True, ha az aut� sikeresen hozz�adva, false, ha m�r l�tezik.
	bool ujAuto(const Auto& a);

	/// �j �gyf�l hozz�ad�sa az adatb�zishoz.
	/// @param u - Az �j �gyf�l p�ld�ny.
	/// @return - True, ha az �gyf�l sikeresen hozz�adva, false, ha m�r l�tezik.
	bool ujUgyfel(const Ugyfel& u);



	/*-------------------------------------------
				Friss�t� tagf�ggv�nyek
	-------------------------------------------*/
	/// Egy aut� adatainak friss�t�se a rendszeren bel�l.
	/// Ha a rendszeren bel�l m�r l�tezik az aut� (rendsz�m alapj�n), akkor az adatai friss�lnek.
	/// @param a - Az aut� �j adatai.
	/// @return - True, ha az aut� sikeresen friss�tve lett, false, ha nem tal�lhat�.
	bool frissitAuto(const Auto& a);

	/// Egy �gyf�l adatainak friss�t�se a rendszeren bel�l.
	/// Ha a rendszeren bel�l m�r l�tezik az �gyf�l (n�v alapj�n), akkor az adatai friss�lnek.
	/// @param u - Az �gyf�l �j adatai.
	/// @return - True, ha az �gyf�l sikeresen friss�tve lett, false, ha nem tal�lhat�.
	bool frissitUgyfel(const Ugyfel& u);



	/*-------------------------------------------
				T�rl� tagf�ggv�nyek
	-------------------------------------------*/
	/// Egy aut� t�rl�se rendsz�m alapj�n.
	/// @param r - A t�rlend� aut� rendsz�ma.
	/// @return - True, ha az aut� t�r�lve lett, false, ha nem tal�lhat�.
	bool torolAuto(const std::string& r);

	/// Egy �gyf�l t�rl�se n�v alapj�n.
	/// @param n - A t�rlend� �gyf�l neve.
	/// @return - True, ha az �gyf�l t�r�lve lett, false, ha nem tal�lhat�.
	bool torolUgyfel(const std::string& n);

	/// Egy adott rendsz�m� aut�hoz tartoz� szervizm�velet t�rl�se a megadott d�tum alapj�n.
	/// @param r - Az aut� rendsz�ma.
	/// @param d - A t�rlend� m�velet d�tuma.
	/// @return - True, ha a m�velet sikeresen t�r�lve lett, false, ha az aut� vagy a megadott d�tum� m�velet nem tal�lhat�.
	bool torolMuvelet(const std::string& r, const Datum& d);



	/*-------------------------------------------
			  Keres� tagf�ggv�nyek
	-------------------------------------------*/
	// Aut� keres�se rendsz�m alapj�n.
	/// @param r - A keresett aut� rendsz�ma (teljes egyez�s).
	/// @return - Az aut� referenci�ja, ha megtal�lta.
	/// @throw - Hib�t dob ha nem tal�lt meg a kerest rendsz�mu autot
	Auto& keresAuto(const std::string& r);

	/// �gyf�l keres�se n�v alapj�n.
	/// @param n - A keresett �gyf�l neve (teljes egyez�s).
	/// @return - Az �gyf�l referenci�ja, ha megtal�lta.
	/// @throw - Hib�t dob ha nem tal�lt meg a kerest nev� embert
	Ugyfel& keresUgyfel(const std::string& n);

	/// Auto l�tez�s�nek ellen�rz�se n�v alapj�n.
	/// @param r - A keresett aut� rendsz�ma (teljes egyez�s).
	/// @return - True, ha az auto megtal�lhat� a rendszerben, false egy�bk�nt.
	bool vanAuto(const std::string& r) const;

	/// �gyf�l l�tez�s�nek ellen�rz�se n�v alapj�n.
	/// @param n - A keresett �gyf�l neve (teljes egyez�s).
	/// @return - True, ha az �gyf�l megtal�lhat� a rendszerben, false egy�bk�nt.
	bool vanUgyfel(const std::string& n) const;



	/*-------------------------------------------
				Fontos tagm�veletek
	-------------------------------------------*/
	/// Egy v�gzett szervizm�velet r�gz�t�se adott aut�hoz.
	/// @param r - Az aut� rendsz�ma.
	/// @param m - A v�gzett szervizm�velet.
	/// @return - True, ha a m�velet sikeresen r�gz�tve lett, false, ha az aut� nem tal�lhat�.
	bool rogzitesVegzettMuvelet(const std::string& r, const VegzettMuvelet& m);

	/// Lek�rdezi az adott aut�hoz tartoz� szervizm�veleteket.�
	/// @param os - A kimeneti adatfolyam.
	/// @param r - Az aut� rendsz�ma.
	void lekeroVegzettMuvelet(std::ostream& os, const std::string& r) const;

	/// Figyelmeztet�seket gener�l az aut� �llapota alapj�n.
	/// @param os - A kimeneti adatfolyam.
	/// @param a - Az aut� p�ld�ny.
	void figyelmeztetesek(std::ostream& os, const Auto& a) const;



	/*-------------------------------------------
			 F�jlkezel� tagf�ggv�nyek
	-------------------------------------------*/
	/// Az aktu�lis rendszeradatok ment�se f�jlba.
	/// @param f - A c�lf�jl neve.
	void mentesFajlba(const std::string& f) const;

	/// Rendszeradatok bet�lt�se f�jlb�l.
	/// @param f - A forr�sf�jl neve.
	void betoltesFajlbol(const std::string& f);

	/**
	 * Fontos tudnival�k a f�jlkezel� f�ggv�nyek m�k�d�s�r�l:
	 *
	 * A f�jlokban t�rolt adatoknak pontosan meg kell felelni�k az el�re defini�lt szab�lyoknak, melyek a k�vetkez�k:
	 *
	 * F�jlnevek:
	 *   - �gyf�l t�pus� f�jl eset�n a f�jln�vnek tartalmaznia kell az "_ufl.txt" v�gz�d�st.
	 *   - Aut� t�pus� f�jl eset�n a f�jln�vnek "_auo.txt" v�gz�d�st kell tartalmaznia.
	 *
	 * F�jlstrukt�ra:
	 *   - �gyfelek eset�n a sorok form�tuma: "ugyfel_neve-telefonszam-email"
	 *   - Aut�k eset�n a form�tum: "rendszam-marka-tipus-kmora-uzembe_helyezes_datuma-szervizmuveletek-tulajdonos_neve"
	 *
	 * Megjegyz�sek az aut�s adatokhoz:
	 *   - A "szervizmuveletek" mez�ben szerepelhet:
	 *     - a "nincs" sz�, ha nem t�rt�nt szervizel�s,
	 *     - vagy egy felsorol�s az elv�gzett m�veletekr�l, az al�bbi form�tumban:
	 *       "tipus,leiras,datum,ar,kmora,extra;"
	 *       ahol:
	 *         - tipus: 'J' (jav�t�s), 'K' (karbantart�s), vagy 'V' (vizsga),
	 *         - az "extra" mez� kiz�r�lag vizsga eset�n tartalmazza a �sikeres� vagy �sikertelen� �rt�ket.
	 *		   - a mez�k k�z�tti elv�laszt� karakter a vessz� (,) �s a v�g�n pontosvessz� (;) ha van tov�bbi szervizmuvelet.
	 *		   - azt is elv�rjuk, hogy a kmora �rt�kek mindig pozit�v eg�sz sz�mok legyenek amik minden esettben <= mint az azt megel�z� "szervizmuvelet kmora" �rt�ke
	 *
	 * Tov�bbi szab�ly:
	 *   - Amennyiben az aut�hoz tartoz� tulajdonos m�g nem szerepel a rendszerben, az �j �gyfelet automatikusan felvessz�k, viszont a telefonsz�m �s e-mail mez�i �resen maradnak.
	 */
};

#endif // SZERVIZNYILVANTARTORENDSZER_H