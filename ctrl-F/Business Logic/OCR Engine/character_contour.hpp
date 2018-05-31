//
//  character_contour.hpp
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-05-31.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#ifndef character_contour_hpp
#define character_contour_hpp

#include <opencv2/core/core.hpp>


using namespace std;
using namespace cv;


class CharacterContour {
    
private:
    
    vector<Point> _charContour;
    Rect _charRect;
    float _charArea;
    
public:
    
    CharacterContour(const vector<Point> &charContour, const Rect &charRect, const float &charArea);
    static bool SortYaxis(CharacterContour &left, CharacterContour &right);
    static bool SortXaxis(CharacterContour &left, CharacterContour &right);
    static vector<vector<CharacterContour>> SortCharacterContours(vector<CharacterContour> &characterContours);
    vector<Point> GetCharContour();
    Rect GetCharRect();
    float GetCharArea();
};
#endif
