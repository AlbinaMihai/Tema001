#include"MyMatrix.h"
//dimensiunile matricilor
#define N1  2
#define N2 3
#define L1 3
#define L2 2
#define  InputFile "Date.txt"
int main(void)
{
	std::ifstream in(InputFile);
	try
	{
		// Pi1, Pi2 matrici patratice  de tip int
		//Di1, Di2 matrici dreptunghiulare de tip int 
		int  *Pi1, *Pi2, *Di1, *Di2;
		// la fel ca mai sus, cu exceptia tipului de date  care este de tip float
		float *Pf1, *Pf2, *Df1, *Df2;
		
		Pi1 = (int *)calloc(N1*N1,  sizeof(int));	
		Pi2= (int *)calloc(N2*N2, sizeof(int));
		Di1 = (int *)calloc(L1*L2, sizeof(int));
		Di2 = (int*)calloc(L2*L1, sizeof(int));
		Pf1 = (float *)calloc(N1*N1, sizeof(float));
		Pf2 = (float *)calloc(N2*N2, sizeof(float));
		Df1= (float *)calloc(L1*L2, sizeof(float));
		Df2 = (float *)calloc(L2*L1, sizeof(float));

		int i;//variabila contor pt crearea matricilor;
		
		for (i = 0; i < N1*N1; ++i)
			Pi1[i] = i;
	
		
		
		for (i = 0; i < N2*N2; ++i)
		   in>>	Pi2[i];
		
		for (i = 0; i < L1*L2; ++i)
			Di1[i] = rand() % 1000;

		for (i = 0; i < L2*L1; ++i)
			Di2[i] = 0;

		//Urmeaza initializarea matricilor de tip float:

		for (i = 0; i < N1*N1; ++i)
			Pf1[i] = (i*i-2.32)/4.62;

		
		//Construim matricea I3
		for (i = 0; i < N2*N2; ++i)
			Pf2[i] = 0;
		for(i=0;i<N2*N2;++i)
		Pf2[(N2 + 1)*i] = 1;

		for (i = 0; i < L1*L2; ++i)
			Df1[i] = (float)((rand() % 1000)/(-i-0.87));

		for (i = 0; i < L2*L1; ++i)
			Df2[i] = i/3.12334;

		MyMatrix<int> S1(Pi1, N1, N1), S2(Pi2, N2, N2), S3(Di1, L1, L2), S4(Di2, L2, L1);
		MyMatrix<float> F1(Pf1, N1, N1), F2(Pf2, N2, N2), F3(Df1, L1, L2), F4(Df2, L2, L1);
		
		S1.ShowMatrix();
		S2.ShowMatrix();
		S3.ShowMatrix();
		S4.ShowMatrix();
		F1.ShowMatrix();
		F2.ShowMatrix();
		F3.ShowMatrix();
		F4.ShowMatrix();
		 

		if (F1 == F2)
			std::cout << "Cele 2 matrici sunt egale\n";
		else
			std::cout << "Nu sunt egale\n";

		S2 = S2 * S2;
		S2.ShowMatrix();

		S3.Transposed();
		S3.ShowTransposed();

		F4 = F4*3;
		F4.ShowMatrix();

		F1 += F1;
		F1.ShowMatrix();		

		F2 -= F2;
		F2.ShowMatrix();

		S1.Inverse();
		S1.ShowInverse();

		//Exceptii care pot aparea in aplicate:
		
		F3.ShowInverse();
		S1 = S2 * S1;
		F1 += F3;
		S3 -= S1;

	}
	catch (const char* s)
	{
		std::cout << s << '\n';
	}

	system("pause");
}

