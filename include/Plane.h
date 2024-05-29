//
// Created by Wang on 2024/5/28.
//

#ifndef BIG_HOMEWORK_PLAN_H
#define BIG_HOMEWORK_PLAN_H

#include <cstring>
#include "Map.h"

class Plane {
private:
    int number;
    char name[20] = {}; //进行一下初始化
    double weight;
    int x, y;
    Map m;
public:
    explicit Plane(int num = 0, char *na = nullptr, double wei = 0.0, int x = 0, int y = 0.0) :
            number(num), weight(wei), x(x), y(y) { if (na) std::strcpy(name, na); };

    void SetPlane(int num, char *na, double w, int xPos, int yPos) {
        number = num;
        std::strcpy(name, na);
        weight = w;
        x = xPos, y = yPos;
    }

    void show() {
        if (!*name) { //如果 name第一位是空的 说明没有值 返回 NULL
            std::cout << "NULL" << std::endl;
            return;
        }
        std::cout << "[Plane Number]" << number << std::setw(20)
                  << "[Plane Name]:" << std::setw(10) << std::left << name << std::right
                  << "[Plane Position]:" << "(" << x << "," << y << ")" << std::endl;
    }

    int CanBrake(double sp, double reDistance) const {
        if (number == 0) return -1;
        else {
            if (weight * sp < reDistance)
                return 1;
            else
                return 0;
        }
    }

    void RadarFind(double radarRadius, Map mapObj) {
        m.DeleteAllCity();
        mapObj.findDistanceCity(x, y, radarRadius,m);
        m.ShowCities();
    }
};

#endif //BIG_HOMEWORK_PLAN_H
