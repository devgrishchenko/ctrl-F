//
//  OCREngine.h
//  ctrl-F
//
//  Created by Igor Grishchenko on 2018-05-29.
//  Copyright © 2018 Igor Grishchenko. All rights reserved.
//

#import <CoreMedia/CoreMedia.h>
#import <UIKit/UIKit.h>

@interface OCREngine : NSObject

- (instancetype)init;
- (void)processBuffer :(CMSampleBufferRef)sampleBuffer;
@end
