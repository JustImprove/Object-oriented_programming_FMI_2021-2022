#pragma once 
#include "Building.h"
#include "Bartender.h"

class Drink 
{
    public: 
        Drink() {AlcoholPercentage = Cost = 0;}; 
        Drink(const String& Name, size_t AlcoholPercentage, double Cost)
            {this->Name = Name; this->Cost = Cost; 
                (AlcoholPercentage > 100) ? this->AlcoholPercentage = 100 : this->AlcoholPercentage = AlcoholPercentage;}; 

        String GetName() const {return Name;};
        size_t GetAlcoholPercentage() const {return AlcoholPercentage;}; 
        size_t GetCost() const {return Cost;};

        void PrintInfo() const;
    
    private: 
        size_t AlcoholPercentage;
        String Name;
        double Cost;
};
class Bar : public Building 
{
    public:
        ~Bar() {delete bartender;};
        Bar() : Building(), bartender(nullptr) {}; 
        Bar(const String& Name, size_t Area, size_t Relevance, const String& Location) 
            : Building(Name, Area, Type::Entertaining, Relevance, Location) {bartender = nullptr;};
        Building* Clone() const override {return new Bar(*this);};

        void AddBartender(Bartender* bartender); 
        void AddDrink(const Drink& drink) {Drinks.Push_Back(drink);};
        void PourDrink(String DrinkName, Worker* Customer); // DISCLAIMER: If cutomer drink smth with alcohol % > 60, he will automatically get "Alcohol Poisoning"
    
        size_t GetAlcoholdDrinks() const;
        size_t GetNonAlcoholDrinks() const {return (Drinks.GetSize() - GetAlcoholdDrinks());};
        void PrintInfo() const override;

    private: 
        mutable Vector<Drink> Drinks; // "Mutable" because operator[] returns &T as T - Type of Vector
        Bartender* bartender; 
            bool isDrinkExisted(String DrinkName, size_t& ReturnIndex);
};