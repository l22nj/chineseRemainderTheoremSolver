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
void kuvaVõrrand(Vorrandisusteem v6rrand) {
    cout << v6rrand;
}

Polunoom muudaTekstPolünoomiks(const string& s) {
    vector<int> v;
    string sõne = s;
    stringstream ss(sõne);
    long long i;
    while (ss >> i)
        v.insert(v.begin(), i);
    Polunoom pol{v};
    return pol;
}

void mainloop() {
    Vorrandisusteem v6rrand;
    vector<Vorrandisusteem> v6rrandid;
    vector<Jaak> tulemus;
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
        v6rrand.lisaVorrand(Jaak(j, Moodul(m)), muudaTekstPolünoomiks(sõne_p));
        sõne_p = "";
    }
    if (v6rrand.vorrandid.empty()) {
        cout << "Nägemiseni!";
        return;
    }
    cout << endl << "Teie sisestatud võrrandisüsteem: " << endl;
    kuvaVõrrand(v6rrand);
    if (v6rrand.lihtsusta(v6rrandid) == 0)
        return;
    cout << endl << "Sellest tulenevad lahenduvad süsteemid on (eraldatud tühja reaga): " << endl;
    for (auto el : v6rrandid) {
        kuvaVõrrand(el);
        tulemus.push_back(el.lahendaSusteem()); // kohe lahendab ära kah
        cout << endl;
    }
    cout << "Seega iga x avaldub ühel järgnevatest kujudest: " << endl;
    for (auto el : tulemus)
        cout << "x = " << el.jaak << " + t*" << el.moodul <<endl;
    cout << "Kus t on suvaline täisarv.";
}


