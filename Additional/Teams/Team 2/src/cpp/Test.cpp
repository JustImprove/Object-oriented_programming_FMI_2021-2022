#include "DataBase.h"

// P.s: all names of specialisations, types are placed in "CharConstants.h"
// P.s 2: User can perform only 1 task after logging-in. Then, the program will propose to start from choosing the sections: people, buildings

/* Code Examples
    1) create "Dan" "1234" "Builder" "232322" "Medical"
        2) login "Dan" "1234"
        2.1) addIllness "Cancer"
    3) create "Mike" "12345" "Doctor" "4323" "Oncologist"
    (Buildings section) 4) create "1234" "Example" "152" "Medical" "100" "Undefined Street 17"
        5) login "Example" 
        5.1) addDoctor "12345"
    (6) cure "12345" "1234" "Cancer"
*/

int main() 
{
    try
    {
        DataBase Test;
        Test.Execute();
    }
    catch(const std::exception& ex)
    {
        std::cerr << ex.what() << '\n';
    }
}