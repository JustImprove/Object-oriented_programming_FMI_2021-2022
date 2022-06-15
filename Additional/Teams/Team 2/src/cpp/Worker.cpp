#include "../h/Worker.h"

void Worker::AddIllness(Illness illness) 
{
    if(Illnesses.GetSize() > 0) 
    {
        if(Illnesses.isExisted(illness)) 
        {
            std::cout << "One person can't have 2 equal diseases !\n";
            return;
        }
    }
        Illnesses.Push_Back(illness);
    std::cout << "#Illness was added successfully#\n";
};
void Worker::CureDisease(Worker* patient, Illness illness) 
{
    for (size_t i = 0; i < patient->Illnesses.GetSize(); ++i)
    {
        if(patient->Illnesses[i] == illness)
            patient->Illnesses.Erase(i);
    }
};
