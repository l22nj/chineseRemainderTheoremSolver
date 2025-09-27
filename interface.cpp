//
// Created by jakob on 25/04/2025.
//

#include "interface.h"

#include <algorithm>
#include <iostream>
#include <sstream>

#include "tester.h"
using namespace std;

/**
 * Kuvab vaadeldava võrrandi konsoolis
 * @param v6rrand Kuvatav võrrand
 */
void kuvaVõrrand(Vorrandisusteem v6rrand) {
    cout << v6rrand;
}

/**
 * Muudab sõne polünoomiks
 * @param s Polünoom sõnena
 * @return Polünoom klassi Polunoom objektina
 */
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

/**
 * Võtab kasutajalt sisendi ja koostab selle põhjal võrrandisüsteemi
 * @return Lahendatav võrrandisüsteem
 */
Vorrandisusteem sisendiTsukkel() {
    Vorrandisusteem vs;
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
        vs.lisaVorrand(Jaak(j, Moodul(m)), muudaTekstPolünoomiks(sõne_p));
        sõne_p = "";
    }
    return vs;
}

/**
 * Programmi põhitöö main.cpp faili jaoks
 * main.cpp failis saab kasutada selle asemel nt testereid
 */
void mainloop() {
    Vorrandisusteem vs = sisendiTsukkel();
    if (vs.vorrandid.empty()) {
        cout << "Nägemiseni!";
        return;
    }
    cout << endl << "Teie sisestatud võrrandisüsteem: " << endl;
    kuvaVõrrand(vs);
    cout << endl << "Sellest tulenevad lahenduvad süsteemid on (eraldatud tühja reaga): " << endl;
    vector<Jaak> tulemus = vs.lahendaSusteemJaKuva();
    cout << "Seega iga x avaldub ühel järgnevatest kujudest: " << endl;
    for (auto el : tulemus)
        cout << "x = " << el.jaak << " + t*" << el.moodul <<endl;
    cout << "Kus t on suvaline täisarv.";
}

void testermainloop() {
    cout << "------TEGU ON TESTERFUNKTSIOONIGA------" << endl;
    Vorrandisusteem vs = sisendiTsukkel();
    if (vs.vorrandid.empty()) {
        cout << "Nägemiseni!";
        return;
    }
    cout << endl << "Teie sisestatud võrrandisüsteem: " << endl;
    kuvaVõrrand(vs);
    if (tester(vs))
        cout << "Kõik lahendid klapivad :)" << endl;
    else
        cout << "Kuskil viga!" << endl;
}


