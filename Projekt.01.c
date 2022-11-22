#include<stdio.h>
#include <stdlib.h> // zeby moc losowac na funkcji rand
#include <time.h> //zeby moc mierzyc czas

int szukaj(int mfw, int nfw, int **tablica2d)
{
int ii=0;
int jj=0;
int suma=0;
for(ii=1;ii<mfw-1;ii++){ /* szukamy i =1, jesli znajdziemy przchodzinmy dalej */

 	for(jj=1;jj<nfw-1;jj++){  /* szukamy j =1, jesli znajdziemy przchodzinmy dalej */
 	 /*sprawdzamy czy wokol znalezionej 1 sa odpowiednio ulozone 0 i 1. jesli tak zwiekszamy sume o jeden*/
 		if((tablica2d)[ii-1][jj-1]!=1 && (tablica2d)[ii-1][jj]==1 
		&& (tablica2d)[ii-1][jj+1]!=1 && (tablica2d)[ii][jj-1]==1 
		&& (tablica2d)[ii][jj]==1 && (tablica2d)[ii][jj+1]==1 
		&& (tablica2d)[ii+1][jj-1]!=1 && (tablica2d)[ii+1][jj]==1 
		&& (tablica2d)[ii+1][jj+1]!=1 && (ii==mfw-2 || (tablica2d)[ii+2][jj]!=1)
		&& (ii==1 ||(tablica2d)[ii-2][jj]!=1) && (jj==1 ||(tablica2d)[ii][jj-2]!=1) 
		&& (jj==nfw-2 ||(tablica2d)[ii][jj+2]!=1)){
		
 			suma++; 
		} 
	} 
}

return suma;
}


int main()
{
int tmp;
int **TAB2D; /*deklaracja tablicy 2D*/
int SUMA=0;
int M=0, N=0, k;
int i=0, j=0, losowa=0;
printf("jesli chcesz wczytywac z pliku wcisnij 1, jesli z klawiatury wcisnij 0\n");
scanf("%d", &k);
while(k<2){
	
	//opcja czytania z klawiatury
	if(k==0){
		SUMA=0;    
		
		/*podajemy ROZMIAR TABLICY*/
		printf("podaj ilosc wierszy: ");
		scanf("%d", &M);  
		printf("\n");
		printf("podaj ilosc kolumn: ");
		scanf("%d", &N);
		printf("\n");

		// alokacja pamięci
		TAB2D = (int **)calloc(M+1, sizeof(int *));
		for (j=0;j<M;j++){
			TAB2D[j]=(int *)calloc(N+1,sizeof(int));
		}

		srand(time(NULL));   /*LOSUJEMY */
		for(i=0; i<M; i++){
			for(j=0; j<N; j++){
				losowa = rand()%2; /*losujemy liczby do tablicy od 0-1*/
				TAB2D[i][j] = losowa;
				printf("%d ",TAB2D[i][j]);
			}
			printf("\n");
		}             
	}

	//opcja czytania z pliku
	if(k==1){
		SUMA=0;
		FILE *plik;
		
    	//otwieramy plik i skanujemy dwie piwerwsze cyfry(rozmiary tablic)
    	if((plik = fopen("liczby.txt", "r")) == NULL)
        	exit(1);

    	if(fscanf(plik, "%d %d", &M, &N) != 2)
			exit(1);
		
		fclose(plik);
		
		//alokujemy pamiec
		TAB2D = (int **)calloc(M, sizeof(int *));
		for (j=0;j<M;j++){
			TAB2D[j]=(int *)calloc(N,sizeof(int));
		}
		//znowu otwieramy plik 
		if((plik = fopen("liczby.txt", "r")) == NULL)
        exit(1);

		if(fscanf(plik, "%d %d", &M, &N) != 2)
		exit(1);

    	for(i=0; i<M; i++)
        	for(j=0; j<N; j++){
        		if(fscanf(plik, "%d", &tmp) != 1)exit(1);
					TAB2D[i][j]=tmp;	
			}
            
		fclose(plik);

    	for(i=0; i<M; i++){
        	for(j=0; j<N; j++)
            	printf ("%d ", TAB2D[i][j]);
        		printf("\n"); 
    	}
    } 

	// zaczynamy mierzyc czas
    clock_t start = clock();

	//wykonujemy funkcje wyszukujaca plusy i wyswietlamy wynik 
	printf("ilosc plusuow to %d\n", szukaj(M,N,TAB2D));
	
	// przestajemy mierzyć czas i obliczamy roznice
    clock_t end = clock();
    double diff= end-start;
    double elapsed = diff/CLOCKS_PER_SEC;     
    
    //wyswietlamy zmierzony czas
    printf("zmierzony czas: %.3f sekund.\n", elapsed);
	
	//otwieramy plik aby moc zapisac wynik w pliku
	FILE *plik;
	if((plik=fopen("wyniki.txt", "w"))==NULL){
		printf("cos poszlo nie tak");
		exit(1);
	}
	//zapisujemy do pliku ilosc plusow i czas
    fprintf(plik, "ilosc plusow to %d \n czas wykonania algorytmu to %.3f  ",szukaj(M,N,TAB2D), elapsed);  
	fclose(plik);  /*zamykamy plik*/        
	 
	 //zwalniamy pamiec
	for(i = 0; i < M; i++){free(TAB2D[i]);} free(TAB2D);           
		printf("jesli chcesz wczytywac z pliku wcisnij 1, jesli z klawiatury wcisnij 0\n");
		scanf("%d", &k);	

}
return 0;
}
