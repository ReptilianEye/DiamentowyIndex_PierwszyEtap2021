#include <iostream>
#include <string>
#include <cstdlib>
#include <math.h>

using namespace std;

int main()
{
    //********** wczytywanie wejscia
    int temp;
    cin >> temp;
    int limit = 200000;
    long long aktualnyKwadrat = 0;
    int start = 1;
    while (aktualnyKwadrat < limit)
    {
        aktualnyKwadrat = pow(start,2);
        cout << start << "  " << aktualnyKwadrat << endl;
        start += 1;
    }


    return 0;
}