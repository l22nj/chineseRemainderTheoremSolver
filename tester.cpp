//
// Created by l22nj on 9/27/25.
//

#include "tester.h"

#include <iostream>

using namespace std;

/**
 * Testib brute force meetodil, kas antud arv sobib võrrandisüsteemi lahendiks
 * @param vs Vorrandisusteem objekt
 * @param i Arv, mida võrrandisüsteemi lahendiks proovitakse
 * @return Tõeväärtus
 */
bool bruteforceTest(Vorrandisusteem& vs, int i) {
    for (auto& vorrand : vs.vorrandid) {
        Polunoom polunoom = vorrand.first;
        Jaak jaak = vorrand.second;
        Jaak polunoomiJaak{polunoom.vaartus(i), jaak.moodul};
        jaak.normeeri();
        polunoomiJaak.normeeri();
        if (polunoomiJaak.jaak != jaak.jaak) {
            return false;
        }
    } return true;
}

/**
 * Leiab brute force meetodil kõik sobivad lahendid võrrandisüsteemile
 * @param vs Vorrandisusteem objekt
 * @return Kõik lahendid, mis rahuldavad antud võrrandisüsteemi
 */
vector<Jaak> bruteforceLahendaJaKuva(Vorrandisusteem& vs) {
    vector<Jaak> tulemused;
    Moodul moodul{vs.leiaMooduliteVahimUhiskordne()};
    cout << "BRUTEFORCE LAHENDID:" << endl;
    for (auto i = 0; i < moodul.vaartus(); ++i) {
        bool flag = true;
        if (!bruteforceTest(vs, i)) {
            flag = false;
        } if (flag) {
            tulemused.emplace_back(i, moodul);
            cout << "Sobiv jääk: " << i << " mod " << moodul <<endl;
        }
    }
    return tulemused;
}

/**
 * Kontrollib, kas programm võrrandisüsteemi lahendamiseks sisendiks saadud võrrandisüsteemi peal toimib!
 * @param vs Võrrandisüsteem, mille peal lahendamist testitakse
 * @return Tõeväärtus, kas seda lahendatakse õigesti
 */
bool tester(Vorrandisusteem& vs) {
    vector<Jaak> tulemusBrute = bruteforceLahendaJaKuva(vs);
    vector<Jaak> tulemus = vs.lahendaSusteemJaKuva();

    sorteeriJaagiVektor(tulemus);
    sorteeriJaagiVektor(tulemusBrute);

    for (auto el : tulemus) {
        cout << "Saadud tulemus: " << el.jaak << " mod " << el.moodul << endl;
    }
     // CLion ei ole nõus õigete indentidega laskma mul seda kirjutada
     if (tulemus.size() < tulemusBrute.size()) {
         for (auto bruteJaak : tulemusBrute) {
             bool flag = true;
             for (auto jaak : tulemus)
                 if (jaak.jaak == bruteJaak.jaak)
                     flag = false;
             if (flag) {
                 cout << "Viga: lahendit " << bruteJaak.jaak << " ei leitud." << endl;
             }
         } return false;
     }
    if (tulemus.size() > tulemusBrute.size()) {
        for (auto jaak : tulemus) {
            bool flag = true;
            for (auto bruteJaak : tulemusBrute)
                if (jaak.jaak == bruteJaak.jaak)
                    flag = false;
            if (flag) {
                cout << "Viga: " << jaak.jaak << " ei ole lahend." << endl;
            }
        } return false;
    }
    for (auto i = 0; i < tulemus.size(); ++i) {
        if (tulemus[i].jaak != tulemusBrute[i].jaak) {
            cout << "Viga: " << tulemus[i].jaak << " ei ole lahend." << endl;
            return false;
        }
    }
    return true;
}