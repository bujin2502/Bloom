#include <iostream>
#include "bloom.h"

typedef std::string elementtype;

const int velicina_polja = BLOOM;
BloomFilter<elementtype, velicina_polja> bloomFilter;

int main()
{
    int izbor;
    while (true)
    {
        std::cout << "       Bloom filter - Izbornik       " << std::endl;
        std::cout << "-------------------------------------" << std::endl;
        std::cout << "1. Stvori Bloom filter               " << std::endl;
        std::cout << "2. Dodaj vrijednost u Bloom filter   " << std::endl;
        std::cout << "3. Provjeri vrijednost u Bloom filtru" << std::endl;
        std::cout << "4. Izlazak iz programa               " << std::endl;
        std::cout << "-------------------------------------" << std::endl;
        std::cout << "Unesi broj željene operacije: ";
        std::cin >> izbor;

        switch (izbor)
        {
        case 1:
            bloomFilter.CreateBF();
            break;
        case 2:
        {
            elementtype vrijednost;
            std::cout << "Unesi vrijednost: ";
            std::cin >> vrijednost;
            bloomFilter.InsertBF(vrijednost);
            break;
        }
        case 3:
        {
            elementtype vrijednost;
            std::cout << "Unesi vrijednost: ";
            std::cin >> vrijednost;
            bool exists = bloomFilter.IsElementBF(vrijednost);
            std::cout << "Vrijednost '" << vrijednost << (exists ? "' je možda u" : "' nije u") << " Bloom filtru." << std::endl;
            break;
        }
        case 4:
            std::cout << "Izlazak iz programa" << std::endl;
            return 0;
        default:
            std::cout << "Neispravan unos. Pokušajte opet." << std::endl;
        }

        std::cout << std::endl;
    }

    return 0;
}

/* Ovaj kod implementira jednostavnu korisničku sučelje za korištenje Bloom filtra, koji je vjerojatnosna struktura podataka za efikasnu provjeru prisutnosti elemenata u skupu. 

Kod započinje uključivanjem potrebnih biblioteka i deklariranjem tipova. Također se definira konstanta velicina_polja, koja predstavlja veličinu Bloom filtera, te se stvara objekt bloomFilter klase BloomFilter, koji koristi tip elementtype i veličinu velicina_polja.

U funkciji main() se koristi beskonačna petlja while(true) kako bi se omogućilo korisniku da izvršava različite operacije sve dok ne odabere izlazak iz programa. Unutar petlje se ispisuje izbornik s različitim opcijama za manipulaciju Bloom filtrom.

Kada korisnik odabere neku operaciju, unosi se odgovarajući broj izbornika (varijabla izbor) putem standardnog ulaza (std::cin >> izbor). Zatim se koristi switch izraz za odabir odgovarajuće akcije na temelju unesenog broja.

- Ako je izbor 1, poziva se metoda CreateBF() na bloomFilter objektu, koja stvara novi Bloom filter.
- Ako je izbor 2, korisniku se traži unos vrijednosti (elementtype vrijednost) putem standardnog ulaza, a zatim se poziva metoda InsertBF(vrijednost) na bloomFilter objektu, koja dodaje vrijednost u Bloom filter.
- Ako je izbor 3, korisniku se također traži unos vrijednosti, a zatim se poziva metoda IsElementBF(vrijednost) na bloomFilter objektu. Metoda provjerava je li vrijednost prisutna u Bloom filtru i vraća bool vrijednost (true ako je vjerojatno prisutna, false ako nije). Rezultat se ispisuje na standardnom izlazu.
- Ako je izbor 4, ispisuje se poruka o izlasku iz programa i petlja se prekida (return 0).

Ako korisnik unese neispravan broj (izbor koji nije 1, 2, 3 ili 4), ispisuje se poruka o neispravnom unosu i petlja se nastavlja.

Nakon svake izvršene operacije, ispisuje se prazna linija radi razdvajanja ispisnih redaka.

Kod završava s return 0, što označava uspješan završetak programa. */