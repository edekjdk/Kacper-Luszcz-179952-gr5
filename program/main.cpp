#include <iostream>
#include <vector>
#include <unordered_set>
#include <fstream>
#include <sstream>

using namespace std;

string plik_wejsciowy = "dane.txt";
string plik_wyjsciowy = "wyniki.txt";


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

    ofstream plik(plik_wyjsciowy, ios::app);
    if(plik.is_open()) {
    cout<< "wersja 1: Liczba kombinacji wynosi " << l_trojek <<": "; //wyswietlamy wyniki
    plik << "wersja 1: Liczba kombinacji wynosi " << l_trojek <<": ";
    for(int i=0; i<wyniki.size(); i++) {
        cout <<"["<< wyniki[i][0] <<" "<< wyniki[i][1]<< " " << wyniki[i][2] << "] ";
        plik << "["<< wyniki[i][0] <<" "<< wyniki[i][1]<< " " << wyniki[i][2] << "] ";
    }
    }
    plik << "\n";
    cout << endl;
    plik.close();
    } else {
        cout << "wersja 1: Liczba kombinacji wynosi 0." << endl;
        ofstream plik(plik_wyjsciowy, ios::app);
        if (plik.is_open()) {
            plik << "wersja 1: Liczba kombinacji wynosi 0." << endl;
            plik.close();
        }
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
        ofstream plik(plik_wyjsciowy, ios::app);
        if(plik.is_open()) {

        cout<< "wersja 2: Liczba kombinacji wynosi " << l_trojek <<": "; //wyswietlamy wyniki
        plik << "wersja 2: Liczba kombinacji wynosi " << l_trojek <<": ";

        for(int i=0; i<wyniki.size(); i++) {
            cout <<"["<< wyniki[i][0] <<" "<< wyniki[i][1]<< " " << wyniki[i][2] << "] ";
            plik << "["<< wyniki[i][0] <<" "<< wyniki[i][1]<< " " << wyniki[i][2] << "] ";

        }
        plik << "\n";
        cout << endl;
        plik.close();
    } else {
        cout << "wersja 2: Liczba kombinacji wynosi 0." << endl;
        ofstream plik(plik_wyjsciowy, ios::app);
        if (plik.is_open()) {
            plik << "wersja 2: Liczba kombinacji wynosi 0." << endl;
            plik.close();
        }
    }
}

}

void wczytaj_z_pliku(string plik_wejsciowy) {
    ifstream wejscie(plik_wejsciowy);

    if (!wejscie.is_open()) {
        cout << "Nie mozna otworzyc pliku wejsciowego!" << endl;
        return;
    }

    vector<int> tab; // Tablica do przechowywania liczb
    int M;           // Wartosc
    int zestaw_numer = 1;

    while (true) {
        tab.clear();

        // Wczytaj tablice liczb
        string linia;
        if (!getline(wejscie, linia)) break;
        stringstream ss(linia);
        int liczba;
        while (ss >> liczba) {
            tab.push_back(liczba);
        }

        // Wczytaj wartosc M
        if (!getline(wejscie, linia)) break;
        M = stoi(linia);

        wersja_1(tab, M);
        wersja_2(tab, M);

        zestaw_numer++;
    }
    wejscie.close();

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
    //testy_wersji_1();
    //testy_wersji_2();
    wczytaj_z_pliku(plik_wejsciowy); //wczytanie danych z pliku

    return 0;
}
