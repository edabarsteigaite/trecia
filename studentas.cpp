#include "studentas.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>


using namespace std;

int generuotiAtsitiktiniBalai(int min, int max) {
    return rand() % (max - min + 1) + min;
}

bool lyginimasPagalVardus(const StudentasV& a, const StudentasV& b) {
    if (a.getVardas() == b.getVardas()) {
        return a.getPavarde() < b.getPavarde();
    }
    return a.getVardas() < b.getVardas();
}

double skaiciuotiGalutiniVidurki(const vector<int>& namu_darbai, int egzamino_rezultatas) {
    double namuDarbuVidurkis = 0.0;
    if (!namu_darbai.empty()) {
        for (int rezultatas : namu_darbai) {
            namuDarbuVidurkis += rezultatas;
        }
        namuDarbuVidurkis /= namu_darbai.size();
    }
    return 0.4 * namuDarbuVidurkis + 0.6 * egzamino_rezultatas;
}

double skaiciuotiGalutiniMediana(const vector<int>& namu_darbai, int egzamino_rezultatas) {
    vector<int> surikiuoti_namu_darbai = namu_darbai;
    sort(surikiuoti_namu_darbai.begin(), surikiuoti_namu_darbai.end());

    if (surikiuoti_namu_darbai.size() % 2 == 0) {
        int vidurinis1 = surikiuoti_namu_darbai[surikiuoti_namu_darbai.size() / 2 - 1];
        int vidurinis2 = surikiuoti_namu_darbai[surikiuoti_namu_darbai.size() / 2];
        double mediana = (vidurinis1 + vidurinis2) / 2.0;
        return 0.4 * mediana + 0.6 * egzamino_rezultatas;
    }
    else {
        int vidurinis = surikiuoti_namu_darbai[surikiuoti_namu_darbai.size() / 2];
        return 0.4 * vidurinis + 0.6 * egzamino_rezultatas;
    }
}

void skaitytiDuomenisIsFailo(const string& failoPavadinimas, vector<StudentasV>& studentaiV) {
    ifstream failas(failoPavadinimas);
    if (!failas.is_open()) {
        cerr << "Klaida: Failas " << failoPavadinimas << " neegzistuoja arba negalima atidaryti." << endl;
        return;
    }
    string eilute;
    getline(failas, eilute);

    while (getline(failas, eilute)) {
        istringstream iss(eilute);
        StudentasV naujasStudentas;

        string vardas, pavarde;
        iss >> vardas >> pavarde;
        naujasStudentas.setVardas(vardas);
        naujasStudentas.setPavarde(pavarde);

        int balas;
        while (iss >> balas) {
            naujasStudentas.getNamuDarbai().push_back(balas);
        }

        if (naujasStudentas.getNamuDarbai().size() > 0) {
            naujasStudentas.setEgzaminoRezultatas(naujasStudentas.getNamuDarbai().back());
            naujasStudentas.getNamuDarbai().pop_back();
        }

        studentaiV.push_back(naujasStudentas);
    }

    failas.close();
}


void ivedimasRanka(vector<StudentasV>& studentaiV) {
    char testi;
    do {
        StudentasV naujasStudentas;

        cout << "Iveskite studento varda: ";
        string vardas;
        cin >> vardas;
        naujasStudentas.setVardas(vardas);

        cout << "Iveskite studento pavarde: ";
        string pavarde;
        cin >> pavarde;
        naujasStudentas.setPavarde(pavarde);

        cout << "Iveskite namu darbu rezultatus (iveskite -1, jei norite baigti): ";


        int namuDarbuRezultatas;
        do {
            while (true) {
                if (!(cin >> namuDarbuRezultatas)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Klaida: Netinkama ivestis. Iveskite balus nuo 1 iki 10: ";
                }
                else if (namuDarbuRezultatas == -1) {
                    break;
                }
                else if (namuDarbuRezultatas < 1 || namuDarbuRezultatas > 10) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Klaida: Netinkamas balas. Iveskite balus nuo 1 iki 10: ";
                }
                else {
                    naujasStudentas.getNamuDarbai().push_back(namuDarbuRezultatas);
                    break;
                }
            }
        } while (namuDarbuRezultatas != -1);

        cout << "Iveskite egzamino rezultata: ";
        int egzaminoRezultatas;
        while (true) {
            if (!(cin >> egzaminoRezultatas)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Klaida: Netinkama ivestis." << endl;
            }
            else if (egzaminoRezultatas < 1 || egzaminoRezultatas > 10) {
                cout << "Klaida: Netinkamas balas." << endl;
            }
            else {
                naujasStudentas.setEgzaminoRezultatas(egzaminoRezultatas);
                break;
            }
        }

        studentaiV.push_back(naujasStudentas);

        cout << "Ar norite ivesti dar viena studenta? (t/n): ";
        cin >> testi;
    } while (testi == 't' || testi == 'T');
}


void ivedimasAtsitiktinai(vector<StudentasV>& studentaiV) {
    char testi;
    do {
        StudentasV naujasStudentas;

        cout << "Iveskite studento varda: ";
        string vardas;
        cin >> vardas;
        naujasStudentas.setVardas(vardas);

        cout << "Iveskite studento pavarde: ";
        string pavarde;
        cin >> pavarde;
        naujasStudentas.setPavarde(pavarde);

        int namuDarbuSkaicius = generuotiAtsitiktiniBalai(1, 10);
        cout << "Generuoti atsitiktiniai namu darbu rezultatai (" << namuDarbuSkaicius << "): ";
        for (int i = 0; i < namuDarbuSkaicius; i++) {
            int balas = generuotiAtsitiktiniBalai(1, 10);
            naujasStudentas.getNamuDarbai().push_back(balas);
            cout << balas << " ";
        }
        cout << endl;

        naujasStudentas.setEgzaminoRezultatas(generuotiAtsitiktiniBalai(1, 10));
        cout << "Generuotas atsitiktinis egzamino rezultatas: " << naujasStudentas.getEgzaminoRezultatas() << endl;

        studentaiV.push_back(naujasStudentas);

        cout << "Ar norite ivesti dar viena studenta? (t/n): ";
        cin >> testi;
    } while (testi == 't' || testi == 'T');
}


void ivedimasIsFailo(vector<StudentasV>& studentaiV) {
    string failoPavadinimas;
    cout << "Iveskite failo pavadinima: ";
    cin >> failoPavadinimas;

    skaitytiDuomenisIsFailo(failoPavadinimas, studentaiV);
}

void spausdintiGalutiniusRezultatus(const vector<StudentasV>& studentaiV) {
    cout << "\nGalutiniai rezultatai:\n";
    cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(20) << "Galutinis (Vid.)" << setw(20) << "Galutinis (Med.)" << endl;
    cout << string(70, '-') << endl;

    for (const StudentasV& studentas : studentaiV) {
        double galutinisVidurkiu = skaiciuotiGalutiniVidurki(studentas.getNamuDarbai(), studentas.getEgzaminoRezultatas());
        double galutinisMediana = skaiciuotiGalutiniMediana(studentas.getNamuDarbai(), studentas.getEgzaminoRezultatas());

        cout << setw(15) << studentas.getVardas() << setw(15) << studentas.getPavarde() << fixed << setprecision(2)
            << setw(20) << galutinisVidurkiu << setw(20) << galutinisMediana << endl;
    }
}
