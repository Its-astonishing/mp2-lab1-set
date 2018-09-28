// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len) : BitLen(len)
{
    if (len < 0)
        throw("NEGATIVE LENGTH");
    MemLen = (len % SIZE == 0) ? len / SIZE : len / SIZE + 1;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
    BitLen = bf.GetLength();
    MemLen = bf.MemLen;
    pMem = new TELEM[MemLen];
    for (int i = 0; i < MemLen; i++)
        pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
    delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
    if (n < 0)
        throw("NEGATIVE LENGTH");
    if (n > BitLen)
        throw("TOO LARGE");
    return n / SIZE;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
    if (n < 0)
        throw("NEGATIVE LENGTH");
    return (1 << n % (SIZE));
}

//доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
    return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
    if (n < 0)
        throw("NEGATIVE LENGTH");
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
    if (n < 0)
        throw("NEGATIVE LENGTH");
    pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] & ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
    if (n < 0)
        throw("NEGATIVE LENGTH");
    return (pMem[GetMemIndex(n)] >> (n % SIZE)) & 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
    if (bf.GetLength() == BitLen)
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    else
    {
        delete[] pMem;
        MemLen = bf.MemLen;
        BitLen = bf.BitLen;
        pMem = new TELEM(MemLen);
        for (int i = 0; i < MemLen; i++)
            pMem[i] = bf.pMem[i];
    }
    return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
    if (BitLen != bf.GetLength())
        return 0;
    for (int i = 0; i < bf.MemLen; i++)
        if (pMem[i] != bf.pMem[i])
            return 0;
    return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
    return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
    TBitField tmp(0);
    if (BitLen > bf.GetLength())
        tmp = *this;
    else
        tmp = bf;
    for (int i = 0; i < MemLen && i < bf.MemLen; i++)
        tmp.pMem[i] = pMem[i] | bf.pMem[i];
    return tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
    TBitField tmp(0);
    if (BitLen > bf.GetLength())
        tmp = *this;
    else
        tmp = bf;
    for (int i = 0; i < MemLen && i < bf.MemLen; i++)
        tmp.pMem[i] = pMem[i] & bf.pMem[i];
    return tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
    TBitField tmp(*this);
    for (int i = 0; i < BitLen; i++)
        if (tmp.GetBit(i))
            tmp.ClrBit(i);
        else
            tmp.SetBit(i);
    return tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
    string str;
    istr >> str;
    int i = str.size() - 1;
    for (auto c : str)
    {
        if (c == '1')
            bf.SetBit(i);
        else
            bf.ClrBit(i);
        i--;
    }
    return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
    for (int i = bf.BitLen - 1; i >= 0; i--)
        ostr << bf.GetBit(i);
    return ostr;
}
