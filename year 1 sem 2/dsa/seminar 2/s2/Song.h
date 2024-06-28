#pragma once
#include <string>
#include "Duration.h"


class Song{
    std::string artist;
    std::string title;
    Duration duration;
    std::string link;

public:
    Song();
    Song(const std::string &artist, const std::string &title, Duration duration, const std::string &link);
    Song(const Song&);

    ~Song();
};


