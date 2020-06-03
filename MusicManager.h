//
// Created by Dell on 03/05/2020.
//

#ifndef AVLTREE_MUSICMANAGER_H
#define AVLTREE_MUSICMANAGER_H

#include "AVLtree.h"
#include "AVLRankTree.h"
#include "List.h"
#include "new"
#include "library2.h"

class MusicManager{

    // ---------- Subclasses ---------- //

    class SongKey;
    class ArtistKey;
    class ArtistData;
    class PlaysData;

    class SongKey{
        int songID;
        int songNumberOfPlays;
        int artistID;

    public:

        SongKey()= delete;
        SongKey(SongKey &songKey) = default;
        SongKey(int songID,int songNumberOfPlays);
        ~SongKey()= default;
        int getSongID() const;
        int getSongNumberOfPlays() const;
        friend bool operator>(const SongKey &songKey1, const SongKey &songKey2){
            if (songKey1.songNumberOfPlays>songKey2.songNumberOfPlays){
                return true;
            }
            if (songKey1.songNumberOfPlays<songKey2.songNumberOfPlays){
                return false;
            }
            if (songKey1.artistID<songKey2.artistID){
                return true;
            }
            if (songKey1.artistID>songKey2.artistID){
                return false;
            }
            return songKey1.songID<songKey2.songID;
        };
        friend bool operator<(const SongKey &songKey1, const SongKey &songKey2){
            if (songKey1.songNumberOfPlays<songKey2.songNumberOfPlays){
                return true;
            }
            if (songKey1.songNumberOfPlays>songKey2.songNumberOfPlays){
                return false;
            }
            if (songKey1.artistID>songKey2.artistID){
                return true;
            }
            if (songKey1.artistID<songKey2.artistID){
                return false;
            }
            return songKey1.songID>songKey2.songID;
        };
        friend bool operator==(SongKey &songKey1,SongKey &songKey2){
            if (songKey1.songNumberOfPlays!=songKey2.songNumberOfPlays)
                return false;
            if (songKey1.artistID!=songKey2.artistID)
                return false;
            else return songKey1.songID==songKey2.songID;
        };
    };

    class ArtistKey{
        int artistID;

    public:

        ArtistKey()= delete;
        ArtistKey(ArtistKey &artistKey)= default;
        explicit ArtistKey(int artistID);
        ~ArtistKey()= default;
        int getArtistID() const;
        friend bool operator>(const ArtistKey &artistKey1, const ArtistKey &artistKey2){
            return artistKey1.artistID<artistKey2.artistID;
        };
        friend bool operator<(const ArtistKey &artistKey1, const ArtistKey &artistKey2){
            return artistKey1.artistID>artistKey2.artistID;
        };
        friend bool operator==(ArtistKey &artistKey1, ArtistKey &artistKey2){
            return artistKey1.artistID==artistKey2.artistID;
        };
    };

    class PlaysData{
        AVLtree<SongKey,int>::AVLNode* songInArtistTree;

    public:

        PlaysData();
        PlaysData(PlaysData &playsData);
        ~PlaysData();
    };

    class ArtistData{
        AVLtree<SongKey,int>* songs_ordered_by_id;
        AVLtree<SongKey,int>* songs_ordered_by_plays;
        AVLRankTree<SongKey,int>::AVLNode* maxPlaysSong;

    public:

        ArtistData()= delete;
        ArtistData(ArtistData &artistData);
        explicit ArtistData(int numberOfSongs);
        ~ArtistData();
        AVLtree<SongKey,int>* &getSongs();
        AVLtree<SongKey,int>::AVLNode** &getSongNodes();
        List<int,PlaysData>::ListNode** &getPlaysNodes();
        AVLRankTree<SongKey,int>::AVLNode* getMaxSongPlays() const;
        void setMaxSongPlays(AVLRankTree<SongKey,int>::AVLNode* newMaxPlaysSong);
    };

    // ---------- Properties ---------- //
    AVLRankTree<SongKey,ArtistData>* songs;
    List<ArtistKey,ArtistData>* artists;
    int artistsCounter;
    int size;

    // ---------- private functions ---------- //

    void extendArtistsArraySize();
    int hashFunction(int id);

    // ---------- public functions ---------- //

public:

    MusicManager();
    ~MusicManager();
    StatusType addArtist(int artistID,int numOfSongs);
    StatusType removeArtist(int artistID);
    StatusType AddSong(int artistID, int songID);
    StatusType RemoveSong(int artistID, int songID);
    StatusType AddToSongCount(int artistID, int songID, int count);
    StatusType GetArtistBestSong(int artistID, int * songID);
    StatusType GetRecommendedSongInPlace(int rank, int * artistID, int * songID);

};

#endif //AVLTREE_MUSICMANAGER_H