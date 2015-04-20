//
//  GWViewBlurType.h
//  Gradual Blur
//
//  Created by George Waters on 4/18/15.
//  Copyright (c) 2015 George Waters. All rights reserved.
//

#ifndef Gradual_Blur_GWViewBlurType_h
#define Gradual_Blur_GWViewBlurType_h

/**
 @typedef GWViewBlurType
 
 @constant GWViewBlurTypeExtraLight Creates a blur effect equivalent to UIBlurEffectStyleExtraLight.
 @constant GWViewBlurTypeLight Creates a blur effect equivalent to UIBlurEffectStyleLight.
 @constant GWViewBlurTypeDark Creates a blur effect equivalent to UIBlurEffectStyleDark.
 
 @abstract Blur styles available for a GWGradualBlurView or GWPopupBlurView.
 */
typedef NS_ENUM(NSInteger, GWViewBlurType) {
    /**Creates a blur effect equivalent to UIBlurEffectStyleExtraLight.*/
    GWViewBlurTypeExtraLight,
    /**GWViewBlurTypeLight Creates a blur effect equivalent to UIBlurEffectStyleLight.*/
    GWViewBlurTypeLight,
    /**GWViewBlurTypeDark Creates a blur effect equivalent to UIBlurEffectStyleDark.*/
    GWViewBlurTypeDark
};

#endif
