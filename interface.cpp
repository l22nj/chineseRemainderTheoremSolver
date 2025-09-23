//
// Created by jakob on 25/04/2025.
//

#include "interface.h"

#include <algorithm>
#include <iostream>
#include <sstream>
using namespace std;

/**
 * Kuvab vaadeldava võrrandi konsoolis
 * @param v6rrand Kuvatav võrrand
 */
void kuvaVõrrand(V6rrand v6rrand) {
    for (size_t i{0}; i < v6rrand.v6rrandid.size(); ++i) {
        cout << v6rrand.v6rrandid[i].first << " kongruentne arvuga " << v6rrand.v6rrandid[i].second.j22k <<
            " mooduli " << v6rrand.v6rrandid[i].second.moodul << " järgi." << endl;
    }
}

Polünoom muudaTekstPolünoomiks(const string& s) {
    vector<int> v;
    string sõne = s;
    stringstream ss(sõne);
    long long i;
    while (ss >> i)
        v.insert(v.begin(), i);
    Polünoom pol{v};
    return pol;
}

void mainloop() {
    V6rrand v6rrand;
    vector<V6rrand> v6rrandid;
    vector<J22k> tulemus;
    int j, m;
    string sõne_p;
    string s;

    cout << "HIINA JÄÄGITEOREEMI ABIL KONGRUENTSISÜSTEEMI LAHENDAJA" << endl;
    cout << "Peate sisestama ükshaaval polünoomid, jäägid ja moodulid" << endl;
    cout << "Kui soovite lõpetada, sisestage POLÜNOOMI asemel 'L' (muul ajal lõpetada ei saa)" << endl;
    cout << endl;
    while (true) {
        cout << "Sisesta polünoomi kordajad (nt x^3 +3x - 1 == '1 0 3 -1') või 'L' : ";
        getline(cin, sõne_p);
        if (sõne_p == "L") break;
        cout << "Sisesta jääk ja moodul (nt '2 9' - st jääk 2 mooduli 9 järgi): ";
        getline(cin, s);
        stringstream(s) >> j >> m;
        v6rrand.lisa_v6rrand(J22k(j, Moodul(m)), muudaTekstPolünoomiks(sõne_p));
        sõne_p = "";
    }
    if (v6rrand.v6rrandid.empty()) {
        cout << "Nägemiseni!";
        return;
    }
    cout << endl << "Teie sisestatud võrrandisüsteem: " << endl;
    kuvaVõrrand(v6rrand);
    if (lihtsusta(v6rrand, v6rrandid) == 0)
        return;
    cout << endl << "Sellest tulenevad lahenduvad süsteemid on (eraldatud tühja reaga): " << endl;
    for (auto el : v6rrandid) {
        kuvaVõrrand(el);
        tulemus.push_back(el.lahenda_systeem()); // kohe lahendab ära kah
        cout << endl;
    }
    cout << "Seega iga x avaldub ühel järgnevatest kujudest: " << endl;
    for (auto el : tulemus)
        cout << "x = " << el.j22k << " + t*" << el.moodul <<endl;
    cout << "Kus t on suvaline täisarv.";
}


