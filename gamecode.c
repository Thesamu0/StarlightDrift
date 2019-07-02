#include "raylib.h"

typedef struct Player //Estrutura com parâmetros do player e alguns parâmetros fixos dos tiros(como cor e velocidade)
{
    Vector2 nave;
    Vector2 shotspeed;
    Vector2 vel;
    int firerate;
    Color cor_nave;
    Color cor_bala;
}Player;

typedef struct Bala //Estrutura com parâmetros para movimentação dos tiros
{
    Vector2 posicao;
    bool ativa;
}Bala;

static Player jogador = {0};
static Bala bala[50] = {0}; //O vetor bala é necessário pois cada elemento dele é uma bala na tela


void Movimento(void) //Função de movimentação
{
    if(IsKeyDown('W'))
    {
        jogador.nave.y -= jogador.vel.y;
    }
    if(IsKeyDown('A'))
    {
        jogador.nave.x -= jogador.vel.x;
    }
    if(IsKeyDown('S'))
    {
        jogador.nave.y += jogador.vel.y;
    }
    if(IsKeyDown('D'))
    {
        jogador.nave.x += jogador.vel.x;
    }
}

void Tiro(Player jogador,Bala bala[50],int* firerate)
{
    if(IsKeyDown(KEY_SPACE)) //Se a barra de espaço está apertada, os tiros saem
    {
        (*firerate)+=5; //A cada frame esse valor aumenta em 5, quando chegar em 20 uma bala é atirada (1 bala a cada 4 frames, pode ser alterado)
        if((*firerate) == 20)
        {
            for(int i = 0;i<50;i++)
            {
                if(!bala[i].ativa)
                {
                    //A bala inicia na posição do player, na "ponta da frente"
                    bala[i].posicao.x = jogador.nave.x; 
                    bala[i].posicao.y = jogador.nave.y - 8;
                    bala[i].ativa = true;
                    break;
                }
            }
            (*firerate) = 0;
        }
    }
    for(int i = 0;i<50;i++)
    {
        if(bala[i].posicao.y>0 && bala[i].ativa)
        {
            //A bala se movimenta de acordo com a "shotspeed(Velocidade do tiro)"
            bala[i].posicao.y -= jogador.shotspeed.y;
            DrawCircle(bala[i].posicao.x,bala[i].posicao.y,3,jogador.cor_bala);
        }
        if(bala[i].posicao.y<0)
        {
            //Se a bala sair da tela, ela fica inativa(pra poupar memória e pra ele poder ser "atirada de novo")
            bala[i].ativa = false;
        }
    }
        
}

int main(void)
{
    //Definindo resolução da tela
    const int Largura_Tela = 720;
    const int Altura_Tela = 876;
    
    //Definindo parâmetros do player(e alguns dos tiros do player)
    jogador.nave.x = 300;
    jogador.nave.y = 650;
    jogador.firerate = 0;
    jogador.vel.x = 8;
    jogador.vel.y = 8;
    jogador.shotspeed.x = 15;
    jogador.shotspeed.y = 15;
    jogador.cor_nave = BLACK;
    jogador.cor_bala = ORANGE;
    
    //Inicializando janela
    InitWindow(Largura_Tela,Altura_Tela,"Starlight Drift");
    
    //carregando imagens e criando texturas, favor copiar o caminho e copiar
    Image imageyy = LoadImage("/Users/lucas/Pictures/FFXV TRAB/bckok.png");
    ImageResize (&imageyy,720,876);
    Texture2D bck = LoadTextureFromImage(imageyy);
    UnloadImage(imageyy);
    
    SetTargetFPS(60);
    
    
    //funcao menu
    while(1)
        {
        
           int posicaodomousex=GetMouseX();
           int posicaodomousey=GetMouseY(); 
            BeginDrawing();
        
                    ClearBackground(RAYWHITE);
                        
                    //desenhando o fundo
                    DrawTexture(bck,0,0,RAYWHITE);
                    DrawText(TextFormat("%i %i",posicaodomousex ,posicaodomousey), 190, 200, 20, LIGHTGRAY); 
                    
                        if (((posicaodomousex>=415)&&(posicaodomousex<=550))&&(posicaodomousey>=550)&&(posicaodomousey<=565))
                        {
                            DrawText("Novo Jogo",400,540,40,LIGHTGRAY);
                            if(IsMouseButtonDown(0))
                                break;
                        }
                        else
                        {
                            DrawText("Novo Jogo",415,550,25,LIGHTGRAY);
                        }
                        if (((posicaodomousex>=415)&&(posicaodomousex<=500))&&(posicaodomousey>=600)&&(posicaodomousey<=620))
                        {
                            DrawText("Créditos",400,590,40,LIGHTGRAY);
                        }
                        else
                        {
                            DrawText("Créditos",415,600,25,LIGHTGRAY);
                        }
                        if (((posicaodomousex>=415)&&(posicaodomousex<=450))&&(posicaodomousey>=650)&&(posicaodomousey<=665))
                        {
                            DrawText("Sair",400,640,40,LIGHTGRAY);
                            if(IsMouseButtonDown(0))
                                CloseWindow();//
                        }
                        else
                        {
                            DrawText("Sair",415,650,25,LIGHTGRAY);
                        }
        
                
                    
                EndDrawing();
        }
        
    while(!WindowShouldClose())
    {
        //Começando a desenhar e chamando as funções
        BeginDrawing();
        Movimento();
        Tiro(jogador,bala,&jogador.firerate);
        ClearBackground(RAYWHITE);
        //Muito importante
        DrawText("homem negro fodase",Largura_Tela/2,Altura_Tela/2,20,LIGHTGRAY);
        DrawCircle(jogador.nave.x,jogador.nave.y,8,jogador.cor_nave);
        
        EndDrawing();
    }
    UnloadTexture(bck); 
    return 0;
}
