/**
*   \file Karbantartas.h
*   A Karbantartas(t) leíró osztály deklarációja és tagfüggvényeinek inline megvalósítása.
*   Ez az osztály a VegzettMuvelet osztályból származik, és a karbantartási mûveletek adatait tárolja.
*/

#ifndef KARBANTARTAS_H
#define KARBANTARTAS_H

#include <iostream>

#include "VegzettMuvelet.h"

class Karbantartas : public VegzettMuvelet {
public:
    /*-------------------------------------------
            Konstruktorok és destruktor
    -------------------------------------------*/
    /// Alapértelmezett konstruktor
    Karbantartas() : VegzettMuvelet() {}

    /// Paraméteres konstruktor
    /// @param m - mûvelet megnevezése
    /// @param d - dátum
    /// @param a - ár
    /// @param k - aktuális km óra állás
    Karbantartas(const std::string& m, const Datum& d, int a, int k) : VegzettMuvelet(m, d, a, k) {}

    /// Másoló konstruktor
    /// @param k - másolandó Karbantartas objektum
    Karbantartas(const Karbantartas& k) : VegzettMuvelet(k.getMuvelet(), k.getDatum(), k.getAr(), k.getAktKmOra()) {}

    /// Destruktor
    ~Karbantartas() {}

    /*-------------------------------------------
                    Operátorok
    -------------------------------------------*/
    /// Értékadó operátor
    /// @param k - másolandó Karbantartas objektum
	/// @return - Az aktuális objektum referenciája
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
     Tiszta absztrakt függvények felüldefiniálása
    -------------------------------------------*/
    /// Másoló függvény (virtuális, tisztán absztrakt)
    /// @return - új példány
    VegzettMuvelet* clone() const override {
        return new Karbantartas(*this);
    }

    /// Kiíró függvény felüldefiniálása
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