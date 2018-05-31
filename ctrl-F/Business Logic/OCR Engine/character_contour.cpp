//
//  character_contour.cpp
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-05-31.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#include "character_contour.hpp"


CharacterContour::CharacterContour(const vector<Point> &charContour, const Rect &charRect, const float &charArea) {
    
    _charContour = charContour;
    _charRect = charRect;
    _charArea = charArea;
}


#pragma mark Getters

vector<Point> CharacterContour::GetCharContour() {
    
    return _charContour;
}


Rect CharacterContour::GetCharRect() {
    
    return _charRect;
}


float CharacterContour::GetCharArea() {
    
    return _charArea;
}


#pragma mark Sorting Character Contours

bool CharacterContour::SortYaxis(CharacterContour &left, CharacterContour &right) {
    
    return(left.GetCharRect().y < right.GetCharRect().y);
}


bool CharacterContour::SortXaxis(CharacterContour &left, CharacterContour &right) {
    
    return(left.GetCharRect().x < right.GetCharRect().x);
}
