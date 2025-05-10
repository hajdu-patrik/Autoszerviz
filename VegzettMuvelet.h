#ifndef VEGZETTMUVELET_H  
#define VEGZETTMUVELET_H  

/**
*   \file VegzettMuvelet.h
*   Az VegzettMuvelet(et) leíró absztrakt osztály deklarációja és tagfüggvényeinek inline megvalósítása.
*
*   Az osztályban szereplõ összes std::string tipusú adattag feltételezi, hogy nem kell ékezetes betûket kezelnie.
*/

#include <string>

#include "Datum.h"

class VegzettMuvelet {
    std::string muvelet;    ///< A mûvelet megnevezése  
    Datum idopont;          ///< A mûvelet idõpontja  
    int ar;                 ///< A mûvelet ára  
    int akt_kmOra;          ///< Az aktuális kilométeróra állás
public:
    /*-------------------------------------------
                  Konstruktorok
    -------------------------------------------*/
    /// Alapértelmezett konstruktor
    /// Létrehoz egy üres mûveletet nullákkal inicializált dátummal és 0 árral.
    VegzettMuvelet() : muvelet(""), idopont(), ar(0), akt_kmOra(0) {}

    /// Paraméteres konstruktor
    /// @param m - Mûvelet neve
    /// @param d - Mûvelet idõpontja
    /// @param a - Mûvelet ára
    VegzettMuvelet(const std::string& m, const Datum& d, int a, int k) : muvelet(m), idopont(d), ar(a), akt_kmOra(k) {}

    /// Másoló konstruktor
    /// @param vm - Másolandó VegzettMuvelet objektum
    VegzettMuvelet(const VegzettMuvelet& vm) : muvelet(vm.muvelet), idopont(vm.idopont), ar(vm.ar), akt_kmOra(vm.akt_kmOra) {}



    /*-------------------------------------------
                    Operátorok
    -------------------------------------------*/
    /// Értékadó operátor
    /// @param vm - Másolandó VegzettMuvelet objektum
    /// @return - Az aktuális objektum referencia
    VegzettMuvelet& operator=(const VegzettMuvelet& vm) {
        if (this != &vm) {
            muvelet = vm.muvelet;
            idopont = vm.idopont;
            ar = vm.ar;
            akt_kmOra = vm.akt_kmOra;
        }
        return *this;
    }



    /*-------------------------------------------
                     Getterek
    -------------------------------------------*/
    /// Getter a mûvelet nevéhez
    /// @return - A mûvelet neve (const referencia)
    const std::string& getMuvelet() const { return muvelet; }

    /// Getter az idõponthoz
    /// @return - A mûvelet dátuma (const referencia)
    const Datum& getDatum() const { return idopont; }

    /// Getter az árhoz
    /// @return - A mûvelet ára
    int getAr() const { return ar; }

    /// Getter az aktuális kilométeróra állásához
    /// @return - Az aktuális kilométeróra állás
    int getAktKmOra() const { return akt_kmOra; }



    /*-------------------------------------------
                    Setterek
    -------------------------------------------*/
    /// Setter az idõponthoz
    /// @param d - Új dátum
    void setDatum(const Datum& d) { idopont = d; }

    /// Setter az árhoz
    /// @param a - Új ár
    void setAr(int a) { ar = a; }

    /// Setter a mûvelet nevéhez
    /// @param m - Új mûvelet név
    void setMuvelet(const std::string& m) { muvelet = m; }

    /// Setter az aktuális kilométeróra állásához
    /// @param k - Új kilométeróra állás
    void setAktKmOra(int k) { akt_kmOra = k; }



    /*-------------------------------------------
                Virtuális függvények
    -------------------------------------------*/
    /// Kiíró függvény (virtuális, tisztán absztrakt)
    /// @param os - A kimeneti stream, ahova a mûvelet kiírásra kerül
    virtual void kiir(std::ostream& os) const = 0;

    /// Másoló függvény (virtuális, tisztán absztrakt)
    /// @return - Egy új VegzettMuvelet pointer, amely a másolt objektumot reprezentálja
    virtual VegzettMuvelet* clone() const = 0;

    /// Virtuális destruktor
    virtual ~VegzettMuvelet() = default;
};

#endif // VEGZETTMUVELET_H