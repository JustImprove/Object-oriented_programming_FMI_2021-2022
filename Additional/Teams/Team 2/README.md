# Clause/idea:
- Имаме симулация на реалния живот буквално. Тоест, класовете са ни обвързани
- Последния клас "DataBase" ни пази 2 хетерогенни контейнера : един с хора (Worker*) и със сгради (Building*)
- За да построим някоя сграда, то първо трябва да създадем работника и да му зададем специализация (всяка специализация е за отделен тип сгради за построяване)
- Също така всяка сграда предлага определена функционалност, като може да променя определен начин параметрите на един Worker 

# Project structure ->
![UML-Diagram of the project](https://github.com/JustImprove/Object-oriented_programming_FMI_2021-2022/blob/PR-task-Teams/Additional/Teams/Team%202/img/UML-Diagram.svg)

## |Copy & move operations|
- Copy() operations са забранени за клас Worker и всички наследени от него, защото няма как в реалната ситуация да има два човека с един и същ "Personal Number" иначе той губи смисъла за съществуване. Move() е позволено 
- Класът Building и всички наследени могат да ползват и двете семантики: Move() & Copy()
- Тъй като последния клас (class DataBase) ще ни съдържа два хетерогенни контейнера от два различни базови класа, то:
- Копиране на 1 DataBase е валидна операция, но тъй като тези операции са забранени в единия хетерогенен контейнер (Vector<Worker*>), то би било добре да обобщим операциите -> да позволим само Move-semantics за целия клас, за да не разваляме общата логика за работа с два базови класа

# Main methods/Functional:
```
~ class Bar, Hospital, University - ще имат колекции от поинтери към обекти, които ще се трият чак в крайния клас 
- По такъв начин, променяйки един Лекар и негови свойства, той ще е променен навсякъде, където се пази (Например, в различни Hospitals)
```
>class Building
- size_t Relevance - означава текуща кондиция на една сграда в "%" (Дали трябва да бъде ремонтирана(ако Relevance < 50), или не)
- Renovate() - напълно оправя сграда -> слага "Relevance" на 100 

>class Bar : public  Building
1) AddBartender(), AddDrink() - добавя напитки в колекция и само един барман (повече не трябва)
2) PourDrink() - всеки може да изпие от бара някаква напитка (алкохолна или не). Ако един човек пие алкохолна напитка със съдържание на алкохол > 60 %, то той получава "Alcohol Poisoning" като болест и повече не може да пие, докато не го премахне 

>class Hospital : public  Building
1) PrintDoctorRoles() - принтира всички роли, които могат да приемат лекари в проекта 
2) AddDoctor() - добавя лекар 
3) CurePatient() - Метод, който вика от конкретния Лекар метод "void CurePatient(Worker* patient, Illness illness)", по който болестта на един пациент може да бъде излекувана

>class University : public  Building
1) PrintProfessorsRoles() - извежда на конзола какви специализации може да притежава един професор
2) GiveNewSpecialisation() - Метод, който вика от определения професор метод "void GiveNewSpecialisation(Worker* other, String& NewSpecialisation)",  по който специализация на Builder, Professor или Doctor може да се промени 
     Пример: Doctor е бил "Oncologist", а след функцията става "Therapist"
3) PrintProfessorsRoles() - принтира всички специализации, които могат да приемат професори в проекта

>class Worker
- "Vector<Illness> GetIllnesses()" - метод, който връща съвкупност от болки, които има един човек (после тези дани ще бъдат анализирани в други класове)

>class Doctor
- "CurePatient(Worker* patient, Illness illness)" - Лекува конкретна болка на конкретен човек, който присътства вече в масива от създадени хора 

>class Professor
- "GiveNewSpecialisation(Worker* other, String& NewSpecialisation)" - метод, който се вика с помощта на клас "University" и променя специализация на един Лекар, Професор или Строител

>class DataBase
*- Имаме две различни категории: People & Buildings*

# Console input for category "People":
  ```
- print
- create "<Name>" "<Personal Nubmer>" "<Specialisation(CharConstants.h)>" "<Salary>" "<Role>" // Tip: "Role" is elective(is for only Doctors, builders and Professors) 
- login "<Name>" "<pNumber>"
     * print
     * addIllness <Name of illness from Illnesses.h>
     * changeSalary <Double value>
  ```
# Console input for category "Buildings":
  ```
- print
- create "<Name>" "<Area>" "<Type of building(CharConstants.h)>" "<Relevance(from 0-100)>" "Location"
- login "<Name>" 
  ```
## Bar        
  ```
- addBartender "<Personal number of already created bartender>"
- addDrink "<Name>" "<Alcohol Percentage(int 0 - 100)>" "Cost(Double positive)"
- pour "<Personal Number of person>" "<Name of drink>"
- print
```  
## Hospital                                                                                                                 
```                                                                                                                 
- print
- addDoctor "<Personal number of already created doctor>"
- cure "<Personal number of doctor>" "<Personal number of patient>" "<Name of illness from Illnesses.h>"
```
## University                                                                                                                 
```                                                                                                                
- print
- addProfessor "<Personal number of already created professor>"
- giveNewSpecialisation "<Personal number of professor>" "<Personal number of student>" "<Role to be obtained (CharConstants.h>)"
 ```                                                                                                           
