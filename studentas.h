#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>

class studentas {
private:
    std::string vardas;
    std::string pavarde;
    std::vector<int> paz;
    int exam = 0;
    double vid_rez = 0.0;
    double med_rez = 0.0;
  
public:
    studentas();

    studentas(const std::string& vardas, const std::string& pavarde, 
        const std::vector<int>& paz, 
        int exam, double vid_rez, double med_rez);
    
    studentas(const studentas& originalas);

    studentas(studentas&& originalas) noexcept;

    studentas& operator=(const studentas& originalas);
    studentas& operator=(studentas&& originalas) noexcept;

    ~studentas();

    const std::string& getVardas() const;
    const std::string& getPavarde() const;
    const std::vector<int>& getPaz() const;

    int getExam() const;
    double getVidRez() const;
    double getMedRez() const;

};

#endif // STUDENTAS_Hf
