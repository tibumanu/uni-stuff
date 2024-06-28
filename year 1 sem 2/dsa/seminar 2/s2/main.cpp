#include <iostream>
#include "Duration.h"
#include "Song.h"
#include "DynamicVector.h"

int main() {
    Duration d = Duration();
    Duration d2();
    Duration d3;
    Song song;
    Song song2("artist!", "title!", Duration(3, 49), "lolcome.com");
    Song song3 = Song(song);
    Song song4 = song3;
    Song song5; song5 = song3;

    DynamicVector dv1;
    DynamicVector dv2(dv1);
    DynamicVector dv3 = dv1;
    return 0;
}
