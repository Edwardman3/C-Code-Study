#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <math.h>

#pragma warning(disable:4996)
#pragma warning(disable:4013)

struct postac
{
	char nazwa[100];
	int poziom;
	int doswiadczenie;
	int doswiadczenie_max;
	int ilosc_monet;
	int spryt;
	int wiedza;
	int zycie;
	int zycie_max;
	int umiejetnosc_sciagania;
	int umiejetnosc_strzelanie;
	int blok;
	int wartosc_specjalna;
	int zadanie;
};

struct loch
{
	struct loch *poprzedni;
	int sila;
	int blok;
	int zycie;
	int zycie_max;
};

struct mapa
{
	int rozmiar;
	int **pixele;
	int wsp_postaci_x;
	int wsp_postaci_y;
};

void CzyszczenieBufora() /*funkcja czyszczaca bufor*/
{
	int c;
	while ((c = getchar()) != '\n' && c != EOF);
}

void WyswietlMapa(struct mapa mapka)
{
	int i, j;
	HANDLE hOut;
	if (mapka.rozmiar > 0)
	{
		for (i = 0; i < mapka.rozmiar; i++)
		{
			for (j = 0; j < mapka.rozmiar; j++)
			{
				if (i == mapka.wsp_postaci_y && j == mapka.wsp_postaci_x)
				{
					hOut = GetStdHandle(STD_OUTPUT_HANDLE);
					SetConsoleTextAttribute(hOut, BACKGROUND_BLUE);
					printf("%c", mapka.pixele[i][j]);
					SetConsoleTextAttribute(hOut, BACKGROUND_RED);
				}
				else
				{
					printf("%c", mapka.pixele[i][j]);
				}
			}
			puts("");
		}
	}
	else
	{
		puts("brak mapy");
	}
}

void OkienkoZInformacjami(struct postac *pilny_student)
{
	puts("_______________________________________________________________________________");
	printf("| %20s | poziom %3d | doswiadczenie: %5d/%5d | monety %4d |\n",pilny_student->nazwa,pilny_student->poziom,pilny_student->doswiadczenie, pilny_student->doswiadczenie_max,pilny_student->ilosc_monet);
	puts("_______________________________________________________________________________");
}

void DodajZadanie(struct loch **kolos, int *ilosc, int poziom)
{
	struct loch *nowy = NULL;
	nowy = (struct loch*)malloc(sizeof(struct loch));
	if (nowy == NULL)
	{
		puts("blad alokacji pamieci zakonczenie programu");
	}
	else
	{
		nowy->poprzedni = *kolos;
		*kolos = nowy;
		*ilosc = *ilosc + 1;
	}
	(*kolos)->sila = poziom;
	(*kolos)->blok = poziom;
	(*kolos)->zycie = poziom * 20;
	(*kolos)->zycie_max = poziom * 20;
	nowy = NULL;
	free(nowy);
}

void Zakonczenie(struct postac *pilny_student)
{
	printf("O wielki %s ,", pilny_student->nazwa);
	puts("Dzieki twoim staraniom udalo Ci sie zdac ostani kurs w semestrze...");
	Sleep(2000);
	puts("Lecz to nie koniec. Kolejne zlo czeka by sie ujawnic... trzymaj sie i mniej oczy szeroko otwarte Siergiej64 ");
	Sleep(4000);
	puts("4 SEMESTR ... nadchodzi!");
	Sleep(5000);
	exit(1000);
}

void WalkaZBosem(struct postac *pilny_student)
{
	int BADUROZAUR_zycie = 300;
	int BADUROZAUR_sila = 20;
	int los_uderzenia;
	int los_uderzenia_postaci;
	char wybor;
	puts("BADUROZAUR: Jestem BADUROZAUR nikt u mnie nie zdal egzaminu ustnego");
	Sleep(2000);
	if (pilny_student->wartosc_specjalna == 1)
	{
		puts("///Na oczach BADUROZAURA zaczynasz pic jego ulubiona whisky, co go wyprowadza z rownowagi///");
		Sleep(2000);
		puts("///Napoj dodal Ci odwagi i sily jestes gotow do egzaminu ustnego///");
		while (pilny_student->zycie > 0 && BADUROZAUR_zycie > 0)
		{
			los_uderzenia = rand() % 2;
			los_uderzenia_postaci = rand() % 4 + 1;
			if ((BADUROZAUR_sila*los_uderzenia - pilny_student->blok * 2) <= 0)
			{
				printf("///Zadanie BADUROZAURA zadalo 0 obrazen\n");
			}
			else
			{
				pilny_student->zycie = pilny_student->zycie - (BADUROZAUR_sila*los_uderzenia - pilny_student->blok * 2);
				printf("///Zadanie BADUROZAURA zadalo %d obrazen\n", (BADUROZAUR_sila*los_uderzenia - pilny_student->blok * 2));
			}
			puts("1. Postaraj sie odpowiedziec");
			puts("2. Odpowiedz pytaniem");
			puts("3. Zacznij lac wode");
			wybor = getch();
			system("cls");
			printf("STUDENT: %d / %d  \n", pilny_student->zycie, pilny_student->zycie_max);
			switch (wybor)
			{
			case '1':
				BADUROZAUR_zycie = BADUROZAUR_zycie - ((pilny_student->spryt) * (pilny_student->umiejetnosc_sciagania)*los_uderzenia_postaci);
				printf("///Zadales %d obrazen\n", ((pilny_student->spryt) * (pilny_student->umiejetnosc_sciagania)*los_uderzenia_postaci));
				break;
			case '2':
				BADUROZAUR_zycie = BADUROZAUR_zycie - ((pilny_student->wiedza) * (pilny_student->umiejetnosc_strzelanie)*los_uderzenia_postaci);
				printf("///Zadales %d obrazen\n", ((pilny_student->wiedza) * (pilny_student->umiejetnosc_strzelanie)*los_uderzenia_postaci));
				break;
			case '3':
				BADUROZAUR_zycie = BADUROZAUR_zycie - ((pilny_student->spryt) * (pilny_student->umiejetnosc_strzelanie)*los_uderzenia_postaci);
				printf("///Zadales %d obrazen\n", ((pilny_student->spryt) * (pilny_student->umiejetnosc_strzelanie)*los_uderzenia_postaci));
				break;
			default:
				break;
			}
			printf("BADUROZAUR: %d / %d  \n", BADUROZAUR_zycie, 300);
		}
		if (BADUROZAUR_zycie <= 0)
		{
			Zakonczenie(pilny_student);
			Sleep(4000);
		}
		else
		{
			puts("Zostales pozarty przez BADUROZAURA");
			puts("GAME OVER he he he");
			while (BADUROZAUR_sila != 0)
			{
				printf("he ");
				Sleep(1000);
				BADUROZAUR_sila--;
			}
			exit(1000);
		}
	}
	else
	{
		puts("BADUROZAUR zadal pytanie na ktore nie znasz odpowiedzi");
		printf("///BADUROZAUR zadal %d obrazen\n", pilny_student->zycie_max);
		puts("Wylatujesz z hukiem z sali za milczenie...");
		pilny_student->zycie = 10;
		Sleep(5000);
	}
}

void UsunZadanie(struct loch **kolos,int *ilosc)
{
	struct loch *tymczasowy=NULL;
	tymczasowy = (*kolos)->poprzedni;
	free((*kolos));
	(*kolos) = tymczasowy;
	*ilosc = *ilosc - 1;
	tymczasowy = NULL;
	free(tymczasowy);
}

void PoziomIDoswiadczenie(struct postac  *pilny_student)
{
	while(pilny_student->doswiadczenie >= pilny_student->doswiadczenie_max)
	{
		pilny_student->poziom = pilny_student->poziom + 1;
		pilny_student->doswiadczenie_max = 100 * (int)pow(2,pilny_student->poziom);	
	}
}

void WykonajZadanie(struct postac *pilny_student)
{
	struct loch *kolos=NULL;
	int ilosc = 0;
	while (ilosc < pilny_student->poziom)
	{
		DodajZadanie(&kolos, &ilosc, pilny_student->poziom);
	}
	pilny_student->zadanie=SystemWalki(&kolos, &ilosc, pilny_student);
}

int SystemWalki(struct loch **kolos,int *ilosc, struct postac *pilny_student)
{
	char wybor;
	int licznik = 1;
	int los_uderzenia;
	int los_uderzenia_zadania;
	while ((*kolos) != NULL)
	{
		
		while (pilny_student->zycie > 0 && (*kolos)->zycie > 0)
		{
			printf("ZADANIE %d\n", licznik);
			los_uderzenia = rand() % 10 + 2;
			los_uderzenia_zadania = rand() % 6 ;
			if ((*kolos)->zycie > 0)
			{
				if (((*kolos)->sila * los_uderzenia_zadania - pilny_student->blok * 3) < 0)
				{
					printf("///Zadanie zadalo 0 obrazen\n");
				}
				else
				{
					pilny_student->zycie = pilny_student->zycie - ((*kolos)->sila * los_uderzenia_zadania - pilny_student->blok * 3);
					printf("///Zadanie zadalo %d obrazen\n", ((*kolos)->sila * los_uderzenia_zadania - pilny_student->blok * 3));
				}
			}
			printf("STUDENT: %d / %d  \n", pilny_student->zycie, pilny_student->zycie_max);
			if (pilny_student->zycie > 0)
			{
				puts("__________________________");
				puts("1. Uzyj sciagi");
				puts("2. Sprobuj rozwiazac");
				puts("3. Zajrzyj do kolegii");
				wybor = getch();
				system("cls");
				switch (wybor)
				{
				case '1':
					(*kolos)->zycie = (*kolos)->zycie - ((pilny_student->spryt) * (pilny_student->umiejetnosc_sciagania)*los_uderzenia - (*kolos)->blok);
					printf("///Zadales %d obrazen\n", ((pilny_student->spryt) * (pilny_student->umiejetnosc_sciagania)*los_uderzenia - (*kolos)->blok));
					break;
				case '2':
					(*kolos)->zycie = (*kolos)->zycie - ((pilny_student->wiedza) * (pilny_student->umiejetnosc_strzelanie)*los_uderzenia - (*kolos)->blok);
					printf("///Zadales %d obrazen\n", ((pilny_student->wiedza) * (pilny_student->umiejetnosc_strzelanie)*los_uderzenia - (*kolos)->blok));
					break;
				case '3':
					(*kolos)->zycie = (*kolos)->zycie - ((pilny_student->spryt) * (pilny_student->umiejetnosc_strzelanie)*los_uderzenia - (*kolos)->blok);
					printf("///Zadales %d obrazen\n", ((pilny_student->spryt) * (pilny_student->umiejetnosc_strzelanie)*los_uderzenia - (*kolos)->blok));
					break;
				default:
					break;
				}
			}
				//printf("STUDENT: %d / %d  \n", pilny_student->zycie, pilny_student->zycie_max);
				printf("ZADANIE: %d / %d  \n", (*kolos)->zycie, (*kolos)->zycie_max);
		}
		if ((*kolos)->zycie <= 0)
		{
			pilny_student->doswiadczenie = pilny_student->doswiadczenie + 10;
			PoziomIDoswiadczenie(pilny_student);
			UsunZadanie(kolos, ilosc);
		}
		else
		{
			puts("///NIE ROZWIAZALES ZADANIA///");
			while ((*kolos) != NULL)
			{
				UsunZadanie(kolos, ilosc);
			}
			pilny_student->zycie = 10;
			pilny_student->doswiadczenie = pilny_student->doswiadczenie - 20 * pilny_student->poziom;
			printf("///Strata %d pkt doswiadczenia", 20 * pilny_student->poziom);
			Sleep(3000);
			return 1;
		}
		licznik++;
	}
	puts("///Zdales kolosa///");

	pilny_student->doswiadczenie = pilny_student->doswiadczenie + (pilny_student->poziom * 30);
	PoziomIDoswiadczenie(pilny_student);

	return 2;
}

void SalaZajeciowa(struct postac *pilny_student,struct mapa *mapka)
{
	int los = rand() % 3;
	mapka->wsp_postaci_x = 14;
	mapka->wsp_postaci_y = 8;
	WyswietlMapa(*mapka);
		if (pilny_student->poziom < 3)
		{
			if (los == 0)
			{
				puts("NADZWYCZAJNY PROWADZACY: Znowu sie spozniles dostajesz zadanie karne...");
			}
			if (los == 1)
			{
				puts("NADZWYCZAJNY PROWADZACY: Oooo przyszedl ochotnik do pytania zapraszam do tablicy ;) ");
			}
			if (los == 2)
			{
				puts("NADZWYCZAJNY PROWADZACY: Dzisiaj na czas? Cos mi tu nie gra... przepytam Cie lepiej");
			}
			puts("///POBIERANIE ZADAN....///");
			Sleep(4000);
			system("cls");
			WykonajZadanie(pilny_student);
		}
		else
		{
			puts("NADZWYCZAJNY PROWADZACY: To niemozliwe ... zdales wszystko co dalo sie zdac... lecz to nie koniec pozostał Ci jeszcze egzamin ustny!");
			puts("PROWADZACY ZAMIENIA SIE W BADUROZAURA!!! MISTYCZNA POSTAC U KTOREJ JESZCZE NIKT NIE ZDAL");
			Sleep(3000);
			WalkaZBosem(pilny_student);

		}
	
}

void WczytajStan(struct postac *pilny_student)
{
	FILE *plik;
	errno_t blad;
	blad = fopen_s(&plik, "ZAPISGRY.csv", "r");
	if (blad == 0)
	{
		fscanf_s(plik, "%[^;];", &pilny_student->nazwa, 100);
		fscanf_s(plik, "%d;", &pilny_student->poziom);
		fscanf_s(plik, "%d;", &pilny_student->doswiadczenie);
		fscanf_s(plik, "%d;", &pilny_student->doswiadczenie_max);
		fscanf_s(plik, "%d;", &pilny_student->ilosc_monet);
		fscanf_s(plik, "%d;", &pilny_student->spryt);
		fscanf_s(plik, "%d;", &pilny_student->wiedza);
		fscanf_s(plik, "%d;", &pilny_student->zycie);
		fscanf_s(plik, "%d;", &pilny_student->zycie_max);
		fscanf_s(plik, "%d;", &pilny_student->umiejetnosc_sciagania);
		fscanf_s(plik, "%d;", &pilny_student->umiejetnosc_strzelanie);
		fscanf_s(plik, "%d;", &pilny_student->blok);
		fscanf_s(plik, "%d;", &pilny_student->wartosc_specjalna);
		fscanf_s(plik, "%d;", &pilny_student->zadanie);
		fclose(plik);
		puts("///WCZYTANO///");
		Sleep(1000);
	}
	else
	{
		puts("Blad odczytu. Uruchom ponownie gre!");
		Sleep(2000);
	}
}

void ZapiszStan(struct postac *pilny_student)
{
	FILE *plik;
	errno_t blad;
	blad = fopen_s(&plik, "ZAPISGRY.csv", "w");
	if (blad == 0)
	{
		fprintf_s(plik, "%s;", pilny_student->nazwa);
		fprintf_s(plik, "%d;", pilny_student->poziom);
		fprintf_s(plik, "%d;", pilny_student->doswiadczenie);
		fprintf_s(plik, "%d;", pilny_student->doswiadczenie_max);
		fprintf_s(plik, "%d;", pilny_student->ilosc_monet);
		fprintf_s(plik, "%d;", pilny_student->spryt);
		fprintf_s(plik, "%d;", pilny_student->wiedza);
		fprintf_s(plik, "%d;", pilny_student->zycie);
		fprintf_s(plik, "%d;", pilny_student->zycie_max);
		fprintf_s(plik, "%d;", pilny_student->umiejetnosc_sciagania);
		fprintf_s(plik, "%d;", pilny_student->umiejetnosc_strzelanie);
		fprintf_s(plik, "%d;", pilny_student->blok);
		fprintf_s(plik, "%d;", pilny_student->wartosc_specjalna);
		fprintf_s(plik, "%d;", pilny_student->zadanie);
		fclose(plik);
		puts("///ZAPISANO///");
		Sleep(1000);
	}
	else
	{
		puts("Blad odczytu. Uruchom ponownie gre!");
		Sleep(2000);
	}
}

void StworzPostac(struct postac *pilny_student)
{
	puts("Podaj imie:");
	scanf("%[^\n]", pilny_student->nazwa);
	pilny_student->poziom = 1;
	pilny_student->doswiadczenie = 0;
	pilny_student->doswiadczenie_max = 100;
	pilny_student->ilosc_monet = 10;
	pilny_student->spryt = 1;
	pilny_student->wiedza = 1;
	pilny_student->zycie = 100;
	pilny_student->zycie_max = 100;
	pilny_student->umiejetnosc_sciagania = 1;
	pilny_student->umiejetnosc_strzelanie = 1;
	pilny_student->blok = 1;
	pilny_student->wartosc_specjalna = 0;
	pilny_student->zadanie = 0;
	puts("Utworzono postac");
}

void SiedzibaRektora(struct postac *pilny_student, struct mapa *mapka)
{
	
	char wybor_siedziba_rektora;
	int warunek_konczacy_siedziba_rektora = 0;
	int los;
	int dodatek = 0;
	system("cls");
	mapka->wsp_postaci_x = 5;
	mapka->wsp_postaci_y = 8;
	WyswietlMapa(*mapka);
	OkienkoZInformacjami(pilny_student);
	puts("REKTOR: Co Cie do mnie sprowadza?");
	while (warunek_konczacy_siedziba_rektora == 0)
	{
		printf("%s:\n", pilny_student->nazwa);
		puts("1. Jestem bidny student dej no troche ze stypendium");
		puts("2. Wykonalem zadanie. Przyszedlem po nagrode");
		puts("3. Opusc Siedzibe Rektora");
		if (pilny_student->poziom == 3)
		{
			puts("4. Przyszedlem po cos by pokonac ostatnia przeszkode");
		}
		wybor_siedziba_rektora = getch();
		switch (wybor_siedziba_rektora)
		{
		case '1':
			system("cls");
			OkienkoZInformacjami(pilny_student);
			los = rand()%2;
				if(los == 1)
				{
					dodatek = (rand() % 25 + 25) * (pilny_student->poziom);
					pilny_student->ilosc_monet = pilny_student->ilosc_monet + dodatek;
					printf("///Otrzymano %d monet///", dodatek);
					puts("REKTOR: Trzymaj znaj laske Pana... a teraz precz!");
				}
				else
				{
					puts("REKTOR: Idz precz nie jestes wystarczajaco prestizowy bym na Ciebie mogl patrzec");
				} 
				puts("///OPUSZCZANIE LOKACJI...///");
				Sleep(3000);
				warunek_konczacy_siedziba_rektora++;
			break;
		case '2':
			system("cls");
			OkienkoZInformacjami(pilny_student);
			if (pilny_student->zadanie == 2)
			{
				puts("REKTOR: Gratulacje! Trzymaj te grosze na wykupienie deficytu");
				pilny_student->ilosc_monet = pilny_student->ilosc_monet + 100 * (pilny_student->poziom);
				pilny_student->zadanie = 0;
				Sleep(3000);
				system("cls");
				OkienkoZInformacjami(pilny_student);
			}
			else
			{
				puts("Jeszcze go nie skonczyles!");
				puts("///OPUSZCZANIE LOKACJI...///");
				Sleep(3000);
				warunek_konczacy_siedziba_rektora++;
			}
			break;
		case '3':
			system("cls");
			warunek_konczacy_siedziba_rektora++;
			break;
		case '4':
			system("cls");
			OkienkoZInformacjami(pilny_student);
			if (pilny_student->poziom == 3)
			{
				puts("REKTOR: Mozesz kupic odemnie cos specjalnego... tylko nie mow nic Panu Profesorowi to jego ulubiona WHISKY TORFOWA");
				printf("REKTOR: Cena jak dla Ciebie... %d\n", 700 - pilny_student->poziom * 100);
				printf("%s:\n", pilny_student->nazwa);
				puts("1. TAK!");
				puts("2. Nie mam tyle...");
				wybor_siedziba_rektora = getch();
					switch (wybor_siedziba_rektora)
					{
					case '1':
						if (pilny_student->wartosc_specjalna != 1)
						{
							if (pilny_student->ilosc_monet >= (700 - pilny_student->poziom * 100))
							{
								pilny_student->ilosc_monet = pilny_student->ilosc_monet - (700 - pilny_student->poziom * 100);
								printf("///Oddano %d monet///", (700 - pilny_student->poziom * 100));
								puts("///Otrzymano WHISKY TORFOWA///");
								pilny_student->wartosc_specjalna = 1;
							}
							else
							{
								puts("REKTOR: Chcesz mnie oszukac? Nie masz tyle pieniedzy!!! Zaraz wezwe straz politechniki i Cie wyniosa stad!");
								printf("%s: Nie trzeba sam znajde droge do wyjscia\n", pilny_student->nazwa);
							}
						}
						else
						{
							puts("REKTOR: Juz Ci to sprzedalem. Nie mam wiecej");
						}
						break;
					case '2':
						if (pilny_student->wartosc_specjalna != 1)
						{
							puts("REKTOR: W takim razie idz juz sobie...zarob i wroc");
							break;
						}
						else
						{
							puts("REKTOR: No to dobrze bo juz Ci to sprzedalem i nie mam wiecej");
						}
					default:
						puts("REKTOR: Zdecyduj sie czego chcesz...");
						break;
					}
			puts("///OPUSZCZANIE LOKACJI...///");
			Sleep(3000);
			warunek_konczacy_siedziba_rektora++;
			}
			
			break;
		default:
			break;
		}
	}

}

void Szkolenie(struct postac *pilny_student)
{
	char wybor;
	int warunek_konczacy_szkolenie = 0;
	while (warunek_konczacy_szkolenie == 0)
	{
		system("cls");
		puts("WYBIERZ CO CHCESZ SIE SZKOLIC:");
		printf("Posiadasz %d monet\n", pilny_student->ilosc_monet);
		printf("1. Spryt 50 monet| %d \n", pilny_student->spryt);
		printf("2. Wiedza 50 monet| %d \n", pilny_student->wiedza);
		printf("3. Sciaganie 50 monet| %d \n", pilny_student->umiejetnosc_sciagania);
		printf("4. Strzelanie 50 monet| %d \n", pilny_student->umiejetnosc_strzelanie);
		printf("5. Wytrzymalosc na Zadania 50 monet | %d \n", pilny_student->zycie_max);
		printf("6. Wymijanie sie 50 monet | %d \n", pilny_student->blok);
		puts("7. Zakoncz szkolenie");
		wybor = getch();
		switch (wybor)
		{
		case '1':
			if (pilny_student->spryt != pilny_student->poziom * 2)
			{
				if (pilny_student->ilosc_monet >= 50)
				{
					pilny_student->spryt = pilny_student->spryt + 1;
					pilny_student->ilosc_monet = pilny_student->ilosc_monet - 50;
				}
				else
				{
					puts("///BRAK FUNDUSZY///");
				}
			}
			else
			{
				puts("///ZDOBADZ WIECEJ DOSWIADCZENIA///");
			}
			break;
		case '2':
			if (pilny_student->wiedza != pilny_student->poziom * 2)
			{
				if (pilny_student->ilosc_monet >= 50)
				{
					pilny_student->wiedza = pilny_student->wiedza + 1;
					pilny_student->ilosc_monet = pilny_student->ilosc_monet - 50;
				}
				else
				{
					puts("///BRAK FUNDUSZY///");
				}
			}
			else
			{
				puts("///ZDOBADZ WIECEJ DOSWIADCZENIA///");
			}
			break;
		case '3':
			if (pilny_student->umiejetnosc_sciagania != pilny_student->poziom * 2)
			{
				if (pilny_student->ilosc_monet >= 50)
				{
					pilny_student->umiejetnosc_sciagania = pilny_student->umiejetnosc_sciagania + 1;
					pilny_student->ilosc_monet = pilny_student->ilosc_monet - 50;
				}
				else
				{
					puts("///BRAK FUNDUSZY///");
				}
			}
			else
			{
				puts("///ZDOBADZ WIECEJ DOSWIADCZENIA///");
			}
			break;
		case '4':
			if (pilny_student->umiejetnosc_strzelanie != pilny_student->poziom * 2)
			{
				if (pilny_student->ilosc_monet >= 50)
				{
					pilny_student->umiejetnosc_strzelanie = pilny_student->umiejetnosc_strzelanie + 1;
					pilny_student->ilosc_monet = pilny_student->ilosc_monet - 50;
				}
				else
				{
					puts("///BRAK FUNDUSZY///");
				}
			}
			else
			{
				puts("///ZDOBADZ WIECEJ DOSWIADCZENIA///");
			}
			break;
		case '5':
			if (pilny_student->zycie_max !=  100 + 10 * pilny_student->poziom)
			{
				if (pilny_student->ilosc_monet >= 50)
				{
					pilny_student->zycie_max = pilny_student->zycie_max + 5;
					pilny_student->ilosc_monet = pilny_student->ilosc_monet - 50;
				}
				else
				{
					puts("///BRAK FUNDUSZY///");
				}
			}
			else
			{
				puts("///ZDOBADZ WIECEJ DOSWIADCZENIA///");
			}
		case '6':
			if (pilny_student->blok != pilny_student->poziom * 2)
			{
				if (pilny_student->ilosc_monet >= 50)
				{
					pilny_student->blok = pilny_student->blok + 1;
					pilny_student->ilosc_monet = pilny_student->ilosc_monet - 50;
				}
				else
				{
					puts("///BRAK FUNDUSZY///");
				}
			}
			else
			{
				puts("///ZDOBADZ WIECEJ DOSWIADCZENIA///");
			}
			break;
		case '7':
			warunek_konczacy_szkolenie++;
			break;
		default:
			break;
		}
	}
}

void Dom(struct postac *pilny_student,struct mapa *mapka)
{
	char wybor_dom;
	int warunek_konczacy_dom=0;
	int zadanie = 0;
	int czas;
	
	OkienkoZInformacjami(pilny_student);
	
	while (warunek_konczacy_dom == 0)
	{
		
		system("cls");
		mapka->wsp_postaci_x = 5;
		mapka->wsp_postaci_y = 16;
		WyswietlMapa(*mapka);
		OkienkoZInformacjami(pilny_student);
		puts("1. Idz spac");
		puts("2. Podszkol sie");
		puts("3. Opusc dom");
		wybor_dom = getch();
		switch (wybor_dom)
		{
		case '1':
			system("cls");
			puts("///Ile godzin chcesz spac?///");
			scanf_s("%d", &czas);
			while (czas > 0)
			{
				system("cls");
				printf("Z");
				Sleep(200);
				printf("z");
				Sleep(200);
				printf("z");
				Sleep(200);
				printf("z");
				Sleep(200);
				czas--;
				pilny_student->zycie = pilny_student->zycie + pilny_student->zycie_max/10;
				if (pilny_student->zycie > pilny_student->zycie_max)
				{
					pilny_student->zycie = pilny_student->zycie_max;
				}
				
			}
			puts("");
			printf("///Twoje zdrowie: %d\n", pilny_student->zycie);
			Sleep(2000);
			break;
		case '2':
			system("cls");
			Szkolenie(pilny_student);
			break;
		case '3':
			system("cls");
			warunek_konczacy_dom++;
			break;
		default:
			system("cls");
			break;
		}
	}
}

void WczytajMapa(struct mapa *mapka)
{
	FILE *plik;
	errno_t blad;
	int i, j;
	blad = fopen_s(&plik, "mapa.txt", "r");
	if (blad == 0)
	{
		fscanf(plik,"%d", &(mapka->rozmiar));
		mapka->pixele = malloc(mapka->rozmiar*sizeof(*mapka->pixele));
		if (mapka->pixele == NULL)
		{
			free(mapka->pixele);
		}
		else
		{
			for (i = 0; i < mapka->rozmiar; i++)
			{
				mapka->pixele[i] = malloc(mapka->rozmiar * sizeof(mapka->pixele));
				if (mapka->pixele[i] == NULL)
				{
					for (j = i; j >= 0; j--)
					{
						free(mapka->pixele[j]);
					}
					free(mapka->pixele);
					i = mapka->rozmiar;
				}
				else
				{
					for (j = 0; j < mapka->rozmiar; j++)
					{
						fscanf_s(plik, "%d", &(mapka->pixele[i][j]));
					}
				}
				puts("");
			}
			puts("");
		}
		fclose(plik);
	}
	else
	{
		puts("blad odczytu");
	}

}

void MenuGry(struct postac *pilny_student)
{
	char wybor_menu_gry;
	int warunek_konczacy_menu_gry = 0;
	struct mapa mapka;	
	mapka.wsp_postaci_x = 14;
	mapka.wsp_postaci_y = 16;
	WczytajMapa(&mapka);
	while(warunek_konczacy_menu_gry==0)
	{
		system("cls");
		mapka.wsp_postaci_x = 14;
		mapka.wsp_postaci_y = 16;
		WyswietlMapa(mapka);
		OkienkoZInformacjami(pilny_student);
		puts("1. Dom");
		puts("2. Siedziba Rektora");
		puts("3. Sala Zajeciowa");
		puts("4. Zapisz Gre");
		puts("5. Wyjscie");
		wybor_menu_gry = getch();
		switch (wybor_menu_gry)
		{
		case '1':
			system("cls");
			Dom(pilny_student,&mapka);
			break;
		case '2':
			system("cls");
			SiedzibaRektora(pilny_student,&mapka);
			break;
		case '4':
			system("cls");
			ZapiszStan(pilny_student);
			break;
		case '3':
			system("cls");
			SalaZajeciowa(pilny_student,&mapka);
			break;
		case '5':
			system("cls");
			puts("Jestes pewny? Moze chcesz zapisac gre?");
			puts("1. Zapisz i wyjdz");
			puts("2. Wyjdz");

			wybor_menu_gry = getch();
			switch (wybor_menu_gry)
			{
			case '1':
				ZapiszStan(pilny_student);
				warunek_konczacy_menu_gry++;
				break;
			case '2':
				warunek_konczacy_menu_gry++;
				break;
			default:
				puts("Zly wybor");
				break;
			}
			break;
		default:
			system("cls");
			break;
		}
	}
}

int main()
{
	struct postac pilny_student;
	char wybor_menu_glowne;
	int warunek_konczacy_menu=0;
	HANDLE hOut;
	srand(time(NULL));
	while (warunek_konczacy_menu == 0)
	{
		hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hOut, BACKGROUND_RED);
		system("cls");
		puts("MENU:");
		puts("1. Nowa gra");
		puts("2. Wczytaj gre");
		
		puts("3. Wyjscie");	
		wybor_menu_glowne = getch();
		switch (wybor_menu_glowne)
		{
		case '1':
			system("cls");
			puts("Witaj w tej pieknej krainie zwanej PWR. Czeka Cie tu wiele przyjemnosci oraz niebezpieczenstw");
			StworzPostac(&pilny_student);
			MenuGry(&pilny_student);
			break;
		case '2':
			system("cls");
			WczytajStan(&pilny_student);
			if (pilny_student.poziom > 0)
			{
				MenuGry(&pilny_student);
			}
			else
			{
				puts("blad odczytu");
			}		
			break;
		case '3':
			puts("Wyjscie");
			warunek_konczacy_menu++;
			break;
		default:
			system("cls");
			break;
		}
	}
	return 0;
}
