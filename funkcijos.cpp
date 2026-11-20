#include "funkcijos.h"

#include <iostream>
#include <iomanip>
#include <numeric>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <utility>
#include <iterator>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::left;
using std::right;
using std::setw;

string pasirinktiFaila()
{
    int pasirinkimas;

    while (true)
    {
        cout << "\n -----Pasirinkite faila:-----\n";
        cout << "1 - studentai1000.txt\n";
        cout << "2 - studentai10000.txt\n";
        cout << "3 - studentai100000.txt\n";
        cout << "4 - studentai1000000.txt\n";
        cout << "5 - studentai10000000.txt\n";
        cout << "6 - Iveskite failo pavadinima paciam\n";
        cout << "0 - atsaukti\n";
        cout << "Pasirinkimas: ";
        cin >> pasirinkimas;
    
    
        if (cin.fail()) 
        {
           cin.clear();
           cin.ignore(10000, '\n');
           cout << "Neteisingas pasirinkimas. Iveskite skaiciu nuo 0 iki 6.\n";
           continue;
        }

        switch (pasirinkimas)
         {
            case 1:
                return "studentai1000.txt";
            case 2:
                return "studentai10000.txt";
            case 3:
                return "studentai100000.txt";
            case 4:
                return "studentai1000000.txt";
            case 5:
                return "studentai10000000.txt";
            case 6:
            {
                string failo_pavadinimas;
                cout << "Iveskite failo pavadinima: ";
                cin >> failo_pavadinimas;
                return failo_pavadinimas;
            }
            case 0:
                return "";
            default:
                cout << "Neteisingas pasirinkimas. Pasirinkite nuo 0 iki 5.\n";
         }
    }    
}
void printas(std::ofstream& failas, const studentas& A, int pasirinkimas, int w_vardas, int w_pavarde){
    failas <<"|"<<left<<setw(w_vardas)<<A.getVardas()<<"|"<<left<<setw(w_pavarde)<<A.getPavarde();
    failas <<std::fixed<<std::setprecision(2);
    if (pasirinkimas==1)
        failas<<"|"<<right<<setw(10)<<std::fixed<<std::setprecision(2)<<A.getVidRez();
    else if (pasirinkimas == 2)
        failas <<"|"<<right<<setw(10)<<std::fixed<<std::setprecision(2)<<A.getMedRez();
    else
         failas<<"|"<<right<<setw(10)<<A.getVidRez()<<"|"<<right<<setw(10)<<A.getMedRez();

    failas<<"|\n";
}
bool lygintiPagalVarda(const studentas& a, const studentas& b) {
    return a.getVardas() < b.getVardas();
}
bool lygintiPagalPavarde(const studentas& a, const studentas& b) {
    return a.getPavarde() < b.getPavarde();
}
bool lygintiPagalGalutiniBala(const studentas& a, const studentas& b, int pasirinkimas) {
     if (pasirinkimas == 1) {
        return a.getVidRez() < b.getVidRez();
    } else {
        return a.getMedRez() < b.getMedRez();
    }
}
void rikiuotiStudentus(std::vector<studentas>& grupe, int rusiavimas, int pasirinkimas)
{
    if (rusiavimas == 1)
    {
        std::sort(grupe.begin(), grupe.end(), lygintiPagalVarda);   
    }
    else if (rusiavimas == 2)
    {
        std::sort(grupe.begin(), grupe.end(), lygintiPagalPavarde);   
    }
    else if (rusiavimas == 3)
    {
        std::sort(grupe.begin(), grupe.end(),
        [pasirinkimas](const studentas &a, const studentas& b)
        {
            return lygintiPagalGalutiniBala(a, b, pasirinkimas);
        });
    }
}
void rikiuotiStudentus(std::list<studentas>& grupe, int rusiavimas, int pasirinkimas)
{
    if (rusiavimas == 1)
    {
        grupe.sort(lygintiPagalVarda);
    }
    else if (rusiavimas == 2)
    {
        grupe.sort(lygintiPagalPavarde);
    }
    else if (rusiavimas == 3)
    {
        grupe.sort(
            [pasirinkimas] (const studentas &a, const studentas& b)
        {
            return lygintiPagalGalutiniBala(a, b, pasirinkimas);
        });
    }
}
void skirstytiStudentus2(std::vector<studentas>& grupe, std::vector<studentas> & vargsiukai, int pasirinkimas) 
{
    vargsiukai.clear();

    size_t i = 0;

    while (i < grupe.size())
    {
        double galutinis = (pasirinkimas == 1)
            ? grupe[i].getVidRez() 
            : grupe[i].getMedRez();

        if (galutinis < 5.0)
        {
            vargsiukai.push_back(std::move(grupe[i]));

            if (i != grupe.size() - 1) 
            {
                grupe[i] = std::move(grupe.back());
            }
            grupe.pop_back();
        }
        else
        {
            i++;
        }       
    }
}
void skirstytiStudentus2(std::list<studentas>& grupe, std::list<studentas> & vargsiukai, int pasirinkimas) 
{
    vargsiukai.clear();

    for (auto it = grupe.begin(); it != grupe.end(); ) 
    {
        double galutinis = (pasirinkimas == 1)
            ? it->getVidRez() 
            : it->getMedRez();

        if (galutinis < 5.0) 
        {
            vargsiukai.push_back(std::move(*it));
            it = grupe.erase(it);
        } 
        else 
        {
            ++it;
        }
    }
}
void skirstytiStudentus3(std::vector<studentas>& grupe, std::vector<studentas>& vargsiukai, int pasirinkimas) 
{
    vargsiukai.clear();

    auto limitas = std::partition(
        grupe.begin(), 
        grupe.end(), 
        [pasirinkimas](const studentas& s) {
            return (pasirinkimas == 1 ? s.getVidRez() : s.getMedRez()) >= 5.0;
        }
    
    );

   vargsiukai.insert(vargsiukai.end(), 
   std::make_move_iterator(limitas), 
   std::make_move_iterator(grupe.end())
    );
   
   grupe.erase(limitas, grupe.end());
}
void skirstytiStudentus3(std::list<studentas>& grupe, std::list<studentas>& vargsiukai, int pasirinkimas) 
{
    vargsiukai.clear();

    auto limitas = std::partition(
        grupe.begin(), 
        grupe.end(), 
        [pasirinkimas](const studentas& s) {
            return (pasirinkimas == 1 ? s.getVidRez() : s.getMedRez()) >= 5.0;
        }
    
    );

   vargsiukai.insert(vargsiukai.end(), 
   std::make_move_iterator(limitas), 
   std::make_move_iterator(grupe.end())
    );
   
   grupe.erase(limitas, grupe.end());
}
