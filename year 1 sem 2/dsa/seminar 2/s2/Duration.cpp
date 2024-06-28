//
// Created by Tibuman on 22.03.2023.
//

#include "Duration.h"

Duration::Duration():minutes(0), seconds(0) {
;
}

Duration::Duration(int minutes, int seconds) {
    this->minutes = minutes;
    this->seconds = seconds;
}

int Duration::getMinutes() const {
    return minutes;
}

int Duration::getSeconds() const {
    return seconds;
}



