#pragma once 
#include "Building.h"
#include "Professor.h"

class University : public Building 
{
    public:
        University() : Building() {};
        University(const String& Name, size_t Area, size_t Relevance, const String& Location)
            : Building(Name, Area, Type::Educational, Relevance, Location) {};

        Building* Clone() const override {return new University(*this);};
        void PrintInfo() const override; 
        void PrintProfessorsRoles() const; 

        void AddProfessor(Professor* other) {Professors.Push_Back(other);}; 
        size_t GetProfessorsCount() const {return Professors.GetSize();}; 
        void GiveNewSpecialisation(Professor* professor, Worker* other, String& NewSpecialisation); 

    private: 
        Vector<Professor*> Professors; // "Mutable", because of operator[] from Vector, that return & on object
};
