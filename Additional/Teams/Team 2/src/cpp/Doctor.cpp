#include "Doctor.h"

void Doctor::CurePatient(Worker* patient, Illness illness) 
{
    if(!patient->GetIllnesses().isExisted(illness)) // Whether this person has stated illness
        std::cout << "Patient don't have such disease !\n";

    if((role == Role::Oncologist) && (illness == Illness::Cancer)) 
    {
         CuredPatients++;
         std::cout << "# {" << patient->GetName() << "} was cured from Cancer#\n";
            CureDisease(patient, illness);
    }
    else if((role == Role::Pulmonologist) && (illness == Illness::Asthma)) 
    {
         CuredPatients++;
         std::cout << "# {" << patient->GetName() << "} was cured from Asthma#\n";
            CureDisease(patient, illness);
    }
    else if(((role == Role::Therapist) && (illness == Illness::Rabies))
           || ((role == Role::Therapist) && (Illness::Alcohol_Poisoning))) 
    {
          CuredPatients++;
          std::cout << "# {" << patient->GetName() << "} was cured from Rabies or Alcohol poisoning#\n";
             CureDisease(patient, illness);
    }
    else
        std::cout << "Such illness can't be cured by this Doctor !\n";
}
void Doctor::PrintInfo() const 
{
    std::cout << "\nDoctor: " << Name << ", Personal Number: " << pNumber 
        << ", Salary: " << Salary << "\nSpecialisation: ";
    switch(role) 
    {
        case Role::Oncologist:
            std::cout << "Oncologist";
            break;
        case Role::Pulmonologist:
            std::cout << "Pulmonologist";
            break;
        case Role::Therapist:
            std::cout << "Therapist";
            break;
        default:
            std::cout << "Undefined";
    }
        std::cout << ", Cured Patients: " << CuredPatients << std::endl;
    std::cout << "Illnesses:\n";
    for (size_t i = 0; i < Illnesses.GetSize(); i++)
    {
        if(Illnesses[i] == Illness::Alcohol_Poisoning)
            std::cout << (i + 1) << ") Alcohol_Poisoning\n";
        else if(Illnesses[i] == Illness::Asthma)
            std::cout << (i + 1) << ") Asthma\n";
        else if(Illnesses[i] == Illness::Cancer)
            std::cout << (i + 1) << ") Cancer\n";
        else if(Illnesses[i] == Illness::Rabies)
            std::cout << (i + 1) << ") Rabies\n";
    }
};
void Doctor::ChangeSpecialisation(Role role) 
{
    if(role != Role::Undefined)
        this->role = role;
    else 
        std::cout << "Role must be defined !\n";
}
