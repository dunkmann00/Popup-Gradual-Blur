//
//  ViewController.m
//  Popup Gradual Blur
//
//  Created by George Waters on 4/15/15.
//  Copyright (c) 2015 George Waters. All rights reserved.
//

#import "ViewController.h"
#import "GWPopupBlurView.h"

@interface ViewController () <UIImagePickerControllerDelegate, UINavigationControllerDelegate>

@property (strong, nonatomic) GWPopupBlurView *popupBlurView;
@property (weak, nonatomic) IBOutlet UIImageView *imageView;
@property (strong, nonatomic) IBOutlet UITapGestureRecognizer *tapGesture;
@property (strong, nonatomic) IBOutlet UIPanGestureRecognizer *panGesture;

@property (strong, nonatomic) IBOutlet UILabel *questionLabel;
@property (strong, nonatomic) IBOutlet UIButton *noButton;
@property (strong, nonatomic) IBOutlet UIButton *yesButton;

@property (nonatomic) BOOL blurOn;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    
    self.popupBlurView = [[GWPopupBlurView alloc] initWithFrame:self.view.bounds];
    self.popupBlurView.viewBlurLevel = 0.0;
    self.popupBlurView.viewBlurType = GWViewBlurTypeDark;
    
    [self.popupBlurView.contentView addSubview:self.questionLabel];
    [self.popupBlurView.contentView addSubview:self.yesButton];
    [self.popupBlurView.contentView addSubview:self.noButton];
    
    [self.view addSubview:self.popupBlurView];
    
    [self.popupBlurView addGestureRecognizer:self.tapGesture];
    [self.popupBlurView addGestureRecognizer:self.panGesture];
    
    self.yesButton.layer.cornerRadius = 15.0;
    self.yesButton.layer.borderWidth = 1.0;
    self.yesButton.layer.borderColor = [UIColor colorWithWhite:1.0 alpha:0.5].CGColor;
    
    self.noButton.layer.cornerRadius = 15.0;
    self.noButton.layer.borderWidth = 1.0;
    self.noButton.layer.borderColor = [UIColor colorWithWhite:1.0 alpha:0.5].CGColor;
    
    self.yesButton.titleLabel.adjustsFontSizeToFitWidth = YES;
    self.yesButton.titleLabel.minimumScaleFactor = 0.1;
    self.noButton.titleLabel.adjustsFontSizeToFitWidth = YES;
    self.noButton.titleLabel.minimumScaleFactor = 0.1;
}

-(void)viewWillTransitionToSize:(CGSize)size withTransitionCoordinator:(id<UIViewControllerTransitionCoordinator>)coordinator
{
    [super viewWillTransitionToSize:size withTransitionCoordinator:coordinator];
    [coordinator animateAlongsideTransition:^(id<UIViewControllerTransitionCoordinatorContext> context) {
        self.popupBlurView.frame = self.view.frame;
    } completion:nil];
}

-(void)viewDidAppear:(BOOL)animated
{
    if(!self.imageView.image)
    {
        [self presentImagePicker];
    }
}

-(void)presentImagePicker
{
    UIImagePickerController *imagePicker = [[UIImagePickerController alloc] init];
    imagePicker.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
    imagePicker.delegate = self;
    [self presentViewController:imagePicker animated:YES completion:nil];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (IBAction)tapGestureRecognized:(UITapGestureRecognizer *)sender {
    if(!self.blurOn)
    {
        self.questionLabel.frame = CGRectMake(8.0, self.view.frame.size.height / 2.0 - 50.0, self.view.frame.size.width - 16.0, 100.0);
        self.yesButton.frame = CGRectMake(8.0, self.questionLabel.frame.origin.y + self.questionLabel.frame.size.height + 8.0, self.view.frame.size.width / 2.0 - 12.0, 40.0);
        self.noButton.frame = CGRectMake(self.yesButton.frame.origin.x + self.yesButton.frame.size.width + 8.0, self.yesButton.frame.origin.y, self.yesButton.frame.size.width, 40.0);
        [self.popupBlurView animateContentOntoViewWithInitialVelocity:0.0 completion:^(BOOL finished) {
            self.blurOn = YES;
        }];
    }
}

- (IBAction)panGestureRecognized:(UIPanGestureRecognizer *)sender {
    
    if(self.blurOn)
    {
        if(sender.state == UIGestureRecognizerStateBegan || sender.state == UIGestureRecognizerStateChanged)
        {
            [self.popupBlurView setVerticalTranslationForContentView:[sender translationInView:self.view].y];
        }else if(sender.state == UIGestureRecognizerStateEnded || sender.state == UIGestureRecognizerStateCancelled)
        {
            CGFloat velocity = [sender velocityInView:self.view].y;
            if(velocity > 20.0)
            {
                [self.popupBlurView animateContentOffViewWithInitialVelocity:velocity completion:^(BOOL finished) {
                    self.blurOn = NO;
                }];
            }else{
                [self.popupBlurView animateContentOntoViewWithInitialVelocity:velocity completion:^(BOOL finished) {
                    
                }];
            }
        }
    }
}

- (IBAction)buttonPressed:(UIButton *)sender {
    [self.popupBlurView animateContentOffViewWithInitialVelocity:0.0 completion:^(BOOL finished) {
        self.blurOn = NO;
        
        if(sender == self.noButton)
        {
            [self presentImagePicker];
        }
    }];
}

-(void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    self.imageView.image = info[UIImagePickerControllerOriginalImage];
    [self.popupBlurView refreshBackground];
    [self dismissViewControllerAnimated:YES completion:^{
        
    }];
}

@end
