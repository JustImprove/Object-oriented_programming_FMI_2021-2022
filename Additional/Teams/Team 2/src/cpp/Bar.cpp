#include "../h/Bar.h"

#pragma region Drink
Drink::Drink(const String& Name, size_t AlcoholPercentage, double Cost) 
{
    this->Name = Name;
    this->Cost = Cost;
        (AlcoholPercentage > 100) ? this->AlcoholPercentage = 100 : this->AlcoholPercentage = AlcoholPercentage;
} 
void Drink::PrintInfo() const
{
    std::cout << "Drink: \'" << Name << "\' Alcohol: " << AlcoholPercentage << " %\n"
        << "Cost: "<< Cost << '\n';
}
#pragma endregion

#pragma region Bar
void Bar::AddBartender(Bartender* bartender)
{
    if(this->bartender == nullptr) 
    {
            this->bartender = bartender; // Sharing the same adress is main there. One Bartender 
        std::cout << "#Bartender was successfully added to the bar#\n";
    }
    else 
        std::cout << "#Bartender is already existed in this {" << Name << "} #\n";
};
void Bar::PourDrink(const String& DrinkName, Worker* Customer)
{
    if(bartender == nullptr)
    {
        std::cout << "There is no bartender existed !\n";
        return;
    }

        size_t ReturnIndex = 0;
    if(!isDrinkExisted(DrinkName, ReturnIndex))
    {
        std::cout << "There is no such drink existed !\n";
        return;
    }
    else if((Customer->GetIllnesses().isExisted(Illness::Alcohol_Poisoning))
        || (Customer->GetSalary() < Drinks[ReturnIndex].GetCost()))
    {
        std::cout << "This drink can't be consumed by the Customer: { Too less money or illness } !\n";
        return;
    }

    bartender->PourDrink();
    std::cout << "#The " << DrinkName << " was consumed by " << Customer->GetName() << " #\n";

    if(Drinks[ReturnIndex].GetAlcoholPercentage() > 60) 
    {
        Customer->AddIllness(Illness::Alcohol_Poisoning);
            std::cout << "# " << Customer->GetName() << " is overdrunked and he can't drink morea alcohol#\n";
    }
};
size_t Bar::GetAlcoholdDrinks() const
{
        int Count = 0;
    for (size_t i = 0; i < Drinks.GetSize(); i++)
            {
                if(Drinks[i].GetAlcoholPercentage() > 0)
                    Count++;
            }
        return Count;
};
void Bar::PrintInfo() const 
{
    std::cout << "\n{" << DateOfCreation << "} Bar: " << Name << ", Area: " << Area 
        << "\nLocation: " << Location << ", Relevance: " << Relevance << " %\n";
    if(bartender != nullptr)
        bartender->PrintInfo();
    for (size_t i = 0; i < Drinks.GetSize(); i++)
    {
        Drinks[i].PrintInfo();
    }
};
bool Bar::isDrinkExisted(const String& DrinkName, size_t& ReturnIndex) 
{    
    for (size_t i = 0; i < Drinks.GetSize(); i++) 
    {
        if(Drinks[i].GetName() == DrinkName) 
        {
            ReturnIndex = i; 
            return true;
        }  
    }
        return false;
};
#pragma endregion
