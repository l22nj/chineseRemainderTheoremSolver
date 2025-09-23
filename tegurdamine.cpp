//
// Created by jakob on 25/04/2025.
//

#include "tegurdamine.h"
#include <iostream>
#include <cmath>
using namespace std;

/**
 * Leiab kahe täisarvu suurima ühisteguri Eukleidese algoritmi abil
 * @param a Täisarv
 * @param b Täisarv
 * @return Arvude 'a' ja 'b' suurim ühistegur
 */
int leiaSuurimÜhistegur(int a, int b) {
    while (true) {
        int temp = b;
        b = a % b;
        a = temp;
        if (b == 0)
            return abs(a);
    }
}

/**
 * Kontrollib, kas sisendiks on algarv
 * @param a Täisarv
 * @return Tõeväärtus, kas 'a' on algarv
 */
bool kasOnAlgarv(long long a) {
    if (abs(a) == 1)
        return false;
    for (long long i{2}; i <= sqrtl(abs(a)); i++)
        if (a % i == 0)
            return false;
    return true;
}

/**
 * Kontrollib, kas sisendiks on täisruut
 * @param a Täisarv
 * @return Tõeväärtus, kas arv 'a' on mõne täisarvu ruut
 */
bool kasOnRuut (long long a) {
    long double arv2 = sqrtl(a);
    if (floor(arv2) == ceil(arv2))
        return true;
    return false;
}

/**
 * Tegurdab arvu 'a' kaheks väiksemaks täisarvuks (Fermat' meetod)
 * @param a Täisarv
 * @return Pair, kus on kaks täisarvu 'a' tegurit
 */
pair<long long, long long> leiaKaksTegurit(long long a) {
    if (a < 3)
        return make_pair(1,a);
    if (a % 2 == 0)
        return make_pair(2, a/2);
    if (kasOnAlgarv(a))
        return make_pair(1, a);

    long long piir = (a + 1) * (a + 1) / 4;

    for (long long i = ceil(sqrtl(a)); i < piir; ++i) {
        long long b = i*i - a;
        if (kasOnRuut(b)) {
            b = sqrtl(b);
            return make_pair(i-b, i+b);
        }
    }
    cout << "väike error (ilmselt liiga suured arvud selle programmi jaoks): " << a << endl;
    return make_pair(0, 0);
}

/**
 * Salvestab map-i 'algtegurid' arvu 'a' algtegurid pair-idena
 * @param a Tegurdatav arv
 * @param algtegurid Map paaridest, mille esimesel kohal on arvus esinev algarv ning teisel kohal selle algarvu aste
 */
void tegurdaArv(long long a, map<long long, long long>& algtegurid) {
    if (abs(a) == 1)
        return;

    auto paar{leiaKaksTegurit(a)};
    long long first = abs(paar.first);
    long long second = abs(paar.second);

    if (kasOnAlgarv(first)) {
        if (algtegurid.contains(first))
            algtegurid[first] += 1;
        else
            algtegurid[first] = 1;
    }
    else
        tegurdaArv(first, algtegurid);

    if (kasOnAlgarv(second)) {
        if (algtegurid.contains(second))
            algtegurid[second] += 1;
        else
            algtegurid[second] = 1;
    }
    else
        tegurdaArv(second, algtegurid);
}

