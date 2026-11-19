#include "studentas.h"
#include <utility>

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
studentas::studentas(const studentas&& originalas) noexcept
    : vardas(std::move(originalas.vardas)), 
      pavarde(std::move(originalas.pavarde)), 
      paz(std::move(originalas.paz)), 
      exam(originalas.exam), 
      vid_rez(originalas.vid_rez), 
      med_rez(originalas.med_rez) {
}
studentas::~studentas() {
}