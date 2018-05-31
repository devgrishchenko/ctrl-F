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


vector<vector<CharacterContour>> CharacterContour::SortCharacterContours(vector<CharacterContour> &characterContours) {
    
    // Sorts contours from top to bottom
    sort(characterContours.begin(), characterContours.end(), CharacterContour::SortYaxis);
    
    vector<vector<CharacterContour>> matrix;
    vector<CharacterContour> single;
    
    //: Sets the Y coordinate of the first line
    int temp = characterContours[0].GetCharRect().y;
    
    for (int i = 0; i < characterContours.size(); i++) {
        
        //: Determines if the next character located on the next line
        if (characterContours[i].GetCharRect().y > temp + 10) {
            
            //: Sorts contours by X coordinate
            sort(single.begin(), single.end(), CharacterContour::SortXaxis);
            
            matrix.push_back(single);
            
            //: Clean up for the next line
            single.clear();
            
            //: Sets the Y coordinate of the next line
            temp = characterContours[i].GetCharRect().y;
        }
        
        single.push_back(characterContours[i]);
    }
    
    sort(single.begin(), single.end(), CharacterContour::SortXaxis);
    matrix.push_back(single);
    
    //: Clean up
    single.clear();
    
    return matrix;
}
