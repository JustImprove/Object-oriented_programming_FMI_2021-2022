#pragma once 
#include "Building.h"
#include "Bartender.h"

class Drink 
{
    public: 
        Drink() : AlcoholPercentage(0), Cost(0) {}; 
        Drink(const String& Name, size_t AlcoholPercentage, double Cost); 

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
            : Building(Name, Area, Type::Entertaining, Relevance, Location), bartender(nullptr) {};
        Building* Clone() const override {return new Bar(*this);};

        void AddBartender(Bartender* bartender); 
        void AddDrink(const Drink& drink) {Drinks.Push_Back(drink);};
        void PourDrink(const String& DrinkName, Worker* Customer); // DISCLAIMER: If cutomer drink smth with alcohol % > 60, he will automatically get "Alcohol Poisoning"
    
        size_t GetCountAlcoholDrinks() const;
        size_t GetCountNonAlcoholDrinks() const {return (Drinks.GetSize() - GetCountAlcoholDrinks());};
        void PrintInfo() const override;

    private: 
        mutable Vector<Drink> Drinks; // "Mutable" because operator[] returns &T as T - Type of Vector
        Bartender* bartender; 
            bool isDrinkExisted(const String& DrinkName, size_t& ReturnIndex);
};
