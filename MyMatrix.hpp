#ifndef MYMATRIX_HPP_INCLUDED
#define MYMATRIX_HPP_INCLUDED

#pragma once
#include<iostream>
#include<fstream>
#include<cstdlib>
template <typename T>
class MyMatrix
{
private:
	int Rows;
	int Colomns;
	T *A;//Matricea
	T *Tr;//Transpusa acesteia
	float *Inv;//Inversa
public:

	MyMatrix() { throw("Introduceti, va rog, matricea"); }
	MyMatrix(int L, int C)
	{

		Rows = L;
		Colomns = C;

		A = (T *)calloc(Rows*Colomns, sizeof(T));
		if (A == NULL)
			throw("Eroare la alocarea matricii! :(");


	}
	MyMatrix(T *S,int L, int C):MyMatrix(L,C)
	{
		for (int i = 0; i < Rows*Colomns; ++i)
			A[i] = S[i];

	}
   
    ~MyMatrix()
  {

	  free(A);

	}
	int GetRowsNr() { return Rows; }
	int GetColomnsNr() { return Colomns; }
	T GetElement(int L, int C) { return A[L*Colomns+C]; }
	void SetElemnt(int L, int C, T NewValue) { A[L*Colomns +C] = NewValue; }
	void ShowMatrix()
	{
		int i, j;
		for (i = 0; i < Rows; ++i)
		{
			std::cout << '\n';
			for (j = 0; j < Colomns; ++j)
				std::cout << A[i*Colomns+j] << " ";
		}
		std::cout << "\n";
	}
	void ShowTransposed()
	{
		register int i, j;

		for (i = 0; i < Colomns; ++i)
		{
			std::cout << '\n';
			for (j = 0; j < Rows; ++j)
				std::cout << Tr[i*Rows + j] << " ";
		}
		std::cout << "\n";
	}
	void ShowInverse()
	{
		if (!Inv)
			throw("Matricea inversa nu a fost calculata!\n");

		int i, j;
		int N = Rows;
		for (i = 0; i < N; ++i)
		{
			std::cout << '\n';
			for (j = 0; j < N; ++j)
				std::cout << Inv[i*N + j] << " ";
		}

		std::cout << "\n";
	}
	void Transposed()
	{
		Tr=(T *)calloc(Rows*Colomns, sizeof(T));

		for (int i = 0; i < Colomns; ++i)
			for (int j = 0; j < Rows; ++j)
				Tr[j * Colomns + i] = A[i * Rows + j];


	}
	MyMatrix& operator=(const MyMatrix & B)
	{
		if (this == &B)
			return *this;

		if (this->Rows != B.Rows || this->Colomns != B.Colomns)
			throw("Nu se poate asigna valoarea matricii respective. Dimensiunile acestora difera!\n");

		int i;
		for (i = 0; i < this->Rows*this->Colomns; ++i)
			A[i] = B.A[i];


		return *this;
	}
	const MyMatrix operator+(const MyMatrix& B) const
	{

		if (this->Rows != B.Rows || this->Colomns != B.Colomns)
			throw("Nu s-a putut realiza suma matricilor, acestea sunt de dimensiuni diferite :(\n");

		MyMatrix<T> Sum(this->Rows, this->Colomns);
		int i;
		for (i = 0; i < this->Rows*this->Colomns; ++i)
				Sum.A[i] = T(this->A[i] + B.A[i]);

		return Sum;
	}
	const MyMatrix& operator+=(const MyMatrix& B)
	{
		if (this->Rows != B.Rows || this->Colomns != B.Colomns)
			throw("Nu s-a putut realiza suma matricilor, acestea sunt de dimensiuni diferite :(\n");

		int i;

		for (i = 0; i < this->Rows*this->Colomns; ++i)
			this->A[i] = this->A[i] + B.A[i];


		return *this;
	}
	const MyMatrix operator-(const MyMatrix& B) const
	{
		MyMatrix<T> Diff(this->Rows, this->Colomns);
		if (this->Rows != B.Rows || this->Colomns != B.Colomns)
			throw("Nu s-a putut realiza diferenta matricilor, acestea sunt de dimensiuni diferite :(\n");

		int i;
		for (i = 0; i < this->Rows*this->Colomns; ++i)
			Diff.A[i] = this->A[i] - B.A[i];

		return Diff;
	}
	const MyMatrix& operator-=(const MyMatrix& B)
	{
		if (this->Rows != B.Rows || this->Colomns != B.Colomns)
			throw("Nu s-a putut realiza diferenta matricilor, acestea sunt de dimensiuni diferite :(\n");

		int i;

		for (i = 0; i < this->Rows*this->Colomns; ++i)
			this->A[i] -=   B.A[i];


		return *this;
	}
	const MyMatrix operator*(const MyMatrix& B) const
	{
		if (this->Colomns != B.Rows || this->Rows != B.Colomns)
			throw("Inmultirea nu poate fi realizata!\n");

		MyMatrix<T> Mul(this->Rows, B.Colomns);

		 register int i, j, k;

		for (int i = 0; i < this->Rows; i++)
			for (int j = 0; j < B.Colomns; j++)
			{

				for (int k = 0; k < B.Rows; k++)
					Mul.A[i * B.Colomns + j] += (A[i * this->Colomns + k] * B.A[k * B.Colomns + j]);


			}

			return Mul;
	}
	const MyMatrix operator*(const T Scalar) const
	{

		MyMatrix<T> Mul(this->Rows, this->Colomns);

		register int i;

		for (i = 0; i < Mul.Rows*Mul.Colomns; ++i)
			Mul.A[i] = Scalar*A[i];

		return Mul;
	}
	bool operator ==(const MyMatrix& B) const
	{
		if (this->Rows != B.Rows || this->Colomns != B.Colomns)
			return false;

		register int i;
		for (i = 0; i < Rows*Colomns; ++i)
			if (A[i] != B.A[i])
				return false;

		return true;
	}
	inline bool operator !=(const MyMatrix&B) const
	{
		return !(operator==(B));
	}
	void GetCofactor(T *&A, T *&Temp, int p, int q, int n)
	{
		int i = 0, j = 0;
		int N = this->Rows;

		for (int row = 0; row < n; row++)
		{
			for (int col = 0; col < n; col++)
			{

				if (row != p && col != q)
				{
					Temp[i*N+j] = A[row*N+col];
					j++;

					if (j == n - 1)
					{
						j = 0;
						i++;
					}
				}
			}
		}
	}
	float GetDeterminant(T *&Aux, int n)
	{
		float D = 0; 

		
		if (n == 1)
			return Aux[0];

		T *Temp; 
		Temp = (T*)calloc(this->Rows*this->Rows, sizeof(T));
		int sign = 1;  

		 
		for (int f = 0; f < n; f++)
		{
			// Getting Cofactor of A[0][f]
			GetCofactor(Aux, Temp, 0, f, n);
			D += sign * Aux[f] * GetDeterminant(Temp, n - 1);

			// terms are to be added with alternate sign
			sign = -sign;
		}

		return D;
	}
	T * Adjoint()
	{
		int N = this->Rows;

		short sign = 1;
		T *Temp, *Adj;
		Temp = (T*)calloc(N*N, sizeof(T));
		Adj = (T*)calloc(N*N, sizeof(T));

		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < N; ++j)
			{
				GetCofactor(A, Temp, i, j, N);
				sign = ((i + j) % 2 == 0) ? 1 : -1;
				Adj[j*N+i]= (sign)*(GetDeterminant(Temp, N - 1));
			}
		}

		return Adj;
	}
	void Inverse()
	{
		if (this->Rows != this->Colomns)
			throw("Matricea nu este patratica! NU se poate calcula o invera a acesteia :(\n");


		float Det = GetDeterminant(A, this->Rows);
		if (!Det)
			throw("Matricea este singulara, nu admite invers\n");


		T *Adj=Adjoint();
		Inv = (float*)calloc(Rows*Rows, sizeof(float));

		for (int i = 0; i < this->Rows*this->Rows; ++i)
			Inv[i] = Adj[i] / (float)Det;


	}


	};

#endif // MYMATRIX_HPP_INCLUDED
