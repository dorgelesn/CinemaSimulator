
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/caissiere.h"
#include "../include/client.h"
#include "../include/argStruct.h"
#include "../include/SalleStruct.h"
#define Nbcaisses 8 
#define NbClients 1000
#define NBSalles 5

pthread_t tid[NbClients+Nbcaisses];
pthread_mutex_t mutex_attenteClient;
pthread_cond_t attendre, dormir;
SalleStruct * lesSalles[NBSalles];

int nbClientsAttente;
int nbAppelCaisse;
