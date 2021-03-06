#pragma once
#include <cstring>
#include <iostream>
#include <string>
using namespace std;
#ifndef LEXICAL_H_INCLUDED
#define LEXICAL_H_INCLUDED
class LEXICAL {
   public:
    void cifafenxi();
    void scaner1();
    char prog1[80], token1[8], ch1;
    int syn1, p1, m1, n1, sum1;
    char *rwtab1[6] = {"begin", "if", "then", "while", "do", "end"};
};

void LEXICAL::cifafenxi() {
    p1 = 0;
    cout << "\t\t【词法分析】" << endl;
    cout << "\t\t请选择输入源程序的方式：\n\t\t(0) "
            "程序框输入：直接输入源代码。\n\t\t(1) "
            "文件输入：将源程序保存在[source_code.txt]文件中。\n\t\t(others) "
            "Exit."
         << endl;
    cout << "\t\t[warning]请确保以'#'结束！" << endl;
    int option = 1;
    cin >> option;
    switch (option) {
        case 0: {
            cout << "请输入：" << endl;
            do {
                scanf("%c", &ch1);
                prog1[p1++] = ch1;
            } while (ch1 != '#');
            break;
        }
        case 1: {
            ifstream fin("source_code.txt");
            string str, sumstr;
            while (fin >> str) {
                sumstr += str;
                if (str[str.length() - 1] == '#') break;
            }
            for (int i = 0; i < sumstr.length(); i++) {
                prog1[p1++] = sumstr[i];
            }
            break;
        }
        default: {
            cout << "\t\t[info]:程序已终止！" << endl;
            exit(0);
        }
    }
    p1 = 0;
    do {
        scaner1();
        switch (syn1) {
            case 11:
                printf("( %-10d%5d )\n", sum1, syn1);
                break;
            case -1:
                printf("you have input a wrong string\n");
                exit(0);
            default:
                printf("( %-10s%5d )\n", token1, syn1);
                break;
        }
    } while (syn1 != 0);
}
void LEXICAL::scaner1() {
    sum1 = 0;
    for (m1 = 0; m1 < 8; m1++) token1[m1++] = NULL;
    ch1 = prog1[p1++];
    m1  = 0;
    while ((ch1 == ' ') || (ch1 == '\n')) ch1 = prog1[p1++];
    if (((ch1 <= 'z') && (ch1 >= 'a')) || ((ch1 <= 'Z') && (ch1 >= 'A'))) {
        while (((ch1 <= 'z') && (ch1 >= 'a')) ||
               ((ch1 <= 'Z') && (ch1 >= 'A')) ||
               ((ch1 >= '0') && (ch1 <= '9'))) {
            token1[m1++] = ch1;
            ch1          = prog1[p1++];
        }
        p1--;
        syn1 = 10;
        for (n1 = 0; n1 < 6; n1++)
            if (strcmp(token1, rwtab1[n1]) == 0) {
                syn1 = n1 + 1;
                break;
            }
    } else if ((ch1 >= '0') && (ch1 <= '9')) {
        while ((ch1 >= '0') && (ch1 <= '9')) {
            sum1 = sum1 * 10 + ch1 - '0';
            ch1  = prog1[p1++];
        }
        p1--;
        syn1 = 11;
    } else
        switch (ch1) {
            case '<':
                token1[m1++] = ch1;
                ch1          = prog1[p1++];
                if (ch1 == '=') {
                    syn1         = 22;
                    token1[m1++] = ch1;
                } else {
                    syn1 = 20;
                    p1--;
                }
                break;
            case '>':
                token1[m1++] = ch1;
                ch1          = prog1[p1++];
                if (ch1 == '=') {
                    syn1         = 24;
                    token1[m1++] = ch1;
                } else {
                    syn1 = 23;
                    p1--;
                }
                break;
            case '+':
                token1[m1++] = ch1;
                ch1          = prog1[p1++];
                if (ch1 == '+') {
                    syn1         = 17;
                    token1[m1++] = ch1;
                } else {
                    syn1 = 13;
                    p1--;
                }
                break;
            case '-':
                token1[m1++] = ch1;
                ch1          = prog1[p1++];
                if (ch1 == '-') {
                    syn1         = 29;
                    token1[m1++] = ch1;
                } else {
                    syn1 = 14;
                    p1--;
                }
                break;
            case '!':
                ch1 = prog1[p1++];
                if (ch1 == '=') {
                    syn1         = 21;
                    token1[m1++] = ch1;
                } else {
                    syn1 = 31;
                    p1--;
                }
                break;
            case '=':
                token1[m1++] = ch1;
                ch1          = prog1[p1++];
                if (ch1 == '=') {
                    syn1         = 25;
                    token1[m1++] = ch1;
                } else {
                    syn1 = 18;
                    p1--;
                }
                break;
            case '*':
                syn1         = 15;
                token1[m1++] = ch1;
                break;
            case '/':
                syn1         = 16;
                token1[m1++] = ch1;
                break;
            case '(':
                syn1         = 27;
                token1[m1++] = ch1;
                break;
            case ')':
                syn1         = 28;
                token1[m1++] = ch1;
                break;
            case '{':
                syn1         = 5;
                token1[m1++] = ch1;
                break;
            case '}':
                syn1         = 6;
                token1[m1++] = ch1;
                break;
            case ';':
                syn1         = 26;
                token1[m1++] = ch1;
                break;
            case '\"':
                syn1         = 30;
                token1[m1++] = ch1;
                break;
            case '#':
                syn1         = 0;
                token1[m1++] = ch1;
                break;
            case ':':
                syn1         = 17;
                token1[m1++] = ch1;
                break;
            default:
                syn1 = -1;
                break;
        }
    token1[m1++] = '\0';
}

#endif // LEXICAL_H_INCLUDED
