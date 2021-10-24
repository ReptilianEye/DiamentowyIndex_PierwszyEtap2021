#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<string> wyniki;
string minimalnySpisOperacji = "";
int najmniejszaIloscOperacji = INT32_MAX;

unordered_map<int, vector<int>> hashTKwadratow;

void przygotowujeTabliceKwadratow()
{
    int kwadrat;
    for (int i = 0; i < 448; i++)
    {
        kwadrat = pow(i, 2);
        string doPosortowania = to_string(kwadrat);
        sort(doPosortowania.begin(), doPosortowania.end(), greater<int>());
        int klucz = stoi(doPosortowania);
        auto search = hashTKwadratow.find(klucz);
        if (search == hashTKwadratow.end())
            hashTKwadratow.insert({klucz, vector<int>{i}});
        else
        {
            vector<int> listaDotychczas = hashTKwadratow[klucz];
            listaDotychczas.push_back(i);
            hashTKwadratow[klucz] = listaDotychczas;
        }
    }
}
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

void zapiszOperacje(long long liczbaPoczatkowa, long long liczbaDocelowa, int &iloscOperacji, string &spisOperacji)
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
bool czyKwadrat(long long liczba)
{
    double pierw = sqrt(liczba);
    int pierwCalkowite = round(pierw);
    if (pierwCalkowite == pierw)
        return true;
    return false;
}
void ZerujeLiczbeZSortowaniem(long long liczba, int iloscOperacji, string spisOperacji)
{
    if (spisOperacji.length() > 100)
        return;
    if (liczba == 0)
    {
        // cout << spisOperacji << endl;
        if (spisOperacji.length() < pow(10, 2))
            wyniki.push_back(spisOperacji);
        // if (minimalnaIloscOperacji > iloscOperacji)
        // {
        //     minimalnaIloscOperacji = iloscOperacji;
        //     minimalnySpisOperacji = spisOperacji;
        // }
        return;
    }
    if (liczba == 1 || liczba == 2 || liczba == 3)
    {
        zapiszOperacje(liczba, 0, iloscOperacji, spisOperacji);
        return ZerujeLiczbeZSortowaniem(liczba-liczba, iloscOperacji, spisOperacji);
    }
    int najblizszyKwadrat = pow(round(sqrt(liczba)), 2);
    int odlegloscDoNajblizszego = abs(liczba - najblizszyKwadrat);
    long long kopiaPierwotnej;
    int roboczaLiczba;
    int iloscOperacjiWGore = 0;
    int iloscOperacjiWDol = 0;
    string spisOperacjiNaTymPoziomie;
    for (int i = 0; i <= odlegloscDoNajblizszego; i++)
    {
        kopiaPierwotnej = liczba;
        for (int j = 0; j < 2; j++)
        {
            if (j % 2 == 0)
                roboczaLiczba = kopiaPierwotnej - i;
            else
                roboczaLiczba = kopiaPierwotnej + i;
            if (sprawdzaCzyLiczbaJestPosortowana(roboczaLiczba))
            {
                auto search = hashTKwadratow.find(roboczaLiczba);
                if (search != hashTKwadratow.end())
                {
                    spisOperacjiNaTymPoziomie = "";
                    for (auto docelowa : search->second)
                    {
                        zapiszOperacje(kopiaPierwotnej, roboczaLiczba, iloscOperacjiWDol, spisOperacjiNaTymPoziomie);
                        if (pow(docelowa, 2) != roboczaLiczba)
                            ZerujeLiczbeZSortowaniem(docelowa, iloscOperacji + 2 + i, "sp" + spisOperacjiNaTymPoziomie + spisOperacji);
                        else
                            ZerujeLiczbeZSortowaniem(docelowa, iloscOperacji + 1 + i, "s" + spisOperacjiNaTymPoziomie + spisOperacji);
                    }
                    continue;
                }
                else
                {
                    spisOperacjiNaTymPoziomie = "";
                    zapiszOperacje(kopiaPierwotnej, roboczaLiczba, iloscOperacjiWDol, spisOperacjiNaTymPoziomie);
                    string liczbaDoPermutacji = to_string(roboczaLiczba);
                    while (prev_permutation(liczbaDoPermutacji.begin(), liczbaDoPermutacji.end()))
                    {
                        if (liczbaDoPermutacji[0] != '0')
                        {

                            ZerujeLiczbeZSortowaniem(stoll(liczbaDoPermutacji), iloscOperacji + 1 + i, 'p' + spisOperacjiNaTymPoziomie + spisOperacji);
                        }
                    }
                }
            }
            if (czyKwadrat(roboczaLiczba))
            {
                spisOperacjiNaTymPoziomie = "";
                zapiszOperacje(kopiaPierwotnej, roboczaLiczba, iloscOperacjiWDol, spisOperacjiNaTymPoziomie);
                kopiaPierwotnej = sqrt(kopiaPierwotnej);
                ZerujeLiczbeZSortowaniem(kopiaPierwotnej, iloscOperacji + 1 + iloscOperacjiWDol, "s" + spisOperacjiNaTymPoziomie + spisOperacji);
            }
        }
    }
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
    przygotowujeTabliceKwadratow();
    ZerujeLiczbeZSortowaniem(docelowaLiczba, 0, "");
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