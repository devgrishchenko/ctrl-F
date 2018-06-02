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
#include <opencv2/imgproc/imgproc.hpp>

#define MIN_CONTOUR_AREA 5
#define MAX_CONTOUR_AREA 250

using namespace std;
using namespace cv;


class CharacterContour {
    
private:
    
    vector<cv::Point> _charContour;
    cv::Rect _charRect;
    float _charArea;
    
public:
    
    CharacterContour(const vector<cv::Point> &charContour);
    vector<cv::Point> GetCharContour();
    cv::Rect GetCharRect();
    float GetCharArea();
    
    static bool SortYaxis(CharacterContour &left, CharacterContour &right);
    static bool SortXaxis(CharacterContour &left, CharacterContour &right);
    static void SortCharacterContours(vector<CharacterContour> &characterContours, vector<vector<CharacterContour>> &textMatrix);
    static void FilterCharacterContours(vector<vector<cv::Point>> &characterContours, vector<CharacterContour> &validCharacterContours);
};
#endif
