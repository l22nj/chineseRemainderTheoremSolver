//
// Created by jakob on 24/04/2025.
//

#include <iostream>
#include <cmath>
#include <ranges>
#include "tegurdamine.h"
#include "j22giteoreem.h"
#include <algorithm>

using namespace std;

ostream& operator<<(ostream& os, const Polünoom& p) // kuvab polünoomi!
{
    for (int i = p.kordajad.size()-1; i >= 0; i--)
    {
        if (p.kordajad[i] != 0)
        {
            if (p.kordajad[i] >= 0 and i < p.kordajad.size()-1) os << " + "; // erinevad tingimused et oleks ilusam
            else if (p.kordajad[i] < 0) os << " - ";
            if (p.kordajad[i] != 1 or i == 0) os << abs(p.kordajad[i]);
            if (i > 0) os << p.muutuja;
            if (i > 1) os << '^' << i;
        }
    }
    return os;
}

ostream& operator<<(ostream& os, Moodul& p) // kujutab moodulit
{
    os << p.v22rtus();
    return os;
}

Polünoom::Polünoom(vector<int>& vektor) //vektoriga konstruktor
{
    muutuja = 'x';
    id = 0;
    for (auto el : vektor) kordajad.push_back(el);
    vektor.clear();
}

Polünoom::Polünoom(vector<int>& vektor, int i) //vahepeal arvasin, et id vaja, aga lõpuks siiski ei läinud
{
    muutuja = 'x';
    id = i;
    for (auto el : vektor) kordajad.push_back(el);
    vektor.clear();
}

Polünoom Polünoom::võta_tuletis()
{
    Polünoom p = *this;
    p.kordajad.erase(p.kordajad.begin());
    auto it = p.kordajad.begin();
    while (it != p.kordajad.end())
    {
        *it *= it - p.kordajad.begin() + 1;
        ++it;
    }
    return p;
}

int Polünoom::v22rtus(int x) const //arvutab kokku mis vaja
{
    int summa{0};
    for (size_t i{0}; i < kordajad.size(); i++) summa += kordajad[i] * pow(x, i);
    return summa;
}

vector<J22k> Polünoom::lahenda_kongruents(J22k& j22k) // leiab sobivad lahendid arvuteooria kursuses õpitu põhjal
{
    Polünoom p = *this;
    Moodul moodul = j22k.moodul;
    int jääk = j22k.j22k;
    p.kordajad[0] -= jääk;
    Polünoom tuletis = p.võta_tuletis();

    vector<J22k> j22gid;
        vector<int> vahev22rtused;
            vector<vector<int>> vahev22rtused_v;

    int vahemoodul;

    if (j22k.moodul.on_lihtne() == false) // muidu see tehnika ei tööta
    {
        cout << "error: Polünoom::lahenda_kongruents pole lihtmoodul";
        return j22gid;
    }
    for (int i{0}; i < moodul.algarv(); i++)
        if (p.v22rtus(i) % moodul.algarv() == 0)
            vahev22rtused.push_back(i);
    vahev22rtused_v.push_back(vahev22rtused);

    for (int i{1}; i < moodul.aste(); i++)
    {
        vahev22rtused.clear();
        vahemoodul = pow(moodul.algarv(), i);

        for (auto x : vahev22rtused_v[i-1])
            for (int y{0}; y < moodul.algarv(); y++)
                if ((tuletis.v22rtus(x)*y + p.v22rtus(x) / vahemoodul) % moodul.algarv() == 0)
                    vahev22rtused.push_back(x + vahemoodul * y);
        vahev22rtused_v.push_back(vahev22rtused);
    }
    for (auto el : vahev22rtused_v.back()) j22gid.emplace_back(el, moodul);
    return j22gid;
}

Moodul::Moodul(const map<long long, long long>& tegurid_m)
{
    for (auto paar : tegurid_m) tegurid[paar.first] = paar.second;
}

int Moodul::algarv() //algarv() ja aste() ainult juhuks, kui moodul on mingi ühe algarvu aste
{
    if (on_lihtne()) return tegurid.begin()->first;
    std::cout << "error: Moodul::algarv() : pole lihtmoodul" << std::endl;
    return 0;
}

int Moodul::aste()
{
    if (on_lihtne()) return tegurid.begin()->second;
    std::cout << "error: Moodul::aste() : pole lihtmoodul" << std::endl;
    return 0;
}

int Moodul::fii() // tagastab täisarvuringis mingi mooduli järgi pööratavate elementide arvu
{                 // (leiab hulga {a | a < n, SÜT(a, n)=1} võimsuse, kus a on naturaalarv)
    int korrutis{1};
    for (auto paar : tegurid)
    {
        korrutis *= pow(paar.first, paar.second - 1);
        korrutis *= (paar.first - 1);
    }
    return korrutis;
}

int Moodul::v22rtus() //tagastab mooduli täisarvuna
{
    int korrutis{1};
    for (auto paar : tegurid)
        korrutis *= pow(paar.first, paar.second);
    return korrutis;
}

bool Moodul::on_lihtne() // ehk kas avaldub kujul p^n, kus p on algarv ja n on naturaalarv
{
    if (tegurid.size() == 1) return true;
    return false;
}

void Moodul::tegurda_ennast() // viib mooduli algarvulisele kujule salvestatuna tegurid vektorisse
{
    bool flag{true};
    for (auto algarv: tegurid | views::keys) // kontrollib ega juba pole sobival kujul
        if (kasAlgarv(algarv) == false)
            flag = false;
    if (flag) return;
    long long arv = v22rtus();
    tegurid.clear();
    tegurda_arv(arv, tegurid);
}

int J22k::pöördjääk()  // leiab arvu a, et j22k*a kongr 1 mod moodul.v22rtus() (ÜHESELT LAHENDUV)
{
    if (eukleidese_algoritm(j22k, moodul.v22rtus()) != 1)
    {
        cout << "viga : J22k::pöördjääk() , jäägi ja mooduli SÜT != 1" << endl;
        return 0;
    }
    int tulemus{1};
    int fii = moodul.fii();
    for (size_t i{0}; i < fii-1; ++i)
    {
        tulemus *= j22k;
        tulemus = tulemus % moodul.v22rtus();
    }
    return tulemus;
}

void J22k::normeeri() // teeb ilusamaks
{
    j22k = j22k % moodul.v22rtus();
    if (j22k < 0) j22k = moodul.v22rtus() + j22k;
}

J22k V6rrand::lahenda_systeem() //lahendab võrrandisüsteemi hiina jäägiteoreemiga, kus kõik polünoomid kujul 'x'
{
    if (kontroll() != true) // kas ühisteguriteta moodulid (hiina jäägiteoreemi tingimus)
    {
        cout << "Moodulid pole ühisteguriteta." << endl;
        return J22k{};
    }
    Moodul korrutis;

    for (auto jääk : v6rrandid | views::values)
        korrutis.tegurid[jääk.moodul.algarv()] = jääk.moodul.aste();

    J22k vahekorrutis{}, summa{0, korrutis};
    for (auto jääk : v6rrandid | views::values)
    {
        vahekorrutis.j22k = korrutis.v22rtus();
        vahekorrutis.moodul = jääk.moodul;
        vahekorrutis.j22k /= jääk.moodul.v22rtus();
        vahekorrutis.j22k *= vahekorrutis.pöördjääk();
        vahekorrutis.j22k *= jääk.j22k;
        summa.j22k += vahekorrutis.j22k;
    }
    summa.normeeri();
    return summa;
}

bool V6rrand::kontroll() //sisuliselt kontrollib, kas võrrandis kõik moodulid ühistegurita
{
    vector<unsigned int> kontrollvektor;
    for (auto jääk : v6rrandid | views::values)
    {
        for (auto kontrollarv : kontrollvektor)
            if (jääk.moodul.algarv() == kontrollarv) return false;
        kontrollvektor.push_back(jääk.moodul.algarv());
    }
    return true;
}

int lihtsusta(V6rrand& võrrand, vector<V6rrand>& tulemus) // tagastab kõik algsest võrranditest tuletatud võrrandisüsteemid
{                                                         // kus polünoomiks 'x'
    Polünoom x{0};
    V6rrand vahevõrrand; //siia tuleb esialgne võrrand algtegurites
    map<long long, long long> tegurdatud_arv;
    vector<pair<Polünoom, J22k>> vahetulemus;
    vector<J22k> vahejäägid;
    vector<vector<J22k>> vahejäägid_v;
    bool flag{false};
    int id{0};
    for (auto paar : võrrand.v6rrandid) // viib võrrandisüsteemi kujule, kus kõik moodulid kujul p^n
    {
        paar.second.moodul.tegurda_ennast();
        for (auto el : paar.second.moodul.tegurid)
            vahevõrrand.lisa_v6rrand(J22k(paar.second.j22k, Moodul(el.first, el.second)), paar.first);
        tegurdatud_arv.clear();
    }
    for (auto el : vahevõrrand.v6rrandid) // talletab kõikvõimalikud (sobivad) lahendid iga polünoomiga kongruentsi jaoks
    {
        for (auto el2: el.first.lahenda_kongruents(el.second))
        {
            // cout << el2.moodul << endl;
            for (auto vahej22gid = vahejäägid_v.begin(); vahej22gid < vahejäägid_v.end(); ++vahej22gid)
                for (auto el3{vahej22gid->begin()}; el3 < vahej22gid->end(); el3++)
                {
                    if (el2.moodul.algarv() == el3->moodul.algarv() and
                        el2.moodul.aste() > el3->moodul.aste() and
                        el2.j22k != el3->j22k) {flag = true; break;}
                    if (el2.moodul.algarv() == el3->moodul.algarv()) vahej22gid->erase(el3);
                }
            if (flag) break;
            vahejäägid.push_back(el2);
        }
        if (vahejäägid.empty())
        {
            cout << "error: V6rrand::lihtsusta(): sisestatud süsteem pole lahenduv.";
            return 0;
        }
        vahejäägid_v.push_back(vahejäägid);
        vahejäägid.clear();
    }

    int korrutis{1}, koht;
    int suurus = vahejäägid_v.size();
    int fix_koht[suurus]{};
    for (auto el : vahejäägid_v) korrutis *= el.size();

    for (unsigned int i{0}; i < korrutis; ++i) // paneb lahendid kokku kõikvõimalikeks võrrandisüsteemideks
    {
        for (int aa{0}; aa < suurus; ++aa)
        {
            if (i == 0) break;
            koht = suurus - aa - 1;
            if (fix_koht[koht] < vahejäägid_v[koht].size()-1)
            {
                fix_koht[koht] += 1;
                break;
            }
            fix_koht[koht] = 0;
        }

        for (unsigned int j{0}; j < suurus; ++j) vahetulemus.emplace_back(x, vahejäägid_v[j][fix_koht[j]]);
        x.id += 1;

        vahevõrrand.v6rrandid.clear();
        for (auto el : vahetulemus) vahevõrrand.lisa_v6rrand(el.second, el.first);
        tulemus.push_back(vahevõrrand);
        vahetulemus.clear();
    }
    if (tulemus.empty())
    {
        cout << "error: V6rrand::lihtsusta(): sisestatud süsteem pole lahenduv.";
        return 0;
    }
    return 1;
}
