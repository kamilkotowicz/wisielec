#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define SCIEZKA "slowa.txt"
#define SCIEZKA2 "najl_wyniki.txt"
#define MDS 20
#define MINDS 2
#define MAXDS 15
#define LZ 35
#define P 128
#define ASCI 256
#define LO 8
struct lista{
    char str[MDS];
    struct lista* nast;
};
typedef struct lista* wsk;
char znaki[]="a¹bcædeêfghijkl³mnñoópqrsœtuvwxyzŸ¿";
enum stan{niema=-1,niewiem=0,jest=1};
enum tryby{latwy=0,trudny=1,dwuos=2};
#ifdef _WIN32
#define getc_unlocked getc
#endif
void read_int(int *n){
    register char c = 0;
    while (c < 33) c=getc_unlocked(stdin);
    int poprawne=1;
    (*n) = 0;
    while (c>32) {
        if(c<48||c>57)poprawne=0;
        (*n)=(*n)*10 + (c-48);
        c=getc_unlocked(stdin);
    }
    if(!poprawne)(*n)=-1;
}
void problem_z_plikiem(){
    printf("Nie mogê otworzyæ pliku\n");
    exit(0);
}
int rozmiar_listy(wsk poc){
    int rozmiar=0;
    while(poc!=NULL){
        ++rozmiar;
        poc=poc->nast;
    }
    return rozmiar;
}
char* lista_od(wsk poc,int i){
    while(i>0){
        --i;
        poc=poc->nast;
    }
    return poc->str;
}
wsk dodaj_do_listy(wsk poc,char* dane){
    wsk nowy=(wsk)malloc(sizeof(struct lista));
    nowy->nast = NULL;
    strcpy((*nowy).str,dane);
    if(poc!=NULL)nowy->nast=poc;
    poc=nowy;
    return poc;
}
wsk poczatkowa_lista(wsk poc,int dl){
    FILE* fin=fopen(SCIEZKA,"r");
    if(fin==NULL)problem_z_plikiem();
    char str[MDS];
    while(fgets(str,MDS,fin)!=NULL){
        if(strlen(str)-1==dl){
            poc=dodaj_do_listy(poc,str);
        }
    }
    fclose(fin);
    return poc;
}
wsk wyczysc_liste(wsk poc){
    while(poc!=NULL){
        wsk nowy=poc->nast;
        free(poc);
        poc=nowy;
    }
    return poc;
}
wsk kopiuj_liste(wsk dokad,wsk skad){
    dokad=wyczysc_liste(dokad);
    while(skad!=NULL){
        dokad=dodaj_do_listy(dokad,skad->str);
        skad=skad->nast;
    }
    return dokad;
}
void wczytaj_najlepsze_wyniki(int wyniki[][3]){
    FILE* fin=fopen(SCIEZKA2,"r");
    if(fin==NULL)problem_z_plikiem();
    for(int i=MINDS;i<=MAXDS;++i){
        int x,y,z;
        fscanf(fin,"%d%d%d",&x,&y,&z);
        wyniki[i][0]=x;
        wyniki[i][1]=y;
        wyniki[i][2]=z;
    }
    fclose(fin);
}
void aktualizuj_najlepsze_wyniki(int dl,int maxhp,int tryb){
    if(dl<MINDS||dl>MAXDS)return;
    int wyniki[MAXDS+1][3];
    wczytaj_najlepsze_wyniki(wyniki);
    FILE* fout=fopen(SCIEZKA2,"w");
    if(fout==NULL)problem_z_plikiem();
    if(wyniki[dl][tryb]>maxhp)wyniki[dl][tryb]=maxhp;
    for(int i=MINDS;i<=MAXDS;++i){
        fprintf(fout,"%d\n",wyniki[i][0]);
        fprintf(fout,"%d\n",wyniki[i][1]);
        fprintf(fout,"%d\n",wyniki[i][2]);
    }
    fclose(fout);
}
void pokaz_tryb(int wyniki[][3],int tryb){
    for(int i=MINDS;i<=MAXDS;++i){
        if(i<10)printf("%d   ",i);
        else printf("%d  ",i);
        if(wyniki[i][tryb]<10)printf("  %d\n",wyniki[i][tryb]);
        else if(wyniki[i][tryb]<=LZ)printf(" %d\n",wyniki[i][tryb]);
        else printf("---\n");
    }
}
void pokaz_najlepsze_wyniki(){
    int wyniki[MAXDS+1][3];
    wczytaj_najlepsze_wyniki(wyniki);
    printf("Tryb ³atwy\n");
    printf("d³ugoœæ s³owa\tnajmniejsza liczba potrzebnych ¿yæ\n");
    pokaz_tryb(wyniki,latwy);
    printf("Tryb trudny\n");
    printf("d³ugoœæ s³owa\tnajmniejsza liczba potrzebnych ¿yæ\n");
    pokaz_tryb(wyniki,trudny);
    printf("Tryb dwuosobowy\n");
    printf("d³ugoœæ s³owa\tnajmniejsza liczba potrzebnych ¿yæ\n");
    pokaz_tryb(wyniki,dwuos);
}
void resetuj_najlepsze_wyniki(){
    char c='n';
    printf("STRACISZ WSZYSTKIE NAJLEPSZE WYNIKI\nCzy na pewno chcesz je usun¹æ?(t/n)\n");
    scanf("%c",&c);
    if(c!='t')return;
    FILE* fout=fopen(SCIEZKA2,"w");
    if(fout==NULL)problem_z_plikiem();
    for(int i=MINDS;i<=MAXDS;++i){
        fprintf(fout,"%d\n%d\n%d\n",LZ+1,LZ+1,LZ+1);
    }
    fclose(fout);
}
void rysuj_wisielca(int hp,int maxhp){
    double stos=1-(double)(hp)/(double)(maxhp);
    int nr=stos*(double)(LO-1);
    switch(nr){
        case 0:
        {
            puts( "  ___" );
            puts( " |   " );
            puts( " |   " );
            puts( " |   " );
            puts( " |   " );
            puts( " |   " );
            puts( "---  " );
            break;
        }
        case 1:
        {
            puts( "  ___" );
            puts( " |  &" );
            puts( " |   " );
            puts( " |   " );
            puts( " |   " );
            puts( " |   " );
            puts( "---  " );
            break;
        }
        case 2:
        {
            puts( "  ___" );
            puts( " |  &" );
            puts( " |  O" );
            puts( " |   " );
            puts( " |   " );
            puts( " |   " );
            puts( "---  " );
            break;
        }
        case 3:
        {
            puts( "  ___" );
            puts( " |  &" );
            puts( " |  O" );
            puts( " | / " );
            puts( " |   " );
            puts( " |   " );
            puts( "---  " );
            break;
        }
        case 4:
        {
            puts( "  ___" );
            puts( " |  &" );
            puts( " |  O" );
            puts( " | /|" );
            puts( " |   " );
            puts( " |   " );
            puts( "---  " );
            break;
        }
        case 5:
        {
            puts( "  ___  " );
            puts( " |  &  " );
            puts( " |  O  " );
            puts( " | /|\\" );
            puts( " |     " );
            puts( " |     " );
            puts( "---    " );
            break;
        }
        case 6:
        {
            puts( "  ___  " );
            puts( " |  &  " );
            puts( " |  O  " );
            puts( " | /|\\" );
            puts( " | /   " );
            puts( " |     " );
            puts( "---    " );
            break;
        }
        default:
        {
            puts( "  ___  " );
            puts( " |  &  " );
            puts( " |  O  " );
            puts( " | /|\\" );
            puts( " | / \\" );
            puts( " |     " );
            puts( "---    " );
            break;
        }
    }
}
int kod_wzorca(char* str,int dl,char lit){
    int wyn=0;
    for(int i=0;i<dl;++i)if(str[i]==lit)wyn+=(1<<i);
    return wyn;
}
void dekodowanie_wzorca(int stan,int dl,char* stan_pozycji,int* nieodgadniete,char lit){
    for(int i=0;i<dl;++i){
        if(((stan>>i)&1)==1){
            stan_pozycji[i]=lit;
            --(*nieodgadniete);
        }
    }
}
void kopiowanie_stanow(int* stan_litery,char* stan_pozycji,int dl,int* sstan_litery,char* sstan_pozycji){
    for(int i=0;i<LZ;++i)stan_litery[znaki[i]+P]=sstan_litery[znaki[i]+P];
    for(int i=0;i<dl;++i)stan_pozycji[i]=sstan_pozycji[i];
}
char najczestsza_litera(wsk poc,int dl,int*stan_litery,int* nr){
    char lit;
    int zlicz[ASCI];
    int kiedy[ASCI];
    for(int i=0;i<LZ;++i){
        zlicz[znaki[i]+P]=0;
        kiedy[znaki[i]+P]=-1;
    }
    (*nr)=0;
    while(poc!=NULL){
        char s[MDS];
        strcpy(s,poc->str);
        for(int i=0;i<dl;++i){
            if(kiedy[s[i]+P]!=(*nr)){
                ++zlicz[s[i]+P];
                kiedy[s[i]+P]=(*nr);
            }
        }
        poc=poc->nast;
        ++(*nr);
    }
    int najw=-1;
    for(int i=0;i<LZ;++i){
        if(zlicz[znaki[i]+P]>najw&&stan_litery[znaki[i]+P]==niewiem){
            najw=zlicz[znaki[i]+P];
            lit=znaki[i];
        }
    }
    return lit;
}
int komp(const void * a, const void * b){
    int _a = *(int*)a;
    int _b = *(int*)b;
    if(_a < _b) return -1;
    else if(_a == _b) return 0;
    else return 1;
}
int najczestszy_wzorzec(wsk poc,int dl,char lit,int* wzorce,int ile_slow){
    int nr=0;
    while(poc!=NULL){
        int kod=kod_wzorca(poc->str,dl,lit);
        wzorce[nr]=kod;
        ++nr;
        poc=poc->nast;
    }
    qsort(wzorce, ile_slow, sizeof(int),komp);
    int najl=-1;
    int najw=-1;
    int ost=-1;
    int aktw=-1;
    for(int i=0;i<ile_slow;++i){
        if(wzorce[i]!=0){
            if(wzorce[i]!=ost){
                ost=wzorce[i];
                aktw=1;
            }
            else ++aktw;
            if(aktw>najw){
                najw=aktw;
                najl=ost;
            }
        }
    }
    return najl;
}
void stworz_podlisty(wsk poc,int* wzorce,wsk* nie,int* sznie,int* wz,wsk* tak,int* sztak,int dl,char lit){
    while(poc!=NULL){
        int kod=kod_wzorca(poc->str,dl,lit);
        if(kod==0){
            (*nie)=dodaj_do_listy((*nie),poc->str);
            ++(*sznie);
        }
        else if(kod==(*wz)){
            (*tak)=dodaj_do_listy((*tak),poc->str);
            ++(*sztak);
        }
        poc=poc->nast;
    }
}
void podzial(int* stan_litery,char* stan_pozycji,int dl,int* sstan_litery,char* sstan_pozycji,wsk poc,int* sznie,int* sztak,char* lit,wsk* nie, wsk* tak,int* wz,char l){
    kopiowanie_stanow(stan_litery,stan_pozycji,dl,sstan_litery,sstan_pozycji);
    int ile_slow;
    if(l=='?')(*lit)=najczestsza_litera(poc,dl,stan_litery,&ile_slow);
    else{
        (*lit)=l;
        ile_slow=rozmiar_listy(poc);
    }
    int* wzorce=(int*)malloc(ile_slow*sizeof(int));
    (*wz)=najczestszy_wzorzec(poc,dl,*lit,wzorce,ile_slow);
    (*nie)=NULL;
    (*tak)=NULL;
    (*sznie)=0;
    (*sztak)=0;
    stworz_podlisty(poc,wzorce,nie,sznie,wz,tak,sztak,dl,(*lit));
    free(wzorce);
}
int analizuj(wsk poc,int dl,int* sstan_litery,char* sstan_pozycji,int hp,int nieodgadniete){
    if(nieodgadniete==0)return 1;
    if(hp==0)return -1;
    int stan_litery[ASCI];
    char stan_pozycji[MDS],lit;
    int sznie,sztak,wz;
    wsk nie,tak;
    podzial(stan_litery,stan_pozycji,dl,sstan_litery,sstan_pozycji,poc,&sznie,&sztak,&lit,&nie,&tak,&wz,'?');
    if(sztak+sznie==0)return 1;
    if(sznie>0){
        stan_litery[lit+P]=niema;
        int wyn=analizuj(nie,dl,stan_litery,stan_pozycji,hp-1,nieodgadniete);
        if(wyn<=0)return wyn;
    }
    if(sztak>0){
        stan_litery[lit+P]=jest;
        dekodowanie_wzorca(wz,dl,stan_pozycji,&nieodgadniete,lit);
        int wyn=analizuj(tak,dl,stan_litery,stan_pozycji,hp,nieodgadniete);
        if(wyn<=0)return wyn;
    }
    return 1;
}
int analizuj_root(wsk* spoc,int dl,int* sstan_litery,char* sstan_pozycji,char l,int hp,int nieodgadniete){
    int stan_litery[ASCI];
    char stan_pozycji[MDS],lit;
    int sznie,sztak,wz;
    wsk nie;
    wsk tak;
    podzial(stan_litery,stan_pozycji,dl,sstan_litery,sstan_pozycji,(*spoc),&sznie,&sztak,&lit,&nie,&tak,&wz,l);
    if(sznie>0){
        stan_litery[lit+P]=niema;
        int wyn=analizuj(nie,dl,stan_litery,stan_pozycji,hp-1,nieodgadniete);
        if(wyn<=0){
            (*spoc)=kopiuj_liste((*spoc),nie);
            return 0;
        }
    }
    if(sztak>0){
        stan_litery[lit+P]=jest;
        dekodowanie_wzorca(wz,dl,stan_pozycji,&nieodgadniete,lit);
        int wyn=analizuj(tak,dl,stan_litery,stan_pozycji,hp,nieodgadniete);
        if(wyn<=0){
            (*spoc)=kopiuj_liste((*spoc),tak);
            return wz;
        }
    }
    if(sznie>=sztak){
        (*spoc)=kopiuj_liste((*spoc),nie);
        return 0;
    }
    if(sztak==0){
        (*spoc)=kopiuj_liste((*spoc),nie);
        return 0;
    }
    if(sznie==0){
        (*spoc)=kopiuj_liste((*spoc),tak);
        return wz;
    }
    if(rand()%2==0){
        (*spoc)=kopiuj_liste((*spoc),nie);
        return 0;
    }
    (*spoc)=kopiuj_liste((*spoc),tak);
    return wz;
}
void trudny_tryb(wsk* poc,int dl,int* stan_litery,char* stan_pozycji,char lit,int* hp,int* nieodgadniete){
    if(stan_litery[lit+P]==niewiem){
        int decyzja=analizuj_root(poc,dl,stan_litery,stan_pozycji,lit,*hp,*nieodgadniete);
        if(decyzja==0){
            stan_litery[lit+P]=niema;
            --(*hp);
        }
        else if(decyzja>0){
            stan_litery[lit+P]=jest;
            dekodowanie_wzorca(decyzja,dl,stan_pozycji,nieodgadniete,lit);
        }
    }
    else --(*hp);
}
void latwy_tryb(char* sl,int dl,int* stan_litery,char* stan_pozycji,char lit,int* hp,int* nieodgadniete){
    if(stan_litery[lit+P]==niewiem){
        for(int i=0;i<dl;++i){
            if(sl[i]==lit){
                stan_litery[lit+P]=jest;
                stan_pozycji[i]=lit;
                --(*nieodgadniete);
            }
        }
        if(stan_litery[lit+P]==niewiem){
            stan_litery[lit+P]=niema;
            --(*hp);
        }
    }
    else --(*hp);
}
void wygrana(char* klucz,int dl,int maxhp,int tryb){
    printf("Gratulacje! Wygra³eœ grê! \nWybrane s³owo to: %s\n\n",klucz);
    aktualizuj_najlepsze_wyniki(dl,maxhp,tryb);
}
void przegrana(char* klucz){
    printf("Niestety przegra³eœ. Nastêpnym razem Ci siê uda.\nWybrane s³owo to: %s\n\n",klucz);
}
void zwykla_gra(int dl,int hp,int tryb){
    wsk poc=NULL;
    poc=poczatkowa_lista(poc,dl);
    char* sl=(char*)malloc(MDS*sizeof(char));
    if(tryb==latwy){
        int los_ind=rand()%rozmiar_listy(poc);
        free(sl);
        sl=lista_od(poc,los_ind);
    }
    else if(tryb==dwuos){
        printf("Podaj s³owo, które drugi gracz ma odgadn¹æ\n");
        fgets(sl,MDS,stdin);
        fflush(stdin);
        dl=strlen(sl)-1;
    }
    int nieodgadniete=dl;
    int stan_litery[ASCI];
    char stan_pozycji[MDS];
    for(int i=0;i<dl;++i)stan_pozycji[i]=0;
    for(int i=0;i<LZ;++i)stan_litery[znaki[i]+P]=niewiem;
    system("cls");
    int maxhp=hp;
    while(nieodgadniete>0&&hp>0){
        char lit=' ';
        printf("Podaj literê\n");
        while((lit<'a'||lit>'z')&&lit!='³'&&lit!='¹'&&lit!='œ'&&lit!='ê'&&lit!='¿'&&lit!='ó'&&lit!='ñ'&&lit!='æ'&&lit!='Ÿ')scanf("%c",&lit);
        if(tryb!=trudny)latwy_tryb(sl,dl,stan_litery,stan_pozycji,lit,&hp,&nieodgadniete);
        else trudny_tryb(&poc,dl,stan_litery,stan_pozycji,lit,&hp,&nieodgadniete);
        system("cls");
        for(int i=0;i<dl;++i){
            if(stan_pozycji[i]==0)printf("?");
            else printf("%c",stan_pozycji[i]);
        }
        printf("\n\nB³êdne litery: ");
        for(int i=0;i<LZ;++i)if(stan_litery[znaki[i]+P]==niema)printf("%c,",znaki[i]);
        printf("\nPozosta³e ¿ycia: %d\n",hp);
        rysuj_wisielca(hp,maxhp);
    }
    if(tryb==trudny){
        int sss=rozmiar_listy(poc);
        if(sss>0){
            int los_ind=rand()%rozmiar_listy(poc);
            free(sl);
            sl=lista_od(poc,los_ind);
        }
    }
    if(nieodgadniete==0)wygrana(sl,dl,maxhp,tryb);
    else przegrana(sl);
    poc=wyczysc_liste(poc);
    if(tryb==dwuos)free(sl);
}
void wczytaj_hp(int* hp){
    while((*hp)<1||(*hp)>LZ){
        printf("Podaj pocz¹tkow¹ liczbê ¿yæ\n");
        read_int(hp);
    }
}
void gra_z_komputerem(){
    int lv=0,dl=0,hp=0;
    while(lv<1||lv>3){
        printf("Wybierz poziom trudnoœci\n1 - ³atwy\n2 - trudny\n3 - wróæ do menu\n");
        read_int(&lv);
    }
    if(lv==3)return;
    while(dl<MINDS||dl>MAXDS){
        printf("Podaj d³ugoœæ s³owa\n");
        read_int(&dl);
    }
    wczytaj_hp(&hp);
    if(lv==1)zwykla_gra(dl,hp,latwy);
    else if(lv==2)zwykla_gra(dl,hp,trudny);
}
void gra_na_2_osoby(){
    char c='n';
    printf("Czy rozpocz¹æ grê na 2 osoby?(t/n)\n");
    scanf("%c",&c);
    if(c!='t')return;
    int hp=0;
    wczytaj_hp(&hp);
    zwykla_gra(0,hp,dwuos);
}
void menu(){
    int tryb=0;
    while(tryb<1||tryb>4){
        printf("Gra w wisielca\n1 - gra z komputerem\n2 - gra na 2 osoby\n3 - najlepsze wyniki\n4 - resetuj najlepsze wyniki\n");
        read_int(&tryb);
    }
    system("cls");
    if(tryb==1)gra_z_komputerem();
    else if(tryb==2)gra_na_2_osoby();
    else if(tryb==3)pokaz_najlepsze_wyniki();
    else if(tryb==4)resetuj_najlepsze_wyniki();
}
int main(){
    system("chcp 1250");
    system("cls");
    srand(time(NULL));
    for(;;)menu();
    return 0;
}
