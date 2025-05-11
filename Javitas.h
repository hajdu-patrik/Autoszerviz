/**
*   \file Javitas.h
*   A Javitas(t) leíró osztály deklarációja és tagfüggvényeinek inline megvalósítása.
*   Ez az osztály a VegzettMuvelet osztályból származik, és a javítási műveletek adatait tárolja.
*/

#ifndef JAVITAS_H
#define JAVITAS_H

#include <iostream>

#include "VegzettMuvelet.h"

class Javitas : public VegzettMuvelet {
public:
    /*-------------------------------------------
            Konstruktorok és destruktor
    -------------------------------------------*/
    /// Alapértelmezett konstruktor
    Javitas() : VegzettMuvelet() {}

    /// Paraméteres konstruktor
    /// @param m - művelet megnevezése
    /// @param d - dátum
    /// @param a - ár
    /// @param k - aktuális km óra állás
    Javitas(const std::string& m, const Datum& d, int a, int k) : VegzettMuvelet(m, d, a, k) {}

    /// Másoló konstruktor
    /// @param j - másolandó Javitas objektum
    Javitas(const Javitas& j) : VegzettMuvelet(j.getMuvelet(), j.getDatum(), j.getAr(), j.getAktKmOra()) {}

    /// Destruktor
    ~Javitas() {}

    /*-------------------------------------------
                    Operátorok
    -------------------------------------------*/
    /// Értékadó operátor
    /// @param j - másolandó Javitas objektum
	/// @return - Az aktuális objektum referenciája
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
    Tiszta absztrakt függvények felüldefiniálása
    -------------------------------------------*/
    /// Másoló függvény (virtuális, tisztán absztrakt)
    /// @return - új példány
    VegzettMuvelet* clone() const override {
        return new Javitas(*this);
    }

    /// Kiíró függvény felüldefiniálása
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