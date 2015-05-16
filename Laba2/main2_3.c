//Задание 15 
//
#include <stdio.h>
#include <malloc.h>

struct lineString{
    char data;
    struct lineString* next; 
};

struct lineString * newElement(char data){
    struct lineString *new = malloc(sizeof(struct lineString));
    if (new == NULL) printf("Error newElement");
    new->data = data;
    new->next = NULL;
    return new;
}

void freeLine(struct lineString* delStr){
    struct lineString* next;
    if (delStr&&delStr->next){
        next= delStr->next;
        while (next){
            free(delStr);
            delStr = next;
            next = next->next;
        }
        
        free(delStr);
    }
}

int Input(struct lineString** obj){
    char buf[21],*str;
    int n,fl=0;
    struct lineString* tek=NULL;
    if(*obj!=NULL){
        freeLine((*obj)->next);
        (*obj)->next = NULL;   
        tek = *obj;
    }else{
        *obj = newElement(0);
        tek = *obj;
    }
    do{
        n=scanf("%20[^\n]",buf);
        if(n<0){
            return 1;    
        }
        if(n>0){
            for(str = buf;*str != '\0';++str){
                tek->next = newElement(*str);
                tek = tek->next;
            }     
        }
        else{
            scanf("%*c");       
        }
    }while(n>0);
    return n;
}


void Print(struct lineString* obj){
    if (obj){
        printf("\'");
        while(obj){
            printf("%c",obj->data);
            obj = obj->next;
        }
        printf("\'");
    }
}
//возращает длинну слова от текущего местоположения до следующего 
int lenSlova(struct lineString* str){
    int i=0;

    if (str&&str->next){
        str = str->next;
        while((str->data != ' ')&&(str->data != '\t')&&(str->data != 0)){
            i++;
            str = str->next;
            if (!str) break;
        }
    }
    return i;
}
//Возращает кол-во пробельных символов от текущего местоположения до следующего слова
int lenTabs(struct lineString* str){
    int i=0;
    if (str&&str->next){
        str=str->next;
        while(((str->data == ' ')||(str->data == '\t'))){
            i++;
            str = str->next;
            if (!str){
                break;}
        }
    }
   
   return i;
}
//удаляет определённое кол-во символов начиная с символа в следующем элементе
struct lineString* stepNextNSim(struct lineString* str,int smeshenie){
    int i;
    if(smeshenie>0)
        for (i=0;str&&i<smeshenie;i++){
            str= str->next;
        }
    return str;
}

struct lineString* newSlovo(struct lineString* q){
    if(q){ 
        q = stepNextNSim(q,lenSlova(q));
        q = stepNextNSim(q,lenTabs(q));
    }
    return q;
}


//Необходимо передать элемент предшествужщий слову
void delNSim(struct lineString* str,int t){
    struct lineString* q,
                     * qf;
    if(str&&str->next) qf=str->next;
    if(t>0){
    q=stepNextNSim(str,t);
    str->next = q->next;
    q->next = NULL;
    freeLine(qf);}
}

int srAr(int *mas,int kol_el){
    int i,sum;
    for(i=0,sum=0;i<kol_el;i++){
        sum+=mas[i];
    }
    return sum/kol_el;
}
struct lineString* insertElemPust(struct lineString* from,char data){
    struct lineString*        
    vrem  = newElement(data);
    vrem->next = from->next;
    from->next = vrem;
    return from->next;
}

struct lineString* work(struct lineString* data){
    struct lineString* tmp =data;
    struct lineString* rez = NULL,*last=NULL;
    int flag=0;
    rez = last =newElement('*');
    while (tmp && tmp->next && tmp->next->next){
        if((tmp->next->data==tmp->next->next->data)&&(tmp->next->data!=' ')&&(tmp->next->data!='\t')){
            last=insertElemPust(last,tmp->next->data); 
            flag = 1;
        }
        else{
            if (flag) {
                last = insertElemPust(last,tmp->data);
                last=insertElemPust(last,' '); 
                flag = 0;
            }
            //else
              //  last=insertElemPust(last,' '); 
        }
        tmp = tmp->next;
    }
    if (flag) last = insertElemPust(last,tmp->data);

    /*last =tmp =rez;
    delNSim(last,lenTabs(last->next));
    printf("vith tab ");
    Print(last);
    while(last&&last->next){ 
            tmp = last = stepNextNSim(last,lenSlova(last));
            delNSim(last,lenTabs(last));
            if(last==tmp)
                if (last != rez)  
                    last=insertElemPust(last,' ');
    }
    delNSim(tmp,1);*/
    last=rez;
    rez=rez->next;
    last->next = NULL;
    freeLine(last);
    return rez;
}


int main(){
    struct lineString* myStr=NULL;
    struct lineString* tmp=NULL;    
    printf("Введите строку:\n");
     while(!Input(&myStr))
    {
        printf("Введено: ");
        Print(myStr);
        printf("\n");
        tmp = work(myStr);
        printf("\nИзменено:");
        /* Print(myStr); */
        Print(tmp);
        freeLine(tmp);
        printf("\nВведите строку:\n");
    }
    freeLine(myStr);
    return 0;
} 

