#ifndef VEGZETTMUVELET_H  
#define VEGZETTMUVELET_H  

/**
*   \file VegzettMuvelet.h
*   Az VegzettMuvelet(et) le�r� absztrakt oszt�ly deklar�ci�ja �s tagf�ggv�nyeinek inline megval�s�t�sa.
*
*   Az oszt�lyban szerepl� �sszes std::string tipus� adattag felt�telezi, hogy nem kell �kezetes bet�ket kezelnie.
*/

#include <string>

#include "Datum.h"

class VegzettMuvelet {
    std::string muvelet;    ///< A m�velet megnevez�se  
    Datum idopont;          ///< A m�velet id�pontja  
    int ar;                 ///< A m�velet �ra  
    int akt_kmOra;          ///< Az aktu�lis kilom�ter�ra �ll�s
public:
    /*-------------------------------------------
                  Konstruktorok
    -------------------------------------------*/
    /// Alap�rtelmezett konstruktor
    /// L�trehoz egy �res m�veletet null�kkal inicializ�lt d�tummal �s 0 �rral.
    VegzettMuvelet() : muvelet(""), idopont(), ar(0), akt_kmOra(0) {}

    /// Param�teres konstruktor
    /// @param m - M�velet neve
    /// @param d - M�velet id�pontja
    /// @param a - M�velet �ra
    VegzettMuvelet(const std::string& m, const Datum& d, int a, int k) : muvelet(m), idopont(d), ar(a), akt_kmOra(k) {}

    /// M�sol� konstruktor
    /// @param vm - M�soland� VegzettMuvelet objektum
    VegzettMuvelet(const VegzettMuvelet& vm) : muvelet(vm.muvelet), idopont(vm.idopont), ar(vm.ar), akt_kmOra(vm.akt_kmOra) {}



    /*-------------------------------------------
                    Oper�torok
    -------------------------------------------*/
    /// �rt�kad� oper�tor
    /// @param vm - M�soland� VegzettMuvelet objektum
    /// @return - Az aktu�lis objektum referencia
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
    /// Getter a m�velet nev�hez
    /// @return - A m�velet neve (const referencia)
    const std::string& getMuvelet() const { return muvelet; }

    /// Getter az id�ponthoz
    /// @return - A m�velet d�tuma (const referencia)
    const Datum& getDatum() const { return idopont; }

    /// Getter az �rhoz
    /// @return - A m�velet �ra
    int getAr() const { return ar; }

    /// Getter az aktu�lis kilom�ter�ra �ll�s�hoz
    /// @return - Az aktu�lis kilom�ter�ra �ll�s
    int getAktKmOra() const { return akt_kmOra; }



    /*-------------------------------------------
                    Setterek
    -------------------------------------------*/
    /// Setter az id�ponthoz
    /// @param d - �j d�tum
    void setDatum(const Datum& d) { idopont = d; }

    /// Setter az �rhoz
    /// @param a - �j �r
    void setAr(int a) { ar = a; }

    /// Setter a m�velet nev�hez
    /// @param m - �j m�velet n�v
    void setMuvelet(const std::string& m) { muvelet = m; }

    /// Setter az aktu�lis kilom�ter�ra �ll�s�hoz
    /// @param k - �j kilom�ter�ra �ll�s
    void setAktKmOra(int k) { akt_kmOra = k; }



    /*-------------------------------------------
                Virtu�lis f�ggv�nyek
    -------------------------------------------*/
    /// Ki�r� f�ggv�ny (virtu�lis, tiszt�n absztrakt)
    /// @param os - A kimeneti stream, ahova a m�velet ki�r�sra ker�l
    virtual void kiir(std::ostream& os) const = 0;

    /// M�sol� f�ggv�ny (virtu�lis, tiszt�n absztrakt)
    /// @return - Egy �j VegzettMuvelet pointer, amely a m�solt objektumot reprezent�lja
    virtual VegzettMuvelet* clone() const = 0;

    /// Virtu�lis destruktor
    virtual ~VegzettMuvelet() = default;
};

#endif // VEGZETTMUVELET_H