#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;
// vector<long long> LKwadratow;
vector<string> wyniki;
string minimalnySpisOperacji = "";
int minimalnaIloscOperacji = INT32_MAX;

bool sprawdzaCzyLiczbaJestPosortowana(long long liczba)
{

    string sprawdzana = to_string(liczba);

    if (sprawdzana.length() == 1)
        return false;

    string pierwotna = sprawdzana;
    sort(sprawdzana.begin(), sprawdzana.end(), greater<int>());
    if (pierwotna == sprawdzana)
        return true;
    else
        return false;
}

void zapiszOperacje(long long &liczbaPoczatkowa, long long liczbaDocelowa, int &iloscOperacji, string &spisOperacji)
{
    char rodzajOperacji;
    if (liczbaPoczatkowa > liczbaDocelowa)
        rodzajOperacji = 'i';
    else
        rodzajOperacji = 'd';

    int ileOperacji = abs(liczbaPoczatkowa - liczbaDocelowa);
    iloscOperacji += ileOperacji;

    for (int i = 0; i < ileOperacji; i++)
        spisOperacji = rodzajOperacji + spisOperacji;

    liczbaPoczatkowa = liczbaDocelowa;
}
void ZerujeLiczbeBezSortowania(long long liczba, int iloscOperacji, string spisOperacji)
{
    if (liczba == 0)
    {
        // cout << spisOperacji << endl;
        wyniki.push_back(spisOperacji);
        if (minimalnaIloscOperacji > iloscOperacji)
        {
            minimalnaIloscOperacji = iloscOperacji;
            minimalnySpisOperacji = spisOperacji;
        }
        return;
    }
    if (liczba == 1 || liczba == 2 || liczba == 3)
    {
        zapiszOperacje(liczba, 0, iloscOperacji, spisOperacji);
        return ZerujeLiczbeBezSortowania(liczba, iloscOperacji, spisOperacji);
    }
   if (sprawdzaCzyLiczbaJestPosortowana(liczba))
    {
        string liczbaDoPermutacji = to_string(liczba);
        while (prev_permutation(liczbaDoPermutacji.begin(), liczbaDoPermutacji.end()))
        {
            if (liczbaDoPermutacji[0] != '0')
                ZerujeLiczbeBezSortowania(stoll(liczbaDoPermutacji), iloscOperacji + 1, 'p' + spisOperacji);
        }
    }
    int najblizszyPierw = round(sqrt(liczba));
    zapiszOperacje(liczba, pow(najblizszyPierw, 2), iloscOperacji, spisOperacji);

    spisOperacji = " " + to_string(liczba) + 's' + spisOperacji;
    liczba = sqrt(liczba);
    iloscOperacji++;

    ZerujeLiczbeBezSortowania(liczba, iloscOperacji, spisOperacji);
}

int main()
{
    //********** wczytywanie wejscia
    long long docelowaLiczba;
    // cin >> docelowaLiczba;

    // for (int i = 1; i <= 200000; i++)
    // {
    // docelowaLiczba = i;
    docelowaLiczba = 184914;
    ZerujeLiczbeBezSortowania(docelowaLiczba, 0, "");
    for (int i = 0; i < wyniki.size(); i++)
    {
        cout << docelowaLiczba << " " << wyniki[i] << endl;
    }
    wyniki.clear();
    // }
    // cout << wyniki.size() << endl;

    // cout << minimalnySpisOperacji << endl;

    // int i = 0;
    // long long kwadrat = pow(i, 2);
    // while (kwadrat < docelowaLiczba)
    // {
    //     LKwadratow.push_back(kwadrat);
    //     i++;
    //     kwadrat = pow(i, 2);
    // }

    return 0;
}