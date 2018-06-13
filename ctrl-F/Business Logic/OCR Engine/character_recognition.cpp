//
//  character_recognition.cpp
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-05-31.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#include "character_recognition.hpp"

Ptr<SVM> svm;
static int count_p = NUM_THREADS;
vector<CharacterContour> contours;
Mat image;
Mat processedImage;
pthread_mutex_t mutexForCount = PTHREAD_MUTEX_INITIALIZER;
pthread_attr_t attr;
pthread_t threads[NUM_THREADS];

CharacterRecognition::CharacterRecognition(const string &modelPath) {
    
    _svm = Algorithm::load<SVM>(modelPath);
    
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

}


void CharacterRecognition::DetectContours(Mat &processedMatrix, vector<vector<Point>> &characterContours) {
    
    //: Finds contours on the image and returns vector
    findContours(processedMatrix.clone(), characterContours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
}


void *ParallelLoop(void *threadId) {
   
    long start = (long)threadId * (contours.size() / NUM_THREADS);
    long end = start + contours.size() / NUM_THREADS + ((long)threadId == NUM_THREADS - 1 ? contours.size() % NUM_THREADS : 0) - 1;
    
    if (contours.size() > 0 && start > 0 && end > 0 && start != end) {
        
        for (unsigned long i = start; i < end; i++) {
            
            cout << image.size() << " " << processedImage.size() << " " << contours.size() << " " << start << " " << end << endl;
            Mat extractedChar;

            resize(processedImage(contours[i].GetCharRect()), extractedChar, {RESIZED_IMAGE_WIDTH, RESIZED_IMAGE_HEIGHT});
            extractedChar.convertTo(extractedChar, CV_32FC1);
            rectangle(image, contours[i].GetCharRect(), Scalar(255, 255, 0), 2);

//            svm->predict(extractedChar.reshape(1 , 1));

            extractedChar.release();
        }
    }

    return NULL;
}


void* tFn(void* arg) {
    
    pthread_mutex_lock(&mutexForCount);
    count_p--;
    if(count_p <= NUM_THREADS) {
        
        pthread_t temp;
        pthread_create(&temp,&attr, ParallelLoop, arg);
        count_p++;
    }
    pthread_mutex_unlock(&mutexForCount);
    
    return NULL;
}


void CharacterRecognition::DetectWord(vector<CharacterContour> &validCharacterContours, Mat &originalMatrix, Mat &processedMatrix) {
    
    if (validCharacterContours.size() == 0) return;
    
//    vector<vector<CharacterContour>> textMatrix;
    
//    cout << validCharacterContours.size() << endl;
//    for (unsigned int i = 0; i < validCharacterContours.size(); i++) {
//
//        Mat extractedChar;
//
//        resize(processedMatrix(validCharacterContours[i].GetCharRect()), extractedChar, {RESIZED_IMAGE_WIDTH, RESIZED_IMAGE_HEIGHT});
//        extractedChar.convertTo(extractedChar, CV_32FC1);
//        rectangle(originalMatrix, validCharacterContours[i].GetCharRect(), Scalar(255, 255, 0), 2);
//
//        _svm->predict(extractedChar.reshape(1 , 1));
//    }
    
    contours = validCharacterContours;
    image = originalMatrix;
    processedImage = processedMatrix;
    
    
    
//    CharacterContour::SortCharacterContours(validCharacterContours, textMatrix);
    
//    //: Line in text
//    for (int iLine = 0; iLine < textMatrix.size(); iLine++) {
//
//        //: Each char in line
//        for (int iChar = 0; iChar < textMatrix[iLine].size(); iChar++) {
//
//            Mat extractedChar;
//
//            resize(processedMatrix(textMatrix[iLine][iChar].GetCharRect()), extractedChar, {RESIZED_IMAGE_WIDTH, RESIZED_IMAGE_HEIGHT});
//            extractedChar.convertTo(extractedChar, CV_32FC1);
//            rectangle(originalMatrix, textMatrix[iLine][iChar].GetCharRect(), Scalar(255, 255, 0), 2);
//
//            cout << _svm->predict(extractedChar.reshape(1 , 1)) << endl;
//        }
//    }
}


void CharacterRecognition::Pipeline(Mat &matrix) {
    
    Mat processedMatrix;
    vector<vector<Point>> characterContours;
    vector<CharacterContour> validCharacterContours;
    
    ImageProcessor::ProcessMat(matrix, processedMatrix);
    this->DetectContours(processedMatrix, characterContours);
    CharacterContour::FilterCharacterContours(characterContours, validCharacterContours);
    
    characterContours.clear();
    
    this->DetectWord(validCharacterContours, matrix, processedMatrix);
}
