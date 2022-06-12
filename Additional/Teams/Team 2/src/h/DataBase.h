#pragma once
#include "Hospital.h"
#include "University.h"
#include "Bar.h"

class DataBase 
{
    private:    
        // Workers part 
        void PrintWorkers() const;
        void CreateWorker(const String& str);
        void LoginWorker(const String& str);
        bool isAlreadyWorker(size_t pNumber) const; // Checks, whether worker with stated pNumber is already in collection

        // Buildings part
        void PrintBuildings() const; 
        void CreateBuilding(const String& str); 
        void LoginBuilding(const String& str); 
        bool isAlreadyBuilding(const String& Name) const;
        void Renovate(const String& str); 

        void BarMenu(Bar* other); 
        void HospitalMenu(Hospital* other); 
        void UniversityMenu(University* other); 

    public: 
        DataBase() = default;
            DataBase(const DataBase& other) = delete; // Deleting Copy() semantics in order to prevent crashes while working with 2 containers of 2 basic classes
            DataBase& operator=(const DataBase& other) = delete;
        DataBase(DataBase&& other) = default;
        DataBase& operator=(DataBase&& other) = default;
        ~DataBase() {Free();};

        void Execute(); 

    private:
        mutable Vector<Building*> Buildings; // "Mutable" because of operator[] (Vector)
        mutable Vector<Worker*> Workers;
            void Free();

        // Define f-tions
        Illness DefineIllness(const String& str) const;
        Building::Type DefineBuildingType(const String& str) const; 
        Doctor::Role DefineDoctorRole(const String& str) const; 
        Professor::Role DefineProfessorRole(const String& str) const; 
};