#include<stdio.h>

int getMax(int a, int b){
    int c = a - b;
    printf("val c este %d si val c>>31 este %d \n",c,c>>31);
    int k = (c>>31) & 0x1;
    printf("valoarea k este %d \n",k);
    int max = a - k * c;
    return max;
    }
int max(int a, int b){
    if ( a > b ) return a ;
        else return b;
    }

int main(){
   // int a,b;
   // scanf("%d %d",&a,&b);
    //printf("%d \n",max(10,4));
    printf("%d \n",getMax(5,11));
    return 0;
}
