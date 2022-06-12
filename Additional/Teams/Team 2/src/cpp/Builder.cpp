#include "Builder.h"

void Builder::AddBuildingToBuiltList(Building* obj) 
{
    if(!CanBuild(obj)) 
    {
        std::cout << "This type of building can't be built !\n";
        return;
    }
        AlreadyBuilt.Push_Back(obj);
}
void Builder::Renovate(Building* obj) 
{
    if(obj->GetRelevance() < 50) 
        obj->Renovate();
}
void Builder::PrintInfo() const 
{
    std::cout << "\nBuilder: " << Name << ", Personal Number: " << pNumber 
        << ", Salary: " << Salary << "\nType of Buildings: ";
    switch (TypeToBuild) 
    {
        case Building::Type::Educational:
            std::cout << "Educational\n";
            break;
        case Building::Type::Entertaining:
            std::cout << "Entertaining\n";
            break;
        case Building::Type::Medical:
            std::cout << "Medical\n";
            break;
        default:
            std::cout << "Undefined\n";
            break;
    }
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
    
    for (size_t i = 0; i < AlreadyBuilt.GetSize(); i++)
    {
        if(i == 0)
            std::cout << "Buildings by {" << Name << "}: \n";
        std::cout << (i + 1) << ") " << AlreadyBuilt[i]->GetName() << '\n';
    }
    
}; 
void Builder::ChangeSpecialisation(Building::Type TypeToBuild) 
{
    if(TypeToBuild != Building::Type::Undefined)
        this->TypeToBuild = TypeToBuild;
    else
        std::cout << "Building type must be defined !\n";
};