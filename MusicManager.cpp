//
// Created by Dell on 05/05/2020.
//

#define INVALID_INDEX -1
#define INITIAL_ARRAY_SIZE 10
#include "MusicManager.h"

// ---------- RankTreeSongKey implementation ---------- //

MusicManager::RankTreeSongKey::RankTreeSongKey(int songID, int songNumberOfPlays, int artistID): songID(songID),songNumberOfPlays(songNumberOfPlays),
artistID(artistID){}

int MusicManager::RankTreeSongKey::getSongID() const {
    return songID;
}

int MusicManager::RankTreeSongKey::getSongNumberOfPlays() const {
    return songNumberOfPlays;
}

int MusicManager::RankTreeSongKey::getSongArtistID() const {
    return artistID;
}

// ---------- ArtistSongsTreeSongKey implementation ---------- //

MusicManager::ArtistSongsTreeByIdAndPlaysSongKey::ArtistSongsTreeByIdAndPlaysSongKey(int songID, int songNumberOfPlays): songID(songID),songNumberOfPlays(songNumberOfPlays){}

int MusicManager::ArtistSongsTreeByIdAndPlaysSongKey::getSongID() const {
    return songID;
}

int MusicManager::ArtistSongsTreeByIdAndPlaysSongKey::getSongNumberOfPlays() const {
    return songNumberOfPlays;
}

// ---------- ArtistSongsTreeByIdAndPlaysSongData implementation ---------- //

MusicManager::ArtistSongsTreeByIdAndPlaysSongData::ArtistSongsTreeByIdAndPlaysSongData(AVLtree<int,ArtistSongsTreeByIdSongData>::AVLNode* songInSongsByIdTree) {
    this->songInSongsByIdTree = songInSongsByIdTree;
}

AVLtree<int,MusicManager::ArtistSongsTreeByIdSongData>::AVLNode* MusicManager::ArtistSongsTreeByIdAndPlaysSongData::getSongInSongsByIdTree() {
    return songInSongsByIdTree;
}

void MusicManager::ArtistSongsTreeByIdAndPlaysSongData::setSongInSongsByIdTree(
        AVLtree<int, MusicManager::ArtistSongsTreeByIdSongData>::AVLNode &songInSongsByIdTree) {
    this->songInSongsByIdTree = &songInSongsByIdTree;
}

// ---------- ArtistSongsTreeByIdSongData implementation ---------- //

MusicManager::ArtistSongsTreeByIdSongData::ArtistSongsTreeByIdSongData(
        AVLtree<MusicManager::ArtistSongsTreeByIdAndPlaysSongKey, MusicManager::ArtistSongsTreeByIdAndPlaysSongData>::AVLNode *songInSongsByIdAndPlaysTree) {
    this->songInSongsByIdAndPlaysTree = songInSongsByIdAndPlaysTree;
}

AVLtree<MusicManager::ArtistSongsTreeByIdAndPlaysSongKey,MusicManager::ArtistSongsTreeByIdAndPlaysSongData>::AVLNode* MusicManager::ArtistSongsTreeByIdSongData::getSongInSongsByIdAndPlaysTree() {
    return songInSongsByIdAndPlaysTree;
}

void MusicManager::ArtistSongsTreeByIdSongData::setSongInSongsByIdTree(
        AVLtree<MusicManager::ArtistSongsTreeByIdAndPlaysSongKey, MusicManager::ArtistSongsTreeByIdAndPlaysSongData>::AVLNode &songInSongsByIdAndPlaysTree) {
    this->songInSongsByIdAndPlaysTree = &songInSongsByIdAndPlaysTree;
}

// ---------- ArtistData implementation ---------- //

MusicManager::ArtistData::ArtistData() {
    songs_ordered_by_id = new AVLtree<int,MusicManager::ArtistSongsTreeByIdSongData>();
    songs_ordered_by_plays_and_id = new AVLtree<MusicManager::ArtistSongsTreeByIdAndPlaysSongKey,ArtistSongsTreeByIdAndPlaysSongData>();
    maxSong = nullptr;
}

MusicManager::ArtistData::ArtistData(MusicManager::ArtistData &artistData) {
    // we need to make an AVLtree copy constructor if we really want to do this
}

MusicManager::ArtistData::~ArtistData() {
    delete songs_ordered_by_plays_and_id;
    delete songs_ordered_by_id;
}

AVLtree<int, MusicManager::ArtistSongsTreeByIdSongData>* MusicManager::ArtistData::getSongsTreeOrderedById() {
    return songs_ordered_by_id;
}

AVLtree<MusicManager::ArtistSongsTreeByIdAndPlaysSongKey,MusicManager::ArtistSongsTreeByIdAndPlaysSongData>* MusicManager::ArtistData::getSongsTreeOrderedByPlaysAndId() {
    return songs_ordered_by_plays_and_id;
}

AVLtree<MusicManager::ArtistSongsTreeByIdAndPlaysSongKey,MusicManager::ArtistSongsTreeByIdAndPlaysSongData>::AVLNode* MusicManager::ArtistData::getMaxSong() {
    return maxSong;
}

// ---------- MusicManager implementation - private ---------- //

int MusicManager::hashFunction(int id,int modulo) {
    return id % modulo;
}

void MusicManager::extendArtistsArraySize(){
    int newSize = this->size * 10;
    List<int,ArtistData>* newArtists = new List<int,ArtistData>[newSize];
    for(int i=0; i < this->size; i++){
        List<int,ArtistData>::ListNode* current = artists[i].getFirst();
        while(current != nullptr){
            int
        }
    }
}

// ---------- MusicManager implementation - public ---------- //

MusicManager::MusicManager() {
    songs = new AVLRankTree<RankTreeSongKey,int>();
    artists = new List<int,ArtistData>[INITIAL_ARRAY_SIZE];
    artistsCounter = 0;
    size = INITIAL_ARRAY_SIZE;
}

MusicManager::~MusicManager() {
    delete[] artists;
    delete songs;
}

StatusType MusicManager::addArtist(int artistID, int numOfSongs) {
    AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>::AVLNode* artistSave = nullptr;
    MusicManager::ArtistKey artistKey(artistID);
    MusicManager::ArtistData artistData(numOfSongs);
    AVLtree<ArtistKey,ArtistData>::AVLNode* artist = nullptr;
    try {
        artist = artists->insert(artistKey,artistData);
    }
    catch (AVLtree<ArtistKey,ArtistData>::AlreadyExist_AVLtree &alreadyExistAvLtree){
        return FAILURE;
    }

    MusicManager::PlaysData newPlaysData;
    int zeroPlayNodeKey=0;
    if (songPlays->getFirst()== nullptr || songPlays->getFirst()->getKey()!= 0){
        songPlays->insertFirst(zeroPlayNodeKey,newPlaysData);
        artistSave = songPlays->getFirst()->getData().getArtistTree()->insert(artistKey,artist);
        songPlays->getFirst()->getData().setMinID(artistSave);
    } else {
        artistSave = songPlays->getFirst()->getData().getArtistTree()->insert(artistKey,artist);
        if (artist->getKey()>songPlays->getFirst()->getData().getMinID()->getKey()){
            songPlays->getFirst()->getData().setMinID(artistSave);
        }
    }

    for (int i = 0; i < numOfSongs; ++i) {
        artist->getData().getPlaysNodes()[i]=songPlays->getFirst();
    }

    songsCounter+=numOfSongs;

    return SUCCESS;
}

StatusType MusicManager::removeArtist(int artistID){
    int songCounter=0;
    // get the key
    MusicManager::ArtistKey artistKey(artistID);

    // get the artist node
    AVLtree<ArtistKey,ArtistData>::AVLNode* artist;
    AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>::AVLNode* previousArtistSave = nullptr;
    try {
        artist = artists->find(artistKey);
    }
    catch (AVLtree<ArtistKey,ArtistData>::NotFound_AVLtree &notFoundAvLtree){
        return FAILURE;
    }

    //get the artist's data
    MusicManager::ArtistData& data = artist->getData();

    AVLtree<SongKey,int>::AVLNode* currentSongNode = data.getSongNodes()[data.getMaxSongID()];

    if (currentSongNode == nullptr){    //if the artist's songs tree is empty
        previousArtistSave = songPlays->getFirst()->getData().getMinID()->getPrevious();
        if (artist->getKey().getArtistID() == songPlays->getFirst()->getData().getMinID()->getKey().getArtistID())
            songPlays->getFirst()->getData().setMinID(previousArtistSave);      //update min_id if we remove the artist with the minimal id from the tree
        songPlays->getFirst()->getData().getArtistTree()->erase(artistKey);
        if ( songPlays->getFirst()->getData().getArtistTree()->getRoot() == nullptr){   //delete the 0 node from plays_list if its tree is empty now
            songPlays->erase(songPlays->getFirst());
        }
    }
    else {
        int currentNumberOfPlays = -1;
        while (currentSongNode != nullptr){
            if (currentSongNode->getKey().getSongNumberOfPlays() != currentNumberOfPlays){
                previousArtistSave = data.getPlaysNodes()[currentSongNode->getKey().getSongID()]->getData().getMinID()->getPrevious();
                if (artist->getKey().getArtistID() == data.getPlaysNodes()[currentSongNode->getKey().getSongID()]->getData().getMinID()->getKey().getArtistID()){
                    data.getPlaysNodes()[currentSongNode->getKey().getSongID()]->getData().setMinID(previousArtistSave);
                }

                data.getPlaysNodes()[currentSongNode->getKey().getSongID()]->getData().getArtistTree()->erase(artistKey);
                // remove the playsNode if his artist Tree is empty
                currentNumberOfPlays = data.getPlaysNodes()[currentSongNode->getKey().getSongID()]->getKey();
                if (data.getPlaysNodes()[currentSongNode->getKey().getSongID()]->getData().getArtistTree()->getRoot() == nullptr){
                    songPlays->erase(data.getPlaysNodes()[currentSongNode->getKey().getSongID()]);
                }
            }
            currentSongNode = currentSongNode->getPrevious();
            songCounter++;
        }
        if (songCounter!=artist->getData().getNumberOfSongs()){
            previousArtistSave = songPlays->getFirst()->getData().getMinID()->getPrevious();
            if (artist->getKey().getArtistID() == songPlays->getFirst()->getData().getMinID()->getKey().getArtistID()){
                songPlays->getFirst()->getData().setMinID(previousArtistSave);
            }
            songPlays->getFirst()->getData().getArtistTree()->erase(artistKey);
            if ( songPlays->getFirst()->getData().getArtistTree()->getRoot() == nullptr){
                songPlays->erase(songPlays->getFirst());
            }
        }
    }
    //remove the artist from the main artists tree
    songsCounter-=artist->getData().getNumberOfSongs();
    artists->erase(artistKey);

    return SUCCESS;
}

StatusType MusicManager::addToSongCount(int artistID, int songID) {
    AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>::AVLNode* artistSave = nullptr;
    AVLtree<ArtistKey,AVLtree<ArtistKey,ArtistData>::AVLNode*>::AVLNode* previousArtistSave = nullptr;
    List<int,PlaysData>::ListNode* playsSave = nullptr;
    AVLtree<SongKey,int>::AVLNode* newSongNode = nullptr;
    int newNumberOfPlays = 0;

    MusicManager::ArtistKey artistKey(artistID);
    AVLtree<ArtistKey,ArtistData>::AVLNode* artist;
    try {
        artist = artists->find(artistKey);
    }
    catch (AVLtree<ArtistKey,ArtistData>::NotFound_AVLtree &notFoundAvLtree){
        return FAILURE;
    }
    if (songID >= artist->getData().getNumberOfSongs())
        return INVALID_INPUT;

    AVLtree<SongKey,int>::AVLNode* songNode = artist->getData().getSongNodes()[songID];

    // in case this is the first play of this song
    if (songNode == nullptr){

        newNumberOfPlays = 1;

        // creating new song node and inserting it to the artist songs tree
        // updating the artist info arrays including the zeroPlays,songNodes
        MusicManager::SongKey newSongKey(songID,newNumberOfPlays);
        artist->getData().getSongNodes()[songID] = artist->getData().getSongs()->insert(newSongKey,artistID);
        newSongNode = artist->getData().getSongNodes()[songID];
        if (artist->getData().getZeroPlays()[songID+1][0]!=INVALID_INDEX)
            artist->getData().getZeroPlays()[artist->getData().getZeroPlays()[songID+1][0]][1] = artist->getData().getZeroPlays()[songID+1][1];
        if (artist->getData().getZeroPlays()[songID+1][1]!=INVALID_INDEX)
            artist->getData().getZeroPlays()[artist->getData().getZeroPlays()[songID+1][1]][0] = artist->getData().getZeroPlays()[songID+1][0];

        // checking if the first node in the songPlays list is not 1 and there are no more
        // or the first node in the songPlays list is not 1 and the second one is not 1
        if ( (songPlays->getFirst()->getKey()!=1 && songPlays->getFirst()->getNext()==nullptr ) ||
             (songPlays->getFirst()->getKey()!=1 && songPlays->getFirst()->getNext()->getKey()!=1) ){
            MusicManager::PlaysData newPlaysData;

            // inserting a new node for 1 plays and saving it (the first node is 0)
            if (songPlays->getFirst()->getKey()==0){
                playsSave = songPlays->insertAfterNode(newNumberOfPlays,newPlaysData,songPlays->getFirst());
            }

                // inserting a new node for 1 plays and saving it (the first node is 1)
            else {
                playsSave = songPlays->insertFirst(newNumberOfPlays,newPlaysData);
            }

            // inserting the artist to the artist tree of the playsNode if it is not already in there
            if ((newSongNode->getNext() == nullptr || newSongNode->getNext()->getKey().getSongNumberOfPlays()!=newSongNode->getKey().getSongNumberOfPlays() ) &&
                ( newSongNode->getPrevious() == nullptr || newSongNode->getPrevious()->getKey().getSongNumberOfPlays()!=newSongNode->getKey().getSongNumberOfPlays())){
                artistSave = playsSave->getData().getArtistTree()->insert(artistKey,artist);
            }
        }

            // if the songPlays node for 1 plays does already exist and it is the first one on the list
        else if (songPlays->getFirst()->getKey()==1){
            if ((newSongNode->getNext() == nullptr || newSongNode->getNext()->getKey().getSongNumberOfPlays()!=newSongNode->getKey().getSongNumberOfPlays() ) &&
                ( newSongNode->getPrevious() == nullptr || newSongNode->getPrevious()->getKey().getSongNumberOfPlays()!=newSongNode->getKey().getSongNumberOfPlays())){
                artistSave = songPlays->getFirst()->getData().getArtistTree()->insert(artistKey,artist);
            }
            playsSave = songPlays->getFirst();
        }

            // if the songPlays node for 1 plays does already exist and it is the second one on the list
        else {
            if ((newSongNode->getNext() == nullptr || newSongNode->getNext()->getKey().getSongNumberOfPlays()!=newSongNode->getKey().getSongNumberOfPlays() ) &&
                (newSongNode->getPrevious() == nullptr || newSongNode->getPrevious()->getKey().getSongNumberOfPlays()!=newSongNode->getKey().getSongNumberOfPlays())){
                artistSave = songPlays->getFirst()->getNext()->getData().getArtistTree()->insert(artistKey,artist);
            }
            playsSave = songPlays->getFirst()->getNext();
        }

        // updating the new playNode of the song if he has a new max artist in his tree
        if (playsSave!= nullptr && (playsSave->getData().getMinID()== nullptr || artist->getKey().getArtistID()<playsSave->getData().getMinID()->getKey().getArtistID())){
            playsSave->getData().setMinID(artistSave);
        }

        // update the artist counter for songs with zero plays, if the artist has no more songs with 0 plays
        // erase the artist from the 0 plays playNode and set a new max artist for this playNode
        artist->getData().setZeroPlaysSongCounter(artist->getData().getZeroPlaysSongCounter()-1);
        if (artist->getData().getZeroPlaysSongCounter()==0){
            previousArtistSave = artist->getData().getPlaysNodes()[songID]->getData().getArtistTree()->find(artistKey)->getPrevious();
            if (artist->getKey().getArtistID()==artist->getData().getPlaysNodes()[songID]->getData().getMinID()->getKey().getArtistID()){
                songPlays->getFirst()->getData().setMinID(previousArtistSave);
            }
            songPlays->getFirst()->getData().getArtistTree()->erase(artistKey);
        }
    }

        // in case the song has 1 play or more
    else {

        // erasing the artist from the artist tree in his current playNode if the artist has no more songs with the playNode number of plays
        // also updating the max artist in the current playNode
        if ((artist->getData().getSongNodes()[songID]->getPrevious()== nullptr || artist->getData().getSongNodes()[songID]->getPrevious()->getKey().getSongNumberOfPlays() != artist->getData().getSongNodes()[songID]->getKey().getSongNumberOfPlays() )&&
            (artist->getData().getSongNodes()[songID]->getNext()== nullptr || artist->getData().getSongNodes()[songID]->getNext()->getKey().getSongNumberOfPlays() != artist->getData().getSongNodes()[songID]->getKey().getSongNumberOfPlays() ) ){
            previousArtistSave = artist->getData().getPlaysNodes()[songID]->getData().getArtistTree()->find(artistKey)->getPrevious();
            if (artist->getKey().getArtistID()==artist->getData().getPlaysNodes()[songID]->getData().getMinID()->getKey().getArtistID()){
                artist->getData().getPlaysNodes()[songID]->getData().setMinID(previousArtistSave);
            }
            artist->getData().getPlaysNodes()[songID]->getData().getArtistTree()->erase(artistKey);
        }

        // creating a new songNode with updated plays and inserting it to the artist songsTree
        // also updating the songNodes array
        newNumberOfPlays = songNode->getKey().getSongNumberOfPlays()+1;
        MusicManager::SongKey oldSongKey(songID,songNode->getKey().getSongNumberOfPlays());
        MusicManager::SongKey newSongKey(songID,newNumberOfPlays);
        artist->getData().getSongs()->erase(oldSongKey);
        artist->getData().getSongNodes()[songID] = artist->getData().getSongs()->insert(newSongKey,artistID);

        // updating the plays List in case the next node of the songPlays list is not the current+1
        if (artist->getData().getPlaysNodes()[songID]->getNext()== nullptr || artist->getData().getPlaysNodes()[songID]->getNext()->getKey()!=artist->getData().getPlaysNodes()[songID]->getKey()+1){
            MusicManager::PlaysData newPlaysData;
            int newPlaysNodeKey = artist->getData().getPlaysNodes()[songID]->getKey()+1;
            playsSave = songPlays->insertAfterNode(newPlaysNodeKey,newPlaysData,artist->getData().getPlaysNodes()[songID]);
            artistSave = artist->getData().getPlaysNodes()[songID]->getNext()->getData().getArtistTree()->insert(artistKey,artist);
            artist->getData().getPlaysNodes()[songID]->getNext()->getData().setMinID(artistSave);
        }

            // updating the plays List in case the next node of the songPlays list is the current+1
        else {
            playsSave = artist->getData().getPlaysNodes()[songID]->getNext();
            if ((artist->getData().getSongNodes()[songID]->getNext() == nullptr || artist->getData().getSongNodes()[songID]->getNext()->getKey().getSongNumberOfPlays()!=artist->getData().getSongNodes()[songID]->getKey().getSongNumberOfPlays() ) &&
                ( artist->getData().getSongNodes()[songID]->getPrevious() == nullptr || artist->getData().getSongNodes()[songID]->getPrevious()->getKey().getSongNumberOfPlays()!=artist->getData().getSongNodes()[songID]->getKey().getSongNumberOfPlays())){
                artistSave = artist->getData().getPlaysNodes()[songID]->getNext()->getData().getArtistTree()->insert(artistKey,artist);
                if (artistSave!= nullptr && artistSave->getKey().getArtistID()<artist->getData().getPlaysNodes()[songID]->getNext()->getData().getMinID()->getKey().getArtistID()){
                    artist->getData().getPlaysNodes()[songID]->getNext()->getData().setMinID(artistSave);
                }
            }
        }
    }

    // erasing current playNode if it is empty, if not finding a new max artist for the the current playNode
    if (artist->getData().getPlaysNodes()[songID]->getData().getArtistTree()->getRoot()==nullptr){
        songPlays->erase(artist->getData().getPlaysNodes()[songID]);
    }

    artist->getData().getPlaysNodes()[songID] = playsSave;



    // updating the artist info about the max song he has
    if (newNumberOfPlays>artist->getData().getMaxSongPlays()||
        (newNumberOfPlays==artist->getData().getMaxSongPlays() && artist->getData().getMaxSongID()>songID)){
        artist->getData().setMaxSongPlays(newNumberOfPlays);
        artist->getData().setMaxSongID(songID);
        artist->getData().setCurrentMaxNotCheckedSong(songID);
    }

    return SUCCESS;
}

