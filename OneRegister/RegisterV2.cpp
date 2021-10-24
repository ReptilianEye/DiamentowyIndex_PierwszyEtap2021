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
bool czyKwadrat(long long liczba)
{
    auto kwadrat = sqrt(liczba);
    if (kwadrat * kwadrat == liczba)
        return true;
    return false;
}
void ZerujeLiczbeZSortowaniem(long long liczba, int iloscOperacji, string spisOperacji)
{
    if (liczba == 0)
    {
        // cout << spisOperacji << endl;
        if (spisOperacji.length() < pow(10, 2))
            wyniki.push_back(spisOperacji);
        if (najmniejszaIloscOperacji > iloscOperacji)
        {
            najmniejszaIloscOperacji = iloscOperacji;
            minimalnySpisOperacji = spisOperacji;
        }
        return;
    }
    if (liczba == 1 || liczba == 2 || liczba == 3)
    {
        zapiszOperacje(liczba, 0, iloscOperacji, spisOperacji);
        return ZerujeLiczbeZSortowaniem(liczba, iloscOperacji, spisOperacji);
    }
    int gornyKwadrat = pow(ceil(sqrt(liczba)), 2);
    for (long long roboczaLiczba = liczba; roboczaLiczba <= gornyKwadrat;roboczaLiczba++)
    {
        if (sprawdzaCzyLiczbaJestPosortowana(roboczaLiczba))
        {
            cout << roboczaLiczba << " ";

            string liczbaDoPermutacji = to_string(roboczaLiczba);
            while (prev_permutation(liczbaDoPermutacji.begin(), liczbaDoPermutacji.end()))
            {
                if (liczbaDoPermutacji[0] != '0')
                    ZerujeLiczbeZSortowaniem(stoll(liczbaDoPermutacji), iloscOperacji + 1, 'p' + spisOperacji);
            }
        }
        if (czyKwadrat(roboczaLiczba))
        {
            long long pierw = sqrt(roboczaLiczba);
            // spisOperacji = " " + to_string(liczba) + 's' + spisOperacji;

            ZerujeLiczbeZSortowaniem(pierw, iloscOperacji + 1, 's' + spisOperacji);
        }
        spisOperacji = 'd' + spisOperacji;
        iloscOperacji++;
        if(spisOperacji.length() > 100)
            return;
    }
    int dolnyKwadrat = pow(floor(sqrt(liczba)), 2);
    for (long long roboczaLiczba = liczba; roboczaLiczba >= dolnyKwadrat; roboczaLiczba--)
    {
        if (sprawdzaCzyLiczbaJestPosortowana(roboczaLiczba))
        {
            cout << roboczaLiczba << " ";
            string liczbaDoPermutacji = to_string(roboczaLiczba);
            while (prev_permutation(liczbaDoPermutacji.begin(), liczbaDoPermutacji.end()))
            {
                if (liczbaDoPermutacji[0] != '0')
                    ZerujeLiczbeZSortowaniem(stoll(liczbaDoPermutacji), iloscOperacji + 1, 'p' + spisOperacji);
            }
        }
        if (czyKwadrat(roboczaLiczba))
        {
            long long pierw = sqrt(roboczaLiczba);
            // spisOperacji = " " + to_string(liczba) + 's' + spisOperacji;

            ZerujeLiczbeZSortowaniem(pierw, iloscOperacji + 1, 's' + spisOperacji);
        }
        spisOperacji = 'i' + spisOperacji;
        iloscOperacji++;
        if(spisOperacji.length() > 100)
            return;
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