#include "../include/global.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string.h>
/* static void print_element_names(xmlNode * a_node)
{
    xmlNode *cur_node = NULL;
    
    for (cur_node = a_node; cur_node; cur_node =
        cur_node->next) {
        if (cur_node->type == XML_ELEMENT_NODE) {
            printf("node type: Element, name: %s\n",
                   cur_node->name);
        }
        print_element_names(cur_node->children);
        }
} */

void parserConfig()
{
    
    xmlDoc*  doc  = NULL;
    xmlNode* cinema = NULL;
    doc = xmlReadFile( "../config.xml", NULL, 0 );
    if ( doc==NULL )
        printf("erreur lors de la lecture du fichier");
    cinema = xmlDocGetRootElement(doc);
    xmlNode* lesFilmsNode = (cinema->children)->next;
    
    printf("node type: Element, name: %s\n",cinema->name);
    printf("nbCaisses : %s\nnbCaissesAuto=%s\nnbClients=%s\npourcentageDePersonnesAuCaisses= %s\npourcentageDePersonnesAuCaissesAuto= %s\n", 
           (const char*)xmlGetProp( cinema, (const xmlChar*)"nbCaisses") ,
           (const char*)xmlGetProp( cinema, (const xmlChar*)"nbCaissesAuto") ,
           (const char*)xmlGetProp( cinema, (const xmlChar*)"nbClients" ),
           (const char*)xmlGetProp( cinema, (const xmlChar*)"pourcentageDePersonnesAuCaisses") ,
           (const char*)xmlGetProp( cinema, (const xmlChar*)"pourcentageDePersonnesAuCaissesAuto"));
    
    
    
    //printf("node type: Element, name: %s\n",lesFilms->name);
    Nbcaisses = atoi((const char*)xmlGetProp( cinema, (const xmlChar*)"nbCaisses"));
    NbcaissesAuto = atoi((const char*)xmlGetProp( cinema, (const xmlChar*)"nbCaissesAuto"));
    NbClients = atoi((const char*)xmlGetProp( cinema, (const xmlChar*)"nbClients" ));
    PourcentAbonnee = atoi((const char*)xmlGetProp( cinema, (const xmlChar*)"PourcentAbonnee" ));
    
    xmlNode* filmNode = NULL;
    int compteurFilm = 0;
    for(filmNode = (lesFilmsNode->children)->next; filmNode; filmNode = filmNode->next)
    {
        if(filmNode->type == XML_ELEMENT_NODE)
            compteurFilm++;
    }
    
    printf("compteur = %d\n",compteurFilm);
    //NBFilms=compteurFilm;
    
    
    xmlNode* lesSallesNode = NULL;
    for(lesSallesNode=lesFilmsNode->next; lesSallesNode; lesSallesNode = lesSallesNode->next)
    {
        if(lesSallesNode->type == XML_ELEMENT_NODE)
            break;
    }
    
    
    printf("les salles %s",lesSallesNode->name);
    xmlNode* salleNode = NULL;
    int compteurSalle = 0;
    for(salleNode = (lesSallesNode->children)->next; salleNode; salleNode = salleNode->next)
    {
        if(salleNode->type == XML_ELEMENT_NODE)
            compteurSalle++;
    }
    
    printf("compteur = %d\n",compteurSalle);
    //NBSalles=compteurSalle;
    
    NBSalles = 5;
    NBFilms = 5;
    
    
    lesFilms = malloc(NBFilms * sizeof(FilmStruct*));
    lesSalles = malloc(NBSalles * sizeof(SalleStruct*));
    
    
    int numSalle;
    char *nom[5]={"toto au cine","starw wars","maze runner","spectre","un avion se crash"};
    char *genres[5]={"comedie","science-fiction","aventure","action","drame"};
    int duree[5]={120,90,180,111,10};
    int horaire[5]={1,2,1,2,1};
    int pegi[5]={3,12,12,16,18};
    
    int i;
    for(i = 0; i<NBFilms; i++)
    {
        FilmStruct * unFilm = malloc(sizeof(FilmStruct));
        unFilm->titre = nom[i];
        unFilm->genre = genres[i];
        unFilm->duree = duree[i];
        unFilm->horaire = horaire[i];
        unFilm->pegi = pegi[i];
        lesFilms[i] = unFilm;
        
    }
    
    for(numSalle =1; numSalle <= NBSalles; numSalle++)
    {
            SalleStruct * uneSalle = malloc(sizeof(SalleStruct));
            uneSalle->film=lesFilms[numSalle-1];
            uneSalle->numero=numSalle;
            uneSalle->CAPACITE = 120;
            uneSalle->NBPersonnes=0;
            lesSalles[numSalle-1] = uneSalle;
    }
    
    
    
    xmlFreeDoc(doc);       // free document
    xmlCleanupParser();    // Free globals
    
    
}