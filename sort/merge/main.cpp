#include <iostream>
#include <vector>

using namespace std;

template<typename T>
void merge_sort(vector<T>& vec, long long first, long long last) {
    //O(n log n)
    if (first != last) { // Если в массиве больше 1 элемента, то их нужно отсортировать
        long long middle = (first + last) / 2;
        merge_sort(vec, first, middle);
        merge_sort(vec, middle + 1, last);

        long long left_i = first;
        long long right_i = middle + 1;

        vector<T> sorted = {}; // Отсортированный массив
        while ((left_i != middle + 1) && (right_i != last + 1)) { // Обрабатываем оба подмассива, пока какой-то из них не станет пустым
            if (vec[left_i] < vec[right_i]) {
                sorted.push_back(vec[left_i]);
                left_i++;
            }
            else {
                sorted.push_back(vec[right_i]);
                right_i++;
            }
        }
        if (left_i != middle + 1) { // Если левый не пуст, то записываем его
            for (long long i = left_i; i < middle + 1; i++) {
                sorted.push_back(vec[i]);
            }
        }
        else if (right_i != last + 1) { // Если правый не пуст, то записываем его
            for (long long i = right_i; i < last + 1; i++) {
                sorted.push_back(vec[i]);
            }
        }
        for (long long i = first; i < last + 1; i++) {
            vec[i] = sorted[i - first];
        }
    }
}

int main() {
    vector<int> a = {5, 4, 2, -8, 12, 4, 3, 981, 75, 9, -15};
    cout << "merge sort\nbefore: ";
    for (auto &it : a) {
        cout << it << ' ';
    }
    merge_sort(a, 0, a.size() - 1);
    cout << "\n after: ";
    for (auto &it : a) {
        cout << it << ' ';
    }
    cin.get();
    return 0;
}