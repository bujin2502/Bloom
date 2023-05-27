#include <iostream>
#include "bloom.h"

typedef std::string ElementType;

const int ArraySize = BLOOM;
BloomFilter<ElementType, ArraySize> bloomFilter;

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
            ElementType vrijednost;
            std::cout << "Unesi vrijednost: ";
            std::cin >> vrijednost;
            bloomFilter.InsertBF(vrijednost);
            break;
        }
        case 3:
        {
            ElementType vrijednost;
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