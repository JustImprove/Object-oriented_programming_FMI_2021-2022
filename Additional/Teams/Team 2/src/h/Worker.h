#pragma once
#include "Illnesses.h" 
#include "../data_structures/String.h"

/*Abstract*/ class Worker 
{
    public:
        enum class Specialisation 
        {
            None, Builder, Doctor, Professor, Bartender
        };

            virtual ~Worker() = default; 
        Worker() : pNumber(0), Salary(0) {}; 
        Worker(const String& Name, size_t pNumber, Specialisation specialisation, double Salary) 
            : Name(Name), specialisation(specialisation), Salary(Salary), pNumber(pNumber) {};
        Worker(Worker&& other) = default; // Move semantics are defined already in String 
        Worker& operator=(Worker&& other) = default; 
        Worker(const Worker& other) = delete; // Deleted Copy() semantics, because in real life it can't be 2 people 
                                              // exactly the same with same pNumbers (the way of implementing setter for pNumber crash the logic, by the way)
        Worker& operator=(const Worker& other) = delete;
        
        // DISCLAIMER: One person will have max 1 specialisation 
        void AddIllness(Illness illness); // Just there illnesses will be added
        void SetSalary(double Salary) {(Salary >= 0) ? this->Salary = Salary : this->Salary = (Salary * -1);}; 
        // There is no need for Clone()* 

        virtual void PrintInfo() const = 0;

        String GetName() const {return Name;};
        size_t GetPNumber() const {return pNumber;};
        Specialisation GetSpecialisation() const {return specialisation;};
        double GetSalary() const {return Salary;};
        Vector<Illness> GetIllnesses() const {return Illnesses;};

    protected: 
        String Name;
        size_t pNumber; // Smth like Identifier 
            Specialisation specialisation;
        double Salary;
            Vector<Illness> Illnesses;

    void CureDisease(Worker* patient, Illness illness); // F-tion isn't going to be used by user or be called from object. Only inside derived class "Doctor"
};
