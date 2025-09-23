//
// Created by jakob on 24/04/2025.
//

#ifndef J22GITEOREEM_H
#define J22GITEOREEM_H
#include <vector>
#include <map>
#include <memory>

class J22k;
class Moodul;

class Polünoom {
public:
    char muutuja;
    int id;
    std::vector<int> kordajad;
    Polünoom(int i): muutuja{'x'} , id{i}
        {
            kordajad.push_back(0);
            kordajad.push_back(1);
        }
    Polünoom(std::vector<int>& vektor);
    Polünoom(std::vector<int>& vektor, int i);
    friend std::ostream& operator<<(std::ostream& os, const Polünoom& p);
    Polünoom võta_tuletis();
    std::vector<J22k> lahenda_kongruents(J22k& j22k);
    int v22rtus(int x) const;
};

class Moodul {
public:
    std::map<long long, long long> tegurid; // siia saab salvestada algteguritena
    Moodul() = default;
    Moodul(long long algarv, long long aste) { tegurid[algarv] = aste; }
    Moodul(const std::map<long long, long long>& tegurid_m);
    Moodul(long long i) { tegurid[i] = 1; } // suvalise arv (mitte tingimata algarvu) moodulisse salvestamiseks
    int algarv();
    int aste();
    friend std::ostream& operator<<(std::ostream& os, Moodul& p);
    int fii();
    int v22rtus();
    bool on_lihtne();
    void tegurda_ennast();
};


class J22k {
public:
    int j22k;
    Moodul moodul;
    J22k() = default;
    J22k(const int& j22k, const Moodul& moodul): j22k(j22k), moodul(moodul) {}
    J22k(const int& j22k, const long long& mod_algarv, const long long mod_aste): j22k(j22k)
    {
        Moodul moodul_m(mod_algarv, mod_aste);
        moodul = moodul_m;
    }
    int pöördjääk();
    void normeeri();
};

class V6rrand {
public:
    std::vector<std::pair<Polünoom, J22k>> v6rrandid; //unique_ptr, sest mdu ei erista samasuguseid võtmeid erinevate jääkidega
    V6rrand() = default;
    void lisa_v6rrand(const J22k& j22k, const Polünoom& polünoom)
    {
        v6rrandid.emplace_back(polünoom, j22k);
    }
    J22k lahenda_systeem();
    bool kontroll();
};

int lihtsusta(V6rrand& võrrand, std::vector<V6rrand>& tulemus);

#endif //J22GITEOREEM_H
