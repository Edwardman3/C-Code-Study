#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include <string.h>

#pragma warning(disable:4996)

struct obraz
{
	char tytul[100];
	char typ[3];
	int szerokosc;
	int wysokosc;
	int szarosc;
	int **piksele;
}*obrazy;

void CzyszczenieBufora() /*funkcja czyszczaca bufor*/
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void WyswietlListeObrazow(int ilosc)
{
	int licznik = 1;
	struct obraz *wybor;
	wybor = NULL;
	if (ilosc == 0)
	{
		puts("brak obrazow");
	}
	else
	{
		while (licznik <= ilosc)
		{
			wybor = (obrazy + licznik - 1);
			printf_s("%d :  %s typ: %s  \n", licznik, wybor->tytul, wybor->typ);
			licznik++;
		}
	}
	wybor = NULL;
	free(wybor);
}

void WyczyscPamiecTablicyStruktur(int ilosc_obrazow)
{
	int i;
	while (ilosc_obrazow>0)
	{
		for (i = ((obrazy + ilosc_obrazow - 1)->wysokosc) - 1; i >= 0; i--)
		{
			free((obrazy + ilosc_obrazow - 1)->piksele[i]);
		}
		free((obrazy + ilosc_obrazow - 1)->piksele);
		ilosc_obrazow--;
	}
	free(obrazy);
}

void ZapiszObraz(struct obraz *zapis)
{
	FILE* plik;
	errno_t err;
	char slowo[100];
	int i = 0;
	int j = 0;
	printf_s("Podaj nazwe obrazu wraz z rozszerzeniem .PGM:");
	scanf_s("%s", slowo, 100);
	err = fopen_s(&plik, slowo, "w");
	if (err == 0)
	{
		fprintf(plik, "%s\n", zapis->typ);
		fprintf(plik, "%d %d\n", zapis->szerokosc, zapis->wysokosc);
		fprintf(plik, "%d\n", zapis->szarosc);
		for (i = 0; i < zapis->wysokosc; i++)
		{
			for (j = 0; j < zapis->szerokosc; j++)
			{
				fprintf(plik, "%d ", zapis->piksele[i][j]);
			}
			fprintf(plik, "\n");
		}
		fclose(plik);
		puts("zapisano");
	}
	else
	{
		puts("blad odczytu");
	}
}

int DodajNowaPozycjaWTablicyStrukut(int ktory_obraz)
{
	struct obraz *wsk_pom;
	if (ktory_obraz == 1)
	{
		wsk_pom = (struct obraz*)malloc(ktory_obraz * sizeof(struct obraz));
	}
	else
	{
		wsk_pom = (struct obraz*)realloc(obrazy, ktory_obraz * sizeof(struct obraz));
	}
	if (wsk_pom != NULL)
	{
		obrazy = wsk_pom;
		wsk_pom = NULL;
		free(wsk_pom);
		return 0;
	}
	else
	{
		wsk_pom = NULL;
		free(wsk_pom);
		return 1;
	}
}

void WczytajObraz(int *ktory_obraz)
{
	FILE* plik;
	errno_t err;
	struct obraz *nowy;
	char slowo[100];
	int i = 0;
	int j = 0;
	printf_s("Podaj nowa nazwe obrazu wraz z rozszerzeniem .PGM:");
	scanf_s("%s", slowo, 100);
	err = fopen_s(&plik, slowo, "r");
	if (err == 0)
	{
		if (DodajNowaPozycjaWTablicyStrukut(*ktory_obraz) == 0)
		{
			nowy = (obrazy + *ktory_obraz - 1);
			strcpy(nowy->tytul, slowo);
			while (fscanf_s(plik, "%s", nowy->typ, 3) != 1 && nowy->typ[0] == 'P')
			{
				fgetc(plik);
			}
			while (fscanf_s(plik, "%d", &(nowy->szerokosc)) != 1)
			{
				fgetc(plik);
			}
			while (fscanf_s(plik, "%d", &(nowy->wysokosc)) != 1)
			{
				fgetc(plik);
			}
			while (fscanf_s(plik, "%d", &(nowy->szarosc)) != 1)
			{
				fgetc(plik);
			}
			nowy->piksele = (int**)malloc(nowy->wysokosc * sizeof(*nowy->piksele));
			if (nowy->piksele == NULL)
			{
				free(nowy->piksele);
				*ktory_obraz = *ktory_obraz - 1;
				while (DodajNowaPozycjaWTablicyStrukut(*ktory_obraz) != 0)
				{
					puts("Nieudana proba zmiejszenia tablicy");
				}
			}
			else
			{
				for (i = 0; i < nowy->wysokosc; i++)
				{
					nowy->piksele[i] = (int *)malloc(nowy->szerokosc * sizeof(nowy->piksele));
					if (nowy->piksele[i] == NULL)
					{
						for (j = i; j >= 0; j--)
						{
							free(nowy->piksele[j]);
						}
						free(nowy->piksele);
						*ktory_obraz = *ktory_obraz - 1;
						while (DodajNowaPozycjaWTablicyStrukut(*ktory_obraz) != 0)
						{
							puts("Nieudana proba zmiejszenia tablicy");
						}
						i = nowy->wysokosc;
					}
					else
					{
						for (j = 0; j < nowy->szerokosc; j++)
						{
							while (fscanf_s(plik, "%d", &(nowy->piksele[i][j])) != 1)
							{
								fgetc(plik);
							}
						}
					}
				}
			}
			fclose(plik);
			puts("wczytano obraz");
			nowy = NULL;
			free(nowy);

		}
		else
		{
			puts("Nie udalo sie znalezc miejsca dla nowego obrazu");
			*ktory_obraz = *ktory_obraz - 1;
		}

	}
	else
	{
		puts("BLAD ODCZYTU");
		*ktory_obraz = *ktory_obraz - 1;
	}
}

struct obraz* WybierzAktywnyObraz(int wybor_obraz, char *tytul)
{
	struct obraz* aktywny_obraz;
	aktywny_obraz = obrazy + wybor_obraz - 1;
	strcpy(tytul, aktywny_obraz->tytul);
	return aktywny_obraz;
}

void WyswietlObraz(struct obraz *aktywny)
{
	int i = 0;
	int j = 0;
	printf("%s\n", aktywny->typ);
	printf("%d %d\n", aktywny->szerokosc, aktywny->wysokosc);
	printf("%d\n", aktywny->szarosc);
	for (i = 0; i < aktywny->wysokosc; i++)
	{
		for (j = 0; j < aktywny->szerokosc; j++)
		{
			printf("%d ", aktywny->piksele[i][j]);
		}
		puts("");
	}
}

void UsunObraz(int wybor, int *ilosc_obrazow)
{
	int i = 0;
	int j = 0;
	while (wybor<*ilosc_obrazow)
	{
		for (i = ((obrazy + (wybor - 1))->wysokosc) - 1; i >= 0; i--)
		{

			free((obrazy + (wybor - 1))->piksele[i]);
		}
		free((obrazy + (wybor - 1))->piksele);
		strcpy((obrazy + (wybor - 1))->tytul, (obrazy + (wybor))->tytul);
		strcpy((obrazy + (wybor - 1))->typ, (obrazy + wybor)->typ);
		(obrazy + (wybor - 1))->szerokosc = (obrazy + wybor)->szerokosc;
		(obrazy + (wybor - 1))->wysokosc = (obrazy + wybor)->wysokosc;
		(obrazy + (wybor - 1))->szarosc = (obrazy + wybor)->szarosc;
		(obrazy + (wybor - 1))->piksele = malloc(((obrazy + wybor)->wysokosc) * sizeof(*((obrazy + wybor)->piksele)));
		for (i = 0; i < (obrazy + wybor)->wysokosc; i++)
		{
			(obrazy + (wybor - 1))->piksele[i] = malloc(((obrazy + wybor)->szerokosc) * sizeof((obrazy + wybor)->piksele));
			for (j = 0; j < (obrazy + wybor)->szerokosc; j++)
			{
				(obrazy + wybor - 1)->piksele[i][j] = (obrazy + wybor)->piksele[i][j];
			}
		}
		wybor++;
	}
	for (i = ((obrazy + wybor - 1)->wysokosc) - 1; i >= 0; i--)
	{
		free((obrazy + wybor - 1)->piksele[i]);
	}
	free((obrazy + wybor - 1)->piksele);
	*ilosc_obrazow = *ilosc_obrazow - 1;
	obrazy = (struct obraz*)realloc(obrazy, *ilosc_obrazow * sizeof(struct obraz));
}

int SzukajMax(int *tablica_histogramu, int rozmiar)
{
	int max = *tablica_histogramu;
	int max_krok = 0;
	int krok = 1;
	while (krok < rozmiar)
	{
		if (max < *(tablica_histogramu + krok))
		{
			max = *(tablica_histogramu + krok);
			max_krok = krok;
		}
		krok++;
	}
	return max_krok;
}

int ZapiszHistogramIZwrocProg(struct obraz *aktywny)
{
	
	int *tablica_histogramu;
	int i = 0;
	int j = 0;
	int wartosc=0;
	tablica_histogramu = calloc((aktywny->szarosc) + 1, sizeof(int));
	for (i = 0; i < aktywny->wysokosc; i++)
	{
		for (j = 0; j < aktywny->szerokosc; j++)
		{
			*(tablica_histogramu + (aktywny->piksele[i][j])) = *(tablica_histogramu + (aktywny->piksele[i][j])) + 1;
		}
	}
	wartosc= SzukajMax(tablica_histogramu, (aktywny->szarosc) + 1);
	free(tablica_histogramu);
	return wartosc;
}

void UtworzenieIZapisaniehistogramu(struct obraz *aktywny)
{
	FILE* plik;
	errno_t err;
	int *tablica_histogramu;
	int i = 0;
	int j = 0;
	int wartosc = 0;
	tablica_histogramu = calloc((aktywny->szarosc) + 1, sizeof(int));
	for (i = 0; i < aktywny->wysokosc; i++)
	{
		for (j = 0; j < aktywny->szerokosc; j++)
		{
			*(tablica_histogramu + (aktywny->piksele[i][j])) = *(tablica_histogramu + (aktywny->piksele[i][j])) + 1;
		}
	}
	err = fopen_s(&plik, "histogram.csv" , "w");
	if (err == 0)
	{
		for (i = 0; i <= (aktywny->szarosc); i++)
		{
			fprintf(plik, "%d; %d \n", i, tablica_histogramu[i]);
		}
		fclose(plik);	
		puts("wygenerowano csv");
	}
	else
	{
		puts("blad odczytu pliku");
	}
	free(tablica_histogramu);
}

void WykonajNegatyw(struct obraz *aktywny)
{
	int i = 0;
	int j = 0;
	for (i = 0; i<aktywny->wysokosc; i++)
	{
		for (j = 0; j<aktywny->szerokosc; j++)
		{
			(aktywny->piksele[i][j]) = (aktywny->szarosc) - (aktywny->piksele[i][j]);
		}
	}
}

int WyborKataObrotu()
{
	int kat;
	printf("Wybierz kat obrotu(90 stopni * k , gdzie k dowolna liczba calkowita):");
	while (scanf_s("%d", &kat) != 1 && kat%90!=0)
	{
		CzyszczenieBufora();
		puts("Podales zly kat");
	}
	return (kat / 90);
}

void Zamien(int *a, int *b)
{
	int pomocniczy = *a;
	*a = *b;
	*b = pomocniczy;
}

void ObrocObrazek(struct obraz *aktywny)
{
	int **tablica_przeksztalcenia;
	int i = 0;
	int j = 0;
	int krok = 0;
	int przebieg = WyborKataObrotu();
	while (krok < przebieg)
	{
		tablica_przeksztalcenia = calloc(aktywny->szerokosc, sizeof(int*));
		for (i = 0; i < aktywny->szerokosc; i++)
		{
			tablica_przeksztalcenia[i] = calloc(aktywny->wysokosc, sizeof(int));
		}
		for (i = 0; i < aktywny->szerokosc; i++)
		{
			for (j = 0; j < aktywny->wysokosc; j++)
			{
				tablica_przeksztalcenia[i][j] = aktywny->piksele[j][(aktywny->szerokosc) - 1 - i];
			}
		}
		for (i = aktywny->wysokosc - 1; i >= 0; i--)
		{
			free(aktywny->piksele[i]);
		}
		free(aktywny->piksele);
		aktywny->piksele = malloc((aktywny->szerokosc) * sizeof(*(aktywny->piksele)));
		for (i = 0; i < aktywny->szerokosc; i++)
		{
			aktywny->piksele[i] = malloc((aktywny->wysokosc) * sizeof(aktywny->piksele));
			for (j = 0; j < aktywny->wysokosc; j++)
			{
				aktywny->piksele[i][j] = tablica_przeksztalcenia[i][j];
			}
		}
		i = aktywny->wysokosc;
		j = aktywny->szerokosc;
		Zamien(&i, &j);
		aktywny->wysokosc = i;
		aktywny->szerokosc = j;
		krok++;
	}
}

void OdbijObrazek(struct obraz *aktywny)
{
	int i = 0;
	int j = 0;
	int krok = 0;
	int wybor;
	int do_zamiany1;
	int do_zamiany2;
	puts("1. Odbij wzgledem osi x");
	puts("2. Odbij wzgledem osi y");

	while (scanf_s("%d", &wybor) != 1 || wybor>2 || wybor<0)
	{
		CzyszczenieBufora();
	}
	if (wybor == 1)
	{
		wybor = (aktywny->wysokosc) / 2;
		while (krok < wybor)
		{
			for (i = 0; i<aktywny->szerokosc; i++)
			{
				do_zamiany1 = aktywny->piksele[krok][i];
				do_zamiany2 = aktywny->piksele[(aktywny->wysokosc) - 1 - krok][i];
				Zamien(&do_zamiany1, &do_zamiany2);
				aktywny->piksele[krok][i] = do_zamiany1;
				aktywny->piksele[(aktywny->wysokosc) - 1 - krok][i] = do_zamiany2;
			}
			krok++;
		}
	}
	else
	{
		wybor = (aktywny->szerokosc) / 2;
		while (krok < wybor)
		{
			for (i = 0; i<aktywny->wysokosc; i++)
			{
				do_zamiany1 = aktywny->piksele[i][krok];
				do_zamiany2 = aktywny->piksele[i][(aktywny->szerokosc) - 1 - krok];
				Zamien(&do_zamiany1, &do_zamiany2);
				aktywny->piksele[i][krok] = do_zamiany1;
				aktywny->piksele[i][(aktywny->szerokosc) - 1 - krok] = do_zamiany2;
			}
			krok++;
		}
	}
}

int ZwrocWartosc0albo255(int odcien)
{
	if (rand() % 2 == 0)
	{
		return 0;
	}
	else
	{
		return odcien;
	}
}

void ZaszumSolIPieprz(struct obraz *aktywny)
{
	int ilosc_zaszumionych = (rand() % (aktywny->szerokosc) * (aktywny->wysokosc)) / (aktywny->szerokosc) + (aktywny->wysokosc);
	int miejsce_kolumna;
	int miejsce_wiersz;
	int krok = 1;
	printf("%d\n", ilosc_zaszumionych);
	while (krok <= ilosc_zaszumionych)
	{
		miejsce_kolumna = rand() % aktywny->wysokosc;
		miejsce_wiersz = rand() % aktywny->szerokosc;
		aktywny->piksele[miejsce_kolumna][miejsce_wiersz] = ZwrocWartosc0albo255(aktywny->szarosc);
		krok++;
	}

}

void WyroznijElementy(struct obraz *aktywny)
{
	int prog = 0;
	int i = 0;
	int j = 0;
	char znak2;
	puts("Wybierz tryb wprowadzenia progu:");
	puts("_________________________________ ");
	puts("1.           Reczny              |");
	puts("_________________________________|");
	puts("2.   Z histogramu(faza testu)    |");
	puts("_________________________________|");
	znak2 = getch();
	switch (znak2)
	{
	case '1':
		system("cls");
		puts("Podaj prog:");
		while (scanf_s("%d", &prog) != 1 && prog<0 && prog>aktywny->szarosc)
		{
			puts("bledne dane");
			CzyszczenieBufora();
		}
		break;
	case '2':
		system("cls");
		prog = ZapiszHistogramIZwrocProg(aktywny);
		break;
	default:
		system("cls");
		puts("BlEDNY WYBOR");
		break;
	}
	for (i = 0; i<aktywny->wysokosc; i++)
	{
		for (j = 0; j<aktywny->szerokosc; j++)
		{
			if (aktywny->piksele[i][j] > prog)
			{
				aktywny->piksele[i][j] = 0;
			}
			else
			{
				aktywny->piksele[i][j] = aktywny->szarosc;
			}
		}
	}
}

void SortowanieBabelkowe(int *tablica, int wielkosc) /*funkcja sortujaca dane w tablicy metoda babelkowa*/
{
	int pozycja = 0;
	int i = 0;
	while (pozycja < wielkosc)
	{
		for (i = 0; i < wielkosc - 1; i++)
		{
			if (*(tablica + i) > *(tablica + i + 1))
			{
				Zamien((tablica + i), (tablica + i + 1));
			}
		}
		pozycja++;
	}
	for (i = 0; i < wielkosc; i++)
	{
		printf("%d ", tablica[i]);
	}
	puts("");
}

void FiltrujMedianowoLubGaussowo(struct obraz *aktywny,int wybor)
{
	int i = 0;
	int j = 0;
	int k = 0;
	int h = 0;
	int krok = 0;
	int srednia = 0;
	int gauss[] = { 1, 2, 1, 2, 4, 2, 1, 2, 1 };
	int szerokosc_okna=0;
	int *tablica_medianowa=NULL;
	int **piksele_pom = NULL;
	if (wybor == 1)
	{
		puts("Podaj rozmiar okna k x k gdzie k liczba nieparzysta wieksza od 2 ale mniejsza od wymiarow obrazka:");
		while (scanf_s("%d", &szerokosc_okna) != 1 && szerokosc_okna <= 2 && szerokosc_okna > aktywny->szerokosc && (szerokosc_okna > aktywny->wysokosc))
		{
			puts("Blednie podana dana");
			CzyszczenieBufora();
		}
	}
	else
	{
		szerokosc_okna = 3;
	}
	tablica_medianowa = calloc((int)pow(szerokosc_okna, 2), sizeof(int));
	if (tablica_medianowa != NULL)
	{
		piksele_pom = (int**)malloc(aktywny->wysokosc * sizeof(*piksele_pom));
		if (piksele_pom == NULL)
		{
			free(piksele_pom);
			puts("Nieudana proba realokacji");
		}
		else
		{
			for (i = 0; i < aktywny->wysokosc; i++)
			{
				piksele_pom[i] = (int *)malloc(aktywny->szerokosc * sizeof(piksele_pom));
				if (piksele_pom[i] == NULL)
				{
					for (j = i; j >= 0; j--)
					{
						free(piksele_pom[j]);
						puts("Nieudana proba realokacji");
					}
					free(piksele_pom);
					i = aktywny->wysokosc;
				}
			}
		}
		for (i = 0; i <= aktywny->wysokosc - szerokosc_okna; i++)
		{
			for (j = 0; j <= aktywny->szerokosc - szerokosc_okna; j++)
			{
				if (wybor == 1)
				{
					for (k = i; k < szerokosc_okna + i; k++)
					{
						for (h = j; h < szerokosc_okna + j; h++)
						{
							tablica_medianowa[krok] = (aktywny->piksele[k][h]);
							krok++;
						}
					}
					krok = 0;
					SortowanieBabelkowe(tablica_medianowa, (int)pow(szerokosc_okna, 2));
					piksele_pom[i + (szerokosc_okna / 2)][j + (szerokosc_okna / 2)] = tablica_medianowa[(int)pow(szerokosc_okna, 2) / 2];
				}
				else
				{
					for (k = i; k < szerokosc_okna + i; k++)
					{
						for (h = j; h < szerokosc_okna + j; h++)
						{		
							tablica_medianowa[krok] = (aktywny->piksele[k][h]) * gauss[krok];
							krok++;
						}
					}
					for (krok = 0; krok<9; krok++)
					{
						srednia = srednia + tablica_medianowa[krok];
					}
					srednia = srednia / 16;
					krok = 0;
					piksele_pom[i + (szerokosc_okna / 2)][j + (szerokosc_okna / 2)] = srednia;
				}
			}
		}
		for (i = (szerokosc_okna / 2); i < aktywny->wysokosc - (szerokosc_okna / 2); i++)
		{
			for (j = (szerokosc_okna / 2); j < aktywny->szerokosc - (szerokosc_okna / 2); j++)
			{
				(aktywny->piksele[i][j]) = piksele_pom[i][j];
			}
		}
		for (i = aktywny->wysokosc - 1; i >= 0; i--)
		{
			free(piksele_pom[i]);
		}
		free(piksele_pom);
	}
	else
	{
		puts("Nieudana proba realokacji");
	}
	
	free(tablica_medianowa);
}

int main()
{
	struct obraz *aktywny = NULL;
	int i = 0;
	int j = 0;
	int warunek_konczacy = 0;
	int ile_obrazow = 0;
	int wybor_obraz;
	char tytul[100] = { "BRAK" };
	char znak;
	char znak2;
	srand(time(NULL));
	while (warunek_konczacy == 0)
	{
		puts("_________________________________ ");
		printf("AKTYWNY OBRAZ: %s\n", tytul);
		puts("_________________________________ ");
		puts("1. Wczytaj obraz                 |");
		puts("_________________________________|");
		puts("2. Wyswietl obraz                |");
		puts("_________________________________|");
		puts("3. Zapis obraz                   |");
		puts("_________________________________|");
		puts("4. Wybor aktywnego obrazu        |");
		puts("_________________________________|");
		puts("5. Usuniecie obrazu              |");
		puts("_________________________________|");
		puts("6. Operacje na obrazach          |");
		puts("_________________________________|");
		puts("7. Zamknij program               |");
		puts("_________________________________|");
		znak = getch();
		switch (znak)
		{
		case '1':

			system("cls");
			ile_obrazow++;
			WczytajObraz(&ile_obrazow);
			system("cls");
			break;

		case '2':

			system("cls");
			if (aktywny != NULL)
			{
				WyswietlObraz(aktywny);
			}
			else
			{
				puts("_____________________");
				puts("/////////////////////");
				puts("BRAK AKTYWNEGO OBRAZU");
				puts("/////////////////////");
			}
			break;

		case '3':

			system("cls");
			if (aktywny != NULL)
			{
				ZapiszObraz(aktywny);
			}
			else
			{
				puts("_____________________");
				puts("/////////////////////");
				puts("BRAK AKTYWNEGO OBRAZU");
				puts("/////////////////////");
			}
			break;


		case '4':

			system("cls");
			if (ile_obrazow != 0)
			{
				WyswietlListeObrazow(ile_obrazow);
				printf("Podaj numer obrazu od 1 do %d: ", ile_obrazow);
				while (scanf_s("%d", &wybor_obraz) != 1 || wybor_obraz>ile_obrazow || wybor_obraz<0)
				{
					puts("BLEDNE PODANIE NUMERU OBRAZU");
					CzyszczenieBufora();
				}
				aktywny = WybierzAktywnyObraz(wybor_obraz, tytul);
				system("cls");
			}
			else
			{
				puts("____________");
				puts("////////////");
				puts("BRAK OBRAZOW");
				puts("////////////");
			}
			break;

		case '5':
			system("cls");
			if (aktywny != NULL)
			{
				UsunObraz(wybor_obraz, &ile_obrazow);
				printf("Usunieto obraz %s\n", tytul);
				strcpy(tytul, "BRAK");
				aktywny = NULL;
			}
			else
			{
				puts("_____________________");
				puts("/////////////////////");
				puts("BRAK AKTYWNEGO OBRAZU");
				puts("/////////////////////");
			}
			break;
		case '6':
			if (aktywny != NULL)
			{
				system("cls");
				puts("_________________________________ ");
				puts("1.       Wykonaj Negatyw         |");
				puts("_________________________________|");
				puts("2.      Szum Sol i Pieprz        |");
				puts("_________________________________|");
				puts("3.         Progowanie            |");
				puts("_________________________________|");
				puts("4.       Obroc Obrazek           |");
				puts("_________________________________|");
				puts("5.       Odbij Obrazek           |");
				puts("_________________________________|");
				puts("6.      Filtruj Obrazek          |");
				puts("_________________________________|");
				puts("7.     Histogram Obrazka         |");
				puts("_________________________________|");

				znak2 = getch();
				switch (znak2)
				{
				case '1':
					system("cls");
					WykonajNegatyw(aktywny);
					break;
				case '2':
					system("cls");
					ZaszumSolIPieprz(aktywny);
					break;
				case '3':
					system("cls");
					WyroznijElementy(aktywny);
					break;
				case '4':
					system("cls");
					ObrocObrazek(aktywny);
					break;
				case '5':
					system("cls");
					OdbijObrazek(aktywny);
					break;
				case '6':
					system("cls");
					puts("_________________________________ ");
					puts("1.            Gauss              |");
					puts("_________________________________|");
					puts("2.          Medianowy            |");
					puts("_________________________________|");
					znak2 = getch();
					switch (znak2)
					{
					case '1':
						system("cls");
						FiltrujMedianowoLubGaussowo(aktywny, 2);
						break;
					case '2':
						system("cls");
						FiltrujMedianowoLubGaussowo(aktywny, 1);
						break;
					default:
						system("cls");
						puts("BlEDNY WYBOR");
						break;
					}
				case '7':
					system("cls");
					UtworzenieIZapisaniehistogramu(aktywny);
					break;
				default:
					system("cls");
					puts("BlEDNY WYBOR");
					break;
				}
			}
			else
			{
				puts("_____________________");
				puts("/////////////////////");
				puts("BRAK AKTYWNEGO OBRAZU");
				puts("/////////////////////");
			}
			break;

		case '7':

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
	WyczyscPamiecTablicyStruktur(ile_obrazow);
	return 0;
}
