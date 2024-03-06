#include <iostream>
using namespace std;


class List
{
public:
    List();
    ~List();
    void push_back(int data);
    int Getsize() { return size; }
    int& operator[](const int index);

private:

    class Node {
    public:
        int data;
        Node* Pnext;
        Node(int data, Node* Pnext = nullptr) {
            this->data = data;
            this->Pnext = Pnext;
        }
    };
    Node* head;
    int size;
};


List::List()
{
    size = 0;
    head = nullptr;
}


List::~List()
{

}


void List::push_back(int data)
{
    if (head == nullptr) {
        head = new Node(data);
    }
    else {
        Node* current = this->head;
        while (current->Pnext != nullptr) {
            current = current->Pnext;
        }
        current->Pnext = new Node(data);
    }
    size++;
}

int& List::operator[](const int index) {
    int counter = 0;
    Node* current = this->head;
    while (current != nullptr) {
        if (counter == index) {
            return current->data;
        }
        current = current->Pnext;
        counter++;
    }
    return counter;
}

bool comp(List a, List b) {
    if ((a[0] == 0) && (b[0] == 0)) {
        if (a.Getsize() == b.Getsize()) {
            for (int i = 0; i < a.Getsize(); i++)
            {
                if (a[i] > b[i]) {
                    return true;

                }
                else if (b[i] > a[i]) {
                    return false;

                }
            }
        }
        else if (a.Getsize() < b.Getsize())
            return false;
        else if (a.Getsize() > b.Getsize())
            return true;
    }
    if ((a[0] == 0) && (b[0] != 0)) {
        return true;
    }
    if ((a[0] != 0) && (b[0] == 0)) {
        return false;
    }
    if (a.Getsize() == b.Getsize()) {
        for (int i = 0; i < a.Getsize(); i++)
        {
            if (a[i] > b[i]) {
                return false;

            }
            else if (b[i] > a[i]) {
                return true;

            }
        }
    }
    else if (a.Getsize() < b.Getsize())
        return true;
    else if (a.Getsize() > b.Getsize())
        return false;
    return 0;
}

int shellSort(List arr[], int n)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i += 1)
        {
            List temp = arr[i];
            int j;
            for (j = i; j >= gap && comp(temp, arr[j - gap]); j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
    return 0;
}

int main()
{
    int sizeOfInput;
    char input = NULL;
    cin >> sizeOfInput;
    List* numbers = new List[sizeOfInput];
    for (int i = -1; i < sizeOfInput; i++) {
        while (cin.get(input)) {
            if (input == '\n') break;
            numbers[i].push_back(atoi(&input));
        }
    }
    shellSort(numbers, sizeOfInput);
    for (int i = 0; i < sizeOfInput; i++) {
        for (int j = 0; j < numbers[i].Getsize(); j++)
        {
            List temp = numbers[i];
            if ((j == 0) && (temp[j] == 0)) {
                if (temp.Getsize() == 1) {
                    cout << "0";
                    continue;
                }
                cout << "-";
                continue;
            }
            printf("%d", temp[j]);
        }
        cout << endl;
    }
    delete[]numbers;
}