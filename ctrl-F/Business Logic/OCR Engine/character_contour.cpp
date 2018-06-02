//
//  character_contour.cpp
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-05-31.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#include "character_contour.hpp"


CharacterContour::CharacterContour(const vector<Point> &charContour) {
    
    _charContour = charContour;
    _charRect = boundingRect(charContour);
    _charArea = contourArea(charContour);
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


#pragma mark Sorting & Filtering Character Contours

bool CharacterContour::SortYaxis(CharacterContour &left, CharacterContour &right) {
    
    return(left.GetCharRect().y < right.GetCharRect().y);
}


bool CharacterContour::SortXaxis(CharacterContour &left, CharacterContour &right) {
    
    return(left.GetCharRect().x < right.GetCharRect().x);
}


void CharacterContour::SortCharacterContours(vector<CharacterContour> &characterContours, vector<vector<CharacterContour>> &textMatrix) {
    
    // Sorts contours from top to bottom
    sort(characterContours.begin(), characterContours.end(), CharacterContour::SortYaxis);
    
    vector<CharacterContour> line;
    
    //: Sets the Y coordinate of the first line
    int temp = characterContours[0].GetCharRect().y;
    
    for (int i = 0; i < characterContours.size(); i++) {
        
        //: Determines if the next character located on the next line
        if (characterContours[i].GetCharRect().y > temp + 10) {
            
            //: Sorts contours by X coordinate
            sort(line.begin(), line.end(), CharacterContour::SortXaxis);
            
            textMatrix.push_back(line);
            
            //: Clean up for the next line
            line.clear();
            
            //: Sets the Y coordinate of the next line
            temp = characterContours[i].GetCharRect().y;
        }
        
        line.push_back(characterContours[i]);
    }
    
    sort(line.begin(), line.end(), CharacterContour::SortXaxis);
    textMatrix.push_back(line);
    
    //: Clean up
    line.clear();
}


void CharacterContour::FilterCharacterContours(vector<vector<Point>> &characterContours, vector<CharacterContour> &validCharacterContours) {
    
    for (unsigned int i = 0; i < characterContours.size(); i++) {
        
        if (contourArea(characterContours[i]) > MIN_CONTOUR_AREA && contourArea(characterContours[i]) < MAX_CONTOUR_AREA) {
        
            validCharacterContours.push_back(CharacterContour(characterContours[i]));
        }
    }
}
