#ifndef BLOOM
#define BLOOM 1000
#endif

#include <iostream>
#include <fstream>
#include <bitset>
#include <functional>

template <typename ElementType, int ArraySize = BLOOM>

class BloomFilter
{

public:
    void CreateBF()
    {
        filter.reset();
        std::ofstream outFile(FILE_NAME);
        if (outFile.is_open())
        {
            outFile << filter;
            std::cout << "Bloom filter je kreiran." << std::endl;
            outFile.close();
        }
        else
        {
            std::cerr << "Nije moguće kreirati Bloom filter." << std::endl;
        }
    }

    void InsertBF(const ElementType &vrijednost)
    {
        std::fstream file(FILE_NAME, std::ios::out | std::ios::in);
        if (file.is_open())
        {
            file >> filter;

            std::hash<ElementType> hashFunc;
            std::size_t hash1 = hashFunc(vrijednost) % ArraySize;
            std::size_t hash2 = (hashFunc(vrijednost) >> 16) % ArraySize;
            std::size_t hash3 = (hashFunc(vrijednost) >> 32) % ArraySize;

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

    bool IsElementBF(const ElementType &vrijednost)
    {
        std::ifstream file(FILE_NAME);
        if (file.is_open())
        {
            file >> filter;
            file.close();

            std::hash<ElementType> hashFunc;
            std::size_t hash1 = hashFunc(vrijednost) % ArraySize;
            std::size_t hash2 = (hashFunc(vrijednost) >> 16) % ArraySize;
            std::size_t hash3 = (hashFunc(vrijednost) >> 32) % ArraySize;

            return filter.test(hash1) && filter.test(hash2) && filter.test(hash3);
        }
        else
        {
            std::cerr << "Nije moguće otvoriti Bloom filter za provjeru." << std::endl;
            return false;
        }
    }

private:
    const std::string FILE_NAME = "bloom.txt";
    std::bitset<ArraySize> filter;
};