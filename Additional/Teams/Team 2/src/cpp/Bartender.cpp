#include "Bartender.h"

void Bartender::PrintInfo() const
{
    std::cout << "\nBartender: " << Name << ", Personal Number: " << pNumber 
        << ", Salary: " << Salary << "\nQuantity of poured drinks: " << PouredDrinks << '\n';
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