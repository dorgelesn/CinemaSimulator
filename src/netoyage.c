#include <libxml/parser.h>
#include <libxml/tree.h>
#include "../include/global.h"



/*
 * 
 * Ce fichier est charger de netoyer la memoire et les threads
 * lors de la fin du programme ou d'une interuption
 * 
 */


//fermeture ses threads caisse et clients
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

//netoyage des arguments de thread client et caisses
static void netoyageArguments(){
 
    int i;
    for(i=0; i<(Nbcaisses+NbcaissesAuto+NbClients); i++)
    {
        
        if(arguments[i]!=NULL)
        {
            printf("netoygae de l'argument thread n° %d\n",i);
            free(arguments[i]);
        }
    }
    printf("netoyage du tableau d'arguments\n");
    free(arguments);
    
}

/*
 *
 *libération du tableau dynamique de films 
 * 
 */

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

/*
 * Netoyage de la liste chainée de salles 
 */

static void netoyageSalles()
{
    detruireLesSalles();
}

/*
 * Netoyage des thread gérent les séances
 */

void netoyageThreadManagement()
{
    int i;
    for(i=0; i<NbSalleMax; i++)
    {
        if(threadManagement[i]!=(pthread_t)NULL)
        {
            printf("arrêt du thread Management n° %d\n",i);
            pthread_cancel(threadManagement[i]);
        }
    }
    printf("netoyage du tableau de pthread_t\n");
    free(threadManagement);
}


/*
 * Neoyage appelé lors de l'execution du programme
 */

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
    pthread_cond_destroy(&conditionEntrerSalle);
    pthread_cond_destroy(&demarrer);
    netoyageThreadManagement();
    
    fermetureThreads();
    netoyageArguments();
    netoyageSalles();
    netoyageFilms();
    //pthread_attr_destroy();
    
    exit(1);
    
    

    
}

/*
 * 
 * netoyage appelé lors d'une interuption au debut ou tout à la fins lorsque 
 * les threads client n'ont pas encore commencés ou se sont déja terminés correctement
 * 
 */

void netoyerFin(){
 
    printf("\n###############################\n#    Netoyage de la memoire   #\n###############################\n");
    pthread_mutex_destroy(&mutex_attenteClient);
    pthread_cond_destroy(&attendre);
    pthread_cond_destroy(&dormir);
    pthread_cond_destroy(&attendreAuto);
    pthread_cond_destroy(&dormirAuto);
    pthread_cond_destroy(&attendreAbonnee);
    pthread_cond_destroy(&conditionEntrerSalle);
    pthread_cond_destroy(&demarrer);
    
    //fermetureThreads();
    netoyageThreadManagement();
    netoyageArguments();
    free(tid);
    netoyageSalles();
    netoyageFilms();
    //pthread_attr_destroy();
    
    exit(1);
    
    

    
}