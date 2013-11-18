#include<stdio.h>

int main(){
    int prices[]={1,5,8,9,10,17,17,20,24,30};
    int revenu[11];
    int rods[11];
    int n = 5;

    int i,j,max;
    for(i = 0; i < n; i++){
       // printf("%d ",prices[i]);
        revenu[i] = 0;
       // printf("%d ",revenu[i]);
        }
    revenu[10] = 0;
    for (i = 1; i <= n; i++){
        max = -1;
        for ( j = 0; j < i; j++)
            if ( max < prices[j] + revenu[i-j-1] ){
                max = prices[j] + revenu[i-j-1];
                rods[i] = j+1;
                }
        revenu[i] = max;
    }
    printf("Venitul maxim este : %d\n",revenu[n]);
    printf("Bucatile de teava sunt :");
    while( n > 0){
        printf(" %d -> %d ;",rods[n],prices[rods[n]]);
        n = n - rods[n];

        }
return 0;
}
