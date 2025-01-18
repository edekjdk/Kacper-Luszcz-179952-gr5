#include <iostream>
#include <vector>
#include <unordered_set>

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


int main()
{
    vector<int>tab1={-5,6,1,2,5,1,2,1,2,4};
    vector<int>tab2={};
    vector<int>tab3={1,2,3,1,2,3,1,2,3};
    vector<int>tab4={2,2,2,2,2,2,2,2};
    int M = 6;
    wersja_1(tab1, M);
    wersja_2(tab1, M);
    wersja_1(tab2, M);
    wersja_2(tab2, M);
    wersja_1(tab3, M);
    wersja_2(tab3, M);
    wersja_1(tab4, M);
    wersja_2(tab4, M);
    return 0;
}
