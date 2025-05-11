/**
*   \file Datum.h
*   A Datum(mot) leíró osztály deklarációja és tagfüggvényeinek inline megvalósítása.
*/

#ifndef DATUM_H  
#define DATUM_H  

#include <iostream>
#include <iomanip>
#include <sstream>

class Datum {
    int ev;     ///< Év  
    int ho;     ///< Hónap  
    int nap;    ///< Nap  

public:
    /*-------------------------------------------
            Konstruktorok és destruktor
    -------------------------------------------*/
    /// Alapértelmezett konstruktor
    /// 0-ra inicializálja az évet, hónapot és napot.
    Datum();

    /// Paraméteres konstruktor
    /// @param e - év
    /// @param h - hónap
    /// @param n - nap
    Datum(int e, int h, int n);

    /// Másoló konstruktor
    /// @param d - másolandó Datum objektum
    Datum(const Datum& d);

    /// Destruktor
    ~Datum();



    /*-------------------------------------------
                    Operátorok
    -------------------------------------------*/
    /// Értékadó operátor
    /// @param d - másolandó Datum objektum
    /// @return - az aktuális objektum referenciája
    Datum& operator=(const Datum& d);

    /// Összehasonlító operátor
    /// @param d - összehasonlítandó Datum objektum
    /// @return - true, ha az objektumok megegyeznek, különben false.
    bool operator==(const Datum& d) const;



    /*-------------------------------------------
                     Getterek
    -------------------------------------------*/
    /// Év lekérdezése
    /// @return - év
    int getEv() const;

    /// Hónap lekérdezése
    /// @return - hónap
    int getHo() const;

    /// Nap lekérdezése
    /// @return - nap
    int getNap() const;

    /// Dátum eltelt napok számának lekérdezése
    /// @param d - másik Datum objektum
    int elteltNap(const Datum& d) const;



    /*-------------------------------------------
                    Setterek
    -------------------------------------------*/
    /// Dátum beállítása
    /// @param e - év
    /// @param h - hónap
    /// @param n - nap
    void setDatum(int e, int h, int n);



    /*-------------------------------------------
                   Segédfüggvények
    -------------------------------------------*/
    /// Létrehoz egy Datum objektumot egy stringbõl.
    /// A string formátuma: "ÉÉÉÉ.HH.NN".
    /// @param str - A dátumot tartalmazó string.
    /// @return - A létrehozott Datum objektum.
    static Datum parseFromString(const std::string& str);

    /// Egy Datum objektumot stringgé alakít "ÉÉÉÉ.HH.NN" formátumban.
    /// @return std::string A formázott dátum szövegként.
    const std::string toString() const;
};
/*-------------------------------------------
            Globális operátorok
-------------------------------------------*/
/// Kimeneti operátor Datum objektumhoz
/// @param os - kimeneti stream
/// @param d - kiírandó Datum objektum
/// @return - módosított kimeneti stream
std::ostream& operator<<(std::ostream& os, const Datum& d);

#endif // !DATUM_H