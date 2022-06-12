#pragma once
#include "String.h"
#include <ctime> // For calculating the time
#include "Illnesses.h"
#pragma warning(disable:4996)

const char DATE_FORMAT[] = "%a %d/%m/%Y %r"; // Regex, that define the way writing the date & time to CreationDate from DateTime struct
const int MAX_DATE_LENGTH = 50;

/*Abstract*/ class Building 
{
    private:
        void DetermineDate(); // Converts current time to String
    public:
        enum class Type 
        {
            Undefined, Educational, Medical, Entertaining
        };
        
        virtual ~Building() = default;
        Building() {Area = Relevance = 0; BuildingType = Type::Undefined;}; 
        Building(const String& Name, size_t Area, Type BuildingType, size_t Relevance, const String& Location) 
            : Name(Name), Area(Area), BuildingType(BuildingType), Location(Location) 
                {(Relevance > 100) ? this->Relevance = 100 : this->Relevance = Relevance; DetermineDate();};
        // There is no need to delete copying of one building -> By the fact, in real life can exist two exactly the same buildings 

        virtual Building* Clone() const = 0;
        virtual void PrintInfo() const = 0; 

        void Renovate(); // Condition of one builidng will become ideal - Relevance to 100%

        String GetName() const {return Name;};
        size_t GetArea() const {return Area;};
        Type GetBuildingType() const {return BuildingType;};
        size_t GetRelevance() const {return Relevance;};
        String GetLocation() const {return Location;};
        String GetDateOfCreation() const {return DateOfCreation;};

    protected: 
        String Name;
        size_t Area; 
        Type BuildingType;
            size_t Relevance; // Var, that shows the condition of one building (new, old...)
        String Location;
        String DateOfCreation; // String-format of current date & time
};