

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char* substring(char*,char*,int,int);
void Read(void);
void GetTriplets(void);
void SetTripletsValues(void);
void ShowTriplets(void);

struct record{
int start;
int stop;
char triplet[4];
};

struct unique{
int start;
int stop;    
char triplet[4];
};

struct record dna[598];
struct unique dna_uniq[299];
int unique_len=0;

int main()
{
    Read();
    GetTriplets();
    SetTripletsValues();
    ShowTriplets();
    getchar();
    return 0;
}
void Read()
{
int i,k=0,j,count,number;
    
    char string[1024],n1[7],n2[7],buff[4],*p,*ptr=NULL;
    char filenamegenes[]="C:\\Users\\Artemis\\.vscode\\.vscode\\.vscode\\agg\\genes01.dat";
    char filenamegenome[]="C:\\Users\\Artemis\\.vscode\\.vscode\\.vscode\\agg\\genome01.dat";

    char tmp[3];
    FILE *fpgenome,*fpgenes;

    fpgenes=fopen(filenamegenes,"r");
    fpgenome=fopen(filenamegenome,"r");

    if (fpgenes!=NULL && fpgenome!=NULL)
    {    
        for(i=0;i<299;i++)
        {
            int startn; 
            int stopn;

            fgets(string,1024,fpgenes);
            substring(n1,string,0,5);
            p=strchr(string,',');
            ++p;
            substring(n2,p,0,5);
            
            sscanf(n1,"%i",&startn);
            sscanf(n2,"%i",&stopn);
            
            fseek(fpgenome,startn-1,SEEK_SET);
            fgets(buff,4,fpgenome);
            buff[4]='\0';

            strcpy(dna[k].triplet,buff);
            dna[k].start=1;
            dna[k].stop=0;
            
            fseek(fpgenome,stopn-3,SEEK_SET);
            fgets(buff,4,fpgenome);
            buff[4]='\0';
            
            k+=1;
            strcpy(dna[k].triplet,buff);
            dna[k].start=0;
            dna[k].stop=1;
            k+=1;
        }
        fclose(fpgenes);
        fclose(fpgenome);
    }
    else
    {
        printf("Something go wrong,cannot open file");
    }
}
void GetTriplets()
{
    strcpy(dna_uniq[0].triplet,dna[0].triplet);
    dna_uniq[0].start=0;
    dna_uniq[0].stop=0;

    for(int i=1;i<598;i++)
    {
        int j=0;
        int found=0;
        while(found==0 && j<=unique_len)
        {
            if(!strcmp(dna_uniq[j].triplet,dna[i].triplet))
                found=1;
            j+=1;    
        }
        if(!found)
        {
            unique_len+=1;
            strcpy(dna_uniq[unique_len].triplet,dna[i].triplet);
            dna_uniq[unique_len].start=0;
            dna_uniq[unique_len].stop=0;
        }
    }
}
void SetTripletsValues()
{
    for(int i=0;i<unique_len;i++)   
     for(int j=0;j<598;j++)
      if(!strcmp(dna_uniq[i].triplet,dna[j].triplet))
        {
            dna_uniq[i].start+=dna[j].start;
            dna_uniq[i].stop+=dna[j].stop;
        }
}   
void ShowTriplets()
{
    printf("\tSTART\n");
    putchar('\n');
    printf("Τριπλέτα\tαριθμός εμφανίσεων\n");
    for(int i=0;i<unique_len;i++)
    {
        if(dna_uniq[i].start!=0)
            printf("%s\t\t\t%d\n",dna_uniq[i].triplet,dna_uniq[i].start);
    }
    putchar('\n');
    printf("\tSTOP\n");
    putchar('\n');
    printf("Τριπλέτα\tαριθμός εμφανίσεων\n");
    for(int i=0;i<unique_len;i++)
    {
        if(dna_uniq[i].stop!=0)
            printf("%s\t\t\t%d\n",dna_uniq[i].triplet,dna_uniq[i].stop);
    }
}
char substring(char destination,char* source,int start,int len)
{
    while(len>=0)
    {
        if(*source!=',' && *source!='\n')
        {
         *destination=*source;
         ++destination;
         ++source;
         len--;
        }
        else
        {
         *destination='\0';
         break;
        }
    }
    return destination;
}
