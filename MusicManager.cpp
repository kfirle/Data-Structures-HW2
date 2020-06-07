//
// Created by Dell on 05/05/2020.
//

#define INVALID_INDEX -1
#define INITIAL_ARRAY_SIZE 10
#define SHRINK_PROPORTION 20
#define INITIAL_PLAYS_NUMBER 0
#include "MusicManager.h"

// ---------- RankTreeSongKey implementation ---------- //

MusicManager::RankTreeSongKey::RankTreeSongKey(int songID, int songNumberOfPlays, int artistID):
        songID(songID),songNumberOfPlays(songNumberOfPlays),artistID(artistID){}

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

MusicManager::ArtistSongsTreeByIdAndPlaysSongKey::ArtistSongsTreeByIdAndPlaysSongKey(int songID, int songNumberOfPlays):
        songID(songID),songNumberOfPlays(songNumberOfPlays){}

int MusicManager::ArtistSongsTreeByIdAndPlaysSongKey::getSongID() const {
    return songID;
}

int MusicManager::ArtistSongsTreeByIdAndPlaysSongKey::getSongNumberOfPlays() const {
    return songNumberOfPlays;
}

// ---------- ArtistSongsTreeByIdAndPlaysSongData implementation ---------- //

MusicManager::ArtistSongsTreeByIdAndPlaysSongData::ArtistSongsTreeByIdAndPlaysSongData() {
    songInSongsByIdTree = nullptr;
}

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

MusicManager::ArtistSongsTreeByIdSongData::ArtistSongsTreeByIdSongData() {
    songInSongsByIdAndPlaysTree = nullptr;
}

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
    this->maxSong = artistData.maxSong;
    this->songs_ordered_by_id = new AVLtree<int,MusicManager::ArtistSongsTreeByIdSongData>();
    this->songs_ordered_by_plays_and_id = new AVLtree<MusicManager::ArtistSongsTreeByIdAndPlaysSongKey,ArtistSongsTreeByIdAndPlaysSongData>();
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

void MusicManager::ArtistData::setMaxSong(AVLtree<MusicManager::ArtistSongsTreeByIdAndPlaysSongKey, MusicManager::ArtistSongsTreeByIdAndPlaysSongData>::AVLNode &maxSong) {
    this->maxSong = &maxSong;
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
            List<int,ArtistData>::ListNode* next = current->getNext();
            this->artists[i].removeFromList(current);
            int hashResult = hashFunction(current->getKey(),newSize);
            newArtists[hashResult].insertFirst(current);
            current = next;
        }
    }
    this->size = newSize;
    delete[] this->artists;
    this->artists = newArtists;
}

void MusicManager::shrinkArtistsArraySize(){
    int newSize = this->size / 10;
    List<int,ArtistData>* newArtists = new List<int,ArtistData>[newSize];
    for(int i=0; i < this->size; i++){
        List<int,ArtistData>::ListNode* current = artists[i].getFirst();
        while(current != nullptr){
            List<int,ArtistData>::ListNode* next = current->getNext();
            this->artists[i].removeFromList(current);
            int hashResult = hashFunction(current->getKey(),newSize);
            newArtists[hashResult].insertFirst(current);
            current = next;
        }
    }
    this->size = newSize;
    delete[] this->artists;
    this->artists = newArtists;
}

// ---------- MusicManager implementation - public ---------- //

MusicManager::MusicManager() {
    songs = new AVLRankTree<RankTreeSongKey,int>();
    artists = new List<int,ArtistData>[INITIAL_ARRAY_SIZE];
    artistsCounter = 0;
    songsCounter = 0;
    size = INITIAL_ARRAY_SIZE;
}

MusicManager::~MusicManager() {
    delete[] artists;
    delete songs;
}

StatusType MusicManager::addArtist(int artistID) {
    MusicManager::ArtistData artistData;
    int hashResult = hashFunction(artistID,this->size);
    if(this->artists[hashResult].checkIfExist(artistID)){
        return FAILURE;
        //Because there is an artist with the same ID in the system
    }
    this->artists[hashResult].insertFirst(artistID, artistData);
    this->artistsCounter++;
    if(this->size == this->artistsCounter){
        this->extendArtistsArraySize();
    }
    return SUCCESS;
}

StatusType MusicManager::removeArtist(int artistID){
    int hashResult = hashFunction(artistID,this->size);
    List<int,ArtistData>::ListNode* artist;
    try {
        artist = this->artists[hashResult].findByKey(artistID);
    }
    catch (List<int,ArtistData>::NotFound_List &notFoundInList){
        return FAILURE;
    }
    if(artist->getData().getMaxSong() != nullptr){
        return FAILURE;
    }
    this->artists[hashResult].erase(artist);
    this->artistsCounter--;
    if(this->size != INITIAL_ARRAY_SIZE){
        if(this->size / artistsCounter >= SHRINK_PROPORTION){
            this->shrinkArtistsArraySize();
        }
    }
    return SUCCESS;
}

StatusType MusicManager::AddSong(int artistID, int songID) {
    int hashResult = hashFunction(artistID,this->size);
    List<int,ArtistData>::ListNode* artist;
    try {
        artist = this->artists[hashResult].findByKey(artistID);
    }
    catch (List<int,ArtistData>::NotFound_List &notFoundInList){
        return FAILURE;
    }
    try {
        artist->getData().getSongsTreeOrderedById()->find(songID);
    }
    catch (AVLtree<int,ArtistSongsTreeByIdSongData>::NotFound_AVLtree &notFoundAVLtree){
        // inserting the new song to the trees of the artist
        ArtistSongsTreeByIdSongData songByIdData;
        AVLtree<int,ArtistSongsTreeByIdSongData>::AVLNode* songByIdNode = artist->getData().getSongsTreeOrderedById()->insert(songID,songByIdData);
        ArtistSongsTreeByIdAndPlaysSongKey songByIdAndPlaysKey(songID,INITIAL_PLAYS_NUMBER);
        ArtistSongsTreeByIdAndPlaysSongData songByIdAndPlaysData;
        AVLtree<ArtistSongsTreeByIdAndPlaysSongKey,ArtistSongsTreeByIdAndPlaysSongData>::AVLNode* songByIdAndPlaysNode = artist->getData().getSongsTreeOrderedByPlaysAndId()->insert(songByIdAndPlaysKey,songByIdAndPlaysData);
        songByIdNode->getData().setSongInSongsByIdTree(*songByIdAndPlaysNode);
        songByIdAndPlaysNode->getData().setSongInSongsByIdTree(*songByIdNode);
        if(artist->getData().getMaxSong() == nullptr){
            artist->getData().setMaxSong(*songByIdAndPlaysNode);
        }
        else{
            if (artist->getData().getMaxSong()->getKey().getSongNumberOfPlays()<songByIdAndPlaysNode->getKey().getSongNumberOfPlays()
                || (artist->getData().getMaxSong()->getKey().getSongNumberOfPlays()==songByIdAndPlaysNode->getKey().getSongNumberOfPlays()
                    && artist->getData().getMaxSong()->getKey().getSongID()>songByIdAndPlaysNode->getKey().getSongID()))
                artist->getData().setMaxSong(*songByIdAndPlaysNode);
        }
        // inserting the new song to the rank tree of all the songs
        RankTreeSongKey songRankTreeKey(songID,INITIAL_PLAYS_NUMBER,artistID);
        songs->insert(songRankTreeKey,artistID);
        this->songsCounter++;
        return SUCCESS;
    }
    return FAILURE;
}

StatusType MusicManager::RemoveSong(int artistID, int songID){
    int hashResult = hashFunction(artistID,this->size);
    List<int,ArtistData>::ListNode* artist;
    try {
        artist = this->artists[hashResult].findByKey(artistID);
    }
    catch (List<int,ArtistData>::NotFound_List &notFoundInList){
        return FAILURE;
        //The artist doesn't exist in the system
    }
    AVLtree<int, MusicManager::ArtistSongsTreeByIdSongData>::AVLNode* song;
    try {
        song = artist->getData().getSongsTreeOrderedById()->find(songID);
    }
    catch (AVLtree<int,ArtistSongsTreeByIdSongData>::NotFound_AVLtree &NotFound_AVLtree){
        return FAILURE;
        //The song doesn't exist in the system
    }
    int num_of_plays = song->getData().getSongInSongsByIdAndPlaysTree()->getKey().getSongNumberOfPlays();
    // removing the song from the songs rank tree
    MusicManager::RankTreeSongKey RankTreeSongKey(songID,num_of_plays,artistID);
    this->songs->erase(RankTreeSongKey);
    // updating maxSong in the songs tree of the artist that is ordered by the id and the number of plays
    if (artist->getData().getMaxSong()->getKey().getSongID()==songID)
        artist->getData().setMaxSong(*artist->getData().getMaxSong()->getPrevious());
    // removing the song from the songs trees of the artist
    ArtistSongsTreeByIdAndPlaysSongKey key(songID,num_of_plays);
    artist->getData().getSongsTreeOrderedByPlaysAndId()->erase(key);
    artist->getData().getSongsTreeOrderedById()->erase(songID);
    this->songsCounter--;
    return SUCCESS;
}

StatusType MusicManager::AddToSongCount(int artistID, int songID, int count) {
    int hashResult = hashFunction(artistID,this->size);
    List<int,ArtistData>::ListNode* artist;
    AVLtree<int,ArtistSongsTreeByIdSongData>::AVLNode* songByIdNode;
    AVLtree<ArtistSongsTreeByIdAndPlaysSongKey,ArtistSongsTreeByIdAndPlaysSongData>::AVLNode* songByIdAndPlaysNode;
    try {
        artist = this->artists[hashResult].findByKey(artistID);
    }
    catch (List<int,ArtistData>::NotFound_List &notFoundInList){
        return FAILURE;
    }
    try {
        songByIdNode = artist->getData().getSongsTreeOrderedById()->find(songID);
    }
    catch (AVLtree<int,ArtistSongsTreeByIdSongData>::NotFound_AVLtree &notFoundAVLtree) {
        return FAILURE;
    }
    // removing the old song node with the old number of plays and inserting the new one (in the song tree of the artist)
    int songNumberOfPlays = songByIdNode->getData().getSongInSongsByIdAndPlaysTree()->getKey().getSongNumberOfPlays();
    ArtistSongsTreeByIdAndPlaysSongKey songByIdAndPlaysKey(songID,songNumberOfPlays);
    ArtistSongsTreeByIdAndPlaysSongKey newSongByIdAndPlaysKey(songID,songNumberOfPlays+count);
    ArtistSongsTreeByIdAndPlaysSongData newSongByIdAndPlaysData;
    artist->getData().getSongsTreeOrderedByPlaysAndId()->erase(songByIdAndPlaysKey);
    songByIdAndPlaysNode = artist->getData().getSongsTreeOrderedByPlaysAndId()->insert(newSongByIdAndPlaysKey,newSongByIdAndPlaysData);
    songByIdNode->getData().setSongInSongsByIdTree(*songByIdAndPlaysNode);
    songByIdAndPlaysNode->getData().setSongInSongsByIdTree(*songByIdNode);
    if (artist->getData().getMaxSong()->getKey().getSongNumberOfPlays()<songByIdAndPlaysNode->getKey().getSongNumberOfPlays()
        || (artist->getData().getMaxSong()->getKey().getSongNumberOfPlays()==songByIdAndPlaysNode->getKey().getSongNumberOfPlays()
            && artist->getData().getMaxSong()->getKey().getSongID()>songByIdAndPlaysNode->getKey().getSongID()))
        artist->getData().setMaxSong(*songByIdAndPlaysNode);
    // removing the old song node with the old number of plays and inserting the new one (in the songs rank tree)
    RankTreeSongKey songRankTreeKey(songID,songNumberOfPlays,artistID);
    RankTreeSongKey newSongRankTreeKey(songID,songNumberOfPlays+count,artistID);
    songs->erase(songRankTreeKey);
    songs->insert(newSongRankTreeKey,artistID);
    return SUCCESS;
}

StatusType MusicManager::GetArtistBestSong(int artistID, int* songID){
    int hashResult = hashFunction(artistID,this->size);
    List<int,ArtistData>::ListNode* artist;
    try {
        artist = this->artists[hashResult].findByKey(artistID);
    }
    catch (List<int,ArtistData>::NotFound_List &notFoundInList){
        return FAILURE;
        //The artist doesn't exist in the system
    }
    AVLtree<MusicManager::ArtistSongsTreeByIdAndPlaysSongKey,MusicManager::ArtistSongsTreeByIdAndPlaysSongData>::AVLNode* max_song = artist->getData().getMaxSong();
    if(max_song == nullptr){
        return FAILURE;
        //The artist doesn't have songs
    }
    *songID = max_song->getKey().getSongID();
    return SUCCESS;
}

StatusType MusicManager::GetRecommendedSongInPlace(int rank, int *artistID, int *songID) {
    if (songsCounter<rank)
        return FAILURE;
    AVLRankTree<RankTreeSongKey,int>::AVLNode* songInRank = songs->select(songsCounter-rank+1);
    *artistID = songInRank->getKey().getSongArtistID();
    *songID = songInRank->getKey().getSongID();
    return SUCCESS;
}
