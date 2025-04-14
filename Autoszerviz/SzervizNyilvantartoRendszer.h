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
				B�v�t� tagf�ggv�nyek
	-------------------------------------------*/
	/// �j aut� hozz�ad�sa az adatb�zishoz.
	/// @param a - Az �j aut� p�ld�ny.
	void ujAuto(const Auto& a);

	/// �j �gyf�l hozz�ad�sa az adatb�zishoz.
	/// @param u - Az �j �gyf�l p�ld�ny.
	void ujUgyfel(const Ugyfel& u);



	/*-------------------------------------------
				Friss�t� tagf�ggv�nyek
	-------------------------------------------*/
	/// Egy aut� adatainak friss�t�se a rendszeren bel�l.
	/// Ha a rendszeren bel�l m�r l�tezik az aut� (rendsz�m alapj�n), akkor az adatai friss�lnek.
	/// @param a - Az aut� �j adatai.
	/// @throws std::out_of_range - Ha az aut� nem tal�lhat�.
	void frissitAuto(const Auto& a);

	/// Egy �gyf�l adatainak friss�t�se a rendszeren bel�l.
	/// Ha a rendszeren bel�l m�r l�tezik az �gyf�l (n�v alapj�n), akkor az adatai friss�lnek.
	/// @param u - Az �gyf�l �j adatai.
	/// @throws std::out_of_range - Ha az �gyf�l nem tal�lhat�.
	void frissitUgyfel(const Ugyfel& u);



	/*-------------------------------------------
				T�rl� tagf�ggv�nyek
	-------------------------------------------*/
	/// Egy aut� t�rl�se rendsz�m alapj�n.
	/// @param r - A t�rlend� aut� rendsz�ma.
	/// @throws std::out_of_range - Ha az aut� nem tal�lhat�.
	void torolAuto(const std::string& r);

	/// Egy �gyf�l t�rl�se n�v alapj�n.
	/// @param n - A t�rlend� �gyf�l neve.
	/// @throws std::out_of_range - Ha az �gyf�l nem tal�lhat�.
	void torolUgyfel(const std::string& n);



	/*-------------------------------------------
			  Keres� tagf�ggv�nyek
	-------------------------------------------*/
	// Aut� keres�se rendsz�m alapj�n.
	/// @param r - A keresett aut� rendsz�ma (teljes egyez�s).
	/// @return - Az aut� referenci�ja, ha megtal�lta.
	/// @throws std::out_of_range - Ha az aut� nem tal�lhat�.
	Auto& keresAuto(const std::string& r);

	/// �gyf�l keres�se n�v alapj�n.
	/// @param n - A keresett �gyf�l neve (teljes egyez�s).
	/// @return - Az �gyf�l referenci�ja, ha megtal�lta.
	/// @throws std::out_of_range - Ha a keresett �gyf�l nem tal�lhat�.
	Ugyfel& keresUgyfel(const std::string& n);



	/*-------------------------------------------
				Fontos tagm�veletek
	-------------------------------------------*/
	/// Egy v�gzett szervizm�velet r�gz�t�se adott aut�hoz.
	/// @param r - Az aut� rendsz�ma.
	/// @param m - A v�gzett szervizm�velet.
	void rogzitesVegzettMuvelet(const std::string& r, const VegzettMuvelet& m);

	/// Lek�rdezi az adott aut�hoz tartoz� szervizm�veleteket.
	/// @param r - Az aut� rendsz�ma.
	void lekeroVegzettMuvelet(std::ostream& os, const std::string& r) const;

	/// Figyelmeztet�seket gener�l az aut� �llapota alapj�n.
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
};

#endif // SZERVIZNYILVANTARTORENDSZER_H