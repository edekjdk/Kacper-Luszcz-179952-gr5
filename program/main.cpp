#include <iostream>
#include <vector>


using namespace std;

void wersja_1(vector<int>tab, int M) {
    vector<vector<int>> wyniki; //wektor przechowywujacy znalezione trojki
    int n = tab.size(); // dlugosc tablicy poczatkowej
    int l_trojek = 0; // zmienna do liczenia wystpien odpowiednich trojek

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
                        l_trojek++;
                    }
                }
            }
        }
    }

    cout<< "Liczba kombinacji wynosi " << l_trojek <<": ";
    for(int i=0; i<wyniki.size(); i++) {
        cout <<"["<< wyniki[i][0] <<" "<< wyniki[i][1]<< " " << wyniki[i][2] << "] "; //wyswietlamy wyniki
    }

}

int main()
{
    vector<int>tab={1,2,5,1,2,1,2,4};
    int M = 6;
    wersja_1(tab, M);
    return 0;
}
