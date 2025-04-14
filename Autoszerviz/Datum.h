#ifndef DATUM_H  
#define DATUM_H  

/**
*   \file Datum.h
*   A Datum(mot) le�r� oszt�ly deklar�ci�ja �s tagf�ggv�nyeinek inline megval�s�t�sa.
*/

#include <iostream>
#include <iomanip>
#include <sstream>

class Datum {
    int ev;     ///< �v  
    int ho;     ///< H�nap  
    int nap;    ///< Nap  

public:
    /*-------------------------------------------
            Konstruktorok �s destruktor
    -------------------------------------------*/
    /// Alap�rtelmezett konstruktor
    /// 0-ra inicializ�lja az �vet, h�napot �s napot.
    Datum();

    /// Param�teres konstruktor
    /// @param e - �v
    /// @param h - h�nap
    /// @param n - nap
    Datum(int e, int h, int n);

    /// M�sol� konstruktor
    /// @param d - m�soland� Datum objektum
    Datum(const Datum& d);

    /// Destruktor
    ~Datum();



	/*-------------------------------------------
		            Oper�torok
	-------------------------------------------*/
    /// �rt�kad� oper�tor
    /// @param d - m�soland� Datum objektum
    /// @return - az aktu�lis objektum referenci�ja
    Datum& operator=(const Datum& d);

    /// �sszehasonl�t� oper�tor
    /// @param d - �sszehasonl�tand� Datum objektum
    /// @return - true, ha az objektumok megegyeznek, k�l�nben false.
    bool operator==(const Datum& d) const;



    /*-------------------------------------------
                     Getterek
    -------------------------------------------*/
    /// �v lek�rdez�se
    /// @return - �v
    int getEv() const;

    /// H�nap lek�rdez�se
    /// @return - h�nap
    int getHo() const;

    /// Nap lek�rdez�se
    /// @return - nap
    int getNap() const;

	/// D�tum eltelt napok sz�m�nak lek�rdez�se
	/// @param d - m�sik Datum objektum
    int elteltNap(const Datum& d) const;



    /*-------------------------------------------
                    Setterek
    -------------------------------------------*/
    /// D�tum be�ll�t�sa
    /// @param e - �v
    /// @param h - h�nap
    /// @param n - nap
    void setDatum(int e, int h, int n);



    /*-------------------------------------------
                   Seg�df�ggv�nyek
    -------------------------------------------*/
    /// L�trehoz egy Datum objektumot egy stringb�l.
    /// A string form�tuma: "����.HH.NN".
    /// @param str - A d�tumot tartalmaz� string.
    /// @return - A l�trehozott Datum objektum.
    static Datum parseFromString(const std::string& str);

    /// Egy Datum objektumot stringg� alak�t "����.HH.NN" form�tumban.
    /// @return std::string A form�zott d�tum sz�vegk�nt.
    const std::string toString() const;
};
/*-------------------------------------------
		    Glob�lis oper�torok
-------------------------------------------*/
/// Kimeneti oper�tor Datum objektumhoz
/// @param os - kimeneti stream
/// @param d - ki�rand� Datum objektum
/// @return - m�dos�tott kimeneti stream
std::ostream& operator<<(std::ostream& os, const Datum& d);

#endif // !DATUM_H