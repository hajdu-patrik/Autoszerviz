#ifndef AUTO_H
#define AUTO_H

/**
*   \file Auto.h
*   Az aut� adatait le�r� oszt�ly.
*
*   Az oszt�ly c�lja, hogy reprezent�lja egy aut� adatait, bele�rtve a
*   rendsz�m, m�rka, t�pus, kilom�ter�ra �ll�sa, �zembe helyez�s d�tuma,
*   valamint a hozz� tartoz� szervizm�veletek list�j�t.
*   Az oszt�ly lehet�s�get biztos�t az adatok kezel�s�re, m�dos�t�s�ra,
*   valamint a szervizt�rt�net nyilv�ntart�s�ra.
*
*   Az oszt�lyban szerepl� �sszes std::string tipus� adattag felt�telezi, hogy nem kell �kezetes bet�ket kezelnie.
*/

#include <string>

#include "Datum.h"
#include "Ugyfel.h"
#include "Vector.hpp"
#include "VegzettMuvelet.h"

class Auto {
    std::string rendszam;                               ///< Az aut� rendsz�ma  
    std::string marka;                                  ///< Az aut� m�rk�ja  
    std::string tipus;                                  ///< Az aut� t�pusa  
    int kmOra;                                          ///< Kilom�ter�ra �ll�sa  
    Datum uzembeHelyezes;                               ///< �zembe helyez�s d�tuma  
    Vector<VegzettMuvelet*> vegzettSzervizMuveletek;    ///< Elv�gzett szervizm�veletek  
    Ugyfel* tulajdonos;                                 ///< Az aut� tulajdonosa  
public:
    /*-------------------------------------------
            Konstruktorok �s destruktor
    -------------------------------------------*/
    /// Alap�rtelmezett konstruktor.  
    Auto();

    /// Param�teres konstruktor.  
    /// @param r - Az aut� rendsz�ma  
    /// @param m - Az aut� m�rk�ja  
    /// @param t - Az aut� t�pusa  
    /// @param k - A kilom�ter�ra �ll�sa  
    Auto(const std::string& r, const std::string& m, const std::string& t, int k);

    /// Param�teres konstruktor.  
    /// @param r - Az aut� rendsz�ma  
    /// @param m - Az aut� m�rk�ja  
    /// @param t - Az aut� t�pusa  
    /// @param k - A kilom�ter�ra �ll�sa  
    /// @param d - Az �zembe helyez�s d�tuma  
    /// @param v - Az aut�hoz tartoz� szervizm�veletek list�ja  
    /// @param u - Az aut� tulajdonosa  
    Auto(const std::string& r, const std::string& m, const std::string& t, int k, const Datum& d, const Vector<VegzettMuvelet*>& v, Ugyfel* u);

    /// M�sol� konstruktor.  
    /// @param a - M�soland� Auto objektum  
    Auto(const Auto& a);

    /// Destruktor  
    virtual ~Auto();



    /*-------------------------------------------
                    Oper�torok
    -------------------------------------------*/
    /// �rt�kad� oper�tor.
    /// @param a - m�soland� Auto objektum
    /// @return - Az aktu�lis objektum referenci�ja
    Auto& operator=(const Auto& a);

    /// Egyenl�s�g oper�tor t�lterhel�se az Auto oszt�lyhoz.
    /// @param a - Az �sszehasonl�tand� Auto objektum.
    /// @return - true, ha az objektumok megegyeznek, k�l�nben false.
    bool operator==(const Auto& a) const;



    /*-------------------------------------------
                     Getterek
    -------------------------------------------*/
    /// Visszaadja az aut� rendsz�m�t.
    /// @return - Rendsz�m.
    const std::string& getRendszam() const;

    /// Visszaadja az aut� m�rk�j�t.
    /// @return - M�rka.
    const std::string& getMarka() const;

    /// Visszaadja az aut� t�pus�t.
    /// @return - T�pus.
    const std::string& getTipus() const;

    /// Visszaadja a kilom�ter�ra aktu�lis �rt�k�t.
    /// @return - Km �ra �rt�ke.
    const int getKmOra() const;

    /// Visszaadja az �zembe helyez�s d�tum�t.
    /// @return - D�tum .
    const Datum& getUzembeHelyezes() const;

    /// Visszaadja az aut�hoz tartoz� szervizm�veletek list�j�t.
    /// @return - Szervizm�veletek vektora.
    Vector<VegzettMuvelet*>& getSzervizMuveletek();

    /// Visszaadja az aut�hoz tartoz� szervizm�veletek list�j�t (const v�ltozat).
    /// @return - Szervizm�veletek vektora.
    const Vector<VegzettMuvelet*>& getSzervizMuveletek() const;

    // Visszaadja az aut� tulajdonos�t.
    /// @return - Az aut� tulajdonosa.
    Ugyfel* getTulajdonos();

    // Visszaadja az aut� tulajdonos�t (const v�ltozat).
    /// @return - Az aut� tulajdonosa.
    const Ugyfel* getTulajdonos() const;



    /*-------------------------------------------
                    Setterek
    -------------------------------------------*/
    /// Be�ll�tja az aut� rendsz�m�t.
    /// @param r - Az �j rendsz�m.
    void setRendszam(const std::string& r);

    /// Be�ll�tja a kilom�ter�ra �rt�k�t.
    /// @param k - Az �j km �ra �rt�k.
    void setKmOra(int k);

    /// Be�ll�tja a tulajdonost.
    /// @param u - Az �j tulajdonos.
    void setTulajdonos(Ugyfel* u);



    /*-------------------------------------------
                Fontos tagm�veletek
    -------------------------------------------*/
    /// M�sol� f�ggv�ny (virtu�lis, tiszt�n absztrakt)
    /// @return - �j p�ld�ny
    virtual Auto* clone() const;

    /// Hozz�ad egy szervizm�veletet az aut� szervizlist�j�hoz.
    /// @param m - A hozz�adand� szervizm�velet pointere
    void addVegzettSzerviz(VegzettMuvelet* m);

    /// T�rli a megadott index� szervizm�veletet a list�b�l.
    /// @param idx - A t�rlend� m�velet poz�ci�ja
    void torolVegzettSzerviz(size_t idx);

    /// Ki�rja az aut� adatait �s szervizm�veleteit az adott ostream-re.
    /// @param os - A kimeneti adatfolyam
    /// @return - Az ostream referenci�ja (l�ncol�shoz)
    void kiir(std::ostream& os) const;
};
/*-------------------------------------------
            Glob�lis oper�torok
-------------------------------------------*/
/// Kimeneti oper�tor Datum objektumhoz
/// @param os - kimeneti stream
/// @param a - ki�rand� Auto objektum
/// @return - m�dos�tott kimeneti stream
std::ostream& operator<<(std::ostream& os, const Auto& a);

#endif // AUTO_H