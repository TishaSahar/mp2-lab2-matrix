// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize(void)const { return Size;       } // размер вектора
  int GetStartIndex(void)const { return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos);             // доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      out << v.pVector[i] << ' ';
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s = 0, int si = 0)
{
	if ((s < 0)||(s > MAX_VECTOR_SIZE))
		throw logic_error("Size incorrect");

	if (si < 0)
		throw logic_error("Negative vector start index");

	if (si > s)
		throw logic_error("StartIndex > Size");

	Size = s;
	StartIndex = si;

	pVector = new ValType[Size];
	for (int i = 0; i < Size; i++)
	{
		pVector[i] = (ValType)0;
	}
} 

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	Size = v.Size;
	StartIndex = v.StartIndex;

	pVector = new ValType[Size];
	for (int i = 0; i < Size; i++)
		pVector[i] = v.pVector[i];
}

template <class ValType>
TVector<ValType>::~TVector()
{
	delete[] pVector;
}

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
	if (pos < StartIndex)
		throw logic_error("Negative index");
	if ((pos - StartIndex) >= Size)
		throw logic_error("Too large index");

	return pVector[pos - StartIndex];
}

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
	if (Size != v.Size)
		return false;

	for (int i = StartIndex; i < Size; i++)
		if (pVector[i] != v.pVector[i])
			return false;

	return true;
}
template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
	if (Size != v.Size)
		return true;

	for (int i = StartIndex; i < Size; i++)
		if (pVector[i] != v.pVector[i])
			return true;

	return false;
}

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	if (this != &v) {
		if (Size != v.Size) {
			delete[] pVector;
			pVector = new ValType[v.Size];
		}
		Size = v.Size;
		StartIndex = v.StartIndex;
		for (int i = 0; i < Size; i++) pVector[i] = v.pVector[i];
	}
	return *this;
}

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	for (int i = StartIndex; i < Size; i++)
	{
		pVector[i] += val;
	}

	return *this;
}

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	for (int i = StartIndex; i < Size; i++)
	{
		pVector[i] -= val;
	}

	return *this;
}

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	for (int i = StartIndex; i < Size; i++)
	{
		pVector[i] *= val;
	}

	return *this;
}

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{

	if (Size != v.Size)
		throw logic_error("No eq size");
	if (StartIndex != v.StartIndex)
		throw logic_error("No eq start index");
	TVector<ValType> res(Size, StartIndex);

	for (int i = StartIndex; i < Size; i++)
	{
		res.pVector[i] = pVector[i] + v.pVector[i];
	}

	return res;
}

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if (Size != v.Size)
		throw logic_error("No eq size");
	if (StartIndex != v.StartIndex)
		throw logic_error("No eq start index");
	TVector<ValType> res(Size, StartIndex);

	for (int i = StartIndex; i < Size; i++)
	{
		res.pVector[i] = pVector[i] - v.pVector[i];
	}

	return res;
}

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{

	if (Size != v.Size)
		throw logic_error("No eq size");
	if (StartIndex != v.StartIndex)
		throw logic_error("No eq start index");
	ValType res = (ValType)0;

	for (int i = StartIndex; i < Size; i++)
	{
		res = res + (pVector[i] * v.pVector[i]);
	}

	return res;
}


// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание

  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s)
{
	if (s < 0 || s > MAX_MATRIX_SIZE)
		throw logic_error("Invalid value for the Size of matrix");

	for (int i = 0; i < s; i++)
	{
		TVector<ValType> temp(s - i, i);
		this->pVector[i] = temp;
	}
}

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
  TVector<TVector<ValType> >(mt) 
{
}
	
template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) 
{
}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	if (this->Size != mt.Size)
		return false;

	for (int i = 0; i < this->Size; i++)
		if (this->pVector[i] != mt.pVector[i])
			return false;

	return true;
}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	if (this->Size != mt.Size)
		return true;

	for (int i = 0; i < this->Size; i++)
		if (this->pVector[i] != mt.pVector[i])
			return true;

	return false;
}

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	if (this == &mt)
	{
		return *this;
	}

	if (this->Size != mt.Size)
	{
		delete[] this->pVector;
		this->Size = mt.Size;
		this->pVector = new TVector<ValType>[this->Size];
	}
	this->StartIndex = mt.StartIndex;

	for (int i = 0; i < this->Size; i++)
		this->pVector[i] = mt.pVector[i];

	return *this;
}

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	if (mt.GetSize() != this->GetSize())
		throw logic_error("Not eq Size in matrix +");
	TMatrix res(GetSize());
	for (int i = 0; i < this->GetSize(); i++)
		res.pVector[i] = this->pVector[i] + mt.pVector[i];

	return res;
}

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	if (mt.GetSize() != this->GetSize())
		throw logic_error("Not eq Size in matrix +");

	TMatrix res(GetSize());
	for (int i = 0; i < GetSize(); i++)
		res.pVector[i] = this->pVector[i] - mt.pVector[i];

	return res;
}

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
