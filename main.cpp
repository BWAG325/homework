#include "include/Map.h"
#include "include/Plane.h"

const char *filename{"../DataBase/database.txt"}; //根据工作目录选择相对路径  可以直接绝对路径

void appendCity(Map &mapObj) {
    int num, x, y;
    char name[20];
    std::cout << "[Input City]:(number,name,x,y)" << std::endl;
    std::cin >> num >> name >> x >> y;
    mapObj.AddCity(num, name, x, y);
}

void delCity(Map &mapObj) {
    int num;
    std::cout << "[City Number]:(number)" << std::endl;
    std::cin >> num;
    mapObj.DeleteCity(num);
}

void updCity(Map &mapObj) {
    int num, x, y, i;
    char name[20] = {};
    std::cout << "[Input City]:(i,number,name,x,y)" << std::endl;
    std::cin >> i >> num >> name >> x >> y;
    mapObj.UpdateCity(i, num, name, x, y);
}

void saveToFile(Map &mapObj) {
    std::cout << "[Start Saving]" << std::endl;
    mapObj.SaveCity(filename);
    std::cout << "[Finish]" << std::endl;
}

void readFromFile(Map &mapObj) {
    mapObj.ImportDataBase(filename);
    std::cout << "[Over]" << std::endl;
}

void showAllCities(Map &mapObj) {
    mapObj.ShowCities();
}

void addPlane(Plane &planeObj) {
    int num, x, y;
    char name[20] = {0};
    double weight;
    std::cout << "[Add Plane]:(number,name,weight,x,y)" << std::endl;
    std::cin >> num >> name >> weight >> x >> y;
    planeObj.SetPlane(num, name, weight, x, y);
}

void showPlane(Plane &planeObj) {
    planeObj.show();
}

void brake(Plane &planeObj) {
    double sp, reDistance;
    int result;
    std::cout << "[Check]:(speed,reDistance)" << std::endl;
    std::cin >> sp >> reDistance;
    result = planeObj.CanBrake(sp, reDistance);
    switch (result) {
        case 1: std::cout << "Yes" << std::endl; break;
        case 0: std::cout << "No" << std::endl; break;
        case -1: std::cout << "Error" << std::endl; break;
        default: break;
    }
}

void radarSearch(Plane &planeObj, Map &mapObj) {
    double dis;
    std::cout << "[Distance]:(distance)" << std::endl;
    std::cin >> dis;
    planeObj.RadarFind(dis, mapObj);
}

char quit() {
    char c;
    std::cout << "[WARNING]:Are you sure to quit (y/n)" << std::endl;
    std::cin >> c;
    return c;
}

int menu() {
    int command;
    system("cls");
    std::cout << "--------------[Menu]--------------" << std::endl;
    std::cout << "[1]appendCity     [2]delCity" << std::endl;
    std::cout << "[3]updateCity     [4]saveToFile" << std::endl;
    std::cout << "[5]readFromFile   [6]showAllCities" << std::endl;
    std::cout << "[7]addPlane       [8]showPlane" << std::endl;
    std::cout << "[9]brake          [10]radarSearch" << std::endl;
    std::cout << "[0]Quit" << std::endl;
    std::cout << "(you choose one each time)" << std::endl;
    std::cout << "----------------------------------" << std::endl;
    std::cin >> command;
    return command;
}

int main() {
    Map mapObj;            //定义地图对象
    Plane planeObj;        //定义飞机对象
    int sel;
    mapObj.ImportDataBase(filename);
    while (true) {
        switch (sel = menu()) {
            case 1:    //追加城市记录
                appendCity(mapObj); break;
            case 2:    //删除城市记录
                delCity(mapObj); break;
            case 3:    //修改城市记录
                updCity(mapObj); break;
            case 4:    //保存城市信息，写入磁盘文件
                saveToFile(mapObj); break;
            case 5:    //从磁盘文件读取城市信息
                readFromFile(mapObj); break;
            case 6:    //显示全部城市信息
                showAllCities(mapObj); break;
            case 7:    //输入飞机信息
                addPlane(planeObj); break;
            case 8:     //显示飞机信息
                showPlane(planeObj); break;
            case 9:     //判断起飞时是否可以刹车
                brake(planeObj); break;
            case 10:    //显示距当前飞机在雷达扫描半径内所有的城市信息
                radarSearch(planeObj, mapObj); break;
            case 0:    //退出处理
                if (quit() != 'y') continue;
                else {
                    saveToFile(mapObj); break;
                }

            default:
                continue;
        }
        system("pause");
        if (sel == 0)break;
    }
    std::cout << "[INFO]:over" << std::endl;

    return 0;
}