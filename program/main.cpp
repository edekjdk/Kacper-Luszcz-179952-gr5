#include <iostream>
#include <vector>
#include <unordered_set>
#include <fstream>
#include <sstream>

using namespace std;

string plik_wejsciowy = "dane.txt";
string plik_wyjsciowy = "wyniki.txt";


void wyswietl_wyniki_i_zapisz(vector<vector<int>>wyniki, int l_trojek, int wersja, int n) {
    static bool czy_pliku_czyszczono = false; // Flaga do jednorazowego czyszczenia pliku
    if (!czy_pliku_czyszczono) {
        ofstream plik_czyszczenie(plik_wyjsciowy, ios::trunc);
        plik_czyszczenie.close();
        czy_pliku_czyszczono = true; // Plik został wyczyszczony
    }


    ofstream plik(plik_wyjsciowy, ios::app);
        if(plik.is_open()) {
        cout<< "wersja "<<wersja<<": Liczba kombinacji wynosi " << l_trojek <<": "; //wyswietlamy wyniki
        plik << "wersja "<<wersja<<": Liczba kombinacji wynosi " << l_trojek <<": ";
        for(int i=0; i<wyniki.size(); i++) {
            cout <<"["<< wyniki[i][0] <<" "<< wyniki[i][1]<< " " << wyniki[i][2] << "] ";
            plik << "["<< wyniki[i][0] <<" "<< wyniki[i][1]<< " " << wyniki[i][2] << "] ";
        }
        }
        plik << "\n";
        cout << endl;
        plik.close();
        if(n<3) {
            cout << "wersja "<<wersja<<": Liczba kombinacji wynosi 0." << endl;
            ofstream plik(plik_wyjsciowy, ios::app);
            if (plik.is_open()) {
                plik<< "wersja "<<wersja<<": Liczba kombinacji wynosi 0." << endl;
                plik.close();
            }
        }
}


void wersja_1(vector<int>tab, int M, bool sprawdz_unikalnosc) {
    vector<vector<int>> wyniki; //wektor przechowywujacy znalezione trojki
    int n = tab.size(); // dlugosc tablicy poczatkowej
    int l_trojek = 0; // zmienna do liczenia wystpien odpowiednich trojek
    int wersja = 1;

    if (n >=3) {
        for(int i=0; i<n-2; i++) {
            for(int j=i+1; j<n-1; j++) {
                for(int k=j+1; k<n; k++) { // 3 zagniedzone petle do sprawdzania wszystkich kombinacji
                    if(tab[i] + tab[j] + tab[k] == M) { // sprawdzamy czy suma danej kombinacji wynosi M
                        vector<int> trojka={tab[i],tab[j], tab[k]};

                        if(sprawdz_unikalnosc) {
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
                    } else {
                        wyniki.push_back(trojka);
                        l_trojek++;
                    }
                    }
                }
            }
        }
    wyswietl_wyniki_i_zapisz(wyniki, l_trojek, wersja, n);
    }
}

void wersja_2(vector<int>tab, int M, bool sprawdz_unikalnosc) {
    vector<vector<int>> wyniki;
    int n = tab.size();
    int l_trojek = 0;
    int wersja = 2;

    if (n >=3) {
        for(int i=0; i<n-1; i++) {
            unordered_set<int> widziane;

            for(int j=i+1; j<n; j++) {
                int x = M - tab[i] - tab[j];

                if(widziane.find(x) != widziane.end()) {
                    vector<int> trojka = {tab[i], x, tab[j]};

                    if(sprawdz_unikalnosc) {

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
                    } else {
                        wyniki.push_back(trojka);
                        l_trojek++;
                    }
                }
                widziane.insert(tab[j]);
            }
        }
    wyswietl_wyniki_i_zapisz(wyniki, l_trojek, wersja,n);
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
        bool sprawdz_unikalnosc=false;
        wersja_1(tab, M, sprawdz_unikalnosc);
        wersja_2(tab, M, sprawdz_unikalnosc);

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
    bool sprawdz_unikalnosc=true;
    wersja_1(tab1, M, sprawdz_unikalnosc);
    wersja_1(tab2, M, sprawdz_unikalnosc);
    wersja_1(tab3, M, sprawdz_unikalnosc);
    wersja_1(tab4, M, sprawdz_unikalnosc);
}

//Funkcja testujaca wersje 2 algorytmu
void testy_wersji_2() {
    bool sprawdz_unikalnosc=true;
    wersja_2(tab1, M, sprawdz_unikalnosc);
    wersja_2(tab2, M, sprawdz_unikalnosc);
    wersja_2(tab3, M, sprawdz_unikalnosc);
    wersja_2(tab4, M, sprawdz_unikalnosc);
}

int main()
{
    testy_wersji_1();
    testy_wersji_2();
    //wczytaj_z_pliku(plik_wejsciowy); //wczytanie danych z pliku

    return 0;
}
