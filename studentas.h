#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>
#include <iosfwd>

class studentas {
private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<int> paz_;
    int exam_ = 0;
    double vid_rez_ = 0.0;
    double med_rez_ = 0.0;
  
public:

    studentas(): exam_(0), vid_rez_(0.0), med_rez_(0.0) {}
    explicit studentas(std::istream& s);

    ~studentas();

    const std::string& getVardas() const;
    const std::string& getPavarde() const;
    const std::vector<int>& getPaz() const;

    int getExam() const;
    double getVidRez() const;
    double getMedRez() const;

    bool nuskaityti(std::istream& s);
    void skaiciuoti();

};

#endif // STUDENTAS_H
