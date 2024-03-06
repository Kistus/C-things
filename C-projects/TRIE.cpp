#include <iostream>
#include<string>
using namespace std;
#define Max 26

struct Trie
{
    struct Trie* galeze[Max];
    string polish;
};


struct Trie* galez()
{
    struct Trie* current = new Trie;
    for (int i = 0; i < Max; i++)
        current->galeze[i] = nullptr;
    return current;
}

void insert(struct Trie* first, string toadd, const string& translation)
{
    struct Trie* current = first;
    for (int i = 0; i < int(toadd.length()); i++)
    {
        int index = toadd[i] - 97;
        if (!current->galeze[index])
            current->galeze[index] = galez();
        current = current->galeze[index];
    }
    current->polish = translation;
}

string search(struct Trie* first, string tofind)
{
    struct Trie* current = first;
    for (int i = 0; i < int(tofind.length()); i++)
    {
        int index = tofind[i] - 97;
        if (!current->galeze[index])
            return "-";
        current = current->galeze[index];
    }
    if (current->polish.length() != 0)
        return current->polish;
    else
        return "-";
}

void star1(struct Trie* start, const string& tofind) {
    bool allnul = false;
    while (!allnul) {
        for (int i = 0; i < Max; i++)
        {
            if (start->galeze[i] != NULL) {
                if (start->galeze[i]->polish.length() != 0)
                    cout << start->galeze[i]->polish << endl;
                star1(start->galeze[i], tofind);
                if (i == 25)
                    allnul = true;
            }
            else if (i == 25)
                allnul = true;
        }
    }
}

void star(struct Trie* first, string tofind) {
    struct Trie* pCrawl = first;
    for (int i = 0; i < int(tofind.length()); i++)
    {
        int index = tofind[i] - 97;
        if (pCrawl->galeze[index] != NULL) {
            if ((i == int(tofind.length() - 1)) && (pCrawl->galeze[index]->polish.length() != 0))
                cout << pCrawl->galeze[index]->polish << endl;
        }
        else {
            cout << "-" << endl;
            return;
        }
        pCrawl = pCrawl->galeze[index];
    }
    star1(pCrawl, tofind);
}

void delete_(struct Trie* start) {
    struct Trie* first = start;
    if (first == NULL)
        return;
    for (int i = 0; i < Max; i++)
        delete_(first->galeze[i]);
    delete first;
}

int main()
{
    string word, tr;
    char input;
    struct Trie* first = galez();
    while (cin >> input)
    {
        if (input == '+') {
            cin >> word >> tr;
            insert(first, word, tr);
        }
        if (input == '?') {
            cin >> word;
            cout << search(first, word) << endl;
        }
        if (input == '*') {
            cin >> word;
            star(first, word);
        }
    }
    delete_(first);
    return 0;
}