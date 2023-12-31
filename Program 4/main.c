#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#pragma warning(disable:4996)
#pragma warning(disable:4013)

void CzyszczenieBufora()
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

struct dane 
{
	char imie[20];
	char nazwisko[30];
	char numer[10];
	char grupa[20];
};

struct ksiazka
{
	struct ksiazka *poprzedni;
	struct dane kontakt;
	struct ksiazka *kolejny;
};

void Wczytaj(struct ksiazka **baza, int *ilosc)
{
	FILE *plik;
	errno_t blad;
	struct ksiazka *nowy = NULL;
	int i = 0;
	blad = fopen_s(&plik, "lista.csv", "r");
	if (blad == 0)
	{
		
		while (feof(plik)!=1)
		{
			nowy = malloc(sizeof(struct ksiazka));
			if (nowy != NULL)
			{
				fscanf(plik, "%[^;] ; %[^;] ; %9[^;] ; %s ", nowy->kontakt.imie, nowy->kontakt.nazwisko, nowy->kontakt.numer, nowy->kontakt.grupa);
				nowy->kolejny = NULL;
				if (*ilosc == 0)
				{
					nowy->poprzedni = NULL;
				}
				else
				{
					nowy->poprzedni = (*baza);
				}
				(*baza)->kolejny = nowy;	
				(*baza) = nowy;
				i++;
				(*ilosc)++;
				
			}
			else
			{
				puts("Blad pamiecie");
			}
		}
		fclose(plik);
		puts("Wczytano");
	}
	else 
	{
		puts("blad otwarcia pliku");
	}
	nowy = NULL;
	free(nowy);
}

void UstawNaGora(struct ksiazka **baza)
{
	while ((*baza)->poprzedni != NULL)
	{
		(*baza) = (*baza)->poprzedni;
	}
}

void UstawNaMiejsce(struct ksiazka **baza, int ktory)
{
	int licznik = 1;
	while (licznik < ktory)
	{
		(*baza) = (*baza)->kolejny;
		licznik++;
	}
}

void UstawNaDol(struct ksiazka **baza)
{
	while ((*baza)->kolejny != NULL)
	{
		(*baza) = (*baza)->kolejny;
	}
}

void WyswietlListeKontaktow(struct ksiazka *baza)
{
	int numerek =1;
	while (baza != NULL)
	{
		printf("%2d.|%20s|%30s|%10s|%20s|\n", numerek,baza->kontakt.imie, baza->kontakt.nazwisko, baza->kontakt.numer, baza->kontakt.grupa);
		baza = baza->kolejny;
		numerek++;
	}
	puts("");
}

int WyborTrybuSortowania(int tryb)
{
	char wybor;
	int warunek_konczacy = 0;
	puts("1. imie");
	puts("2. nazwisko");
	puts("3. grupa");
	puts("4. Cofnij");
	wybor = getch();
	system("cls");
	while (1>0)
	{
		switch (wybor)
		{
			case '1':
				return 1;
				break;
			case '2':
				return 2;
				break;
			case '3':
				return 3;
				break;
			case '4':
				return tryb;
				break;
			default:
				puts("Zly wybor");
				break;
		}
	}
	
}

void Sortowanie(struct ksiazka **baza,int tryb)
{
	struct ksiazka *E = NULL;
	int ilosc_zmian = 1;
	int dzialanie = 0;
	E = malloc(sizeof(struct ksiazka));
	while (ilosc_zmian != 0)
	{
		ilosc_zmian = 0;
		while ((*baza)->kolejny != NULL)
		{
			if (tryb == 1)
			{
				dzialanie = strcoll((*baza)->kontakt.imie, (*baza)->kolejny->kontakt.imie);
			}
			if (tryb == 2)
			{
				dzialanie = strcoll((*baza)->kontakt.nazwisko, (*baza)->kolejny->kontakt.nazwisko);
			}
			if (tryb == 3)
			{
				dzialanie = strcoll((*baza)->kontakt.grupa, (*baza)->kolejny->kontakt.grupa);
			}
			if (dzialanie == 1)
			{
				ilosc_zmian++;
				E = (*baza);
				if (E->poprzedni != NULL)
				{
					E->poprzedni->kolejny = E->kolejny;
				}
				E->kolejny->poprzedni = E->poprzedni;
				E->poprzedni = E->kolejny;
				E->kolejny = E->poprzedni->kolejny;
	
				E->poprzedni->kolejny = E;
				if (E->kolejny != NULL)
				{
					E->kolejny->poprzedni = E;
				}
				
			}
			if ((*baza)->kolejny != NULL)
			{
				(*baza) = (*baza)->kolejny;
			}
		}
		UstawNaGora(&(*baza));
	}
	E = NULL;
	free(E);
}

void Wyszukiwanie(struct ksiazka *baza)
{
	struct ksiazka *tymczasowy = NULL;
	int numerek = 0;
	int licznik=0;
	char tab[30] = {"\0"};
	char chwilowe[30];
	char *wynik;
	char c =(char)(88);
	char cos[80] = {"\0"};
	while ((int)c != 27)
	{
		printf("Wyszukaj(ESC przerywa wyszukiwanie): ");
		printf("%s", tab);
		c = getch();
		system("cls");
		cos[0] = c;
		strcat(tab, cos);
		tymczasowy = baza;
		while (tymczasowy != NULL)
		{
			baza = tymczasowy;
			strcpy(chwilowe, baza->kontakt.imie);
			while (licznik < (int)strlen(chwilowe))
			{
				chwilowe[licznik] = tolower(chwilowe[licznik]);
				licznik++;
			}
			licznik = 0;
			wynik = strstr(chwilowe, tab);
			if (wynik != NULL)
			{
				numerek++;
				printf("%2d.|%20s|%30s|%10s|%20s|\n", numerek, baza->kontakt.imie, baza->kontakt.nazwisko, baza->kontakt.numer, baza->kontakt.grupa);
			}
			else
			{
				strcpy(chwilowe, baza->kontakt.nazwisko);
				while (licznik < (int)strlen(chwilowe))
				{
					chwilowe[licznik] = tolower(chwilowe[licznik]);
					licznik++;
				}
				licznik = 0;
				wynik = strstr(chwilowe, tab);
				if (wynik != NULL)
				{
					numerek++;
					printf("%2d.|%20s|%30s|%10s|%20s|\n", numerek, baza->kontakt.imie, baza->kontakt.nazwisko, baza->kontakt.numer, baza->kontakt.grupa);
				}
				else
				{
					strcpy(chwilowe, baza->kontakt.grupa);
					chwilowe[0] = tolower(chwilowe[0]);
					while (licznik < (int)strlen(chwilowe))
					{
						chwilowe[licznik] = tolower(chwilowe[licznik]);
						licznik++;
					}
					licznik = 0;
					wynik = strstr(chwilowe, tab);
					if (wynik != NULL)
					{
						numerek++;
						printf("%2d.|%20s|%30s|%10s|%20s|\n", numerek, baza->kontakt.imie, baza->kontakt.nazwisko, baza->kontakt.numer, baza->kontakt.grupa);
					}
				}
			}
			tymczasowy = baza->kolejny;		
		}
		numerek = 0;
		UstawNaGora(&(baza));
	}
	tymczasowy = NULL;
	free(tymczasowy);
}

void DodajKontakt(struct ksiazka **baza,int tryb,int *ilosc)
{
	struct ksiazka *nowy = malloc(sizeof(struct ksiazka));
	if (nowy != NULL)
	{
		struct ksiazka *E = NULL;
		struct ksiazka *tymczasowy = NULL;
		int dzialanie = 0;
		scanf("%s", nowy->kontakt.imie);
		scanf("%s", nowy->kontakt.nazwisko);
		scanf("%s", nowy->kontakt.numer);
		scanf("%s", nowy->kontakt.grupa);
		if (tryb == 0)
		{
			UstawNaDol(&(*baza));
			if (*ilosc == 0)
			{
				nowy->poprzedni = NULL;
			}
			else
			{
				nowy->poprzedni = (*baza);
			}
			(*baza)->kolejny = nowy;
			nowy->kolejny = NULL;
			(*baza) = nowy;
			(*ilosc)++;
		}
		else
		{
			tymczasowy = (*baza);
			while (tymczasowy != NULL && dzialanie != 1)
			{
				(*baza) = tymczasowy;
				if (tryb == 1)
				{
					dzialanie = strcoll((*baza)->kontakt.imie, nowy->kontakt.imie);
				}
				if (tryb == 2)
				{
					dzialanie = strcoll((*baza)->kontakt.nazwisko, nowy->kontakt.nazwisko);
				}
				if (tryb == 3)
				{
					dzialanie = strcoll((*baza)->kontakt.grupa, nowy->kontakt.grupa);
				}
				if (dzialanie == 1)
				{
					E = (*baza);
					nowy->kolejny = E;
					nowy->poprzedni = E->poprzedni;
					E->poprzedni = nowy;
					if (nowy->poprzedni != NULL)
					{
						nowy->poprzedni->kolejny = nowy;
					}
					UstawNaDol(&(*baza));
					tymczasowy = (*baza);
					(*ilosc)++;
				}
				else
				{
					tymczasowy = (*baza)->kolejny;
					if (tymczasowy == NULL)
					{
						nowy->poprzedni = (*baza);
						(*baza)->kolejny = nowy;
						nowy->kolejny = NULL;
						(*baza) = nowy;
						(*ilosc)++;
					}
				}
			}
		}
		nowy = NULL;
		E = NULL;
		tymczasowy = NULL;
		free(nowy);
		free(E);
		free(tymczasowy);
	}
	else
	{
		puts("blad alokacji");
	}
}

void UsunKontakt(struct ksiazka **baza, int ktory)
{
	struct ksiazka *E=NULL;
	struct ksiazka *tymczasowy=NULL;
	UstawNaMiejsce(&(*baza), ktory);
	E = (*baza);
	if (E->poprzedni == NULL)
	{
		if (E->kolejny == NULL)
		{
			tymczasowy=NULL;
			free(E);
			(*baza) = tymczasowy;
		}
		else
		{
			tymczasowy = (*baza)->kolejny;
			E->kolejny->poprzedni = NULL;
			E->kolejny=NULL;
			free(E);
			(*baza) = tymczasowy;
		}	
	}
	else
	{
		if (E->kolejny == NULL)
		{
			tymczasowy = (*baza)->poprzedni;
			E->poprzedni->kolejny = NULL;
			free(E);
			(*baza) = tymczasowy;
		}
		else
		{
			tymczasowy = (*baza)->poprzedni;
			E->poprzedni->kolejny = E->kolejny;
			E->kolejny->poprzedni = E->poprzedni;
			free(E);
			(*baza) = tymczasowy;	
		}
	}
	tymczasowy = NULL;
	free(tymczasowy);
}

void CzyszczenieKsiazki(struct ksiazka **baza)
{
	while ((*baza)!= NULL)
	{
		UsunKontakt(&(*baza), 1);
	}	
}

int main()
{
	struct ksiazka *baza=NULL;
	int ilosc = 0;
	int ktory = 0;
	int warunek_konczacy = 0;
	int tryb_sortowania = 0;
	char wybor;
	baza = malloc(sizeof(struct ksiazka));
	baza->poprzedni = NULL;
	baza->kolejny = NULL;
	setlocale(LC_ALL, "polish_poland");	
	while (warunek_konczacy != 1)
	{
		printf("Ksiazka zawiera: %d kontaktow\n", ilosc);
		puts("1. Wczytaj ksiazke");
		puts("2. Wyswietl ksiazke");
		puts("3. Sortuj ksiazke");
		puts("4. Dodaj Kontakt");
		puts("5. Wyszukaj kontakt");
		puts("6. Usun kontakt");
		puts("7. Wylacz");
		wybor = getch();
		switch (wybor)
		{		
		case '1':		
			system("cls");
			UstawNaGora(&baza);
			if (ilosc > 0)
			{		
				CzyszczenieKsiazki(&baza);
				
				ilosc = 0;
			}
			baza = malloc(sizeof(struct ksiazka));
			baza->poprzedni = NULL;
			baza->kolejny = NULL;
			Wczytaj(&baza, &ilosc);
			UstawNaGora(&baza);			
			break;	
		case '2':
			system("cls");
			UstawNaGora(&baza);	
			if (ilosc>0)
			{
				WyswietlListeKontaktow(baza);
				UstawNaGora(&baza);
			}
			else
			{
				puts("brak kontaktow");
			}
			break;
		case '3':
			system("cls");
			UstawNaGora(&baza);
			if (ilosc > 0)
			{
				
				tryb_sortowania = WyborTrybuSortowania(tryb_sortowania);
				Sortowanie(&baza, tryb_sortowania);
			}
			else
			{
				puts("brak kontakow");
			}
			break;
		case '4':
			system("cls");
			UstawNaGora(&baza);
			DodajKontakt(&baza, tryb_sortowania,&ilosc);
			break;
		case '5':
			system("cls");
			UstawNaGora(&baza);
			if (ilosc > 0)
			{
				
				Wyszukiwanie(baza);
			}
			else
			{
				puts("brak kontaktow");
			}
			break;
		case '6':
			system("cls");
			if (ilosc > 0)
			{
				
				UstawNaGora(&baza);
				WyswietlListeKontaktow(baza);
				UstawNaGora(&baza);
				printf("Podaj miejsce z ktorego ma byc usuniety kontakt: ");
				while (scanf_s("%d", &ktory) != 1 || ktory > ilosc || ktory <= 0)
				{
					system("cls");
					WyswietlListeKontaktow(baza);
					UstawNaGora(&baza);
					puts("BLEDNE WPROWADZENIE DANYCH");
					printf("Podaj miejsce z ktorego ma byc usuniety kontakt: ");
					CzyszczenieBufora();
				}
				UsunKontakt(&baza, ktory);
				ilosc--;
			}
			else
			{
				puts("brak kontaktow");
			}
			break;
		case '7':
			warunek_konczacy++;
			UstawNaGora(&baza);
			CzyszczenieKsiazki(&baza);
			break;
		default:
			puts("Zly wybor");
			break;
		}
	}
	return 0;
}
