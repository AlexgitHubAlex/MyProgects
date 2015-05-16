#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
struct Node
{
     
    int key;
    struct Item *info;
    struct Node *link;
};
 
struct Item
{
     
    int release;
    char *string;
    struct Item *next;
};
 
void testStart();
int deleteItems(struct Item **);
int deleteItem(struct Node *, int);
int addItem(int, char *);
int findByKey(int);
int findByKeyAndRelease(int, int);
int deleteByKey(int);
int deleteByKeyAndRelease(int, int);
int menu(int, int);
struct Node *getRow(int);
struct Item *getItem(struct Node *, int);
void writefile(struct Node *);
int readfile();
void destroy();
int printTable(struct Node *);
int printItems(struct Node *);
int printItem(struct Item *, int);
 
struct Node *table;
 
int main(int argc, char const *argv[])
{
     
    int i, start = 0, file = 0;
    for (i = 1; i < argc; i++) {
            if (strcmp(argv[i], "start") == 0) {
                        start = 1;
                    }
            if (strcmp(argv[i], "file") == 0) {
                        file = 1;
                    }
        }
    if (start) {
            testStart();
        } else if (file) {
                if (!readfile()) {
                            printf("%s\n", "Файл не найден");
                            getchar();
                            return 1;
                        }
            }
    int command = 0;
    int mod;
    char tmp[256];
    do {
            printf("%s", "1 - Добавить\n2 - Найти\n3 - Удалить\n4 - Вывести\n0 - Выход\n");
            printf("%s", "Ваш выбор: ");
            if (!scanf("%d", &command)) {
                        printf("%s\n", "Ошибка ввода");
                        gets(tmp); 
                        mod = 1;
                    } else {
                                mod = 0;
                            }
        } while(menu(command, mod));
    if (file) {
            writefile(table);
        }
    destroy();
    getchar();
    return 0;
}
 
struct Node *getRow(int key)
{
 
    if (!table) {
            table = (struct Node *) malloc(sizeof(struct Node));
            table->key = key;
            return table;
        }
    struct Node *tmpTable = table;
    while (tmpTable) {
            if (tmpTable->key == key) {
                        return tmpTable;
                    }
            if (!tmpTable->link) {
                        tmpTable->link = (struct Node *) malloc(sizeof(struct Node));
                        tmpTable->link->key = key;
                        tmpTable->link->info = NULL;
                        return tmpTable->link;
                    }
            tmpTable = tmpTable->link;
        }
}
 
struct Item *getItem(struct Node *tmpTable, int release)
{
 
    if (!tmpTable->info) {
            tmpTable->info = (struct Item *) malloc(sizeof(struct Item));
            tmpTable->info->release = 0;
            return tmpTable->info;
        }
    struct Item *tmpItem = NULL;
    if (release >= 0) {
            tmpItem = tmpTable->info;
            while (tmpItem) {
                        if (tmpItem->release == release) {
                                        return tmpItem;
                                    } else if (tmpItem->release < release) {
                                                    return NULL;
                                                }
                        tmpItem = tmpItem->next;
                    }
        } else {
                tmpItem = (struct Item *) malloc(sizeof(struct Item));
                tmpItem->release = tmpTable->info->release + 1;
                tmpItem->next = tmpTable->info;
                tmpTable->info = tmpItem;
                return tmpTable->info;
            }
    return NULL;
}
 
int readfile()
{
 
    FILE *file = NULL;
    int i, strLen = 0, type = 0, key = 0;
    struct Node *tmpTable = NULL;
    struct Item *item = NULL;
 
    if (!(file = fopen("Table.dat", "rb"))) {
            return 0;
        }
    while (fread(&type, sizeof(int), 1, file)) {
            switch (type) {
                        case 1:
                            fread(&key, sizeof(int), 1, file);
                            tmpTable = getRow(key);
                            break;
                        case 2:
                            if (!tmpTable->info) {
                                                tmpTable->info = (struct Item *) malloc(sizeof(struct Item));
                                                item = tmpTable->info;
                                            } else {
                                                                item->next = (struct Item *) malloc(sizeof(struct Item));
                                                                item = item->next;
                                                            }
                            fread(&item->release, sizeof(int), 1, file);
                            fread(&strLen, sizeof(int), 1, file);
                            item->string = (char *) malloc(strLen * sizeof(char));
                            fread(item->string, sizeof(char), strLen, file);
                            break;
                    }
        }
    return 1;
}
 
void writefile(struct Node *tmpTable)
{
 
    FILE *file = NULL;
    int strLen = 0, typeT = 1, typeI = 2;
    file = fopen("Table.dat", "wb");
    struct Item *tmpItem = NULL;
    while (tmpTable) {
            fwrite(&typeT, sizeof(int), 1, file);
            fwrite(&tmpTable->key, sizeof(int), 1, file);
            tmpItem = tmpTable->info;
            while (tmpItem) {
                        strLen = strlen(tmpItem->string);
                        fwrite(&typeI, sizeof(int), 1, file);
                        fwrite(&tmpItem->release, sizeof(int), 1, file);
                        fwrite(&strLen, sizeof(int), 1, file);
                        fwrite(tmpItem->string, sizeof(char), strLen, file);
                        tmpItem = tmpItem->next;
                    }
            tmpTable = tmpTable->link;
        }
    fclose(file);
}
 
void destroy()
{
 
    struct Node *tmpTable = NULL;
    while (table) {
            tmpTable = table;
            table = table->link;
            deleteItems(&tmpTable->info);
            free(tmpTable);
        }
    table = NULL;
}
 
void testStart()
{
 
    addItem(0, "str1");
    addItem(0, "str2");
    addItem(0, "str3");
    addItem(1, "str4");
    addItem(1, "str5");
    addItem(3, "str6");
    addItem(3, "str7");
    addItem(4, "str8");
    addItem(5, "str9");
    addItem(6, "str10");
    addItem(6, "str11");
    addItem(6, "str12");
    addItem(7, "str13");
    addItem(7, "str14");
    addItem(8, "str15");
    addItem(8, "str16");
}
 
int printTable(struct Node *tmpTable)
{
 
    int empty = 1;
    while(tmpTable) {
            if (printItems(tmpTable)) {
                        empty = 0;
                    }
            tmpTable = tmpTable->link;
        }
    if (empty) {
            printf("%s\n", "Таблица пуста");
            return 0;
        }
    return 1;
}
 
int printItems(struct Node *tmpTable)
{
 
    int empty = 1;
    struct Item *item = tmpTable->info;
    while(item) {
            if (printItem(item, tmpTable->key)) {
                        empty = 0;
                    }
            item = item->next;
        }
    if (empty) {
            return 0;
        }
    return 1;
}
 
int printItem(struct Item *item, int key)
{
 
    if (item && item->string) {
            printf(" [%d] (%d) %s\n", key, item->release, item->string);
                    return 1;
                        }
        return 0;
}
 
int deleteItems(struct Item **item)
{
 
    struct Item *tmpItem = NULL;
    int empty = 1;
    while(*item) {
            if ((*item)->string) {
                        empty = 0;
                    }
            tmpItem = *item;
            *item = (*item)->next;
            if (tmpItem->string) {
                        free(tmpItem->string);
                    }
            free(tmpItem);
        }
    if (empty) {
            return 0;
        }
    *item = NULL;
    return 1;
}
 
int deleteItem(struct Node *tmpTable, int release)
{
 
    struct Item *item = tmpTable->info;
    if (tmpTable->info->release == release) {
            tmpTable->info = tmpTable->info->next;
            if (item->string) {
                        free(item->string);
                    }
            free(item);
            return 1;
        }
    if (release < 0 || !(item = getItem(tmpTable, release + 1))) {
            return 0;
        }
    struct Item *tmpItem = item->next;
    item->next = item->next->next;
    if (tmpItem->string) {
            free(tmpItem->string);
        }
    free(tmpItem);
    return 1;
}
 
int addItem(int key, char *buf)
{
 
    struct Item *item;
    item = getItem(getRow(key), -1);
    item->string = (char *) malloc(strlen(buf) * sizeof(char));
    strcpy(item->string, buf);
    return 1;
}
 
int findByKey(int key)
{
 
    if (!printItems(getRow(key))) {
            printf("%s\n", "Элементы с заданным ключем не найдены!");
            return 0;
        }
    return 1;
}
 
int findByKeyAndRelease(int key, int release)
{
 
    int i;
    if (release < 0 || !printItem(getItem(getRow(key), release), key)) {
            printf("%s\n", "Элемент с заданным ключем и версией не найден!");
            return 0;
        }
    return 1;
}
 
int deleteByKey(int key)
{
 
    struct Node *tmpTable = getRow(key);
    if (!deleteItems(&tmpTable->info)) {
            printf("%s\n", "Элементы с заданным ключем не найдены!");
            return 0;
        }
    printf("Все элементы с ключем %d удалены\n", key);
    return 1;
}
 
int deleteByKeyAndRelease(int key, int release)
{

    int i;
    if (!deleteItem(getRow(key), release)) {
            printf("%s\n", "Элемент с заданным ключем и версией не найден!");
            return 0;
        }
    printf("Элемент с ключем %d и версией %d удален\n", key, release);
    return 1;
}
 
int menu(int command, int showList)
{
 
    int key, release;
    char buf[256];
    char tmp[256];
    strcpy(buf, "");
    if (showList) {
             
            return 1;
        }
    switch (command) {
            case 0:
                return 0;
            case 1:
                printf("%s\n", "Введите ключ");
                if (!scanf("%d", &key)) {
                                printf("%s\n", "Ошибка ввода");
                                gets(tmp);
                                return 1;
                            }
                printf("%s\n", "Введите строку");
                if (!scanf("%s", buf)) {
                                printf("%s\n", "Ошибка ввода");
                                gets(tmp);
                                return 1;
                            }
                if (addItem(key, buf)) {
                                printf("\n%s\n\n", "Элемент добавлен");
                            } else {
                                            printf("\n%s\n\n", "Ошибка добавления элемента");
                                        }
                break;
            case 2:
                printf("%s", "1 - Найти по ключу\n2 - Найти по ключу и версии\n0 - Вернуться назад\n");
                printf("%s", "Ваш выбор: ");
                if (!scanf("%d", &command)) {
                                printf("%s\n", "Ошибка ввода");
                                gets(tmp);
                                return 1;
                            } else {
                                            switch (command) {
                                                                case 0:
                                                                    break;
                                                                case 1:
                                                                    printf("%s\n", "Введите ключ");
                                                                    if (!scanf("%d", &key)) {
                                                                                                printf("%s\n", "Ошибка ввода");
                                                                                                gets(tmp);
                                                                                                return 1;
                                                                                            }
                                                                    printf("%s\n", "Результат:\n");
                                                                    findByKey(key);
                                                                    printf("\n");
                                                                    break;
                                                                case 2:
                                                                    printf("%s\n", "Введите ключ");
                                                                    if (!scanf("%d", &key)) {
                                                                                                printf("%s\n", "Ошибка ввода");
                                                                                                gets(tmp);
                                                                                                return 1;
                                                                                            }
                                                                    printf("%s\n", "Введите версию");
                                                                    if (!scanf("%d", &release)) {
                                                                                                printf("%s\n", "Ошибка ввода");
                                                                                                gets(tmp);
                                                                                                return 1;
                                                                                            }
                                                                    printf("%s\n", "Результат:\n");
                                                                    findByKeyAndRelease(key, release);
                                                                    printf("\n");
                                                                    break;
                                                                default:
                                                                    printf("%s\n", "Команда не найдена");
                                                                    break;
                                                            }
                                        }
                break;
            case 3:
                printf("%s", "1 - Удалить по ключу\n2 - Удалить по ключу и версии\n0 - Вернуться назад\n");
                printf("%s", "Ваш выбор: ");
                if (!scanf("%d", &command)) {
                                printf("%s\n", "Ошибка ввода");
                                gets(tmp);
                            } else {
                                            switch (command) {
                                                                case 0:
                                                                    break;
                                                                case 1:
                                                                    printf("%s\n", "Введите ключ");
                                                                    if (!scanf("%d", &key)) {
                                                                                                printf("%s\n", "Ошибка ввода");
                                                                                                gets(tmp);
                                                                                                return 1;
                                                                                            }
                                                                    printf("%s\n", "Результат:\n");
                                                                    deleteByKey(key);
                                                                    printf("\n");
                                                                    break;
                                                                case 2:
                                                                    printf("%s\n", "Введите ключ");
                                                                    if (!scanf("%d", &key)) {
                                                                                                printf("%s\n", "Ошибка ввода");
                                                                                                gets(tmp);
                                                                                                return 1;
                                                                                            }
                                                                    printf("%s\n", "Введите версию");
                                                                    if (!scanf("%d", &release)) {
                                                                                                printf("%s\n", "Ошибка ввода");
                                                                                                gets(tmp);
                                                                                                return 1;
                                                                                            }
                                                                    printf("%s\n", "Результат:\n");
                                                                    deleteByKeyAndRelease(key, release);
                                                                    printf("\n");
                                                                    break;
                                                                default:
                                                                    printf("%s\n", "Команда не найдена");
                                                                    break;
                                                            }
                                        }
                break;
            case 4:
                printf("%s\n\n", "Таблица:");
                printTable(table);
                printf("\n");
                break;
            default:
                printf("%s", "Команда не найдена\n");
                break;
        }
    return 1;
} 
