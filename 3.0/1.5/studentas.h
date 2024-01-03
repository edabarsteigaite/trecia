#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include "zmogus.h"


using std::string;
using std::vector;
using std::list;

class StudentasV : public Zmogus {
private:
    std::string vardas;
    std::string pavarde;
    std::vector<int> namu_darbai;
    int egzamino_rezultatas;
    float galutinisBalas;

public:
    // konstruktorius
    StudentasV() : egzamino_rezultatas(0), galutinisBalas(0.0) {}

    void Rodymas() const override {
    }

    //getteriai ir setteriai
    const std::string& getVardas() const {
        return vardas;
    }

    void setVardas(const std::string& vardas) {
        this->vardas = vardas;
    }

    const std::string& getPavarde() const {
        return pavarde;
    }

    void setPavarde(const std::string& pavarde) {
        this->pavarde = pavarde;
    }

    std::vector<int>& getNamuDarbai() {
        return namu_darbai;
    }
    const std::vector<int>& getNamuDarbai() const {
        return namu_darbai;
    }

    void setNamuDarbai(const std::vector<int>& namu_darbai) {
        this->namu_darbai = namu_darbai;
    }

    int getEgzaminoRezultatas() const {
        return egzamino_rezultatas;
    }

    void setEgzaminoRezultatas(int egzamino_rezultatas) {
        this->egzamino_rezultatas = egzamino_rezultatas;
    }

    float getGalutinisBalas() const {
        return galutinisBalas;
    }

    void setGalutinisBalas(float galutinisBalas) {
        this->galutinisBalas = galutinisBalas;
    }


    // destruktorius
    ~StudentasV() {
        //std::cout << "iskviestas destruktorius " << vardas << " " << pavarde << std::endl;
    }

    // kopijavimo konstruktorius
    StudentasV(const StudentasV& other) {
        //std::cout << "iskviestas kopijavimo konstruktorius " << other.vardas << " " << other.pavarde << std::endl;
        vardas = other.vardas;
        pavarde = other.pavarde;
        namu_darbai = other.namu_darbai;
        egzamino_rezultatas = other.egzamino_rezultatas;
        galutinisBalas = other.galutinisBalas;
    }

    // kopijavimo priskyrimo operatorius
    StudentasV& operator=(const StudentasV& other) {
        // std::cout << "iskviestas kopijavimo priskyrimo operatorius " << other.vardas << " " << other.pavarde << std::endl;
        if (this != &other) {
            namu_darbai.clear();
            vardas = other.vardas;
            pavarde = other.pavarde;
            namu_darbai = other.namu_darbai;
            egzamino_rezultatas = other.egzamino_rezultatas;
            galutinisBalas = other.galutinisBalas;
        }
        return *this;
    }
    // perdengtas ivesties operatorius
    friend std::istream& operator>>(std::istream& input, StudentasV& studentas) {
        //std::cout << "iskviestas perdengtas ivesties operatorius " << studentas.vardas << " " << studentas.pavarde << std::endl;
        std::cout << "Enter vardas: ";
        input >> studentas.vardas;

        std::cout << "Enter pavarde: ";
        input >> studentas.pavarde;


        return input;
    }

    // perdengtas isvesties operatorius
    friend std::ostream& operator<<(std::ostream& output, const StudentasV& studentas) {
        // std::cout << "iskviestas perdengtas isvesties operatorius " << std::endl;
        output << "Vardas: " << studentas.vardas << "\n";
        output << "Pavarde: " << studentas.pavarde << "\n";

        return output;
    }

};

class StudentasL {
private:
    std::string vardas;
    std::string pavarde;
    std::list<int> namu_darbai;
    int egzamino_rezultatas;
    float galutinisBalas;
public:
    // konstruktorius
    StudentasL() : egzamino_rezultatas(0), galutinisBalas(0.0) {}

    // getteriai ir setteriai
    const std::string& getVardas() const {
        return vardas;
    }

    void setVardas(const std::string& vardas) {
        this->vardas = vardas;
    }

    const std::string& getPavarde() const {
        return pavarde;
    }

    void setPavarde(const std::string& pavarde) {
        this->pavarde = pavarde;
    }

    std::list<int>& getNamuDarbai() {
        return namu_darbai;
    }

    void setNamuDarbai(const std::list<int>& namu_darbai) {
        this->namu_darbai = namu_darbai;
    }

    int getEgzaminoRezultatas() const {
        return egzamino_rezultatas;
    }

    void setEgzaminoRezultatas(int egzamino_rezultatas) {
        this->egzamino_rezultatas = egzamino_rezultatas;
    }

    float getGalutinisBalas() const {
        return galutinisBalas;
    }

    void setGalutinisBalas(float galutinisBalas) {
        this->galutinisBalas = galutinisBalas;
    }
    // destruktorius
    ~StudentasL() {
        //std::cout << "iskviestas destruktorius " << vardas << " " << pavarde << std::endl;
    }

    // kopijavimo konstruktorius
    StudentasL(const StudentasL& other) {
        //std::cout << "iskviestas kopijavimo konstruktorius " << other.vardas << " " << other.pavarde << std::endl;
        vardas = other.vardas;
        pavarde = other.pavarde;
        namu_darbai = other.namu_darbai;
        egzamino_rezultatas = other.egzamino_rezultatas;
        galutinisBalas = other.galutinisBalas;
    }

    // kopijavimo priskyrimo operatorius
    StudentasL& operator=(const StudentasL& other) {
        //std::cout << "iskviestas kopijavimo priskyrimo operatorius " << other.vardas << " " << other.pavarde << std::endl;
        if (this != &other) {
            namu_darbai.clear();
            vardas = other.vardas;
            pavarde = other.pavarde;
            namu_darbai = other.namu_darbai;
            egzamino_rezultatas = other.egzamino_rezultatas;
            galutinisBalas = other.galutinisBalas;
        }
        return *this;
    }
};

int generuotiAtsitiktiniBalai(int min, int max);
bool lyginimasPagalVardus(const StudentasV& a, const StudentasV& b);
double skaiciuotiGalutiniVidurki(const std::vector<int>& namu_darbai, int egzamino_rezultatas);
double skaiciuotiGalutiniMediana(const std::vector<int>& namu_darbai, int egzamino_rezultatas);
void skaitytiDuomenisIsFailo(const std::string& failoPavadinimas, std::vector<StudentasV>& studentaiV);
void ivedimasRanka(std::vector<StudentasV>& studentaiV);
void ivedimasAtsitiktinai(std::vector<StudentasV>& studentaiV);
void ivedimasIsFailo(std::vector<StudentasV>& studentaiV);
void spausdintiGalutiniusRezultatus(const std::vector<StudentasV>& studentaiV);


void rusiavimas_vector(vector<StudentasV>& studentaiV);
void generavimas_vector(vector<StudentasV>& studentaiV, int count, const string& failas);
void saugojimas_vector(const string& failas, const vector<StudentasV>& studentaiV);
void skaitymas_vector(vector<StudentasV>& studentaiV, const string& pav);

void rusiavimas_pagal_balus_vector(vector<StudentasV>& studentaiV, vector<StudentasV>& vargsiukai);
void isvedimas_vargsiukai_vector(const string& failas_vargsiukai, const vector<StudentasV>& vargsiukai);
void isvedimas_kietiakai_vector(const string& failas_kietiakai, const vector<StudentasV>& studentaiV);

void generavimo_laikas_vector(vector<StudentasV>& studentaiV, int skaicius, const string& failas);
void skaitymo_laikas_vector(vector<StudentasV>& studentaiV, int skaicius, const string& failas);
void rusiavimo_laikas_vector(vector<StudentasV>& studentaiV, int skaicius, vector<StudentasV>& vargsiukai);
void isvedimo_vargsiukai_laikas_vector(const string& failas_vargsiukai, int skaicius, const vector<StudentasV>& vargsiukai);
void isvedimo_kietiakai_laikas_vector(const string& failas_kietiakai, int skaicius, const vector<StudentasV>& studentaiV);
void testavimas_vector(const string& failoPav, int skaicius, const string& kietiakaiF, const string& vargsiukaiF);

void rusiavimas_list(list<StudentasL>& studentaiL);
void generavimas_list(list<StudentasL>& studentaiL, int count, const string& failas);
void saugojimas_list(const string& failas, const list<StudentasL>& studentaiL);
void skaitymas_list(list<StudentasL>& studentaiL, const string& pav);

void rusiavimas_pagal_balus_list(list<StudentasL>& studentaiL, list<StudentasL>& vargsiukai);
void isvedimas_vargsiukai_list(const string& failas_vargsiukai, const list<StudentasL>& vargsiukai);
void isvedimas_kietiakai_list(const string& failas_kietiakai, const list<StudentasL>& studentaiL);

void generavimo_laikas_list(list<StudentasL>& studentaiL, int skaicius, const string& failas);
void skaitymo_laikas_list(list<StudentasL>& studentaiL, int skaicius, const string& failas);
void rusiavimo_laikas_list(list<StudentasL>& studentaiL, int skaicius, list<StudentasL>& vargsiukai);
void isvedimo_vargsiukai_laikas_list(const string& failas_vargsiukai, int skaicius, const list<StudentasL>& vargsiukai);
void isvedimo_kietiakai_laikas_list(const string& failas_kietiakai, int skaicius, const list<StudentasL>& studentaiL);
void testavimas_list(const string& failoPav, int skaicius, const string& kietiakaiF, const string& vargsiukaiF);

#endif // STUDENTAS_H_INCLUDED
