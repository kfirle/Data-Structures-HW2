#include <iostream>

#include "MusicManager.h"

int main() {
    MusicManager* manager = new MusicManager();
    int best_song;
    int artist_id, song_ig;
    cout << "test 1: " << manager->addArtist(123)<< endl;
    cout << "test 2: " << manager->addArtist(456)<< endl;
    cout << "test 3: " << manager->AddSong(123,7)<< endl;
    cout << "test 4: " << manager->AddSong(123,4)<< endl;
    cout << "test 5: " << manager->AddSong(789,10)<< endl;
    cout << "test 6: " << manager->removeArtist(123) << endl;
    cout << "test 7: " << manager->removeArtist(0) << endl;
    cout << "test 8: " << manager->removeArtist(456) << endl;
    cout << "test 9: " << manager->addArtist(456)<< endl;
    cout << "test 10: " << manager->AddToSongCount(123,4,5)<< endl;
    cout << "test 11: " << manager->GetArtistBestSong(123,&best_song)<< endl;
    cout << "test 12: " << manager->GetRecommendedSongInPlace(3,&artist_id,&song_ig)<< endl;
    return 0;
}