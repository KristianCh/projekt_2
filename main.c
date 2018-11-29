#include <stdio.h>
#include <stdint.h>
#include <string.h>

typedef struct zaznam {
	char kategoria[51];
	char znacka[51];
	char predajca[101];
	int cena;
	int rok_vyroby;
	char stav_vozidla[201];

	struct zaznam *next;
}zaznam;

//fukncie
void nacitaj_subor(FILE *f, zaznam *z);
void vymaz_vsetky(zaznam *z);
void vypis_zaznam(zaznam *z);
void vypis_vsetky(zaznam *z);

//pomocne funkcie
char* substring(char str[], int start, int end);
char* trim_string(char str[]);

int main() {
	zaznam *zaznamy = NULL;
	FILE *f = NULL;

	while (1) {
		char prikaz;
		scanf("%c", &prikaz);
		switch (prikaz) {
		case 'n':
			//nacita zaznamy
			nacitaj_subor(f, zaznamy); 
			vypis_vsetky(zaznamy);
			break;
		case 'v':
			//vypise zaznamy
			vypis_vsetky(zaznamy);
			break;
		case 'p':
			//prida zaznam
			break;
		case 'z':
			//zmazanie podla znacky auta
			break;
		case 'h':
			//vyhlada a vypise podla znacky a ceny
			break;
		case 'a':
			//aktualizacia zaznamu
			break;
		case 'k':
			//koniec
			vymaz_vsetky(zaznamy);
			return 0;
			break;
		default:
			break;
		}
	}
	return 0;
}

//vrati retazec vytvoreni zo vstupneho retazca na poziciach start az end
char* substring(char str[], int start, int end) {
	char* out = (char*)malloc(sizeof(char) * (end - start + 2));
	for (int i = start; i <= end + 1; i++) {
		out[i - start] = str[i];
	}
	out[end - start + 1] = '\0';
	return out;
}

//odstrani prebytocne znaky zo zaciatku a konca retazca
char* trim_string(char str[]) {
	int zprava = 0;
	int len = strlen(str);
	//najde prvy platny znak zprava
	while (1) {
		if ('0' <= str[len - zprava] && str[len - zprava] <= '9' || 'A' <= str[len - zprava] && str[len - zprava] <= 'Z' ||
			'a' <= str[len - zprava] && str[len - zprava] <= 'z' || str[len - zprava] == '$') break;
		zprava++;
		//printf("zprava %d %c %s\n", zprava, str[len - zprava], str);
	}
	return substring(str, 0, len - zprava);
}

void vypis_zaznam(zaznam *z) {
	if (z != NULL) {
		printf("%s\n", z->kategoria);
		printf("%s\n", z->znacka);
		printf("%s\n", z->predajca);
		printf("%d\n", z->cena);
		printf("%d\n", z->rok_vyroby);
		printf("%s\n", z->stav_vozidla);
	}
	else {
		printf("null pointer\n");
	}
}

void vypis_vsetky(zaznam *z) {
	zaznam *pom = z;
	if (pom == NULL) printf("null pointer\n");
	while (pom != NULL) {
		vypis_zaznam(pom);
		pom = pom->next;
	}
	z = NULL;
}

void vymaz_vsetky(zaznam *z) {
	while (z != NULL) {
		zaznam *clear = z;
		z = z->next;
		free(clear);
	}
}

void nacitaj_subor(FILE *f, zaznam *z) {
	vymaz_vsetky(z);
	f = fopen("auta.txt", "r");
	z = (zaznam*)malloc(sizeof(zaznam));
	zaznam *pom = z;
	int prve = 1;
	char str[201];
	int pos = 0;
	while (fgets(str, 201, f) != NULL) {
		if (str[0] == '$') {
			pos = 0;
			if (!prve) {
				pom->next = (zaznam*)malloc(sizeof(zaznam));
				pom = pom->next;
			}
			prve = 0;
			pom->next = NULL;
		}
		else {
			pos++;
			strcpy(str, trim_string(str));
			//printf("%s\n", str);
			switch (pos) {
			case 1:
				strcpy(pom->kategoria, str);
				break;
			case 2:
				strcpy(pom->znacka, str);
				break;
			case 3:
				strcpy(pom->predajca, str);
				break;
			case 4:
				pom->cena, atoi(str);
				//printf("%s %d\n", str, pom->cena);
				break;
			case 5:
				pom->rok_vyroby, atoi(str);
				//printf("%s %d\n", str, pom->cena);
				break;
			case 6:
				strcpy(pom->stav_vozidla, str);
				break;
			default:
				break;
			}
		}
	}
	//vypis_zaznam(z);
	//vypis_vsetky(z);
	fclose(f);
}