#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <numeric>
#include <iomanip>
#include <string>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <list>
#include "studentas.h"

using namespace std;

void generavimas_vector(vector<StudentasV>& studentaiV, int count, const string& failas) {
    studentaiV.clear();
    srand(time(nullptr));

    ofstream F(failas);
    if (!F) {
        cerr << "Nepavyko atidaryti failo " << failas << endl;
        return;
    }

    F << left << setw(15) << "Vardas" << setw(15) << "Pavarde";
    for (int i = 1; i <= 10; i++) {
        F << setw(4) << "ND" + to_string(i);
    }
    F << setw(8) << "Egzaminas" << endl;

    studentaiV.reserve(count);

    for (int i = 1; i <= count; i++) {
        StudentasV studentas;
        studentas.setVardas("Vardas" + to_string(i));
        studentas.setPavarde("Pavarde" + to_string(i));
        studentaiV.push_back(studentas);

        F << setw(15) << studentas.getVardas() << " " << setw(15) << studentas.getPavarde();
        for (int j = 0; j < 10; j++) {
            studentas.getNamuDarbai().push_back(rand() % 10 + 1);
            F << setw(4) << studentas.getNamuDarbai()[j];
        }
        studentas.setEgzaminoRezultatas(rand() % 10 + 1);
        F << setw(8) << studentas.getEgzaminoRezultatas() << endl;
    }

    F.close();
}




void saugojimas_vector(const string& failas, const vector<StudentasV>& studentaiV)
{
    ofstream F(failas);
    if (!F) {
        cerr << "Nepavyko atidaryti failo " << failas << endl;
        return;
    }

    F << left << setw(15) << "Vardas" << setw(15) << " Pavarde" << setw(15) << "Galutinis " << setw(15) << endl;
    for (const StudentasV& studentas : studentaiV) {
        F << setw(15) << studentas.getVardas() << " " << setw(15) << studentas.getPavarde();
        F << " " << fixed << setprecision(2) << setw(16) << studentas.getGalutinisBalas() << " " << fixed << setprecision(2) << "\n";
    }
    F.close();
}


void skaitymas_vector(vector<StudentasV>& studentaiV, const string& pav) {
    ifstream F(pav);

    try {
        if (!F) {
            throw runtime_error("Failas neegzistuoja: " + pav);
        }

        string line;
        bool firstLine = true;
        while (getline(F, line)) {
            if (firstLine) {
                firstLine = false;
                continue;
            }
            istringstream iss(line);
            StudentasV studentas;

            string vardas, pavarde;
            iss >> vardas >> pavarde;
            studentas.setVardas(vardas);
            studentas.setPavarde(pavarde);
            for (int i = 0; i < 10; i++) {
                int pazymys;
                iss >> pazymys;
                studentas.getNamuDarbai().push_back(pazymys);
            }

            int egzaminoRezultatas;
            iss >> egzaminoRezultatas;
            studentas.setEgzaminoRezultatas(egzaminoRezultatas);

            float vidurkis = accumulate(studentas.getNamuDarbai().begin(), studentas.getNamuDarbai().end(), 0.0) / studentas.getNamuDarbai().size();
            studentas.setGalutinisBalas(0.4 * vidurkis + 0.6 * studentas.getEgzaminoRezultatas());

            studentaiV.push_back(studentas);
        }
        F.close();
    }
    catch (const exception& e) {
        cerr << "Failas neperskaitomas" << e.what() << endl;
    }
}





float galutinisBalasVector(const StudentasV& studentas) {

    std::vector<int>& namuDarbai = const_cast<StudentasV&>(studentas).getNamuDarbai();

    float vidurkis = accumulate(namuDarbai.begin(), namuDarbai.end(), 0.0) / namuDarbai.size();

    return 0.4 * vidurkis + 0.6 * studentas.getEgzaminoRezultatas();
}



void rusiavimas_vector(vector<StudentasV>& studentai) {
    std::sort(studentai.begin(), studentai.end(), [](const StudentasV& a, const StudentasV& b) {
        return a.getPavarde() < b.getPavarde();
        });
}


void rusiavimas_pagal_balus_vector(vector<StudentasV>& studentaiV, vector<StudentasV>& vargsiukai)
{
    auto partitionIt = std::partition(studentaiV.begin(), studentaiV.end(), [](const StudentasV& studentas) {
        return studentas.getGalutinisBalas() >= 5;
        });

    vargsiukai.clear();
    std::move(partitionIt, studentaiV.end(), std::back_inserter(vargsiukai));
    studentaiV.erase(partitionIt, studentaiV.end());
}



void isvedimas_vargsiukai_vector(const string& failas_vargsiukai, const vector<StudentasV>& vargsiukai)
{
    vector<StudentasV> sortedVargsiukai = vargsiukai;
    sort(sortedVargsiukai.begin(), sortedVargsiukai.end(), [](const StudentasV& a, const StudentasV& b) {
        int aSkaicius = stoi(a.getVardas().substr(6));
        int bSkaicius = stoi(b.getVardas().substr(6));

        if (aSkaicius != bSkaicius) {
            return aSkaicius < bSkaicius;
        }
        return a.getPavarde() < b.getPavarde();
        });

    saugojimas_vector(failas_vargsiukai, sortedVargsiukai);
}

void isvedimas_kietiakai_vector(const string& failas_kietiakai, const vector<StudentasV>& studentaiV)
{
    vector<StudentasV> sortedKietiakai = studentaiV;
    sort(sortedKietiakai.begin(), sortedKietiakai.end(), [](const StudentasV& a, const StudentasV& b) {
        int aSkaicius = stoi(a.getVardas().substr(6));
        int bSkaicius = stoi(b.getVardas().substr(6));

        if (aSkaicius != bSkaicius) {
            return aSkaicius < bSkaicius;
        }

        return a.getPavarde() < b.getPavarde();
        });

    saugojimas_vector(failas_kietiakai, sortedKietiakai);
}



void generavimo_laikas_vector(vector<StudentasV>& studentaiV, int skaicius, const string& failas) {
    auto start = std::chrono::steady_clock::now();
    generavimas_vector(studentaiV, skaicius, failas);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = end - start;
    cout << skaicius << " irasu generavimo laikas: " << duration.count() << endl;
}

void skaitymo_laikas_vector(vector<StudentasV>& studentaiV, int skaicius, const string& failas) {
    auto start = std::chrono::steady_clock::now();
    skaitymas_vector(studentaiV, failas);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = end - start;
}

void rusiavimo_laikas_vector(vector<StudentasV>& studentaiV, int skaicius, vector<StudentasV>& vargsiukai) {
    auto start = std::chrono::steady_clock::now();
    rusiavimas_pagal_balus_vector(studentaiV, vargsiukai);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = end - start;
}

void isvedimo_vargsiukai_laikas_vector(const string& failas_vargsiukai, int skaicius, const vector<StudentasV>& vargsiukai) {
    auto start = std::chrono::steady_clock::now();
    isvedimas_vargsiukai_vector(failas_vargsiukai, vargsiukai);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = end - start;
}

void isvedimo_kietiakai_laikas_vector(const string& failas_kietiakai, int skaicius, const vector<StudentasV>& studentaiV) {
    auto start = std::chrono::steady_clock::now();
    isvedimas_kietiakai_vector(failas_kietiakai, studentaiV);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = end - start;
}
