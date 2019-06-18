Aplicatia e impartita in 2
->main.cpp in care declaram  obiecte ale clasei "MyMatrix" si in care facem operatii cu acestea. Source.cpp mai contine si un bloc de tip try-catch care afiseaza diferitele erori umane in folosirea aplicatiei
->MyMatrix.h: header in care sunt declarate si definite metodele si membrii necesari
 
Observatii:

	1)Pt a evita crearea a 2 clase si duplicarea codului(una pt matrici de tip int si alta pt cele de tip float) am folosit un template adresat clasei MyMatrix

	2)Nu am  folosit un .cpp separat pt definirea  elementelor din clasa MyMatrix pt ca am folosit template-uri care nu permit acest lucru 

	3) Chiar daca matricile sunt tablouri bidimensionale, am ales sa le reprezint printr-un vector unidimensionl( in memorie sunt stocate la fel si astfel eficientizez timpul de lucru cu acestea prin accesul mai rapid la elemente)

Clasa MyMatrix:

Membrii:

->Contine 2 intregi care stocheaza dimensiunile matricilor
->un pointer de tip T(template, care poate fi int sau float) *A in care se stocheaza matricea 
->un pointer T *Tr in care se stocheaza matricea transpusa, daca utilizatorul o cere( acesta e initializat  in momentul  calculului transpusei)
-> un pointer *Inv in care e stocata matricea inversa
Toti acesti membrii sunt de tip private( utilizatorul nu ii poate accesa direct)

Metode:

-> constructori+ destructori
-> metode de tip Get si Set pt  preluarea sau setarea anumitor parametrii in obiect care sa nu afecteze matricea (se poate modifica un element A[i][j] din matrice, dar nu se pot modifica  numarul de linii sau de coloane)
-> metode care afiseaza matriciile din obiect (A,Tr,Inv)
->operatori supraincarcati care realizeaza operatii cu matrici (=,+,-,*,+=,-=,==,!=)
->metode folosite pt calculul matriciilor Tr sau Inv
Nota:Aceste metode sunt de tip public 


	Functiile membre folosite pt supraincarcarea operatorilor:
	
Operatori aritmetici si de atribuire:+,-,*,+=,-=

	Acestea actioneaza in 2 etape:
	1)Verifica daca operatia respectiva se poate executa (pt operatorul + se verifica daca cele 2 matrici au aceleasi dimensiuni, pt * se verifica dimensiunile liinilor si coloanelor celor 2 matrici, etc.)
          In caz de nerespectare a acestor  reguli se arunca un mesaj informativ utilizatorului
		ALTFEL
	Se sare la pasul 2
	
	2)Se executa operatia in sine si se returneaza rezultatul

	Observatie:
	
	La algoritmul de inmultire a 2 matrici, cea mai rapida metoda avea complexitatea O(n^82), insa putea calcula doar produsul intre 2 matrici patratice, pt matrici dreptunghiulare se foloseste algoritmul clasic cu O(n^3), eficientizat prin alocarea mai rapida a variabilelor in memorie sau in registrii procesorului
        De asemenea, operatorul * e supraincarcat cu 2 metode, una pt produsul intre 2 matrici, iar cealalata pt produsul dintre un scalar si o matrice

Operatori relationari:!=, ==
 
 1)Se verifica dimensiunile, daca acestea difera se returneaza false
 ALTFEL
 2) Se verifica element cu element din matrice, iar in caz de inegalitate se returneaza false, ALTFEL true

 
	
  Metoda Transposed()
   
  Aceasta aloca in memoria heap vectorul Tr de dimensiuni Linie*Coloana si  trece in acesta transpusa matricii A dupa formula:
  Tr[j * Colomns + i] = A[i * Rows + j];

   Metoda Inverse()
  Aceasta folsoseste alte 3 functii: una pt calculul determinantului, alta pt  calculul determinantilor folositi la dezvoltarea dupa o linie sau coloana si alta pt calculul matricei adjuncte
  Pasi:
  1) VErifica daca matricea e patratica (NU: arunca mesaj de informare utilizatorului, DA: Sare la pasul 2)
  2)Calculeaza determinantul ( Det=0, informeaza utilizatorul ca matricea nu are inversa, Det!=0: Sare la 3)
  3)Calculeaza matricea adjuncta care va fi inmultita cu determinantul si astfel rezulta inversa

  
	In main.cpp s-au initializat mai multe obiecte pt testarea metodelor din clasa MyMatrix;  
  
