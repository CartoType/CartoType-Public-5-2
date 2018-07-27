//
//  ViewController.h
//  TestGL
//
//  Created by Graham Asher on 15/11/2017.
//  Copyright © 2017 CartoType. All rights reserved.
//

#import <GLKit/GLKit.h>
#import "CartoTypeMapView.h"

@interface ViewController : GLKViewController <UIGestureRecognizerDelegate, UISearchBarDelegate>

-(id)initWithFramework:(CartoTypeFramework*)aFramework;

@end
