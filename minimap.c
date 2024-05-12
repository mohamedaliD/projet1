
#include "minimap.h"

"@param Cette fonction initialise une structure Minimap en chargeant des images pour la minimap, le joueur, et une animation associée, tout en initialisant les positions et les compteurs nécessaires, ainsi qu'une structure de temps."

void initmap( Minimap * m)
{
    m->surface_minimap = IMG_Load("image/minimap.png");
    m->surface_minijoueur = IMG_Load("image/miniperso.png");

    m->pos_minimap.x = 500;
    m->pos_minimap.y = 0 ; 

    m->pos_animation.x = 495;
    m->pos_animation.y = 0;

    m->pos_affichage.x = 0;
    m->pos_affichage.y = 0;
    m->pos_affichage.w = 256;
    m->pos_affichage.h = 144;



    int i = 0;
    char nomimage[50];
    
    for(i=0 ; i<59;i++)
    {
        sprintf(nomimage,"image/animation/%d.png",i);
        m->animation[i] = IMG_Load(nomimage);
        if(m->animation[i] == NULL)
        {
            printf("error laod minimap %d \n",i);
        }
    }

m->compteur_general = 0;
m->compteur_animation = 0;

init_temp(&m->time);

}

"@param Cette fonction affiche la minimap, le joueur et une animation associée sur l'écran à l'aide de la bibliothèque SDL (Simple DirectMedia Layer) en utilisant les surfaces et les positions fournies."
void afficherminimap(Minimap m, SDL_Surface * screen)
{
    
    SDL_BlitSurface(m.surface_minimap,&m.pos_affichage,screen,&m.pos_minimap);
    SDL_BlitSurface(m.surface_minijoueur,NULL,screen,&m.pos_minijoueur);
    SDL_BlitSurface(m.animation[m.compteur_animation],NULL,screen,&m.pos_animation);
}
@param
void update_minimap(Minimap *m,SDL_Rect pos_perso,SDL_Rect camera)
{

m->pos_minijoueur.x = (pos_perso.x * 20 / 100) + m->pos_minimap.x;
m->pos_minijoueur.y = (pos_perso.y * 20 / 100) + m->pos_minimap.y;

printf("camer x = %d \n",camera.x);

m->pos_affichage.x = camera.x * 20 / 100;

m->compteur_general ++;

if(m->compteur_general % 5 == 0)
{
    m->compteur_animation ++;
    if(m->compteur_animation > 58)
    {
        m->compteur_animation = 0;
    }
}



}
"@param Cette fonction met à jour la position du joueur sur la minimap en fonction de sa position dans le jeu, ajuste la position d'affichage de la minimap en fonction de la position de la caméra dans le jeu, et anime la minimap en faisant défiler une série d'images."
void init_temp(Temps *t)
{
    t->pos_temp.x = 10;
    t->pos_temp.y = 10;

    t->police = TTF_OpenFont("font/arial.ttf",20);

    t->noir.r=0;
    t->noir.g = 0;
    t->noir.b = 0;


    t->tempdebut = SDL_GetTicks();
}

"@param Cette fonction affiche le temps écoulé depuis le début du jeu sous forme de minutes et de secondes, et la couleur d'un pixel à une position spécifique sur une surface SDL est récupérée."
void afficher_temp(Temps *t,SDL_Surface *screen)
{
    int temptotal;

    temptotal = (SDL_GetTicks() - t->tempdebut) /1000 ;

    t->minute = (temptotal/60)%60;
    t->second = temptotal % 60;

    char temp[20];
    sprintf(temp,"%d:%d",t->minute,t->second);


    t->surface_temp = TTF_RenderText_Blended(t->police,temp,t->noir);
    if(t->surface_temp == NULL)
    {
        printf("error load text temp \n");
    }

    SDL_BlitSurface(t->surface_temp,NULL,screen,&t->pos_temp);


    

}


SDL_Color GetPixel(SDL_Surface *pSurface, int x, int y)
{
    SDL_Color color = {0, 0, 0, 255};
    if (x < 0 || x >= pSurface->w || y < 0 || y >= pSurface->h) {
        return color;
    }
    Uint32 col=0;
    char *pPosition = (char *) pSurface->pixels;
    pPosition += (pSurface->pitch * (y));
    pPosition += (pSurface->format->BytesPerPixel * (x));
    memcpy(&col, pPosition, pSurface->format->BytesPerPixel);

    SDL_GetRGB(col, pSurface->format, &color.r, &color.g, &color.b);
    return color;
}

"@param Cette fonction détecte les collisions entre un personnage et un masque de collision (Masque) en vérifiant les couleurs des pixels aux positions spécifiées autour du personnage. Elle détermine si le personnage entre en collision avec les bords du masque et met à jour les drapeaux de collision (col_droite, col_gauche, col_up, col_down) en conséquence."
int collisionPP( Personne *p, SDL_Surface * Masque,SDL_Rect pos_aff)
{


    SDL_Rect tout_pos[8];

    tout_pos[0].x  =  p->pos_perso.x + 0 + pos_aff.x;
    tout_pos[0].y  = p->pos_perso.y + 0  + pos_aff.y;

    tout_pos[1].x  = p->pos_perso.x + 60 + pos_aff.x  ;
    tout_pos[1].y  = p->pos_perso.y + 0  + pos_aff.y ;

    tout_pos[2].x  = p->pos_perso.x + 120 + pos_aff.x  ;
    tout_pos[2].y  = p->pos_perso.y + 0   + pos_aff.y;

    tout_pos[3].x  = p->pos_perso.x + 120 + pos_aff.x  ;
    tout_pos[3].y  = p->pos_perso.y + 60  + pos_aff.y ;

    tout_pos[4].x  = p->pos_perso.x + 120 + pos_aff.x ;
    tout_pos[4].y  = p->pos_perso.y + 120 + pos_aff.y ;

    tout_pos[5].x  = p->pos_perso.x + 60 + pos_aff.x  ;
    tout_pos[5].y  = p->pos_perso.y + 120 + pos_aff.y  ;

    tout_pos[6].x  = p->pos_perso.x + 0 + pos_aff.x ;
    tout_pos[6].y  = p->pos_perso.y + 120  + pos_aff.y ;

    tout_pos[7].x  = p->pos_perso.x + 0 + pos_aff.x ;
    tout_pos[7].y  = p->pos_perso.y + 60 + pos_aff.y;


    SDL_Color color_pos[8];

    int i =0;

    for(i=0;i<8;i++)
    {
        color_pos[i] = GetPixel(Masque,tout_pos[i].x,tout_pos[i].y);
    }

    

    if((color_pos[3].r == 0 && color_pos[3].g == 0 && color_pos[3].b == 0))
    {

        p->col_droite =1;
        return 1;
    }
    else
    {
        p->col_droite = 0;
    }

    if((color_pos[7].r == 0 && color_pos[7].g == 0 && color_pos[7].b == 0))
    {

        p->col_gauche =1;
        return 1;
    }
    else
    {
        p->col_gauche = 0;
    }

    if((color_pos[1].r == 0 && color_pos[1].g == 0 && color_pos[1].b == 0))
    {

        p->col_up =1;
        return 1;
    }
    else
    {
        p->col_up = 0;
    }

    if((color_pos[5].r == 0 && color_pos[5].g == 0 && color_pos[5].b == 0))
    {

        p->col_down =1;
        return 1;
    }
    else
    {
        p->col_down = 0;
    }




    return 0;
}
