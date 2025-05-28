/* Ovo ce biti moj mali side project koji radim za vrijeme kolokvija.
 * Radi se o C programu koji ce koristiti AES-128 za sifriranje podataka.
 * Program u binarnu datoteku sprema lozinke za razlicite usluge.
 * Radi se o cli i postojati ce posebna "konzola" programa.
 * Program nece biti kompliciran, svrha je minimalisticki i jednostavan
 * alat za spremanje i dohvacanje lozinki.
 * Lozinke ce se spremati u dvije datoteke, jedna je backup.
 * Naravno, tijekom enkripcije ce se na neki nacin implementirati
 * MIC/MAC za provjeru integriteta.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <openssl/evp.h>

#define FILENAME "just_your_everyday_file.bin"
#define MAX_INPUT 256

// Custom funkcija za makivanje whitespaceova u inputu korisnika
char* trim(char* string) {
    char* end;

    // Makni whitespaceove ispred
    while(isspace((unsigned char)*string)) string++;

    // Ako je bila prazna linija vrati odmah
    if (*string == 0) 
        return string;

    // Uzmi zadnji znak inputa
    end = string + strlen(string) - 1;
    // Makni whitespaceove odozada
    while (end > string && isspace((unsigned char)*end)) end--;

    // Null terminiraj input
    *(end + 1) = '\0';

    return string;
}

// Funkcija za inicijalizaciju binarne datoteke
void init() {

}

// Funkcija za dekripciju datoteke
void decrypt() {

}

int main(int argc, char* argv[]) {
    // Provjera ulaza
    if(argc != 2) {
        printf("Usage: mnemo [master_password]");
        return 1;
    }

    // Provjeri ako postoji datoteka
    FILE *file = fopen(FILENAME, "rb");

    if(file) {
        // Ako datoteka postoji, desifriraj je
        decrypt(file);
        // Sto dalje
    } else {
        // Ako datoteka ne postoji pitaj korisnika sto zeli dalje
        char line[8];

        // Pitaj korisnika zeli li kreirati datoteku
        printf("Password file does not exist! Do you want to create it? (y/n): ");

        if(fgets(line, sizeof(line), stdin) != NULL) {
            if(line[0] == 'y' || line[0] == 'Y') {
                // Kreiraj datoteku i postavi dummy vrijednost
                init();
            }
        } else {
            printf("Input error.");
            return 1;
        }
    }

    // Buffer za unos korisnika u simuliranom shellu
    char input[MAX_INPUT];

    // Beskonacna petlja za simuliranje shella
    while(1) {
        // Ispis
        printf("tool > ");
        fflush(stdout);

        // Citaj ulaz korisnika
        if(fgets(input, MAX_INPUT, stdin) == NULL) break;

        // Makni LF iz korisnikovog inputa
        input[strcspn(input, "\n")] = 0;
        // Trimaj input korisnika
        char *input_t = trim(input);

        // Naredba 'exit' izlazi iz simuliranog shella
        if(strcmp(input_t, "exit") == 0) {
            break;
        } else if(strlen(input_t) == 0) {   // Ignoriraj prazne linije
            continue;
        } else if(strcmp(input_t, "clear") == 0) {  // Simulira ciscenje prompta
            system("cls");
        } else {
            printf("Unknown command.\n");
        }
    }
}
