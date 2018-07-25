//
//  ViewController.mm
//  TestGL
//
//  Created by Graham Asher on 15/11/2017.
//  Copyright © 2017 CartoType. All rights reserved.
//

#import "ViewController.h"
#import <CartoType/CartoType.h>
#import <vector>

@implementation ViewController

// instance variables
{
CartoTypeFramework* m_framework;
int m_ui_scale;
CartoTypePoint m_route_start;
CartoTypePoint m_route_end;
CartoTypeRoute* m_route;
std::vector<CartoTypePoint> m_route_points;
CGPoint m_current_point;
}

-(id)initWithFramework:(CartoTypeFramework*)aFramework
    {
    if (!(self = [super init]))
        return nil;
    if (aFramework == nil)
        return nil;
    m_framework = aFramework;
    return self;
    }

-(void)viewDidLoad
    {
    [super viewDidLoad];

    // Create a pan gesture recognizer.
    UIPanGestureRecognizer* my_pan_recognizer = [[UIPanGestureRecognizer alloc] initWithTarget:self action:@selector(handlePanGesture:)];
    my_pan_recognizer.delegate = self;
    [self.view addGestureRecognizer:my_pan_recognizer];
    
    // Create a pinch gesture recognizer.
    UIPinchGestureRecognizer* my_pinch_recognizer = [[UIPinchGestureRecognizer alloc] initWithTarget:self action:@selector(handlePinchGesture:)];
    my_pinch_recognizer.delegate = self;
    [self.view addGestureRecognizer:my_pinch_recognizer];
    
    // Create a rotation gesture recognizer.
    UIRotationGestureRecognizer* my_rotation_recognizer = [[UIRotationGestureRecognizer alloc] initWithTarget:self action:@selector(handleRotationGesture:)];
    my_rotation_recognizer.delegate = self;
    [self.view addGestureRecognizer:my_rotation_recognizer];
    
    // Create a tap gesture recognizer.
    UITapGestureRecognizer* my_tap_recognizer = [[UITapGestureRecognizer alloc] initWithTarget:self action:@selector(handleTapGesture:)];
    my_tap_recognizer.delegate = self;
    [self.view addGestureRecognizer:my_tap_recognizer];
    
    m_ui_scale = [[UIScreen mainScreen] scale];
    m_route = nullptr;
    
    self.view.multipleTouchEnabled = YES;
    }

-(IBAction)handlePanGesture:(UIPanGestureRecognizer*)aRecognizer
    {
    if ([aRecognizer state] == UIGestureRecognizerStateChanged)
        {
        auto t = [aRecognizer translationInView:nil];
        [m_framework panX:-t.x * m_ui_scale andY:-t.y * m_ui_scale];
        t.x = t.y = 0;
        [aRecognizer setTranslation:t inView:nil];
        }
    else if ([aRecognizer state] == UIGestureRecognizerStateRecognized)
        {
        }
    else if ([aRecognizer state] == UIGestureRecognizerStateCancelled)
        {
        }
    }

-(IBAction)handlePinchGesture:(UIPinchGestureRecognizer*)aRecognizer
    {
    if ([aRecognizer state] == UIGestureRecognizerStateChanged)
        {
        CGPoint p = [aRecognizer locationInView:nullptr];
        [m_framework zoomAt:[aRecognizer scale] x:p.x * m_ui_scale y:p.y * m_ui_scale coordType:DisplayCoordType];
        aRecognizer.scale = 1;
        }
    else if ([aRecognizer state] == UIGestureRecognizerStateRecognized)
        {
        }
    else if ([aRecognizer state] == UIGestureRecognizerStateCancelled)
        {
        
        }
    }

-(IBAction)handleRotationGesture:(UIRotationGestureRecognizer*)aRecognizer
    {
    if ([aRecognizer state] == UIGestureRecognizerStateChanged)
        {
        [m_framework rotate:[aRecognizer rotation] / M_PI * 180];
        [aRecognizer setRotation:0];
        }
    else if ([aRecognizer state] == UIGestureRecognizerStateRecognized)
        {
        }
    else if ([aRecognizer state] == UIGestureRecognizerStateCancelled)
        {
        }
    }

-(IBAction)handleTapGesture:(UITapGestureRecognizer*)aRecognizer
    {
    if ([aRecognizer state] == UIGestureRecognizerStateRecognized)
        {
        // hack: toggle perspective
        //[m_framework setPerspective:![m_framework getPerspective]];

        // Create a route between the last two points tapped.
        auto p = [aRecognizer locationInView:nullptr];
        m_route_start = m_route_end;
        m_route_end.x = p.x * m_ui_scale;
        m_route_end.y = p.y * m_ui_scale;
        [m_framework convertPoint:&m_route_end from:DisplayCoordType to:MapCoordType];
        if (m_route_start.x && m_route_start.y)
            [m_framework startNavigationFrom:m_route_start startCoordType:MapCoordType to:m_route_end endCoordType:MapCoordType];
        }
    }

-(void)didReceiveMemoryWarning
    {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
    }

-(BOOL)gestureRecognizer:(UIGestureRecognizer*)aR1 shouldRecognizeSimultaneouslyWithGestureRecognizer:(UIGestureRecognizer *)aR2
    {
    return YES;
    }

@end
