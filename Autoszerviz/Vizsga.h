#ifndef VIZSGA_H
#define VIZSGA_H

/**
*   \file Vizsga.h
*   A Vizsga(t) leíró osztály deklarációja és tagfüggvényeinek inline megvalósítása.
*   Ez az osztály a VegzettMuvelet osztályból származik, és a vizsgák adatait tárolja.
* 
*   Kiegészíti az õsosztályt egy sikeres logikai értékkel, ami a vizsga sikerességét jelzi.
*/

#include "VegzettMuvelet.h"
#include <iostream>

class Vizsga : public VegzettMuvelet {
    bool sikeres; ///< A vizsga sikeressége
public:
    /*-------------------------------------------
            Konstruktorok és destruktor
    -------------------------------------------*/
    /// Alapértelmezett konstruktor
    Vizsga() : VegzettMuvelet(), sikeres(false) {}

    /// Paraméteres konstruktor
    /// @param m - mûvelet megnevezése
    /// @param d - dátum
    /// @param a - ár
    /// @param s - sikeresség
    Vizsga(const std::string& m, const Datum& d, int a, int k, bool s) : VegzettMuvelet(m, d, a, k), sikeres(s) {}

	/// Másoló konstruktor
	/// @param v - másolandó Vizsga objektum
	Vizsga(const Vizsga& v) : VegzettMuvelet(v.getMuvelet(), v.getDatum(), v.getAr(), v.getAktKmOra()), sikeres(v.sikeres) {}

    /// Destruktor
    ~Vizsga() {}



    /*-------------------------------------------
                    Operátorok
    -------------------------------------------*/
	/// Értékadó operátor
	/// @param v - másolandó Vizsga objektum
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
    /// Sikeresség lekérdezése
    /// @return - igaz, ha sikeres volt
    bool getSikeres() const { return sikeres; }



    /*-------------------------------------------
                    Setterek
    -------------------------------------------*/
    /// Sikeresség beállítása
    /// @param s - új sikerességi érték
    void setSikeres(bool s) { sikeres = s; }



    /*-------------------------------------------
     Tiszta absztrakt függvények felüldefiniálása
    -------------------------------------------*/
	/// Másoló függvény (virtuális, tisztán absztrakt)
	/// @return - új példány
    VegzettMuvelet* clone() const override {
        return new Vizsga(*this);
    }

    /// Kiíró függvény felüldefiniálása
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