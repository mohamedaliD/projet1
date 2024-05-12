@file main.c
@brief main program.
@author mohamedali
@version 1.0
@date Apr 06, 2024
#include <stdio.h>
#include <stdlib.h>


#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "minimap.h"







int main()
{

TTF_Init();
SDL_Init(SDL_INIT_EVERYTHING);


SDL_Surface *ecran;
ecran = SDL_SetVideoMode(1280,720,32,SDL_HWSURFACE);
int quitter=1;
SDL_Event event;


SDL_Surface *background;
background = IMG_Load("image/background.png");
SDL_Rect pos_aff;
pos_aff.x =0;
pos_aff.y=0;
pos_aff.w=1280;
pos_aff.h=720;

SDL_Surface *masque;
masque = IMG_Load("image/backgroundMasque.png");




Personne perso;

perso.img = IMG_Load("perso.png");
perso.pos_perso.x = 0;
perso.pos_perso.y = 560;
perso.pos_perso.w = 120;
perso.pos_perso.h = 120;



Minimap map;
initmap(&map);



SDL_EnableKeyRepeat(50,50);

while(quitter == 1)
{

    SDL_BlitSurface(background,&pos_aff,ecran,NULL);

    SDL_BlitSurface(perso.img,NULL,ecran,&perso.pos_perso);
    afficherminimap(map,ecran);
    afficher_temp(&map.time,ecran);
    SDL_Flip(ecran);



    if(SDL_PollEvent(&event)){
        switch (event.type)
        {
        case SDL_QUIT:
                quitter=0;
            break;
        case SDL_KEYDOWN:
               if(event.key.keysym.sym == SDLK_LEFT)
               {
                    if(perso.col_gauche == 0){
                        perso.pos_perso.x -=10;
                        if(perso.pos_perso.x > 0 && pos_aff.x> 0)
                        {
                            pos_aff.x -= 10;
                            perso.pos_perso.x +=10;
                        }
                    }
               }
               if(event.key.keysym.sym == SDLK_RIGHT)
               {

                if(perso.col_droite == 0){
                 perso.pos_perso.x +=10;
                 if(perso.pos_perso.x > 680)
                 {
                     pos_aff.x += 10;
                     perso.pos_perso.x -=10;
                 }
                }
                else
                {
                    printf(" you can't move there is collision \n");
                }


               }
               if(event.key.keysym.sym == SDLK_UP)
               {
                if(perso.col_up == 0){
                    perso.pos_perso.y -=10;
                }
               }
               if(event.key.keysym.sym == SDLK_DOWN)
               {
                if(perso.col_down == 0){
                    perso.pos_perso.y +=10;
                }
               }
            break;

        default:
            break;
        }
    }

    update_minimap(&map,perso.pos_perso,pos_aff);
    
    collisionPP(&perso,masque,pos_aff);

    printf( " col d : %d | col g : %d |  col up %d | col down: %d \n",perso.col_droite,perso.col_gauche,perso.col_up,perso.col_down );


}
}
