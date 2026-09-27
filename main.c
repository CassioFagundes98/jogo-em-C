#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define TAM 15
#define FASES 4
#define MAX_INIMIGOS 5

char labirinto[TAM][TAM];

int bombas = 0;
int bombasArea = 0;

int faseAtual=0;
int jogadorX,jogadorY;
int inimigosX[MAX_INIMIGOS],inimigosY[MAX_INIMIGOS];
int qtdInimigos;

int passos=0,pontos=100;

char mapas[FASES][TAM][TAM] = {

/* FASE 1 */
{
{'@',' ',' ','X',' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' '},
{'X','X',' ','X',' ','X',' ','X',' ','X','X','X','X','X',' '},
{' ',' ',' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' ','X',' '},
{' ','X','X','X',' ','X',' ','X','X','X','X','X',' ','X',' '},
{' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' ','X',' ',' ',' '},
{'X','X',' ','X','X','X','X','X','X','X',' ','X','X','X',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ','X',' ',' ',' ',' ',' '},
{' ','X','X','X','X','X',' ','X',' ','X','X','X','X','X',' '},
{' ',' ',' ',' ',' ','X',' ','X',' ',' ',' ',' ',' ','X',' '},
{' ','X','X','X',' ','X',' ','X','X','X','X','X',' ','X',' '},
{' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' ','X',' ',' ',' '},
{'X','X',' ','X','X','X','X','X','X','X',' ','X','X','X',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ','X',' ',' ',' ',' ',' '},
{' ','X','X','X','X','X','X','X',' ','X','X','X','X','X',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','O'}
},

/* FASE 2 (corrigida pra NÃO travar) */
{
{'@',' ',' ','X',' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' '},
{'X','X',' ','X',' ','X',' ','X',' ','X','X','X','X','X',' '},
{' ',' ',' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' ','X',' '},
{' ','X','X','X',' ','X',' ','X','X','X','X','X',' ','X',' '},
{' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' ','X',' ',' ',' '},
{'X','X',' ','X','X','X','X','X','X','X',' ','X','X','X',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ','X',' ',' ',' ',' ',' '},
{' ','X','X','X','X','X',' ','X',' ','X','X','X','X','X',' '},
{' ',' ',' ',' ',' ','X',' ','X',' ',' ',' ',' ',' ','X',' '},
{' ','X','X','X',' ','X',' ','X','X','X','X','X',' ','X',' '},
{' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' ','X',' ',' ',' '},
{'X','X',' ','X','X','X','X','X','X','X',' ','X','X','X',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ','X',' ',' ',' ',' ',' '},
{' ','X','X','X','X','X','X','X',' ','X','X','X','X','X',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','O'}
},

/* FASE 3 */
{
{'@',' ',' ',' ',' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' '},
{'X','X',' ','X',' ','X',' ','X',' ','X','X','X','X','X',' '},
{' ',' ',' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' ','X',' '},
{' ','X','X','X',' ','X',' ','X','X','X','X','X',' ','X',' '},
{' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' ','X',' ',' ',' '},
{'X','X',' ','X','X','X','X','X','X','X',' ','X','X','X',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ','X',' ',' ',' ',' ',' '},
{' ','X','X','X','X','X',' ','X',' ','X','X','X','X','X',' '},
{' ',' ',' ',' ',' ','X',' ','X',' ',' ',' ',' ',' ','X',' '},
{' ','X','X','X',' ','X',' ','X','X','X','X','X',' ','X',' '},
{' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' ','X',' ',' ',' '},
{'X','X',' ','X','X','X','X','X','X','X',' ','X','X','X',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ','X',' ',' ',' ',' ',' '},
{' ','X','X','X','X','X','X','X',' ','X','X','X','X','X',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','O'}
},

/* FINAL */
{
{'@',' ',' ',' ',' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' '},
{'X','X',' ','X',' ','X',' ','X',' ','X','X','X','X','X',' '},
{' ',' ',' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' ','X',' '},
{' ','X','X','X',' ','X',' ','X','X','X','X','X',' ','X',' '},
{' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' ','X',' ',' ',' '},
{'X','X',' ','X','X','X','X','X','X','X',' ','X','X','X',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ','X',' ',' ',' ',' ',' '},
{' ','X','X','X','X','X',' ','X',' ','X','X','X','X','X',' '},
{' ',' ',' ',' ',' ','X',' ','X',' ',' ',' ',' ',' ','X',' '},
{' ','X','X','X',' ','X',' ','X','X','X','X','X',' ','X',' '},
{' ',' ',' ','X',' ',' ',' ',' ',' ',' ',' ','X',' ',' ',' '},
{'X','X',' ','X','X','X','X','X','X','X',' ','X','X','X',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ','X',' ',' ',' ',' ',' '},
{' ','X','X','X','X','X','X','X',' ','X','X','X','X','X',' '},
{' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','O'}
}

};

/* EXPLOSÃO */
void explodirArea(int x,int y){
    for(int i=-1;i<=1;i++){
        for(int j=-1;j<=1;j++){
            int nx=x+i, ny=y+j;
            if(nx>=0&&nx<TAM&&ny>=0&&ny<TAM){
                if(labirinto[nx][ny]=='X')
                    labirinto[nx][ny]=' ';
            }
        }
    }
}

/* SOM */
void som(int t){
    if(t==1) Beep(800,80);
    if(t==2) Beep(300,150);
    if(t==3){ Beep(1000,150); Beep(1300,150); }
    if(t==4){ Beep(200,400); }
}

/* CARREGAR */
void carregarFase(){
    for(int i=0;i<TAM;i++)
        for(int j=0;j<TAM;j++)
            labirinto[i][j]=mapas[faseAtual][i][j];

    jogadorX=0; jogadorY=0;

    qtdInimigos = faseAtual+1;

    inimigosX[0]=14; inimigosY[0]=14;
    inimigosX[1]=14; inimigosY[1]=0;
    inimigosX[2]=0;  inimigosY[2]=14;
    inimigosX[3]=7;  inimigosY[3]=7;

    /* buffs */
    labirinto[2][2]='B';
    labirinto[10][10]='D';
}

/* DESENHO */
void mostrar(){
    system("cls");

    printf("Fase:%d Passos:%d Pontos:%d B:%d D:%d\n\n",
        faseAtual+1,passos,pontos,bombas,bombasArea);

    for(int i=0;i<TAM;i++){
        for(int j=0;j<TAM;j++){

            int inimigo=0;
            for(int k=0;k<qtdInimigos;k++)
                if(i==inimigosX[k]&&j==inimigosY[k]) inimigo=1;

            if(inimigo) printf("\033[41m M \033[0m");
            else if(labirinto[i][j]=='@') printf("\033[42m @ \033[0m");
            else if(labirinto[i][j]=='O') printf("\033[44m O \033[0m");
            else if(labirinto[i][j]=='X') printf("\033[47m   \033[0m");
            else if(labirinto[i][j]=='B') printf("\033[46m B \033[0m");
            else if(labirinto[i][j]=='D') printf("\033[43m D \033[0m");
            else printf("\033[90m . \033[0m");
        }
        printf("\n");
    }
}

/* IA BFS */
void moverInimigo(int id){

    int visit[TAM][TAM]={0};
    int px[TAM][TAM], py[TAM][TAM];
    int fx[TAM*TAM], fy[TAM*TAM];

    int ini=0,fim=0;

    fx[fim]=inimigosX[id];
    fy[fim]=inimigosY[id];
    visit[inimigosX[id]][inimigosY[id]]=1;
    fim++;

    int dx[4]={1,-1,0,0};
    int dy[4]={0,0,1,-1};

    while(ini<fim){
        int x=fx[ini], y=fy[ini];
        ini++;

        if(x==jogadorX && y==jogadorY){

            while(px[x][y]!=inimigosX[id] || py[x][y]!=inimigosY[id]){
                int tx=px[x][y];
                int ty=py[x][y];
                x=tx; y=ty;
            }

            inimigosX[id]=x;
            inimigosY[id]=y;
            return;
        }

        for(int i=0;i<4;i++){
            int nx=x+dx[i], ny=y+dy[i];

            if(nx>=0&&nx<TAM&&ny>=0&&ny<TAM){
                if(!visit[nx][ny] && labirinto[nx][ny]!='X'){
                    visit[nx][ny]=1;
                    px[nx][ny]=x;
                    py[nx][ny]=y;
                    fx[fim]=nx; fy[fim]=ny;
                    fim++;
                }
            }
        }
    }
}

void moverTodos(){
    for(int i=0;i<qtdInimigos;i++)
        moverInimigo(i);
}

/* MOVIMENTO */
int mover(char d){
    int nx=jogadorX, ny=jogadorY;

    if(d=='w') nx--;
    if(d=='s') nx++;
    if(d=='a') ny--;
    if(d=='d') ny++;

    if(nx<0||nx>=TAM||ny<0||ny>=TAM) return 1;

    /* BUFF */
    if(labirinto[nx][ny]=='B'){ bombas++; som(3); }
    if(labirinto[nx][ny]=='D'){ bombasArea++; som(3); }

    /* PAREDE */
    if(labirinto[nx][ny]=='X'){
        if(bombasArea>0){
            bombasArea--;
            explodirArea(nx,ny);
            som(3);
        }
        else if(bombas>0){
            bombas--;
            labirinto[nx][ny]=' ';
            som(3);
        }
        else{
            pontos-=5;
            som(2);
            return 1;
        }
    }

    labirinto[jogadorX][jogadorY]=' ';
    jogadorX=nx; jogadorY=ny;

    /* VITÓRIA ANTES */
    if(labirinto[jogadorX][jogadorY]=='O'){
        if(faseAtual<FASES-1){
            faseAtual++;
            carregarFase();
            som(3);
            return 1;
        } else{
            mostrar();
            printf("\nZEROU O JOGO\n");
            return 0;
        }
    }

    labirinto[jogadorX][jogadorY]='@';

    /* INIMIGOS */
    moverTodos();

    for(int i=0;i<qtdInimigos;i++){
        if(jogadorX==inimigosX[i] && jogadorY==inimigosY[i]){
            mostrar();
            printf("\nINIMIGO TE PEGOU\n");
            som(4);
            return 0;
        }
    }

    passos++;
    pontos+=2;
    som(1);

    return 1;
}

/* MAIN */
int main(){
    char c;
    int rodando=1;

    carregarFase();

    while(rodando){
        mostrar();
        scanf(" %c",&c);
        rodando=mover(c);
    }

    return 0;
}
