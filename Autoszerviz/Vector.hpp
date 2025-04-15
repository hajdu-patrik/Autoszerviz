#ifndef VECTOR_HPP  
#define VECTOR_HPP 

/**
*	\file Vector.h
*	Dinamikus tömb sablon osztály, az std::vector alapvetõ funkcionalitását megvalósítva.
*	@tparam T - A tárolt elemek típusa.
*	@tparam VECTOR_MERET - Alapértelmezett kezdõ kapacitás (opcionális, alapértelmezett: 100).
*/

#include "Memtrace.h"
#include <stdexcept>

template<typename T, size_t VECTOR_MERET = 100>
class Vector {
	size_t kapacitas = VECTOR_MERET;	///< kapacitás
	size_t meret;						///< aktuális elemek száma
	T* tomb;							///< pointer az adatokra
public:
	/*-------------------------------------------
			Konstruktorok és destruktor
	-------------------------------------------*/
	/// Alapértelmezett konstruktor.
	/// Üres vektort hoz létre, elõre lefoglalt kapacitással.
	Vector() : meret(0), kapacitas(VECTOR_MERET), tomb(new T[kapacitas]) {}

	/// Paraméteres konstruktor
	/// @param m - Kezdeti kapacitás
	/// @throws std::invalid_argument - Ha a kapacitás meghaladja a VECTOR_MERET-et
	Vector(size_t m) : meret(0), kapacitas(m) {
		if (kapacitas > VECTOR_MERET) throw std::out_of_range("Kapacitas tullepes! (paramteres konstruktor)");
		tomb = new T[kapacitas];
	}

	/// Másoló konstruktor.
	/// @param v - Másolandó vector példány
	Vector(const Vector& v) : meret(v.meret), kapacitas(v.kapacitas), tomb(new T[kapacitas]) {
		if (meret > kapacitas) {
			throw std::out_of_range("Puffer tulcsordulasa! (masolo konstruktor)");
		}
		for (size_t i = 0; i < meret; i++) {
			tomb[i] = v.tomb[i];
		}
	}

	/// Destruktor.
	/// Felszabadítja a dinamikusan foglalt memóriát.
	~Vector() { delete[] tomb; }



	/*-------------------------------------------
				Iterátor támogatás
	-------------------------------------------*/
	/// Mutató az elsõ elemre (iterátor kezdete)
	/// @return - Pointer az elsõ elemre
	T* begin() { return tomb; }

	/// Konstans mutató az elsõ elemre (konstans iterátor kezdete)
	/// @return - Konstans pointer az elsõ elemre
	const T* begin() const { return tomb; }

	/// Mutató az utolsó elem utáni területre (iterátor vége)
	/// @return Pointer az utolsó elem utáni területre
	T* end() { return tomb + meret; }

	/// Konstans mutató az utolsó elem utáni területre (konstans iterátor vége)
	/// @return Konstans pointer az utolsó elem utáni területre
	const T* end() const { return tomb + meret; }



	/*-------------------------------------------
					Operátorok
	-------------------------------------------*/
	/// Értékadó operátor.
	/// @param v - Másolandó vector példány
	/// @return - Az aktuális objektum referenciája
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

	/// Egyenlõségvizsgáló operátor
	/// @param v - Összehasonlítandó vector
	/// @return true - ha a vektorok tartalma megegyezik
	bool operator==(const Vector& v) const {
		if (meret != v.meret) return false;
		for (size_t i = 0; i < meret; i++) {
			if (tomb[i] != v.tomb[i]) return false;
		}
		return true;
	}

	/// Indexelõ operátor
	/// @param idx - Index
	/// @return - Az adott indexû elem referenciája
	/// @note - Nincs határellenõrzés!
	T& operator[](size_t idx) { return tomb[idx]; }

	/// Konstans indexelõ operátor
	/// @param idx - Index
	/// @return - Az adott indexû elem konstans referenciája
	/// @note - Nincs határellenõrzés!
	const T& operator[](size_t idx) const { return tomb[idx]; }



	/*-------------------------------------------
		Kapacitással kapcsolatos mûveletek
	-------------------------------------------*/
	/// Visszaadja a vektorban tárolt elemek számát.
	/// @return - Az aktuális elemszám (meret)
	size_t size() const { return meret; }

	/// Visszaadja a vektor kapacitását.
	/// @return - A kapacitás (kapacitas)
	size_t capacity() const { return kapacitas; }

	/// Megvizsgálja, hogy a vektor üres-e.
	/// @return true - ha nincs benne elem, különben false
	bool empty() const { return meret == 0; }

	/// Megváltoztatja a vektor méretét
	/// @param ns - Az új méret
	/// @param v - Az új elemek értéke (opcionális)
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

	/// Foglal memóriát a megadott kapacitásra
	/// @param m - új kapacitás
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

	/// Csökkenti a kapacitást a jelenlegi elemszámra.
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
			Elem-hozzáférési mûveletek
	-------------------------------------------*/
	/// Biztonságos elemhozzáférés
	/// @param idx - Index
	/// @return - Az adott indexû elem referenciája
	/// @throws - std::out_of_range Ha az index érvénytelen
	T& at(size_t idx) {
		if (idx >= meret) throw std::out_of_range("Index tulcsordulas! (at)");
		return tomb[idx];
	}

	/// Biztonságos konstans elemhozzáférés
	/// @param idx - Index
	/// @return - Az adott indexû elem konstans referenciája
	/// @throws - std::out_of_range Ha az index érvénytelen
	const T& at(size_t idx) const {
		if (idx >= meret) throw std::out_of_range("Index tulcsordulas! (const at)");
		return tomb[idx];
	}

	/// Az elsõ elem referenciája
	/// @return - Az elsõ elem referenciája
	/// @throws - std::out_of_range Ha a vektor üres
	T& front() {
		if (empty()) throw std::out_of_range("Ures vector! (front)");
		return tomb[0];
	}

	/// Az utolsó elem referenciája
	/// @return - Az utolsó elem referenciája
	/// @throws - std::out_of_range Ha a vektor üres
	T& back() {
		if (empty()) throw std::out_of_range("Ures vector! (back)");
		return tomb[(meret-1)];
	}

	/// Az elsõ elem konstans referenciája
	/// @return - Az elsõ elem konstans referenciája
	/// @throws - std::out_of_range Ha a vektor üres
	const T& front() const {
		if (empty()) throw std::out_of_range("Ures vector! (const front)");
		return tomb[0];
	}

	/// Az utolsó elem konstans referenciája
	/// @return - Az utolsó elem konstans referenciája
	/// @throws - std::out_of_range Ha a vektor üres
	const T& back() const {
		if (empty()) throw std::out_of_range("Ures vector! (const back)");
		return tomb[(meret-1)];
	}



	/*-------------------------------------------
				Módosító mûveletek
	-------------------------------------------*/
	/// Új elem hozzáadása a végére
	/// @param v - A hozzáadandó érték
	void push_back(const T& v) {
		if (meret >= kapacitas) {
			reserve(kapacitas * 2);
		}
		tomb[meret++] = v;
	}

	/// Utolsó elem törlése
	/// @throws - std::out_of_range Ha a vektor üres
	void pop_back() {
		if (empty()) throw std::out_of_range("Ures vector! (pop_back)");
		--meret;
	}

	/// Elem beszúrása a megadott pozícióra
	/// @param p - Beszúrási pozíció (iterátor)
	/// @param v - A beszúrandó érték
	/// @return - Iterator az új elemre
	/// @throws - std::out_of_range Ha a pozíció érvénytelen
	T* insert(T* p, const T& v) {
		size_t idx = p - tomb;
		if (idx > meret) throw std::out_of_range("Ervenytelen pozicio! (insert)");

		if (meret >= kapacitas) {
			reserve(kapacitas == 0 ? 1 : kapacitas * 2);
			p = tomb + idx;  // Frissítjük a pozíciót, mert a tomb újra lett foglalva
		}

		for (size_t i = meret; i > idx; --i) {
			tomb[i] = tomb[i - 1];
		}
		tomb[idx] = v;
		meret++;
		return tomb + idx;
	}

	/// Elem törlése a megadott pozícióról
	/// @param p - Törlendõ elem pozíciója (iterátor)
	/// @return - Iterator a törölt elem utáni elemre
	/// @throws - std::out_of_range Ha a pozíció érvénytelen
	T* erase(T* p) {
		size_t idx = p - tomb;
		if (idx >= meret) throw std::out_of_range("Ervenytelen pozicio! (erase)");

		for (size_t i = idx; i < (meret-1); i++) {
			tomb[i] = tomb[i + 1];
		}
		--meret;
		return tomb + idx;
	}

	/// Minden elem törlése
	void clear() {
		meret = 0;
	}
};

#endif // !VECTOR_HPP