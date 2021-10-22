#include <iostream>
#include <vector>

using namespace std;

// Typy danych

class Wierzcholek
{
public:
    int wartoscBezMerge;
    int gdzieProwadzi;
    int waga;
};

class Skrot
{
public:
    int skadProwadzi;
    int gdzieProwadzi;
    int waga;
};

const int MAXINT = 2147483647;

// **********************
// *** PROGRAM GŁÓWNY ***
// **********************
int znajdzPozycjePoMerge(int szukanyWierzcholek, vector<vector<Wierzcholek>> lista)
{
    if (szukanyWierzcholek == 0)
        return 0;
    for (int i = 0; i < lista.size(); i++)
    {
        for (int j = 0; j < lista[i].size(); j++)
        {
            if (lista[i][j].wartoscBezMerge == szukanyWierzcholek)
                return lista[i][j].gdzieProwadzi;
        }
    }
    return -10000;
}
int zwracaKolejnyPotrzebny(int poprzedni, bool *potrzebne, int koniec)
{
    for (int i = poprzedni; i <= koniec; i++)
    {
        if (potrzebne[i])
            return i;
    }
    return -10000;
}
int main()
{
    int start, koniec, n, liczbaSkrotow;
    int x, y, w;
    int i, j, u;

    start = 0;
    cin >> koniec >> liczbaSkrotow;

    bool *potrzebneWierzcholki = new bool[koniec + 1]{false};
    potrzebneWierzcholki[0] = true;
    potrzebneWierzcholki[koniec] = true;

    int iloscPotrzebnychWierzcholkow = 2;
    vector<Skrot> listaSkrotow;

    for (int i = 0; i < liczbaSkrotow; i++)
    {
        cin >> x >> y >> w;
        if (y > koniec) //wykluczamy przypadek kiedy skrot jest za koncem trasy
            continue;

        Skrot nowy;
        nowy.skadProwadzi = x;
        nowy.gdzieProwadzi = y;
        nowy.waga = w;
        listaSkrotow.push_back(nowy);
        if (!potrzebneWierzcholki[x])
        {
            potrzebneWierzcholki[x] = true;
            iloscPotrzebnychWierzcholkow++;
        }
        if (!potrzebneWierzcholki[y])
        {
            potrzebneWierzcholki[y] = true;
            iloscPotrzebnychWierzcholkow++;
        }
    }

    n = iloscPotrzebnychWierzcholkow;
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

    int poprzedniWierzcholek = 0;
    for (int i = 0; i < n - 1; i++)
    {
        int wartoscBezMerge = zwracaKolejnyPotrzebny(poprzedniWierzcholek + 1, potrzebneWierzcholki, koniec);
        Wierzcholek NowyWierzcholek;
        NowyWierzcholek.wartoscBezMerge = wartoscBezMerge;
        NowyWierzcholek.gdzieProwadzi = i + 1;
        NowyWierzcholek.waga = wartoscBezMerge - poprzedniWierzcholek;
        poprzedniWierzcholek = wartoscBezMerge;

        listaSasiedztwa[i].push_back(NowyWierzcholek);
    }

    for (i = 0; i < listaSkrotow.size(); i++)
    {
        x = znajdzPozycjePoMerge(listaSkrotow[i].skadProwadzi, listaSasiedztwa);
        y = znajdzPozycjePoMerge(listaSkrotow[i].gdzieProwadzi, listaSasiedztwa);
        w = listaSkrotow[i].waga;

        Wierzcholek NowyWierzcholek;
        NowyWierzcholek.gdzieProwadzi = y;
        NowyWierzcholek.waga = w;

        listaSasiedztwa[x].push_back(NowyWierzcholek);
    }
    tablicaKosztowD[start] = 0;

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

    cout << tablicaKosztowD[n - 1] << endl;

    return 0;
}
