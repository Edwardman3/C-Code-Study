#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#pragma warning(disable:4013)
#pragma warning(disable:4473)

struct liczba_zespolona
{
	float Re;
	float Im;
	struct liczba_zespolona *poprzedni;
};

void Lista()
{
	puts("1. Re Im - liczba zespolona");
	puts("2. Re 0  - czesc rzeczywista liczby zespolonej");
	puts("3. 0  Im - czesc urojona liczby zespolonej");
	puts("4. '+' '-' '*' '/' - znaki dzialan");
	puts("5. 'x' - wylacz program");
}

int WprowadzKomentarz(float *czesc_rzecz, float *czesc_zesp)
{
	int warunek_zamykajacy = 0;
	char komenda[50];
	char znak;
	puts("Podaj polecenie:");

	while (warunek_zamykajacy == 0)
	{
		gets(komenda);
		if (strlen(komenda) == 1)
		{
			if (komenda[0] == 'x')
			{
				puts("Zamykanie programu");
				return 1;
			}
			if (komenda[0] == '+' || komenda[0] == '-' || komenda[0] == '*' || komenda[0] == '/')
			{
				return (int)komenda[0];
			}

		}
		if (sscanf_s(komenda, "%f ", czesc_rzecz) == 1)
		{
			if (sscanf_s(komenda, "%f %f", czesc_rzecz, czesc_zesp) == 2)
			{
				warunek_zamykajacy++;
			}
			else
			{
				if (sscanf_s(komenda, "%f %c", czesc_rzecz, &znak) == 2)
				{
					puts("Bledny komunikat");
				}
				else
				{
					*czesc_zesp = 0;
					warunek_zamykajacy++;
				}
			}
		}
		else
		{
			puts("Bledny komunikat");
		}
	}
	return 0;
}

void Dodawanie(float Re1, float Im1, float *Re2, float *Im2)
{
	*Re2 = *Re2 + Re1;
	*Im2 = *Im2 + Im1;
}

void Dzielenie(float Re1, float Im1, float *Re2, float *Im2)
{
	float pom1;
	float pom2;
	pom1 = (((*Re2) * Re1) + ((*Im2) * Im1)) / ((float)pow(Re1, 2) + (float)pow(Im1, 2));
	pom2 = (((*Im2) * Re1) - ((*Re2) * Im1)) / ((float)pow(Re1, 2) + (float)pow(Im1, 2));
	*Re2 = pom1;
	*Im2 = pom2;
}

void Mnożenie(float Re1, float Im1, float *Re2, float *Im2)
{
	float pom1;
	float pom2;
	pom1 = (Re1 * (*Re2)) - (Im1 * (*Im2));
	pom2 = (Re1 * (*Im2)) + ((*Re2) * Im1);
	*Re2 = pom1;
	*Im2 = pom2;
}

void Wyswietl(struct liczba_zespolona *gora,int ilosc)
{
	struct liczba_zespolona *wyswietl=NULL;
	struct liczba_zespolona *tymczasowy = NULL;
	int i = 0;
	wyswietl = gora;
	if (ilosc > 0)
	{
		while (i < ilosc)
		{
			printf("%f i%f\n", wyswietl->Re, wyswietl->Im);
			tymczasowy = wyswietl->poprzedni;
			wyswietl = tymczasowy;
			i++;
		}
		i = 0;
	}
	wyswietl = NULL;
	free(wyswietl);
}

void Dodaj(struct liczba_zespolona **gora,int *polecenie, int *ilosc)
{
	struct liczba_zespolona *nowy = NULL;
	nowy = (struct liczba_zespolona*)malloc(sizeof(struct liczba_zespolona));
	if (nowy == NULL)
	{
		puts("blad alokacji pamieci zakonczenie programu");
		*polecenie = 1;
	}
	else
	{
		nowy->poprzedni = *gora;
		*gora = nowy;
		*ilosc=*ilosc+1;
	}
	nowy = NULL;
	free(nowy);
}

void Zdejmij(struct liczba_zespolona **gora, float *Re, float *Im, int *ilosc)
{
	struct liczba_zespolona *tymczasowy;
	*Re = (*gora)->Re;
	*Im = (*gora)->Im;
	tymczasowy = (*gora)->poprzedni;
	free((*gora));
	(*gora) = tymczasowy;
	*ilosc=*ilosc-1;
	tymczasowy = NULL;
	free(tymczasowy);
}

void CzyStosPusty(struct liczba_zespolona *gora,int ilosc)
{
	if (gora == NULL)
	{
		puts("Pusty stos");
	}
	else
	{
		Wyswietl(gora,ilosc);
	}
}

int main()
{
	struct liczba_zespolona *gora = NULL;
	float buforRe = 0;
	float buforIm = 0;
	int ilosc = 0;
	int polecenie = 0;
	puts("PROGRAM: Kalkulator liczb zespolonych: Wprowadzaj nastepujace komunikaty!!!");
	Lista();
	while (polecenie != 1)
	{
		CzyStosPusty(gora,ilosc);
		polecenie = WprowadzKomentarz(&buforRe, &buforIm);
		if (polecenie == 0)
		{
			Dodaj(&gora, &polecenie, &ilosc);
			gora->Re = buforRe;
			gora->Im = buforIm;
			buforRe = 0;
			buforIm = 0;
		}
		if (polecenie > 1)
		{
			if (ilosc >= 2)
			{
				
				Zdejmij(&gora, &buforRe, &buforIm, &ilosc);
				system("cls");
				if ((char)polecenie == '+')
				{
					printf("(%f i%f) + (%f i%f) = ", (gora->Re), (gora->Im), buforRe, buforIm);
					Dodawanie(buforRe, buforIm, &(gora->Re), &(gora->Im));
					printf("(%f i%f)\n", (gora->Re), (gora->Im));
				}
				if ((char)polecenie == '-')
				{
					printf("(%f i%f) - (%f i%f) = ",(gora->Re), (gora->Im),buforRe, buforIm);
					Dodawanie((-1)*buforRe, (-1)*buforIm, &(gora->Re), &(gora->Im));
					printf("(%f i%f)\n", (gora->Re), (gora->Im));
				}
				if ((char)polecenie == '*')
				{
					printf("(%f i%f) * (%f i%f) = ", (gora->Re), (gora->Im), buforRe, buforIm);
					Mnożenie(buforRe, buforIm, &(gora->Re), &(gora->Im));
					printf("(%f i%f)\n", (gora->Re), (gora->Im));
				}
				if ((char)polecenie == '/')
				{
					if (buforRe == 0 || buforIm == 0)
					{
						puts("Dzialanie zabronione. Dzielisz przez zero");
						Dodaj(&gora, &polecenie, &ilosc);
						gora->Re = buforRe;
						gora->Im = buforIm;
						buforRe = 0;
						buforIm = 0;
					}
					else
					{
						printf("(%f i%f) / (%f i%f) = ", (gora->Re), (gora->Im), buforRe, buforIm);
						Dzielenie(buforRe, buforIm, &(gora->Re), &(gora->Im));
						printf("(%f i%f)\n", (gora->Re), (gora->Im));
					}
				}
			}
			else
			{
				puts("Wprowadz wiecej liczb by wykonac dane polecenie");
			}
		}
	}
	while (ilosc != 0)
	{
		Zdejmij(&gora, &buforRe, &buforIm, &ilosc);
	}
	return 0;
}
