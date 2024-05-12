#ifndef MINIMAP_H_INCLUDED
#define MINIMAP_H_INCLUDED


#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

typedef struct 
{
    SDL_Surface *surface_temp;
    SDL_Rect pos_temp;

    TTF_Font *police;
    SDL_Color noir;

    int tempdebut;

    int second, minute;

}Temps;


typedef struct 
{
    SDL_Surface *surface_minimap;
    SDL_Surface *surface_minijoueur;
    

    SDL_Surface *animation[59];

    SDL_Rect pos_minimap;
    SDL_Rect pos_animation;
    SDL_Rect pos_affichage;

    SDL_Rect pos_minijoueur;
    int compteur_animation;
    int compteur_general;

    Temps time;

}Minimap;



typedef struct 
{
    SDL_Surface *img;
    SDL_Rect pos_perso;

    int col_droite,col_gauche,col_up,col_down;

}Personne;








void initmap( Minimap * m);
void afficherminimap (Minimap m, SDL_Surface * screen);
void update_minimap(Minimap *m,SDL_Rect pos_perso,SDL_Rect camera);
SDL_Color GetPixel(SDL_Surface *pSurface, int x, int y);
int collisionPP( Personne *p, SDL_Surface * Masque,SDL_Rect pos_aff);

void init_temp(Temps *t);
void afficher_temp(Temps *t,SDL_Surface *screen);



#endif