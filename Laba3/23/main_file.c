#include <stdio.h>

int main(){
 FILE *f;
 int i=45;
 f = fopen("hello","wb");
 fwrite(&i,sizeof(int),1,f);
 fclose(f);

 f = fopen("hello","rb");
 fread(&i,sizeof(int),1,f);
 printf("%d",i);
 fclose(f);
return 0;
} 

