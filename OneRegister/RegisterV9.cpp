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
string *ZnaneOdpowiedzi = new string[200000]{string("", INT32_MAX)};

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

void ZerujeLiczbeBezSortowania(long long liczba, int iloscOperacji, string spisOperacji, long long oryginalnaLiczba)
{
    if (iloscOperacji >= najmniejszaIloscOperacji)
        return;
    if (liczba == 0)
    {
        if (spisOperacji.length() < ZnaneOdpowiedzi[oryginalnaLiczba].length())
        {
            ZnaneOdpowiedzi[oryginalnaLiczba] = spisOperacji;
        }
        return;
    }
    if (liczba == 1 || liczba == 2 || liczba == 3)
    {
        string spisOperacjiNaTymPoziomie = zwracaSpisOperacjiWBok(liczba, 0);
        return ZerujeLiczbeBezSortowania(0, iloscOperacji + liczba, spisOperacjiNaTymPoziomie + spisOperacji, oryginalnaLiczba);
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
    ZerujeLiczbeBezSortowania(liczbaDoOdwiedzeniaPrzezPierwiastek, iloscOperacji, spisOperacji,oryginalnaLiczba);
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

                string liczbaDoPermutacji = to_string(liczbaRobocza);
                string spisOperacjiNaTymPoziomie = zwracaSpisOperacjiWBok(liczba, liczbaRobocza);
                while (prev_permutation(liczbaDoPermutacji.begin(), liczbaDoPermutacji.end()))
                {
                    int liczbaDoOdwiedzenia = stoll(liczbaDoPermutacji);
                    if (!visited[liczbaDoOdwiedzenia])
                        if (liczbaDoPermutacji[0] != '0')
                        {
                            ZerujeLiczbeZSortowaniem(stoll(liczbaDoPermutacji), iloscOperacji + 1 + spisOperacjiNaTymPoziomie.length(), 'p' + spisOperacjiNaTymPoziomie + spisOperacji);

                            // ZerujeLiczbeZSortowaniem(liczbaDoOdwiedzenia, iloscOperacji + 1 + abs(liczba - liczbaRobocza), to_string(liczbaRobocza) + "->" + liczbaDoPermutacji + 'p' + spisOperacjiNaTymPoziomie + spisOperacji);
                            visited[liczbaDoOdwiedzenia] = false;
                        }
                }
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
    long przewidywanyWynik;
    cin >> docelowaLiczba;
    // while (!cin.eof())
    // {
    // cin >> docelowaLiczba >> przewidywanyWynik;
    // for (int i = 7800; i <= 8000; i++)
    // {
    // docelowaLiczba = i;
    // docelowaLiczba = 8796;
    // auto t1 = chrono::high_resolution_clock::now();
    int pierwiastekDocelowej = ceil(sqrt(docelowaLiczba));
    int kolejnyKwadrat;
    for (int i = 1; i <= pierwiastekDocelowej; i++)
    {
        kolejnyKwadrat = pow(i, 2);
        if (!sprawdzaCzyLiczbaJestPosortowana(kolejnyKwadrat))
            ZerujeLiczbeBezSortowania(pow(i, 2), 0, "");
    }
    ZerujeLiczbeZSortowaniem(docelowaLiczba, 0, "");
    // auto t2 = chrono::high_resolution_clock::now();
    // auto duration = chrono::duration_cast<chrono::milliseconds>(t2 - t1);
    // if (duration.count() > 5000)
    // cout << i << " " << duration.count() << endl;
    // for (int j = 0; j < wyniki.size(); j++)

    // {
    // if (wyniki[wyniki.size() - 1].length() != przewidywanyWynik)
    // cout << "blad dla " << docelowaLiczba << " " << wyniki[wyniki.size() - 1].length() << endl;
    cout << wyniki[wyniki.size() - 1].length() << endl;
    // wyniki.clear();
    // najmniejszaIloscOperacji = INT32_MAX;
    // }

    // cout << docelowaLiczba << " " << wyniki[j] << endl;
    // cout << docelowaLiczba << " " << wyniki[wyniki.size() - 1].length() << endl;

    // }
    // najmniejszaIloscOperacji = INT32_MAX;
    // }
    // cout << wyniki.size() << endl;
    // wyniki.clear();

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