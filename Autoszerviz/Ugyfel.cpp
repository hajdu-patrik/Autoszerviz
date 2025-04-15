/**
*   \file Ugyfel.cpp
*   Az ugyfel osztály tagfüggvényeinek megvalósítása.
*/

#include "Ugyfel.h"

/*-------------------------------------------
        Konstruktorok és destruktor
-------------------------------------------*/
/// Alapértelmezett konstruktor
Ugyfel::Ugyfel() : nev(""), telefonszam(""), email("") {}

/// Paraméteres konstruktor.
/// @param n - Az ügyfél neve
/// @param t - Az ügyfél telefonszáma
/// @param e - Az ügyfél e-mail címe
Ugyfel::Ugyfel(const std::string& n, const std::string& t, const std::string& e) : nev(n), telefonszam(t), email(e) {}

/// Másoló konstruktor
/// @param u - másolandó Karbantartas objektum
Ugyfel::Ugyfel(const Ugyfel& u) : nev(u.nev), telefonszam(u.telefonszam), email(u.email) {}

/// Destruktor
Ugyfel::~Ugyfel() {}



/*-------------------------------------------
                Operátorok
-------------------------------------------*/
/// Értékadó operátor
/// @param u - másolandó Vizsga objektum
/// @return - Az aktuális objektum referenciája
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
/// Az ügyfél nevének lekérdezése.
/// @return - Név.
const std::string& Ugyfel::getNev() const { return nev; }

/// Az ügyfél telefonszámának lekérdezése.
/// @return - Telefonszám.
const std::string& Ugyfel::getTelefonszam() const { return telefonszam; }

/// Az ügyfél e-mail címének lekérdezése.
/// @return - E-mail cím.
const std::string& Ugyfel::getEmail() const { return email; }



/*-------------------------------------------
                Setterek
-------------------------------------------*/
/// Az ügyfél nevének beállítása.
/// @param n - Az új név.
void Ugyfel::setNev(const std::string& n) { nev = n; }

/// Az ügyfél telefonszámának beállítása.
/// @param t - Az új telefonszám.
void Ugyfel::setTelefonszam(const std::string& t) { telefonszam = t; }

/// Az ügyfél e-mail címének beállítása.
/// @param e - Az új e-mail cím.
void Ugyfel::setEmail(const std::string& e) { email = e; }



/*-------------------------------------------
 Tiszta absztrakt függvények felüldefiniálása
-------------------------------------------*/
/// Kiírja az ügyfél adatait az adott ostream-re.
/// @param os - A kimeneti adatfolyam.
/// @return - Az ostream referenciája (láncoláshoz).
void Ugyfel::kiir(std::ostream& os) const {
    os << "Nev: " << nev << "\n"
        << "Telefonszam: " << telefonszam << "\n"
        << "Email: " << email << "\n"
        << std::endl;
}



/*-------------------------------------------
			Globális operátorok
-------------------------------------------*/
/// Kimeneti operátor Datum objektumhoz
/// @param os - kimeneti stream
/// @param u - kiírandó Ugyfel objektum
/// @return - módosított kimeneti stream
std::ostream& operator<<(std::ostream& os, const Ugyfel& u) {
	u.kiir(os);
	return os;
}