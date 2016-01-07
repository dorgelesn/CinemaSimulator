
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "../include/argStruct.h"
#include "../include/FilmStruct.h"
#include "../include/SalleStruct.h"
#include "../include/ListeSalle.h"
#include "../include/caissiere.h"
#include "../include/client.h"
#include "../include/abonnee.h"
#include "../include/caisseAuto.h"
#include "../include/managementSalles.h"
#include "../include/getFilm.h"
#include "../include/netoyage.h"

pthread_t* tid;
pthread_t* threadManagement;
pthread_mutex_t mutex_attenteClient;
pthread_cond_t attendre, dormir, attendreAuto, dormirAuto, attendreAbonnee, demarrer, conditionEntrerSalle;
//SalleStruct * lesSalles[NBSalles];
//FilmStruct * lesFilms[NBFilms];
ListeSalle lesSallesList;
//SalleStruct ** lesSalles;
FilmStruct ** lesFilms;


int NBSalles;
int NbSalleMax;
int NBFilms;
int nbClientsAttente;
int nbClientsAttenteAuto;
int nbClientInternet;
int nbAppelCaisse;
int nbAbonneeAttente;
int lancerFilms;
int nbAbonnee;
int nbAbonneeAcheteBillet;
int Nbcaisses;
int NbcaissesAuto;
int NbClients;
int PourcentAbonnee;
int LimiteRefusPlace;
int pourcentageDePersonnesAuCaisses;
int pourcentageDePersonnesAuCaissesAuto;
//for esay cleaning of memory 
argStruct ** arguments;