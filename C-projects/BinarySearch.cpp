#include <iostream>
using namespace std;


int search(int* arr, int l, int n, int k) {
    int  midle, r = n - 1;
    while ((l < r) && (r - l != 1)) {
        midle = (l + r) / 2;
        if (k > arr[midle]) {
            if (arr[l] > arr[l + 1])
                r = midle;
            else
                l = midle;
        }
        else if (k < arr[midle]) {
            if (arr[l] > arr[l + 1])
                l = midle;
            else
                r = midle;
        }
        else
            return midle;
    }
    if (((k >= arr[r]) && (k <= arr[l])) || ((k >= arr[l]) && (k <= arr[r]))) {
        if (r - l == 1) {
            if (l == 0)
                return l;
            else if (r == n - 1)
                return r;
        }
    }
    return -1;
}

int main() {
    int m, n, p, k;
    cin >> m;
    for (int u = 0; u < m; u++) {
        cin >> n;
        int* arr = new int[n];
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        cin >> p;
        for (int o = 0; o < p; o++) {
            cin >> k;
            cout << search(arr, 0, n, k) << endl;
        }
        delete[]arr;
    }
}