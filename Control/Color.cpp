//
// Created by chris on 3/5/18.
//

#include "Color.h"

Color::Color(int r, int g, int b){
    r_ = r;
    g_ = g;
    b_ = b;
}

int Color::getr() {
    return r_;
}

int Color::getg() {
    return g_;
}

int Color::getb() {
    return b_;
}

Color::Color() {
    r_ = 1;
    g_ = 1;
    b_ = 1;
}
