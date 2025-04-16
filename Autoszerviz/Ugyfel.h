#ifndef UGYFEL_H
#define UGYFEL_H

/**
*   \file Ugyfel.h
*   Az Ugyfel(et) le�r� oszt�ly deklar�ci�ja �s tagf�ggv�nyeinek inline megval�s�t�sa.
* 
*   Az oszt�ly c�lja, hogy reprezent�lja egy aut�szerviz �gyfeleit,
*   bele�rtve a nev�ket, el�rhet�s�geiket.
* 
*   Az oszt�lyban szerepl� �sszes std::string tipus� adattag felt�telezi, hogy nem kell �kezetes bet�ket kezelnie.
*/

#include <string>
#include <iostream>

class Ugyfel {
    std::string nev;            ///< Az �gyf�l neve
    std::string telefonszam;    ///< Az �gyf�l telefonsz�ma
    std::string email;          ///< Az �gyf�l e-mail c�me
public:
    /*-------------------------------------------
            Konstruktorok �s destruktor
    -------------------------------------------*/
    /// Alap�rtelmezett konstruktor
    Ugyfel();
    
    /// Param�teres konstruktor.
    /// @param n - Az �gyf�l neve
    /// @param t - Az �gyf�l telefonsz�ma
    /// @param e - Az �gyf�l e-mail c�me
    Ugyfel(const std::string& n, const std::string& t, const std::string& e);

    /// M�sol� konstruktor
    /// @param u - m�soland� Karbantartas objektum
    Ugyfel(const Ugyfel& u);

    /// Destruktor
    ~Ugyfel();



    /*-------------------------------------------
                    Oper�torok
    -------------------------------------------*/
    /// �rt�kad� oper�tor
    /// @param u - m�soland� Vizsga objektum
	/// @return - Az aktu�lis objektum referenci�ja
    Ugyfel& operator=(const Ugyfel& u);



    /*-------------------------------------------
                     Getterek
    -------------------------------------------*/
    /// Az �gyf�l nev�nek lek�rdez�se.
    /// @return - N�v.
    const std::string& getNev() const;

    /// Az �gyf�l telefonsz�m�nak lek�rdez�se.
    /// @return - Telefonsz�m.
    const std::string& getTelefonszam() const;

    /// Az �gyf�l e-mail c�m�nek lek�rdez�se.
    /// @return - E-mail c�m.
    const std::string& getEmail() const;



    /*-------------------------------------------
                    Setterek
    -------------------------------------------*/
    /// Az �gyf�l nev�nek be�ll�t�sa.
    /// @param n - Az �j n�v.
    void setNev(const std::string& n);

    /// Az �gyf�l telefonsz�m�nak be�ll�t�sa.
    /// @param t - Az �j telefonsz�m.
    void setTel(const std::string& t);

    /// Az �gyf�l e-mail c�m�nek be�ll�t�sa.
    /// @param e - Az �j e-mail c�m.
    void setEmail(const std::string& e);



    /*-------------------------------------------
                Fontos tagm�veletek
    -------------------------------------------*/
    /// M�sol� f�ggv�ny (virtu�lis, tiszt�n absztrakt)
    /// @return - �j p�ld�ny
    virtual Ugyfel* clone() const;

    /// Ki�rja az �gyf�l adatait az adott ostream-re.
    /// @param os - A kimeneti adatfolyam.
    /// @return - Az ostream referenci�ja (l�ncol�shoz).
    void kiir(std::ostream& os) const;
};
/*-------------------------------------------
            Glob�lis oper�torok
-------------------------------------------*/
/// Kimeneti oper�tor Datum objektumhoz
/// @param os - kimeneti stream
/// @param u - ki�rand� Ugyfel objektum
/// @return - m�dos�tott kimeneti stream
std::ostream& operator<<(std::ostream& os, const Ugyfel& u);

#endif // UGYFEL_H