#include <iostream>
#include <iomanip>
#include "studentas.h"
#include <chrono>
#include <thread>

using namespace std;


int main()
{
    vector<StudentasV> studentaiV;
    list<StudentasL> studentaiL;
    int pasirinkimas_failai;
    char pasirinkimas_konteineris;
    char pasirinkimas_veiksmas;


    srand(time(0));


    cout << "Pasirinkite, ka norite daryti (r - ranka, a - atsitiktinai, f - nuskaityti is failo, t - testavimas): ";
    while (!(cin >> pasirinkimas_veiksmas) || (pasirinkimas_veiksmas != 'r' && pasirinkimas_veiksmas != 'R' && pasirinkimas_veiksmas != 'a' && pasirinkimas_veiksmas != 'A' && pasirinkimas_veiksmas != 'f' && pasirinkimas_veiksmas != 'F' && pasirinkimas_veiksmas != 't' && pasirinkimas_veiksmas != 'T'))
    {
        cout << "Pasirinkite r, a, f arba t: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (pasirinkimas_veiksmas == 'r' || pasirinkimas_veiksmas == 'R') {
        ivedimasRanka(studentaiV);
        spausdintiGalutiniusRezultatus(studentaiV);

    }

    else if (pasirinkimas_veiksmas == 'a' || pasirinkimas_veiksmas == 'A') {
        ivedimasAtsitiktinai(studentaiV);
        spausdintiGalutiniusRezultatus(studentaiV);
    }
    else if (pasirinkimas_veiksmas == 'f' || pasirinkimas_veiksmas == 'F') {
        ivedimasIsFailo(studentaiV);
        spausdintiGalutiniusRezultatus(studentaiV);

    }

    else if (pasirinkimas_veiksmas == 't' || pasirinkimas_veiksmas == 'T') {
        cout << "Pasirinkite ar norite generuoti failus (spauskite 1), ar atlikti testavima su failais (spauskite 2) " << endl;
        while (!(cin >> pasirinkimas_failai) || pasirinkimas_failai < 1 || pasirinkimas_failai > 2)
        {
            cout << "Pasirinkite 1 arba 2";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Pasirinkite ar norite naudoti vector konteineri (spauskite v) ar list konteineri (spauskite l) ?" << endl;
        while (!(cin >> pasirinkimas_konteineris) || (pasirinkimas_konteineris != 'v' && pasirinkimas_konteineris != 'V' && pasirinkimas_konteineris != 'l' && pasirinkimas_konteineris != 'L'))
        {
            cout << "Pasirinkite v arba l ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (pasirinkimas_failai == 1)
        {
            if (pasirinkimas_konteineris == 'v' || pasirinkimas_konteineris == 'V')
            {
                generavimo_laikas_vector(studentaiV, 1000, "studentai_1000.txt");
                generavimo_laikas_vector(studentaiV, 10000, "studentai_10000.txt");
                generavimo_laikas_vector(studentaiV, 100000, "studentai_100000.txt");
                generavimo_laikas_vector(studentaiV, 1000000, "studentai_1000000.txt");
                generavimo_laikas_vector(studentaiV, 10000000, "studentai_10000000.txt");

                cout << "-----------------------------------------------------" << endl;

                testavimas_vector("studentai_1000.txt", 1000, "kietiakai_1000.txt", "vargsiukai_1000.txt");
                testavimas_vector("studentai_10000.txt", 10000, "kietiakai_10000.txt", "vargsiukai_10000.txt");
                testavimas_vector("studentai_100000.txt", 100000, "kietiakai_100000.txt", "vargsiukai_100000.txt");
                testavimas_vector("studentai_1000000.txt", 1000000, "kietiakai_1000000.txt", "vargsiukai_1000000.txt");
                testavimas_vector("studentai_10000000.txt", 10000000, "kietiakai_10000000.txt", "vargsiukai_10000000.txt");
            }
            else
            {
                generavimo_laikas_list(studentaiL, 1000, "studentai_1000.txt");
                generavimo_laikas_list(studentaiL, 10000, "studentai_10000.txt");
                generavimo_laikas_list(studentaiL, 100000, "studentai_100000.txt");
                generavimo_laikas_list(studentaiL, 1000000, "studentai_1000000.txt");
                generavimo_laikas_list(studentaiL, 10000000, "studentai_10000000.txt");

                cout << "-----------------------------------------------------" << endl;
                testavimas_list("studentai_1000.txt", 1000, "kietiakai_1000.txt", "vargsiukai_1000.txt");
                testavimas_list("studentai_10000.txt", 10000, "kietiakai_10000.txt", "vargsiukai_10000.txt");
                testavimas_list("studentai_100000.txt", 100000, "kietiakai_100000.txt", "vargsiukai_100000.txt");
                testavimas_list("studentai_1000000.txt", 1000000, "kietiakai_1000000.txt", "vargsiukai_1000000.txt");
                testavimas_list("studentai_10000000.txt", 10000000, "kietiakai_10000000.txt", "vargsiukai_10000000.txt");
            }
        }
        else if (pasirinkimas_failai == 2)
        {
            if (pasirinkimas_konteineris == 'v' || pasirinkimas_konteineris == 'V')
            {
                testavimas_vector("studentai_1000.txt", 1000, "kietiakai_1000.txt", "vargsiukai_1000.txt");
                testavimas_vector("studentai_10000.txt", 10000, "kietiakai_10000.txt", "vargsiukai_10000.txt");
                testavimas_vector("studentai_100000.txt", 100000, "kietiakai_100000.txt", "vargsiukai_100000.txt");
                testavimas_vector("studentai_1000000.txt", 1000000, "kietiakai_1000000.txt", "vargsiukai_1000000.txt");
                testavimas_vector("studentai_10000000.txt", 10000000, "kietiakai_10000000.txt", "vargsiukai_10000000.txt");
            }
            else
            {
                testavimas_list("studentai_1000.txt", 1000, "kietiakai_1000.txt", "vargsiukai_1000.txt");
                testavimas_list("studentai_10000.txt", 10000, "kietiakai_10000.txt", "vargsiukai_10000.txt");
                testavimas_list("studentai_100000.txt", 100000, "kietiakai_100000.txt", "vargsiukai_100000.txt");
                testavimas_list("studentai_1000000.txt", 1000000, "kietiakai_1000000.txt", "vargsiukai_1000000.txt");
                testavimas_list("studentai_10000000.txt", 10000000, "kietiakai_10000000.txt", "vargsiukai_10000000.txt");
            }
        }
    }

    std::this_thread::sleep_for(std::chrono::seconds(30));
    return 0;
}