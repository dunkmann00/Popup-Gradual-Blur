# Popup-Gradual-Blur

<img src="/Popup Gradual Blur/ScreenCapture.gif" align="right">
Gradually animate the blurring of background content and have views popup over the blur.

A GWPopupBlurView object provides a way to add a blur over views that gradually animates onto the screen. It also lets you add views to its contentView so they can be slid onto the GWPopupBlurView in coordination with the blur using a spring animation.
 
This can be used to achieve the effect of content being slid onto the screen while everything below that content is gradually blurred out of focus.
 
The view takes a snapshot of what is behind it and applies the blur to that snapshot. If you want the view to update the snapshot of what is behind it you can call the refreshBackground method. Since the GWPopupBlurView is used to provide an overlay on top of content that is in the "background," there usually is not too many changes going on. This is why the static snapshot of what is behind the blurred view is still an effective way to represent what is actually behind the view. However, if changes do occur you can easily update the background to represent those changes. The view is capable of handling the refresh with good performance but would not be able to if it was being updated in real time.

The Xcode project in the repository has a working example of the popup gradual blur in use. When you tap the photo that was selected from your photo library the blur will animate onto the screen. Tapping 'yes' or 'no' animates it off and dragging it down makes the blur and content adjust to the distance dragged.
