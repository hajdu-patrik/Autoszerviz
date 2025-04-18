#ifndef KARBANTARTAS_H
#define KARBANTARTAS_H

/**
*   \file Karbantartas.h
*   A Karbantartas(t) le�r� oszt�ly deklar�ci�ja �s tagf�ggv�nyeinek inline megval�s�t�sa.
*   Ez az oszt�ly a VegzettMuvelet oszt�lyb�l sz�rmazik, �s a karbantart�si m�veletek adatait t�rolja.
*/

#include "VegzettMuvelet.h"
#include <iostream>

class Karbantartas : public VegzettMuvelet {
public:
    /*-------------------------------------------
            Konstruktorok �s destruktor
    -------------------------------------------*/
    /// Alap�rtelmezett konstruktor
    Karbantartas() : VegzettMuvelet() {}

    /// Param�teres konstruktor
    /// @param m - m�velet megnevez�se
    /// @param d - d�tum
    /// @param a - �r
    Karbantartas(const std::string& m, const Datum& d, int a, int k) : VegzettMuvelet(m, d, a, k) {}

	/// M�sol� konstruktor
	/// @param k - m�soland� Karbantartas objektum
	Karbantartas(const Karbantartas& k) : VegzettMuvelet(k.getMuvelet(), k.getDatum(), k.getAr(), k.getAktKmOra()) {}

    /// Destruktor
    ~Karbantartas() {}



    /*-------------------------------------------
                    Oper�torok
    -------------------------------------------*/
	/// �rt�kad� oper�tor
	/// @param k - m�soland� Karbantartas objektum
	Karbantartas& operator=(const Karbantartas& k) {
		if (this != &k) {
			setMuvelet(k.getMuvelet());
			setDatum(k.getDatum());
			setAr(k.getAr());
			setAktKmOra(k.getAktKmOra());
		}
		return *this;
	}



    /*-------------------------------------------
     Tiszta absztrakt f�ggv�nyek fel�ldefini�l�sa
    -------------------------------------------*/
    /// M�sol� f�ggv�ny (virtu�lis, tiszt�n absztrakt)
    /// @return - �j p�ld�ny
    VegzettMuvelet* clone() const override {
        return new Karbantartas(*this);
    }

    /// Ki�r� f�ggv�ny fel�ldefini�l�sa
    /// @param os - kimeneti stream
    void kiir(std::ostream& os) const override {
        os << "\tKarbantartas: " << getMuvelet()
            << ", Datum: " << getDatum()
            << ", Ar: " << getAr() << " Ft"
			<< ", Akt. km: " << getAktKmOra()
            << std::endl;
    }
};

#endif // KARBANTARTAS_H