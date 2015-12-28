#include "../include/global.h"
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <string.h>
static void print_element_names(xmlNode * a_node)
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
}

void parserConfig()
{
    
    xmlDoc*  doc  = NULL;
    xmlNode* cinema = NULL;
    doc = xmlReadFile( "../config.xml", NULL, 0 );
    if ( doc==NULL )
        printf("erreur lors de la lecture du fichier");
    xmlNode *cur_node = &doc;
    cinema = xmlDocGetRootElement(doc);
    xmlNode* lesFilms = (cinema->children)->next;
    
    printf("node type: Element, name: %s\n",cinema->name);
    printf("nbCaisses : %s\nnbCaissesAuto=%s\n nbClients=%s\n pourcentageDePersonnesAuCaisses= %s\n pourcentageDePersonnesAuCaissesAuto= %s\n", 
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
    
    
    xmlFreeDoc(doc);       // free document
    xmlCleanupParser();    // Free globals
    
    
}