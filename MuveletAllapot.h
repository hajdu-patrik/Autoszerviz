/**
*	\file MuveletAllapot.h
*   Ez a f�jl a men�rendszer �llapotait defini�lja.
*/

#ifndef MUVELETALLAPOT_H
#define MUVELETALLAPOT_H

/// A m�velet v�grehajt�s�nak �llapot�t jelz� enum.
enum class MuveletAllapot {
    Siker,
    Kilepes,
    Hiba
};

#endif // !MUVELETALLAPOT_H