//
// Created by jakob on 24/04/2025.
//

#ifndef J22GITEOREEM_H
#define J22GITEOREEM_H
#include <vector>
#include <map>
#include <memory>

class Jaak;
class Moodul;

class Polunoom {
public:
    char muutuja;
    std::vector<int> kordajad;
    Polunoom(): muutuja{'x'}
        {
            kordajad.push_back(0);
            kordajad.push_back(1);
        }
    Polunoom(std::vector<int>& v);
    friend std::ostream& operator<<(std::ostream& os, const Polunoom& p);
    Polunoom votaTuletis();
    std::vector<Jaak> lahendaKongruents(Jaak& j);

    long long vaartus(int x) const;
};

class Moodul {
public:
    std::map<long long, long long> tegurid;
    Moodul() = default;
    Moodul(long long algarv, long long aste) { tegurid[algarv] = aste; }
    Moodul(const std::map<long long, long long>& tegurid_m);
    Moodul(long long i) {
        tegurid[i] = 1;
    } // Suvalise arvu (mitte tingimata algarvu) moodulina salvestamiseks
    int algarv();
    int aste();
    friend std::ostream& operator<<(std::ostream& os, Moodul& m);
    int leiaFii();
    int vaartus();
    bool onLihtne();
    void tegurdaEnnast();
};


class Jaak {
public:
    int jaak;
    Moodul moodul;
    Jaak() = default;
    Jaak(const int& j22k, const Moodul& moodul): jaak(j22k), moodul(moodul) {}
    Jaak(const int& j22k, const long long& mod_algarv, const long long mod_aste): jaak(j22k)
    {
        Moodul moodul_m(mod_algarv, mod_aste);
        moodul = moodul_m;
    }
    int leiaPoordjaak();
    void normeeri();
};

class Vorrandisusteem {
public:
    std::vector<std::pair<Polunoom, Jaak>> vorrandid;
    Vorrandisusteem() = default;
    void lisaVorrand(const Jaak& j22k, const Polunoom& polünoom)
    {
        vorrandid.emplace_back(polünoom, j22k);
    }
    Jaak lahendaSusteem();
    bool kontroll();
    void tegurdaMoodulid();
    int lihtsusta(Vorrandisusteem& vorrand, std::vector<Vorrandisusteem>& tulemus);
};



#endif //J22GITEOREEM_H
