#ifndef UGYFEL_H
#define UGYFEL_H

/**
*   \file Ugyfel.h
*   Az Ugyfel(et) leíró osztály deklarációja és tagfüggvényeinek inline megvalósítása.
* 
*   Az osztály célja, hogy reprezentálja egy autószerviz ügyfeleit,
*   beleértve a nevüket, elérhetõségeiket.
* 
*   Az osztályban szereplõ összes std::string tipusú adattag feltételezi, hogy nem kell ékezetes betûket kezelnie.
*/

#include <string>
#include <iostream>

class Ugyfel {
    std::string nev;            ///< Az ügyfél neve
    std::string telefonszam;    ///< Az ügyfél telefonszáma
    std::string email;          ///< Az ügyfél e-mail címe
public:
    /*-------------------------------------------
            Konstruktorok és destruktor
    -------------------------------------------*/
    /// Alapértelmezett konstruktor
    Ugyfel();
    
    /// Paraméteres konstruktor.
    /// @param n - Az ügyfél neve
    /// @param t - Az ügyfél telefonszáma
    /// @param e - Az ügyfél e-mail címe
    Ugyfel(const std::string& n, const std::string& t, const std::string& e);

    /// Másoló konstruktor
    /// @param u - másolandó Karbantartas objektum
    Ugyfel(const Ugyfel& u);

    /// Destruktor
    ~Ugyfel();



    /*-------------------------------------------
                    Operátorok
    -------------------------------------------*/
    /// Értékadó operátor
    /// @param u - másolandó Vizsga objektum
	/// @return - Az aktuális objektum referenciája
    Ugyfel& operator=(const Ugyfel& u);



    /*-------------------------------------------
                     Getterek
    -------------------------------------------*/
    /// Az ügyfél nevének lekérdezése.
    /// @return - Név.
    const std::string& getNev() const;

    /// Az ügyfél telefonszámának lekérdezése.
    /// @return - Telefonszám.
    const std::string& getTelefonszam() const;

    /// Az ügyfél e-mail címének lekérdezése.
    /// @return - E-mail cím.
    const std::string& getEmail() const;



    /*-------------------------------------------
                    Setterek
    -------------------------------------------*/
    /// Az ügyfél nevének beállítása.
    /// @param n - Az új név.
    void setNev(const std::string& n);

    /// Az ügyfél telefonszámának beállítása.
    /// @param t - Az új telefonszám.
    void setTel(const std::string& t);

    /// Az ügyfél e-mail címének beállítása.
    /// @param e - Az új e-mail cím.
    void setEmail(const std::string& e);



    /*-------------------------------------------
                Fontos tagmûveletek
    -------------------------------------------*/
    /// Másoló függvény (virtuális, tisztán absztrakt)
    /// @return - új példány
    virtual Ugyfel* clone() const;

    /// Kiírja az ügyfél adatait az adott ostream-re.
    /// @param os - A kimeneti adatfolyam.
    /// @return - Az ostream referenciája (láncoláshoz).
    void kiir(std::ostream& os) const;
};
/*-------------------------------------------
            Globális operátorok
-------------------------------------------*/
/// Kimeneti operátor Datum objektumhoz
/// @param os - kimeneti stream
/// @param u - kiírandó Ugyfel objektum
/// @return - módosított kimeneti stream
std::ostream& operator<<(std::ostream& os, const Ugyfel& u);

#endif // UGYFEL_H