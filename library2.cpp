//
// Created by Dell on 11/05/2020.
//

#include "library1.h"
#include "MusicManager.h"

void *Init(){
    MusicManager *DS = NULL;
    try {
        DS = new MusicManager();
    }
    catch (std::bad_alloc &badAlloc){
        return NULL;
    }
    return (void *)DS;
}

StatusType AddArtist(void *DS, int artistID){
    if (DS == NULL || artistID<=0)
        return INVALID_INPUT;
    try {
        return ((MusicManager *)DS)->addArtist(artistID);
    }
    catch (std::bad_alloc &badAlloc){
        return ALLOCATION_ERROR;
    }
}

StatusType RemoveArtist(void *DS, int artistID){
    if (DS == NULL || artistID <= 0)
        return INVALID_INPUT;
    try {
        return ((MusicManager *)DS)->removeArtist(artistID);
    }
    catch (std::bad_alloc &badAlloc) {
        return ALLOCATION_ERROR;
    }
}

StatusType AddSong(void *DS, int artistID, int songID){
    if (DS == NULL || artistID <= 0 || songID < 0)
        return FAILURE;
    try {
        return ((MusicManager *)DS)->AddSong(artistID,songID);
    }
    catch (std::bad_alloc &badAlloc) {
        return ALLOCATION_ERROR;
    }
}

StatusType RemoveSong(void *DS, int artistID, int songID){

}

StatusType AddToSongCount(void *DS, int artistID, int songID, int count){
    if (DS == NULL || artistID <= 0 || songID < 0 || count <= 0)
        return INVALID_INPUT;
    try {
        return ((MusicManager *)DS)->addToSongCount(artistID,songID,count);
    }
    catch (std::bad_alloc &badAlloc){
        return ALLOCATION_ERROR;
    }
}

StatusType GetArtistBestSong(void *DS, int artistID, int *songId){

}

StatusType GetRecommendedSongInPlace(void *DS, int rank, int *artistId, int *songId){
    if (DS == NULL || artistId == NULL || songId == NULL || rank <=0)
        return INVALID_INPUT;
    try {
        return ((MusicManager *)DS)->GetRecommendedSongInPlace(rank,artistId,songId);
    }
    catch (std::bad_alloc &badAlloc){
        return ALLOCATION_ERROR;
    }
}

void Quit(void** DS){
    delete *((MusicManager **)DS);
    *DS = NULL;
}