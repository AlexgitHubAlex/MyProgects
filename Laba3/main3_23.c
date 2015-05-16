#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
#define  SIZE 10
#define  MAX_STR_SIZE 41
//---------------Описание структур----------------------------------------------------
struct Info
{
    int release;
    char *info;
    struct Info *next;
};

struct Item
{
    int key;
    struct Info *info;
    struct Item *next;
};

struct TabItem
{
    struct Item* masive[SIZE];
};




//---------------Прототипы функций----------------------------------------------------
//Общие функции
int getInt (int *data);
int include(struct TabItem* obj);
int find   (struct TabItem* obj);
int delete (struct TabItem* obj);
int view   (struct TabItem* obj);
int quit   (struct TabItem* obj);
int dialog (char *msgs[], int N);
//Функции работы с TabItem
struct Item* getItem(struct TabItem*,int);          //V
//int addItem(struct Item*,int ,struct Info* );//??

//Функции работы с Item
int heshFun (int );                                 //V
struct Item*  findItem(struct Item*,int key);       //V
struct Item* insertInfo(struct Item*, struct Info*);//X


//функции работы с Info
struct Info* newInfo(char *str,int release);        //X
int delInfo(struct Info*);                          //X

//---------------Определение функций--------------------------------------------------
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


//int setsTableData = 0;
int include(struct TabItem* obj)
{
    int i;//,j=MAX_STR_SIZE-1;
    char buf[MAX_STR_SIZE];
    struct Info* vrem;
    struct Item* tekObj;
    //ввод данных
    printf("include\n");
    printf("Введите ключь: ");
    getInt(&i);
    printf("Введите строку: ");
    scanf("%40s^[\n]%*s",buf);
    //создание элементов
    vrem = newInfo(buf,i);
    if(!vrem) { printf("error include\n");return 0;}
    tekObj = findItem(getItem(obj,heshFun(i)),i);

    if (!tekObj) {
        tekObj = addItem(getItem(obj,heshFun(i)),i);
        obj->masive[heshFun(i)] = tekObj;
    }
    //вставка элементов
    obj->masive[heshFun(i)] = insertInfo(getItem(obj,heshFun(i)),vrem);
    return 1;
}

int find   (struct TabItem* obj)
{
    printf("find\n");
    return 1;
}
int delete (struct TabItem* obj)
{
    printf("delete\n");
    return 1;
}
int view   (struct TabItem* obj)
{
    printf("view\n");
    return 1;
}
int quit   (struct TabItem* obj)
{
    printf("quit\n");
    return 0;
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

int heshFun(int i){
    return i%SIZE;
}

struct Item*  findItem(struct Item* objList,int key){
    
    while(objList){
        if (objList->key == key) return objList;
        objList = objList->next;
    }
    return objList;
}

struct Item* getItem(struct TabItem* obj,int index){
    return obj->masive[index];
}

struct Item* insertInfo(struct Item*, struct Info*){
    struct Item* vrem=malloc(struct Item);
    vrem->
}
//---------------Дополнительные необходимые структуры---------------------------------

int (*func[])(struct TabItem*) = {quit,view,include,find,delete};

char* mes[] = { "1. Просмотр таблицы",
                "2. Добавить элемент",
                "3. Найти элемент",
                "4. Удалить элемент",
                "5. Выход",
                };

int mesLen = sizeof(mes)/ sizeof(mes[0]);





//---------------Основная функция-----------------------------------------------------
int main()
{

    struct TabItem table=NULL;
    int rc;
    while(1)
    {
        rc = dialog(mes, mesLen);
        if(!func[rc](&table))
            break; // обнаружен конец файла
       // scanf("%*s");
       // while (getchar() != '\n');
    }
    printf("That's all. Bye!\n");
    //delTable(&table);
    return 0;
}



