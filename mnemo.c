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

#define FILENAME "justYourEverydayFile.bin"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[]) {
    // Provjera ulaza
    if(argc != 2) {
        printf("Usage: mnemo <master_password>");
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
}