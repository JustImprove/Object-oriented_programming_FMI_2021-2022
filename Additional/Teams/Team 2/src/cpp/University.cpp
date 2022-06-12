#include "University.h"

void University::PrintInfo() const 
{
    std::cout << "\n{" << DateOfCreation << "} University: " << Name << ", Area: " << Area 
        << "\nLocation: " << Location << ", Relevance: " << Relevance << " %\nProfessors: \n";
    for (size_t i = 0; i < Professors.GetSize(); i++)
    {
        Professors[i]->PrintInfo();
    }
}
void University::PrintProfessorsRoles() const 
{
    std::cout << "There are such roles for professors: " << "\n1)Doctor_of_medical_sciences\n2)Architecture\n";
}
void University::GiveNewSpecialisation(Professor* professor, Worker* other, String& NewSpecialisation) 
{
    for (size_t i = 0; i < Professors.GetSize(); i++)
    {
        if(Professors[i]->GetPNumber() == professor->GetPNumber())
            Professors[i]->GiveNewSpecialisation(other, NewSpecialisation);
    }
}