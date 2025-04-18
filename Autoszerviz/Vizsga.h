#ifndef VIZSGA_H
#define VIZSGA_H

/**
*   \file Vizsga.h
*   A Vizsga(t) le�r� oszt�ly deklar�ci�ja �s tagf�ggv�nyeinek inline megval�s�t�sa.
*   Ez az oszt�ly a VegzettMuvelet oszt�lyb�l sz�rmazik, �s a vizsg�k adatait t�rolja.
* 
*   Kieg�sz�ti az �soszt�lyt egy sikeres logikai �rt�kkel, ami a vizsga sikeress�g�t jelzi.
*/

#include "VegzettMuvelet.h"
#include <iostream>

class Vizsga : public VegzettMuvelet {
    bool sikeres; ///< A vizsga sikeress�ge
public:
    /*-------------------------------------------
            Konstruktorok �s destruktor
    -------------------------------------------*/
    /// Alap�rtelmezett konstruktor
    Vizsga() : VegzettMuvelet(), sikeres(false) {}

    /// Param�teres konstruktor
    /// @param m - m�velet megnevez�se
    /// @param d - d�tum
    /// @param a - �r
    /// @param s - sikeress�g
    Vizsga(const std::string& m, const Datum& d, int a, int k, bool s) : VegzettMuvelet(m, d, a, k), sikeres(s) {}

	/// M�sol� konstruktor
	/// @param v - m�soland� Vizsga objektum
	Vizsga(const Vizsga& v) : VegzettMuvelet(v.getMuvelet(), v.getDatum(), v.getAr(), v.getAktKmOra()), sikeres(v.sikeres) {}

    /// Destruktor
    ~Vizsga() {}



    /*-------------------------------------------
                    Oper�torok
    -------------------------------------------*/
	/// �rt�kad� oper�tor
	/// @param v - m�soland� Vizsga objektum
	Vizsga& operator=(const Vizsga& v) {
		if (this != &v) {
			setMuvelet(v.getMuvelet());
			setDatum(v.getDatum());
			setAr(v.getAr());
			setAktKmOra(v.getAktKmOra());
			sikeres = v.sikeres;
		}
		return *this;
	}



    /*-------------------------------------------
                     Getterek
    -------------------------------------------*/
    /// Sikeress�g lek�rdez�se
    /// @return - igaz, ha sikeres volt
    bool getSikeres() const { return sikeres; }



    /*-------------------------------------------
                    Setterek
    -------------------------------------------*/
    /// Sikeress�g be�ll�t�sa
    /// @param s - �j sikeress�gi �rt�k
    void setSikeres(bool s) { sikeres = s; }



    /*-------------------------------------------
     Tiszta absztrakt f�ggv�nyek fel�ldefini�l�sa
    -------------------------------------------*/
	/// M�sol� f�ggv�ny (virtu�lis, tiszt�n absztrakt)
	/// @return - �j p�ld�ny
    VegzettMuvelet* clone() const override {
        return new Vizsga(*this);
    }

    /// Ki�r� f�ggv�ny fel�ldefini�l�sa
    /// @param os - kimeneti stream
    void kiir(std::ostream& os) const override {
        os << "\tVizsga: " << getMuvelet()
            << ", Datum: " << getDatum()
            << ", Ar: " << getAr()
            << " Ft, Sikeres: " << (sikeres ? "igen" : "nem")
			<< ", Akt. km: " << getAktKmOra()
            << std::endl;
    }
};

#endif // VIZSGA_H