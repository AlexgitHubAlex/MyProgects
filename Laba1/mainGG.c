#include "stdio.h"
#include "malloc.h"
#include "stdio.h"

struct Line{
    int     n;
    int* line;
};

struct Matr{
    int m;
    struct Line *matr;
};

int gatInt(int *);
int gatDouble(double*);
int getMaxmin(int*,int,int);
int input(struct Matr*);
void output(struct Matr);
int work(struct Matr);
void Free(struct Matr*);

//Ввод с проверкой-----------------------------------------------------------
int gatInt(int *data){
    int f=1;
    do{
        if (f==0) scanf("%*c"); 
        f=scanf("%d",data);
        if (f==-1)return 0;
    }while (!f);
    return 1;
}

int gatDouble (double *data){
    int f=1;
    do{
        if (f==0) scanf("%*c"); 
        f=scanf("%lf",data);
        if (f==-1)return 0;
    }while (!f);
    return 1;
}
//--------------------------------------------------------------------------
//Ввод в структуру
int input(struct Matr*pM){
    int i,j;
    char * mes="\n";
    printf("Введите кол-во строк:");
    do{
        printf("%s",mes);
        if (!gatInt(&pM->m)) return 0;
        mes = "Ввод прошёл неудачно попробуйте ещё раз ....\n" ;   
    }while(pM->m<0);
    if (pM->m==0)return 0;
    pM->matr = malloc(pM->m*sizeof(struct Line));

    for (i=0;i<pM->m;++i){
        mes="\n";
        printf("Введите кол-во элементов %d строки... ",i+1);
        do{
            printf("%s",mes);
            //printf("%d",&pM->matr[i].m);
            if(!gatInt(&pM->matr[i].n)) return 0;
            mes = "Ввод прошёл неудачно попробуйте ещё раз ....\n";
        }while(pM->matr[i].n==0);
        pM->matr[i].line= malloc(pM->matr[i].n*sizeof(int));
        for (j=0;j<pM->matr[i].n;++j)
            if(!gatInt(&pM->matr[i].line[j])) return 0;                                                   
    }
    return 1;
}

void Free(struct Matr* pM){
    int i;
    for(i=0;i< pM->m;i++)
        free(pM->matr[i].line);
    free(pM->matr);
    pM->matr = 0;
    pM->m=0;
    
}
void output(struct Matr M){
    int i,j;
    for (i=0;i<M.m;i++)
        for (j=0;j<M.matr[i].n;j++)
            printf("%d%c",M.matr[i].line[j],j==M.matr[i].n-1?'\n':' ');
}
int max(struct Line obj){
   int rez=obj.line[0];
    int i;
    for (i=1;i<obj.n;i++)
        if (obj.line[i]>rez) rez=obj.line[i];
    return rez;
}
double srAr(struct Line obj){
    int i;
    double rez=obj.line[0];
    for (i=1;i<obj.n;i++)
        //if (obj.line[i]>rez) rez=obj.line[i];
        rez+=obj.line[i];
    rez/=obj.n;
    return rez;
}
void swap(struct Matr *M,int i,int j){
    struct Line vrem;
    vrem.n = M->matr[i].n;
    vrem.line = M->matr[i].line;
    
    M->matr[i].n = M->matr[j].n;
    M->matr[i].line = M->matr[j].line;

    M->matr[j].n =vrem.n;
    M->matr[j].line = vrem.line;


}
void vork(struct Matr M){
/*    struct Line k;
    double tek;
    int i;
    k.n=M.m;
    k.line=malloc(M.m*sizeof(double));
    for (i=0;i<k.n;i++){
        k.line[i]=srAr(M.matr[i]);
    }

    tek=max(k);
    printf("Результат:\n");
    for (i=0;i<k.n;i++){
        printf("\"%lf\"",k.line[i])
            ;
        k.line[i]/=tek;
        printf("%lf ",k.line[i]);
    }
    free(k.line);

*/
    struct Line vrem;

    int maxPolel=0,imaxPolel=0,maxOtr=0,imaxOtr=0,poltek,otrtek,i,j;
    for (i=0;i<M.m;i++){
        poltek=0;
        otrtek=0;
        for(j=0;j<M.matr[i].n;j++){
            if(M.matr[i].line[j]<=0) otrtek++;
            if(M.matr[i].line[j]>0) poltek++;
        }
        if(maxPolel<poltek) {imaxPolel=i;maxPolel=poltek;}
        if(maxOtr<otrtek) {imaxOtr=i;maxOtr=otrtek;}
    }
        
    swap(&M,0,imaxPolel);
    swap(&M,M.m-1,imaxOtr);
 }
int main(){
   // double k;
   // while(1)
   // if (gatDouble(&k))printf("\n%f",k);
    struct Matr M;
    while(1){
    if(input(&M)==0)break;
    printf("input data");
    output(M);
    vork(M);
    printf("rezulatt\n");
    output(M);
    Free(&M);
    }
    return 0;
}
