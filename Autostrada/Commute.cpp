#include <iostream>
#include <vector>

using namespace std;

// Typy danych

class Wierzcholek
{
public:
    int gdzieProwadzi;
    int waga;
};

const int MAXINT = 2147483647;

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************

int main()
{
    int start, koniec, n, liczbaSkrotow;
    int x, y, w;
    int i, j, u;

    start = 0;
    cin >> n >> liczbaSkrotow;
    koniec = n;
    n++;

    int liczbaKrawedzi = n + liczbaSkrotow - 1;

    // Tworzymy tablice dynamiczne
    int *tablicaKosztowD = new int[n]; // Tablica kosztów dojścia
    int *tablicasciezkiP = new int[n]; // Tablica poprzedników
    bool *QS = new bool[n];            // Zbiory Q i S
    int *tablicaWag = new int[n];
    vector<vector<Wierzcholek>> listaSasiedztwa; // Tablica list sąsiedztwa

    // przygotowanie tablicy danych
    for (i = 0; i < n; i++)
    {
        tablicaKosztowD[i] = MAXINT;
        tablicasciezkiP[i] = -1;
        QS[i] = false;
        vector<Wierzcholek> a;
        listaSasiedztwa.push_back(a);
    }
    for (int i = 0; i < n - 1; i++)
    {
        Wierzcholek NowyWierzcholek;           // Tworzymy element listy sąsiedztwa
        NowyWierzcholek.gdzieProwadzi = i + 1; // Wierzchołek docelowy krawędzi
        NowyWierzcholek.waga = 1;              // Waga krawędzi

        listaSasiedztwa[i].push_back(NowyWierzcholek); // Element dołączamy do listy
    }
    // Odczytujemy skroty
    for (i = 0; i < liczbaSkrotow; i++)
    {
        cin >> x >> y >> w; // Odczytujemy krawędź z wagą

        if (y > koniec)     //wykluczamy przypadek kiedy skrot jest za koncem trasy
            continue;

        Wierzcholek NowyWierzcholek;       // Tworzymy element listy sąsiedztwa
        NowyWierzcholek.gdzieProwadzi = y; // Wierzchołek docelowy krawędzi
        NowyWierzcholek.waga = w;          // Waga krawędzi

        listaSasiedztwa[x].push_back(NowyWierzcholek); // Element dołączamy do listy
    }

    tablicaKosztowD[start] = 0; // Koszt dojścia do wierzcholka startowego jest zerowy

    // Wyznaczamy ścieżki
    for (i = 0; i < n; i++)
    {
        for (j = 0; QS[j]; j++)
            ; //ustawiamy j na start nalezacy do Q (grafu niezanalizowanego)

        for (u = j++; j < n; j++)
            if (!QS[j] && (tablicaKosztowD[j] < tablicaKosztowD[u])) // Szukamy wierzchołka w Q o najmniejszym koszcie d
                u = j;

        QS[u] = true; // Znaleziony wierzchołek przenosimy do S

        // Modyfikujemy odpowiednio wszystkich sąsiadów u, którzy są w Q
        for (int k = 0; k < listaSasiedztwa[u].size(); k++)
            if (!QS[listaSasiedztwa[u][k].gdzieProwadzi] && (tablicaKosztowD[listaSasiedztwa[u][k].gdzieProwadzi] > tablicaKosztowD[u] + listaSasiedztwa[u][k].waga))
            {
                tablicaKosztowD[listaSasiedztwa[u][k].gdzieProwadzi] = tablicaKosztowD[u] + listaSasiedztwa[u][k].waga;
                tablicasciezkiP[listaSasiedztwa[u][k].gdzieProwadzi] = u;
            }
    }

    cout << tablicaKosztowD[koniec] << endl;

    return 0;
}
