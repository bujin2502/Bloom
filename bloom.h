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
        bloomfilter.reset();
        std::ofstream izlazni_dokument(ime_dokumenta);
        if (izlazni_dokument.is_open())
        {
            izlazni_dokument << bloomfilter;
            std::cout << "Bloom filter je kreiran." << std::endl;
            izlazni_dokument.close();
        }
        else
        {
            std::cerr << "Nije moguce kreirati Bloom filter." << std::endl;
        }
    }

    void InsertBF(const elementtype &vrijednost)
    {
        std::fstream file(ime_dokumenta, std::ios::out | std::ios::in);
        if (file.is_open())
        {
            file >> bloomfilter;

            std::hash<elementtype> funkcija_sazimanja;
            std::size_t sazetak1 = funkcija_sazimanja(vrijednost) % velicina_polja;
            std::size_t sazetak2 = (funkcija_sazimanja(vrijednost) >> 16) % velicina_polja;
            std::size_t sazetak3 = (funkcija_sazimanja(vrijednost) >> 32) % velicina_polja;

            bloomfilter.set(sazetak1, true);
            bloomfilter.set(sazetak2, true);
            bloomfilter.set(sazetak3, true);

            file.seekp(0);
            file << bloomfilter;
            file.close();

            std::cout << "Vrijednost '" << vrijednost << "' je dodana u Bloom filter." << std::endl;
        }
        else
        {
            std::cerr << "Nije moguce azurirati Bloom filter." << std::endl;
        }
    }

    bool IsElementBF(const elementtype &vrijednost)
    {
        std::ifstream file(ime_dokumenta);
        if (file.is_open())
        {
            file >> bloomfilter;
            file.close();

            std::hash<elementtype> funkcija_sazimanja;
            std::size_t sazetak1 = funkcija_sazimanja(vrijednost) % velicina_polja;
            std::size_t sazetak2 = (funkcija_sazimanja(vrijednost) >> 16) % velicina_polja;
            std::size_t sazetak3 = (funkcija_sazimanja(vrijednost) >> 32) % velicina_polja;

            return bloomfilter.test(sazetak1) && bloomfilter.test(sazetak2) && bloomfilter.test(sazetak3);
        }
        else
        {
            std::cerr << "Nije moguce otvoriti Bloom filter za provjeru." << std::endl;
            return false;
        }
    }

private:
    const std::string ime_dokumenta = "bloom.txt";
    std::bitset<velicina_polja> bloomfilter;

};