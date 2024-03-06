#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
using namespace std;

typedef struct cannon {
    int y;
    int x;
    bool condition;
}cannon;

typedef struct engine {
    int y;
    int x;
    bool condition;
}engine;

struct ship {
    int id;
    int size;
    char owner;
    bool onboard;
    bool radar_condition;
    int head_y;
    int head_x;
    char dimention;
    int moves_counter;
    int shoots_counter;
    cannon cannon;
    engine engine;
};

typedef struct starting_position {
    int y1;
    int x1;
    int y2;
    int x2;
}starting_position;

struct spy {
    int y1;
    int x1;
    int y2;
    int x2;
};

struct player {
    starting_position starting_position;
    ship arr[40];
    int car_amount;
    int bat_amount;
    int cru_amount;
    int des_amount;
    int ship_parts;
    spy spy_arr[50];
};

void clear(int ROWS, char** arr) {
    for (int i = 0; i < ROWS; i++) {
        free(arr[i]);
    }
    free(arr);
}

void parts_placing(char owner, bool xdim, int current_ship, int c, int y, int x, int size, player* playerA, player* playerB) {
    if (owner == 'A') {
        if (xdim == false) {
            playerA->arr[current_ship].cannon.y = y + 1 * c;
            playerA->arr[current_ship].cannon.x = x;
            playerA->arr[current_ship].engine.y = y + (size - 1) * c;
            playerA->arr[current_ship].engine.x = x;
        }
        if (xdim == true) {
            playerA->arr[current_ship].cannon.y = y;
            playerA->arr[current_ship].cannon.x = x + 1 * c;
            playerA->arr[current_ship].engine.y = y;
            playerA->arr[current_ship].engine.x = x + (size - 1) * c;
        }
    }
    if (owner == 'B') {
        if (xdim == false) {
            playerB->arr[current_ship].cannon.y = y + 1 * c;
            playerB->arr[current_ship].cannon.x = x;
            playerB->arr[current_ship].engine.y = y + (size - 1) * c;
            playerB->arr[current_ship].engine.x = x;
        }
        if (xdim == true) {
            playerB->arr[current_ship].cannon.y = y;
            playerB->arr[current_ship].cannon.x = x + 1 * c;
            playerB->arr[current_ship].engine.y = y;
            playerB->arr[current_ship].engine.x = x + (size - 1) * c;
        }
    }
}

bool close_ship(int y, int x, int ROWS, int COLS, int size, int c, bool xdim, char** arr) {
    bool to_close = false;
    if (xdim == false) {
        for (int i = 0; i < size; i++) {
            if ((arr[y + i * c][x] != 32) && (arr[y + i * c][x] != 35))
            {
                to_close = true;
            }
            if (x == 0) {
                if ((arr[y + i * c][x + 1] != 32) && (arr[y + i * c][x + 1] != 35))
                {
                    to_close = true;
                }
            }
            if (x == COLS - 1) {
                if ((arr[y + i * c][x - 1] != 32) && (arr[y + i * c][x - 1] != 35))
                {
                    to_close = true;
                }
            }
            if ((i == 0) && (y != 0) && (y != ROWS - 1)) {
                if ((arr[y - c][x] != 32) && (arr[y - c][x] != 35))
                {
                    to_close = true;
                }
            }
            if ((i == size - 1) && (y + i * c != 0) && (y + i * c != ROWS - 1)) {
                if ((arr[y + i * c + c][x] != 32) && (arr[y + i * c + c][x] != 35))
                {
                    to_close = true;
                }
            }
            if ((x > 0) && (x < COLS - 1)) {
                if ((arr[y + i * c][x + 1] != 32) && (arr[y + i * c][x - 1] != 35))
                {
                    to_close = true;
                }
            }
        }
    }
    else {
        for (int i = 0; i < size; i++) {
            if ((arr[y][x + i * c] != 32) && (arr[y][x + i * c] != 35))
            {
                to_close = true;
            }
            if (y == 0) {
                if ((arr[y + 1][x + i * c] != 32) && (arr[y + 1][x + i * c] != 35))
                {
                    to_close = true;
                }
            }
            if (x == ROWS - 1) {
                if ((arr[y - 1][x + i * c] != 32) && (arr[y - 1][x + i * c] != 35))
                {
                    to_close = true;
                }
            }
            if ((i == 0) && (x != 0) && (x != COLS - 1)) {
                if ((arr[y][x - c] != 32) && (arr[y][x - c] != 35))
                {
                    to_close = true;
                }
            }
            if ((i == size - 1) && (x + i * c != 0) && (x + i * c != COLS - 1)) {
                if ((arr[y][x + i * c + c] != 32) && (arr[y][x + i * c + c] != 35))
                {
                    to_close = true;
                }
            }
            if ((y > 0) && (y < ROWS - 1)) {
                if ((arr[y + 1][x + i * c] != 32) && (arr[y - 1][x + i * c] != 35))
                {
                    to_close = true;
                }
            }
        }
    }
    return to_close;
}

char** set_board_size(int ROWS, int COLS) {
    char** arr = (char**)malloc(ROWS * sizeof(char*));
    for (int i = 0; i < ROWS; i++) {
        arr[i] = (char*)malloc(COLS * sizeof(char));
    }
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            arr[i][j] = ' ';
        }
    }
    return arr;
}

void shooting(int y, int x, char** arr, int rows, int cols, char owner, int current_ship, player* playerA, player* playerB) {
    bool all_ship_placed = true;
    bool field_exist = true;
    if ((y > rows) || (y < 0) || (x > cols) || (x < 0)) {
        field_exist = false;
        cout << "INVALID OPERATION \"SHOOT " << y << " " << x << "\": FIELD DOES NOT EXIST" << endl; clear(rows, arr); exit(1);
    }

    for (int i = 0; i < 40; i++) {
        if (((playerA->arr[i].onboard == false) && (playerA->arr[i].size != 0)) || ((playerB->arr[i].onboard == false) && (playerB->arr[i].size != 0)))
        {
            all_ship_placed = false;
            cout << "INVALID OPERATION \"SHOOT " << y << " " << x << "\": NOT ALL SHIPS PLACED" << endl; clear(rows, arr); exit(1);
        }
    }
    if ((all_ship_placed == true) && (field_exist == true)) {
        if ((owner == 'A') && (current_ship != -1))
        {
            playerA->arr[current_ship].shoots_counter++;
        }
        if ((owner == 'B') && (current_ship != -1))
        {
            playerB->arr[current_ship].shoots_counter++;
        }
        if (arr[y][x] == '+')
        {
            arr[y][x] = 'x';
            if (owner == 'A') {
                playerB->ship_parts--;
                for (int i = 0; i < 40; i++)
                {
                    if ((x == playerB->arr[i].cannon.x) && (y == playerB->arr[i].cannon.y))
                    {
                        playerB->arr[i].cannon.condition = false;
                    }
                    if ((x == playerB->arr[i].engine.x) && (y == playerB->arr[i].engine.y))
                    {
                        playerB->arr[i].engine.condition = false;
                    }
                    if ((x == playerB->arr[i].head_x) && (y == playerB->arr[i].head_y))
                    {
                        playerB->arr[i].radar_condition = false;
                    }
                }
            }
            if (owner == 'B') {
                playerA->ship_parts--;
                for (int i = 0; i < 40; i++)
                {
                    if ((x == playerA->arr[i].cannon.x) && (y == playerA->arr[i].cannon.y))
                    {
                        playerA->arr[i].cannon.condition = false;
                    }
                    if ((x == playerA->arr[i].engine.x) && (y == playerA->arr[i].engine.y))
                    {
                        playerA->arr[i].engine.condition = false;
                    }
                    if ((x == playerA->arr[i].head_x) && (y == playerA->arr[i].head_y))
                    {
                        playerA->arr[i].radar_condition = false;
                    }
                }
            }
        }
    }
}

void reef_placing(int y, int x, int ROWS, int COLS, char** arr) {
    if ((y >= 0) && (y <= ROWS - 1) && (x >= 0) && (x <= COLS - 1))
        arr[y][x] = '#';
}

void basic_print(int ROWS, int COLS, char** arr, player* playerA, player* playerB) {
    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            cout << arr[i][j];
        }
        cout << endl;
    }
    cout << "PARTS REMAINING:: A : " << playerA->ship_parts << " B : " << playerB->ship_parts << endl;
}

void fleet(char owner, int car, int bat, int cru, int des, player* playerA, player* playerB) {
    int i;
    if (owner == 'A') {
        for (i = 0; i < car; i++)
        {
            playerA->arr[i].owner = owner;
            playerA->arr[i].size = 5;
            playerA->arr[i].onboard = false;
        }
        for (i; i < bat + car; i++)
        {
            playerA->arr[i].owner = owner;
            playerA->arr[i].size = 4;
            playerA->arr[i].onboard = false;
        }
        for (i; i < cru + bat + car; i++)
        {
            playerA->arr[i].owner = owner;
            playerA->arr[i].size = 3;
            playerA->arr[i].onboard = false;
        }
        for (i; i < des + cru + bat + car; i++)
        {
            playerA->arr[i].owner = owner;
            playerA->arr[i].size = 2;
            playerA->arr[i].onboard = false;
        }
    }
    else if (owner == 'B') {
        for (i = 0; i < car; i++)
        {
            playerB->arr[i].owner = owner;
            playerB->arr[i].size = 5;
            playerB->arr[i].onboard = false;
        }
        for (i; i < bat + car; i++)
        {
            playerB->arr[i].owner = owner;
            playerB->arr[i].size = 4;
            playerB->arr[i].onboard = false;
        }
        for (i; i < cru + bat + car; i++)
        {
            playerB->arr[i].owner = owner;
            playerB->arr[i].size = 3;
            playerB->arr[i].onboard = false;
        }
        for (i; i < des + cru + bat + car; i++)
        {
            playerB->arr[i].owner = owner;
            playerB->arr[i].size = 2;
            playerB->arr[i].onboard = false;
        }
    }
}

void A_xdim(char owner, int size, int cond, int start_pos_x1, int start_pos_x2, int c, bool xdim, int y, int x, char dimention, int id, char komand[3], int condition, char** arr, bool extended, int ROWS, int COLS, player* playerA, player* playerB) {
    bool to_close = false;
    for (int i = 0; i < size; i++)
    {
        if ((start_pos_x1 <= x + i * c) && (x + i * c <= start_pos_x2)) {}
        else
        {
            cout << "INVALID OPERATION \"";
            if (extended == true) {
                cout << "SHIP " << y << " " << x << " " << dimention << " " << id << " ";
                for (int j = 0; j < 3; j++) { cout << komand[j]; }
                cout << " " << condition << "\": NOT IN STARTING POSITION" << endl;
                clear(ROWS, arr);
                exit(1);
            }
            else if (extended == false) {
                cout << "PLACE_SHIP " << y << " " << x << " " << dimention << " " << id << " ";
                for (int j = 0; j < 3; j++) { cout << komand[j]; }
                cout << "\": NOT IN STARTING POSITION" << endl;
                clear(ROWS, arr);
                exit(1);
            }
        }
    }
    for (int i = 0; i < size; i++)
    {
        if (arr[y][x + i * c] == '#') {
            cout << "INVALID OPERATION \"";
            if (extended == true) {
                cout << "SHIP " << owner << " " << y << " " << x << " " << dimention << " " << id << " ";
                for (int j = 0; j < 3; j++) { cout << komand[j]; }
                cout << " " << condition << "\": PLACING SHIP ON REEF" << endl;
                clear(ROWS, arr);
                exit(1);
            }
            else if (extended == false) {
                cout << "PLACE_SHIP " << y << " " << x << " " << dimention << " " << id << " ";
                for (int j = 0; j < 3; j++) { cout << komand[j]; }
                cout << "\": PLACING SHIP ON REEF" << endl;
                clear(ROWS, arr);
                exit(1);
            }
        }
    }
    to_close = close_ship(y, x, ROWS, COLS, size, c, xdim, arr);
    if (to_close == true) {
        cout << "INVALID OPERATION \"";
        if (extended == true) {
            cout << "SHIP " << owner << " " << y << " " << x << " " << dimention << " " << id << " ";
            for (int j = 0; j < 3; j++) { cout << komand[j]; }
            cout << " " << condition << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
            clear(ROWS, arr);
            exit(1);
        }
        else if (extended == false) {
            cout << "PLACE_SHIP " << y << " " << x << " " << dimention << " " << id << " ";
            for (int j = 0; j < 3; j++) { cout << komand[j]; }
            cout << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
            clear(ROWS, arr);
            exit(1);
        }
    }
    for (int i = 0; i < size; i++)
    {
        if (cond % 10 == 1)
        {
            arr[y][x + i * c] = '+';
            playerA->ship_parts++;
        }
        else if (cond % 10 == 0)
        {
            arr[y][x + i * c] = 'x';
        }
        cond /= 10;
    }
    for (int i = 0; i < 40; i++) {
        if ((playerA->arr[i].onboard == false) && (playerA->arr[i].size == size)) {
            playerA->arr[i].id = id;
            playerA->arr[i].onboard = true;
            playerA->arr[i].head_x = x;
            playerA->arr[i].head_y = y;
            playerA->arr[i].dimention = dimention;
            playerA->arr[i].cannon.condition = true;
            playerA->arr[i].engine.condition = true;
            playerA->arr[i].radar_condition = true;
            parts_placing(owner, xdim, i, c, y, x, size, playerA, playerB);
            break;
        }
    }
}

void A_no_xdim(char owner, int size, int cond, int start_pos_y1, int start_pos_y2, int c, bool xdim, int y, int x, char dimention, int id, char komand[3], int condition, char** arr, bool extended, int ROWS, int COLS, player* playerA, player* playerB) {
    bool to_close = false;
    for (int i = 0; i < size; i++)
    {
        if ((start_pos_y1 <= y + i * c) && (y + i * c <= start_pos_y2)) {}
        else
        {
            cout << "INVALID OPERATION \"";
            if (extended == true) {
                cout << "SHIP " << owner << " " << y << " " << x << " " << dimention << " " << id << " ";
                for (int j = 0; j < 3; j++) { cout << komand[j]; }
                cout << " " << condition << "\": NOT IN STARTING POSITION" << endl;
                clear(ROWS, arr);
                exit(1);
            }
            else if (extended == false) {
                cout << "PLACE_SHIP " << y << " " << x << " " << dimention << " " << id << " ";
                for (int j = 0; j < 3; j++) { cout << komand[j]; }
                cout << "\": NOT IN STARTING POSITION" << endl;
                clear(ROWS, arr);
                exit(1);
            }
        }
    }
    for (int i = 0; i < size; i++)
    {
        if (arr[y + i * c][x] == '#') {
            cout << "INVALID OPERATION \"";
            if (extended == true) {
                cout << "SHIP " << owner << " " << y << " " << x << " " << dimention << " " << id << " ";
                for (int j = 0; j < 3; j++) { cout << komand[j]; }
                cout << " " << condition << "\": PLACING SHIP ON REEF" << endl;
                clear(ROWS, arr);
                exit(1);
            }
            else if (extended == false) {
                cout << "PLACE_SHIP " << y << " " << x << " " << dimention << " " << id << " ";
                for (int j = 0; j < 3; j++) { cout << komand[j]; }
                cout << "\": PLACING SHIP ON REEF" << endl;
                clear(ROWS, arr);
                exit(1);
            }
        }
    }
    to_close = close_ship(y, x, ROWS, COLS, size, c, xdim, arr);
    if (to_close == true) {
        cout << "INVALID OPERATION \"";
        if (extended == true) {
            cout << "SHIP " << owner << " " << y << " " << x << " " << dimention << " " << id << " ";
            for (int j = 0; j < 3; j++) { cout << komand[j]; }
            cout << " " << condition << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
            clear(ROWS, arr);
            exit(1);
        }
        else if (extended == false) {
            cout << "PLACE_SHIP " << y << " " << x << " " << dimention << " " << id << " ";
            for (int j = 0; j < 3; j++) { cout << komand[j]; }
            cout << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
            clear(ROWS, arr);
            exit(1);
        }
    }
    for (int i = 0; i < size; i++)
    {
        if (cond % 10 == 1) {
            {arr[y + i * c][x] = '+';
            playerA->ship_parts++; }
        }
        if (cond % 10 == 0) {
            {arr[y + i * c][x] = 'x'; }
        }
        cond /= 10;
    }
    for (int i = 0; i < 40; i++) {
        if ((playerA->arr[i].onboard == false) && (playerA->arr[i].size == size)) {
            playerA->arr[i].id = id;
            playerA->arr[i].onboard = true;
            playerA->arr[i].head_x = x;
            playerA->arr[i].head_y = y;
            playerA->arr[i].dimention = dimention;
            playerA->arr[i].cannon.condition = true;
            playerA->arr[i].engine.condition = true;
            playerA->arr[i].radar_condition = true;
            parts_placing(owner, xdim, i, c, y, x, size, playerA, playerB);
            break;
        }
    }
}

void placing_ship_A(char owner, int size, int amount, int cond, int start_pos_y1, int start_pos_x1, int start_pos_y2, int start_pos_x2, int c, bool xdim, int y, int x, char dimention, int id, char komand[3], int condition, char** arr, bool extended, int ROWS, int COLS, player* playerA, player* playerB) {
    for (int i = 0; i < 40; i++)
    {
        if ((id == playerA->arr[i].id) && (size == playerA->arr[i].size) && (playerA->arr[i].onboard == true))
        {
            cout << "INVALID OPERATION \"";
            if (extended == true) {
                cout << "SHIP " << owner << " " << y << " " << x << " " << dimention << " " << id << " ";
                for (int j = 0; j < 3; j++) { cout << komand[j]; }
                cout << " " << condition << "\": SHIP ALREADY PRESENT" << endl;
                clear(ROWS, arr);
                exit(1);
            }
            else if (extended == false) {
                cout << "PLACE_SHIP " << y << " " << x << " " << dimention << " " << id << " ";
                for (int j = 0; j < 3; j++) { cout << komand[j]; }
                cout << "\": SHIP ALREADY PRESENT" << endl;
                clear(ROWS, arr);
                exit(1);
            }
        }
    }
    if (id >= amount) {
        cout << "INVALID OPERATION \"";
        if (extended == true) {
            cout << "SHIP " << owner << " " << y << " " << x << " " << dimention << " " << id << " ";
            for (int j = 0; j < 3; j++) { cout << komand[j]; }
            cout << " " << condition << "\": ALL SHIPS OF THE CLASS ALREADY SET" << endl;
            clear(ROWS, arr);
            exit(1);
        }
        else if (extended == false) {
            cout << "PLACE_SHIP " << y << " " << x << " " << dimention << " " << id << " ";
            for (int j = 0; j < 3; j++) { cout << komand[j]; }
            cout << "\": ALL SHIPS OF THE CLASS ALREADY SET" << endl;
            clear(ROWS, arr);
            exit(1);
        }
    }

    if (xdim == false) {
        A_no_xdim(owner, size, cond, start_pos_y1, start_pos_y2, c, xdim, y, x, dimention, id, komand, condition, arr, extended, ROWS, COLS, playerA, playerB);
    }
    else {
        A_xdim(owner, size, cond, start_pos_x1, start_pos_x2, c, xdim, y, x, dimention, id, komand, condition, arr, extended, ROWS, COLS, playerA, playerB);
    }
}

void B_xdim(char owner, int size, int cond, int start_pos_x1, int start_pos_x2, int c, bool xdim, int y, int x, char dimention, int id, char komand[3], int condition, char** arr, bool extended, int ROWS, int COLS, player* playerA, player* playerB) {
    bool to_close = false;
    for (int i = 0; i < size; i++)
    {
        if (start_pos_x1 <= x + i * c <= start_pos_x2) {}
        else {
            cout << "INVALID OPERATION \"";
            if (extended == true) {
                cout << "SHIP " << owner << " " << y << " " << x << " " << dimention << " " << id << " ";
                for (int j = 0; j < 3; j++) { cout << komand[j]; }
                cout << " " << condition << "\": NOT IN STARTING POSITION" << endl;
                clear(ROWS, arr);
                exit(1);
            }
            else if (extended == false) {
                cout << "PLACE_SHIP " << y << " " << x << " " << dimention << " " << id << " ";
                for (int j = 0; j < 3; j++) { cout << komand[j]; }
                cout << "\": NOT IN STARTING POSITION" << endl;
                clear(ROWS, arr);
                exit(1);
            }
        }
    }
    for (int i = 0; i < size; i++)
    {
        if (arr[y][x + i * c] == '#') {
            cout << "INVALID OPERATION \"";
            if (extended == true) {
                cout << "SHIP " << owner << " " << y << " " << x << " " << dimention << " " << id << " ";
                for (int j = 0; j < 3; j++) { cout << komand[j]; }
                cout << " " << condition << "\": PLACING SHIP ON REEF" << endl;
                clear(ROWS, arr);
                exit(1);
            }
            else if (extended == false) {
                cout << "PLACE_SHIP " << y << " " << x << " " << dimention << " " << id << " ";
                for (int j = 0; j < 3; j++) { cout << komand[j]; }
                cout << "\": PLACING SHIP ON REEF" << endl;
                clear(ROWS, arr);
                exit(1);
            }
        }
    }
    to_close = close_ship(y, x, ROWS, COLS, size, c, xdim, arr);
    if (to_close == true) {
        cout << "INVALID OPERATION \"";
        if (extended == true) {
            cout << "SHIP " << owner << " " << y << " " << x << " " << dimention << " " << id << " ";
            for (int j = 0; j < 3; j++) { cout << komand[j]; }
            cout << " " << condition << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
            clear(ROWS, arr);
            exit(1);
        }
        else if (extended == false) {
            cout << "PLACE_SHIP " << y << " " << x << " " << dimention << " " << id << " ";
            for (int j = 0; j < 3; j++) { cout << komand[j]; }
            cout << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
            clear(ROWS, arr);
            exit(1);
        }
    }
    for (int i = 0; i < size; i++)
    {
        if (cond % 10 == 1)
        {
            arr[y][x + i * c] = '+';
            playerB->ship_parts++;
        }
        else if (cond % 10 == 0)
        {
            arr[y][x + i * c] = 'x';
        }
        cond /= 10;
    }
    for (int i = 0; i < 40; i++) {
        if ((playerB->arr[i].onboard == false) && (playerB->arr[i].size == size)) {
            playerB->arr[i].id = id;
            playerB->arr[i].onboard = true;
            playerB->arr[i].head_x = x;
            playerB->arr[i].head_y = y;
            playerB->arr[i].dimention = dimention;
            playerB->arr[i].cannon.condition = true;
            playerB->arr[i].engine.condition = true;
            playerB->arr[i].radar_condition = true;
            parts_placing(owner, xdim, i, c, y, x, size, playerA, playerB);
            break;
        }
    }
}

void B_no_xdim(char owner, int size, int cond, int start_pos_y1, int start_pos_y2, int c, bool xdim, int y, int x, char dimention, int id, char komand[3], int condition, char** arr, bool extended, int ROWS, int COLS, player* playerA, player* playerB) {
    bool to_close = false;
    for (int i = 0; i < size; i++)
    {
        if (start_pos_y1 <= x + i * c <= start_pos_y2) {}
        else {
            cout << "INVALID OPERATION \"";
            if (extended == true) {
                cout << "SHIP " << owner << " " << y << " " << x << " " << dimention << " " << id << " ";
                for (int j = 0; j < 3; j++) { cout << komand[j]; }
                cout << " " << condition << "\": NOT IN STARTING POSITION" << endl;
                clear(ROWS, arr);
                exit(1);
            }
            else if (extended == false) {
                cout << "PLACE_SHIP " << y << " " << x << " " << dimention << " " << id << " ";
                for (int j = 0; j < 3; j++) { cout << komand[j]; }
                cout << "\": NOT IN STARTING POSITION" << endl;
                clear(ROWS, arr);
                exit(1);
            }
        }
    }
    for (int i = 0; i < size; i++)
    {
        if (arr[y + i * c][x] == '#') {
            cout << "INVALID OPERATION \"";
            if (extended == true) {
                cout << "SHIP " << owner << " " << y << " " << x << " " << dimention << " " << id << " ";
                for (int j = 0; j < 3; j++) { cout << komand[j]; }
                cout << " " << condition << "\": PLACING SHIP ON REEF" << endl;
                clear(ROWS, arr);
                exit(1);
            }
            else if (extended == false) {
                cout << "PLACE_SHIP " << y << " " << x << " " << dimention << " " << id << " ";
                for (int j = 0; j < 3; j++) { cout << komand[j]; }
                cout << "\": PLACING SHIP ON REEF" << endl;
                clear(ROWS, arr);
                exit(1);
            }
        }
    }
    to_close = close_ship(y, x, ROWS, COLS, size, c, xdim, arr);
    if (to_close == true) {
        cout << "INVALID OPERATION \"";
        if (extended == true) {
            cout << "SHIP " << owner << " " << y << " " << x << " " << dimention << " " << id << " ";
            for (int j = 0; j < 3; j++) { cout << komand[j]; }
            cout << " " << condition << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
            clear(ROWS, arr);
            exit(1);
        }
        else if (extended == false) {
            cout << "PLACE_SHIP " << y << " " << x << " " << dimention << " " << id << " ";
            for (int j = 0; j < 3; j++) { cout << komand[j]; }
            cout << "\": PLACING SHIP TOO CLOSE TO OTHER SHIP" << endl;
            clear(ROWS, arr);
            exit(1);
        }
    }
    for (int i = 0; i < size; i++)
    {
        if (cond % 10 == 1)
        {
            arr[y + i * c][x] = '+';
            playerB->ship_parts++;
        }
        else if (cond % 10 == 0)
        {
            arr[y + i * c][x] = 'x';
        }
        cond /= 10;
    }
    for (int i = 0; i < 40; i++) {
        if ((playerB->arr[i].onboard == false) && (playerB->arr[i].size == size)) {
            playerB->arr[i].id = id;
            playerB->arr[i].onboard = true;
            playerB->arr[i].head_x = x;
            playerB->arr[i].head_y = y;
            playerB->arr[i].dimention = dimention;
            playerB->arr[i].cannon.condition = true;
            playerB->arr[i].engine.condition = true;
            playerB->arr[i].radar_condition = true;
            parts_placing(owner, xdim, i, c, y, x, size, playerA, playerB);
            break;
        }
    }
}

void placing_ship_B(char owner, int size, int amount, int cond, int start_pos_y1, int start_pos_x1, int start_pos_y2, int start_pos_x2, int c, bool xdim, int y, int x, char dimention, int id, char komand[3], int condition, char** arr, bool extended, int ROWS, int COLS, player* playerA, player* playerB) {
    for (int i = 0; i < 40; i++)
    {
        if (id == playerB->arr[i].id && size == playerB->arr[i].size && playerB->arr[i].onboard == true)
        {
            cout << "INVALID OPERATION \"";
            if (extended == true) {
                cout << "SHIP " << owner << " " << y << " " << x << " " << dimention << " " << id << " ";
                for (int j = 0; j < 3; j++) { cout << komand[j]; }
                cout << " " << condition << "\": SHIP ALREADY PRESENT" << endl;
                clear(ROWS, arr);
                exit(1);
            }
            else if (extended == false) {
                cout << "PLACE_SHIP " << y << " " << x << " " << dimention << " " << id << " ";
                for (int j = 0; j < 3; j++) { cout << komand[j]; }
                cout << "\": SHIP ALREADY PRESENT" << endl;
                clear(ROWS, arr);
                exit(1);
            }
        }
    }
    if (id >= amount) {
        cout << "INVALID OPERATION \"";
        if (extended == true) {
            cout << "SHIP " << owner << " " << y << " " << x << " " << dimention << " " << id << " ";
            for (int j = 0; j < 3; j++) { cout << komand[j]; }
            cout << " " << condition << "\": ALL SHIPS OF THE CLASS ALREADY SET" << endl;
            clear(ROWS, arr);
            exit(1);
        }
        else if (extended == false) {
            cout << "PLACE_SHIP " << y << " " << x << " " << dimention << " " << id << " ";
            for (int j = 0; j < 3; j++) { cout << komand[j]; }
            cout << "\": ALL SHIPS OF THE CLASS ALREADY SET" << endl;
            clear(ROWS, arr);
            exit(1);
        }
    }
    if (xdim == false) {
        B_no_xdim(owner, size, cond, start_pos_y1, start_pos_y2, c, xdim, y, x, dimention, id, komand, condition, arr, extended, ROWS, COLS, playerA, playerB);
    }
    else {
        B_xdim(owner, size, cond, start_pos_x1, start_pos_x2, c, xdim, y, x, dimention, id, komand, condition, arr, extended, ROWS, COLS, playerA, playerB);
    }
}

void placing_ship(char owner, int y, int x, char dimention, int id, char komand[3], int condition, char** arr, bool extended, int ROWS, int COLS, player* playerA, player* playerB) {
    const int CAR = 214, BAT = 215, CRU = 234, DES = 220, N = 78, S = 83, E = 69, W = 87;
    int  c = 1, start_pos_y1 = 0, start_pos_x1 = 0, start_pos_y2 = 0, start_pos_x2 = 0, amount = 0, cond, size = 0;
    bool xdim = false;
    for (int i = 0; i < 3; i++)
    {
        size += komand[i];
    }
    switch (dimention)
    {
    case S:
        c = -1;
        break;
    case E:
        c = -1;
        xdim = true;
        break;
    case W:
        xdim = true;
        break;
    }
    if (owner == 'A') {
        start_pos_y1 = playerA->starting_position.y1;
        start_pos_x1 = playerA->starting_position.x1;
        start_pos_y2 = playerA->starting_position.y2;
        start_pos_x2 = playerA->starting_position.x2;
        switch (size)
        {
        case CAR:
            size = 5;
            amount = playerA->car_amount;
            if (extended == true) { cond = condition; }
            else { cond = 11111; }
            break;
        case BAT:
            size = 4;
            amount = playerA->bat_amount;
            if (extended == true) { cond = condition; }
            else { cond = 1111; }
            break;
        case CRU:
            size = 3;
            amount = playerA->cru_amount;
            if (extended == true) { cond = condition; }
            else { cond = 111; }
            break;
        case DES:
            size = 2;
            amount = playerA->des_amount;
            if (extended == true) { cond = condition; }
            else { cond = 11; }
            break;
        }
        long p = 0;
        while (cond)
        {
            p = p * 10 + cond % 10;
            cond /= 10;
        }
        cond = p;
        placing_ship_A(owner, size, amount, cond, start_pos_y1, start_pos_x1, start_pos_y2, start_pos_x2, c, xdim, y, x, dimention, id, komand, condition, arr, extended, ROWS, COLS, playerA, playerB);
    }
    if (owner == 'B') {
        start_pos_y1 = playerB->starting_position.y1;
        start_pos_x1 = playerB->starting_position.x1;
        start_pos_y2 = playerB->starting_position.y2;
        start_pos_x2 = playerB->starting_position.x2;
        switch (size)
        {
        case CAR:
            size = 5;
            amount = playerB->car_amount;
            if (extended == true) { cond = condition; }
            else { cond = 11111; }
            break;
        case BAT:
            size = 4;
            amount = playerB->bat_amount;
            if (extended == true) { cond = condition; }
            else { cond = 1111; }
            break;
        case CRU:
            size = 3;
            amount = playerB->cru_amount;
            if (extended == true) { cond = condition; }
            else { cond = 111; }
            break;
        case DES:
            size = 2;
            amount = playerB->des_amount;
            if (extended == true) { cond = condition; }
            else { cond = 11; }
            break;
        }
        long p = 0;
        while (cond)
        {
            p = p * 10 + cond % 10;
            cond /= 10;
        }
        cond = p;
        placing_ship_B(owner, size, amount, cond, start_pos_y1, start_pos_x1, start_pos_y2, start_pos_x2, c, xdim, y, x, dimention, id, komand, condition, arr, extended, ROWS, COLS, playerA, playerB);
    }
}

void move_F(bool xdim, int c, int size, int y, int x, int moves_count, bool eng_cond, int current_ship, int id, char komand[3], char owner, char** arr, int ROWS, int COLS, player* playerA, player* playerB) {
    if ((moves_count > 2) || ((moves_count > 1) && (size == 5))) {
        cout << "INVALID OPERATION \"MOVE " << id << " ";
        for (int i = 0; i < 3; i++) { cout << komand[i]; }
        cout << " F\": SHIP MOVED ALREADY"; clear(ROWS, arr);
        exit(1);
    }
    if (eng_cond == false) {
        cout << "INVALID OPERATION \"MOVE " << id << " ";
        for (int i = 0; i < 3; i++) { cout << komand[i]; }
        cout << " F\": SHIP CANNOT MOVE"; clear(ROWS, arr);
        exit(1);
    }
    if (xdim == false) {
        if ((y == 0) || (y == ROWS - 1)) {
            cout << "INVALID OPERATION \"MOVE " << id << " ";
            for (int i = 0; i < 3; i++) { cout << komand[i]; }
            cout << " F\": SHIP WENT FROM BOARD"; clear(ROWS, arr);
            exit(1);
        }
        else if (arr[y - 1 * c][x] == '#') {
            cout << "INVALID OPERATION \"MOVE " << id << " ";
            for (int i = 0; i < 3; i++) { cout << komand[i]; }
            cout << " F\": PLACING SHIP ON REEF"; clear(ROWS, arr);
            exit(1);
        }
        for (int i = 0; i < size; i++)
        {
            arr[y + i * c][x] = ' ';
        }
        if (close_ship(y - 1 * c, x, ROWS, COLS, size, c, xdim, arr) == true) {
            for (int i = 0; i < size; i++) { arr[y + i * c][x] = '+'; }
            cout << "INVALID OPERATION \"MOVE " << id << " ";
            for (int i = 0; i < 3; i++) { cout << komand[i]; }
            cout << " F\": PLACING SHIP TOO CLOSE TO OTHER SHIP"; clear(ROWS, arr);
            exit(1);
        }
        else {
            for (int i = 0; i < size; i++)
            {
                arr[(y - 1 * c) + i * c][x] = '+';
                if (owner == 'A') {
                    playerA->arr[current_ship].head_y = y - 1 * c;
                    parts_placing(owner, xdim, current_ship, c, playerA->arr[current_ship].head_y, playerA->arr[current_ship].head_x, size, playerA, playerB);
                }
                if (owner == 'B') {
                    playerB->arr[current_ship].head_y = y - 1 * c;
                    parts_placing(owner, xdim, current_ship, c, playerA->arr[current_ship].head_y, playerA->arr[current_ship].head_x, size, playerA, playerB);
                }
            }
            if (owner == 'A')
            {
                playerA->arr[current_ship].moves_counter++;
            }
            if (owner == 'B')
            {
                playerB->arr[current_ship].moves_counter++;
            }
        }
    }
    else {
        if ((x == 0) || (x == COLS - 1)) {
            cout << "INVALID OPERATION \"MOVE " << id << " ";
            for (int i = 0; i < 3; i++) { cout << komand[i]; }
            cout << " F\": SHIP WENT FROM BOARD"; clear(ROWS, arr);
            exit(1);
        }
        if (arr[y][x - 1 * c] == '#') {
            cout << "INVALID OPERATION \"MOVE " << id << " ";
            for (int i = 0; i < 3; i++) { cout << komand[i]; }
            cout << " F\": PLACING SHIP ON REEF"; clear(ROWS, arr);
            exit(1);
        }
        for (int i = 0; i < size; i++) { arr[y][x + i * c] = ' '; }
        if (close_ship(y, x - 1 * c, ROWS, COLS, size, c, xdim, arr) == true) {
            for (int i = 0; i < size; i++) { arr[y][x + i * c] = '+'; }
            cout << "INVALID OPERATION \"MOVE " << id << " ";
            for (int i = 0; i < 3; i++) { cout << komand[i]; }
            cout << " F\": PLACING SHIP TOO CLOSE TO OTHER SHIP"; clear(ROWS, arr);
            exit(1);
        }
        else {
            for (int i = 0; i < size; i++)
            {
                arr[y][(x - 1 * c) + i * c] = '+';
                if (owner == 'A') {
                    playerA->arr[current_ship].head_x = x - 1 * c;
                    parts_placing(owner, xdim, current_ship, c, playerA->arr[current_ship].head_y, playerA->arr[current_ship].head_x, size, playerA, playerB);
                }
                if (owner == 'B') {
                    playerB->arr[current_ship].head_x = x - 1 * c;
                    parts_placing(owner, xdim, current_ship, c, playerA->arr[current_ship].head_y, playerA->arr[current_ship].head_x, size, playerA, playerB);
                }
            }
            if (owner == 'A')
            {
                playerA->arr[current_ship].moves_counter++;
            }
            if (owner == 'B')
            {
                playerB->arr[current_ship].moves_counter++;
            }
        }
    }
}

void move_L(bool xdim, int c, int size, int y, int x, int moves_count, bool eng_cond, int current_ship, int id, char komand[3], char owner, char** arr, int ROWS, int COLS, player* playerA, player* playerB) {
    if ((moves_count > 2) || ((moves_count > 1) && (size == 5))) {
        cout << "INVALID OPERATION \"MOVE " << id << " ";
        for (int i = 0; i < 3; i++) { cout << komand[i]; }
        cout << " L\": SHIP MOVED ALREADY"; clear(ROWS, arr);
        exit(1);
    }
    if (eng_cond == false) {
        cout << "INVALID OPERATION \"MOVE " << id << " ";
        for (int i = 0; i < 3; i++) { cout << komand[i]; }
        cout << " L\": SHIP CANNOT MOVE"; clear(ROWS, arr);
        exit(1);
    }
    if (xdim == false) {
        if ((x - (size - 1) * c < 0) || (x - (size - 1) * c > COLS - 1) || (y == 0) || (y == ROWS - 1) || ((x == 0) && (c == 1)) || ((x == COLS - 1) && (c == -1))) {
            cout << "INVALID OPERATION \"MOVE " << id << " ";
            for (int i = 0; i < 3; i++) { cout << komand[i]; }
            cout << " L\": SHIP WENT FROM BOARD"; clear(ROWS, arr);
            exit(1);
        }
        for (int k = 0; k < size; k++) {
            if (arr[y - 1 * c][x - k * c] == '#') {
                cout << "INVALID OPERATION \"MOVE " << id << " ";
                for (int i = 0; i < 3; i++) { cout << komand[i]; }
                cout << " L\": PLACING SHIP ON REEF"; clear(ROWS, arr);
                exit(1);
            }
        }
        for (int i = 0; i < size; i++) { arr[y + i * c][x] = ' '; }
        if (close_ship(y - 1 * c, x - (size - 1) * c, ROWS, COLS, size, c, true, arr) == true) {
            for (int i = 0; i < size; i++) { arr[y + i * c][x] = '+'; }
            cout << "INVALID OPERATION \"MOVE " << id << " ";
            for (int j = 0; j < 3; j++) { cout << komand[j]; }
            cout << " L\": PLACING SHIP TOO CLOSE TO OTHER SHIP"; clear(ROWS, arr);
            exit(1);
        }
        for (int i = 0; i < size; i++)
        {
            arr[y - 1 * c][x - i * c] = '+';
            if (owner == 'A') {
                playerA->arr[current_ship].head_y = y - 1 * c;
                playerA->arr[current_ship].head_x = x - i * c;
                parts_placing(owner, true, current_ship, c, playerA->arr[current_ship].head_y, playerA->arr[current_ship].head_x, size, playerA, playerB);
                if (c == 1) { playerA->arr[current_ship].dimention = 'W'; }
                if (c == -1) { playerA->arr[current_ship].dimention = 'E'; }
            }
            if (owner == 'B') {
                playerB->arr[current_ship].head_y = y - 1 * c;
                playerB->arr[current_ship].head_x = x - i * c;
                parts_placing(owner, true, current_ship, c, playerA->arr[current_ship].head_y, playerA->arr[current_ship].head_x, size, playerA, playerB);
                if (c == 1) { playerB->arr[current_ship].dimention = 'W'; }
                if (c == -1) { playerB->arr[current_ship].dimention = 'E'; }
            }
        }
        if (owner == 'A') { playerA->arr[current_ship].moves_counter++; }
        if (owner == 'B') { playerB->arr[current_ship].moves_counter++; }
    }
    else {
        if ((y + (size - 1) * c < 0) || (y + (size - 1) * c > ROWS - 1) || (x == 0) || (x == COLS - 1) || ((y == 0) && (c == -1)) || ((y == ROWS - 1) && (c == -1))) {
            cout << "INVALID OPERATION \"MOVE " << id << " ";
            for (int i = 0; i < 3; i++) { cout << komand[i]; }
            cout << " L\": SHIP WENT FROM BOARD"; clear(ROWS, arr);
            exit(1);
        }
        for (int k = 0; k < size; k++)
        {
            if (arr[y + k * c][x - 1 * c] == '#') {
                cout << "INVALID OPERATION \"MOVE " << id << " ";
                for (int i = 0; i < 3; i++) { cout << komand[i]; }
                cout << " L\": PLACING SHIP ON REEF"; clear(ROWS, arr);
                exit(1);
            }
        }
        for (int i = 0; i < size; i++) { arr[y][x + i * c] = ' '; }
        if (close_ship(y + (size - 1) * c, x - 1 * c, ROWS, COLS, size, c * -1, false, arr) == true) {
            for (int i = 0; i < size; i++) { arr[y][x + i * c] = '+'; }
            cout << "INVALID OPERATION \"MOVE " << id << " ";
            for (int j = 0; j < 3; j++) { cout << komand[j]; }
            cout << " L\": PLACING SHIP TOO CLOSE TO OTHER SHIP"; clear(ROWS, arr);
            exit(1);
        }
        for (int i = 0; i < size; i++)
        {
            arr[y + i * c][x - 1 * c] = '+';
            if (owner == 'A') {
                playerA->arr[current_ship].head_x = x - 1 * c;
                playerA->arr[current_ship].head_y = y + i * c;
                parts_placing(owner, false, current_ship, -c, playerA->arr[current_ship].head_y, playerA->arr[current_ship].head_x, size, playerA, playerB);
                if (c == 1) { playerA->arr[current_ship].dimention = 'S'; }
                if (c == -1) { playerA->arr[current_ship].dimention = 'N'; }
            }
            if (owner == 'B') {
                playerB->arr[current_ship].head_x = x - 1 * c;
                playerB->arr[current_ship].head_y = y + i * c;
                parts_placing(owner, false, current_ship, -c, playerA->arr[current_ship].head_y, playerA->arr[current_ship].head_x, size, playerA, playerB);
                if (c == 1) { playerB->arr[current_ship].dimention = 'S'; }
                if (c == -1) { playerB->arr[current_ship].dimention = 'N'; }
            }
        }
        if (owner == 'A') { playerA->arr[current_ship].moves_counter++; }
        if (owner == 'B') { playerB->arr[current_ship].moves_counter++; }
    }
}

void move_R(bool xdim, int c, int size, int y, int x, int moves_count, bool eng_cond, int current_ship, int id, char komand[3], char owner, char** arr, int ROWS, int COLS, player* playerA, player* playerB) {
    if ((moves_count > 2) || ((moves_count > 1) && (size == 5))) {
        cout << "INVALID OPERATION \"MOVE " << id << " ";
        for (int i = 0; i < 3; i++) { cout << komand[i]; }
        cout << " R\": SHIP MOVED ALREADY"; clear(ROWS, arr);
        exit(1);
    }
    if (eng_cond == false) {
        cout << "INVALID OPERATION \"MOVE " << id << " ";
        for (int i = 0; i < 3; i++) { cout << komand[i]; }
        cout << " R\": SHIP CANNOT MOVE"; clear(ROWS, arr);
        exit(1);
    }
    if (xdim == false) {
        if ((x + (size - 1) * c < 0) || (x + (size - 1) * c > COLS - 1) || (y == 0) || (y == ROWS - 1) || ((x == 0) && (c == -1)) || ((x == COLS - 1) && (c == 1))) {
            cout << "INVALID OPERATION \"MOVE " << id << " ";
            for (int i = 0; i < 3; i++) { cout << komand[i]; }
            cout << " R\": SHIP WENT FROM BOARD"; clear(ROWS, arr);
            exit(1);
        }
        for (int k = 0; k < size; k++)
        {
            if (arr[y - 1 * c][x + k * c] == '#') {
                cout << "INVALID OPERATION \"MOVE " << id << " ";
                for (int i = 0; i < 3; i++) { cout << komand[i]; }
                cout << " R\": PLACING SHIP ON REEF"; clear(ROWS, arr);
                exit(1);
            }
        }
        for (int i = 0; i < size; i++) { arr[y + i * c][x] = ' '; }
        if (close_ship(y - 1 * c, x + (size - 1) * c, ROWS, COLS, size, c * -1, true, arr) == true) {
            for (int i = 0; i < size; i++) { arr[y + i * c][x] = '+'; }
            cout << "INVALID OPERATION \"MOVE " << id << " ";
            for (int j = 0; j < 3; j++) { cout << komand[j]; }
            cout << " R\": PLACING SHIP TOO CLOSE TO OTHER SHIP"; clear(ROWS, arr);
            exit(1);
        }
        for (int i = 0; i < size; i++)
        {
            arr[y - 1 * c][x + i * c] = '+';
            if (owner == 'A') {
                playerA->arr[current_ship].head_y = y - 1 * c;
                playerA->arr[current_ship].head_x = x + i * c;
                parts_placing(owner, true, current_ship, -c, playerA->arr[current_ship].head_y, playerA->arr[current_ship].head_x, size, playerA, playerB);
                if (c == 1) { playerA->arr[current_ship].dimention = 'E'; }
                if (c == -1) { playerA->arr[current_ship].dimention = 'W'; }
            }
            if (owner == 'B') {
                playerB->arr[current_ship].head_y = y - 1 * c;
                playerB->arr[current_ship].head_x = x + i * c;
                parts_placing(owner, true, current_ship, -c, playerA->arr[current_ship].head_y, playerA->arr[current_ship].head_x, size, playerA, playerB);
                if (c == 1) { playerB->arr[current_ship].dimention = 'E'; }
                if (c == -1) { playerB->arr[current_ship].dimention = 'W'; }
            }
        }
        if (owner == 'A') { playerA->arr[current_ship].moves_counter++; }
        if (owner == 'B') { playerB->arr[current_ship].moves_counter++; }
    }
    else {
        if ((y - (size - 1) * c < 0) || (y - (size - 1) * c > ROWS - 1) || (x == 0) || (x == COLS - 1) || ((y == 0) && (c == 1)) || ((y == ROWS - 1) && (c == -1))) {
            cout << "INVALID OPERATION \"MOVE " << id << " ";
            for (int i = 0; i < 3; i++) { cout << komand[i]; }
            cout << " R\": SHIP WENT FROM BOARD"; clear(ROWS, arr);
            exit(1);
        }
        for (int k = 0; k < size; k++)
        {
            if (arr[y - k * c][x - 1 * c] == '#') {
                cout << "INVALID OPERATION \"MOVE " << id << " ";
                for (int i = 0; i < 3; i++) { cout << komand[i]; }
                cout << " R\": PLACING SHIP ON REEF"; clear(ROWS, arr);
                exit(1);
            }
        }
        for (int i = 0; i < size; i++) { arr[y][x + i * c] = ' '; }
        if (close_ship(y - (size - 1) * c, x - 1 * c, ROWS, COLS, size, c, false, arr) == true) {
            for (int i = 0; i < size; i++) { arr[y][x + i * c] = '+'; }
            cout << "INVALID OPERATION \"MOVE " << id << " ";
            for (int j = 0; j < 3; j++) { cout << komand[j]; }
            cout << " R\": PLACING SHIP TOO CLOSE TO OTHER SHIP"; clear(ROWS, arr);
            exit(1);
        }
        for (int i = 0; i < size; i++)
        {
            arr[y - i * c][x - 1 * c] = '+';
            if (owner == 'A') {
                playerA->arr[current_ship].head_x = x - 1 * c;
                playerA->arr[current_ship].head_y = y - i * c;
                parts_placing(owner, false, current_ship, c, playerA->arr[current_ship].head_y, playerA->arr[current_ship].head_x, size, playerA, playerB);
                if (c == 1) { playerA->arr[current_ship].dimention = 'N'; }
                if (c == -1) { playerA->arr[current_ship].dimention = 'S'; }
            }
            if (owner == 'B') {
                playerB->arr[current_ship].head_x = x - 1 * c;
                playerB->arr[current_ship].head_y = y - i * c;
                parts_placing(owner, false, current_ship, c, playerA->arr[current_ship].head_y, playerA->arr[current_ship].head_x, size, playerA, playerB);
                if (c == 1) { playerB->arr[current_ship].dimention = 'N'; }
                if (c == -1) { playerB->arr[current_ship].dimention = 'S'; }
            }
        }
        if (owner == 'A') { playerA->arr[current_ship].moves_counter++; }
        if (owner == 'B') { playerB->arr[current_ship].moves_counter++; }
    }
}

void making_move(int id, char komand[3], char dimention, char owner, char** arr, int ROWS, int COLS, player* playerA, player* playerB) {
    int size, y, x, dim, current_ship, moves_count;
    bool eng_cond;

    if (strcmp(komand, "CAR") == 0) { size = 5; }
    if (strcmp(komand, "BAT") == 0) { size = 4; }
    if (strcmp(komand, "CRU") == 0) { size = 3; }
    if (strcmp(komand, "DES") == 0) { size = 2; }

    for (int i = 0; i < 40; i++) {
        if (owner == 'A') {
            if ((playerA->arr[i].id == id) && (playerA->arr[i].size == size)) {
                x = playerA->arr[i].head_x;
                y = playerA->arr[i].head_y;
                dim = playerA->arr[i].dimention;
                moves_count = playerA->arr[i].moves_counter;
                eng_cond = playerA->arr[i].engine.condition;
                current_ship = i;
                break;
            }
        }
        if (owner == 'B') {
            if ((playerB->arr[i].id == id) && (playerB->arr[i].size == size)) {
                x = playerB->arr[i].head_x;
                y = playerB->arr[i].head_y;
                dim = playerB->arr[i].dimention;
                moves_count = playerB->arr[i].moves_counter;
                eng_cond = playerB->arr[i].engine.condition;
                current_ship = i;
                break;
            }
        }
    }

    int c = 1;
    bool xdim = false;
    if (dim == 'S') { c = -1; }
    if (dim == 'E') { c = -1; xdim = true; }
    if (dim == 'W') { xdim = true; }

    if (dimention == 'F') {
        move_F(xdim, c, size, y, x, moves_count, eng_cond, current_ship, id, komand, owner, arr, ROWS, COLS, playerA, playerB);
    }
    if (dimention == 'L') {
        move_L(xdim, c, size, y, x, moves_count, eng_cond, current_ship, id, komand, owner, arr, ROWS, COLS, playerA, playerB);
    }
    if (dimention == 'R') {
        move_R(xdim, c, size, y, x, moves_count, eng_cond, current_ship, id, komand, owner, arr, ROWS, COLS, playerA, playerB);
    }
}

void ex_shooting(int id, char komand[3], int y, int x, char owner, char** arr, int rows, int cols, player* playerA, player* playerB) {
    double size, dist;
    bool cannon_condition;
    int cannon_y, cannon_x, shoots_amount, current_ship;

    if (strcmp(komand, "CAR") == 0) { size = 5; }
    if (strcmp(komand, "BAT") == 0) { size = 4; }
    if (strcmp(komand, "CRU") == 0) { size = 3; }
    if (strcmp(komand, "DES") == 0) { size = 2; }

    for (int i = 0; i < 40; i++)
    {
        if (owner == 'A') {
            if ((playerA->arr[i].id == id) && (playerA->arr[i].size == size)) {
                cannon_y = playerA->arr[i].cannon.y;
                cannon_x = playerA->arr[i].cannon.x;
                cannon_condition = playerA->arr[i].cannon.condition;
                shoots_amount = playerA->arr[i].shoots_counter;
                current_ship = i;
                break;
            }
        }
        if (owner == 'B') {
            if ((playerB->arr[i].id == id) && (playerB->arr[i].size == size)) {
                cannon_y = playerB->arr[i].cannon.y;
                cannon_x = playerB->arr[i].cannon.x;
                cannon_condition = playerB->arr[i].cannon.condition;
                shoots_amount = playerB->arr[i].shoots_counter;
                current_ship = i;
                break;
            }
        }
    }

    dist = sqrt(((cannon_y - y) * (cannon_y - y)) + ((cannon_x - x) * (cannon_x - x)));

    if ((dist > size) && (size != 5)) {
        cout << "INVALID OPERATION \"SHOOT " << id << " ";
        for (int i = 0; i < 3; i++) { cout << komand[i]; }
        cout << " " << y << " " << x << "\": SHOOTING TOO FAR"; clear(rows, arr);
        exit(1);
    }
    if (cannon_condition == false) {
        cout << "INVALID OPERATION \"SHOOT " << id << " ";
        for (int i = 0; i < 3; i++) { cout << komand[i]; }
        cout << " " << y << " " << x << "\": SHIP CANNOT SHOOT"; clear(rows, arr);
        exit(1);
    }
    if (shoots_amount >= size) {
        cout << "INVALID OPERATION \"SHOOT " << id << " ";
        for (int i = 0; i < 3; i++) { cout << komand[i]; }
        cout << " " << y << " " << x << "\": TOO MANY SHOOTS"; clear(rows, arr);
        exit(1);
    }
    shooting(y, x, arr, rows, cols, owner, current_ship, playerA, playerB);
}

char** radar_print(char** arr, char owner, int ROWS, int COLS, player* playerA, player* playerB) {
    bool put_in = false;
    char** radarr = (char**)malloc(ROWS * sizeof(char*));
    for (int i = 0; i < ROWS; i++) {
        radarr[i] = (char*)malloc(COLS * sizeof(char));
    }

    for (int i = 0; i < ROWS; i++)
    {
        for (int j = 0; j < COLS; j++)
        {
            put_in = false;
            if (owner == 'A') {
                for (int k = 0; k < 40; k++) {
                    if ((sqrt(((playerA->arr[k].head_y - i) * (playerA->arr[k].head_y - i)) + ((playerA->arr[k].head_x - j) * (playerA->arr[k].head_x - j))) <= playerA->arr[k].size) && (playerA->arr[k].size != 0))
                    {
                        radarr[i][j] = arr[i][j];
                        put_in = true;
                    }
                    if ((sqrt(((playerA->arr[k].head_y - i) * (playerA->arr[k].head_y - i)) + ((playerA->arr[k].head_x - j) * (playerA->arr[k].head_x - j))) <= 1) && (playerA->arr[k].size != 0))
                    {
                        radarr[i][j] = arr[i][j];
                        put_in = true;
                    }
                }
                for (int l = 0; l < 50; l++)
                {
                    if (((i >= playerA->spy_arr[l].y1) && (i <= playerA->spy_arr[l].y2) && (j >= playerA->spy_arr[l].x1) && (j <= playerA->spy_arr[l].x2)) && (playerA->spy_arr[l].x1 != playerA->spy_arr[l].x2))
                    {
                        radarr[i][j] = arr[i][j];
                        put_in = true;
                    }
                }
            }
            else if (owner == 'B') {
                for (int k = 0; k < 40; k++) {
                    if ((sqrt(((playerB->arr[k].head_y - i) * (playerB->arr[k].head_y - i)) + ((playerB->arr[k].head_x - j) * (playerB->arr[k].head_x - j))) <= playerB->arr[k].size) && (playerB->arr[k].size != 0))
                    {
                        radarr[i][j] = arr[i][j];
                        put_in = true;
                    }
                    if ((sqrt(((playerB->arr[k].head_y - i) * (playerB->arr[k].head_y - i)) + ((playerB->arr[k].head_x - j) * (playerB->arr[k].head_x - j))) <= 1) && (playerB->arr[k].size != 0))
                    {
                        radarr[i][j] = arr[i][j];
                        put_in = true;
                    }
                }
                for (int l = 0; l < 50; l++)
                {
                    if (((i >= playerB->spy_arr[l].y1) && (i <= playerB->spy_arr[l].y2) && (j >= playerB->spy_arr[l].x1) && (j <= playerB->spy_arr[l].x2)) && (playerB->spy_arr[l].x1 != playerB->spy_arr[l].x2))
                    {
                        radarr[i][j] = arr[i][j];
                        put_in = true;
                    }
                }
            }
            if (put_in == false) { radarr[i][j] = '?'; }
            cout << radarr[i][j];
        }
        cout << endl;
    }
    return radarr;
}

void spy_send(int id, int y, int x, char owner, player* playerA, player* playerB) {
    if (owner == 'A') {
        for (int i = 0; i < 50; i++) {
            if ((playerA->spy_arr[i].x1 == 0) && (playerA->spy_arr[i].x2 == 0)) {
                playerA->spy_arr[i].y1 = y - 1;
                playerA->spy_arr[i].y2 = y + 1;
                playerA->spy_arr[i].x1 = x - 1;
                playerA->spy_arr[i].x2 = x + 1;
                break;
            }
        }
        for (int k = 0; k < 40; k++)
        {
            if ((playerA->arr[k].id == id) && (playerA->arr[k].size == 5)) { playerA->arr[k].shoots_counter++; }
        }
    }

    if (owner == 'B') {
        for (int i = 0; i < 50; i++) {
            if ((playerB->spy_arr[i].x1 == 0) && (playerB->spy_arr[i].x2 == 0)) {
                playerB->spy_arr[i].y1 = y - 1;
                playerB->spy_arr[i].y2 = y + 1;
                playerB->spy_arr[i].x1 = x - 1;
                playerB->spy_arr[i].x2 = x + 1;
                break;
            }
        }
        for (int k = 0; k < 40; k++)
        {
            if ((playerB->arr[k].id == id) && (playerB->arr[k].size == 5)) { playerB->arr[k].shoots_counter++; }
        }
    }
}

void ship_cond(int y, int x, char dimention, int size, char** arr) {
    int c = 1;
    bool xdim = false;
    if (dimention == 'S') { c = -1; }
    if (dimention == 'E') { c = -1; xdim = true; }
    if (dimention == 'W') { xdim = true; }
    if (xdim == false) {
        for (int i = 0; i < size; i++)
        {
            if (arr[y + i * c][x] == 'x') { cout << 0; }
            else { cout << 1; }
        }
    }
    if (xdim == true) {
        for (int i = 0; i < size; i++)
        {
            if (arr[y][x + i * c] == 'x') { cout << 0; }
            else { cout << 1; }
        }
    }
}

void save(int ROWS, int COLS, char** arr, player* playerA, player* playerB) {
    cout << "[state]" << endl;
    cout << "BOARD_SIZE " << ROWS << " " << COLS << endl;
    cout << "NEXT_PLAYER ";
    { cout << "A" << endl; }
    cout << "INIT_POSITION A " << playerA->starting_position.y1 << " " << playerA->starting_position.x1 << " " << playerA->starting_position.y2 << " " << playerA->starting_position.x2 << endl;
    cout << "SET_FLEET A " << playerA->car_amount << " " << playerA->bat_amount << " " << playerA->cru_amount << " " << playerA->des_amount << endl;
    for (int i = 0; i < playerA->car_amount + playerA->bat_amount + playerA->cru_amount + playerA->des_amount; i++) {
        cout << "SHIP A " << playerA->arr[i].head_y << " " << playerA->arr[i].head_x << " " << playerA->arr[i].dimention << " " << playerA->arr[i].id << " ";
        switch (playerA->arr[i].size) {
        case 2:cout << "DES ";
            break;
        case 3:cout << "CRU ";
            break;
        case 4:cout << "BAT ";
            break;
        case 5:cout << "CAR ";
            break;
        }
        ship_cond(playerA->arr[i].head_y, playerA->arr[i].head_x, playerA->arr[i].dimention, playerA->arr[i].size, arr);
        cout << " " << endl;
    }
    cout << "INIT_POSITION B " << playerB->starting_position.y1 << " " << playerB->starting_position.x1 << " " << playerB->starting_position.y2 << " " << playerB->starting_position.x2 << endl;
    cout << "SET_FLEET B " << playerB->car_amount << " " << playerB->bat_amount << " " << playerB->cru_amount << " " << playerB->des_amount << endl;
    for (int i = 0; i < playerB->car_amount + playerB->bat_amount + playerB->cru_amount + playerB->des_amount; i++) {
        cout << "SHIP B " << playerB->arr[i].head_y << " " << playerB->arr[i].head_x << " " << playerB->arr[i].dimention << " " << playerB->arr[i].id << " ";
        switch (playerB->arr[i].size) {
        case 2:cout << "DES ";
            break;
        case 3:cout << "CRU ";
            break;
        case 4:cout << "BAT ";
            break;
        case 5:cout << "CAR ";
            break;
        }
        ship_cond(playerB->arr[i].head_y, playerB->arr[i].head_x, playerB->arr[i].dimention, playerB->arr[i].size, arr);
        cout << " " << endl;
    }
    cout << "[state]" << endl;
}

void prnt_1(int ROWS, int COLS, char** arr, player* playerA, player* playerB) {
    int i, j, indexR;
    if (COLS > 10) { indexR = 1; }
    else { indexR = 0; }
    ROWS += indexR + 1;
    COLS += 2;

    char** prarr = (char**)malloc(ROWS * sizeof(char*));
    for (i = 0; i < ROWS; i++) {
        prarr[i] = (char*)malloc(COLS * sizeof(char));
    }

    prarr[0][0] = ' ';
    prarr[0][1] = ' ';
    prarr[1][0] = ' ';
    prarr[1][1] = ' ';

    char tens = 48;
    int count = 0;
    int ones = 48;
    for (j = 2; j < COLS; j++)
    {
        if (count == 10)
        {
            ones = 48;
            tens++;
            count = 0;
        }
        if (indexR > 0) { prarr[0][j] = tens; }
        prarr[indexR][j] = ones;
        ones++;
        count++;
    }
    ones = 48;
    count = 0;
    tens = 48;
    for (j = indexR + 1; j < ROWS; j++)
    {
        if (count == 10)
        {
            tens++;
            ones = 48;
            count = 0;
        }
        prarr[j][0] = tens;
        count++;
        prarr[j][1] = ones;
        ones++;
    }

    int lines = 0, colons = 0;
    for (i = indexR + 1; i < ROWS; i++)
    {
        colons = 0;
        for (j = 2; j < COLS; j++)
        {
            prarr[i][j] = arr[lines][colons];
            for (int k = 0; k < 40; k++) {
                if ((lines == playerA->arr[k].head_y) && (colons == playerA->arr[k].head_x) && (arr[lines][colons] == '+'))
                {
                    prarr[i][j] = '@'; break;
                }
                if ((lines == playerA->arr[k].engine.y) && (colons == playerA->arr[k].engine.x) && (arr[lines][colons] == '+'))
                {
                    prarr[i][j] = '%'; break;
                }
                if ((lines == playerA->arr[k].cannon.y) && (colons == playerA->arr[k].cannon.x) && (arr[lines][colons] == '+'))
                {
                    prarr[i][j] = '!'; break;
                }
                if ((lines == playerB->arr[k].head_y) && (colons == playerB->arr[k].head_x) && (arr[lines][colons] == '+'))
                {
                    prarr[i][j] = '@'; break;
                }
                if ((lines == playerB->arr[k].engine.y) && (colons == playerB->arr[k].engine.x) && (arr[lines][colons] == '+'))
                {
                    prarr[i][j] = '%'; break;
                }
                if ((lines == playerB->arr[k].cannon.y) && (colons == playerB->arr[k].cannon.x) && (arr[lines][colons] == '+'))
                {
                    prarr[i][j] = '!'; break;
                }
            }
            colons++;
        }
        lines++;
    }

    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            cout << prarr[i][j];
        }
        cout << endl;
    }
    cout << "PARTS REMAINING:: A : " << playerA->ship_parts << " B : " << playerB->ship_parts << endl;
    clear(ROWS, prarr);
}


int main() {
    bool state_close = false, playerA_turn = true, playerB_turn = false, ex_ship, ex_shoot = false;
    const int STATE = 729, PLAYERA = 902, PLAYERB = 903, SET_FLEET = 699, NEXT_PLAYER = 875, PRINT0 = 445, PLACE_SHIP = 760, SHOOT = 397, SHIP = 308, INIT_POSITION = 1032, REEF = 290, BOARD_SIZE = 770, EXTENDED_SHIPS = 1079, PRINT1 = 446, MOVE = 311, SPY = 252, SAVE = 303;

    player* playerA = new player();
    player* playerB = new player();

    playerA->starting_position.y1 = 0;
    playerA->starting_position.x1 = 0;
    playerA->starting_position.y2 = 9;
    playerA->starting_position.x2 = 9;

    playerB->starting_position.y1 = 11;
    playerB->starting_position.x1 = 0;
    playerB->starting_position.y2 = 20;
    playerB->starting_position.x2 = 9;

    playerA->car_amount = playerB->car_amount = 1;
    playerA->bat_amount = playerB->bat_amount = 2;
    playerA->cru_amount = playerB->cru_amount = 3;
    playerA->des_amount = playerB->des_amount = 4;

    for (int k = 0; k < 40; k++) {
        playerA->arr[k].moves_counter = 0;
        playerB->arr[k].moves_counter = 0;
    }

    int ROWS = 21, COLS = 10, i = 0, id, komand = 0, condition = 1, x, y;
    char** arr = set_board_size(ROWS, COLS);
    char input, owner, dim, s, name[100] = { '\0' };;

    fleet('A', playerA->car_amount, playerA->bat_amount, playerA->cru_amount, playerA->des_amount, playerA, playerB);
    fleet('B', playerB->car_amount, playerB->bat_amount, playerB->cru_amount, playerB->des_amount, playerA, playerB);

    while (cin >> input)
    {
        komand += input;
        name[i] = input;
        i++;
        switch (komand)
        {
        case STATE:
            state_close = false;
            if (strcmp(name, "[state]") != 0)
            {
                break;
            }
            komand = 0;
            i = 0;
            ex_ship = true;
            memset(name, 0, sizeof name);
            while (state_close == false && cin >> input)
            {
                komand += input;
                name[i] = input;
                i++;
                switch (komand)
                {
                case STATE:
                    if (strcmp(name, "[state]") != 0)
                    {
                        break;
                    }
                    komand = 0;
                    memset(name, 0, sizeof name);
                    i = 0;
                    state_close = true;
                    break;
                case PRINT0:
                    if (strcmp(name, "PRINT0") != 0)
                    {
                        break;
                    }
                    basic_print(ROWS, COLS, arr, playerA, playerB);
                    komand = 0;
                    memset(name, 0, sizeof name);
                    i = 0;
                    break;
                case SET_FLEET:
                    if (strcmp(name, "SET_FLEET") != 0)
                    {
                        break;
                    }
                    cin >> owner;
                    if (owner == 'A') {
                        memset(playerA->arr, 0, sizeof(playerA->arr));
                        cin >> playerA->car_amount >> playerA->bat_amount >> playerA->cru_amount >> playerA->des_amount;
                        fleet(owner, playerA->car_amount, playerA->bat_amount, playerA->cru_amount, playerA->des_amount, playerA, playerB);
                    }
                    else if (owner == 'B') {
                        memset(playerB->arr, 0, sizeof(playerB->arr));
                        cin >> playerB->car_amount >> playerB->bat_amount >> playerB->cru_amount >> playerB->des_amount;
                        fleet(owner, playerB->car_amount, playerB->bat_amount, playerB->cru_amount, playerB->des_amount, playerA, playerB);
                    }
                    komand = 0;
                    memset(name, 0, sizeof name);
                    i = 0;
                    break;
                case NEXT_PLAYER:
                    if (strcmp(name, "NEXT_PLAYER") != 0)
                    {
                        break;
                    }
                    cin >> owner;
                    if (owner == 'A')
                    {
                        playerA_turn = true;
                        playerB_turn = false;
                    }
                    if (owner == 'B')
                    {
                        playerA_turn = false;
                        playerB_turn = true;
                    }
                    komand = 0;
                    memset(name, 0, sizeof name);
                    i = 0;
                    break;
                case BOARD_SIZE:
                    if (strcmp(name, "BOARD_SIZE") != 0)
                    {
                        break;
                    }
                    clear(ROWS, arr);
                    cin >> ROWS >> COLS;
                    arr = set_board_size(ROWS, COLS);
                    komand = 0;
                    memset(name, 0, sizeof name);
                    i = 0;
                    break;
                case INIT_POSITION:
                    if (strcmp(name, "INIT_POSITION") != 0)
                    {
                        break;
                    }
                    cin >> owner;
                    if (owner == 'A') {
                        cin >> playerA->starting_position.y1 >> playerA->starting_position.x1 >> playerA->starting_position.y2 >> playerA->starting_position.x2;
                    }
                    if (owner == 'B') {
                        cin >> playerB->starting_position.y1 >> playerB->starting_position.x1 >> playerB->starting_position.y2 >> playerB->starting_position.x2;
                    }
                    komand = 0;
                    memset(name, 0, sizeof name);
                    i = 0;
                    break;
                case REEF:
                    if (strcmp(name, "REEF") != 0)
                    {
                        break;
                    }
                    cin >> y >> x;
                    reef_placing(y, x, ROWS, COLS, arr);
                    komand = 0;
                    memset(name, 0, sizeof name);
                    i = 0;
                    break;
                case SHIP:
                    if (strcmp(name, "SHIP") != 0)
                    {
                        break;
                    }
                    memset(name, 0, sizeof name);
                    cin >> owner >> y >> x >> dim >> id;
                    for (i = 0; i < 3; i++) {
                        cin >> s;
                        name[i] = s;
                    }
                    cin >> condition;
                    placing_ship(owner, y, x, dim, id, name, condition, arr, ex_ship, ROWS, COLS, playerA, playerB);
                    komand = 0;
                    memset(name, 0, sizeof name);
                    i = 0;
                    break;
                case EXTENDED_SHIPS:
                    if (strcmp(name, "EXTENDED_SHIPS") != 0)
                    {
                        break;
                    }
                    ex_shoot = true;
                    komand = 0;
                    memset(name, 0, sizeof name);
                    i = 0;
                    break;
                case PRINT1:
                    if (strcmp(name, "PRINT1") != 0)
                    {
                        break;
                    }
                    prnt_1(ROWS, COLS, arr, playerA, playerB);
                    komand = 0;
                    memset(name, 0, sizeof name);
                    i = 0;
                    break;
                case SAVE:
                    if (strcmp(name, "SAVE") != 0)
                    {
                        break;
                    }
                    save(ROWS, COLS, arr, playerA, playerB);
                    komand = 0;
                    memset(name, 0, sizeof name);
                    i = 0;
                    break;
                }
            }
            break;

        case PLAYERA:
            if (strcmp(name, "[playerA]") != 0)
            {
                break;
            }
            komand = 0;
            i = 0;
            owner = 'A';
            ex_ship = false;
            memset(name, 0, sizeof name);
            for (int k = 0; k < 40; k++) {
                playerA->arr[k].moves_counter = 0;
                playerB->arr[k].shoots_counter = 0;
            }
            if (playerA_turn == false)
            {
                cout << "INVALID OPERATION \"[playerA] \": THE OTHER PLAYER EXPECTED";
            }
            while (playerA_turn == true && cin >> input)
            {
                komand += input;
                name[i] = input;
                i++;
                switch (komand)
                {
                case PLAYERA:
                    if (strcmp(name, "[playerA]") != 0)
                    {
                        break;
                    }
                    playerA_turn = false;
                    playerB_turn = true;
                    komand = 0;
                    memset(name, 0, sizeof name);
                    i = 0;
                    break;
                case PLACE_SHIP:
                    if (strcmp(name, "PLACE_SHIP") != 0)
                    {
                        break;
                    }
                    memset(name, 0, sizeof name);
                    cin >> y >> x >> dim >> id;
                    for (i = 0; i < 3; i++) {
                        cin >> s;
                        name[i] = s;
                    }
                    placing_ship(owner, y, x, dim, id, name, condition, arr, ex_ship, ROWS, COLS, playerA, playerB);
                    komand = 0;
                    memset(name, 0, sizeof name);
                    i = 0;
                    break;
                case SHOOT:
                    if (strcmp(name, "SHOOT") != 0)
                    {
                        break;
                    }
                    memset(name, 0, sizeof name);
                    if (ex_shoot == true) {
                        cin >> id;
                        for (i = 0; i < 3; i++) {
                            cin >> name[i];
                        }
                        cin >> y >> x;
                        ex_shooting(id, name, y, x, 'A', arr, ROWS, COLS, playerA, playerB);
                    }
                    if (ex_shoot == false) {
                        cin >> y >> x;
                        shooting(y, x, arr, ROWS, COLS, 'A', -1, playerA, playerB);
                    }
                    if (playerA->ship_parts == 0)
                    {
                        cout << "B won" << endl;
                        clear(ROWS, arr);
                    }
                    if (playerB->ship_parts == 0) {
                        cout << "A won" << endl;
                        clear(ROWS, arr);
                    }
                    komand = 0;
                    memset(name, 0, sizeof name);
                    i = 0;
                    break;
                case MOVE:
                    if (strcmp(name, "MOVE") != 0)
                    {
                        break;
                    }
                    memset(name, 0, sizeof name);
                    cin >> id;
                    for (i = 0; i < 3; i++) {
                        cin >> name[i];
                    }
                    cin >> dim;
                    making_move(id, name, dim, 'A', arr, ROWS, COLS, playerA, playerB);
                    komand = 0;
                    memset(name, 0, sizeof name);
                    i = 0;
                    break;
                case SPY:
                    if (strcmp(name, "SPY") != 0)
                    {
                        break;
                    }
                    cin >> id >> y >> x;
                    spy_send(id, y, x, 'A', playerA, playerB);
                    komand = 0;
                    memset(name, 0, sizeof name);
                    i = 0;
                    break;
                case PRINT0:
                    if (strcmp(name, "PRINT0") != 0)
                    {
                        break;
                    }
                    clear(ROWS, radar_print(arr, 'A', ROWS, COLS, playerA, playerB));
                    komand = 0;
                    memset(name, 0, sizeof name);
                    i = 0;
                    break;
                case PRINT1:
                    if (strcmp(name, "PRINT1") != 0)
                    {
                        break;
                    }
                    prnt_1(ROWS, COLS, radar_print(arr, owner, ROWS, COLS, playerA, playerA), playerA, playerB);
                    komand = 0;
                    memset(name, 0, sizeof name);
                    i = 0;
                    break;
                }
            }
            break;

        case PLAYERB:
            if (strcmp(name, "[playerB]") != 0)
            {
                break;
            }
            for (int k = 0; k < 40; k++) {
                playerB->arr[k].moves_counter = 0;
                playerB->arr[k].shoots_counter = 0;
            }
            komand = 0;
            i = 0;
            owner = 'B';
            ex_ship = false;
            memset(name, 0, sizeof name);
            if (playerB_turn == false)
            {
                cout << "INVALID OPERATION \"[playerB] \": THE OTHER PLAYER EXPECTED";
            }
            while (playerB_turn == true && cin >> input)
            {
                komand += input;
                name[i] = input;
                i++;
                switch (komand)
                {
                case PLAYERB:
                    if (strcmp(name, "[playerB]") != 0)
                    {
                        break;
                    }
                    playerB_turn = false;
                    playerA_turn = true;
                    komand = 0;
                    memset(name, 0, sizeof name);
                    i = 0;
                    break;
                case PLACE_SHIP:
                    if (strcmp(name, "PLACE_SHIP") != 0)
                    {
                        break;
                    }
                    memset(name, 0, sizeof name);
                    cin >> y >> x >> dim >> id;
                    for (i = 0; i < 3; i++) {
                        cin >> s;
                        name[i] = s;
                    }
                    placing_ship(owner, y, x, dim, id, name, condition, arr, ex_ship, ROWS, COLS, playerA, playerB);
                    komand = 0;
                    memset(name, 0, sizeof name);
                    i = 0;
                    break;
                case SHOOT:
                    if (strcmp(name, "SHOOT") != 0)
                    {
                        break;
                    }
                    memset(name, 0, sizeof name);
                    if (ex_shoot == true) {
                        cin >> id;
                        for (i = 0; i < 3; i++) {
                            cin >> name[i];
                        }
                        cin >> y >> x;
                        ex_shooting(id, name, y, x, 'B', arr, ROWS, COLS, playerA, playerB);
                    }
                    if (ex_shoot == false) {
                        x, y;
                        cin >> y >> x;
                        shooting(y, x, arr, ROWS, COLS, 'B', -1, playerA, playerB);
                    }
                    if (playerA->ship_parts == 0) { cout << "B won" << endl; exit(1); }
                    if (playerB->ship_parts == 0) { cout << "A won" << endl; exit(1); }
                    komand = 0;
                    memset(name, 0, sizeof name);
                    i = 0;
                    break;
                case MOVE:
                    if (strcmp(name, "MOVE") != 0)
                    {
                        break;
                    }
                    memset(name, 0, sizeof name);
                    cin >> id;
                    for (i = 0; i < 3; i++) {
                        cin >> name[i];
                    }
                    cin >> dim;
                    making_move(id, name, dim, 'B', arr, ROWS, COLS, playerA, playerB);
                    komand = 0;
                    memset(name, 0, sizeof name);
                    i = 0;
                    break;
                case SPY:
                    if (strcmp(name, "SPY") != 0)
                    {
                        break;
                    }
                    cin >> id >> y >> x;
                    spy_send(id, y, x, 'B', playerA, playerB);
                    komand = 0;
                    memset(name, 0, sizeof name);
                    i = 0;
                    break;
                case PRINT0:
                    if (strcmp(name, "PRINT0") != 0)
                    {
                        break;
                    }
                    clear(ROWS, radar_print(arr, 'B', ROWS, COLS, playerA, playerB));
                    komand = 0;
                    memset(name, 0, sizeof name);
                    i = 0;
                    break;
                case PRINT1:
                    if (strcmp(name, "PRINT1") != 0)
                    {
                        break;
                    }
                    prnt_1(ROWS, COLS, radar_print(arr, owner, ROWS, COLS, playerA, playerA), playerA, playerB);
                    komand = 0;
                    memset(name, 0, sizeof name);
                    i = 0;
                    break;
                }
            }
            break;
        }
    }
    clear(ROWS, arr);
    return 0;