#pragma once 
#include "Worker.h"

class Bartender : public Worker 
{
    public:
        Bartender() : Worker() {PouredDrinks = 0; specialisation = Specialisation::Bartender;};
        Bartender(String Name, size_t pNumber, double Salary) : 
            Worker(Name, pNumber, Specialisation::Bartender, Salary), PouredDrinks(0) {};

        size_t GetPouredDrinksCount() const {return PouredDrinks;};
        void PourDrink() {PouredDrinks++;};
        void PrintInfo() const override;

    private: 
        size_t PouredDrinks; 
};
