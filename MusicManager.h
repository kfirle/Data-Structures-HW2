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

    class RankTreeSongKey;
    class ArtistSongsTreeByIdAndPlaysSongKey;
    class ArtistSongsTreeByIdAndPlaysSongData;
    class ArtistSongsTreeByIdSongData;
    class ArtistData;

    // key for the songs in the songsRankTree
    class RankTreeSongKey{
        int songID;
        int songNumberOfPlays;
        int artistID;

    public:

        RankTreeSongKey()= delete;
        RankTreeSongKey(RankTreeSongKey &songKey) = default;
        RankTreeSongKey(int songID,int songNumberOfPlays,int artistID);
        ~RankTreeSongKey()= default;
        int getSongID() const;
        int getSongNumberOfPlays() const;
        int getSongArtistID() const;
        friend bool operator>(const RankTreeSongKey &songKey1, const RankTreeSongKey &songKey2){
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
        friend bool operator<(const RankTreeSongKey &songKey1, const RankTreeSongKey &songKey2){
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
        friend bool operator==(RankTreeSongKey &songKey1,RankTreeSongKey &songKey2){
            if (songKey1.songNumberOfPlays!=songKey2.songNumberOfPlays)
                return false;
            if (songKey1.artistID!=songKey2.artistID)
                return false;
            else return songKey1.songID==songKey2.songID;
        };
    };

    // key for the songs in the songs tree that is sorted by the number of plays and than by the id
    class ArtistSongsTreeByIdAndPlaysSongKey{
        int songID;
        int songNumberOfPlays;

    public:

        ArtistSongsTreeByIdAndPlaysSongKey()= delete;
        ArtistSongsTreeByIdAndPlaysSongKey(ArtistSongsTreeByIdAndPlaysSongKey &songKey) = default;
        ArtistSongsTreeByIdAndPlaysSongKey(int songID,int songNumberOfPlays);
        ~ArtistSongsTreeByIdAndPlaysSongKey()= default;
        int getSongID() const;
        int getSongNumberOfPlays() const;
        friend bool operator>(const ArtistSongsTreeByIdAndPlaysSongKey &songKey1, const ArtistSongsTreeByIdAndPlaysSongKey &songKey2){
            if (songKey1.songNumberOfPlays>songKey2.songNumberOfPlays) return true;
            if (songKey1.songNumberOfPlays<songKey2.songNumberOfPlays) return false;
            else return songKey1.songID<songKey2.songID;
        };
        friend bool operator<(const ArtistSongsTreeByIdAndPlaysSongKey &songKey1, const ArtistSongsTreeByIdAndPlaysSongKey &songKey2){
            if (songKey1.songNumberOfPlays<songKey2.songNumberOfPlays) return true;
            if (songKey1.songNumberOfPlays>songKey2.songNumberOfPlays) return false;
            else return songKey1.songID>songKey2.songID;
        };
        friend bool operator==(ArtistSongsTreeByIdAndPlaysSongKey &songKey1,ArtistSongsTreeByIdAndPlaysSongKey &songKey2){
            if (songKey1.songNumberOfPlays!=songKey2.songNumberOfPlays)
                return false;
            else return songKey1.songID==songKey2.songID;
        };
    };

    // data for the songs in the songs tree that is sorted by the number of plays and than by the id
    class ArtistSongsTreeByIdAndPlaysSongData{
        AVLtree<int,ArtistSongsTreeByIdSongData>::AVLNode* songInSongsByIdTree;

        public:
        ArtistSongsTreeByIdAndPlaysSongData();
        ArtistSongsTreeByIdAndPlaysSongData(ArtistSongsTreeByIdAndPlaysSongData &songData) = default;
        explicit ArtistSongsTreeByIdAndPlaysSongData(AVLtree<int,ArtistSongsTreeByIdSongData>::AVLNode* songInSongsByIdTree);
        AVLtree<int,ArtistSongsTreeByIdSongData>::AVLNode *getSongInSongsByIdTree();
        void setSongInSongsByIdTree(AVLtree<int,ArtistSongsTreeByIdSongData>::AVLNode &songInSongsByIdTree);
    };

    // data for the songs in the songs tree that is sorted by the id
    class ArtistSongsTreeByIdSongData{
        AVLtree<ArtistSongsTreeByIdAndPlaysSongKey,ArtistSongsTreeByIdAndPlaysSongData>::AVLNode* songInSongsByIdAndPlaysTree;

        public:

        ArtistSongsTreeByIdSongData();
        ArtistSongsTreeByIdSongData(ArtistSongsTreeByIdSongData &songData) = default;
        explicit ArtistSongsTreeByIdSongData(AVLtree<ArtistSongsTreeByIdAndPlaysSongKey,ArtistSongsTreeByIdAndPlaysSongData>::AVLNode* songInSongsByIdAndPlaysTree);
        AVLtree<ArtistSongsTreeByIdAndPlaysSongKey,ArtistSongsTreeByIdAndPlaysSongData>::AVLNode *getSongInSongsByIdAndPlaysTree();
        void setSongInSongsByIdTree(AVLtree<ArtistSongsTreeByIdAndPlaysSongKey,ArtistSongsTreeByIdAndPlaysSongData>::AVLNode &songInSongsByIdAndPlaysTree);
    };

    // data for the artists in the chains in the hash table
    class ArtistData{
        AVLtree<int, ArtistSongsTreeByIdSongData>* songs_ordered_by_id;
        AVLtree<ArtistSongsTreeByIdAndPlaysSongKey,ArtistSongsTreeByIdAndPlaysSongData>* songs_ordered_by_plays_and_id;
        AVLtree<ArtistSongsTreeByIdAndPlaysSongKey,ArtistSongsTreeByIdAndPlaysSongData>::AVLNode* maxSong;

    public:

        ArtistData();
        ArtistData(ArtistData &artistData);
        ~ArtistData();
        AVLtree<ArtistSongsTreeByIdAndPlaysSongKey,ArtistSongsTreeByIdAndPlaysSongData>::AVLNode* getMaxSong();
        void setMaxSong(AVLtree<ArtistSongsTreeByIdAndPlaysSongKey,ArtistSongsTreeByIdAndPlaysSongData>::AVLNode &maxSong);
        AVLtree<ArtistSongsTreeByIdAndPlaysSongKey,ArtistSongsTreeByIdAndPlaysSongData>* getSongsTreeOrderedByPlaysAndId();
        AVLtree<int, ArtistSongsTreeByIdSongData>* getSongsTreeOrderedById();
    };

    // ---------- Properties ---------- //
    AVLRankTree<RankTreeSongKey,int>* songs;
    List<int,ArtistData>* artists;
    int artistsCounter;
    int songsCounter;
    int size;

    // ---------- private functions ---------- //

    int hashFunction(int id, int modulo);
    void extendArtistsArraySize();
    void shrinkArtistsArraySize();

    // ---------- public functions ---------- //

public:

    MusicManager();
    ~MusicManager();
    StatusType addArtist(int artistID);
    StatusType removeArtist(int artistID);
    StatusType AddSong(int artistID, int songID);
    StatusType RemoveSong(int artistID, int songID);
    StatusType AddToSongCount(int artistID, int songID, int count);
    StatusType GetArtistBestSong(int artistID, int * songID);
    StatusType GetRecommendedSongInPlace(int rank, int * artistID, int * songID);

};

#endif //AVLTREE_MUSICMANAGER_H