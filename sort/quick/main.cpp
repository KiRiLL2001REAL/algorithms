#include <iostream>
#include <vector>

using namespace std;

template<typename T>
void quick_sort(vector<T>& vec, long long first, long long last) {
    //O(n log n)
    if (first != last) { // Если элементов больше 1, то массив нужно отсортировать
        long long mid = first + (last - first) / 2;
        T pivot = vec[mid];
        long long left = first;
        long long right = last;
        while (left <= right) {
            while (vec[left] < pivot)  left++;
            while (pivot < vec[right]) right--;
            if (left <= right) {
                swap(vec[left], vec[right]);
                left++;
                right--;
            }
        }
        if (first < right) quick_sort(vec, first, right);
        if (left < last) quick_sort(vec, left, last);
    }
}

int main() {
    vector<int> a = {5, 4, 2, -8, 12, 4, 3, 981, 75, 9, -15};
    cout << "quick sort\nbefore: ";
    for (auto &it : a) {
        cout << it << ' ';
    }
    quick_sort(a, 0, a.size() - 1);
    cout << "\n after: ";
    for (auto &it : a) {
        cout << it << ' ';
    }
    cin.get();
    return 0;
}