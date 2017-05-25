//
//  main.c
//  CTSA
//
//  Created by GulcanErtop on 13.05.2017.
//  Copyright © 2017 GulcanErtop. All rights reserved.
//

#include <stdio.h>
#include <curses.h>
#include<stdlib.h>
#include<time.h>
#include <pthread.h>

int arr[1000];
int ilk[500];
int son[500];
int birlestir[500];
int denemedizi[500];
int elemanSayisi=500;
int limitSayi = 1000;
int butunEleman=1000;



pthread_t bid[sizeof(ilk)];
pthread_t sid[sizeof(son)];
pthread_t brid[sizeof(arr)];
pthread_attr_t attr;

int index1 = 0, index2 = 0;


void selectionSort (int *dizi)
{
    int i, j, enKucuk, temp;
    for (i=0; i<elemanSayisi-1; i++)
    {
        enKucuk = i;
        for (j=i+1; j<elemanSayisi; j++)
        {
            if (dizi[j] < dizi [enKucuk])
            enKucuk = j;
        }
        temp = dizi[i];
        dizi[i] = dizi[enKucuk];
        dizi[enKucuk] = temp;
    }

}

void merge() {
    int answer[1000];
    int i = 499, j =  499 , k = 1000, l;
    
    while (k > 0)
        answer[--k] =
        (j < 0 || (i >= 0 && ilk[i] >= son[j])) ? ilk[i--] : son[j--];
    
    
    
    for (l=0; l<1000; l++) {
        arr[l] = answer[l];
    }
    
    
}

void *runner(void *param)
{
    int threadNumber = (int)param;
    switch (threadNumber) {
        case 0:
            selectionSort(ilk);
            break;
        case 1:
            selectionSort(son);
            break;
        case 2:
            merge();
            break;
        default:
            break;
    }
    
    return 0;
}


int main(int argc, const char *argv[])
    {
        int i = 0;
        //Rastgele sayı üretme
        srand(time(NULL));  //farklı sayı üretir
        for(i=0;i<1000;i++){arr[i] = rand()%1000;}
        
        //2 dizi oluştur
        for (i=0; i<500; i++)
        {
            ilk[i]+=arr[i];
        }
        
        int b =500;
        for (i=0; i<500; i++)
        {
            son[i]+=arr[b];
            b++;
        }

        pthread_create(&sid[0], NULL, runner, 0);
        pthread_create(&sid[1], NULL, runner, 1);
        
        pthread_join(sid[0], NULL);
        pthread_join(sid[1], NULL);
        
        pthread_create(&sid[2], NULL, runner, 2);
        pthread_join(sid[2], NULL);
        
        //Dosya işlemleri
        
        FILE *fptr;
        
        fptr = fopen("program.txt", "w");
        
        
        for (i=0; i<1000; i++) {
            printf("%d\n",arr[i]);
            fprintf(fptr,"%d\n", arr[i]);
            }
        fclose(fptr);
        pthread_exit(0);
}


