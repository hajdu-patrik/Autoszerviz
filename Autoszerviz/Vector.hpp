#ifndef VECTOR_HPP  
#define VECTOR_HPP 

/**
*	\file Vector.h
*	Dinamikus t�mb sablon oszt�ly, az std::vector alapvet� funkcionalit�s�t megval�s�tva.
*	@tparam T - A t�rolt elemek t�pusa.
*	@tparam VECTOR_MERET - Alap�rtelmezett kezd� kapacit�s (opcion�lis, alap�rtelmezett: 100).
*/

#include "Memtrace.h"
#include <stdexcept>

template<typename T, size_t VECTOR_MERET = 100>
class Vector {
	size_t kapacitas = VECTOR_MERET;	///< kapacit�s
	size_t meret;						///< aktu�lis elemek sz�ma
	T* tomb;							///< pointer az adatokra
public:
	/*-------------------------------------------
			Konstruktorok �s destruktor
	-------------------------------------------*/
	/// Alap�rtelmezett konstruktor.
	/// �res vektort hoz l�tre, el�re lefoglalt kapacit�ssal.
	Vector() : meret(0), kapacitas(VECTOR_MERET), tomb(new T[kapacitas]) {}

	/// Param�teres konstruktor
	/// @param m - Kezdeti kapacit�s
	/// @throws std::invalid_argument - Ha a kapacit�s meghaladja a VECTOR_MERET-et
	Vector(size_t m) : meret(0), kapacitas(m) {
		if (kapacitas > VECTOR_MERET) throw std::out_of_range("Kapacitas tullepes! (paramteres konstruktor)");
		tomb = new T[kapacitas];
	}

	/// M�sol� konstruktor.
	/// @param v - M�soland� vector p�ld�ny
	Vector(const Vector& v) : meret(v.meret), kapacitas(v.kapacitas), tomb(new T[kapacitas]) {
		if (meret > kapacitas) {
			throw std::out_of_range("Puffer tulcsordulasa! (masolo konstruktor)");
		}
		for (size_t i = 0; i < meret; i++) {
			tomb[i] = v.tomb[i];
		}
	}

	/// Destruktor.
	/// Felszabad�tja a dinamikusan foglalt mem�ri�t.
	~Vector() { delete[] tomb; }



	/*-------------------------------------------
				Iter�tor t�mogat�s
	-------------------------------------------*/
	/// Mutat� az els� elemre (iter�tor kezdete)
	/// @return - Pointer az els� elemre
	T* begin() { return tomb; }

	/// Konstans mutat� az els� elemre (konstans iter�tor kezdete)
	/// @return - Konstans pointer az els� elemre
	const T* begin() const { return tomb; }

	/// Mutat� az utols� elem ut�ni ter�letre (iter�tor v�ge)
	/// @return Pointer az utols� elem ut�ni ter�letre
	T* end() { return tomb + meret; }

	/// Konstans mutat� az utols� elem ut�ni ter�letre (konstans iter�tor v�ge)
	/// @return Konstans pointer az utols� elem ut�ni ter�letre
	const T* end() const { return tomb + meret; }



	/*-------------------------------------------
					Oper�torok
	-------------------------------------------*/
	/// �rt�kad� oper�tor.
	/// @param v - M�soland� vector p�ld�ny
	/// @return - Az aktu�lis objektum referenci�ja
	Vector& operator=(const Vector& v) {
		if (this != &v) {
			delete[] tomb;
			meret = v.meret;
			kapacitas = v.kapacitas;
			tomb = new T[kapacitas];
			for (size_t i = 0; i < meret; i++)
				tomb[i] = v.tomb[i];
		}
		return *this;
	}

	/// Egyenl�s�gvizsg�l� oper�tor
	/// @param v - �sszehasonl�tand� vector
	/// @return true - ha a vektorok tartalma megegyezik
	bool operator==(const Vector& v) const {
		if (meret != v.meret) return false;
		for (size_t i = 0; i < meret; i++) {
			if (tomb[i] != v.tomb[i]) return false;
		}
		return true;
	}

	/// Indexel� oper�tor
	/// @param idx - Index
	/// @return - Az adott index� elem referenci�ja
	/// @note - Nincs hat�rellen�rz�s!
	T& operator[](size_t idx) { return tomb[idx]; }

	/// Konstans indexel� oper�tor
	/// @param idx - Index
	/// @return - Az adott index� elem konstans referenci�ja
	/// @note - Nincs hat�rellen�rz�s!
	const T& operator[](size_t idx) const { return tomb[idx]; }



	/*-------------------------------------------
		Kapacit�ssal kapcsolatos m�veletek
	-------------------------------------------*/
	/// Visszaadja a vektorban t�rolt elemek sz�m�t.
	/// @return - Az aktu�lis elemsz�m (meret)
	size_t size() const { return meret; }

	/// Visszaadja a vektor kapacit�s�t.
	/// @return - A kapacit�s (kapacitas)
	size_t capacity() const { return kapacitas; }

	/// Megvizsg�lja, hogy a vektor �res-e.
	/// @return true - ha nincs benne elem, k�l�nben false
	bool empty() const { return meret == 0; }

	/// Megv�ltoztatja a vektor m�ret�t
	/// @param ns - Az �j m�ret
	/// @param v - Az �j elemek �rt�ke (opcion�lis)
	void resize(size_t ns, const T& v = T()) {
		if (ns > kapacitas) {
			reserve(ns);
		}
		if (ns > meret) {
			for (size_t i = meret; i < ns; i++) {
				tomb[i] = v;
			}
		}
		meret = ns;
	}

	/// Foglal mem�ri�t a megadott kapacit�sra
	/// @param m - �j kapacit�s
	void reserve(size_t m) {
		if (m <= kapacitas) return;

		T* new_tomb = new T[m];
		for (size_t i = 0; i < meret; i++) {
			new_tomb[i] = tomb[i];
		}
		delete[] tomb;
		tomb = new_tomb;
		kapacitas = m;
	}

	/// Cs�kkenti a kapacit�st a jelenlegi elemsz�mra.
	void shrink_to_fit() {
		if (kapacitas == meret) return;

		T* new_tomb = new T[meret];
		for (size_t i = 0; i < meret; i++) {
			new_tomb[i] = tomb[i];
		}
		delete[] tomb;
		tomb = new_tomb;
		kapacitas = meret;
	}



	/*-------------------------------------------
			Elem-hozz�f�r�si m�veletek
	-------------------------------------------*/
	/// Biztons�gos elemhozz�f�r�s
	/// @param idx - Index
	/// @return - Az adott index� elem referenci�ja
	/// @throws - std::out_of_range Ha az index �rv�nytelen
	T& at(size_t idx) {
		if (idx >= meret) throw std::out_of_range("Index tulcsordulas! (at)");
		return tomb[idx];
	}

	/// Biztons�gos konstans elemhozz�f�r�s
	/// @param idx - Index
	/// @return - Az adott index� elem konstans referenci�ja
	/// @throws - std::out_of_range Ha az index �rv�nytelen
	const T& at(size_t idx) const {
		if (idx >= meret) throw std::out_of_range("Index tulcsordulas! (const at)");
		return tomb[idx];
	}

	/// Az els� elem referenci�ja
	/// @return - Az els� elem referenci�ja
	/// @throws - std::out_of_range Ha a vektor �res
	T& front() {
		if (empty()) throw std::out_of_range("Ures vector! (front)");
		return tomb[0];
	}

	/// Az utols� elem referenci�ja
	/// @return - Az utols� elem referenci�ja
	/// @throws - std::out_of_range Ha a vektor �res
	T& back() {
		if (empty()) throw std::out_of_range("Ures vector! (back)");
		return tomb[(meret-1)];
	}

	/// Az els� elem konstans referenci�ja
	/// @return - Az els� elem konstans referenci�ja
	/// @throws - std::out_of_range Ha a vektor �res
	const T& front() const {
		if (empty()) throw std::out_of_range("Ures vector! (const front)");
		return tomb[0];
	}

	/// Az utols� elem konstans referenci�ja
	/// @return - Az utols� elem konstans referenci�ja
	/// @throws - std::out_of_range Ha a vektor �res
	const T& back() const {
		if (empty()) throw std::out_of_range("Ures vector! (const back)");
		return tomb[(meret-1)];
	}



	/*-------------------------------------------
				M�dos�t� m�veletek
	-------------------------------------------*/
	/// �j elem hozz�ad�sa a v�g�re
	/// @param v - A hozz�adand� �rt�k
	void push_back(const T& v) {
		if (meret >= kapacitas) {
			reserve(kapacitas * 2);
		}
		tomb[meret++] = v;
	}

	/// Utols� elem t�rl�se
	/// @throws - std::out_of_range Ha a vektor �res
	void pop_back() {
		if (empty()) throw std::out_of_range("Ures vector! (pop_back)");
		--meret;
	}

	/// Elem besz�r�sa a megadott poz�ci�ra
	/// @param p - Besz�r�si poz�ci� (iter�tor)
	/// @param v - A besz�rand� �rt�k
	/// @return - Iterator az �j elemre
	/// @throws - std::out_of_range Ha a poz�ci� �rv�nytelen
	T* insert(T* p, const T& v) {
		size_t idx = p - tomb;
		if (idx > meret) throw std::out_of_range("Ervenytelen pozicio! (insert)");

		if (meret >= kapacitas) {
			reserve(kapacitas == 0 ? 1 : kapacitas * 2);
			p = tomb + idx;  // Friss�tj�k a poz�ci�t, mert a tomb �jra lett foglalva
		}

		for (size_t i = meret; i > idx; --i) {
			tomb[i] = tomb[i - 1];
		}
		tomb[idx] = v;
		meret++;
		return tomb + idx;
	}

	/// Elem t�rl�se a megadott poz�ci�r�l
	/// @param p - T�rlend� elem poz�ci�ja (iter�tor)
	/// @return - Iterator a t�r�lt elem ut�ni elemre
	/// @throws - std::out_of_range Ha a poz�ci� �rv�nytelen
	T* erase(T* p) {
		size_t idx = p - tomb;
		if (idx >= meret) throw std::out_of_range("Ervenytelen pozicio! (erase)");

		for (size_t i = idx; i < (meret-1); i++) {
			tomb[i] = tomb[i + 1];
		}
		--meret;
		return tomb + idx;
	}

	/// Minden elem t�rl�se
	void clear() {
		meret = 0;
	}
};

#endif // !VECTOR_HPP