#include "../h/Professor.h"
#include "../h/Builder.h"
#include "../h/Doctor.h"
#include "../h/CharConstants.h"

void Professor::ChangeSpecialisation(Role role) 
{
    if(role != Role::Undefined)
        this->role = role;
    else
        std::cout << "Role must be defined !\n";
}
void Professor::GiveNewSpecialisation(Worker* other, const String& NewSpecialisation) 
{
    if(this == other)
        return;

    if(other->GetSpecialisation() == Worker::Specialisation::Builder && role == Role::Architecture) 
    {
        if(NewSpecialisation == Educational)
            dynamic_cast<Builder*>(other)->ChangeSpecialisation(Building::Type::Educational);
        else if(NewSpecialisation == Medical)
            dynamic_cast<Builder*>(other)->ChangeSpecialisation(Building::Type::Medical);
        else if(NewSpecialisation == Entertaining) 
            dynamic_cast<Builder*>(other)->ChangeSpecialisation(Building::Type::Entertaining);
        std::cout << "#The specialisation of builder was changed#\n";
            StudentsThatWereTaught++;
    }
    else if(other->GetSpecialisation() == Worker::Specialisation::Doctor 
        && role == Role::Doctor_of_medical_sciences)
    {
        if(NewSpecialisation == Oncologist) 
            dynamic_cast<Doctor*>(other)->ChangeSpecialisation(Doctor::Role::Oncologist);
        else if(NewSpecialisation == Pulmonologist)
            dynamic_cast<Doctor*>(other)->ChangeSpecialisation(Doctor::Role::Pulmonologist);
        else if(NewSpecialisation == Therapist)
            dynamic_cast<Doctor*>(other)->ChangeSpecialisation(Doctor::Role::Therapist);
        std::cout << "#The specialisation of doctor was changed#\n";
            StudentsThatWereTaught++;
    }
    else if(other->GetSpecialisation() == Worker::Specialisation::Professor) 
    {
        if(role == Role::Architecture && NewSpecialisation == Architecture)
            dynamic_cast<Professor*>(other)->ChangeSpecialisation(Role::Architecture);
        else if(role == Role::Doctor_of_medical_sciences && NewSpecialisation == Doctor_of_medical_sciences)
            dynamic_cast<Professor*>(other)->ChangeSpecialisation(Role::Doctor_of_medical_sciences);
        std::cout << "#The specialisation of professor was changed#\n";
            StudentsThatWereTaught++;
    }
    else 
        std::cout << "#Specialisation of stated worker can't be changed by stated professor#\n";
};
void Professor::PrintInfo() const
{
    std::cout << "\nProfessor: " << Name << ", Personal Number: " << pNumber 
        << ", Salary: " << Salary << "\nSpecialisation: ";
    switch(role) 
    {
        case Role::Architecture:
            std::cout << "Architecture";
            break;
        case Role::Doctor_of_medical_sciences:
            std::cout << "Doctor_of_medical_sciences";
            break;
        default:
            std::cout << "Undefined";
    }
        std::cout << ", Taught people: " << StudentsThatWereTaught << '\n';
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
