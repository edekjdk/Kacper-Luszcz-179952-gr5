#include <iostream>
#include <vector>
#include <unordered_set>
#include <fstream>
#include <sstream>

using namespace std;

void wersja_1(vector<int>tab, int M) {
    vector<vector<int>> wyniki; //wektor przechowywujacy znalezione trojki
    int n = tab.size(); // dlugosc tablicy poczatkowej
    int l_trojek = 0; // zmienna do liczenia wystpien odpowiednich trojek

    if (n >=3) {
        for(int i=0; i<n-2; i++) {
            for(int j=i+1; j<n-1; j++) {
                for(int k=j+1; k<n; k++) { // 3 zagniedzone petle do sprawdzania wszystkich kombinacji
                    if(tab[i] + tab[j] + tab[k] == M) { // sprawdzamy czy suma danej kombinacji wynosi M
                        vector<int> trojka={tab[i],tab[j], tab[k]};

                        bool unikalna = true;
                        for(int l=0; l<wyniki.size(); l++) { // sprawdzamy czy aktualna trojka
                            if(wyniki[l] == trojka) {          //  znajduje sie w wynikach
                                unikalna = false;
                                break;
                            }
                        }

                        if(unikalna) {
                            wyniki.push_back(trojka); //dodajemy jesli trojka jest unikalna
                            l_trojek++; //
                        }
                    }
                }
            }
        }
    cout<< "wersja 1: Liczba kombinacji wynosi " << l_trojek <<": "; //wyswietlamy wyniki
    for(int i=0; i<wyniki.size(); i++) {
        cout <<"["<< wyniki[i][0] <<" "<< wyniki[i][1]<< " " << wyniki[i][2] << "] ";
    }
    cout << endl;
    } else {
        cout << "wersja 1: Liczba kombinacji wynosi 0." << endl;
    }

}

void wersja_2(vector<int>tab, int M) {
    vector<vector<int>> wyniki;
    int n = tab.size();
    int l_trojek = 0;

    if (n >=3) {
        for(int i=0; i<n-1; i++) {
            unordered_set<int> widziane;

            for(int j=i+1; j<n; j++) {
                int x = M - tab[i] - tab[j];

                if(widziane.find(x) != widziane.end()) {
                    vector<int> trojka = {tab[i], x, tab[j]};


                    bool unikalna = true;
                    for(int l=0; l<wyniki.size(); l++) { // sprawdzamy czy aktualna trojka
                        if(wyniki[l] == trojka) {          //  znajduje sie w wynikach
                            unikalna = false;
                            break;
                        }
                    }

                    if(unikalna) {
                        wyniki.push_back(trojka); //dodajemy jesli trojka jest unikalna
                        l_trojek++; //
                    }
                }
                widziane.insert(tab[j]);
            }
        }

        cout<< "wersja 2: Liczba kombinacji wynosi " << l_trojek <<": "; //wyswietlamy wyniki
        for(int i=0; i<wyniki.size(); i++) {
            cout <<"["<< wyniki[i][0] <<" "<< wyniki[i][1]<< " " << wyniki[i][2] << "] ";
        }
        cout << endl;
    } else {
        cout << "wersja 2: Liczba kombinacji wynosi 0." << endl;
    }
}

string plik_wejsciowy = "dane.txt";
string plik_wyjsciowy = "wyniki.txt";

void wczytaj_zapisz_do_pliku(const string& plik_we, const string& plik_wy, int wersja) {
    ifstream wejscie(plik_we);
    ofstream wyjscie(plik_wy, ios::app);

    if (!wejscie.is_open()) {
        cerr << "Nie mo¿na otworzyæ pliku wejœciowego!" << endl;
        return;
    }
    if (!wyjscie.is_open()) {
        cerr << "Nie mo¿na otworzyæ pliku wyjœciowego!" << endl;
        return;
    }

    vector<int> tab; // Tablica do przechowywania liczb
    int M;           // Wartoœæ M
    int zestaw_numer = 1; // Numer aktualnego zestawu danych

    while (true) {
        tab.clear();

        // Wczytaj tablicê liczb
        string linia;
        if (!getline(wejscie, linia)) break;
        stringstream ss(linia);
        int liczba;
        while (ss >> liczba) {
            tab.push_back(liczba);
        }

        // Wczytaj wartoœæ M
        if (!getline(wejscie, linia)) break;
        M = stoi(linia);

        // Wykonanie odpowiedniej wersji algorytmu

        // Przechwyæ wyniki z odpowiedniej wersji algorytmu
        stringstream wynik_stream;
        streambuf* poprzedni_bufor = cout.rdbuf(wynik_stream.rdbuf()); // Przekierowanie cout do strumienia
/*
        if (wersja == 1) {
            wersja_1(tab, M); // Twoja funkcja wersja_1 wypisuje wyniki na ekran
        } else if (wersja == 2) {
            wersja_2(tab, M); // Twoja funkcja wersja_2 wypisuje wyniki na ekran
        } else {
            cerr << "Nieprawid³owa wersja algorytmu: " << wersja << endl;
            cout.rdbuf(poprzedni_bufor); // Przywróæ cout
            return;
        }

            wersja_1(tab, M);
            wersja_2(tab, M);
            cout.rdbuf(poprzedni_bufor); // Przywróæ cout
            return;
*/
            wersja_1(tab, M);
           // wersja_2(tab, M);
        cout.rdbuf(poprzedni_bufor); // Przywróæ cout

        // Zapisz wyniki do pliku
        wyjscie << wynik_stream.str() << endl;
        zestaw_numer++;
    }

    cout << "Wyniki zapisano do pliku: " << plik_wy << endl;

    wejscie.close();
    wyjscie.close();
}


//Dane do testowania
vector<int>tab1={-5,6,1,2,5,1,2,1,2,4};
vector<int>tab2={};
vector<int>tab3={1,2,3,1,2,3,1,2,3};
vector<int>tab4={2,2,2,2,2,2,2,2};

int M=6;

//Funkcja testujaca wersje 1 algorytmu
void testy_wersji_1() {
    wersja_1(tab1, M);
    wersja_1(tab2, M);
    wersja_1(tab3, M);
    wersja_1(tab4, M);
}

//Funkcja testujaca wersje 2 algorytmu
void testy_wersji_2() {
    wersja_2(tab1, M);
    wersja_2(tab2, M);
    wersja_2(tab3, M);
    wersja_2(tab4, M);
}

int main()
{
    testy_wersji_1();
    testy_wersji_2();
    wczytaj_zapisz_do_pliku(plik_wejsciowy, plik_wyjsciowy,1); //wczytanie danych z pliku i zapis do pliku wynikow wersji 1
    wczytaj_zapisz_do_pliku(plik_wejsciowy, plik_wyjsciowy,2); //wczytanie danych z pliku i zapis do pliku wynikow wersji 2
    return 0;
}
