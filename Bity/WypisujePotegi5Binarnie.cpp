#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>

using namespace std;

const int iloscPoteg5Do50Dlugosci = 22;
string *tablicaPoteg5Binarnie = new string[iloscPoteg5Do50Dlugosci];
int wynik = -1;

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
void ZnajdujeIlePoteg5JestWLiczbieBinarniej(string binarna, int start,int numberWycinka)
{
    if (start >= binarna.length())
    {
        cout << numberWycinka << endl;
        return;
    }
    string roboczaBinarna = binarna.substr(start);
    for (int i = 3; i <= binarna.length(); i++)
    {
        string wycinekBinarnej = roboczaBinarna.substr(0, i);
        if (sprawdzaCzyPodstringJestPotega5(wycinekBinarnej))
        {

            return ZnajdujeIlePoteg5JestWLiczbieBinarniej(binarna, start + i,numberWycinka+1);
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

    ZnajdujeIlePoteg5JestWLiczbieBinarniej(binarna, 0, 0);

    return 0;
}