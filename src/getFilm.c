#include "../include/global.h"

int getIndex(int filmId){
 
    int i;
    for(i=0; i<NBFilms; i++){
     
        if(lesFilms[i]->id==filmId)
            return i;
        
    }
    return -1;
    
}