#include <iostream>
#include <vector>

using namespace std;

template<typename T>
void selection_sort(vector<T>& vec) {
    //O(n^2)
    size_t size = vec.size();
    for (size_t i = 0; i < size; i++) {
        size_t index = i;
        T min = vec[index];
        for (size_t j = i + 1; j < size; j++) {
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