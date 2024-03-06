#include <iostream>
#include <string>

using namespace std;

class Vector
{
    string* arr;
    int cur_size;
    int capacity;
public:
    Vector()
    {
        cur_size = 0;
        capacity = 1;
        arr = new string[capacity];
    };

    int size() const
    {
        return cur_size;
    }

    int is_empty() const
    {
        return cur_size == 0;
    }

    void push(const string& data)
    {
        if (cur_size == capacity)
        {
            capacity *= 2;
            string* old_arr = arr;
            arr = new string[capacity];

            for (int i = 0; i < cur_size; i++)
                arr[i] = old_arr[i];


            delete[] old_arr;
        }
        arr[cur_size++] = data;
        return;
    }

    void pop()
    {
        if (is_empty())
            return;

        cur_size--;
    }

    void set(const string& data, int i) {
        arr[i] = data;
    }

    string operator [](const int i) const
    {
        return arr[i];
    }
};

void swap(Vector& arr, int l, int r) {
    string tmp = arr[l];
    arr.set(arr[r], l);
    arr.set(tmp, r);
}

bool comp(string l, string r) {
    for (int i = 6; i < 10; i++) {
        if (l.at(i) < r.at(i))
            return true;
        else if (l.at(i) == r.at(i))
            continue;
        else
            return false;
    }
    for (int i = 3; i < 5; i++) {
        if (l.at(i) < r.at(i))
            return true;
        else if (l.at(i) == r.at(i))
            continue;
        else
            return false;
    }
    for (int i = 0; i < 2; i++) {
        if (l.at(i) < r.at(i))
            return true;
        else if (l.at(i) == r.at(i))
            continue;
        else
            return false;
    }
    return false;
}

void heapify(Vector& arr, int i, bool alfabet) {
    int parent = (i - 1) / 2;
    if (alfabet == true) {
        if (arr[i].substr(11) < arr[parent].substr(11)) {
            swap(arr, i, parent);
            heapify(arr, parent, alfabet);
        }
    }
    else {
        if (comp(arr[i], arr[parent])) {
            swap(arr, i, parent);
            heapify(arr, parent, alfabet);
        }
    }
}

void heapifydel(Vector& arr, int i, bool alfabet) {
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int n = arr.size();

    if (alfabet == true) {
        if (l < n && arr[l].substr(11) < arr[smallest].substr(11))
            smallest = l;
        if (r < n && arr[r].substr(11) < arr[smallest].substr(11))
            smallest = r;
    }
    else {
        if (l < n && comp(arr[l], arr[smallest]))
            smallest = l;
        if (r < n && comp(arr[r], arr[smallest]))
            smallest = r;
    }

    if (smallest != i) {
        swap(arr, i, smallest);
        heapifydel(arr, smallest, alfabet);
    }
}

void buildHeap(Vector& arr, bool alfabet) {
    for (int i = (arr.size() / 2) - 1; i >= 0; i--) {
        heapifydel(arr, i, alfabet);
    }
}

void deleteRoot(Vector& arr, bool alfabet) {
    cout << arr[0] << endl;
    arr.set(arr[arr.size() - 1], 0);
    arr.pop();
    heapifydel(arr, 0, alfabet);
}

void printArray(Vector& arr) {
    int n = arr.size();
    for (int i = 0; i < n; ++i)
        cout << arr[i] << endl;
}

int main()
{
    Vector arr;
    string name, data, key;
    char input;
    int kol = 0;
    bool alfabet = true;
    while (true)
    {
        cin >> input;
        if (input == 'q')
            break;
        if (input == '+') {
            cin >> kol;
            for (int i = 0; i < kol; i++)
            {
                cin >> data >> name;
                key = data + " " + name;
                arr.push(key);
                if (alfabet == true)
                    heapify(arr, arr.size() - 1, alfabet);
                if (alfabet == false)
                    heapify(arr, arr.size() - 1, alfabet);
            }
        }
        if (input == '-') {
            cin >> kol;
            for (int i = 0; i < kol; i++)
                deleteRoot(arr, alfabet);
        }
        if (input == 'r') {
            if (alfabet == true) {
                buildHeap(arr, false);
                alfabet = false;
                continue;
            }
            if (alfabet == false) {
                buildHeap(arr, true);
                alfabet = true;
            }
        }
        if (input == 'p')
            printArray(arr);
    }
    return 0;
}