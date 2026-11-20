#include "studentas.h"
#include <utility>
#include <sstream>
#include <algorithm>
#include <numeric>

studentas::studentas() {
}

studentas::studentas(const std::string& vardas, 
                     const std::string& pavarde, 
                     const std::vector<int>& paz, 
                     int exam, double vid_rez, double med_rez)
    : vardas(vardas), 
      pavarde(pavarde), 
      paz(paz), 
      exam(exam), 
      vid_rez(vid_rez), 
      med_rez(med_rez) {
}
studentas::studentas(const studentas& originalas)
    : vardas(originalas.vardas), 
      pavarde(originalas.pavarde), 
      paz(originalas.paz), 
      exam(originalas.exam), 
      vid_rez(originalas.vid_rez), 
      med_rez(originalas.med_rez) {
}
studentas::studentas(studentas&& originalas) noexcept
    : vardas(std::move(originalas.vardas)), 
      pavarde(std::move(originalas.pavarde)), 
      paz(std::move(originalas.paz)), 
      exam(originalas.exam), 
      vid_rez(originalas.vid_rez), 
      med_rez(originalas.med_rez) {
}
studentas& studentas::operator=(const studentas& originalas) {
    if (this != &originalas) {
        vardas = originalas.vardas;
        pavarde = originalas.pavarde;
        paz = originalas.paz;
        exam = originalas.exam;
        vid_rez = originalas.vid_rez;
        med_rez = originalas.med_rez;
    }
    return *this;
}
studentas& studentas::operator=(studentas&& originalas) noexcept {
    if (this != &originalas) {
        vardas = std::move(originalas.vardas);
        pavarde = std::move(originalas.pavarde);
        paz = std::move(originalas.paz);
        exam = originalas.exam;
        vid_rez = originalas.vid_rez;
        med_rez = originalas.med_rez;
    }
    return *this;
}
studentas::~studentas() {
}
const std::string& studentas::getVardas() const {
    return vardas;
}
const std::string& studentas::getPavarde() const {
    return pavarde;
}
const std::vector<int>& studentas::getPaz() const {
    return paz;
}
int studentas::getExam() const {
    return exam;
}
double studentas::getVidRez() const {
    return vid_rez;
}
double studentas::getMedRez() const {
    return med_rez;
}   
bool studentas::nuskaityti(std::istream& s) {
    if (!(s >> vardas >> pavarde)) {
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
    exam = rezultatai.back();
    rezultatai.pop_back();
    paz = std::move(rezultatai);

    return true;
}
void studentas::skaiciuoti() {
    if (paz.empty()) {
        vid_rez = 0.6 * exam;
        med_rez = 0.6 * exam;
        return;
    }
    double suma = std::accumulate(paz.begin(), paz.end(), 0.0);
    double vidurkis = suma / paz.size();

    std::vector<int> surikiuoti_paz = paz;
    std::sort(surikiuoti_paz.begin(), surikiuoti_paz.end());

    int dydis = surikiuoti_paz.size();
    double mediana;
    
    if (dydis % 2 == 0) {
        mediana = (surikiuoti_paz[dydis / 2 - 1] + surikiuoti_paz[dydis / 2]) / 2.0;
    } else {
        mediana = surikiuoti_paz[dydis / 2];
    }

    vid_rez = 0.4 * vidurkis + 0.6 * exam;
    med_rez = 0.4 * mediana + 0.6 * exam;
}