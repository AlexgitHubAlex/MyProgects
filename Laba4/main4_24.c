#include <stdio.h>

struct XY{
    float x;
    float y;                        
};

struct AABB{
    struct XY center;               //координаты центра листа
    struct XY halfDimension;        //середина ветки
};

struct QuadTree{
#define QT_NODE_CAPACITY 4       //кол-во информации которую можно хранить в одном узле
    struct AABB boundary;           //ограниченный параллелепипед выровненный по коорд.
    struct XY points[QT_NODE_CAPACITY];
    char* string[QT_NODE_CAPACITY];
    //Потомки
    struct QuadTree* northWest; //0
    struct QuadTree* northEast; //1
    struct QuadTree* southWest; //2
    struct QuadTree* southEast; //3 
};

void set_XY(struct XY* obj,int set_x,int set_y){
    obj->x = set_x;
    obj->y = set_y;
}

void set_AABB(struct AABB* obj,int set_cen_x,int set_cen_y,int set_half_x,int set_half_y){
    set_XY(&obj->center,        set_cen_x,  set_cen_y );
    set_XY(&obj->halfDimension, set_half_x, set_half_y);
}

int main(){

return 0;
} 

