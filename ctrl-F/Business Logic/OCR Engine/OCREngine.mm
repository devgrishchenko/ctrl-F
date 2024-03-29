//
//  OCREngine.m
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-05-29.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#import "OCREngine.h"
#import "character_recognition.hpp"

@implementation OCREngine

CharacterRecognition *_characterRecognition;


- (instancetype)init {
    
    if (self = [super init]) {
        
        _characterRecognition = new CharacterRecognition([self getModelPath]);
    }
    
    return self;
}


- (string)getModelPath {
    
    return [[[NSBundle mainBundle] pathForResource:@"knn-ocr" ofType:@"model"] UTF8String];
}


- (void)processBuffer :(CMSampleBufferRef)sampleBuffer :(NSString*)word {
    
    CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
    CVPixelBufferLockBaseAddress(imageBuffer, 0);
    
    unsigned char *buffer = (unsigned char *)CVPixelBufferGetBaseAddress(imageBuffer);
    
    Mat matrix;
    
    //: Get matrix
    ImageProcessor::Buffer2Mat(matrix, buffer,
                               (int)CVPixelBufferGetBytesPerRow(imageBuffer),
                               (int)CVPixelBufferGetHeight(imageBuffer),
                               (int)CVPixelBufferGetWidth(imageBuffer));
    
    CVPixelBufferUnlockBaseAddress(imageBuffer, kCVPixelBufferLock_ReadOnly);
    
    //: Recognition
    _characterRecognition->Pipeline(matrix, [word UTF8String]);
    
    CVPixelBufferLockBaseAddress(imageBuffer, 0);
    
    //: Get buffer back
    ImageProcessor::Mat2Buffer(matrix, buffer);

    CVPixelBufferUnlockBaseAddress(imageBuffer, 0);
    
    matrix.release();
}
@end
