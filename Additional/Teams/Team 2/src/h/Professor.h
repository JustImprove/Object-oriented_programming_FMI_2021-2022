#pragma once 
#include "Worker.h"
#pragma warning (disable:4996)

class Professor : public Worker 
{
    public:
        enum class Role 
        {
            Undefined,
            Doctor_of_medical_sciences/*To teach doctors*/, 
            Architecture/*To teach builders*/,
            // P.s: Bartender don't have exact specialisation 
        };
    
        Professor() : Worker() {StudentsThatWereTaught = 0; specialisation = Specialisation::Professor; role = Role::Undefined;};
        Professor(String Name, size_t pNumber, double Salary, Role role): Worker(Name, pNumber, Specialisation::Professor, Salary) 
            {StudentsThatWereTaught = 0; this->role = role;};
        
        void ChangeSpecialisation(Role role);
        Role GetRole() const {return role;};
        
        // Трябва да бъде извън класа - сега е просто заради демонстративни цели
        void GiveNewSpecialisation(Worker* other, String& NewSpecialisation); // String reqires non-const var to compare with "=="
        void PrintInfo() const override;

    private:
        size_t StudentsThatWereTaught;
        Role role;
};
