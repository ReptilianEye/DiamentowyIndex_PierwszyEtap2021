#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;
// vector<long long> LKwadratow;
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

void ZerujeLiczbeZSortowaniem(long long liczba, int iloscOperacji)
{
    visited[liczba] = true;
    long long oryginalnaLiczba = liczba;
    if (liczba == 0)
    {
        najmniejszaIloscOperacji = min(najmniejszaIloscOperacji, iloscOperacji);
        return;
    }
    if (liczba == 1 || liczba == 2 || liczba == 3)
        return ZerujeLiczbeZSortowaniem(0, iloscOperacji + liczba);

    int najblizszyKwadrat = pow(round(sqrt(liczba)), 2);
    int odlegloscDoNajblizszego = abs(liczba - najblizszyKwadrat);
    for (int i = liczba - odlegloscDoNajblizszego; i <= liczba + odlegloscDoNajblizszego; i++)
    {
        int liczbaRobocza = i;
        if (sprawdzaCzyLiczbaJestPosortowana(liczbaRobocza))
        {
            string liczbaDoPermutacji = to_string(liczbaRobocza);
            while (prev_permutation(liczbaDoPermutacji.begin(), liczbaDoPermutacji.end()))
            {
                int liczbaDoOdwiedzenia = stoll(liczbaDoPermutacji);
                if (!visited[liczbaDoOdwiedzenia])
                    if (liczbaDoPermutacji[0] != '0')
                    {
                        ZerujeLiczbeZSortowaniem(stoll(liczbaDoPermutacji), iloscOperacji + 1 + abs(liczba - liczbaRobocza));
                        visited[liczbaDoOdwiedzenia] = false;
                    }
            }
        }
    }
    //zejscie do najblizszego pierwiastka
    iloscOperacji += abs(liczba - najblizszyKwadrat);
    liczba = sqrt(najblizszyKwadrat);
    iloscOperacji++;
    ZerujeLiczbeZSortowaniem(liczba, iloscOperacji);
    visited[oryginalnaLiczba] = false;
    //----
}

int main()
{
    //********** wczytywanie wejscia
    long long docelowaLiczba;
    // cin >> docelowaLiczba;

    for (int i = 1; i <= 200000; i++)
    {
        docelowaLiczba = i;
        // docelowaLiczba = 184914;
        ZerujeLiczbeZSortowaniem(docelowaLiczba, 0);
        cout << i << " " << najmniejszaIloscOperacji << endl;
        najmniejszaIloscOperacji = INT32_MAX;
    }

    return 0;
}