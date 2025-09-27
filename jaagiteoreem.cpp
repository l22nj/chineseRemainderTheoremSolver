//
// Created by jakob on 24/04/2025.
//

#include <iostream>
#include <cmath>
#include <ranges>
#include "tegurdamine.h"
#include "jaagiteoreem.h"
#include <algorithm>

using namespace std;

/**
 * Tagastab sisendiks oleva polünoomi ostream objektis sõnena
 * @param os ostream objekt
 * @param p Polünoom
 * @return Kuvatav polünoom ostream objektina
 */
ostream& operator<<(ostream& os, const Polunoom& p) {
    for (int i = p.kordajad.size()-1; i >= 0; i--) {
        if (p.kordajad[i] != 0) {
            // if-ide sees erinevad tingimused, et lõpptulemus oleks ilusam
            if (p.kordajad[i] >= 0 and i < p.kordajad.size()-1)
                os << " + ";
            else if (p.kordajad[i] < 0)
                os << " - ";
            if (p.kordajad[i] != 1 or i == 0)
                os << abs(p.kordajad[i]);
            if (i > 0)
                os << p.muutuja;
            if (i > 1)
                os << '^' << i;
        }
    } return os;
}

/**
 * Tagastab sisendiks oleva mooduli väärtuse ostream objektina
 * @param os ostream objekt
 * @param m Moodul
 * @return Kuvatav moodul oma väärtusena ostream objektina
 */
ostream& operator<<(ostream& os, Moodul& m) {
    os << m.vaartus();
    return os;
}

/**
 * Klassi Polunoom konstruktor vektori abil
 * @param v Vektor
 */
Polunoom::Polunoom(vector<int>& v) {
    muutuja = 'x';
    for (auto el : v)
        kordajad.push_back(el);
    v.clear();
}

/**
 * Võtab iseendast tuletise
 * @return Iseenda tuletis polünoomina
 */
Polunoom Polunoom::votaTuletis() {
    Polunoom tuletis = *this;
    tuletis.kordajad.erase(tuletis.kordajad.begin());
    auto it = tuletis.kordajad.begin();
    while (it != tuletis.kordajad.end()) {
        *it *= it - tuletis.kordajad.begin() + 1;
        ++it;
    } return tuletis;
}

/**
 * Tagastab polünoomi väärtuse etteantud kohal
 * @param x Muutuja väärtustus
 * @return Polünoomi väärtus antud arvu 'x' juures
 */
long long Polunoom::vaartus(int x) const {
    long long vaartus = 0;
    for (size_t i{0}; i < kordajad.size(); i++)
        vaartus += kordajad[i] * pow(x, i);
    return vaartus;
}

/**
 * Lahendab kongruentsi mingi jäägi suhtes
 * Tartu Ülikooli Arvuteooria (1. osa) kursusematerjalide põhjal
 * @param j Jääk, mille suhtes kongruentsi lahendada
 * @return Vektor kõikvõimalikest jäägiklassi 'x' väärtustest
 */
vector<Jaak> Polunoom::lahendaKongruents(Jaak& j) {
    Polunoom p = *this;
    Moodul moodul = j.moodul;
    int jaakArv = j.jaak;
    p.kordajad[0] -= jaakArv;
    Polunoom tuletis = p.votaTuletis();
    vector<Jaak> jaagid;
    vector<int> vahevaartused;
    vector<vector<int>> vahevaartusteVektor;

    if (j.moodul.onLihtne() == false) {
        cout << "error: Polunoom::lahendaKongruents pole lihtmoodul";
        return jaagid;
    }
    for (int i{0}; i < moodul.algarv(); i++)
        if (p.vaartus(i) % moodul.algarv() == 0)
            vahevaartused.push_back(i);
    vahevaartusteVektor.push_back(vahevaartused);

    for (int i{1}; i < moodul.aste(); i++) {
        vahevaartused.clear();
        int vahemoodul = pow(moodul.algarv(), i);

        for (auto x : vahevaartusteVektor[i-1]) {
            for (int y{0}; y < moodul.algarv(); y++) {
                int vahetulemus = (tuletis.vaartus(x)*y + p.vaartus(x) / vahemoodul) % moodul.algarv();
                if (vahetulemus == 0) {
                    vahevaartused.push_back(x + vahemoodul * y);
                }
            }
        } vahevaartusteVektor.push_back(vahevaartused);
    }
    for (auto el : vahevaartusteVektor.back())
        jaagid.emplace_back(el, moodul);
    return jaagid;
}

/**
 * Klassi Moodul konstruktor mapi põhjal, kus võtmeteks algarvud ja väärtusteks nende astmed
 * @param tegurid_m Mingi täisarv teguriteks lahti võetuna
 */
Moodul::Moodul(const map<long long, long long>& tegurid_m) {
    for (auto paar : tegurid_m)
        tegurid[paar.first] = paar.second;
}

/**
 * Juhul, kui mooduli puhul on tegemist täisarvuga, mis avaldub kujul p^a, kus p on suvaline algarv ning a täisarv,
 * siis tagaastab p
 * @return 'p'
 */
int Moodul::algarv() {
    if (onLihtne())
        return tegurid.begin()->first;
    std::cout << "error: Moodul::algarv() : pole lihtmoodul" << std::endl;
    return 0;
}
/**
 * Juhul, kui mooduli puhul on tegemist täisarvuga, mis avaldub kujul p^a, kus p on suvaline algarv ning a täisarv,
 * siis tagaastab a
 * @return 'a'
 */
int Moodul::aste() {
    if (onLihtne())
        return tegurid.begin()->second;
    std::cout << "error: Moodul::aste() : pole lihtmoodul" << std::endl;
    return 0;
}

/**
 * Tagastab täisarvuringis mingi mooduli järgi pööratavate elementide arvu
 * @return Hulga {a | a < n, SÜT(a, n)=1, a on naturaalarv} võimsus
 */
int Moodul::leiaFii() {
    int korrutis{1};
    for (auto paar : tegurid) {
        korrutis *= pow(paar.first, paar.second - 1);
        korrutis *= (paar.first - 1);
    } return korrutis;
}

/**
 * Leiab mooduli väärtuse täisarvuna
 * @return Vektoris 'tegurid' olevate algarvude, võetuna vastavale astmele, summa
 */
int Moodul::vaartus() {
    int korrutis{1};
    for (auto paar : tegurid)
        korrutis *= pow(paar.first, paar.second);
    return korrutis;
}

/**
 * Teeb kindlaks, kas mooduli väärtus avaldub kujul p^n, kus p on algarv ja n on naturaalarv
 * @return Tõeväärtus
 */
bool Moodul::onLihtne() {
    if (tegurid.size() == 1)
        return true;
    return false;
}

/**
 * Viib mooduli algarvulisele kujule salvestatuna 'tegurid' vektorisse
 */
void Moodul::tegurdaEnnast() {
    bool flag{true};
    for (auto algarv: tegurid | views::keys) // kontrollib ega juba pole sobival kujul
        if (kasOnAlgarv(algarv) == false)
            flag = false;
    if (flag)
        return;
    long long arv = vaartus();
    tegurid.clear();
    tegurdaArv(arv, tegurid);
}

/**
 * Leiab endale oma mooduli suhtes pöördjäägi 'tulemus', st jaak * tulemus.jaak = 1
 * See on üheselt lahenduv!
 * @return Vastav pöördjääk
 */
int Jaak::leiaPoordjaak() {
    if (leiaSuurimUhistegur(jaak, moodul.vaartus()) != 1) {
        cout << "viga : Jaak::leiaPoordjaak() , jäägi ja mooduli SÜT != 1" << endl;
        return 0;
    }
    int tulemus{1};
    int fii = moodul.leiaFii();
    for (size_t i{0}; i < fii-1; ++i) {
        tulemus *= jaak;
        tulemus = tulemus % moodul.vaartus();
    } return tulemus;
}

/**
 * Viib isendivälja 'jaak'  mingile samasse jäägiklassi kuuluvale positiivsele, moodulist väiksemale kujule
 */
void Jaak::normeeri() {
    jaak = jaak % moodul.vaartus();
    if (jaak < 0)
        jaak = moodul.vaartus() + jaak;
}

/**
 * Lahendab Hiina jäägiteoreemi abil võrrandisüsteemi, kus kõik polünoomid on oma jäägi suhtes lihtsalt kujul 'x'
 * Kui lahend leidub, siis üheselt lahenduv!
 * @return Vastav jääk kindla mooduli suhtes
 */
Jaak Vorrandisusteem::lahendaSusteem() {
    // Kontrollib, kas moodulid on ilma ühiste teguriteta (hiina jäägiteoreemi tingimus)
    if (kontroll() != true) {
        cout << "Moodulid pole ühisteguriteta." << endl;
        return Jaak{};
    }
    // Leiab mooduli, mille suhtes lahenduseks olev jääk peab olema
    Moodul korrutis;
    for (auto jaak : vorrandid | views::values)
        korrutis.tegurid[jaak.moodul.algarv()] = jaak.moodul.aste();
    // Leiab Hiina jäägiteoreemi abil vastava jäägi
    Jaak vahekorrutis{};
    Jaak summa{0, korrutis};
    for (auto jaak : vorrandid | views::values) {
        vahekorrutis.jaak = korrutis.vaartus();
        vahekorrutis.moodul = jaak.moodul;
        vahekorrutis.jaak /= jaak.moodul.vaartus();
        vahekorrutis.jaak *= vahekorrutis.leiaPoordjaak();
        vahekorrutis.jaak *= jaak.jaak;
        summa.jaak += vahekorrutis.jaak;
    }
    summa.normeeri();
    return summa;
}

/**
 * Kontrollib, ega võrrandisüsteemis olevad moodulid ei ole ühest suurema ühisteguriga
 * @return Tõeväärtus
 */
bool Vorrandisusteem::kontroll() {
    vector<unsigned int> kontrollvektor;
    for (auto jaak : vorrandid | views::values) {
        for (auto kontrollarv : kontrollvektor)
            if (jaak.moodul.algarv() == kontrollarv)
                return false;
        kontrollvektor.push_back(jaak.moodul.algarv());
    } return true;
}

/**
 * Viib võrrandi samaväärsele kujule, kus kõik moodulid on kujul p^n, kus p on algarv
 */
void Vorrandisusteem::tegurdaMoodulid() {
    vector<pair<Polunoom, Jaak>> uuedVorrandid;
    map<long long, long long> tegurdatudArv;
    for (auto paar : vorrandid) {
        paar.second.moodul.tegurdaEnnast();
        for (auto tegur : paar.second.moodul.tegurid)
            uuedVorrandid.emplace_back(
                paar.first, Jaak(paar.second.jaak, Moodul(tegur.first, tegur.second))
                );
        tegurdatudArv.clear();
    } vorrandid.clear();
    for (auto paar : uuedVorrandid) {
        vorrandid.push_back(paar);
        cout << paar.first << " + " << paar.second.jaak << " + " << paar.second.moodul;
    }
}

/**
 * Leiab võrrandi iga polünoomi lahendid
 * @return Vektor, mille igaks elemendiks on vektor ühe võrrandis oleva polünoomi kõikvõimalike lahenditega
 * jäägi suhtes, millega koos ta on võrrandisse salvestatud
 */
vector<vector<Jaak>> Vorrandisusteem::leiaPolunoomideLahendid() {
    vector<Jaak> vahejaagid; // kus polünoomiks 'x'
    vector<vector<Jaak>> vahejaagiVektoriteVektor;
    bool flag{false};

    for (auto vorrand : vorrandid) {
        for (auto jaak: vorrand.first.lahendaKongruents(vorrand.second)) {
            for (auto vahejaagiVektor : vahejaagiVektoriteVektor)
                for (auto it = vahejaagiVektor.begin(); it < vahejaagiVektor.end(); it++) {
                    if (jaak.moodul.algarv() == it->moodul.algarv() and
                            jaak.moodul.aste() > it->moodul.aste() and
                            jaak.jaak != it->jaak) {
                        flag = true;
                        break;
                            }
                    if (jaak.moodul.algarv() == it->moodul.algarv())
                        vahejaagiVektor.erase(it);
                }
            if (flag)
                break;
            vahejaagid.push_back(jaak);
        }
        vahejaagiVektoriteVektor.push_back(vahejaagid);
        vahejaagid.clear();
    } return vahejaagiVektoriteVektor;
}

/**
 * Leiab võrrandite mooduli väärtuste vähima ühiskordse
 * @return VÜK
 */
int Vorrandisusteem::leiaMooduliteVahimUhiskordne() {
    int mooduliteVahimUhiskordne = 1;
    for (auto paar : vorrandid) {
        mooduliteVahimUhiskordne /=
            leiaSuurimUhistegur(mooduliteVahimUhiskordne, paar.second.moodul.vaartus());
        mooduliteVahimUhiskordne *= paar.second.moodul.vaartus();
    }
    return mooduliteVahimUhiskordne;
}
/**
 * Leiab kõik sisendiks antud võrrandisüsteemist lahenduvad võrrandisüsteemid, kus polünoomid on kujul 'x'
 * @param vorrand Lahendatav võrrandisüsteem
 * @param tulemus Vektor võrrandisüsteemidest, kuhu salvestab kõik sobivad süsteemid
 * @return 1, kui 'tulemus' pole tühi vektor, 0 muidu
 */
int Vorrandisusteem::lihtsusta(vector<Vorrandisusteem>& tulemus) {
    Polunoom x{};
    map<long long, long long> tegurdatudArv;
    vector<pair<Polunoom, Jaak>> vahetulemus;
    vector<Jaak> vahejaagid; // kus polünoomiks 'x;

    // Viib võrrandisüsteemi kujule, kus kõik moodulid kujul p^n
    tegurdaMoodulid();

    // Talletab kõikvõimalikud (sobivad) lahendid iga polünoomiga kongruentsi jaoks
    vector<vector<Jaak>> vahejaagiVektoriteVektor = leiaPolunoomideLahendid();
    if (vahejaagiVektoriteVektor.empty())
        return 0;

    int korrutis = 1;
    for (auto el : vahejaagiVektoriteVektor)
        korrutis *= el.size();
    int suurus = vahejaagiVektoriteVektor.size();
    vector<int> indeksid;
    for (int i = 0; i < suurus; i++)
        indeksid.push_back(0);

    // Paneb eraldi polünomiaalsete kongruentside lahendid kokku kõikvõimalikeks lahenduvateks võrrandisüsteemideks
    for (unsigned int i{0}; i < korrutis; ++i) {
        // Tegeleb indeksitega kombinatoorika nimel
        for (int j{0}; j < suurus; ++j) {
            if (i == 0)
                break;
            int indeks = suurus - j - 1;
            if (indeksid[indeks] < vahejaagiVektoriteVektor[indeks].size()-1) {
                indeksid[indeks] += 1;
                break;
            } indeksid[indeks] = 0;
        }
        // Kasutab indekseid kombinatsioonide leidmiseks
        Vorrandisusteem vahevorrand;
        for (unsigned int j{0}; j < suurus; ++j)
            vahetulemus.emplace_back(x, vahejaagiVektoriteVektor[j][indeksid[j]]);
        vahevorrand.vorrandid.clear();
        for (auto el : vahetulemus)
            vahevorrand.lisaVorrand(el.second, el.first);
        tulemus.push_back(vahevorrand);
        vahetulemus.clear();
    }
    if (tulemus.empty()) {
        cout << "Sisestatud võrrandisüsteem pole lahenduv.";
        return 0;
    } return 1;
}

/**
 * Kuvab võrrandisüsteemi konsoolis
 * @param os ostream objekt
 * @param vs Vorrandisusteem objekt
 * @return ostream objekt, kuhu on salvestatud vastav sõne
 */
ostream& operator<<(ostream& os, Vorrandisusteem& vs) {
    for (size_t i{0}; i < vs.vorrandid.size(); ++i) {
        os << vs.vorrandid[i].first << " kongruentne arvuga " << vs.vorrandid[i].second.jaak <<
            " mooduli " << vs.vorrandid[i].second.moodul << " järgi." << endl;
    } return os;
}
