#include "studentas.h"
#include <utility>
#include <sstream>
#include <algorithm>
#include <numeric>

studentas::studentas(std::istream & s) : studentas() {
    if (nuskaityti(s)) {
        skaiciuoti();
    } else {
        throw std::runtime_error("Klaida nuskaityme.");
    }
}

studentas::~studentas() {
}

const std::string& studentas::getVardas() const {
    return vardas_;
}
const std::string& studentas::getPavarde() const {
    return pavarde_;
}
const std::vector<int>& studentas::getPaz() const {
    return paz_;
}
int studentas::getExam() const {
    return exam_;
}
double studentas::getVidRez() const {
    return vid_rez_;
}
double studentas::getMedRez() const {
    return med_rez_;
}   
bool studentas::nuskaityti(std::istream& s) {
    if (!(s >> vardas_ >> pavarde_)) {
        return false;
    }
    std::vector<int> rezultatai;

    int x;
    while (s >> x) {
        if (x < 1 || x > 10) {
            return false;
        }
       rezultatai.push_back(x);
    }
    if (!s.eof() || rezultatai.empty()) {
        return false;
    }
    exam_ = rezultatai.back();
    rezultatai.pop_back();
    paz_ = std::move(rezultatai);

    return true;
}
void studentas::skaiciuoti() {
    if (paz_.empty()) {
        vid_rez_ = 0.6 * exam_;
        med_rez_ = 0.6 * exam_;
        return;
    }
    double suma = std::accumulate(paz_.begin(), paz_.end(), 0.0);
    double vidurkis = suma / paz_.size();

    std::vector<int> surikiuoti_paz = paz_;
    std::sort(surikiuoti_paz.begin(), surikiuoti_paz.end());

    int dydis = surikiuoti_paz.size();
    double mediana;
    
    if (dydis % 2 == 0) {
        mediana = (surikiuoti_paz[dydis / 2 - 1] + surikiuoti_paz[dydis / 2]) / 2.0;
    } else {
        mediana = surikiuoti_paz[dydis / 2];
    }

    vid_rez_ = 0.4 * vidurkis + 0.6 * exam_;
    med_rez_ = 0.4 * mediana + 0.6 * exam_;
}