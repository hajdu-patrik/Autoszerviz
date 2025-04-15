/**
*   \file Ugyfel.cpp
*   Az ugyfel oszt�ly tagf�ggv�nyeinek megval�s�t�sa.
*/

#include "Ugyfel.h"

/*-------------------------------------------
        Konstruktorok �s destruktor
-------------------------------------------*/
/// Alap�rtelmezett konstruktor
Ugyfel::Ugyfel() : nev(""), telefonszam(""), email("") {}

/// Param�teres konstruktor.
/// @param n - Az �gyf�l neve
/// @param t - Az �gyf�l telefonsz�ma
/// @param e - Az �gyf�l e-mail c�me
Ugyfel::Ugyfel(const std::string& n, const std::string& t, const std::string& e) : nev(n), telefonszam(t), email(e) {}

/// M�sol� konstruktor
/// @param u - m�soland� Karbantartas objektum
Ugyfel::Ugyfel(const Ugyfel& u) : nev(u.nev), telefonszam(u.telefonszam), email(u.email) {}

/// Destruktor
Ugyfel::~Ugyfel() {}



/*-------------------------------------------
                Oper�torok
-------------------------------------------*/
/// �rt�kad� oper�tor
/// @param u - m�soland� Vizsga objektum
/// @return - Az aktu�lis objektum referenci�ja
Ugyfel& Ugyfel::operator=(const Ugyfel& u) {
    if (this != &u) {
        nev = u.nev;
        telefonszam = u.telefonszam;
        email = u.email;
    }
    return *this;
}



/*-------------------------------------------
                 Getterek
-------------------------------------------*/
/// Az �gyf�l nev�nek lek�rdez�se.
/// @return - N�v.
const std::string& Ugyfel::getNev() const { return nev; }

/// Az �gyf�l telefonsz�m�nak lek�rdez�se.
/// @return - Telefonsz�m.
const std::string& Ugyfel::getTelefonszam() const { return telefonszam; }

/// Az �gyf�l e-mail c�m�nek lek�rdez�se.
/// @return - E-mail c�m.
const std::string& Ugyfel::getEmail() const { return email; }



/*-------------------------------------------
                Setterek
-------------------------------------------*/
/// Az �gyf�l nev�nek be�ll�t�sa.
/// @param n - Az �j n�v.
void Ugyfel::setNev(const std::string& n) { nev = n; }

/// Az �gyf�l telefonsz�m�nak be�ll�t�sa.
/// @param t - Az �j telefonsz�m.
void Ugyfel::setTelefonszam(const std::string& t) { telefonszam = t; }

/// Az �gyf�l e-mail c�m�nek be�ll�t�sa.
/// @param e - Az �j e-mail c�m.
void Ugyfel::setEmail(const std::string& e) { email = e; }



/*-------------------------------------------
 Tiszta absztrakt f�ggv�nyek fel�ldefini�l�sa
-------------------------------------------*/
/// Ki�rja az �gyf�l adatait az adott ostream-re.
/// @param os - A kimeneti adatfolyam.
/// @return - Az ostream referenci�ja (l�ncol�shoz).
void Ugyfel::kiir(std::ostream& os) const {
    os << "Nev: " << nev << "\n"
        << "Telefonszam: " << telefonszam << "\n"
        << "Email: " << email << "\n"
        << std::endl;
}



/*-------------------------------------------
			Glob�lis oper�torok
-------------------------------------------*/
/// Kimeneti oper�tor Datum objektumhoz
/// @param os - kimeneti stream
/// @param u - ki�rand� Ugyfel objektum
/// @return - m�dos�tott kimeneti stream
std::ostream& operator<<(std::ostream& os, const Ugyfel& u) {
	u.kiir(os);
	return os;
}