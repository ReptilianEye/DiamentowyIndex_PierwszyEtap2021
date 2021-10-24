#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

//Driver method to test map class
int main()
{
    unordered_map<int, vector<int>> h;

    h.insert({1, vector<int>{1, 2, 3}});
    h.insert({2, vector<int>{4, 5, 6}});
    auto b = h[2];
    for (auto el : b)
        cout << el << " ";

    auto search = h.find(4);
    if (search == h.end())
        std::cout << "Not found\n";

    return 0;
}