#include <stdio.h>
#include <string.h>
 
int main(int argc, char* argv[])
{
    char curr,prev;
    int  i,j,l,count;
    char Buf[200];
 
    while (1)
    {
            for (i=0; i<200; i++) Buf[i]=0; 
            scanf("%s",Buf);
            l=strlen(Buf);
            if (l==0) break;
            prev=Buf[0];
            count=1;
            for (i=1; i<l; i++)
            {
                        curr=Buf[i];
                        if (curr == prev) 
                            count++;
                        else
                        {
                                        if (count > 1) 
                                        {
                                                            for (j=1; j<=count; j++) printf("%c",prev);
                                                            printf(" ");
                                                                            }
                                                        count=1;
                                                                    }
                                    prev=curr;
                                            }
                    if (count > 1) 
                                {
                                            for (j=1; j<=count; j++) printf("%c",prev);
                                            printf(" ");
                                                    }
                            printf("\n");
    }        return 0;
} 
