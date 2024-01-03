#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <iostream>
#include <string>

class Zmogus {
protected:
    std::string vardas;
    std::string pavarde;

public:
    // konstruktorius
    Zmogus(const std::string& vardas, const std::string& pavarde) : vardas(vardas), pavarde(pavarde) {}

    // konstruktorius
    Zmogus() : vardas(""), pavarde("") {}

    // metodas isvestinems klasems
    virtual void Rodymas() const = 0;

    // dekonstruktorius
    virtual ~Zmogus() {
        //std::cout << "Zmogus dekonstruktorius\n";
    }
};

#endif // ZMOGUS_H

