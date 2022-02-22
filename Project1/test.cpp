#include <bits/stdc++.h>

using namespace std;

void print_list(list<int>& lst) {
    for(auto x : lst)
        cout << x << " ";
    cout << endl;
}

int main() {

    list<int> sample;
    for(int i = 1; i <= 10; i++)
        sample.push_back(i);

    print_list(sample);

    auto it = sample.begin();
    auto after_it = sample.begin();
    for(int i = 0; i < 9; i++) {
        it++;
        auto cpy_it = it;
        after_it = ++cpy_it;
    }

    sample.erase(it);

    print_list(sample);

    sample.insert(after_it, 10);

    print_list(sample);

    return 0;
}
