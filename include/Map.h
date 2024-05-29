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

    void mkdir(City *ptr = nullptr) { //根据 maxCounter创建空间 并将 ptr的值复制进去
        City *c = new City[maxCounter];
        if (ptr != nullptr) // 如果不是空指针，复制一下
            for (int i = 0; i < curCounter; ++i)
                *(c + i) = *ptr++;
        delete[] ctr; //释放原有的内存空间
        ctr = c; //指向新的地址
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

    ~Map() { //释放内存
        delete[] ctr;
    }

    void findDistanceCity(int x, int y, double dis, Map &map) { //注意使用引用  便于传回 Map 类型的值进行处理
        for (int i = 0; i < curCounter; ++i) {
            if (Distance(x, y, (ctr + i)->getX(), (ctr + i)->getY()) <= dis) {
                map.AddCity((ctr + i)->getNum(), (ctr + i)->getName(), (ctr + i)->getX(), (ctr + i)->getY());
            }
        }
    }

    void AddCity(int num, char *na, int x, int y) {
        if (curCounter >= maxCounter) { //判定数目 超了以后翻倍
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
                *(ctr) = *(ctr + 1); //最后一位的数据没有进行覆盖 不读就算没了
            ++ctr;
        }
        --curCounter;
    }

    void DeleteAllCity() { //只要认为没有，就是全都删了，没必要覆盖
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
        if (!curCounter) std::cout << "NULL" << std::endl; //如果没有输出 NULL
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
