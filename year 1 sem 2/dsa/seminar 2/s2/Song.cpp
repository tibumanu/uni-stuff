

#include "Song.h"

#include <utility>

Song::Song() {
    title = "";
    artist = "";
    duration = Duration();
    link = "";
}

Song::Song(const std::string &a, const std::string &t, Duration d, const std::string &l):
artist(a), title{t}, duration(d), link(l)
{

}

Song::Song(const Song& songToBeCopied) {
    title = songToBeCopied.title;
    artist = songToBeCopied.artist;
    duration = songToBeCopied.duration;
    link = songToBeCopied.link;
}

Song::~Song() {
;
}


