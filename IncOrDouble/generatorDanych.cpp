#include <iostream>
#include <string>
#include <cstdlib>
#include <time.h>

using namespace std;

int main()
{
    srand((unsigned)time(NULL));
    int n = 10;
    int maxPrzedzial = 1000;
    for (int i = 0; i < n; i++)
        cout << rand() % maxPrzedzial << " ";
    return 0;
}