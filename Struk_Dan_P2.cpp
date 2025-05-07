// Struk_Dan_P2.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "Kolejkapriorytetowa_kopiec.h"
#include "Priorityqueue_tablica.h"

#include <fstream>
#include <sstream>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

vector<vector<pair<string, int>>> wczytaj_dane(const string& nazwa_pliku, int rozmiar) {
    ifstream plik(nazwa_pliku);
    vector<vector<pair<string, int>>> zbiory;
    string linia;
    vector<pair<string, int>> aktualny_zbior;

    while (getline(plik, linia)) {
        if (linia == "---") {
            if (!aktualny_zbior.empty()) {
                zbiory.push_back(aktualny_zbior);
                aktualny_zbior.clear();
            }
        }
        else {
            stringstream ss(linia);
            string nazwa;
            int priorytet;
            ss >> nazwa >> priorytet;
            aktualny_zbior.emplace_back(nazwa, priorytet);
        }
    }// pobiera dane z pliku i zapisuje je w zbiorach w tablicy

    if (!aktualny_zbior.empty()) {
        zbiory.push_back(aktualny_zbior); // dodaje ostatni zestaw
    }

    return zbiory;
}

void test() {
    vector<int> rozmiary = { 5000, 8000, 10000, 16000, 20000, 40000, 60000, 100000 };
    string operacja = "extract_max_altenative_kp_kopiec";
    ofstream csv("wyniki_" + operacja + ".csv");
    csv << "rozmiar,czas_usredniony_ns\n";

    for (int rozmiar : rozmiary) {
        string plik_danych = "dane_" + to_string(rozmiar) + ".txt";
        auto zbiory = wczytaj_dane(plik_danych, rozmiar);

        long long suma_czasu = 0;

        for (const auto& zbior : zbiory) { //operujemy na jednym z 10 zbiorów danych dla danego rozmiaru
            for (int i = 0; i < 100; ++i) { // powtarzamy operacje 100 razy dla tego samego zbioru dla lepszego uśrednienia wyników
                Kolejkapriorytetowa_kopiec pq;
                for (int j = 0; j < zbior.size() - 1; ++j) {
                    pq.insert(zbior[j].first, zbior[j].second);
                }

                

                auto start = high_resolution_clock::now();
                //for (int i = 0; i < 100; ++i) {
                    pq.extract_max(); //wykonywana operacja
                //}
                    auto end = high_resolution_clock::now();
                
                auto czas = duration_cast<nanoseconds>(end - start).count();
                suma_czasu += czas;
            }
        }

        double sredni_czas = static_cast<double>(suma_czasu) / (zbiory.size() * 100);// uśrednienie czasów
        csv << rozmiar << "," << sredni_czas << "\n";
        cout << "Zakonczono: " << rozmiar << " - średni czas: " << sredni_czas << " ns\n";
    }// zapisuje do pliku średnie wyniki danej operacji dla każdego rozmiaru struktury (operacja zmieniana jest ręcznie dla każdego testu, wraz z nazwą pliku do którego zostanie zapisana)

    csv.close();
}



int main()
{
    test(); // wykonujemy zadany wyżej test
}
// Uruchomienie programu: Ctrl + F5 lub menu Debugowanie > Uruchom bez debugowania
// Debugowanie programu: F5 lub menu Debugowanie > Rozpocznij debugowanie

// Porady dotyczące rozpoczynania pracy:
//   1. Użyj okna Eksploratora rozwiązań, aby dodać pliki i zarządzać nimi
//   2. Użyj okna programu Team Explorer, aby nawiązać połączenie z kontrolą źródła
//   3. Użyj okna Dane wyjściowe, aby sprawdzić dane wyjściowe kompilacji i inne komunikaty
//   4. Użyj okna Lista błędów, aby zobaczyć błędy
//   5. Wybierz pozycję Projekt > Dodaj nowy element, aby utworzyć nowe pliki kodu, lub wybierz pozycję Projekt > Dodaj istniejący element, aby dodać istniejące pliku kodu do projektu
//   6. Aby w przyszłości ponownie otworzyć ten projekt, przejdź do pozycji Plik > Otwórz > Projekt i wybierz plik sln
