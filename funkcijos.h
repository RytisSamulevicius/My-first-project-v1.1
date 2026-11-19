#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <utility>
#include <string>
#include <vector>
#include <list>
#include <iomanip>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::left;
using std::right;
using std::setw;
using std::fixed;
using std::setprecision;

#include "studentas.h"

std::string pasirinktiFaila();
void printas(std::ofstream& failas, const studentas& A, int pasirinkimas, int w_vardas, int w_pavarde);
void skaiciavimas(studentas& B);
bool lygintiPagalVarda(const studentas& a, const studentas& b);
bool lygintiPagalPavarde(const studentas& a, const studentas& b);
bool lygintiPagalGalutiniBala(const studentas& a, const studentas& b, int pasirinkimas);
void rikiuotiStudentus(std::vector<studentas>&grupe, int rusiavimas, int pasirinkimas);
void rikiuotiStudentus(std::list<studentas>&grupe, int rusiavimas, int pasirinkimas);
void skirstytiStudentus2(std::vector<studentas>& grupe, std::vector<studentas> & vargsiukai, int pasirinkimas);
void skirstytiStudentus2(std::list<studentas>& grupe, std::list<studentas> & vargsiukai, int pasirinkimas);
void skirstytiStudentus3(std::vector<studentas>& grupe, std::vector<studentas>& vargsiukai, int pasirinkimas);
void skirstytiStudentus3(std::list<studentas>& grupe, std::list<studentas>& vargsiukai, int pasirinkimas);

template <typename T>
bool NuskaitytiFaila(const std::string & failo_pavadinimas, T& grupe)
{
    std::ifstream failas (failo_pavadinimas);
    if (!failas.is_open()){
        std::cout << "Nepavyko atidaryti failo " << failo_pavadinimas << "\n";
        return false;
    }
    std::stringstream buferis;
    buferis << failas.rdbuf();
    failas.close();

    grupe.clear();
    std::string eilute;
    std::getline(buferis, eilute);

    while(std::getline(buferis, eilute))
    {
        std::stringstream s(eilute);
        studentas S;
        
        if(!S.nuskaityti(s)) {
            std::cout << "Klaida nuskaityme: " << eilute << "\n";
            continue;
        }
        S.skaiciuoti();

        grupe.push_back(std::move(S));
        
    }
    return true;

}
template <typename T>
void IrasytiIFaila(const string & failo_pavadinimas, const T& studentai, int pasirinkimas)
{
    std::ofstream failas(failo_pavadinimas);
    if (!failas.is_open()) {
        cout << "Nepavyko sukurti failo: " << failo_pavadinimas << "\n";
        return; 
    }

    std::ostringstream buferis;
    buferis <<left<<setw(20)<<"Vardas"<<setw(20)<<"Pavarde";
    if (pasirinkimas == 1)
        buferis <<right<<setw(15)<<"Gal.(vid)";
    else 
        buferis <<right<<setw(15)<<"Gal.(med)";
    buferis << "\n";

    buferis << std::fixed << std::setprecision(2);
    for (const studentas& s : studentai) 
    {
        buferis <<left<<setw(20)<<s.getVardas()<<setw(20)<<s.getPavarde();
        if (pasirinkimas == 1)
            buferis <<right<<setw(15)<<s.getVid_rez();
        else 
            buferis <<right<<setw(15)<<s.getMed_rez();
        buferis << "\n";
    }
    failas << buferis.str();
    if (!failas){
        cout << "Klaida irasyme i faila: " << failo_pavadinimas << "\n";
    }
    
}
template <typename T>
void skirstytiStudentus (const T& grupe, T& vargsiukai, T& kietiakai, int pasirinkimas)
{ 
    vargsiukai.clear();
    kietiakai.clear();

    for (const studentas& s : grupe) 
    {
        double galutinis;
        if (pasirinkimas == 1)
            galutinis = s.getVid_rez();
        else
            galutinis = s.getMed_rez();

        if (galutinis < 5.0) 
            vargsiukai.push_back(s);
        else 
            kietiakai.push_back(s);
    }
}
#endif
