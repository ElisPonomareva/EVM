#include <ctime>
#include <cstdlib>
#include <iostream>

#include "functions.h"
#include "constants.h"

using namespace std;

int Random(int chance) {
    int min = 0, max = 100;
    int current = rand() % 100;
    if (current <= chance) {
        return 1;
    }
    return 2;
}

int getChangePercent(double chance) {
    return int(chance * 100);
}

void input() {
    cout << "������� ���-�� ������:" << endl;
    cin >> commandsCount;
    cout << "������� ����������� ����������� ���������� [0.9, 0.8, 0.6]:" << endl;
    cin >> registerChange;
    cout << "������� ����� ��������� � ������ [2, 5, 10]:" << endl;
    cin >> memAccess;
    cout << "������� ����������� ������� ������� ���� [0.9, 0.7, 0.5]:" << endl;
    cin >> typeChance;
    cout << "������� ����� ���������� ������ ������� ���� [4, 8, 16]:" << endl;
    cin >> typeAccess;

}
