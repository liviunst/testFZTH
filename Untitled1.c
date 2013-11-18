#include<stdio.h>
#include<stdlib.h>

int main()
{
    float x;
    x=(float)100/(float)31;
    float y=1;
    float i;
    for(i=x;i<=100;i+=x)
        {printf("%.2f -> %.2f \n",y,i);
        y=(int)i;
        if(i-y>0) y++;
}
    return 0;
}
