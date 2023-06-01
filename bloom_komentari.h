#ifndef BLOOM
#define BLOOM 1000
#endif

#include <iostream>
#include <fstream>
#include <bitset>
#include <functional>

template <typename elementtype, int velicina_polja = BLOOM>

class BloomFilter
{

public:
    void CreateBF()
    {
        filter.reset();
        std::ofstream izlazni_dokument(ime_dokumenta);
        if (izlazni_dokument.is_open())
        {
            izlazni_dokument << filter;
            std::cout << "Bloom filter je kreiran." << std::endl;
            izlazni_dokument.close();
        }
        else
        {
            std::cerr << "Nije moguće kreirati Bloom filter." << std::endl;
        }
    }

/*     Ovaj dio koda definira metodu `CreateBF()` unutar klase `BloomFilter`. Evo objašnjenja što se događa u toj metodi:

- `filter.reset();` resetira sve bitove u `filter` na vrijednost 0. To osigurava da je filter prazan prije nego što se bilo koji element dodaje u njega.

- `std::ofstream izlazni_dokument(ime_dokumenta);` otvara izlaznu datoteku `izlazni_dokument` s nazivom datoteke `ime_dokumenta`, koja je u ovom slučaju "bloom.txt".

- `if (izlazni_dokument.is_open())` provjerava je li otvaranje datoteke uspjelo.

  - Ako je otvaranje uspjelo, linija `izlazni_dokument << filter;` zapisuje trenutno stanje `filter` u otvorenu datoteku. To se radi koristeći operator `<<` za izlazni tok, što znači da se bitovi filtera zapisuju u datoteku.

  - Nakon toga, ispisuje se poruka "Bloom filter je kreiran." koristeći `std::cout << "Bloom filter je kreiran." << std::endl;`.

  - Na kraju, `izlazni_dokument.close();` zatvara otvorenu datoteku.

- Ako otvaranje datoteke nije uspjelo, ispisuje se poruka "Nije moguće kreirati Bloom filter." koristeći `std::cerr << "Nije moguće kreirati Bloom filter." << std::endl;`.

Ukratko, `CreateBF()` metoda resetira filter, otvara datoteku "bloom.txt" i sprema trenutno stanje filtera u tu datoteku. Ako je otvaranje datoteke uspjelo, ispisuje se poruka o uspješnom stvaranju Bloom filtera; inače, ispisuje se poruka o neuspjehu. */

    void InsertBF(const elementtype &vrijednost)
    {
        std::fstream file(ime_dokumenta, std::ios::out | std::ios::in);
        if (file.is_open())
        {
            file >> filter;

            std::hash<elementtype> hashFunc;
            std::size_t hash1 = hashFunc(vrijednost) % velicina_polja;
            std::size_t hash2 = (hashFunc(vrijednost) >> 16) % velicina_polja;
            std::size_t hash3 = (hashFunc(vrijednost) >> 32) % velicina_polja;

            filter.set(hash1, true);
            filter.set(hash2, true);
            filter.set(hash3, true);

            file.seekp(0);
            file << filter;
            file.close();

            std::cout << "Vrijednost '" << vrijednost << "' je dodana u Bloom filter." << std::endl;
        }
        else
        {
            std::cerr << "Nije moguće ažurirati Bloom filter." << std::endl;
        }
    }

/* Ovaj dio koda definira metodu InsertBF(const elementtype &vrijednost) unutar klase BloomFilter. Evo objašnjenja što se događa u toj metodi:

    std::fstream file(ime_dokumenta, std::ios::out | std::ios::in); otvara datoteku file za čitanje i pisanje (std::ios::out | std::ios::in). Datoteka koja se otvara je "bloom.txt".

    if (file.is_open()) provjerava je li otvaranje datoteke uspjelo.

        Ako je otvaranje uspjelo, linija file >> filter; čita trenutno stanje filtera iz datoteke. To se radi koristeći operator >> za unosni tok, što znači da se bitovi filtera čitaju iz datoteke i postavljaju u odgovarajuće stanje.

        Nakon toga, stvara se objekt hashFunc od klase std::hash<elementtype> koji se koristi za generiranje hash vrijednosti. Tri različite hash vrijednosti se generiraju primjenom hashFunc na vrijednost. Ove hash vrijednosti se zatim koriste za postavljanje odgovarajućih bitova na 1 u bitsetu filter.

        file.seekp(0); postavlja pokazivač za pisanje na početak datoteke kako bi se filter zapisao na početak datoteke.

        file << filter; zapisuje trenutno stanje filtera u datoteku. To se radi koristeći operator << za izlazni tok, što znači da se bitovi filtera zapisuju u datoteku.

        file.close(); zatvara otvorenu datoteku.

        Na kraju, ispisuje se poruka "Vrijednost 'vrijednost' je dodana u Bloom filter." koristeći std::cout << "Vrijednost '" << vrijednost << "' je dodana u Bloom filter." << std::endl;.

    Ako otvaranje datoteke nije uspjelo, ispisuje se poruka "Nije moguće ažurirati Bloom filter." koristeći std::cerr << "Nije moguće ažurirati Bloom filter." << std::endl;.

Ukratko, InsertBF(const elementtype &vrijednost) metoda otvara datoteku "bloom.txt" za čitanje i pisanje, čita trenutno stanje filtera iz datoteke, postavlja odgovarajuće bitove na 1 na temelju hash vrijednosti elemenata, zapisuje ažurirano stanje filtera natrag u datoteku, te ispisuje poruku o uspješnom dodavanju elementa u Bloom filter. Ako otvaranje datoteke nije uspjelo, ispisuje se poruka o neuspjehu. */

    bool IsElementBF(const elementtype &vrijednost)
    {
        std::ifstream file(ime_dokumenta);
        if (file.is_open())
        {
            file >> filter;
            file.close();

            std::hash<elementtype> hashFunc;
            std::size_t hash1 = hashFunc(vrijednost) % velicina_polja;
            std::size_t hash2 = (hashFunc(vrijednost) >> 16) % velicina_polja;
            std::size_t hash3 = (hashFunc(vrijednost) >> 32) % velicina_polja;

            return filter.test(hash1) && filter.test(hash2) && filter.test(hash3);
        }
        else
        {
            std::cerr << "Nije moguće otvoriti Bloom filter za provjeru." << std::endl;
            return false;
        }
    }

/* Ovaj dio koda definira metodu IsElementBF(const elementtype &vrijednost) unutar klase BloomFilter. Evo objašnjenja što se događa u toj metodi:

    std::ifstream file(ime_dokumenta); otvara datoteku file za čitanje. Datoteka koja se otvara je "bloom.txt".

    if (file.is_open()) provjerava je li otvaranje datoteke uspjelo.

        Ako je otvaranje uspjelo, linija file >> filter; čita trenutno stanje filtera iz datoteke. To se radi koristeći operator >> za unosni tok, što znači da se bitovi filtera čitaju iz datoteke i postavljaju u odgovarajuće stanje.

        Zatim se stvara objekt hashFunc od klase std::hash<elementtype> koji se koristi za generiranje hash vrijednosti. Tri različite hash vrijednosti se generiraju primjenom hashFunc na vrijednost. Ove hash vrijednosti se zatim koriste za provjeru postavljenosti bitova u bitsetu filter.

        file.close(); zatvara otvorenu datoteku.

        Na kraju, metoda vraća logički rezultat koji provjerava je li svi provjereni bitovi u filteru postavljeni na 1. Ako jesu, vraća se true; inače, vraća se false.

    Ako otvaranje datoteke nije uspjelo, ispisuje se poruka "Nije moguće otvoriti Bloom filter za provjeru." koristeći std::cerr << "Nije moguće otvoriti Bloom filter za provjeru." << std::endl;, a zatim se vraća false.

Ukratko, IsElementBF(const elementtype &vrijednost) metoda otvara datoteku "bloom.txt" za čitanje, čita trenutno stanje filtera iz datoteke, provjerava postavljenost bitova u filteru na temelju hash vrijednosti elementa i vraća logički rezultat koji označava je li element prisutan u Bloom filteru. Ako otvaranje datoteke nije uspjelo, vraća se false. */


private:
    const std::string ime_dokumenta = "bloom.txt";
    std::bitset<velicina_polja> filter;

/* Ovaj dio koda je dio privatnog dijela klase BloomFilter i sadrži dvije privatne varijable:

    const std::string ime_dokumenta = "bloom.txt"; je konstanta tipa std::string koja sadrži naziv datoteke u kojoj se pohranjuje Bloom filter. U ovom slučaju, naziv datoteke je "bloom.txt". Ova varijabla je konstantna, što znači da se vrijednost ne može promijeniti nakon što je dodijeljena.

    std::bitset<velicina_polja> filter; je objekt tipa std::bitset koji se koristi za pohranjivanje bitova Bloom filtera. std::bitset je šablonska klasa koja omogućuje manipulaciju skupom bitova. Veličina bitseta je određena parametrom velicina_polja, koji je postavljen na vrijednost BLOOM ili 1000 (prema definiciji iznad). Ovaj bitset predstavlja sam Bloom filter i koristi se za postavljanje ili provjeru postavljenosti pojedinih bitova u filteru.

Ključna riječ private: označava da su ove varijable privatne, što znači da se mogu pristupiti samo unutar klase BloomFilter i nisu dostupne izvan nje. To pruža enkapsulaciju, ograničavajući izravan pristup tim varijablama izvan klase i promjenu njihovih vrijednosti samo putem javnih metoda klase. */

};

/* Ovaj kod definira klasu BloomFilter koja implementira Bloom filter, vjerojatnosnu strukturu podataka koja se koristi za provjeru pripadnosti elemenata skupu s određenom vjerojatnosti pogreške. Evo što radi svaki dio koda:

- Prvi dio koristi preprocesorske direktive #ifndef, #define i #endif kako bi provjerio je li simbol BLOOM definiran. Ako nije, definira ga i postavlja na vrijednost 1000.

- Zatim se uključuju potrebne biblioteke za rad s Bloom filtrom: iostream, fstream, bitset i functional.

- Sljedeći dio definira šablonsku klasu BloomFilter. Ta klasa ima nekoliko metoda:

  - CreateBF(): Ova metoda stvara ili resetira Bloom filter. Resetira filter na početno stanje i sprema ga u datoteku "bloom.txt".

  - InsertBF(const elementtype &vrijednost): Ova metoda dodaje element u Bloom filter. Otvorena je datoteka "bloom.txt" u načinu pisanja i čitanja. Čita se trenutno stanje filtera iz datoteke, a zatim se primjenjuje hash funkcija na element kako bi se generirala tri različita hash broja. Ti hash brojevi se koriste za postavljanje odgovarajućih bitova na 1 u bitsetu filtera. Nakon toga, filter se zapisuje natrag u datoteku.

  - IsElementBF(const elementtype &vrijednost): Ova metoda provjerava je li element prisutan u Bloom filteru. Otvorena je datoteka "bloom.txt" u načinu čitanja. Trenutno stanje filtera se čita iz datoteke, a zatim se primjenjuje ista hash funkcija na element kako bi se generirala tri hash broja. Provjerava se jesu li bitovi na tim pozicijama u filteru postavljeni na 1. Ako su svi bitovi postavljeni na 1, vraća se true; inače, vraća se false.

- Na kraju se deklarira konstanta ime_dokumenta s vrijednošću "bloom.txt" i definira se privatni član klase, bitset filter, koji predstavlja sam Bloom filter.

Ukratko, ovaj kod implementira Bloom filter kroz klasu BloomFilter s metodama za stvaranje, dodavanje i provjeru elemenata u filteru. Filter se sprema i čita iz datoteke "bloom.txt". */