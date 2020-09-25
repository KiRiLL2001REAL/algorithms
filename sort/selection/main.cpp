#include <iostream>
#include <vector>

using namespace std;

template<typename T>
void selection_sort(vector<T>& vec) {
    //O(n^2)
    long long size = vec.size();
    for (long long i = 0; i < size; i++) {
        long long index = i;
        T min = vec[index];
        for (long long j = i + 1; j < size; j++) {
            if (vec[j] < min) {
                min = vec[j];
                index = j;
            }
        }
        if (index != i) {
            T x = vec[i];
            vec[i] = vec[index];
            vec[index] = x;
        }
    }
}

int main() {
    vector<int> a = {5, 4, 2, -8, 12, 4, 3, 981, 75, 9, -15};
    cout << "selection sort\nbefore: ";
    for (auto &it : a) {
        cout << it << ' ';
    }
    selection_sort(a);
    cout << "\n after: ";
    for (auto &it : a) {
        cout << it << ' ';
    }
    cin.get();
    return 0;
}