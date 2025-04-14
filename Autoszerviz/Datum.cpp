/**
*   \file Datum.cpp
*   A datum oszt�ly tagf�ggv�nyeinek megval�s�t�sa.
*/

#include "Datum.h"

/*-------------------------------------------
        Konstruktorok �s destruktor
-------------------------------------------*/
/// Alap�rtelmezett konstruktor
/// 0-ra inicializ�lja az �vet, h�napot �s napot.
Datum::Datum() : ev(0), ho(0), nap(0) {}

/// Param�teres konstruktor
/// @param e - �v
/// @param h - h�nap
/// @param n - nap
Datum::Datum(int e, int h, int n) : ev(e), ho(h), nap(n) {}

/// M�sol� konstruktor
/// @param d - m�soland� Datum objektum
Datum::Datum(const Datum& d) : ev(d.ev), ho(d.ho), nap(d.nap) {}

/// Destruktor
Datum::~Datum() {}



/*-------------------------------------------
                Oper�torok
-------------------------------------------*/
/// �rt�kad� oper�tor
/// @param d - m�soland� Datum objektum
/// @return - az aktu�lis objektum referenci�ja
Datum& Datum::operator=(const Datum& d) {
    if (this != &d) {
        ev = d.ev;
        ho = d.ho;
        nap = d.nap;
    }
    return *this;
}

/// �sszehasonl�t� oper�tor
/// @param d - �sszehasonl�tand� Datum objektum
/// @return - true, ha az objektumok megegyeznek, k�l�nben false.
bool Datum::operator==(const Datum& d) const {
    return ev == d.ev && ho == d.ho && nap == d.nap;
}



/*-------------------------------------------
                 Getterek
-------------------------------------------*/
/// �v lek�rdez�se
/// @return - �v
int Datum::getEv() const { return ev; }

/// H�nap lek�rdez�se
/// @return - h�nap
int Datum::getHo() const { return ho; }

/// Nap lek�rdez�se
/// @return - nap
int Datum::getNap() const { return nap; }

/// D�tum eltelt napok sz�m�nak lek�rdez�se
/// @param d - m�sik Datum objektum
int Datum::elteltNap(const Datum& d) const {
    int e = d.getEv() - ev;
    int h = d.getHo() - ho;
    int n = d.getNap() - nap;
    return e * 365 + h * 30 + n;
}

/*-------------------------------------------
                Setterek
-------------------------------------------*/

/// D�tum be�ll�t�sa
/// @param e - �v
/// @param h - h�nap
/// @param n - nap
void Datum::setDatum(int e, int h, int n) {
    ev = e;
    ho = h;
    nap = n;
}



/*-------------------------------------------
               Seg�df�ggv�nyek
-------------------------------------------*/
/// L�trehoz egy Datum objektumot egy stringb�l.
/// A string form�tuma: "����.HH.NN".
/// @param str - A d�tumot tartalmaz� string.
/// @return - A l�trehozott Datum objektum.
Datum Datum::parseFromString(const std::string& str) {
    std::istringstream iss(str);
    int e = 0, h = 0, n = 0;
    char dot1 = '\0', dot2 = '\0';

    if (!(iss >> e >> dot1 >> h >> dot2 >> n) || dot1 != '.' || dot2 != '.') throw std::invalid_argument("Hibas datum formatum! (parseFromString)");

    return Datum(e, h, n);
}

/// Egy Datum objektumot stringg� alak�t "����.HH.NN" form�tumban.
/// @return std::string A form�zott d�tum sz�vegk�nt.
const std::string Datum::toString() const {
    std::ostringstream oss;

    oss << std::setw(4) << std::setfill('0') << ev << "."
        << std::setw(2) << std::setfill('0') << ho << "."
        << std::setw(2) << std::setfill('0') << nap;

    return oss.str();
}




/*-------------------------------------------
            Glob�lis oper�torok
-------------------------------------------*/
/// Kimeneti oper�tor Datum objektumhoz
/// @param os - kimeneti stream
/// @param d - ki�rand� Datum objektum
/// @return - m�dos�tott kimeneti stream
std::ostream& operator<<(std::ostream& os, const Datum& d) {
    return os << std::setw(4) << std::setfill('0') << d.getEv() << "."
        << std::setw(2) << std::setfill('0') << d.getHo() << "."
        << std::setw(2) << std::setfill('0') << d.getNap();
}