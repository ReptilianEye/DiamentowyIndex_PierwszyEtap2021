#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <algorithm>
#include <chrono>

using namespace std;

// vector<long long> LKwadratow;
vector<string> wyniki;
string minimalnySpisOperacji = "";
int najmniejszaIloscOperacji = INT32_MAX;
bool *visited = new bool[2000001]{false};
string *ZnaneOdpowiedzi = new string[451]{""};

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

string zwracaSpisOperacjiWBok(long long liczbaPoczatkowa, long long liczbaDocelowa)
{
    string spisOperacji = "";
    char rodzajOperacji;
    if (liczbaPoczatkowa > liczbaDocelowa)
        rodzajOperacji = 'i';
    else
        rodzajOperacji = 'd';

    int ileOperacji = abs(liczbaPoczatkowa - liczbaDocelowa);

    for (int i = 0; i < ileOperacji; i++)
        spisOperacji = rodzajOperacji + spisOperacji;

    return spisOperacji;
}

void ZerujeLiczbeBezSortowania(long long liczba, int iloscOperacji, string spisOperacji)
{
    if (iloscOperacji >= najmniejszaIloscOperacji)
        return;
    long long oryginalnaLiczba = liczba;
    if (liczba == 0)
    {
        // cout << spisOperacji << endl;
        wyniki.push_back(spisOperacji);
        // if (spisOperacji.length() != iloscOperacji)
        // throw invalid_argument("Zla ilosc operacji");
        if (najmniejszaIloscOperacji > iloscOperacji)
        {
            najmniejszaIloscOperacji = iloscOperacji;
            // minimalnySpisOperacji = spisOperacji;
        }
        return;
    }
    if (liczba == 1 || liczba == 2 || liczba == 3)
    {
        string spisOperacjiNaTymPoziomie = zwracaSpisOperacjiWBok(liczba, 0);
        return ZerujeLiczbeBezSortowania(0, iloscOperacji + liczba, spisOperacjiNaTymPoziomie + spisOperacji);
    }

    //zejscie do najblizszego pierwiastka
    int najblizszyKwadrat = pow(round(sqrt(liczba)), 2);
    int odlegloscDoNajblizszego = abs(liczba - najblizszyKwadrat);

    string operacjeDoPierwiastka = zwracaSpisOperacjiWBok(liczba, najblizszyKwadrat);
    iloscOperacji += abs(liczba - najblizszyKwadrat);

    long long liczbaDoOdwiedzeniaPrzezPierwiastek = sqrt(najblizszyKwadrat);
    spisOperacji = operacjeDoPierwiastka + spisOperacji;
    // spisOperacji = " " + to_string(liczba) + 's' + spisOperacji;
    spisOperacji = 's' + spisOperacji;
    iloscOperacji++;
    ZerujeLiczbeBezSortowania(liczbaDoOdwiedzeniaPrzezPierwiastek, iloscOperacji, spisOperacji);
    // visited[oryginalnaLiczba] = false;
    //----
}

void ZerujeLiczbeZSortowaniem(long long liczba, int iloscOperacji, string spisOperacji)
{

    if (iloscOperacji >= najmniejszaIloscOperacji)
        return;
    visited[liczba] = true;
    long long oryginalnaLiczba = liczba;
    if (liczba == 0)
    {
        // cout << spisOperacji << endl;
        wyniki.push_back(spisOperacji);
        // if (spisOperacji.length() != iloscOperacji)
        // throw invalid_argument("Zla ilosc operacji");
        if (najmniejszaIloscOperacji > iloscOperacji)
        {
            najmniejszaIloscOperacji = iloscOperacji;
            // minimalnySpisOperacji = spisOperacji;
        }
        return;
    }
    if (liczba < 450)
        if (ZnaneOdpowiedzi[liczba] != "")
        {
            string znanaOdpowiedz = ZnaneOdpowiedzi[liczba];
            return ZerujeLiczbeZSortowaniem(0, iloscOperacji + znanaOdpowiedz.length(), znanaOdpowiedz + spisOperacji);
        }
    if (liczba == 1 || liczba == 2 || liczba == 3)
    {
        string spisOperacjiNaTymPoziomie = zwracaSpisOperacjiWBok(liczba, 0);
        return ZerujeLiczbeZSortowaniem(0, iloscOperacji + liczba, spisOperacjiNaTymPoziomie + spisOperacji);
    }

    int najblizszyKwadrat = pow(round(sqrt(liczba)), 2);
    int odlegloscDoNajblizszego = abs(liczba - najblizszyKwadrat);
    for (int i = 0; i <= odlegloscDoNajblizszego; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            int liczbaRobocza;
            if (j % 2 == 0)
                liczbaRobocza = liczba - i;
            else
                liczbaRobocza = liczba + i;
            if (sprawdzaCzyLiczbaJestPosortowana(liczbaRobocza))
            {

                string stringDoPermutowania = to_string(liczbaRobocza);
                string spisOperacjiNaTymPoziomie = zwracaSpisOperacjiWBok(liczba, liczbaRobocza);
                sort(stringDoPermutowania.begin(), stringDoPermutowania.end());
                do
                {
                    int liczbaDoOdwiedzenia = stoll(stringDoPermutowania);
                    if (liczbaDoOdwiedzenia != liczbaRobocza)
                        if (!visited[liczbaDoOdwiedzenia])
                            if (stringDoPermutowania[0] != '0')
                            {
                                cout << liczbaRobocza << " " << stringDoPermutowania << " " << spisOperacji << endl;
                                ZerujeLiczbeZSortowaniem(liczbaDoOdwiedzenia, iloscOperacji + 1 + spisOperacjiNaTymPoziomie.length(), 'p' + spisOperacjiNaTymPoziomie + spisOperacji);

                                // ZerujeLiczbeZSortowaniem(liczbaDoOdwiedzenia, iloscOperacji + 1 + abs(liczba - liczbaRobocza), to_string(liczbaRobocza) + "->" + stringDoPermutowania + 'p' + spisOperacjiNaTymPoziomie + spisOperacji);
                                visited[liczbaDoOdwiedzenia] = false;
                            }
                } while (next_permutation(stringDoPermutowania.begin(), stringDoPermutowania.end()));
            }
        }
    }
    //zejscie do najblizszego pierwiastka
    string operacjeDoPierwiastka = zwracaSpisOperacjiWBok(liczba, najblizszyKwadrat);
    iloscOperacji += abs(liczba - najblizszyKwadrat);

    liczba = sqrt(najblizszyKwadrat);
    spisOperacji = operacjeDoPierwiastka + spisOperacji;
    // spisOperacji = " " + to_string(liczba) + 's' + spisOperacji;
    spisOperacji = 's' + spisOperacji;
    iloscOperacji++;
    ZerujeLiczbeZSortowaniem(liczba, iloscOperacji, spisOperacji);
    visited[oryginalnaLiczba] = false;
    //----
}
int main()
{
    //********** wczytywanie wejscia
    long long docelowaLiczba;
    // cin >> docelowaLiczba;

    for (int i = 1; i <= 450; i++)
    {
        // docelowaLiczba = 8796;
        docelowaLiczba = i;
        ZerujeLiczbeBezSortowania(docelowaLiczba, 0, "");
        ZerujeLiczbeZSortowaniem(docelowaLiczba, 0, "");
        // for (int j = 0; j < wyniki.size(); j++)
        // {
        // cout << docelowaLiczba << " " << wyniki[j] << endl;
        // }
        ZnaneOdpowiedzi[i] = wyniki[wyniki.size() - 1];
        najmniejszaIloscOperacji = INT32_MAX;
        wyniki.clear();
        for (int j = 0; j < 450; j++)
            visited[j] = false;
    }

    //do testow
    int limit = 10000;
    // for (int i = 7800; i <=limit; i++)
    // {
        // docelowaLiczba = i;
        docelowaLiczba = 7827;
        auto t1 = chrono::high_resolution_clock::now();
        ZerujeLiczbeBezSortowania(docelowaLiczba, 0, "");
        ZerujeLiczbeZSortowaniem(docelowaLiczba, 0, "");
        auto t2 = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(t2 - t1);
        // cout << docelowaLiczba << endl;
        if (duration.count() > 5000)
        cout << docelowaLiczba << " " << duration.count() << endl;
        // for (int j = 0; j < wyniki.size(); j++)
        // {
        //     cout << docelowaLiczba << " " << wyniki[j] << endl;
        // }
        najmniejszaIloscOperacji = INT32_MAX;
        wyniki.clear();
        for (int j = 0; j <= limit; j++)
            visited[j] = false;
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