
#include <stdio.h>
#include <string.h>#include <string.h>#include <string.h>
struct XY{
    int x;
    int y;                        
};

struct AABB{
    struct XY center;               //координаты центра листа
    struct XY halfDimension;        //середина ветки
};

struct Point{
    struct XY key;
    char *str;
};
struct QuadTree{
#define QT_NODE_CAPACITY 4          //кол-во информации которую можно хранить в одном узле
    struct AABB boundary;           //ограниченный параллелепипед выровненный по коорд.
    struct Point *points[QT_NODE_CAPACITY];
    int busy;
    //Потомки
    struct QuadTree* northWest;     //0
    struct QuadTree* northEast;     //1
    struct QuadTree* southWest;     //2
    struct QuadTree* southEast;     //3 
};
//Функции:
void set_XY(struct XY* obj,int set_x,int set_y);
void set_AABB(struct AABB* obj,
            int set_cen_x,int set_cen_y,
            int set_half_x,int set_half_y);

void set_Point(struct Point *obj,int x,int y,char *str);
struct Point* new_Point(int x,int y,char *str);
void delete_Point(struct Point* obj);
struct QuadTree* new_QuadTree(int z_x,int z_y,int s_x,int s_y);
int XY_sravnenie(struct XY* a,struct XY* b); //>
int Point_sravnenie(struct Point *a,struct Point *b);
int add_Point(struct QuadTree* obj,struct Point* point);
int insert_point(struct QuadTree **obj,struct Point *point,
                int z_x,int z_y, int s_x,int s_y);
int print_Point(struct Point* point,char* fon);
int print_QuadTree(struct QuadTree *obj,char *);
int find
//Глобальные переменные
struct QuadTree *tree;


//////////kkk

char* mes[] = { "1. Просмотр дерево",
                "2. Добавить элемент",
    //            "3. Найти элемент",
      //          "4. Удалить элемент",
                "3. Выход",
                };

int mesLen = sizeof(mes)/ sizeof(mes[0]);
int getInt(int *data)
{
    int f=1;
    do{
        if (f==0) scanf("%*c");
        f=scanf("%d",data);
        if (f==-1)return 0;
    }while (!f);
    return 1;
}
int dialog (char *msgs[], int N)
{
    char *errmsg= ""; 
    int rc;
    int i,n;
    do{
        puts(errmsg);
        errmsg= "You are wrong. Repeate, please!";      // вывод списка альтернатив
        printf("------------------------------------------------------------------------------------------\n");
        for(i= 0; i< N; ++i){
            puts(msgs[i]);
        }

        printf("------------------------------------------------------------------------------------------\n");
        puts("--> ");
        n = getInt(&rc);                                // ввод No альтернативы
        if(n == 0)                                      // конец файла – конец работы
            rc= 0;

    system("clear");
    } while(rc< 0 || rc>= N+1);
    return rc%N;
}

//////////kkk


void set_XY(struct XY* obj,int set_x,int set_y){
    obj->x = set_x;
    obj->y = set_y;
}

void set_AABB(struct AABB* obj,
              int set_cen_x,int set_cen_y,
              int set_half_x,int set_half_y){
    set_XY(&obj->center,        set_cen_x,  set_cen_y );
    set_XY(&obj->halfDimension, set_half_x, set_half_y);
}

void set_Point(struct Point *obj,int x,int y,char *str){
    obj->key.x = x;
    obj->key.y = y;
    /* set_XY(&obj->key,x,y); */
    obj->str = str;
}

struct Point* new_Point(int x,int y,char *str){
    struct Point *newElem;
    newElem  = malloc(sizeof(struct Point));
    set_Point(newElem,x,y,str);
    return newElem;
}

void delete_Point(struct Point* obj){
    free (obj->str);
    free (obj);
}

struct QuadTree* new_QuadTree(int z_x,int z_y,int s_x,int s_y){
    int i;
    struct QuadTree *newObj;
    newObj = malloc(sizeof(struct QuadTree));
    set_AABB(&newObj->boundary,z_x,z_y,s_x,s_y);
    for (i=0;i<QT_NODE_CAPACITY;i++){
        newObj->points[i] = NULL;
    }
    newObj->busy = 0;
    newObj->northEast = NULL;
    newObj->northWest = NULL;
    newObj->southEast = NULL;
    newObj->southWest = NULL;
    return newObj;
}
int XY_sravnenie(struct XY* a,struct XY* b){ //>
    if(a->x>b->x) return 0;
    if(a->x<b->x) return 1;
    if(a->y>b->y) return 0;
    if(a->y<b->y) return 1;
    return -1; //error
}

int Point_sravnenie(struct Point *a,struct Point *b){
    return XY_sravnenie(&a->key,&b->key);
}
int in_quad(int x,int y,int _x1, int _y1,int _x2,int _y2 ){
    return ((x >= _x1) && (x<= _x2)&& 
    (y >= _y1) && (y <= _y2));
}
int find_list_num(struct Point *point,struct QuadTree *obj){
int i = 0; 
        if (point->key.x  >  obj->boundary.center.x){i+=2;}

        if (point->key.y  >  obj->boundary.center.y){i+=1;}
     
/*
        if (in_quad(point->key.x,point->key.y,
                    obj->boundary.center.x-obj->boundary.halfDimension.x,
                    obj->boundary.center.x,
                    obj->boundary.center.y-obj->boundary.halfDimension.y,
                    obj->boundary.center.y)
                )return 0;


        if (in_quad(point->key.x,point->key.y,
                    obj->boundary.center.x-obj->boundary.halfDimension.x,
                    obj->boundary.center.x,
                    obj->boundary.center.y,
                    obj->boundary.center.y+obj->boundary.halfDimension.y
                    )
                )return 1;

        if (in_quad(point->key.x,point->key.y,
                    obj->boundary.center.x,
                    obj->boundary.center.x+obj->boundary.halfDimension.x,
                    obj->boundary.center.y-obj->boundary.halfDimension.y,
                    obj->boundary.center.y)
                )return 2;
        if (in_quad(point->key.x,point->key.y,
                    obj->boundary.center.x,
                    obj->boundary.center.x+obj->boundary.halfDimension.x,
                    obj->boundary.center.y,
                    obj->boundary.center.y+obj->boundary.halfDimension.y)
                )return 3;
  */     

        return i;
}

int add_Point(struct QuadTree* obj,struct Point* point){
    struct Point *tmp = NULL,*next = point;
    int i,sost,p;
    struct XY    *center = &obj->boundary.center,
          *halfDimension = &obj->boundary.halfDimension;
   //проверка на принадлежность границам квадрата
    p=((( point->key.x >= (center->x - halfDimension->x) )&&
        ( point->key.x <= (center->x + halfDimension->x)))&&
       (( point->key.y >= (center->y - halfDimension->y) )&&
        ( point->key.y <= (center->y + halfDimension->y))) 
    );
    printf("p=%d",p);
    if (p)
    {
        i=0;
        i = find_list_num(point,obj);
        if (obj->points[i]){
            sost = !Point_sravnenie(point,obj->points[i]);
            if (sost == -1) return -1;
            return 1;
        }else{
            obj->points[i] = point;
            return 0;
        }

       // if (sost) break;
    }
   else{
  // printf("net P")
   printf("x=%d\ty=%d\tcx=%d\ty=%d\thx=%d\dhy=%d",point->key.x,point->key.y,center->x,center->y,halfDimension->x,halfDimension->y);
  }
}

int insert_point(struct QuadTree **obj,struct Point *point,
                int z_x,int z_y, int s_x,int s_y){
   int t,i; 
    if(!*obj) {
       // if (z_x<1) z_x = 1;
       // if (z_y<1) z_x = 1;
      //  if (s_x<1) z_x = 1;
      //  if (s_y<1) z_x = 1;
        *obj = new_QuadTree(z_x,z_y,s_x,s_y); 
    }
    t = add_Point(*obj,point);
    if (t==-1){ printf("Нельзя добавить данные с таким ключём");
        return -1;
    }
    if (t == 0) {(*obj)->busy+=1; return 0;}
    if (t == 1){
        i=0;
        i = find_list_num(point,*obj);
        printf
            ("i=%d\n",i);
        switch(i){ 
            case 0: return insert_point(&(*obj)->northWest,point,z_x-s_x/2
                                                                ,z_y-s_y/2
                                                                ,s_x/2
                                                                ,s_y/2);
            case 1:  return insert_point(&(*obj)->northEast,point,z_x-s_x/2
                                                                ,z_y+s_y/2
                                                                ,s_x/2
                                                                ,s_y/2);
            case 2: return insert_point(&(*obj)->southWest,point,z_x+s_x/2
                                                                ,z_y-s_y/2
                                                                ,s_x/2
                                                                ,s_y/2);
            case 3: return insert_point(&(*obj)->southEast,point,z_x+s_x/2
                                                                ,z_y+s_y/2
                                                                ,s_x/2
                                                                ,s_y/2);
        }
    }
}
int print_Point(struct Point* point,char* fon){
    printf("%s\t [%3d,%3d]\t%s", fon,point->key.x,point->key.y,point->str);
    return 1;
}

int print_QuadTree(struct QuadTree *obj,char *str){
    int i=0,j=0;
    char *stroka[60];
    if (!obj) return 0; 
    for (j=0;j<4;j++)
        if (obj->points[j]){
            i+=print_Point(obj->points[j],str);
        //   printf("\t%d,\t %d,\t %d,\t %d",  obj->boundary.center.x,
         /*                           obj->boundary.center.y,
                                    obj->boundary.halfDimension.x,
                                    obj->boundary.halfDimension.y
                                    );
          *///otladka
        }
        strcpy(stroka,str);
        strcat(stroka,"0");
    i+=print_QuadTree(obj->northWest,stroka);
        strcpy(stroka,str);
        strcat(stroka,"1");
    i+=print_QuadTree(obj->northEast,stroka);
    /*  */
    /* for (j=0;j<4;j++) */
    /*     if (obj->points[j]) */
    /*        i+=print_Point(obj->points[j],str); */
    
        strcpy(stroka,str);
        strcat(stroka,"2");
    i+=print_QuadTree(obj->southWest,stroka);
        strcpy(stroka,str);
        strcat(stroka,"3");
    i+=print_QuadTree(obj->southEast,stroka);
    return i;
}

void input_Data(){
    char str[180],*str1;
    int x,y;
    struct Point *point;
    printf("\ninput ");
    scanf("%d %d %s",&x,&y,str);
    str1 = malloc(sizeof(char)*(strlen(str)+1));
    strcpy(str1,str);

    point =  new_Point(x,y,str1);
    insert_point(&tree,point,0,0,1,1);
}


int main(){
    int i,j,rc;
    struct Point *point;;
    tree = NULL;
   /* for (i=-5;i<4;i++)
        for(j=-5;j<4;j++)
        {
            point = new_Point(i,j,"str");
            insert_point(&tree,point,0,0,1,1);
        }
   */
    while(1){
        rc = dialog(mes, mesLen);
    switch(rc){
        case 0: return 0;
        case 1:
            print_QuadTree(tree,"\nk");
            break;
        case 2:
            input_Data();
            break;
        case 3:;
        case 4:;
        case 5:;
        case 6:;
        break;
    }
   }
    print_QuadTree(tree,"\n");
return 0;
}


