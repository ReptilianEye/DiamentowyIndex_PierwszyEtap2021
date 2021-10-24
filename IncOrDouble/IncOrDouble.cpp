#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void DzieliLiczbyNa2(int *Liczby, int n)
{
    for (int i = 0; i < n; i++)
    {
        Liczby[i] = Liczby[i] / 2;
    }
}
int ZmniejszaLiczbyNaParzyste(int *Liczby, int n)
{
    int iloscZmniejszonych = 0;
    for (int i = 0; i < n; i++)
    {
        if (Liczby[i] % 2 == 1)
        {
            Liczby[i] = Liczby[i] - 1;
            iloscZmniejszonych++;
        }
    }
    return iloscZmniejszonych;
}
bool SprawdzCzyWszystkieToZero(int *Liczby, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (Liczby[i] != 0)
            return false;
    }
    return true;
}
int main()
{
    //********** wczytywanie wejscia
    int n;
    cin >> n;
    int *Liczby = new int[n];
    for (int i = 0; i < n; i++)
    {
        int liczba;
        cin >> liczba;
        Liczby[i] = liczba;
    }
    int iloscOperacji = 0;
    while (!SprawdzCzyWszystkieToZero(Liczby, n))
    {
        int iloscZmniejszonychO1 = ZmniejszaLiczbyNaParzyste(Liczby, n);
        if (iloscZmniejszonychO1 == 0)
        {
            DzieliLiczbyNa2(Liczby, n);
            iloscOperacji++;
        }
        iloscOperacji = iloscOperacji + iloscZmniejszonychO1;
    }
    cout << iloscOperacji << endl;

    return 0;
}