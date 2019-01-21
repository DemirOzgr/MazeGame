#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// STRUCT  VE STACK OLUSUMU
struct n
{
    int x;
    struct n * sonraki;
    struct n * onceki;
};
typedef struct n dugum;
struct n * ilk=NULL;
struct n * son=NULL;
int durum;
void sil(int aranan)
{
    struct n *p;

    for(p=ilk; p!=NULL; p=p->sonraki)
    {
        if(aranan==p->x)
        {
            if(ilk==p)
            {
                if(ilk->sonraki!=NULL)
                {
                    ilk=p->sonraki;
                    ilk->onceki=NULL;
                }
                else
                {
                    ilk=NULL;
                    son=NULL;
                }
            }
            else
            {
                p->onceki->sonraki=p->sonraki;
                if(p==son)
                    son=son->onceki;
                else
                    p->sonraki->onceki=p->onceki;
            }

        }

    }
    free(p);
}

void sona_ekle(int eklen_sayi)
{

    struct n * yeni;

    if (son == NULL)
    {
        // LISTEDE  ELEMAN YOKSA
        yeni = malloc(sizeof(struct n));
        yeni->x = eklen_sayi;
        // LISTEYE BAGLA
        yeni->sonraki = NULL;
        yeni->onceki = NULL;
        ilk = yeni;
        son = yeni;
    }
    else
    {
        // YENI ELEMAN ICIN YER AL
        yeni = malloc(sizeof(struct n));
        yeni->x = eklen_sayi;

        // YENI ELEMANI LISTENIN SONUNA BAGLA
        yeni->sonraki = NULL;
        yeni->onceki = son;
        son->sonraki = yeni;
        son = yeni;
    }
}
int main ()
{
    srand(time(NULL));
    // MATRIS GIRISI
    int i,j,boyut,x,y,a,b;
    printf("Lutfen Matrisin Boyutunu Giriniz\n");
    scanf("%d",&boyut);
    while(boyut>20)
    {
        printf("Yanlis Boyut Girdiniz (20 Veya Kucuk Bir Deger Giriniz)\n");
        scanf("%d",&boyut);
    }
    boyut=boyut+2;
    int matris[boyut][boyut];
    for(i=0; i<boyut; i++)
    {
        for(j=0; j<boyut; j++)
        {
            matris[i][j]=rand()%2;
        }
    }
    // MATRISIN ETRAFININ CEVRILMESI
    for(i=0; i<boyut; i++)
    {
        for(j=0; j<boyut; j++)
        {
            if(i==0 && j<=boyut-1)
            {
                matris[i][j]=0;
            }
            if(i==boyut-1 && j<=boyut-1)
            {
                matris[i][j]=0;
            }
            if((i>0 && i<boyut-1)&&(j==0 || j==boyut-1))
            {
                matris[i][j]=0;
            }
        }
    }
    printf("OLUSAN MATRIS\n\n");
    for(i=1; i<boyut-1; i++)
    {
        for(j=1; j<boyut-1; j++)
        {
            printf("%3d",matris[i][j]);
        }
        printf("\n");
    }
    //BASLANGIC VE CIKIS GIRISLERININ DOGRULUGU
tekrar:

    printf("\nBaslangic Noktasinin Koordinatlarini Girin\n");
    printf("x : ");
    scanf("%d",&x);
    printf("y : ");
    scanf("%d",&y);
    x++;
    y++;
    if(x==1)
    {
        if((y>boyut-2 || y<1))
        {
            printf("Yanlis deger girdiniz \n");
            goto tekrar;
        }
    }
    if(x==boyut-2)
    {
        if((y>boyut-2 || y<1))
        {
            printf("yanlis deger girdiniz\n");
            goto tekrar;
        }
    }
    if(x>1 && x<boyut-2)
    {
        if(!(y==1 || y==boyut-2))
        {
            printf("yanlis deger girdiniz\n");
            goto tekrar;
        }
    }
    if(matris[x][y]!=1)
    {
        printf("yanlis deger girdiniz\n");
        goto tekrar;
    }
tekrar2:

    printf("\nBitis Noktasinin Koordinatlarini Girin\n");
    printf("a : ");
    scanf("%d",&a);
    printf("b : ");
    scanf("%d",&b);
    a++;
    b++;
    if(a==1)
    {
        if((b>boyut-2 || b<1))
        {
            printf("Yanlis deger girdiniz \n");
            goto tekrar2;
        }
    }
    if(a==boyut-2)
    {
        if((b>boyut-2 || b<1))
        {
            printf("yanlis deger girdiniz\n");
            goto tekrar2;
        }
    }
    if(a>1 && a<boyut-2)
    {
        if(!(b==1 || b==boyut-2))
        {
            printf("yanlis deger girdiniz\n");
            goto tekrar2;
        }
    }
    if(x==a && y==b)
    {
        printf("ayni noktalari sectiniz\n");
        goto tekrar;
    }
    // BAGLI LISTE OLUSUMU
    dugum *root;
    root=NULL;
    root=(dugum*)malloc(sizeof(dugum));
    root->x=matris[x][y];
    dugum *yedek;
    yedek=NULL;
    int t,z;
    t=x;
    z=y;
    while(x!=a || y!=b)
    {
        printf("matris [%d][%d]\n",x,y);
        if(matris[x][y+1]!=1 && matris[x+1][y]!=1 && matris[x-1][y]!=1 && matris[x][y-1]!=1)
        {
            if(x==t && y==t)
            {
                printf("\nBU LABIRENTIN BELIRTILEN DEGERLER ICIN COZUMU YOKTUR\n");
                break;
            }
            matris[x][y]=0;
            son->x=0;
            sil(matris[x][y]);
            if(durum==1)
            {

                y=y-1;
            }
            else if(durum==2)
            {

                y=y+1;
            }
            else if(durum==3)
            {
                x=x-1;
            }
            else if(durum==4)
            {
                x=x+1;
            }
        }
        // BAGLI LISTE ILE DORT YONE ILERLEME
        if(matris[x][y+1]==1)
        {
            matris[x][y]=2;
            sona_ekle(matris[x][y+1]);
            matris[x][y+1]=2;
            y++;
            durum=1;
            printf("saga");

        }
        else if(matris[x+1][y]==1)
        {
            matris[x][y]=2;
            sona_ekle(matris[x+1][y]);
            matris[x+1][y]=2;
            x++;
            durum=3;
            printf("asagi");
        }
        else if(matris[x][y-1]==1)
        {
            matris[x][y]=2;
            sona_ekle(matris[x][y-1]);
            matris[x][y-1]=2;
            y--;
            durum=2;
            printf("sola");
        }
        else if(matris[x-1][y]==1 )
        {
            matris[x][y]=2;
            sona_ekle(matris[x-1][y]);
            matris[x-1][y]=2;
            x--;
            durum=4;
            printf("yukari");
        }
    }
    printf("\nILK HAL\n\n");
    for(i=1; i<boyut-1; i++)
    {
        for(j=1; j<boyut-1; j++)
        {
            printf("%3d",matris[i][j]);
        }
        printf("\n");
    }

    for(i=0; i<boyut; i++)
    {
        for(j=0; j<boyut; j++)
        {
            if(matris[i][j]==1)
                matris[i][j]=0;
            if(matris[i][j]==2)
            {
                matris[i][j]=1;
            }
        }
    }
    printf("\nSON HAL\n\n");
    for(i=1; i<boyut-1; i++)
    {
        for(j=1; j<boyut-1; j++)
        {
            printf("%3d",matris[i][j]);
        }
        printf("\n");
    }
    return 0;
}