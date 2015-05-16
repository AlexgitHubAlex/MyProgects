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
void printTabItem(struct TabItem *);                 //v
//int addItem(struct Item*,int ,struct Info* );//??

//Функции работы с Item
int heshFun (int );                                 //V
struct Item* newItem   (struct Item*,int key);      //V
struct Item* findItem  (struct Item*,int key);      //V
struct Info* insertInfo(struct Item*, struct Info*);//V
void         printItem (struct Item*,int);          //V
struct Item* delItem(struct Item*);                 //V
struct Item* previousItem(struct Item*,struct Item*);//V

//функции работы с Info
struct Info* newInfo  (char *str,int release);        //V
struct Info* delInfo  (struct Info*);                 //V
void         printInfo(struct Info*,int,int);         //V

struct Info* previousInfo(struct Info*,struct Info*); //V
struct Info* findInfo (struct Info*,int);
//---------------Дополнительные необходимые структуры---------------------------------

int (*func[])(struct TabItem*) = {quit,view,include,find,delete};

char* mes[] =     { "1. Просмотр таблицы",
                    "2. Добавить элемент",
                    "3. Найти элемент",
                    "4. Удалить элемент",
                    "5. Выход"
                  };

int mesLen = sizeof(mes)/ sizeof(mes[0]);

char* mesDel[] = {  "1. Удалить элемент по ключу",
                    "2. Удалить элемент по ключу и по версии",
                    "3. Показать таблицу",
                    "4. Отмена"
                 };
int mesLenDel = sizeof(mesDel)/sizeof(mesDel[0]);

char* mesFind[] = { "1. Поиск элемент по ключу",
                    "2. Поиск элемент по ключу и по версии",
                    "3. Отмена"
                 };
int mesLenFind = sizeof(mesFind)/sizeof(mesFind[0]);


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
    scanf("\n");
    scanf("%40[^\n]%*c",buf);
    //создание элементов
    vrem = newInfo(buf,i);
    if(!vrem) { printf("error include\n");return 0;}
    tekObj = findItem(getItem(obj,heshFun(i)),i);

    if (!tekObj) {
        tekObj = newItem(getItem(obj,heshFun(i)),i);
        obj->masive[heshFun(i)] = tekObj;
    }
    //вставка элементов
    tekObj->info = insertInfo(tekObj,vrem);
    return 1;
}

int find   (struct TabItem* obj)
{
    int i,j;
    struct Item* tekSpis=NULL;
    do{ 
        i = dialog(mesFind,mesLenFind);
        switch (i){
            case 1: printf("find\n");
                    printf("введите ключь ");
                    scanf("%d",&j);
                    tekSpis = findItem(obj->masive[heshFun(j)],j);
                    printItem(tekSpis,1);
                    break;
            case 2: printf("find\n");
                    printf("введите ключь ");
                    scanf("%d",&j);
                    tekSpis = findItem(obj->masive[heshFun(j)],j);
                    printItem(tekSpis,1);
                    if(tekSpis){
                        printf("Введите версию ");
                        scanf("%d",&j);
                        printInfo(findInfo(tekSpis->info,j),tekSpis->key,1);
                    }else
                        printf("данные не найдены ");
                    break;
            case 3: 
                    
                    break;
        }
    }while(i);

    return 1;
}
int delete (struct TabItem* obj)
{
    int i,j,k;
    struct Item* tekSpis, *predTekSpis;
    struct Info* tekInfo,*predTekInfo;
    printf("delete\n");
    do{ 
        i = dialog(mesDel,mesLenDel);
        switch (i){
            case 1:
                    printf("введите ключь ");
                    scanf("%d",&j);
                    tekSpis = findItem(obj->masive[heshFun(j)],j);
                    if (obj->masive[heshFun(j)] == tekSpis) 
                        obj->masive[heshFun(j)] = delItem(tekSpis);
                    else{
                        predTekSpis = previousItem(obj->masive[heshFun(j)],tekSpis);
                        predTekSpis->next =  delItem(tekSpis);
                    }
                    break;
            case 2: 
                    printf("введите ключь ");
                    scanf("%d",&j);
                    tekSpis = findItem(obj->masive[heshFun(j)],j);
                    printf("find\n");
                    printItem(tekSpis,1);

                    printf("Введите версию ");
                    scanf("%d",&k);
                    tekInfo = findInfo(tekSpis->info,k);
                    printf("find\n");
                    printInfo(tekInfo,99,1);
                    if(tekInfo == tekSpis->info){ 
                        tekSpis->info = delInfo(tekInfo);
                        if(tekSpis->info==NULL) {
                            if (obj->masive[heshFun(j)] == tekSpis){ 
                                obj->masive[heshFun(j)] = delItem(tekSpis);
                            }else{
                                predTekSpis = previousItem(obj->masive[heshFun(j)],tekSpis);
                                predTekSpis->next =  delItem(tekSpis);
                            }
                        } 
                    }else{
                        predTekInfo = previousInfo(tekSpis->info,tekInfo);
                        
                        printf("!!");
                        printInfo(predTekInfo,99,1);
                        
                        predTekInfo->next = delInfo(tekInfo);
                    }
                    break;
            case 3: printf("3");
                    view(obj);    
                    break;
            case 4: printf("4");
                    
                    break;
        }
    }while(i);
    return 1;
}
int view   (struct TabItem* obj)
{
    printf("view\n");
    printTabItem(obj);
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
        printf("-------------------------------------------------------------------------------------\n");
        for(i= 0; i< N; ++i){
            puts(msgs[i]);
        }

        printf("-------------------------------------------------------------------------------------\n");
        printf("--> ");
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

struct Info* insertInfo(struct Item* tekObj, struct Info* newInfo){
    if(tekObj->info){
        newInfo->release = tekObj->info->release+1;
        newInfo->next = tekObj->info;
    }
    return newInfo;
}

struct Item* newItem(struct Item* nextObj,int key)
{
    struct Item* vrem;
    vrem = malloc(sizeof(struct Item));
    vrem->key = key;
    vrem->info = NULL;
    vrem->next = nextObj;
    return vrem;
}
struct Info* newInfo(char *str,int release){
    struct Info* vrem = malloc(sizeof(struct Info));
    vrem->release = 0;
    vrem->info = malloc ((strlen(str)+1)*sizeof(char));
    strcpy(vrem->info,str);
    vrem->next = NULL;
    return vrem;
}

void printTabItem(struct TabItem *obj){
    int i;
    for (i=0;i<SIZE;i++)
        printItem(obj->masive[i],0);
}
void printItem(struct Item* obj,int kolPrint){
    int fl = 1;
    while(obj&&fl){
        printInfo(obj->info,obj->key,0);
        obj = obj->next;
        if(kolPrint == 1) fl =0;
        kolPrint--;
    }
}
void printInfo(struct Info* obj,int key,int kolPrint){
    int fl = 1;
    if(!obj) printf("Список пуст\n");
    while(obj&&fl){
        printf("[%d] \t[%d] \t\'%s\'\n",key,obj->release,obj->info);
        obj = obj->next;
        if(kolPrint == 1) fl = 0;
        kolPrint--;
    }

}
//удаляет текущий элемент и возращает ссылку на следующий
struct Item* delItem(struct Item* delObj){
    struct Item* rez=NULL;
    if(delObj) {
        rez = delObj->next;

        //освободить item;
        while(delObj->info){
            delObj->info = delInfo(delObj->info);
        }
       free (delObj);
    }
    return rez;
}
struct Info* delInfo(struct Info* delObj){
    struct Info* rez=NULL;
    printf("del : ");
    printInfo(delObj,0,1);
    if(delObj){
        rez = delObj->next; 
        free (delObj->info);
        free (delObj);
    }
    return rez;
}

struct Info* previousInfo(struct Info* spis,struct Info* nextObj){   
    struct Info* zapas = nextObj;    
    while(spis){
        if(spis->next == nextObj) return spis;  
        spis =  spis->next;
    }
    return zapas;
}

struct Item* previousItem(struct Item* spis,struct Item* nextObj){
    struct Item* zapas = nextObj;    
    while(spis){
        if(spis->next == nextObj) return spis; 
        spis = spis->next;
    }
    return zapas;
  
}
struct Info* findInfo(struct Info* spis,int release){
    while(spis){
        if (release == spis->release) return spis;
        spis = spis->next;
    }
    return NULL;
}
//---------------Основная функция-----------------------------------------------------
int main()
{
    struct TabItem table;
    int rc,i;
    for (i=0;i<SIZE;i++){
        table.masive[i] = NULL;
    }
    while(1)
    {
        rc = dialog(mes, mesLen);
        if(!func[rc](&table))
            break; // обнаружен конец файла
    }
    printf("That's all. Bye!\n");
    return 0;
}
