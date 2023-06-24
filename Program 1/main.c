#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <locale.h>

#pragma warning(disable:4996)

void CzyszczenieBufora() /*funkcja czyszczaca bufor*/
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void WczytajDziedzine(float *zakres_dolny, float *zakres_gorny) /*funkcja wczytuje dolny i gorny przedzial dziedziny*/
{
	printf("Podaj dolna granice(Liczba w formacie dziesiętnym): ");
	while ((scanf_s("%f", zakres_dolny)) != 1)
	{
		system("cls");
		puts("BLEDNE WPROWADZENIE DANYCH");
		printf("Podaj dolna granice(Liczba w formacie dziesiętnym): ");
		CzyszczenieBufora();
	}
	printf("Dolna granica przyjela wartosc: %f\n", *zakres_dolny);
	printf("Podaj gorna granice (liczba w formacie dziesiętnym wieksza od dolnej granicy): ");
	while (((scanf_s("%f", zakres_gorny))) != 1 || (*zakres_gorny<=*zakres_dolny)  )
	{
		system("cls");
		puts("BLEDNE WPROWADZENIE DANYCH");
		printf("Podaj gorna granice (liczba w formacie dziesiętnym wieksza od dolnej granicy): ");
		CzyszczenieBufora();
	}
	printf("Gorna granica przyjela wartosc: %f\n", *zakres_gorny);
}

void WczytajWspolczynniki(float *tablica_wspolczynniki) /*funkcja wczytuje wspoczynniki w kolejnosi A ,B  */
{
	int warunek_konczacy = 0;
	while (warunek_konczacy <= 1)
	{
		printf("Podaj wspolczynnik %c: ", warunek_konczacy + 65);
		while ((scanf_s("%f", (tablica_wspolczynniki + warunek_konczacy))) != 1)
		{
			system("cls");
			puts("BLEDNE WPROWADZENIE DANYCH");
			printf("Podaj wspolczynnik %c: ", warunek_konczacy + 65);
			CzyszczenieBufora();
		}
		printf("Wspolczynnik %c przyjela wartosc: %f \n", warunek_konczacy + 65, *(tablica_wspolczynniki + warunek_konczacy));
		warunek_konczacy++;
	}
}

void GenerujPrzebieg(float *tablica_wspolczynniki, float *zakres_dolny, float *zakres_gorny, float *tablica_wyniki, int wielkosc) /*funkcja generuje przebieg funkcji przy podanych parametrach*/
{
	float skok = ((*zakres_gorny) - (*zakres_dolny)) / wielkosc;
	float licznik = (*zakres_dolny);
	int miejsce = 0;
	while (miejsce < wielkosc)
	{
		*(tablica_wyniki + miejsce) = *(tablica_wspolczynniki) * (float)pow(sin(*(tablica_wspolczynniki + 1)*licznik), 2);
		licznik = licznik + skok;
		miejsce++;
	}
}

float GenerujAmplituda() /*funkcja generuje i zwraca wielkosc szumu*/
{
	float skok = (float)(rand() % 10) / 10;
	if (rand() % 2 == 1)
	{
		skok = skok*(float)(-1.0);
	}
	return skok;
}

void GenerujSzum(float *tablica_wyniki, int wielkosc) /*funkjca generuje wystepowanie szumu*/
{
	int ilosc_zaszumionych = (rand() % wielkosc)/4;
	int miejsce;
	int krok = 1;
	while (krok <= ilosc_zaszumionych)
	{
		miejsce = rand() % wielkosc;
		*(tablica_wyniki + miejsce) = *(tablica_wyniki + miejsce) + GenerujAmplituda();
		krok++;
	}

}

void ZapiszWyniki(float *tablica_wyniki, int wielkosc) /*funkcja zapisuje dane do pliku csv*/
{
	int i = 0;
	FILE *plik;
	errno_t  blad_otwarcia;
	blad_otwarcia = fopen_s(&plik, "Szum.csv", "w");
	if (blad_otwarcia == 0)
	{
		while (i < wielkosc)
		{
			fprintf(plik, "%f;", *(tablica_wyniki + i));
			i++;
		}
		fclose(plik);
	}
	else
	{
		puts("BLAD ODCZYTU PLIKU");
	}
}

void WczytajWielkoscTablicy(int *wielkosc) /*funkcja wczytujaca wielkosc tablicy*/
{
	float pobierana;
	printf("Podaj wielkosc tablicy(Liczba calkowita wieksza od 0):");

	while (scanf_s("%f", &pobierana) != 1 || (int)pobierana != pobierana)
	{
		system("cls");
		puts("BLEDNE WPROWADZENIE DANYCH");
		printf("Podaj wielkosc tablicy(Liczba calkowita wieksza od 0):");
		CzyszczenieBufora();
	}
	CzyszczenieBufora();
	*wielkosc = (int)pobierana;
	printf("Wielkosc przyjela wartosc: %d \n", *wielkosc);
}

void WczytajWyniki(float **tablica_wyniki, int *wielkosc) /*funkcja wczytujaca dane z pliku csv*/
{
	FILE *plik;
	errno_t blad_otwarcia;
	int licznik = 0;
	float *wskaznik_bezpieczenstwa;
	blad_otwarcia = fopen_s(&plik, "Szum.csv", "r");
	if (blad_otwarcia == 0)
	{
		while (1>0)
		{
			if (licznik == 0)
			{
				wskaznik_bezpieczenstwa = malloc(sizeof(**tablica_wyniki));
			}
			else
			{
				wskaznik_bezpieczenstwa = realloc(*tablica_wyniki, (licznik+1) * sizeof(**tablica_wyniki));
			}
			if (wskaznik_bezpieczenstwa != NULL)
			{
				*tablica_wyniki = wskaznik_bezpieczenstwa;
				fscanf_s(plik, "%f;", (*tablica_wyniki + licznik));
				if (feof(plik) != 0)
				{
					break;
				}
				licznik++;
			}
			else
			{
				puts("Realokacja nie powiodla sie. Wczytywanie przerwano!");
				free(tablica_wyniki);
				break;
			}
		}
		fclose(plik);
	}
	else
	{
		puts("BLAD ODCZYTU PLIKU");
	}

	*wielkosc = licznik;
}

void ZamienWartosci(float *a, float *b) /*funkcja zamienia wartosci dwoch danych*/
{
	
	float pom = *a;	
	*a = *b;	
	*b = pom;
}

void SortowanieBabelkowe(float *tablica,int wielkosc) /*funkcja sortujaca dane w tablicy metoda babelkowa*/
{
	int pozycja = 0;	
	int i=0;	
	while (pozycja < wielkosc)
	{
		for (i = 0; i < wielkosc-1; i++)
		{
			if (*(tablica + i) > *(tablica + i + 1))
			{
				ZamienWartosci((tablica + i), (tablica + i + 1));
			}
		}
		pozycja++;
	}
}

float LiczSrednia(float *tablica, int wielkosc) /*funkjca liczy i zwraca wartosc sredniej z tablicy*/
{
	int i;
	float srednia = 0;
	float suma = 0;
	for (i = 0; i < wielkosc; i++)
	{
		suma = suma + *(tablica + i);
		
	}
	srednia = suma / wielkosc;
	return srednia;
}

void FiltrujPrzebieg(float *tablica_wyniki, int wielkosc, int wybor) /*funkcja odszumia zaszumiony sygnal dla wybor==1 metoda medianowa dla wybor !=1 metoda sredniej*/
{
	int szerokosc_okna = 0;
	int pozycja = 0;
	int i = 0;
	int srodek = 0;
	float *tablica_przefiltrowana=malloc(sizeof(float)*wielkosc);
	float *tablica_okno;
	
	puts("Podaj szerokosc okna w formacie 2n+1 dla n calkowitego:");
	scanf_s("%d", &szerokosc_okna);
	if (szerokosc_okna % 2 == 0)
	{
		puts("Podana szerokosc okna nie jest liczba nieparzysta. Filtracja nieudana.");
	}
	else
	{				
		srodek = 1 + (szerokosc_okna / 2);
		tablica_okno = malloc(sizeof(float)*szerokosc_okna);
		while (pozycja < srodek-1)
			{
			*(tablica_przefiltrowana + pozycja) = *(tablica_wyniki + pozycja);
			pozycja++;
			}
		pozycja = 0;
		while (pozycja < wielkosc - (szerokosc_okna - 1))
		{
				for (i = 0; i < szerokosc_okna; i++)
				{
					*(tablica_okno + i) = *(tablica_wyniki + pozycja + i);
				}
				if (wybor==1)
				{
					SortowanieBabelkowe(tablica_okno, szerokosc_okna);
					*(tablica_przefiltrowana + pozycja + (srodek - 1)) = *(tablica_okno + (srodek - 1));
					
				}
				else
				{
					*(tablica_przefiltrowana + pozycja + (srodek - 1)) = LiczSrednia(tablica_okno, szerokosc_okna);

				}
				pozycja++;
		}
		while (pozycja<wielkosc)
		{
			*(tablica_przefiltrowana + pozycja) = *(tablica_wyniki+pozycja);
			pozycja++;
		}
		for (i = 0; i < wielkosc; i++)
		{
			*(tablica_wyniki+i) = *(tablica_przefiltrowana+i);
		}
		free(tablica_okno);
		free(tablica_przefiltrowana);
	}
}

int main()
{
	float zakres_dolny = 0.0;
	float zakres_gorny = 0.0;
	float tablica_wspolczynniki[2];
	float *tablica_wyniki = NULL;
	int wielkosc = 0;
	int warunek_konczacy = 0;
	char znak;
	char wybor;
	srand(time(NULL));
	setlocale(LC_ALL, "polish_POLAND");
	while (warunek_konczacy == 0)
	{
		
		puts("_________________________________ ");
		puts("1. Generowanie sygnału           |");
		puts("_________________________________|");
		puts("2. Zaszumiania sygnału           |");
		puts("_________________________________|");
		puts("3. Zapis sygnału do pliku .csv   |");
		puts("_________________________________|");
		puts("4. Odczyt sygnału z pliku .csv   |");
		puts("_________________________________|");
		puts("5. Filtruj zaszumiony sygnal     |"); 
		puts("_________________________________|");
		puts("6. Zamknij program               |");
		puts("_________________________________|");
		znak = getch();
		switch (znak)
		{
		case '1':

			system("cls");
			WczytajWielkoscTablicy(&wielkosc);
			tablica_wyniki = malloc(wielkosc * sizeof(float));
			WczytajDziedzine(&zakres_dolny, &zakres_gorny);
			WczytajWspolczynniki(tablica_wspolczynniki);
			GenerujPrzebieg(tablica_wspolczynniki, &zakres_dolny, &zakres_gorny, tablica_wyniki, wielkosc);
			puts("______________________");
			puts("//////////////////////");
			puts("...WYGENEROWANO SYGNAL");
			puts("//////////////////////");
			break;

		case '2':

			system("cls");
			if (tablica_wyniki == NULL)
			{
				puts("___________");
				puts("///////////");
				puts("BRAK DANYCH");
				puts("///////////");
			}
			else
			{
				GenerujSzum(tablica_wyniki, wielkosc);
				puts("____________________");
				puts("////////////////////");
				puts("...ZASZUMIONO SYGNAL");
				puts("////////////////////");
			}
			break;

		case '3':

			system("cls");
			if (tablica_wyniki == NULL)
			{
				puts("___________");
				puts("///////////");
				puts("BRAK DANYCH");
				puts("///////////");
			}
			else
			{
				ZapiszWyniki(tablica_wyniki, wielkosc);
				puts("__________________");
				puts("//////////////////");
				puts("...ZAPISANO SYGNAl");
				puts("//////////////////");
			}
			break;

		case '4':

			system("cls");
			WczytajWyniki(&tablica_wyniki,&wielkosc);
			puts("__________________");
			puts("//////////////////");
			puts("...WCZYTANO SYGNAL");
			puts("//////////////////");
			break;

		case '5':
			
			system("cls");
			if (tablica_wyniki == NULL)
			{
				puts("___________");
				puts("///////////");
				puts("BRAK DANYCH");
				puts("///////////");
			}
			else
			{
				puts("Wybierz tryb filtrowania:");
				puts("____________________________________________ ");
				puts("1. Filtrowanie medianowe                    |");
				puts("____________________________________________|");
				puts("2. Filtrowanie z uzyciem sredniej chwilowej |");
				puts("____________________________________________|");
				wybor = getch();
				switch (wybor)
				{
				case '1':
					FiltrujPrzebieg(tablica_wyniki, wielkosc, 1);
					break;
				case '2':
					FiltrujPrzebieg(tablica_wyniki, wielkosc, 0);
					break;
				default:
					puts("_________________");
					puts("/////////////////");
					puts("NIEPOPRAWNY WYBOR");
					puts("/////////////////");
					break;
				}
				puts("________________________");
				puts("////////////////////////");
				puts("...PRZEFILTROWANO SYGNAL");
				puts("////////////////////////");
			}
			break;

		case '6':

			warunek_konczacy = 1;
			break;
		default:
			puts("_________________");
			puts("/////////////////");
			puts("NIEPOPRAWNY WYBOR");
			puts("/////////////////");
			break;
		}
	}
	free(tablica_wyniki);
	return 0;
}
