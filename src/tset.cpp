//ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП

//tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//  Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)

//Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
    if (mp < 0)
        throw("NEGATIVE POWER");
    MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.MaxPower)
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
    MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
    return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    if (Elem < 0 || Elem > MaxPower)
        throw("ERROR");
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
    if (Elem < 0 || Elem > MaxPower)
        throw("ERROR");
    BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
    if (Elem < 0 || Elem > MaxPower)
        throw("ERROR");
    BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
    MaxPower = s.MaxPower;
    BitField = s.BitField;
    return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
    return BitField != s.BitField;
}

TSet TSet::operator+(const TSet &s) // объединение
{
    TSet tmp(*this);
    tmp.BitField = BitField | s.BitField;
    tmp.MaxPower = tmp.BitField.GetLength();
    return tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
    if (Elem < 0 || Elem > MaxPower)
        throw("ERROR");
    TSet ts(MaxPower);
    ts.BitField.SetBit(Elem);
    return ts;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
    if (Elem < 0 || Elem > MaxPower)
        throw("ERROR");
    TSet ts(MaxPower);
    ts.BitField.ClrBit(Elem);
    return ts;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
    TSet tmp(*this);
    tmp.BitField = BitField & s.BitField;
    tmp.MaxPower = tmp.BitField.GetLength();
    return tmp;
}

TSet TSet::operator~(void) // дополнение
{
    TSet tmp(*this);
    tmp.BitField = ~tmp.BitField;
    return tmp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
    string str;
    istr >> str;
    int i = str.size() - 1;
    for (auto c : str)
    {
        if (c == '1')
            s.BitField.SetBit(i);
        else
            s.BitField.ClrBit(i);
        i--;
    }
    return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
    for (int i = s.MaxPower - 1; i >= 0; i--)
        ostr << s.BitField.GetBit(i);
    return ostr;
}
