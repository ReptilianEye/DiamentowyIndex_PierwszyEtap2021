#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>

using namespace std;

int main()
{
    srand((unsigned)time(NULL));
    int n = 1000;
    int iloscSkrotow = 12;
    int maxPrzedzial = n - 500;
    cout << n << " " << iloscSkrotow << endl;
    for (int i = 0; i < iloscSkrotow; i++)
    {
        int poczatkowyWierzcholek = rand() % maxPrzedzial;
        cout << poczatkowyWierzcholek << " " << poczatkowyWierzcholek + rand() % maxPrzedzial << " " << rand() % 50 << endl;
    }
    return 0;
}