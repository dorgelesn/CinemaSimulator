#include "../include/global.h"
#define Salle SalleStruct

void * fonc_client(void *i)
{

    argStruct *arg = i;
    //50% des clients vont au caisses et 50% vont au caisses automatiques
    Salle * maSalle=NULL;
    
    int random = rand()%(100-0) +0;
    printf("Le client %d arrive \t",arg->num);
    if((random<pourcentageDePersonnesAuCaisses)&&(Nbcaisses!=0))
    {
        maSalle=AcheterBillet(arg->num);
        printf("Le client %d à acheté son billet auprès d'une caissière\n", arg->num);
    }
    else if((random<(pourcentageDePersonnesAuCaissesAuto+pourcentageDePersonnesAuCaisses))&&(NbcaissesAuto!=0))
    {
        maSalle=AcheterBilletAuto(arg->num);
        printf("Le client %d à acheté son billet à la caisse automatique\n", arg->num);
    }
    else
    {
        maSalle=AcheterBilletInternet(arg->num);
        printf("Le client %d à acheté son billet sur internet\n", arg->num);
    }
    checkFileDattente();
    allerVoirFilm(maSalle, arg, "client");
    printf("Le client %d sort du cinema\n", arg->num);
    
    
    /* temps de vente */
    //usleep(200000);
    return 0;
}
void checkFileDattente(){
    pthread_mutex_lock(&mutex_attenteClient);
    
    if(nbClientsAttenteAuto==0 && nbClientsAttente==0 &&nbClientInternet==0 &&nbAbonneeAttente==0 && passed==0)
    {

        ListeSalle l = lesSallesList;
        do{
            pthread_cond_broadcast(&(demarrer));
            l=l->nxt;
        }while(l!=NULL);
    }
    
    pthread_mutex_unlock(&mutex_attenteClient);
    
}

Salle * AcheterBilletInternet(int i)
{
    
    pthread_mutex_lock(&mutex_attenteClient);
    nbClientInternet++;
    Salle * laSalle=NULL;
    printf("Le client %d fait son achat sur internet \n",i);
    laSalle=choisirFilm(i);
    nbClientInternet--;
    //checkFileDattente();
    pthread_mutex_unlock(&mutex_attenteClient);
    return  laSalle;
    
}

Salle * AcheterBillet(int i)
{
    
    pthread_mutex_lock(&mutex_attenteClient);
    Salle * laSalle=NULL;
    nbClientsAttente++;
    pthread_cond_signal(&dormir);
    printf("Le client %d arrive \n",i);
    pthread_cond_wait(&attendre,&mutex_attenteClient);
    laSalle=choisirFilm(i);
    
    nbClientsAttente --;
    //checkFileDattente();
    pthread_mutex_unlock(&mutex_attenteClient);
    return  laSalle;
    
}

Salle * AcheterBilletAuto(int i)
{
    
    pthread_mutex_lock(&mutex_attenteClient);
    Salle * laSalle=NULL;
    nbClientsAttenteAuto++;
    pthread_cond_signal(&dormirAuto);
    printf("Le client %d arrive en caisse automatique\n",i);
    pthread_cond_wait(&attendreAuto,&mutex_attenteClient);
    laSalle=choisirFilm(i);
    
    nbClientsAttenteAuto --;
    //checkFileDattente();
    pthread_mutex_unlock(&mutex_attenteClient);
    return  laSalle;
    
}

//le client choisis un film, si il n'y a plus de place il y a 80 % de chance
// pour que le client quitte le cinema, sinon il choisis un autre film.

Salle * choisirFilm(int i)
{
    
    int film = rand()%(NBFilms-0) +0;
    printf("client %d veut voir le film %s\n",i, lesFilms[film]->titre);
    SalleStruct * laSalle = NULL;
    laSalle = choixSalle(lesFilms[film]);
    
    if(laSalle == NULL)
    {
        printf("il n'y a plus de place pour le film %s\n",lesFilms[film]->titre);
        lesFilms[film]->NbPlaceRefuse++;
        if(lesFilms[film]->NbPlaceRefuse>=LimiteRefusPlace)
        {
            lesFilms[film]->NbPlaceRefuse=0;
            if(NBSalles < NbSalleMax)
            {
                SalleStruct * uneSalle = malloc(sizeof(SalleStruct));
                uneSalle->film=lesFilms[film];
                uneSalle->numero=NBSalles+1;
                uneSalle->CAPACITE = 80;
                uneSalle->NBPersonnes=0;
                pthread_cond_init(&(uneSalle->conditionEntrerSalle),NULL);
                pthread_cond_init(&(uneSalle->filmTermine),NULL);
                pthread_cond_init(&(uneSalle->demarrer),NULL);
                pthread_cond_init(&(uneSalle->toutLemondeDansLaSalle),NULL);
                pthread_cond_init(&(uneSalle->toutLemondeEstSorti),NULL);
                printf("UneSalle à été ajoutée : \n");
                lesSallesList=ajouterSalle(lesSallesList,uneSalle);
                afficherSalles();
                printf("client %d à acheté sa place pour le film %s dans la salle %d à la place %d\n",i,uneSalle->film->titre,uneSalle->numero,uneSalle->NBPersonnes+1);
                (uneSalle->NBPersonnes)++;
                pthread_create(threadManagement+NBSalles,0,(void *(*)())fonc_managerSalles,lesSallesList->val);
                NBSalles++;
                return laSalle;
            }
        }
        int random = rand()%(100-0) +0;
        if(random >= 80)
        {
            printf("le client %d va essayer de voir un autre film\n",i);
            if(choisirFilm(i)==NULL)
            {   
                return NULL;
            }
            else
            {
                return laSalle;
            }
            
        }
        else{
            printf("le client %d sort du cinema car il n'y avait plus de place pour son film\n",i);
            return laSalle;
        }
        
        
    }
    else
    {
        printf("client %d à acheté sa place pour le film %s dans la salle %d à la place %d\n",i,laSalle->film->titre,laSalle->numero,laSalle->NBPersonnes+1);
        (laSalle->NBPersonnes)++;
        if(laSalle->NBPersonnes>=laSalle->CAPACITE)
        {
            pthread_cond_signal(&(laSalle->demarrer));
            printf("#passé par la %s \n", laSalle->film->titre);
        }
        return laSalle;
    }
    
    return laSalle;
}

SalleStruct* choixSalle(FilmStruct * unFilm)
{
    
    element *tmp = lesSallesList;
    while(tmp != NULL)
    {
        if(tmp->val->film == unFilm){
            
            if(tmp->val->NBPersonnes < tmp->val->CAPACITE)
            {
                return tmp->val;
            }
            
        }
        tmp = tmp->nxt;
        
    }
    
    
    return NULL;
}

void allerVoirFilm(Salle * maSalle, argStruct * arg, char * type)
{
    pthread_mutex_lock(&mutex_attenteClient);
    
    
    
    if(maSalle!=NULL)
    {
        maSalle->personnesAttendent++;
        /*
         * Au debut, je voulais que les clients attendes devant la salle puis rentrent regarder le film
         * Mais j'ai eu un problème d'interbloquage ici, c'est pour cela qu'il y a un comptage des personnes qui attendent.
         */
        
        printf("Le %s %s attend devant la salle\n", type, maSalle->film->titre);
        pthread_cond_wait(&(conditionEntrerSalle),&mutex_attenteClient);
        maSalle->personnesAttendent--;
        printf("Le %s %d regarde son film\n", type, arg->num);

    }    
    pthread_mutex_unlock(&mutex_attenteClient);
}








