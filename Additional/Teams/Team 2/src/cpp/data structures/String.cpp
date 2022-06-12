#include "String.h"
#include <cstring>
#include <cmath>

const int MAX_LINE_LENGTH = 1024;
const int DECIMAL_SYMBOLS = 5;

// "Big 4" + Move semantics
String::String(const char* Str) 
{
    Size = strlen(Str);
        this->Str = new char[Size + 1];
    strcpy(this->Str, Str);
}
String::String(size_t Val) 
{
    Size = SymbolsInValue(Val);

        Str = new char[Size + 1];
    for (size_t i = 0; i < Size; i++, Val /= 10)
        Str[(Size - 1) - i] = ((Val % 10) + '0'); // Convert from int to ascii digits 
}
void String::Copy(const String& other) 
{
    Size = other.Size;
        Str = new char[other.Size];
    strcpy(Str, other.Str);
}
void String::Move(String&& other) 
{
    Size = other.Size;
        Str = other.Str;
    other.Str = nullptr;
    other.Size = 0;
}
String& String::operator=(const String& other) 
{
    if(this != &other) 
    {
        Free();
        Copy(other);
    }
        return *this;
}
String& String::operator=(String&& other) 
{
    if(this != &other) 
    {
        Free();
        Move((String&&)other);
    }
        return *this;
}

// Operators overload
void String::operator+=(const char other) 
{   
    char* Buffer = new char[Size + 2]{};
        strcpy(Buffer, this->Str);
    Buffer[Size] = other; // FIXME: Test
        
    delete[] this->Str;
        this->Str = Buffer;
    Size += 1;
}
bool String::operator==(const String& other) const
{
    return (!strcmp(Str, other.Str));
}
char& String::operator[](unsigned int Index) const
{
    if(Index > Size)
        throw "\nError: Invalid index !\n";
        
    return Str[Index];
}
void String::operator+=(const String& other) 
{
    char* Temp = new char[Size += (other.Size + 1)];
        strcpy(Temp, Str);
    strcat(Temp, other.Str);
    
    delete[] Str;
        Str = Temp;
}
bool operator>(const String& f, const String& s) 
{
    return (f.GetSize() > s.GetSize());
}
String operator+(const String& f, const String& s) 
{
    String Result(f);
        Result += s;
    return Result;
}
std::ostream& operator<<(std::ostream& Stream, const String& str) 
{
    Stream << str.C_Str();
        return Stream;
}
std::istream& operator>>(std::istream& Stream, String& str) 
{
    char buffer[MAX_LINE_LENGTH + 1]{};
	Stream.getline(buffer, MAX_LINE_LENGTH);

	str.Free();
	str.Size = strlen(buffer);
	str.Str = new char[str.Size + 1];
	    strcpy(str.Str, buffer);

	return Stream;
}

// Additional f-tions
char* IntToString(size_t Val) 
{
    int dCount = 0; 
        size_t Temp = Val;
    while(Temp != 0) 
    {
        Temp /= 10;
        dCount++;
    }
        char* Buffer = new char[dCount + 1]{}; 
    for (size_t i = 0; i < dCount; i++)
    {
        Buffer[dCount - 1 - i] = ((Val % 10) + '0'); // Convert from int to ascii digits
            Val /= 10;
    }
        return Buffer;
}

// Functionality
void String::GetLine() 
{
    char Buffer[MAX_LINE_LENGTH + 1]{};
        std::cin.getline(Buffer, MAX_LINE_LENGTH);
    
    if(Size >= strlen(Buffer))
        strcpy(Str, Buffer);
    else 
    {
        size_t NewSize = strlen(Buffer);
            delete[] Str;
        Str = new char[NewSize + 1]{};
        strcpy(Str, Buffer);
            Size = NewSize;
    }
} 
double String::ToDouble() const
{
    char* Str = this->Str; // Pointer to perform iterations

    double Val = 0;
    int AfterDot = 0;
    double Scale = 1;
    int Neg = 0; 

    if (*Str == '-') 
    {
        Str++;
        Neg = 1;
    }
    while (*Str) 
    {
        if (AfterDot) 
        {
            Scale = Scale / 10;
            Val = Val + (*Str - '0') * Scale;
        } 
        else 
        {
            if (*Str == '.') 
                AfterDot++;
            else
                Val = Val * 10.0 + (*Str - '0');
        }
    Str++;
    }

    if(Neg) 
        return -Val;
    else    
        return Val;
}
void String::Reverse(size_t Index) 
{
        int sSize = strlen(Str);
    for (size_t i = 0, j = Index; i < (sSize - Index) / 2; i++, j++)
        Swap(Str[j], Str[sSize - i - 1]);
}
void String::Clear() 
{
    Free();
        Str = new char[1]{""};
    Size = 0;
}
size_t String::SymbolsInValue(size_t Val) const 
{
        int Counter = 0;
    while(Val != 0) 
    {
        Val /= 10;
        Counter++;
    }
        return Counter;
}
void String::Insert(const char* Str, size_t Index) 
{
    if(Index >= Size)
        return; 

        char* Buffer = new char[Size + strlen(Str) + 1]{};   
    for (size_t i = 0, j = 0; i < (Size + 1); i++)
    {   
        if(i != Index) 
        {
            Buffer[j] = this->Str[i];
                j++;
        }
        else
        {
            strcat(Buffer, Str);
                j += strlen(Str);
        }
    }
        delete[] this->Str;
    this->Str = Buffer;
}
void String::Insert(size_t Val, size_t Index) 
{
    if(Index >= Size)
        return; 

    char* Str = IntToString(Val);
        char* Buffer = new char[Size + strlen(Str) + 1]{};   
    for (size_t i = 0, j = 0; i < (Size + 1); i++)
    {   
        if(i != Index) 
        {
            Buffer[j] = this->Str[i];
                j++;
        }
        else
        {
            strcat(Buffer, Str);
                j += strlen(Str);
        }
    }
        delete[] this->Str;
    this->Str = Buffer;
        delete[] Str;
}
Vector<String> String::StrBetweenBoundaries(const char StartS, const char EndS, bool SpaceAfterEndSBeforeStartS) const
{
    String Buffer;
        Vector<String> Result;
    for (size_t i = 0; (Str[i] != '\0'); i++)
    {
        if(Str[i] == StartS) 
        {
            for (size_t j = (i + 1); j < Size; j++)
            {
                    Buffer += Str[j];
                if(Str[j + 1] == EndS) 
                {
                    if(SpaceAfterEndSBeforeStartS) // Smth like regex - to define, whether skipping EndS is needed or not 
                        i = j + 1;
                    else
                        i = j;
                    break;
                }
            }
                Result.Push_Back(Buffer);
            Buffer.Clear();
        }
    }
        return Result;
}
bool String::isExisted(const char* Str) const 
{
    size_t Length = strlen(Str);

        if(Length == 0 && Size == 0)
            return true;

        for (size_t i = 0, j = 0; i < Size; i++)
        {
            if(this->Str[i] == Str[j]) 
            {
                j++;

                if(j == Length)
                    return true; 
            } 
            else 
                j = 0; 
        }
    return false;
}