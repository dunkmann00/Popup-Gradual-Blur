//
//  GWPopupBlurView.h
//  Popup Gradual Blur
//
//  Created by George Waters on 3/1/15.
//  Copyright (c) 2015 George Waters. All rights reserved.
//

#import <GLKit/GLKit.h>

/**
 @typedef GWViewBlurType
 
 @constant GWViewBlurTypeExtraLight Creates a blur effect equivalent to UIBlurEffectStyleExtraLight.
 @constant GWViewBlurTypeLight Creates a blur effect equivalent to UIBlurEffectStyleLight.
 @constant GWViewBlurTypeDark Creates a blur effect equivalent to UIBlurEffectStyleDark.
 
 @abstract Blur styles available for a GWPopupBlurView.
 */
typedef NS_ENUM(NSInteger, GWViewBlurType) {
    /**Creates a blur effect equivalent to UIBlurEffectStyleExtraLight.*/
    GWViewBlurTypeExtraLight,
    /**GWViewBlurTypeLight Creates a blur effect equivalent to UIBlurEffectStyleLight.*/
    GWViewBlurTypeLight,
    /**GWViewBlurTypeDark Creates a blur effect equivalent to UIBlurEffectStyleDark.*/
    GWViewBlurTypeDark
};
/**
 A GWPopupBlurView object provides a way to add a blur over views that gradually animates onto the screen. It also lets you add views to its contentView so they can be slid onto the GWPopupBlurView in coordination with the blur using a spring animation.
 
 This can be used to achieve the effect of content being slid onto the screen while everything below that content is gradually blurred out of focus.
 
 The view takes a snapshot of what is behind it and applies the blur to that snapshot. If you want the view to update the snapshot of what is behind it you can call the refreshBackground method. Since the GWPopupBlurView is used to provide an overlay on top of content that is in the "background," there usually is not too many changes going on. This is why the static snapshot of what is behind the blurred view is still an effective way to represent what is actually behind the view. However, if changes do occur you can easily update the background to represent those changes. The view is capable of handling the refresh with good performance but would not be able to if it was being updated in real time.
 */
@interface GWPopupBlurView : UIView
/**
 The type of blur displayed by the view.
 
 This is GWViewBlurTypeLight by default.
 */
@property (nonatomic) GWViewBlurType viewBlurType;
/**
 The level of blur that the view should display.
 
 This is a value that is between 0.0 and 1.0 inclusive. 1.0 represents full blur and 0.0 represents no blur at all. The default value is 1.0.
 */
@property (nonatomic) CGFloat viewBlurLevel;
/**
 The view that any subviews should be added to.
 
 Subviews that you want to add to the GWPopupBlurView should be added to contentView rather than the view directly. All subviews in the content view will animate onto & off the view when the animation methods of this class are called.
 */
@property (weak, nonatomic, readonly) UIView *contentView;
/**
 @param velocity The initial spring velocity of the subviews on the content view. If the content view was being dragged up or down you can use this to match the speed of that drag for a smooth start to the animation. Velocity is in p/s, exactly how it is represented with a pan gesture recognizer.
 @param completionHandler A block object to be executed when the animation sequence ends. This block has no return value and takes a single Boolean argument that indicates whether or not the animations actually finished before the completion handler was called. This parameter may be NULL.
 
 Animates the content view onto the view to a vertical translation of 0.0. Using this to move the content view also causes the blur level to change. When the content view is below the GWPopupBlurView the blur is 0.0 and as it animates on, the blur gradually increases to 1.0. When the content view has no subviews this method will still animate the blur level.
 */
-(void)animateContentOntoViewWithInitialVelocity:(CGFloat)velocity completion:(void (^)(BOOL finished))completionHandler;
/**
 @param velocity The initial spring velocity of the subviews on the content view. If the content view was being dragged up or down you can use this to match the speed of that drag for a smooth start to the animation. Velocity is in p/s, exactly how it is represented with a pan gesture recognizer.
 @param completionHandler A block object to be executed when the animation sequence ends. This block has no return value and takes a single Boolean argument that indicates whether or not the animations actually finished before the completion handler was called. This parameter may be NULL.
 
 Animates the content view off the view to a vertical translation set to the height of the blur view. Using this to move the content view also causes the blur level to change. When the content view is directly on the GWPopupBlurView the blur is 1.0 and as it animates off, the blur gradually decreases to 0.0. When the content view has no subviews this method will still animate the blur level.
 */
-(void)animateContentOffViewWithInitialVelocity:(CGFloat)velocity completion:(void(^)(BOOL finished))completionHandler;
/**
 @param yTranslation The distance to translate the content view vertically.
 
 Sets how far the center of the content view should be offset against the center of the GWPopupBlurView. The content view can only be moved down and the maximum amount it can be moved is the height of the GWPopupBlurView. As the content view is moved the blur level is also changed. When the content view is directly on top of the GWPopupBlurView (yTranslation of 0.0) the blur level is 1.0, and when the content view is directly below the view the blur level is 0.0. The blur level is directly proportional to the location of the content view.
 */
-(void)setVerticalTranslationForContentView:(CGFloat)yTranslation;
/**
 Tells the gradual blur view to refresh its background.
 
 This method will capture whatever content is currently behind the view and update its appearance. This is called internally whenever the gradual blur view is added to a new superview or when its frame changes. Anytime a view behind the gradual blur view has changed and you want the gradual blur view to show the change, you must call this method.
 */
-(void)refreshBackground;

@end
