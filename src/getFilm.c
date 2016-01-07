#include "../include/global.h"


//retourne l'index du film possédant l'identifiant filmId
//Utile pour lier les films au salle lors du parsing du fichier de configuration.
int getIndex(int filmId){
 
    int i;
    for(i=0; i<NBFilms; i++){
     
        if(lesFilms[i]->id==filmId)
            return i;
        
    }
    return -1;
    
}