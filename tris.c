#include <stdlib.h>
#include "tris.h"

// ===== TRI FUSION =====
static void fusion(int *tab,int g,int m,int d){
 int n1=m-g+1,n2=d-m;
 int *L=malloc(n1*sizeof(int));int *R=malloc(n2*sizeof(int));
 for(int i=0;i<n1;i++)L[i]=tab[g+i];
 for(int j=0;j<n2;j++)R[j]=tab[m+1+j];
 int i=0,j=0,k=g;
 while(i<n1 && j<n2){if(L[i]<=R[j])tab[k++]=L[i++];else tab[k++]=R[j++];}
 while(i<n1)tab[k++]=L[i++];
 while(j<n2)tab[k++]=R[j++];
 free(L);free(R);
}
static void fusion_rec(int *tab,int g,int d){if(g<d){int m=g+(d-g)/2;fusion_rec(tab,g,m);fusion_rec(tab,m+1,d);fusion(tab,g,m,d);}}
void tri_fusion(int *tab,int n){if(n>1)fusion_rec(tab,0,n-1);}

// ===== TRI RAPIDE - pivot = dernier element (version cours) =====
static int partition(int *tab,int bas,int haut){
 int pivot=tab[haut];int i=bas-1;
 for(int j=bas;j<haut;j++){if(tab[j]<=pivot){i++;int t=tab[i];tab[i]=tab[j];tab[j]=t;}}
 int t=tab[i+1];tab[i+1]=tab[haut];tab[haut]=t;return i+1;
}
static void rapide_rec(int *tab,int bas,int haut){
 while(bas<haut){
   int p=partition(tab,bas,haut);
   // On traite le plus petit cote en recursif, le grand en boucle -> evite stack overflow
   if(p-bas < haut-p){rapide_rec(tab,bas,p-1);bas=p+1;}
   else{rapide_rec(tab,p+1,haut);haut=p-1;}
 }
}
void tri_rapide(int *tab,int n){if(n>1)rapide_rec(tab,0,n-1);}

int est_trie(int *tab,int n){for(int i=1;i<n;i++)if(tab[i]<tab[i-1])return 0;return 1;}
