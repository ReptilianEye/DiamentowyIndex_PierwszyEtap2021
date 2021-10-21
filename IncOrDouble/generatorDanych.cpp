#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>

using namespace std;

int main()
{
    srand((unsigned)time(NULL));
    int n = 50;
    int maxPrzedzial = 1000;
    cout << n << endl;
    for (int i = 0; i < n; i++)
        cout <<  maxPrzedzial << " ";
    return 0;
}