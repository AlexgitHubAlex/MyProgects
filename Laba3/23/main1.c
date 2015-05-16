
#include <unistd.h>
#include <stdio.h> 
#include <malloc.h>
#include <string.h>
#define  SIZE 10
#define  MAX_STR_SIZE 41
//---------------Описание структур----------------------------------------------------
struct Info
{
    int release;
    size_t smechenie;
    //size_t len;
   // char *info;
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



FILE *file = NULL;
int Size_Char_Data=0;
size_t end_of_file;
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
struct Item* getItem(struct TabItem*,int);              //V
int          printTabItem(struct TabItem *);            //v
//int addItem(struct Item*,int ,struct Info* );//??

//Функции работы с Item
int heshFun (int );                                     //V
struct Item* newItem   (struct Item*,int key);          //V
struct Item* findItem  (struct Item*,int key);          //V
struct Info* insertInfo(struct Item*, struct Info*);    //V
int          printItem (struct Item*,int);              //V
struct Item* delItem(struct Item*);                     //V
struct Item* previousItem(struct Item*,struct Item*);   //V

//функции работы с Info
struct Info* newInfo  (char *str,int release,int );     //V
struct Info* delInfo  (struct Info*);                   //V
int          printInfo(struct Info*,int,int);           //V

struct Info* previousInfo(struct Info*,struct Info*);   //V
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
    printf("Введите ключ: ");
    getInt(&i);
    

    printf("Введите строку: ");
    scanf("\n");
    scanf("%40[^\n]%*c",buf);
    //создание элементов
    vrem = newInfo(buf,i,0);
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
                    printf("введите ключ ");
                    scanf("%d",&j);
                    tekSpis = findItem(obj->masive[heshFun(j)],j);
                    printItem(tekSpis,1);
                    break;
            case 2: printf("find\n");
                    printf("введите ключ ");
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
                    printf("введите ключ ");
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
                    printf("введите ключ ");
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
    int k = 0;
    printf("view\n");
    k += printTabItem(obj);
   // printf("%d",k);
    if(!k) printf("данных нет");
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
        if (objList->key == key) 
            return objList;
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
struct Info* newInfo(char *str,int release,int flag){
    extern int  Size_Char_Data;
    size_t len=0;
    struct Info* vrem = malloc(sizeof(struct Info));
    vrem->release = 0;
    //vrem->info = malloc ((strlen(str)+1)*sizeof(char));
    //strcpy(vrem->info,str);
    if(flag == 0){
        fseek(file,Size_Char_Data,SEEK_SET); 
        vrem->smechenie = Size_Char_Data;
        len = 1+strlen(str);
        fwrite(str,sizeof(char),len,file);
    }else{
        vrem->smechenie = flag;
    }
    //vrem->len = len;
    Size_Char_Data+=len;
    //*
    
    vrem->next = NULL;
    return vrem;
}

int printTabItem(struct TabItem *obj){
    int i,k=0;
    for (i=0;i<SIZE;i++){
       // ! printf("hesh key {%d}\n",i);
        k += printItem(obj->masive[i],0);
    }
    return k;
  //  printf("endi\n");
}
int printItem(struct Item* obj,int kolPrint){
    int k = 0;
    while(obj){
        
       // ! printf("key{%d}\n",obj->key);
        k += printInfo(obj->info,obj->key,0);
        obj = obj->next;
        if(!kolPrint){ continue; } 
        if (--kolPrint<=1) break;
    }
    return k;
}
int printInfo(struct Info* obj,int key,int kolPrint){
    int fl = 1,k=0;//,kol=30;
    char str[40];
    if(!obj) printf("Список пуст\n");
    while(obj){
        //printf("[%d] \t[%d] \t\'%s\'\n",key,obj->release,obj->info);
        fseek(file,obj->smechenie,SEEK_SET);
        fscanf(file,"%40[^\n]s",str);
        printf("[%d] \t[%d] \t\'%s\'\n",key,obj->release,str); 
        k++;
        obj = obj->next;
        if(!kolPrint){ continue; } 
        if(--kolPrint <= 1) break;
    }
    return k;
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
FILE* getFile(FILE *file,size_t *kolData){
    int kol_info=0;
    char nameFile[40]={0},
         YesNo; 
    *kolData = 4;
    system("clear");
    system("ls");
    printf("Введите имя файла для работы: ");
    scanf("%s",nameFile);
    file = fopen(nameFile,"a+b"); //если нет файла создаём новый
    fclose(file);
    file = fopen(nameFile,"rw+b");
    if (!file) {printf("file open error."); return NULL;}
    if (fread(kolData,sizeof(size_t),1,file))
    {
        fseek(file,*kolData,SEEK_SET);
        fread(&kol_info,sizeof(int),1,file);

        printf("in file %zd data",kol_info);

    }else{
        printf("file pust\n");
        fwrite(kolData,sizeof(size_t),1,file);
    }
    return file;

}
void chengeKolChar(FILE* file,size_t kolData,size_t mesto){
    fseek(file,mesto,SEEK_SET); 
    //fprintf(file,"%zd",kolData);
 //   printf("write pos// = %d\n data = %zd",ftell(file),kolData);
    //if(
    fwrite(&kolData,sizeof(size_t),1,file);
    //) puts("запись успешно выполнена\n");

    fseek(file,mesto,SEEK_SET);
    fread(&kolData,sizeof(size_t),1,file);
//    printf("\nkolDataf = %zd",kolData);
}

void printTabItemInFile(FILE* file,struct TabItem *table){
    extern int  Size_Char_Data;
    int i,kol_data=0;
    struct Item *tmpItem;
    struct Info *tmpInfo;
    fseek(file,Size_Char_Data,SEEK_SET);
    fwrite(&kol_data,sizeof(int),1,file);
    for (i=0;i<SIZE;i++){
        tmpItem=table->masive[i];
        while(tmpItem){
            tmpInfo = tmpItem->info;
            while(tmpInfo){
                fwrite(&(tmpItem->key),      sizeof(int),1,   file);
                fwrite(&(tmpInfo->release),  sizeof(int),1,   file);
                fwrite(&(tmpInfo->smechenie),sizeof(size_t),1,file);
                kol_data++;
                tmpInfo= tmpInfo->next;
            }

            tmpItem=tmpItem->next;
        }
    }

    fseek(file,Size_Char_Data,SEEK_SET);
    fwrite(&kol_data,sizeof(int),1,file);
    end_of_file = ftell(file);
    
}

void readTableItemFile(FILE *file,struct TabItem *table){
    extern int  Size_Char_Data;
    int key,release,smechenie,pred_key=-1,kol_data;
    struct Info **tekInfo=NULL;
    struct Item **tekItem = NULL;//,**LtekObj;
    //int f=0;
   // char k;
    printf("\n");
   // f=1;
    if(Size_Char_Data>4){

        fseek(file,Size_Char_Data,SEEK_SET);
        fread(&kol_data,sizeof(int),1,file);
        while(kol_data){
            kol_data --;
            fread(&key,sizeof(int),1,file);
            fread(&release,sizeof(int),1,file);
            fread(&smechenie,sizeof(size_t),1,file);
// !            printf("%d \t%d \t%zd\n",key,release,smechenie);
            if(key!=pred_key){//если ключи не совпадают
             
                if(tekItem) 
                        {tekItem = &(*tekItem)->next;}                 //если хеши совпали и есть хоть один элемент
                if(heshFun(key)!=heshFun(pred_key))                     //если хеши не совпадают
                    {tekItem = &table->masive[heshFun(key)];}
                    *tekItem  = newItem(NULL,key);
                tekInfo = &(*tekItem)->info;    
            }
            *tekInfo = newInfo("",key,smechenie);//создание нового элемента
            (*tekInfo)->release = release;
           
            tekInfo = &((*tekInfo)->next);

            pred_key = key;
        }
    }
}
 

//---------------Основная функция-----------------------------------------------------
int main()
{
    extern int  Size_Char_Data;
    struct TabItem table;
    int rc,i;
    file = getFile(file,&Size_Char_Data);
    //printf("vvedite chislo");
    //scanf("%d",&i);
    //chengeKolChar(file,i,0);
    //load();





    for (i=0;i<SIZE;i++){
        table.masive[i] = NULL;
    }

    readTableItemFile(file,&table); 



    //work
    while(1)
    {
        rc = dialog(mes, mesLen);
        if(!func[rc](&table))
            break; // обнаружен конец файла
    }
    //write to file
    chengeKolChar(file,Size_Char_Data,0);
    printTabItemInFile(file,&table);

    fseek(file,end_of_file,SEEK_SET);
    fclose(file);

    printf("That's all. Bye!\n");

    return 0;
}
