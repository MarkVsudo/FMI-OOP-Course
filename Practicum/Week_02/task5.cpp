// Създайте структура, която представлява песен, която съдържа следните характеристики:

// заглавие (до 100 символа)
// изпълнител (до 100 символа)
// жанр (може да бъде Rock, Pop, Thrash Metal, K-pop, Chalga)
// рейтинг (дробно число от 0 до 5)
// брой слушания (цяло число)

// Създайте структура Playlist, която се описва с най-много 64 песни. Реализирайте следните функции:

// добавяне на песен в колекцията (ако капацитетът е запълнен, принтирайте подходящо съобщение)
// връщане на указател към песен по подаден предикат, приемащ като аргумент 1 песен
// сортиране на песните по подаден предикат, приемащ като аргументи 2 песни

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

enum Genre
{
  ROCK = 1,
  POP,
  THRASH_METAL,
  K_POP,
  CHALGA
};

struct Song
{
  unsigned long long streams;
  double rating;
  Genre genre;
  char title[100];
  char artist[100];
};

struct Playlist
{
  const unsigned cap = 64;
  unsigned size = 0;
  Song songs[64];
};

void printPlaylist(const Playlist &playlist)
{
  for (unsigned i = 0; i < playlist.size; i++)
  {
    cout << "-- Song " << i + 1 << " --" << endl;
    cout << "Streams: " << playlist.songs[i].streams << endl;
    cout << "Rating: " << playlist.songs[i].rating << endl;
    cout << "Genre: " << playlist.songs[i].genre << endl;
    cout << "Title: " << playlist.songs[i].title << endl;
    cout << "Artist: " << playlist.songs[i].artist << endl;
  }
}

Song readSongData(Song &song)
{
  cout << "-- Enter data for a song --" << endl;

  do
  {
    cout << "Enter song streams: ";
    cin >> song.streams;
  } while (song.streams < 0);

  do
  {
    cout << "Enter song rating (0 - 5): ";
    cin >> song.rating;
  } while (song.rating < 0 || song.rating > 5);

  int genreChoice;
  do
  {
    cout << "Enter song genre:\n"
            "1) Rock\n"
            "2) Pop\n"
            "3) Thrash Metal\n"
            "4) K-Pop\n"
            "5) Chalga\n"
            "Choice: ";
    cin >> genreChoice;

  } while (genreChoice < 1 || genreChoice > 5);

  song.genre = (Genre)genreChoice;

  cout << "Enter song title: ";
  cin.ignore();
  cin.getline(song.title, 100);

  cout << "Enter artist name: ";
  cin.getline(song.artist, 100);

  return song;
}

void addSong(Playlist &playlist, const Song &song)
{
  if (playlist.size >= playlist.cap)
  {
    cout << "Playlist is full. Cannot add more songs." << endl;
    return;
  }

  playlist.songs[playlist.size] = song;
  playlist.size++;

  cout << "Song added successfully: " << song.title << " by " << song.artist << endl;
}

bool hasGoodRating(const Song &song)
{
  return song.rating >= 4;
}

Song *findSong(Playlist &playlist, bool (*predicate)(const Song &))
{
  for (unsigned i = 0; i < playlist.size; i++)
  {
    if (predicate(playlist.songs[i]))
      return &playlist.songs[i];
  }

  return nullptr;
}

bool hasHigherRating(const Song &song1, const Song &song2)
{
  return song1.rating > song2.rating;
}

void sortSongs(Playlist &playlist, bool (*predicate)(const Song &, const Song &))
{
  // Bubble sort
  for (unsigned i = 0; i < playlist.size - 1; i++)
  {
    for (unsigned j = 0; j < playlist.size - i - 1; j++)
    {
      if (predicate(playlist.songs[j], playlist.songs[j + 1]))
      {
        Song tempSong = playlist.songs[j];
        playlist.songs[j] = playlist.songs[j + 1];
        playlist.songs[j + 1] = tempSong;
      }
    }
  }
}

int main()
{

  Playlist testPlaylist;
  Song testSong1, testSong2, testSong3;

  readSongData(testSong1);
  addSong(testPlaylist, testSong1);
  readSongData(testSong2);
  addSong(testPlaylist, testSong2);
  readSongData(testSong3);
  addSong(testPlaylist, testSong3);

  Song *foundSong = findSong(testPlaylist, hasGoodRating);

  if (foundSong)
  {
    cout << "Found song: " << foundSong->title << endl;
  }
  else
  {
    cout << "No song found with this condition!";
  }

  cout << "-- Playlist before sorting --" << endl;
  printPlaylist(testPlaylist);

  cout << "-- Playlist after sorting --" << endl;
  sortSongs(testPlaylist, hasHigherRating);
  printPlaylist(testPlaylist);

  return 0;
}