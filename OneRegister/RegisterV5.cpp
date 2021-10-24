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
int najmniejszaIloscOperacji = INT32_MAX;
bool *visited = new bool[2000001]{false};

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
void ZerujeLiczbeZSortowaniem(long long liczba, int iloscOperacji, string spisOperacji)
{
    visited[liczba] = true;
    if (liczba == 0)
    {
        // cout << spisOperacji << endl;
        wyniki.push_back(spisOperacji);
        // if (najmniejszaIloscOperacji > iloscOperacji)
        // {
        //     najmniejszaIloscOperacji = iloscOperacji;
        //     minimalnySpisOperacji = spisOperacji;
        // }
        return;
    }
    if (liczba == 1 || liczba == 2 || liczba == 3)
    {
        string spisOperacjiNaTymPoziomie = zwracaSpisOperacjiWBok(liczba, 0);
        return ZerujeLiczbeZSortowaniem(0, iloscOperacji + spisOperacjiNaTymPoziomie.length(), spisOperacjiNaTymPoziomie + spisOperacji);
    }

    int najblizszyKwadrat = pow(round(sqrt(liczba)), 2);
    int odlegloscDoNajblizszego = abs(liczba - najblizszyKwadrat);
    for (int i = liczba - odlegloscDoNajblizszego; i <= liczba + odlegloscDoNajblizszego; i++)
    {
        int liczbaRobocza = i;
        if (sprawdzaCzyLiczbaJestPosortowana(liczbaRobocza))
        {

            string liczbaDoPermutacji = to_string(liczbaRobocza);
            string spisOperacjiNaTymPoziomie = zwracaSpisOperacjiWBok(liczba, liczbaRobocza);
            while (prev_permutation(liczbaDoPermutacji.begin(), liczbaDoPermutacji.end()))
            {
                int liczbaDoOdwiedzenia = stoi(liczbaDoPermutacji);
                if (!visited[liczbaDoOdwiedzenia])
                    if (liczbaDoPermutacji[0] != '0')
                    {
                        ZerujeLiczbeZSortowaniem(stoll(liczbaDoPermutacji), iloscOperacji + 1 + spisOperacjiNaTymPoziomie.length(), 'p' + spisOperacjiNaTymPoziomie + spisOperacji);

                        // ZerujeLiczbeZSortowaniem(stoll(liczbaDoPermutacji), iloscOperacji + 1 + spisOperacjiNaTymPoziomie.length(), to_string(liczbaRobocza) + "->" + liczbaDoPermutacji + 'p' + spisOperacjiNaTymPoziomie + spisOperacji);
                    }
            }
        }
    }
    //zejscie do najblizszego pierwiastka

    string operacjeDoPierwiastka = zwracaSpisOperacjiWBok(liczba, najblizszyKwadrat);
    liczba = sqrt(najblizszyKwadrat);
    spisOperacji = operacjeDoPierwiastka + spisOperacji;
    iloscOperacji + operacjeDoPierwiastka.length();
    // spisOperacji = " " + to_string(liczba) + 's' + spisOperacji;
    spisOperacji = 's' + spisOperacji;
    iloscOperacji++;
    ZerujeLiczbeZSortowaniem(liczba, iloscOperacji, spisOperacji);
    //----
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