//
// Created by l22nj on 9/27/25.
//

#include "tester.h"

using namespace std;

vector<Jaak> testiVorrand(Vorrandisusteem& vs) {
    vector<Jaak> tulemused;
    Moodul moodul{vs.leiaMooduliteVahimUhiskordne()};
    for (auto i = 0; i < moodul.vaartus(); ++i) {
        bool flag = true;
        for (auto& vorrand : vs.vorrandid) {
            Polunoom polunoom = vorrand.first;
            Jaak jaak = vorrand.second;
            Jaak polunoomiJaak{polunoom.vaartus(i), jaak.moodul};
            jaak.normeeri();
            polunoomiJaak.normeeri();
            if (polunoomiJaak.jaak != jaak.jaak) {
                flag = false;
                break;
            }
        } if (flag) {
            tulemused.emplace_back(i, moodul);
        }
    }
    return tulemused;
}