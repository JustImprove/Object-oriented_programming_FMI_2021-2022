#pragma once
#include <iostream>
#include "Vector.h" // Is crucial for below f-tion

class String 
{
    public: 
        String() : Size(0) {Str = new char[1]{""};};
        String(const char*); 
            String(const String& other) {Copy(other);};
            String& operator=(const String&); 
        String(String&& other) {Move((String&&)other);};
        String& operator=(String&&); 
            ~String() {Free();};

        // Convertations
        String(size_t Val); 
        double ToDouble() const;

        // Operators
            friend std::ostream& operator<<(std::ostream& Stream, const String& str); 
            friend std::istream& operator>>(std::istream& Stream, String& str); 
        bool operator==(const String& other) const;
        char& operator[](unsigned int Index) const; 
        void operator+=(const String& other);
        void operator+=(const char other);

        // Functionality 
        size_t GetSize() const {return Size;};
        const char* C_Str() const {return Str;};
        void Reverse(size_t Index = 0);
        void Clear();
        bool isEmpty() const {return (Size == 0);};
        size_t SymbolsInValue(size_t Val) const;
            void Insert(const char* Str, size_t Index); 
            void Insert(size_t Val, size_t Index); 
        Vector<String> StrBetweenBoundaries(const char StartS, const char EndS, bool SpaceAfterEndSBeforeStartS = 1) const; // F-tion, that will get all the data between start & end char till the str Size
        bool isExisted(const char* Str) const;
        void GetLine(); // Equivalent method to cin.getline() for custom String

    private: 
        char* Str;
        size_t Size;
            void Copy(const String&); 
            void Move(String&&); 
            void Free() {delete[] Str; Str = nullptr;};
};

// Operators
bool operator>(const String& f, const String& s); // Checks only the length
String operator+(const String& f, const String& s);

// Additional functions 
char* IntToString(size_t Val);
template<class T>
void Swap(T& First, T& Second)
{
    T Temp = First;
        First = Second;
    Second = Temp;
}