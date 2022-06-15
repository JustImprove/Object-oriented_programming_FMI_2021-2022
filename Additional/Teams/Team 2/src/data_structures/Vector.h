#pragma once
#include <iostream>

template<class T>
class Vector 
{
    public: 
        // Copy & move-semantics
        Vector() {Size = Capacity = 0; Collection = nullptr;}; 
        Vector(size_t Capacity) : Size(0), Capacity(0), Collection(nullptr) {Resize(Capacity);}; 
            Vector(const Vector& other) {Copy(other);}; 
            Vector(Vector&& other) {Move(std::move(other));}; 
        Vector& operator=(const Vector& other); 
        Vector& operator=(Vector&& other); 
            ~Vector() {Free();};

        // Resizing
        void Reserve(size_t Size) {Resize(Size);}; 
        void ShrinkToFit(); 
        void Clear() {Free(); Size = Capacity = 0;}; 

        // Editing data
            T& operator[](size_t Index);
            const T& operator[](size_t Index) const;
        void Push_Back(const T& Element); 
        void Pop_Back(); 
        void Push_Front(const T& Element); 
        void Pop_Front(); 
        void Insert(size_t Index, const T& Element);
        void Erase(size_t Index); 
        void Swap(size_t FirstIndex, size_t SecondIndex); 

        // Status
        bool isExisted(const T& Element) const; 
        size_t GetSize() const {return Size;};
        size_t GetCapacity() const {return Capacity;};
        bool isEmpty() const {return (Size == 0);};
        size_t End() const {return (Size >= 1) ? (Size - 1) : Size;}; // Return's index of the last added element 

    private: 
        T* Collection;
            size_t Size;
            size_t Capacity;
        void Move(Vector&& other); 
        void Copy(const Vector& other); 
            void Free() {delete[] Collection; Collection = nullptr;};
        void Resize(size_t ExtendOn = 6); // It'll be used for deleting elements 
};

#pragma region Copy & move-semantics
template<class T>
void Vector<T>::Move(Vector<T>&& other) 
{
    Size = other.Size;
    Capacity = other.Capacity;
    Collection = other.Collection;
        other.Size = other.Capacity = 0;
        other.Collection = nullptr;
}

template<class T>
void Vector<T>::Copy(const Vector<T>& other) 
{
    Size = other.Size;
    Capacity = other.Capacity;
        Collection = new T[Size];
    for (size_t i = 0; i < Size; i++)
    {
        Collection[i] = other.Collection[i];
    }
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) 
{
    if(this != &other) 
    {
        Free();
        Copy(other);
    }
        return *this;
}

template<class T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) 
{
    if(this != &other) 
    {
        Free();
        Move(std::move(other));
    }
        return *this;
}

#pragma endregion

#pragma region Resizing
template<class T>
void Vector<T>::ShrinkToFit() 
{
    if(Size < Capacity)
    {
            T* Buffer = new T[Size];
        for (size_t i = 0; i < Size; i++)
        {
            Buffer[i] = Collection[i];
        }
            delete[] Collection;
        Collection = Buffer;
            Capacity = Size;
    } 
}

template<class T>
void Vector<T>::Resize(size_t ExtendOn) 
{
        T* Buffer = new T[Capacity += ExtendOn];
    for (size_t i = 0; i < Size; i++)
    {
        Buffer[i] = Collection[i];
    }
    delete[] Collection;
        Collection = Buffer;
}

#pragma endregion

#pragma region Editing data
template<class T>
T& Vector<T>::operator[](size_t Index) 
{
    if(Index >= Size)
        throw std::out_of_range("\nIndex of range exception\n");
    
    return Collection[Index];
}

template<class T>
const T& Vector<T>::operator[](size_t Index) const
{
    if(Index >= Size)
        throw std::out_of_range("\nIndex of range exception\n");
    
    return Collection[Index];
}

template<class T>
void Vector<T>::Swap(size_t FirstIndex, size_t SecondIndex) 
{
    if(FirstIndex < Capacity && SecondIndex < Capacity) 
    {
            T Temp = Collection[FirstIndex];
        Collection[FirstIndex] = Collection[SecondIndex];
        Collection[SecondIndex] = Temp;  
    }
    else
        throw std::out_of_range("\nIndex of range exception\n"); 
}

template<class T>
void Vector<T>::Push_Back(const T& Element) 
{
    if(Size == Capacity) 
        Resize(); 

    Collection[Size++] = Element;
}

template<class T>
void Vector<T>::Pop_Back() 
{
    if(Size == 0)
        throw std::logic_error("\nThere is no elements to be deleted\n");

    Size--;
}

template<class T>
void Vector<T>::Push_Front(const T& Element) 
{
    if(Size == Capacity)
        Resize();

    for (size_t i = 0; i < Size; i++)
    {
        Swap(i, Size);
    }
        Collection[0] = Element;
    Size++;
}

template<class T>
void Vector<T>::Pop_Front() 
{
    for (size_t i = 0; i < (Size - 1); i++)
        Swap(i, i + 1);

    Size--;
}

template<class T>
void Vector<T>::Insert(size_t Index, const T& Element) 
{
    if(Index >= Size)
        throw std::out_of_range("\nIndex of range exception\n");

    if(Size == Capacity)
        Resize();

    for (size_t i = Index; i < Size; i++)
        Swap(i, Size);

    Collection[Index] = Element;
        Size++;
}

template<class T>
void Vector<T>::Erase(size_t Index) 
{
    if(Index >= Size)
        throw std::out_of_range("\nIndex of range exception\n");

    for (size_t i = Index; i < (Size - 1); i++)
        Swap(i, i + 1);
    
    Pop_Back();
}

#pragma endregion

#pragma region Streams 
template<class T>
std::ostream& operator<<(std::ostream& Stream, Vector<T>& Vec) 
{
    int Size = Vec.GetSize();
        Stream << "{ ";
    for (size_t i = 0; i < Size; i++)
    {
            Stream << Vec[i];
        if((i + 1) < Size)
            Stream << ", ";
        else
            Stream << " }";
    }
        return Stream;
}

template<class T>
std::istream& operator>>(std::istream& Stream, Vector<T>& Vec) 
{
        T Element;
    while(Stream >> Element) 
        {Vec.Push_Back(Element);};
    return Stream;
}

#pragma endregion

#pragma region Status 
template<class T>
bool Vector<T>::isExisted(const T& Element) const 
{
    for (size_t i = 0; i < Size; i++)
    {
        if(Collection[i] == Element)
            return true;
    }   
        return false;
}

#pragma endregion
