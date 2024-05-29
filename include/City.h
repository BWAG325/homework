//
// Created by Wang on 2024/5/28.
//
#ifndef BIG_HOMEWORK_CITY_H
#define BIG_HOMEWORK_CITY_H

#include <iostream>
#include <iomanip>
#include <cstring>

class City {
private:
    int number;
    char name[20] = {0};
    int x, y;

    friend class Map;

public:
    explicit City(int n = 0, char *p = nullptr, int x = 0, int y = 0) : number(n), x(x), y(y) { setName(p); };

    City(City &c) { //拷贝构造函数
        number = c.number;
        setName(c.name);
        x = c.x, y = c.y;
    }

    void setNumber(int num) {
        number = num;
    }

    void setName(char *na) {
        if (na == nullptr) return;
        int i = 0;
        while (*na != '\0')
            name[i++] = *na++;
    }

    void setPosition(int xPos, int yPos) {
        x = xPos, y = yPos;
    }

    auto getName()-> char * {
        char *ptr=name;
        return ptr;
    }

    int getNum() const {
        return number;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    void show() {
        std::cout << "[City Number]" << number << std::setw(15)
                  << "[City Name]:" << std::setw(10) << std::left << name << std::right
                  << "[City Position]:" << "(" << x << "," << y << ")" << std::endl;
    }
};

#endif //BIG_HOMEWORK_CITY_H
