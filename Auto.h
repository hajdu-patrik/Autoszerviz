#ifndef AUTO_H
#define AUTO_H

/**
*   \file Auto.h
*   Az autó adatait leíró osztály.
*
*   Az osztály célja, hogy reprezentálja egy autó adatait, beleértve a
*   rendszám, márka, típus, kilométeróra állása, üzembe helyezés dátuma,
*   valamint a hozzá tartozó szervizmûveletek listáját.
*   Az osztály lehetõséget biztosít az adatok kezelésére, módosítására,
*   valamint a szerviztörténet nyilvántartására.
*
*   Az osztályban szereplõ összes std::string tipusú adattag feltételezi, hogy nem kell ékezetes betûket kezelnie.
*/

#include <string>

#include "Datum.h"
#include "Ugyfel.h"
#include "Vector.hpp"
#include "VegzettMuvelet.h"

class Auto {
    std::string rendszam;                               ///< Az autó rendszáma  
    std::string marka;                                  ///< Az autó márkája  
    std::string tipus;                                  ///< Az autó típusa  
    int kmOra;                                          ///< Kilométeróra állása  
    Datum uzembeHelyezes;                               ///< Üzembe helyezés dátuma  
    Vector<VegzettMuvelet*> vegzettSzervizMuveletek;    ///< Elvégzett szervizmûveletek  
    Ugyfel* tulajdonos;                                 ///< Az autó tulajdonosa  
public:
    /*-------------------------------------------
            Konstruktorok és destruktor
    -------------------------------------------*/
    /// Alapértelmezett konstruktor.  
    Auto();

    /// Paraméteres konstruktor.  
    /// @param r - Az autó rendszáma  
    /// @param m - Az autó márkája  
    /// @param t - Az autó típusa  
    /// @param k - A kilométeróra állása  
    Auto(const std::string& r, const std::string& m, const std::string& t, int k);

    /// Paraméteres konstruktor.  
    /// @param r - Az autó rendszáma  
    /// @param m - Az autó márkája  
    /// @param t - Az autó típusa  
    /// @param k - A kilométeróra állása  
    /// @param d - Az üzembe helyezés dátuma  
    /// @param v - Az autóhoz tartozó szervizmûveletek listája  
    /// @param u - Az autó tulajdonosa  
    Auto(const std::string& r, const std::string& m, const std::string& t, int k, const Datum& d, const Vector<VegzettMuvelet*>& v, Ugyfel* u);

    /// Másoló konstruktor.  
    /// @param a - Másolandó Auto objektum  
    Auto(const Auto& a);

    /// Destruktor  
    virtual ~Auto();



    /*-------------------------------------------
                    Operátorok
    -------------------------------------------*/
    /// Értékadó operátor.
    /// @param a - másolandó Auto objektum
    /// @return - Az aktuális objektum referenciája
    Auto& operator=(const Auto& a);

    /// Egyenlõség operátor túlterhelése az Auto osztályhoz.
    /// @param a - Az összehasonlítandó Auto objektum.
    /// @return - true, ha az objektumok megegyeznek, különben false.
    bool operator==(const Auto& a) const;



    /*-------------------------------------------
                     Getterek
    -------------------------------------------*/
    /// Visszaadja az autó rendszámát.
    /// @return - Rendszám.
    const std::string& getRendszam() const;

    /// Visszaadja az autó márkáját.
    /// @return - Márka.
    const std::string& getMarka() const;

    /// Visszaadja az autó típusát.
    /// @return - Típus.
    const std::string& getTipus() const;

    /// Visszaadja a kilométeróra aktuális értékét.
    /// @return - Km óra értéke.
    const int getKmOra() const;

    /// Visszaadja az üzembe helyezés dátumát.
    /// @return - Dátum .
    const Datum& getUzembeHelyezes() const;

    /// Visszaadja az autóhoz tartozó szervizmûveletek listáját.
    /// @return - Szervizmûveletek vektora.
    Vector<VegzettMuvelet*>& getSzervizMuveletek();

    /// Visszaadja az autóhoz tartozó szervizmûveletek listáját (const változat).
    /// @return - Szervizmûveletek vektora.
    const Vector<VegzettMuvelet*>& getSzervizMuveletek() const;

    // Visszaadja az autó tulajdonosát.
    /// @return - Az autó tulajdonosa.
    Ugyfel* getTulajdonos();

    // Visszaadja az autó tulajdonosát (const változat).
    /// @return - Az autó tulajdonosa.
    const Ugyfel* getTulajdonos() const;



    /*-------------------------------------------
                    Setterek
    -------------------------------------------*/
    /// Beállítja az autó rendszámát.
    /// @param r - Az új rendszám.
    void setRendszam(const std::string& r);

    /// Beállítja a kilométeróra értékét.
    /// @param k - Az új km óra érték.
    void setKmOra(int k);

    /// Beállítja a tulajdonost.
    /// @param u - Az új tulajdonos.
    void setTulajdonos(Ugyfel* u);



    /*-------------------------------------------
                Fontos tagmûveletek
    -------------------------------------------*/
    /// Másoló függvény (virtuális, tisztán absztrakt)
    /// @return - új példány
    virtual Auto* clone() const;

    /// Hozzáad egy szervizmûveletet az autó szervizlistájához.
    /// @param m - A hozzáadandó szervizmûvelet pointere
    void addVegzettSzerviz(VegzettMuvelet* m);

    /// Törli a megadott indexû szervizmûveletet a listából.
    /// @param idx - A törlendõ mûvelet pozíciója
    void torolVegzettSzerviz(size_t idx);

    /// Kiírja az autó adatait és szervizmûveleteit az adott ostream-re.
    /// @param os - A kimeneti adatfolyam
    /// @return - Az ostream referenciája (láncoláshoz)
    void kiir(std::ostream& os) const;
};
/*-------------------------------------------
            Globális operátorok
-------------------------------------------*/
/// Kimeneti operátor Datum objektumhoz
/// @param os - kimeneti stream
/// @param a - kiírandó Auto objektum
/// @return - módosított kimeneti stream
std::ostream& operator<<(std::ostream& os, const Auto& a);

#endif // AUTO_H