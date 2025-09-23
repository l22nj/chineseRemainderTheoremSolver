//
// Created by jakob on 25/04/2025.
//

#include "tegurdamine.h"
#include <iostream>
#include <cmath>
using namespace std;

int eukleidese_algoritm(int a, int b) // leiab suurima ühisteguri kahe arvu vahel
{
    int syt{a}, j22k{b}, vahej22k;
    while (true)
    {
        vahej22k = j22k;
        j22k = syt % j22k;
        syt = vahej22k;

        if (j22k == 0) return abs(syt);
    }
}

bool kasAlgarv(long long arv)
{
    if (abs(arv) == 1) return false;
    for (long long i{2}; i <= sqrtl(abs(arv)); i++)
        if (arv % i == 0)
            return false;
    return true;
}

bool kasOnRuut (long long arv)
{
    long double arv2 = sqrtl(arv);
    if (floor(arv2) == ceil(arv2)) return true;
    return false;
}

pair<long long, long long> fermat_meetod(long long arv) // info.txt natuke seletatud
{
    if (arv < 3) return make_pair(1,arv);
    if (arv % 2 == 0) return make_pair(2, arv/2);
    if (kasAlgarv(arv)) return make_pair(1, arv);

    long long piir = (arv + 1) * (arv + 1) / 4, b;

    for (long long a = ceil(sqrtl(arv)); a < piir; ++a)
    {
        b = a*a - arv;
        if (kasOnRuut(b))
        {
            b = sqrtl(b);
            return make_pair(a-b, a+b);
        }
    }
    cout << "väike error (ilmselt liiga suured arvud selle programmi jaoks): " << arv << endl;
    return make_pair(0, 0);
}

void tegurda_arv(long long arv, map<long long, long long>& m) // viib arvu algteguriteks Fermat' meetodi abil ja salvestab m
{
    if (abs(arv) == 1) return;

    auto paar{fermat_meetod(arv)};
    long long first{abs(paar.first)}, second{abs(paar.second)};

    if (kasAlgarv(first))
    {
        if (m.contains(first)) m[first] += 1;
        else m[first] = 1;
    }
    else tegurda_arv(first, m);

    if (kasAlgarv(second))
    {
        if (m.contains(second)) m[second] += 1;
        else m[second] = 1;
    }
    else tegurda_arv(second, m);
}

