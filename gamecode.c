#include "raylib.h"

typedef struct Player //Estrutura com parâmetros do player e alguns parâmetros fixos dos tiros(como cor e velocidade)
{
    Vector2 nave;
    Vector2 shotspeed;
    Vector2 vel;
    int firerate;
    Color cor_nave;
    Color cor_bala;
    float raio;
}Player;

typedef struct Bala //Estrutura com parâmetros para movimentação dos tiros
{
    Vector2 posicao;
    bool ativa;
}Bala;

/*typedef struct Inimigu//estrutura para fazer os inimigos e futuramente suas balas
{
    Vector2 posicao;
    bool ativa;
    Color cordoini;
    float raio;
}Inimigu*/

static Player jogador = {0};
static Bala bala[50] = {0}; //O vetor bala é necessário pois cada elemento dele é uma bala na tela
//static Inimigu foe[50]={0}//O vetor bala é necessário pois cada elemento dele é um na tela

void creditos()
{   
    while(1)
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("CREDITOS",150,50,70,RAYWHITE);
        DrawText("Lucas Fernandes Lins",70,150,50,RAYWHITE);
        DrawText("Matheus Felipe Lima",70,250,50,RAYWHITE);
        DrawText("Jose Rodrigues Neto",70,350,50,RAYWHITE);
        DrawText("Joao Victor Galdino",70,450,50,RAYWHITE);
        DrawText("Luiz Fernando Barbosa",70,550,50,RAYWHITE);
        DrawText("Pressione S para sair",100,750,20,RAYWHITE);
        EndDrawing();
        if(IsKeyPressed(83))
            break;
        
    }
}


void menuu (Texture2D* bck,Texture2D* nave)
{
    while(1)
        {
        
           int posicaodomousex=GetMouseX();
           int posicaodomousey=GetMouseY(); 
            BeginDrawing();
        
                    ClearBackground(RAYWHITE);
                        
                    //desenhando o fundo
                    DrawTexture(*bck,0,0,RAYWHITE);
                    //DrawText(TextFormat("%i %i",posicaodomousex ,posicaodomousey), 190, 200, 20, LIGHTGRAY); 
                    
                        if (((posicaodomousex>=415)&&(posicaodomousex<=550))&&(posicaodomousey>=570)&&(posicaodomousey<=585))
                        {
                            DrawText("Novo Jogo",400,560,40,LIGHTGRAY);
                            if(IsMouseButtonDown(0))
                                break;
                        }
                        else
                        {
                            DrawText("Novo Jogo",415,570,25,LIGHTGRAY);
                        }
                        if (((posicaodomousex>=415)&&(posicaodomousex<=500))&&(posicaodomousey>=620)&&(posicaodomousey<=635))
                        {
                            DrawText("Créditos",400,610,40,LIGHTGRAY);
                            if(IsMouseButtonDown(0))
                                creditos();
                        }
                        else
                        {
                            DrawText("Créditos",415,620,25,LIGHTGRAY);
                        }
                        if (((posicaodomousex>=415)&&(posicaodomousex<=460))&&(posicaodomousey>=670)&&(posicaodomousey<=695))
                        {
                            DrawText("Sair",400,660,40,LIGHTGRAY);
                            if(IsMouseButtonDown(0))
                            {
                                UnloadTexture(*bck); 
                                UnloadTexture(*nave);    
                                CloseWindow();
                            }
                                
                        }
                        else
                        {
                            DrawText("Sair",415,670,25,LIGHTGRAY);
                        }
        
                
                    
                EndDrawing();
        }
}


void Pause(int* pont)
{   
   
        
        while(1)
        {
            BeginDrawing();
            ClearBackground(BLACK);
            DrawText("PAUSE",150,50,50,RAYWHITE);
            DrawText("Para voltar pressione P",70,150,20,RAYWHITE);
            DrawText("Para ir para o menu pressione M",70,250,20,RAYWHITE);
            EndDrawing();
            if(IsKeyPressed(KEY_P))
                break;
            if(IsKeyPressed('M'))
            {
              (*pont) = 1;
              break;
            }
        }
    
}

void Movimento() //Função de movimentação
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
                    bala[i].posicao.x = jogador.nave.x+20; 
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
    //criando variavel para menu ingame
    int checkmenu=0;
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
    jogador.raio = 10;
    //declarando float de movimento da tela
     float movbackground = 0.0f;
    
    
    //Inicializando janela
    InitWindow(Largura_Tela,Altura_Tela,"Starlight Drift");
    
    //carregando imagens e criando texturas, favor copiar o caminho e copiar
    Image imageyy = LoadImage("/Users/lucas/Pictures/FFXV TRAB/bckatt.png");
    Image background = LoadImage("/Users/lucas/Pictures/FFXV TRAB/space.png");
    ImageResize(&background,720,876);
    Image nave1 = LoadImage("/Users/lucas/Pictures/FFXV TRAB/navee.png");
    ImageResize(&nave1,40,50);
    Texture2D bck = LoadTextureFromImage(imageyy);
    Texture2D nave = LoadTextureFromImage(nave1);
    Texture2D fundo = LoadTextureFromImage(background);
    UnloadImage(background);
    UnloadImage(nave1);
    UnloadImage(imageyy);
    
    SetTargetFPS(60);
    
    while(1)
    {   
      //impedindo loop infinito
        checkmenu=0;
        //funcao menu
        menuu(&bck,&nave);
        
    while(1)
    {
        //Começando a desenhar e chamando as funções
        Movimento();
        if(IsKeyPressed(KEY_P))
            {
                Pause(&checkmenu);
            }
        if(checkmenu==1)
            break;
        movbackground += 3.0; //velocidade do background
        if(movbackground >= background.height) movbackground = 0; //looping do background
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureEx(fundo,(Vector2){0,movbackground},0.0f,1.0f,WHITE);
        DrawTextureEx(fundo,(Vector2){0,-background.height + movbackground},0.0f,1.0f,WHITE);
        //Muito importante
        DrawText("homem negro fodase",Largura_Tela/2,Altura_Tela/2,20,LIGHTGRAY);
        //DrawCircle(jogador.nave.x,jogador.nave.y,8,jogador.cor_nave);
        DrawTexture(nave,jogador.nave.x,jogador.nave.y,RAYWHITE);
        Tiro(jogador,bala,&jogador.firerate);
        
        EndDrawing();
    }
}
    UnloadTexture(bck); 
    UnloadTexture(nave);
    return 0;
}
