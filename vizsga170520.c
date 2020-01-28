#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <locale.h>

#define MAX 128
#define N 32

struct idsin{
char azonosito[MAX];
}id[N];

struct idsout{
char belepokod[MAX];
}kod[N];

int slen(char *s){
int a=strlen(s)-1;
return a;
}

int s_ishexa(char *s){
int i,a=0;
for(i=0;i<strlen(s)-1;++i){
    if(!isxdigit(s[i]))a++;
}
if(a!=0)return 0;
return 1;
}

int main(void){

setlocale(LC_ALL,"hun");
FILE *fp;
char buf[MAX];
int i,n;

fp=fopen("users.txt","w");
if(!fp)perror("hiba: ");

n=0;
while(1){
    int letezo=0;
    printf("Adjon meg azonos�t�t: ");
    fgets(id[n].azonosito,MAX,stdin);
    if(id[n].azonosito[0]=='\n' || n >= N-1)break;
    if(!s_ishexa(id[n].azonosito))printf("Nem hexadecim�lis!\n");
    else {
        if(slen(id[n].azonosito)!=8)printf("Az azonos�t�nak 8 jegy�nek kell lennie!\n");
        else {
            if(n>0){
                for(i=0;i<n;++i){
                    if(strcmp(id[n].azonosito,id[i].azonosito)==0){
                        printf("M�r l�tez� azonos�t�!\n");
                        letezo = 1;
                    }
                }
            }
            if(letezo!=1){fprintf(fp,"%s",id[n].azonosito);n++;}
        }
    }
}

printf("Bel�ptet�si �zemm�d...\n\n");

fclose(fp);
FILE *fp1;
fp1=fopen("users.txt","r");

for(i=0;i<n;++i){
    if(fscanf(fp1,"%s",kod[i].belepokod)==EOF)break;
}

while(1){
    int egyezes=0;
    printf("�rja be a bel�p� k�dot!\n");

    fgets(buf,MAX,stdin);
    if(buf[0]=='\n')break;
    buf[slen(buf)]='\0';

    for(i=0;i<n;++i){
        if(strcmp(buf,kod[i].belepokod)==0){
            printf("ajt� nyitva!\n",n);
            Sleep(3000);
            printf("ajt� z�rva!\n");
            egyezes=1;
        }
    }
    if(egyezes!=1)printf("hib�s bel�p� k�d\n");
}

fclose(fp1);

return 0;
}


