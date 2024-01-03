#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <numeric>
#include <algorithm>
#include "studentas.h"

using namespace std;

void generavimas_list(list<StudentasL>& studentaiL, int count, const string& failas) {
    studentaiL.clear();
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

    for (int i = 1; i <= count; i++) {
        StudentasL studentas;
        studentas.setVardas("Vardas" + to_string(i));
        studentas.setPavarde("Pavarde" + to_string(i));

        F << setw(15) << studentas.getVardas() << " " << setw(15) << studentas.getPavarde();
        for (int j = 0; j < 10; j++) {
            studentas.getNamuDarbai().push_back(rand() % 10 + 1);
            F << setw(4) << studentas.getNamuDarbai().back();
        }

        studentas.setEgzaminoRezultatas(rand() % 10 + 1);
        F << setw(8) << studentas.getEgzaminoRezultatas() << endl;

        studentaiL.push_back(studentas);
    }

    F.close();
}

float galutinisBalasList(const StudentasL& studentas) {
    std::list<int>& namuDarbai = const_cast<StudentasL&>(studentas).getNamuDarbai();

    float vidurkis = accumulate(namuDarbai.begin(), namuDarbai.end(), 0.0) / namuDarbai.size();

    return 0.4 * vidurkis + 0.6 * studentas.getEgzaminoRezultatas();
}

void saugojimas_list(const string& failas, const list<StudentasL>& studentaiL)
{
    ofstream F(failas);
    if (!F) {
        cerr << "Nepavyko atidaryti failo " << failas << endl;
        return;
    }

    F << left << setw(15) << "Vardas" << setw(15) << " Pavarde" << setw(15) << "Galutinis " << setw(15) << endl;
    for (const StudentasL& studentas : studentaiL) {
        F << setw(15) << studentas.getVardas() << " " << setw(15) << studentas.getPavarde();
        F << " " << fixed << setprecision(2) << setw(16) << studentas.getGalutinisBalas() << " " << fixed << setprecision(2) << "\n";
    }
    F.close();
}

void skaitymas_list(list<StudentasL>& studentaiL, const string& pav) {
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
            StudentasL studentas;

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

            studentaiL.push_back(studentas);
        }
        F.close();
    }
    catch (const exception& e) {
        cerr << "Failas neperskaitomas" << e.what() << endl;
    }
}


void rusiavimas_list(list<StudentasL>& studentaiL) {
    studentaiL.sort([](const StudentasL& a, const StudentasL& b) {
        return a.getPavarde() < b.getPavarde();
        });
}

void rusiavimas_pagal_balus_list(list<StudentasL>& studentaiL, list<StudentasL>& vargsiukai)
{
    auto partitionIt = std::partition(studentaiL.begin(), studentaiL.end(), [](const StudentasL& studentas) {
        return studentas.getGalutinisBalas() >= 5;
        });

    vargsiukai.clear();
    std::move(partitionIt, studentaiL.end(), std::back_inserter(vargsiukai));

    studentaiL.erase(partitionIt, studentaiL.end());
}

void isvedimas_vargsiukai_list(const string& failas_vargsiukai, const list<StudentasL>& vargsiukai) {
    list<StudentasL> sortedVargsiukai = vargsiukai;
    sortedVargsiukai.sort([](const StudentasL& a, const StudentasL& b) {
        int aSkaicius = stoi(a.getVardas().substr(6));
        int bSkaicius = stoi(b.getVardas().substr(6));

        if (aSkaicius != bSkaicius) {
            return aSkaicius < bSkaicius;
        }
        return a.getPavarde() < b.getPavarde();
        });

    saugojimas_list(failas_vargsiukai, sortedVargsiukai);
}

void isvedimas_kietiakai_list(const string& failas_kietiakai, const list<StudentasL>& studentaiL)
{
    list<StudentasL> sortedKietiakai = studentaiL;
    sortedKietiakai.sort([](const StudentasL& a, const StudentasL& b) {
        int aSkaicius = stoi(a.getVardas().substr(6));
        int bSkaicius = stoi(b.getVardas().substr(6));

        if (aSkaicius != bSkaicius) {
            return aSkaicius < bSkaicius;
        }
        return a.getPavarde() < b.getPavarde();
        });

    saugojimas_list(failas_kietiakai, sortedKietiakai);
}

void generavimo_laikas_list(list<StudentasL>& studentaiL, int skaicius, const string& failas) {
    auto start = std::chrono::steady_clock::now();
    generavimas_list(studentaiL, skaicius, failas);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = end - start;
    cout << skaicius << " irasu failo generavimo laikas: " << duration.count() << endl;
}

void skaitymo_laikas_list(list<StudentasL>& studentaiL, int skaicius, const string& failas) {
    auto start = std::chrono::steady_clock::now();
    skaitymas_list(studentaiL, failas);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = end - start;
}

void rusiavimo_laikas_list(list<StudentasL>& studentaiL, int skaicius, list<StudentasL>& vargsiukai) {
    auto start = std::chrono::steady_clock::now();
    rusiavimas_pagal_balus_list(studentaiL, vargsiukai);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = end - start;
}

void isvedimo_vargsiukai_laikas_list(const string& failas_vargsiukai, int skaicius, const list<StudentasL>& vargsiukai) {
    auto start = std::chrono::steady_clock::now();
    isvedimas_vargsiukai_list(failas_vargsiukai, vargsiukai);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = end - start;
}

void isvedimo_kietiakai_laikas_list(const string& failas_kietiakai, int skaicius, const list<StudentasL>& studentaiL) {
    auto start = std::chrono::steady_clock::now();
    isvedimas_kietiakai_list(failas_kietiakai, studentaiL);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> duration = end - start;
}
