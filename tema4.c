#include<stdio.h>
#include<stdlib.h>

//branch Horia

unsigned char * initializare(unsigned char *w,int n)
    {
        w=(unsigned char *)calloc(n,sizeof(unsigned char));
        return w;
    }
void umple(unsigned char *w,int n,int m,int p)
    {
        int i;
        for(i=n;i<n+m;i++)
            *(w+i)=p;

    }

/*void alloc(unsigned char *p,int a,int b)
    {
        int *w,*v;
        int ind,ind1;
        w=(int)p;
        if(*w==0) {if(b-a-12>=0)    {*w=4;
                                     w=(int)(p+4);
                                     *w=0;
                                     w=(int)(p+8);
                                     *w=0;
                                     w=(int)(p+12);
                                     *w=12+a;
                                    }
                    printf("16");
                    }
            else {if(*w-4>=12+a){v=(int)(p+12);
                                 *v=a+12;
                                 v=(int)(p+8);
                                 *v=0;
                                 v=(int)(p+4);
                                 *v=*w;
                                 v=(int)(p+*w+4);
                                 *v=4;
                                 *w=4;

                                }
                         else {ind=*w;
                               w=(int)(p+ind);
                               if(*w==0) {v=(int)(p+ind+8);
                                          if((b-ind-(*v))>=a) {*w=ind+*v;
                                                                ind1=*w;
                                                                w=(int)(p+ind+(*v));
                                                                *w=0;
                                                                *(w+1)=ind1;
                                                                *(w+2)=a+12;
                                                                printf("%d",ind+a+12);
                                                               }
                                            }
                              }
                }
    }
*/

int alloc(unsigned char *p,int a, int b)
    {
        int start,ant,act,size,urm,marime;
        start=*((int*)p);
        if(start==0) {if(a+12<=b-4)   {                           //verifica daca primii 4 octeti sunt 0 ...
                                     *((int*)p)=4;              //in acest caz aloca memorie la inceputul arenei daca arena-4>=size
                                     *((int*)(p+4))=0;
                                     *((int*)(p+8))=0;
                                     *((int*)(p+12))=a+12;
                                     //printf("1 ");
                                     return 16;
                                     }
                          else return 0;
                      }
               else  {if(start-4>=a+12)                         //in cazul in care in arena se afla un bloc se verifica daca blocul pe care vrem
                                        {                       //sa-l alocam incape intre primul indice al arenei si primul bloc alocat
                                         *((int*)p)=4;
                                         *((int*)(p+4))=start;
                                         *((int*)(p+8))=0;
                                         *((int*)(p+12))=a+12;
                                         *((int*)(p+start+4))=4;
                                         //printf("2 ");
                                         return 16;

                                        }
                                else {while(*((int*)(p+start))!=0)
                                        {
                                     //       ant=*((int*)(p+start+4));
                                            size=*((int*)(p+start+8));
                                     //       act=*((int*)(p+ant));
                                            urm=*((int*)(p+start));
                                            marime=urm-start-size;
                                            if(marime>=a+12)    {
                                                                 *((int*)(p+urm+4))=urm-marime;
                                                                 *((int*)(p+urm-marime))=urm;
                                                                 *((int*)(p+urm-marime+4))=start;
                                                                 *((int*)(p+urm-marime+8))=a+12;
                                                                 *((int*)(p+start))=urm-marime;
                                                                 //printf("3 ");
                                                                 return (urm-marime+12);
                                                                }
                                            start=*((int*)(p+start));

                                        }
                                        size=*((int*)(p+start+8));
                                        ant=*((int*)(p+start+4));
                                        act=*((int*)(p+ant));

                                        //printf("%d %d",act,size);

                                        if((b-act-size)>=a+12) {
                                                                 *((int*)(p+act+size))=0;
                                                                 *((int*)(p+act+size+4))=act;
                                                                 *((int*)(p+act+size+8))=a+12;
                                                                 *((int*)(p+act))=act+size;
                                                                 //printf("4 ");
                                                                 return(act+size+12);
                                                                }
                                                else return 0;

                                        }
                        }
    }

void elibereaza(unsigned char *p,int x)
    {
        int ind,ind2;
    ind=*((int*)p);
    if(ind+12==x) {
                ind2=*((int*)(p+ind));
                *((int*)p)=ind2;

                if(ind2!=0) {*((int*)(p+ind2+4))=0;
                            }
                //*((int*)(p+ind))=0;
                //*((int*)(p+ind+4))=0;
                //*((int*)(p+ind+8))=0;

                }
     else {ind=*((int*)(p+x-12));
        if(ind!=0) {*((int*)(p+ind+4))=*((int*)(p+x-8));

                    }
        ind=*((int*)(p+x-8));
        if(ind!=0) {*((int*)(p+ind))=*((int*)(p+x-12));

                    }
        //*((int*)(p+x-12))=0;
        //*((int*)(p+x-8))=0;
        //*((int*)(p+x-4))=0;
     }
    }

int showfree(unsigned char *p,int b)
        {
            int start,nblocks=0,fbytes=0,size,urm,marime;
            start=*((int*)p);
            if(start==0) {
                          printf("1 blocks (%d bytes) free\n",b);
                          return 0;
                         }
             else {
                    if(start-4>0) {
                                    nblocks++;
                                    fbytes+=start-4;
                                    }
                    while(*((int*)(p+start))!=0)
                            {
                                urm=*((int*)(p+start));
                                size=*((int*)(p+start+8));
                                marime=urm-size-start;
                                if(marime>0) {
                                             nblocks++;
                                             fbytes+=marime;
                                            }
                                start=*((int*)(p+start));
                            }
                    size=*((int*)(p+start+8));
                    marime=b-start-size;
                    if(marime>0){
                                nblocks++;
                                fbytes+=marime;
                                }
                    printf("%d blocks (%d bytes) free\n",nblocks,fbytes);
                    return 0;

                    }
        }

int showalloc(unsigned char *p,int b)
        {
            int start,nblocks=0,fbytes=0,size,urm,marime;
            start=*((int*)p);
            if(start==0) {
                          printf("FREE %d bytes\n",b);
                          return 0;
                         }
             else { printf("OCCUPIED 4 bytes\n");
                    if(start-4>0) {
                                    printf("FREE %d bytes\n",fbytes+=start-4);
                                    }
                    while(*((int*)(p+start))!=0)
                            {
                                urm=*((int*)(p+start));
                                size=*((int*)(p+start+8));
                                printf("OCCUPIED %d bytes\n",size);
                                marime=urm-size-start;
                                if(marime>0) {
                                                printf("FREE %d bytes\n",marime);
                                             }
                                start=*((int*)(p+start));
                            }
                    size=*((int*)(p+start+8));
                    printf("OCCUPIED %d bytes\n",size);
                    marime=b-start-size;
                    if(marime>0){
                                printf("FREE %d bytes\n",marime);
                                }
                    return 0;

                    }
        }

int showusage(unsigned char *p,int b)
        {
            int start,nblocks=0,obytes=0,size,urm,marime;
            start=*((int*)p);
            if(start==0) {
                          printf("0 blocks (0 bytes) used\n",b);
                          return 0;
                         }
             else {
                    while(*((int*)(p+start))!=0)
                            {
                                nblocks++;
                                obytes+=(*((int*)(p+start+8))-12);
                                start=*((int*)(p+start));
                            }
                    nblocks++;
                    obytes+=(*((int*)(p+start+8))-12);
                    printf("%d blocks (%d bytes) used\n",nblocks,obytes);
                    return 0;

                    }
        }

int showusagee(unsigned char *p,int b)
        {
            int start,nblocks=0,obytes=0,size,urm,marime;
            float eff;
            start=*((int*)p);
            if(start==0) {
                          printf("0\% efficiency\n",b);
                          return 0;
                         }
             else {
                    while(*((int*)(p+start))!=0)
                            {
                                nblocks++;
                                obytes+=(*((int*)(p+start+8))-12);
                                start=*((int*)(p+start));
                            }
                    nblocks++;
                    obytes+=(*((int*)(p+start+8))-12);
                    eff=(float)obytes/(float)(obytes+12*nblocks+4);
                    eff=eff*100;
                    size=(int)eff;
                    printf("%d%% efficiency\n",size);
                    return 0;

                    }
        }

int showusageee(unsigned char *p,int b)
        {
            int start,oblocks=0,fblocks=0,size,urm,marime;
            double frag;
            start=*((int*)p);
            if(start==0) {
                          printf("0%% fragmentation\n",b);
                          return 0;
                         }
             else {
                    if(start-4>0) {
                                    fblocks++;
                                    }
                    while(*((int*)(p+start))!=0)
                            {
                                urm=*((int*)(p+start));
                                size=*((int*)(p+start+8));
                                oblocks++;
                                marime=urm-size-start;
                                if(marime>0) {
                                                fblocks++;
                                             }
                                start=*((int*)(p+start));
                            }
                    size=*((int*)(p+start+8));
                    oblocks++;
                    marime=b-start-size;
                    if(marime>0){
                                fblocks++;
                                }
                    frag=(float)(fblocks-1)/(float)(oblocks);
                    frag=frag*100;
                    size=(int)frag;
                    printf("%d%% fragmentation\n",size);
                    return 0;

                    }
        }
int main()
{
    char s[30],cuv[20];
    int x,y,z,i,*pp,N;
    unsigned char *p;
    gets(s);
    while(strcmp(s,"FINALIZE")!=0)
    {
        if(strncmp(s,"INITIALIZE",10)==0) {sscanf(s,"%s %d",cuv,&x);
                                            p=initializare(p,x);
                                            N=x;
                                          /*  *((int*)p)=4;
                                            *((int*)(p+4))=80;
                                            *((int*)(p+8))=0;
                                            *((int*)(p+12))=20;
                                            *((int*)(p+80))=0;
                                            *((int*)(p+80+4))=4;
                                            *((int*)(p+80+8))=20;*/

                                            }

        if(strcmp(s,"DUMP")==0) {printf("%.8X\t",0);
                                  for(i=0;i<N;i++)
                                     {
                                     if(i%8==0 && i/8%2==1) printf(" ");
                                     if(i%16==0 && i!=0) printf("\n%.8X\t",i);
                                     printf("%.2X ",*(p+i),i);
                                    }
                                 printf("\n%.8X\n",N);
                                }

        if(strncmp(s,"ALLOC",5)==0){sscanf(s,"%s %d",cuv,&x);
                                    printf("%d\n",alloc(p,x,N));
                                    }

        if(strncmp(s,"FREE",4)==0) {sscanf(s,"%s %d",cuv,&x);
                                    elibereaza(p,x);
                                    }

        if(strncmp(s,"FILL",4)==0) {sscanf(s,"%s %d %d %d",cuv,&x,&y,&z);
                                    umple(p,x,y,z);
                                    }
        if(strncmp(s,"SHOW",4)==0) {strcpy(s,s+5);
                                    if(strncmp(s,"FREE",4)==0) {
                                                          showfree(p,N);
                                                          }
                                    if(strncmp(s,"ALLOCATIONS",11)==0){
                                                                      showalloc(p,N);
                                                                      }
                                    if(strncmp(s,"USAGE",5)==0){
                                                                showusage(p,N);
                                                                showusagee(p,N);
                                                                showusageee(p,N);
                                                                }
                                    }

        gets(s);
    }

    free(p);
    return 0;


}
