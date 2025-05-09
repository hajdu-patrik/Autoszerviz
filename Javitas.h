#ifndef JAVITAS_H
#define JAVITAS_H

/**
*   \file Javitas.h
*   A Javitas(t) le�r� oszt�ly deklar�ci�ja �s tagf�ggv�nyeinek inline megval�s�t�sa.
*   Ez az oszt�ly a VegzettMuvelet oszt�lyb�l sz�rmazik, �s a jav�t�si m�veletek adatait t�rolja.
*/

#include <iostream>

#include "VegzettMuvelet.h"

class Javitas : public VegzettMuvelet {
public:
    /*-------------------------------------------
            Konstruktorok �s destruktor
    -------------------------------------------*/
    /// Alap�rtelmezett konstruktor
    Javitas() : VegzettMuvelet() {}

    /// Param�teres konstruktor
    /// @param m - m�velet megnevez�se
    /// @param d - d�tum
    /// @param a - �r
    Javitas(const std::string& m, const Datum& d, int a, int k) : VegzettMuvelet(m, d, a, k) {}

	/// M�sol� konstruktor
	/// @param j - m�soland� Javitas objektum
    Javitas(const Javitas& j) : VegzettMuvelet(j.getMuvelet(), j.getDatum(), j.getAr(), j.getAktKmOra()) {}

    /// Destruktor
    ~Javitas() {}



    /*-------------------------------------------
                    Oper�torok
    -------------------------------------------*/
	/// �rt�kad� oper�tor
	/// @param j - m�soland� Javitas objektum
    Javitas& operator=(const Javitas& j) {
        if (this != &j) {
			setMuvelet(j.getMuvelet());
			setDatum(j.getDatum());
			setAr(j.getAr());
			setAktKmOra(j.getAktKmOra());
        }
		return *this;
    }



    /*-------------------------------------------
     Tiszta absztrakt f�ggv�nyek fel�ldefini�l�sa
    -------------------------------------------*/
    /// M�sol� f�ggv�ny (virtu�lis, tiszt�n absztrakt)
    /// @return - �j p�ld�ny
    VegzettMuvelet* clone() const override {
        return new Javitas(*this);
    }

    /// Ki�r� f�ggv�ny fel�ldefini�l�sa
    /// @param os - kimeneti stream
    void kiir(std::ostream& os) const override {
        os << "\tJavitas: " << getMuvelet()
            << ", Datum: " << getDatum()
            << ", Ar: " << getAr() << " Ft"
			<< ", Akt. km: " << getAktKmOra()
            << std::endl;
    }
};

#endif // JAVITAS_H