#include "../h/Hospital.h"

void Hospital::PrintInfo() const 
{
    std::cout << "\n{" << DateOfCreation << "} Hospital: " << Name << ", Area: " << Area 
        << "\nLocation: " << Location << ", Relevance: " << Relevance << " %\nDoctors: \n";
    for (size_t i = 0; i < Doctors.GetSize(); i++)
    {
        Doctors[i]->PrintInfo();
    }
}
void Hospital::PrintDoctorsRoles() const 
{
    std::cout << "There are such roles for doctors:\n" 
        << "1)Oncologist\n2)Pulmonologist\n3)Therapist\n";
}
void Hospital::CurePatient(Doctor* doctor, Worker* patient, Illness illness) 
{
    for (size_t i = 0; i < Doctors.GetSize(); i++)
    {
        if(Doctors[i]->GetPNumber() == doctor->GetPNumber())
            Doctors[i]->CurePatient(patient, illness);
    }
}
