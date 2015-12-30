#include "../include/global.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string.h>
/* static void print_element_names(xmlNode * a_node)
 * {
 *    xmlNode *cur_node = NULL;
 *    
 *    for (cur_node = a_node; cur_node; cur_node =
 *        cur_node->next) {
 *        if (cur_node->type == XML_ELEMENT_NODE) {
 *            printf("node type: Element, name: %s\n",
 *                   cur_node->name);
 *        }
 *        print_element_names(cur_node->children);
 *        }
 * } */

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
    /*printf("nbCaisses : %s\nnbCaissesAuto=%s\nnbClients=%s\npourcentageDePersonnesAuCaisses= %s\npourcentageDePersonnesAuCaissesAuto= %s\n", 
           (const char*)xmlGetProp( cinema, (const xmlChar*)"nbCaisses") ,
           (const char*)xmlGetProp( cinema, (const xmlChar*)"nbCaissesAuto") ,
           (const char*)xmlGetProp( cinema, (const xmlChar*)"nbClients" ),
           (const char*)xmlGetProp( cinema, (const xmlChar*)"pourcentageDePersonnesAuCaisses") ,
           (const char*)xmlGetProp( cinema, (const xmlChar*)"pourcentageDePersonnesAuCaissesAuto"));*/
    
    
    
    //printf("node type: Element, name: %s\n",lesFilms->name);
    char* NbcaissesXML = (char*)xmlGetProp( cinema, (const xmlChar*)"nbCaisses");
    char* LimiteRefusPlaceXML = (char*)xmlGetProp( cinema, (const xmlChar*)"LimiteRefusPlace");
    char* NbcaissesAutoXML = (char*)xmlGetProp( cinema, (const xmlChar*)"nbCaissesAuto");
    char* NbClientsXML = (char*)xmlGetProp( cinema, (const xmlChar*)"nbClients" );
    char* PourcentAbonneeXML = (char*)xmlGetProp( cinema, (const xmlChar*)"PourcentAbonnee" );
    char* NbSalleMaxXML = (char*)xmlGetProp( cinema, (const xmlChar*)"NbSalleMax" );
    Nbcaisses = atoi(NbcaissesXML);
    NbcaissesAuto = atoi(NbcaissesAutoXML);
    NbClients = atoi(NbClientsXML);
    PourcentAbonnee = atoi(PourcentAbonneeXML);
    NbSalleMax = atoi(NbSalleMaxXML);
    LimiteRefusPlace=atoi(LimiteRefusPlaceXML);
    
    xmlFree(LimiteRefusPlaceXML);
    xmlFree(NbSalleMaxXML);
    xmlFree(NbcaissesXML);
    xmlFree(NbcaissesAutoXML);
    xmlFree(NbClientsXML);
    xmlFree(PourcentAbonneeXML);
    xmlNode* filmNode = NULL;
    int compteurFilm = 0;
    for(filmNode = (lesFilmsNode->children)->next; filmNode; filmNode = filmNode->next)
    {
        if(filmNode->type == XML_ELEMENT_NODE)
            compteurFilm++;
    }
    
    printf("compteur = %d\n",compteurFilm);
    NBFilms=compteurFilm;
    
    
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
    NBSalles=compteurSalle;
    
    
    lesFilms = malloc(NBFilms * sizeof(FilmStruct*));
    printf("OK\n");
    int i = 0;
    for(filmNode = (lesFilmsNode->children)->next; filmNode; filmNode = filmNode->next)
    {
        
        if(filmNode->type == XML_ELEMENT_NODE)
        {
            char* filmId = (char*)xmlGetProp( filmNode, (const xmlChar*)"id");
            char* filmTitre = (char*)xmlGetProp( filmNode, (const xmlChar*)"titre");
            char* filmGenre = (char*)xmlGetProp( filmNode, (const xmlChar*)"genre");
            char* filmDuree = (char*)xmlGetProp( filmNode, (const xmlChar*)"duree");
            char* filmHoraire = (char*)xmlGetProp( filmNode, (const xmlChar*)"horaire");
            char* filmPegi = (char*)xmlGetProp( filmNode, (const xmlChar*)"pegi");
            //printf("%s %s %s %s %s %s\n", filmId, filmGenre, filmTitre, filmDuree, filmHoraire, filmPegi);
            
            FilmStruct * unFilm = malloc(sizeof(FilmStruct));
            unFilm->id = atoi(filmId);
            unFilm->titre = filmTitre;
            unFilm->genre = filmGenre;
            unFilm->duree = atoi(filmDuree);
            unFilm->horaire = atoi(filmHoraire);
            unFilm->pegi = atoi(filmPegi);
            unFilm->NbPlaceRefuse=0;
            lesFilms[i] = unFilm;
            i++;
            xmlFree(filmId);

            xmlFree(filmDuree);
            xmlFree(filmHoraire);
            xmlFree(filmPegi);
            
        }
    }

    for(salleNode = (lesSallesNode->children)->next; salleNode; salleNode = salleNode->next)
    {
        if(salleNode->type == XML_ELEMENT_NODE)
        {
            char* numeroSalle = (char*)xmlGetProp( salleNode, (const xmlChar*)"numeroSalle");
            char* capacite = (char*)xmlGetProp( salleNode, (const xmlChar*)"capacite");
            char* film = (char*)xmlGetProp( salleNode, (const xmlChar*)"film");
            
            SalleStruct * uneSalle = malloc(sizeof(SalleStruct));
            uneSalle->film=lesFilms[getIndex(atoi(film))];
            uneSalle->numero=atoi(numeroSalle);
            uneSalle->CAPACITE = atoi(capacite);
            uneSalle->NBPersonnes=0;
            //printf("ajouter Salle : \n");
            lesSallesList=ajouterSalle(lesSallesList, uneSalle);
            xmlFree(numeroSalle);
            xmlFree(capacite);
            xmlFree(film);
            
        }
    }
    
    
    
    
    xmlFreeDoc(doc);  // free document
    xmlCleanupParser();    // Free globals
    
    
}