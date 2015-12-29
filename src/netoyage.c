#include <libxml/parser.h>
#include <libxml/tree.h>
#include "../include/global.h"

static void fermetureThreads(){
 
    int i;
    for(i=0; i<(Nbcaisses+NbcaissesAuto+NbClients); i++)
    {
        if(tid[i]!=(pthread_t)NULL)
        {
            printf("arrêt du thread n° %d\n",i);
            pthread_cancel(tid[i]);
        }
    }
    printf("netoyage du tableau de pthread_t\n");
    free(tid);
    //free(arguments);
    
}

static void netoyageArguments(){
 
    int i;
    for(i=0; i<(Nbcaisses+NbcaissesAuto+NbClients); i++)
    {
        printf("netoygae de l'argument thread n° %d\n",i);
        if(arguments[i]!=NULL)
        free(arguments[i]);
    }
    printf("netoyage du tableau d'arguments\n");
    free(arguments);
    
}

static void netoyageFilms()
{
    int i;
    for(i=0;i<NBFilms;i++)
    {
        printf("nettoyage du film n° %d\n",i);
        xmlFree(lesFilms[i]->titre);
        xmlFree(lesFilms[i]->genre);
        free(lesFilms[i]);
    }
    free(lesFilms);
    
}

static void netoyageSalles()
{
    int i;
    for(i=0;i<NBSalles;i++)
    {
        printf("nettoyage de la salle n° %d\n",i);
        free(lesSalles[i]);
    }
    free(lesSalles);
}


void netoyer(){
 
    // libération des ressources
    
    /*
     *Ressource à netoyer : 
     * 
     * pthread_mutex_t mutex_attenteClient;
     *   pthread_cond_t attendre, dormir, attendreAuto, dormirAuto, attendreAbonnee;
     */
    printf("\n###############################\n#    Netoyage de la memoire   #\n###############################\n");
    pthread_mutex_destroy(&mutex_attenteClient);
    pthread_cond_destroy(&attendre);
    pthread_cond_destroy(&dormir);
    pthread_cond_destroy(&attendreAuto);
    pthread_cond_destroy(&dormirAuto);
    pthread_cond_destroy(&attendreAbonnee);
    
    fermetureThreads();
    netoyageArguments();
    netoyageSalles();
    netoyageFilms();
    //pthread_attr_destroy();
    
    exit(1);
    
    

    
}
