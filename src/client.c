#include "../include/global.h"

void * fonc_client(void *i)
{
    argStruct *arg = i;
    AcheterBillet(arg->num);
    
    /* temps de vente */
    //usleep(200000);
    printf("Le client %d à acheté son billet auprès d'une caissière\n", arg->num);
    return 0;
}

void AcheterBillet(int i)
{
    
    pthread_mutex_lock(&mutex_attenteClient);
    nbClientsAttente++;
    pthread_cond_signal(&dormir);
    printf("Le client %d arrive \n",i);
    pthread_cond_wait(&attendre,&mutex_attenteClient);
    choisirFilm(i);
    
    nbClientsAttente --;
    pthread_mutex_unlock(&mutex_attenteClient);
    
}
//le client choisis un film, si il n'y a plus de place il y a 80 % de chance
// pour que le client quitte le cinema, sinon il choisis un autre film.

void choisirFilm(int i)
{
    
    int film = rand()%(NBSalles-0) +0;
    printf("client %d veut voir le film %s\n",i, lesSalles[film]->film);
    if(lesSalles[film]->NBPersonnes==lesSalles[film]->CAPACITE)
    {
        printf("il n'y a plus de place pour le film %s\n",lesSalles[film]->film);
        int random = rand()%(100-0) +0;
        if(random >= 80)
        {
            printf("le client %d va essayer de voir un autre film\n",i);
            choisirFilm(i);
        }
        else{
            printf("le client %d sort du cinema car il n'y avait plus de place pour son film\n",i);
        }
            
        
    }
    else
    {
        printf("client %d à acheté sa place pour le film %s dans la salle %d\n",i,lesSalles[film]->film,lesSalles[film]->numero);
        //Ajouter un mutex pour la capaacité des salles quand il y aura 3 moyens de commander les billets 
        (lesSalles[film]->NBPersonnes)++;
        
    }
    
    
}