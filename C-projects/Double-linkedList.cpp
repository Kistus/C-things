#include <iostream>
#include<string.h>
using namespace std;

#define BEG 71
#define END 68
#define ITER_NUMB 10
#define ALL 65

struct list_el
{
    unsigned long long int data;
    list_el* prev;
    list_el* next;
};

class List
{
    int size;
    list_el* arr[10];
    list_el* begin;
    list_el* end;
public:
    List()
    {
        for (int i = 0; i < ITER_NUMB; i++)
        {
            arr[i] = NULL;
        }
        size = 0;
        begin = NULL;
        end = NULL;
    }
    list_el* pre(int);
    void add_before(list_el*, unsigned long long int);
    void add_after(list_el*, unsigned long long int);
    void print(int) const;
    void delete_(list_el*);
    void init(int, list_el*);
    void plus(int);
    void minus(int);
};

list_el* List::pre(int x) {
    list_el* n;
    if (x == BEG)
        n = begin;
    else if (x == END)
        n = end;
    else
        n = arr[x];
    return n;
}

void List::add_before(list_el* current, unsigned long long int data) {
    list_el* nw = new list_el();
    if (begin == NULL) {
        nw->next = NULL;
        nw->prev = NULL;
        nw->data = data;
        begin = nw;
        end = nw;
    }
    else if (current->prev == NULL) {
        nw->data = data;
        nw->next = current;
        nw->prev = NULL;
        current->prev = nw;
        begin = nw;
    }
    else {
        nw->data = data;
        nw->next = current;
        nw->prev = current->prev;
        current->prev->next = nw;
        current->prev = nw;
    }
    size++;
}

void List::add_after(list_el* current, unsigned long long data) {
    list_el* nw = new list_el();
    if (begin == NULL) {
        nw->next = NULL;
        nw->prev = NULL;
        nw->data = data;
        begin = nw;
        end = nw;
    }
    else if (current->next == NULL) {
        nw->data = data;
        current->next = nw;
        nw->prev = current;
        nw->next = NULL;
        end = nw;
    }
    else {
        nw->data = data;
        nw->next = current->next;
        nw->prev = current;
        current->next->prev = nw;
        current->next = nw;
    }
    size++;
}

void List::delete_(list_el* current) {
    if (begin->next == NULL) {
        delete(current);
        begin = NULL;
        end = NULL;
        for (int i = 0; i < ITER_NUMB; i++)
            arr[i] = NULL;
    }
    else if (current->prev == NULL) {
        for (int i = 0; i < ITER_NUMB; i++)
        {
            if (arr[i] == current)
                arr[i] = arr[i]->next;
        }
        current->next->prev = NULL;
        begin = current->next;
        delete(current);
    }
    else if (current->next == NULL) {
        for (int i = 0; i < ITER_NUMB; i++)
        {
            if (arr[i] == current)
                arr[i] = arr[i]->prev;
        }
        current->prev->next = NULL;
        end = current->prev;
        delete(current);
    }
    else {
        for (int i = 0; i < ITER_NUMB; i++)
        {
            if (arr[i] == current)
                arr[i] = arr[i]->next;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete(current);
    }
    size--;
}

void List::init(int iter, list_el* n) {
    arr[iter] = n;
}

void::List::plus(int iterator) {
    if (arr[iterator]->next != NULL)
        arr[iterator] = arr[iterator]->next;
}

void::List::minus(int iterator) {
    if (arr[iterator]->prev != NULL)
        arr[iterator] = arr[iterator]->prev;
}

void List::print(const int one) const {
    if (size > 0) {
        if (one == ALL) {
            list_el* curr = begin;
            while (curr != NULL)
            {
                cout << curr->data << " ";
                curr = curr->next;
            }
            cout << endl;
        }
        else {
            list_el* curr = arr[one];
            cout << curr->data << endl;
        }
    }
}


int main() {
    List lst;
    char command[100];
    unsigned long long int number;
    int iterator;
    while (true)
    {
        cin >> command;
        if (feof(stdin) != 0)
        {
            break;
        }
        if (strcmp(command, "I") == 0) {
            memset(command, 0, 100);
            continue;
        }
        if (strcmp(command, ".A") == 0) {
            cin >> command;
            if (strcmp(command, "BEG") == 0) {
                cin >> number;
                lst.add_before(lst.pre(BEG), number);
            }
            else if (strcmp(command, "END") == 0) {
                cin >> number;
                lst.add_before(lst.pre(END), number);
            }
            else {
                cin >> number;
                lst.add_before(lst.pre(atoi(command)), number);
            }
        }
        if (strcmp(command, "A.") == 0) {
            cin >> command;
            if (strcmp(command, "BEG") == 0) {
                cin >> number;
                lst.add_after(lst.pre(BEG), number);
            }
            else if (strcmp(command, "END") == 0) {
                cin >> number;
                lst.add_after(lst.pre(END), number);
            }
            else {
                cin >> number;
                lst.add_after(lst.pre(atoi(command)), number);
            }
        }
        if (strcmp(command, "R") == 0) {
            cin >> command;
            if (strcmp(command, "BEG") == 0)
                lst.delete_(lst.pre(BEG));
            else if (strcmp(command, "END") == 0)
                lst.delete_(lst.pre(END));
            else
                lst.delete_(lst.pre(atoi(command)));
        }
        if (strcmp(command, "P") == 0) {
            cin >> command;
            if (strcmp(command, "ALL") == 0) {
                lst.print(ALL);
            }
            else {
                lst.print(atoi(command));
            }
        }
        if (strcmp(command, "i") == 0) {
            cin >> iterator;
            cin >> command;
            if (strcmp(command, "BEG") == 0)
                lst.init(iterator, lst.pre(BEG));
            else if (strcmp(command, "END") == 0)
                lst.init(iterator, lst.pre(END));
            else
                lst.init(iterator, lst.pre(atoi(command)));
        }
        if (strcmp(command, "+") == 0) {
            cin >> iterator;
            lst.plus(iterator);
        }
        if (strcmp(command, "-") == 0) {
            cin >> iterator;
            lst.minus(iterator);
        }
    }
}