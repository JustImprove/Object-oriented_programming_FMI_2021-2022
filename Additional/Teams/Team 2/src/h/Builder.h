#pragma once 
#include "Worker.h"
#include "Building.h"

class Builder : public Worker 
{
    public:
        Builder() : Worker() {specialisation = Specialisation::Builder; TypeToBuild = Building::Type::Undefined;};
        Builder(String Name, size_t pNumber, double Salary, Building::Type TypeToBuild) 
            : Worker(Name, pNumber, Worker::Specialisation::Builder, Salary) 
                {this->TypeToBuild = TypeToBuild;};

        void ChangeSpecialisation(Building::Type TypeToBuild);

        void AddBuildingToBuiltList(Building* obj);
        size_t BuiltBuildingsCount() const {return AlreadyBuilt.GetSize();};
        void Renovate(Building* obj); // Relevance = condition. If it's < 50% -> then building need to be renovated
        void PrintInfo() const override;  

    private: 
        mutable Vector<Building*> AlreadyBuilt; // Just copies of pointers to buildings, that were built by current Builder (exact buildings will be in final class)
        Building::Type TypeToBuild;  
    bool CanBuild(const Building* obj) const 
        {return (TypeToBuild == obj->GetBuildingType());};
};
