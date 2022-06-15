#include "DataBase.h"
#include "CharConstants.h"
#include "Builder.h"a

const int MIN_PARAMETRES_FOR_WORKER = 4;
const int EXACT_PARAMETRES_FOR_BUILDINGS = 6;

void DataBase::Free() 
{
    for (size_t i = 0; i < Buildings.GetSize(); i++)
    {
        delete Buildings[i];
    }
        Buildings.Clear();
    for (size_t i = 0; i < Workers.GetSize(); i++)
    {
        delete Workers[i];
    }
        Workers.Clear();
}

void DataBase::Execute() 
{
        String Buffer;
    while(!(Buffer == "quit")) 
    {
            Buffer.Clear();
        std::cout << "#Press number#\n1) People section\n2) Buildings section\n> ";
            std::cin >> Buffer;
        if(Buffer == "1")
        {
            std::cout << "#Peoples section entered#\n";
                Buffer.Clear();
            std::cout << "> ";
                std::cin >> Buffer;
            if(Buffer.isExisted("print"))
                PrintWorkers();
            else if(Buffer.isExisted("create")) 
                CreateWorker(Buffer);
            else if(Buffer.isExisted("login")) 
                LoginWorker(Buffer);
        }
        else if (Buffer == "2")
        {
            std::cout << "#Buildings section entered#\n";
                Buffer.Clear();
            std::cout << "> ";
                std::cin >> Buffer;
            if(Buffer.isExisted("print"))
                PrintBuildings();
            else if(Buffer.isExisted("create"))
                CreateBuilding(Buffer);
            else if(Buffer.isExisted("login"))
                LoginBuilding(Buffer);
            else if(Buffer.isExisted("renovate"))
                Renovate(Buffer);
        }
    };
}

#pragma region Define functions
Illness DataBase::DefineIllness(const String& str) const 
{
    if(str == AlcoholPoisoning)
        return Illness::Alcohol_Poisoning;
    else if(str == Cancer)
        return Illness::Cancer;
    else if(str == Asthma)
        return Illness::Asthma;
    else if(str == Rabies)
        return Illness::Rabies;
    else
        throw std::logic_error("\nError: stated illness was invalid !\n");
} 
Building::Type DataBase::DefineBuildingType(const String& str) const 
{
    if(str == Educational)
        return Building::Type::Educational;
    else if(str == Medical)
        return Building::Type::Medical;
    else if(str == Entertaining)
        return Building::Type::Entertaining;
    else
        throw std::logic_error("\nError: stated Building type was incorrect !\n");
}
Doctor::Role DataBase::DefineDoctorRole(const String& str) const 
{
    if(str == Oncologist)
        return Doctor::Role::Oncologist;
    else if(str == Pulmonologist)
        return Doctor::Role::Pulmonologist;
    else if(str == Therapist)
        return Doctor::Role::Therapist;
    else 
        throw std::logic_error("\nError: stated Docto specialisation was invalid !\n"); 
}
Professor::Role DataBase::DefineProfessorRole(const String& str) const 
{
    if(str == Architecture)
        return Professor::Role::Architecture;
    else if(str == Doctor_of_medical_sciences)
        return Professor::Role::Doctor_of_medical_sciences;
    else
        throw std::logic_error("\nError: stated Professor specialisation was invalid !\n");
}
#pragma endregion

#pragma region Workers: Functions
bool DataBase::isAlreadyWorker(size_t pNumber) const
{
    for (size_t i = 0; i < Workers.GetSize(); i++)
    {
        if(Workers[i]->GetPNumber() == pNumber)
            return true;
    }
        return false;
}
void DataBase::PrintWorkers() const 
{
    if(Workers.GetSize() == 0) 
    {
        std::cout << "#There is no workers yet#\n";
            return;
    }

    for (size_t i = 0; i < Workers.GetSize(); i++)
        Workers[i]->PrintInfo();
}
void DataBase::CreateWorker(const String& str) 
{
        Vector<String> Params = str.StrBetweenBoundaries('"', '"');
    if(Params.GetSize() < MIN_PARAMETRES_FOR_WORKER) 
    {
        std::cout << "Invalid input of parametres !\n";
            return;
    }
    else if(isAlreadyWorker(Params[1].ToDouble())) 
    {
        std::cout << "Worker with stated pNumber is already existed !\n";
            return;
    }

    if(Params.GetSize() == 5) // If "Role" field was stated 
    {
        if(Params[2] == builder) 
        {
            Workers.Push_Back(new Builder(Params[0], Params[1].ToDouble(), Params[3].ToDouble(), DefineBuildingType(Params[4])));
                std::cout << "#Builder was created successfully#\n";
        }
        else if(Params[2] == doctor) 
        {
            Workers.Push_Back(new Doctor(Params[0], Params[1].ToDouble(), Params[3].ToDouble(), DefineDoctorRole(Params[4])));
                std::cout << "#Doctor was created successfully#\n";
        }
        else if(Params[2] == professor) 
        {
            Workers.Push_Back(new Professor(Params[0], Params[1].ToDouble(), Params[3].ToDouble(), DefineProfessorRole(Params[4])));
                std::cout << "#Professor was created successfully#\n";
        }
    }
    else 
    {
        Workers.Push_Back(new Bartender(Params[0], Params[1].ToDouble(), Params[3].ToDouble()));
            std::cout << "#Bartender was created successfully#\n";
    }
}
void DataBase::LoginWorker(const String& str) 
{
    String Buffer;
        Vector<String> Params = str.StrBetweenBoundaries('"', '"'); // Template: create "value" "..."; Params[0] = "value";...;
    if(Params.GetSize() < 2) 
    {
            std::cout << "Invalid input of parametres !\n";
        return;
    }
    
    for (size_t i = 0; i < Workers.GetSize(); i++)
    {
        if(Workers[i]->GetPNumber() == (int)(Params[1].ToDouble())) 
        {
                Params.Clear(); // Avoiding error behavior below
            std::cout << "Login succeeded !\n> ";
                std::cin >> Buffer;
            Params = Buffer.StrBetweenBoundaries('"', '"');  
            
            if(Buffer.isExisted("print")) // Firstly, we pass the case, when "Params" can be empty
                Workers[i]->PrintInfo();
            else if(Buffer.isExisted("addIllness")) 
                Workers[i]->AddIllness(DefineIllness(Params[0]));
            else if(Buffer.isExisted("changeSalary")) 
            {
                Workers[i]->SetSalary(Params[0].ToDouble());
                    std::cout << "#Salary was changed to{" << Params[0].ToDouble() << "}#\n";
            } 
            return;
        }
    }
        std::cout << "#There is no worker added with such name or pNumber#\n";
}
#pragma endregion

#pragma region Buildings: Functions 
void DataBase::Renovate(const String& str) 
{
        Vector<String> Params = str.StrBetweenBoundaries('"', '"');
    if(Params.GetSize() == 2) 
    {
        if(!isAlreadyWorker(Params[1].ToDouble())) 
        {
            std::cout << "#There is no builder to renovate {" << Params[0] << "} #\n";
                return;
        }

        for (size_t i = 0; i < Buildings.GetSize(); i++)
        {
            if(Buildings[i]->GetName() == Params[0]) 
                Buildings[i]->Renovate();
            else
                std::cout << "#There is no such building to be renovated#\n";
        }
    }   
    else
        std::cout << "#Invalid input of parametres#\n";
}
void DataBase::PrintBuildings() const 
{
    if(Buildings.GetSize() == 0) 
    {
        std::cout << "#There is no buildings yet#\n";
            return;
    }

    for (size_t i = 0; i < Buildings.GetSize(); i++)
        Buildings[i]->PrintInfo();
}
void DataBase::CreateBuilding(const String& str) 
{
        Vector<String> Params = str.StrBetweenBoundaries('"', '"');
    if(Params.GetSize() != EXACT_PARAMETRES_FOR_BUILDINGS) 
    {
        std::cout << "Invalid input of parametres !\n";
            return;
    }
    else if(isAlreadyBuilding(Params[1])) 
    {
        std::cout << "Building with stated Name is already existed !\n";
            return;
    }
        Building::Type Temp = DefineBuildingType(Params[3]);
    if(!isAlreadyWorker(Params[0].ToDouble())) 
    {
        std::cout << "#There is no such builder to create stated building#\n";
            return;
    }

    if(Temp == Building::Type::Educational) 
    {
        Buildings.Push_Back(new University(Params[1], Params[2].ToDouble(), Params[4].ToDouble(), Params[5]));
            std::cout << "#University was created successfully#\n";
    }
    else if(Temp == Building::Type::Medical) 
    {
        Buildings.Push_Back(new Hospital(Params[1], Params[2].ToDouble(), Params[4].ToDouble(), Params[5]));
            std::cout << "#Hospital was created successfully#\n";
    }
    else if(Temp == Building::Type::Entertaining) 
    {
        Buildings.Push_Back(new Bar(Params[1], Params[2].ToDouble(), Params[4].ToDouble(), Params[5]));
            std::cout << "#Bar was created successfully#\n";
    }

    for (size_t i = 0; i < Workers.GetSize(); i++)
    {
        if(Workers[i]->GetPNumber() == Params[0].ToDouble())
            dynamic_cast<Builder*>(Workers[i])->AddBuildingToBuiltList(Buildings[Buildings.End()]); // Add yet created building to the built list of exact builder (synchronisation)
    }
    
}
bool DataBase::isAlreadyBuilding(const String& Name) const 
{
    for (size_t i = 0; i < Buildings.GetSize(); i++)
    {
        if(Buildings[i]->GetName() == Name)
            return true;
    }
        return false;
}
void DataBase::LoginBuilding(const String& str) 
{
        Vector<String> Params = str.StrBetweenBoundaries('"', '"'); // Template: create "value" "..."; Params[0] = "value";...;
    if(Params.GetSize() < 1) 
    {
            std::cout << "Invalid input of parametres !\n";
        return;
    }

    for (size_t i = 0; i < Buildings.GetSize(); i++)
    {
        if(Buildings[i]->GetName() == Params[0]) 
        {
                std::cout << "Login succeeded !\n";
            if(Buildings[i]->GetBuildingType() == Building::Type::Educational)
                UniversityMenu(dynamic_cast<University*>(Buildings[i]));
            else if(Buildings[i]->GetBuildingType() == Building::Type::Entertaining)
                BarMenu(dynamic_cast<Bar*>(Buildings[i]));
            else if(Buildings[i]->GetBuildingType() == Building::Type::Medical)
                HospitalMenu(dynamic_cast<Hospital*>(Buildings[i]));

            return;
        }
    }
        std::cout << "#There is no building created to be loged in#\n";
}
void DataBase::BarMenu(Bar* other) 
{
    String Buffer;
        std::cout << "#The Bar {" << other->GetName() << "} was entered#\n> ";
    std::cin >> Buffer;
        Vector<String> Params = Buffer.StrBetweenBoundaries('"', '"');
    if(Buffer == "print")
        other->PrintInfo();
    else if(Buffer.isExisted("addBartender") && Params.GetSize() == 1) 
    {
        for (size_t i = 0; i < Workers.GetSize(); i++)
        {
            if(Workers[i]->GetPNumber() == Params[0].ToDouble()) 
            {
                if(Workers[i]->GetSpecialisation() == Worker::Specialisation::Bartender) 
                {
                    other->AddBartender(dynamic_cast<Bartender*>(Workers[i]));
                    break;
                }
            }
        }
        
    }
    else if(Buffer.isExisted("addDrink") && Params.GetSize() == 3) 
    {
        other->AddDrink(Drink(Params[0], Params[1].ToDouble(), Params[2].ToDouble()));
            std::cout << "#Drink {" << Params[0] << "} was added to bar#\n";
    } 
    else if(Buffer.isExisted("pour") && Params.GetSize() == 2) 
    {
        for (size_t i = 0; i < Workers.GetSize(); i++)
        {
            if(Workers[i]->GetPNumber() == Params[0].ToDouble()) 
            {
                other->PourDrink(Params[1], Workers[i]);
                    std::cout << "# " << Params[1] << " was drinked by {" << Workers[i]->GetName() << "} #\n";
            }
        }
    }
}
void DataBase::HospitalMenu(Hospital* other) 
{
    String Buffer;
        std::cout << "#The Hospital {" << other->GetName() << "} was entered#\n> ";
    std::cin >> Buffer;
        Vector<String> Params = Buffer.StrBetweenBoundaries('"', '"');
    if(Buffer == "print")
        other->PrintInfo();
    else if(Buffer.isExisted("addDoctor") && Params.GetSize() == 1) 
    {
        for (size_t i = 0; i < Workers.GetSize(); i++)
        {
            if(Workers[i]->GetPNumber() == Params[0].ToDouble()) 
            {
                if(Workers[i]->GetSpecialisation() == Worker::Specialisation::Doctor) 
                {
                    other->AddDoctor(dynamic_cast<Doctor*>(Workers[i]));
                        std::cout << "#Doctor was successfully added to the Hospital#\n";
                    break;
                }
            }
        }
    }
    else if(Buffer.isExisted("cure") && Params.GetSize() == 3) 
    {
            Illness Temp = DefineIllness(Params[2]); // Defining illness from typed string between " "
        if(!isAlreadyWorker(Params[0].ToDouble()) || !isAlreadyWorker(Params[1].ToDouble())) 
        {
            std::cout << "#Invalid Personal number of Doctor or Patient#\n";
            return;
        }

        for (size_t i = 0; i < Workers.GetSize(); i++)
        {
            if(Workers[i]->GetPNumber() == Params[0].ToDouble()) // Check, whether one worker is doctor with staten pNumber above
            {
                for (size_t j = 0; j < Workers.GetSize(); j++) // Searching the index of patient
                {
                    if(Workers[j]->GetPNumber() == Params[1].ToDouble()) 
                    {
                        other->CurePatient(dynamic_cast<Doctor*>(Workers[i]), Workers[j], Temp);
                            return;
                    }
                }
            }    
        }
        
    }
}
void DataBase::UniversityMenu(University* other) 
{
    String Buffer;
        std::cout << "#The University {" << other->GetName() << "} was entered#\n> ";
    std::cin >> Buffer;
        Vector<String> Params = Buffer.StrBetweenBoundaries('"', '"');
    if(Buffer == "print")
        other->PrintInfo();
    else if(Buffer.isExisted("addProfessor") && Params.GetSize() == 1) 
    {
        for (size_t i = 0; i < Workers.GetSize(); i++)
        {
            if(Workers[i]->GetPNumber() == Params[0].ToDouble()) 
            {
                if(Workers[i]->GetSpecialisation() == Worker::Specialisation::Professor) 
                {
                    other->AddProfessor(dynamic_cast<Professor*>(Workers[i]));
                        std::cout << "#Professor was successfully added to the University#\n";
                    break;
                }
            }
        }
    }
    else if(Buffer.isExisted("giveNewSpecialisation") && Params.GetSize() == 3) 
    {
        if(!isAlreadyWorker(Params[0].ToDouble()) || !isAlreadyWorker(Params[1].ToDouble())) 
        {
            std::cout << "#Invalid Personal number of Professor or student#\n";
            return;
        }

        for (size_t i = 0; i < Workers.GetSize(); i++)
        {
            if(Workers[i]->GetPNumber() == Params[0].ToDouble()) // Firstly, we are trying to find professor with stated pNumber
            {
                for (size_t j = 0; j < Workers.GetSize(); j++)
                {
                    if(Workers[j]->GetPNumber() == Params[1].ToDouble()) // Secondly, we are searching the worker with stated pNumber
                    {
                        other->GiveNewSpecialisation(dynamic_cast<Professor*>(Workers[i]), Workers[j], Params[2]);
                            return;
                    }
                }
            }
        }
        
    }
}
#pragma endregion
