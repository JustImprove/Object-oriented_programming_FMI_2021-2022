#pragma once 
#include "Worker.h"

class Doctor : public Worker 
{
    public:
        enum class Role 
        {
            Undefined, Oncologist/* (cancer) */, Pulmonologist/* (asthma) */, Therapist/* (poisoning, rabies) */
        }; 
        
        Doctor() : Worker(), CuredPatients(0), specialisation(Specialisation::Doctor), role(Role::Undefined) {}; // "Role" ще е Undefined по подразбиране
        Doctor(String Name, size_t pNumber, double Salary, Role role) 
            : Worker(Name, pNumber, Specialisation::Doctor, Salary), role(role), CuredPatients(0) {};

        void ChangeSpecialisation(Role role); // One doctor will not change his specialisation without Professor (According the logic)
        void CurePatient(Worker* patient, Illness illness);

        void PrintInfo() const override;
        Role GetRole() const {return this->role;};

    private:
        size_t CuredPatients; 
        Role role;
};
