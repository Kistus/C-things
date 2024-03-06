#include <iostream>
using namespace std;

struct node {
    int el;
    struct node* l;
    struct node* r;
};

struct node* newNode(int el)
{
    struct node* nw = new node[sizeof(struct node)];
    nw->el = el;
    nw->l = NULL;
    nw->r = NULL;
    return nw;
}

struct node* dod_el(struct node* node, int el)
{
    if (node == NULL)
        return newNode(el);
    else if (el < node->el)
        node->l = dod_el(node->l, el);
    else
        node->r = dod_el(node->r, el);

    return node;
}

struct node* min(struct node* node)
{
    struct node* current = node;
    while (current && current->l != NULL)
        current = current->l;

    return current;
}

struct node* max(struct node* node) {
    struct node* current = node;
    while (current && current->r != NULL)
        current = current->r;

    return current;
}

struct node* search(struct node* f_node, int el) {
    if (f_node == NULL || f_node->el == el) {
        return f_node;
    }
    else if (f_node->el < el) {
        return search(f_node->r, el);
    }
    else
        return  search(f_node->l, el);
}

struct node* delete_(struct node* f_node, int el)
{
    if (f_node == NULL)
        return f_node;

    if (el < f_node->el)
        f_node->l = delete_(f_node->l, el);

    else if (el > f_node->el)
        f_node->r = delete_(f_node->r, el);

    else {
        if ((f_node->l == NULL) && (f_node->r == NULL))
            return NULL;

        else if (f_node->l == NULL) {
            struct node* temp = f_node->r;
            delete[]f_node;
            return temp;
        }
        else if (f_node->r == NULL) {
            struct node* temp = f_node->l;
            delete[]f_node;
            return temp;
        }
        struct node* temp = min(f_node->r);
        f_node->el = temp->el;
        f_node->r = delete_(f_node->r, temp->el);
    }
    return f_node;
}

int main()
{
    struct node* f_node = NULL;
    char input;
    while (true) {
        cin >> input;
        if (input == 'q') {
            break;
        }
        if (input == '+') {
            int n;
            cin >> n;
            f_node = dod_el(f_node, n);
        }
        if (input == '-') {
            int n;
            cin >> n;
            f_node = delete_(f_node, n);
        }
        if (input == 'm') {
            struct node* tmp = min(f_node);
            cout << tmp->el << endl;
        }
        if (input == 'M') {
            struct node* tmp = max(f_node);
            cout << tmp->el << endl;
        }
        if (input == '?') {
            int n;
            cin >> n;
            if (search(f_node, n) != NULL)
                cout << 1 << endl;
            else
                cout << 0 << endl;
        }
    }
    return 0;
}