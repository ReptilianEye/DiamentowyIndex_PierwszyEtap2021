#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void printIP(string IP)
{
    for (int i = 0; i < IP.length(); i++)
        cout << IP[i];
    cout << endl;
}

int liczbaZnalezionychIP = 0;
void wypisujeIP(int *TIP, int i, int iloscKropek, string IP, int n)
{
    string liczbaPoKropce = "";
    if (iloscKropek == 0)
    {
        for (i; i < n; i++)
        {
            IP = IP + to_string(TIP[i]);
            liczbaPoKropce = liczbaPoKropce + to_string(TIP[i]);
            if (stoi(liczbaPoKropce) > 255)
                return;
            if (liczbaPoKropce.length() > 3)
                return;
            if (liczbaPoKropce.length() > 2 && liczbaPoKropce[0] == '0')
                return;
        }
        if (IP[IP.length() - 1] == '.')
            return;
        liczbaZnalezionychIP++;
        printIP(IP);
    }
    else
    {
        if (TIP[i] == 0)
            wypisujeIP(TIP, i + 1, iloscKropek - 1, IP + to_string(TIP[i]) + ".", n);
        else
        {
            int iloscOdKropki = 0;
            string fragmentIP = "";

            for (i; i < n; i++)
            {

                iloscOdKropki++;
                if (iloscOdKropki > 3)
                    return;

                fragmentIP = fragmentIP + to_string(TIP[i]);
                if (stoi(fragmentIP) > 255)
                    return;
                wypisujeIP(TIP, i + 1, iloscKropek - 1, IP + fragmentIP + ".", n);
            }
        }
    }
}
int main()
{
    //********** wczytywanie wejscia
    string s;
    cin >> s;
    int n = s.length();
    if (s[0] == '0' || n < 4 || n > 16) //TODO do sprawdzenia czy drugi warunek jest prawdziwy
    {
        cout << "NO";
        return 0;
    }

    int *TIP = new int[n];
    for (int i = 0; i < n; i++)
    {
        TIP[i] = s[i] - '0';
    }
    wypisujeIP(TIP, 0, 3, "", n);
    
    if (liczbaZnalezionychIP == 0)
        cout << "NO" << endl;

    return 0;
}