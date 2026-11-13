#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tris.h"

int* copie_tab(int *src,int n){int *c=malloc(n*sizeof(int));memcpy(c,src,n*sizeof(int));return c;}
int* tab_aleatoire(int n){int *t=malloc(n*sizeof(int));for(int i=0;i<n;i++)t[i]=rand()%100000;return t;}
int* tab_trie(int n){int *t=malloc(n*sizeof(int));for(int i=0;i<n;i++)t[i]=i;return t;}

double mesurer(void (*tri)(int*,int),int *tab,int n){
 clock_t d=clock();tri(tab,n);clock_t f=clock();return (double)(f-d)/CLOCKS_PER_SEC;
}

int main(){
 srand(42);
 printf("=== VERIFICATION ===\n");
 int petits[]={5,2,9,1,7,3};
 int a1[6],a2[6];memcpy(a1,petits,6*sizeof(int));memcpy(a2,petits,6*sizeof(int));
 tri_fusion(a1,6);tri_rapide(a2,6);
 printf("Fusion sur aleatoire : %s\n",est_trie(a1,6)?"OK":"FAIL");
 printf("Rapide sur aleatoire : %s\n",est_trie(a2,6)?"OK":"FAIL");
 int trie_test[10];for(int i=0;i<10;i++)trie_test[i]=i;
 tri_fusion(trie_test,10);printf("Fusion sur deja trie : %s\n",est_trie(trie_test,10)?"OK":"FAIL");
 for(int i=0;i<10;i++)trie_test[i]=i;
 tri_rapide(trie_test,10);printf("Rapide sur deja trie : %s\n",est_trie(trie_test,10)?"OK":"FAIL");

 printf("\n=== BANC DE MESURES ===\n");
 int tailles[]={10000,50000,100000};
 printf("%-10s | %-12s | %-12s | %-12s | %-12s\n","n","Fusion Alea","Rapide Alea","Fusion Trie","Rapide Trie");
 FILE *csv=fopen("mesures.csv","w");fprintf(csv,"n,fusion_alea,rapide_alea,fusion_trie,rapide_trie\n");
 for(int k=0;k<3;k++){
   int n=tailles[k];
   int *base_alea=tab_aleatoire(n);
   int *c1=copie_tab(base_alea,n);int *c2=copie_tab(base_alea,n);
   double t1=mesurer(tri_fusion,c1,n);double t2=mesurer(tri_rapide,c2,n);
   free(base_alea);free(c1);free(c2);
   int *base_trie=tab_trie(n);
   int *c3=copie_tab(base_trie,n);int *c4=copie_tab(base_trie,n);
   double t3=mesurer(tri_fusion,c3,n);double t4=mesurer(tri_rapide,c4,n);
   printf("%-10d | %-12f | %-12f | %-12f | %-12f\n",n,t1,t2,t3,t4);
   fprintf(csv,"%d,%f,%f,%f,%f\n",n,t1,t2,t3,t4);
   free(base_trie);free(c3);free(c4);
 }
 fclose(csv);
 printf("\nVoir commentaire.txt pour l'explication du pire cas\n");
 printf("TP5 OK - valgrind 0 fuite attendu\n");
 return 0;
}
