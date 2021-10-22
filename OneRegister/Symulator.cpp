#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

long long posortujLiczbe(long long liczba)
{
    string liczbaDoPosortowania = to_string(liczba);
    sort(liczbaDoPosortowania.begin(), liczbaDoPosortowania.end(), greater<int>());
    return stoll(liczbaDoPosortowania);
}

int main()
{
    //********** wczytywanie wejscia
    string spisInstrukcji;
    cin >> spisInstrukcji;

    long long wynik = 0;
    for (int i = 0; i < spisInstrukcji.length(); i++)
    {
        char instrukcja = spisInstrukcji[i];
        if (instrukcja == 'i')
            wynik++;
        else if (instrukcja == 'd')
            wynik--;
        else if (instrukcja == 's')
            wynik = pow(wynik, 2);
        else if (instrukcja == 'p')
            wynik = posortujLiczbe(wynik);
    }
    cout << wynik << endl;
    return 0;
}
