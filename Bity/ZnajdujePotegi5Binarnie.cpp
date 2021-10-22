#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>

using namespace std;

const int iloscPoteg5Do50Dlugosci = 22;
string *tablicaPoteg5Binarnie = new string[iloscPoteg5Do50Dlugosci];
bool CzyZnalezlismy = false;

string toBinary(long long liczba)
{
    string binarna = "";
    while (liczba != 0)
    {
        binarna = to_string(liczba % 2) + binarna;
        liczba = liczba / 2;
    }
    return binarna;
}

bool sprawdzaCzyPodstringJestPotega5(string binarna)
{
    for (int i = 0; tablicaPoteg5Binarnie[i].length() <= binarna.length(); i++)
    {
        if (tablicaPoteg5Binarnie[i].length() == binarna.length())
            if (tablicaPoteg5Binarnie[i] == binarna)
                return true;
            else
                return false;
    }
}
void ZnajdujeIlePoteg5JestWLiczbieBinarniej(string binarna, int numberWycinka)
{
    if (binarna.length() == 0)
    {
        cout << numberWycinka << endl;
        CzyZnalezlismy = true;
        return;
    }
    for (int i = binarna.length(); i > 0; i--)
    {
        if (CzyZnalezlismy)
            return;
        string wycinekBinarnej = binarna.substr(0, i);
        if (sprawdzaCzyPodstringJestPotega5(wycinekBinarnej))
        {
            ZnajdujeIlePoteg5JestWLiczbieBinarniej(binarna.substr(i), numberWycinka + 1);
        }
    }
}
int main()
{
    //********** wczytywanie wejscia

    string binarna;
    cin >> binarna;
    for (int i = 0; i < 22; i++)
    {
        string potega5Binarnie = toBinary(pow(5, i));
        tablicaPoteg5Binarnie[i] = potega5Binarnie;
        // cout << potega5Binarnie << " " << potega5Binarnie.length() << endl;
    }

    ZnajdujeIlePoteg5JestWLiczbieBinarniej(binarna, 0);
    if (!CzyZnalezlismy)
        cout << -1 << endl;
    return 0;
}
