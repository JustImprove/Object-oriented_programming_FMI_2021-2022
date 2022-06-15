#include "../h/Building.h"

Building::Building(const String& Name, size_t Area, Type BuildingType, size_t Relevance, const String& Location) 
   : Name(Name), Area(Area), BuildingType(BuildingType), Location(Location) 
{
   (Relevance > 100) ? this->Relevance = 100 : this->Relevance = Relevance; 
       DetermineDate();
}
void Building::DetermineDate() 
{
    char* Temp = new char[MAX_DATE_LENGTH + 1]{};
        time_t t; // Variable that will get info about local date & time below in the code
    struct tm *DateTime; // Struct, that will hold concrete date & time of creation of the Account

    t = time(NULL);
    DateTime = localtime(&t);
        strftime(Temp, MAX_DATE_LENGTH, DATE_FORMAT, DateTime); // F-tion, that fill str <Buffer> with received date & time from DateTime var.
    DateOfCreation = Temp;
        delete[] Temp; 
}
void Building::Renovate() 
{
    if(Relevance < 50) 
    {
        Relevance = 100;
            std::cout << "#Buiding {" << Name << "} was fully renovated#\n";
    }
    else
        std::cout << "#There is no need for {" << Name << "} to be renovated#\n";
}
