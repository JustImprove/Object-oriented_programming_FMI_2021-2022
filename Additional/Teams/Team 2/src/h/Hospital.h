#pragma once 
#include "Building.h"
#include "Doctor.h"

class Hospital : public Building 
{
    public:
        Hospital() : Building() {};
        Hospital(const String& Name, size_t Area, size_t Relevance, const String& Location)
            : Building(Name, Area, Type::Medical, Relevance, Location) {};

        Building* Clone() const override {return new Hospital(*this);};
        void PrintInfo() const override; 
        void PrintDoctorsRoles() const; 

        void AddDoctor(Doctor* other) {Doctors.Push_Back(other);}; 
        size_t GetDoctorsCount() const {return Doctors.GetSize();}; 
        void CurePatient(Doctor* doctor, Worker* patient, Illness illness);
    private:
        mutable Vector<Doctor*> Doctors; 
};