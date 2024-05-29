//
// Created by Wang on 2024/5/28.
//

#ifndef BIG_HOMEWORK_MAP_H
#define BIG_HOMEWORK_MAP_H

#include "City.h"
#include <fstream>
#include <cmath>
#include <cstdlib>

class Map {
private:
    City *ctr;
    int curCounter = 0;
    int maxCounter;

    void mkdir(City *ptr = nullptr) { //���� maxCounter�����ռ� ���� ptr��ֵ���ƽ�ȥ
        City *c = new City[maxCounter];
        if (ptr != nullptr) // ������ǿ�ָ�룬����һ��
            for (int i = 0; i < curCounter; ++i)
                *(c + i) = *ptr++;
        delete[] ctr; //�ͷ�ԭ�е��ڴ�ռ�
        ctr = c; //ָ���µĵ�ַ
    }

    double Distance(int x1, int y1, int x2, int y2) {
        return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
    }

    void ReadCity(std::ifstream &file) {
        int num, x, y;
        char name[20];
        while (file >> num >> name >> x >> y)
            AddCity(num, name, x, y);
    }

public:
    explicit Map(int max = 1) : ctr(nullptr), maxCounter(max) { mkdir(); };

    void ImportDataBase(const char *filename) {
        std::ifstream txt(filename);
        if (txt.is_open()) {
            ReadCity(txt);
            txt.close();
        }
    }

    Map(Map &m) {
        curCounter = m.curCounter;
        maxCounter = m.maxCounter;
        ctr = nullptr;
        mkdir(m.ctr);
    }

    ~Map() { //�ͷ��ڴ�
        delete[] ctr;
    }

    void findDistanceCity(int x, int y, double dis, Map &map) { //ע��ʹ������  ���ڴ��� Map ���͵�ֵ���д���
        for (int i = 0; i < curCounter; ++i) {
            if (Distance(x, y, (ctr + i)->getX(), (ctr + i)->getY()) <= dis) {
                map.AddCity((ctr + i)->getNum(), (ctr + i)->getName(), (ctr + i)->getX(), (ctr + i)->getY());
            }
        }
    }

    void AddCity(int num, char *na, int x, int y) {
        if (curCounter >= maxCounter) { //�ж���Ŀ �����Ժ󷭱�
            maxCounter *= 2;
            mkdir(ctr);
        }
        ++curCounter;
        (ctr + curCounter - 1)->setNumber(num);
        (ctr + curCounter - 1)->setName(na);
        (ctr + curCounter - 1)->setPosition(x, y);
    }

    void DeleteCity(int num) {
        int move = 0;
        for (int i = 0; i < curCounter; ++i) {
            if (ctr->getNum() == num) {
                move = 1;
            }
            if (move)
                *(ctr) = *(ctr + 1); //���һλ������û�н��и��� ��������û��
            ++ctr;
        }
        --curCounter;
    }

    void DeleteAllCity() { //ֻҪ��Ϊû�У�����ȫ��ɾ�ˣ�û��Ҫ����
        curCounter = 0;
    }

    void SaveCity(const char *filename) {
        std::ofstream txt(filename);
        for (int i = 0; i < curCounter; ++i) {
            txt << (ctr + i)->getNum() << " " << (ctr + i)->getName() << " " << (ctr + i)->getX() << " "
                << (ctr + i)->getY() << std::endl;
        }
        txt.close();
    }

    void UpdateCity(int i, int num, char *na, int x, int y) {
        (ctr + i)->setNumber(num);
        (ctr + i)->setName(na);
        (ctr + i)->setPosition(x, y);
    }

    void ShowCities() {
        if (!curCounter) std::cout << "NULL" << std::endl; //���û����� NULL
        for (int i = 0; i < curCounter; ++i)
            (ctr + i)->show();
    }

    int FindCity(int num) {
        for (int i = 0; i < curCounter; ++i) {
            if ((ctr + i)->getNum() == num) {
                return i;
            }
        }
        return -1;
    }

    int GetCurCounter() {
        return curCounter;
    }

    int GetPositionX(int i) {
        return (ctr + i)->getX();
    }

    int GetPositionY(int i) {
        return (ctr + i)->getY();
    }

    void ShowCity(int i) {
        (ctr + i)->show();
    }
};

#endif //BIG_HOMEWORK_MAP_H
