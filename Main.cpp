/**
 *  \file Main.cpp
 *  Ez a fajl az autoszerviz nyilvantarto rendszer belepesi pontja.
 */

#include "Applikacio.h"

int main() {
    Applikacio app;
    if (app.applikacio()) {
        return 0; // korrekt kil�p�s
    }
    return 0;  // szint�n korrekt, de redund�ns
}