
#import "ofCocoa.h"
#import <AppKit/AppKit.h>

void cocoaInit()
{
NSApplicationLoad();
}

void cocoaAlert(const char *title, const char *message, unsigned type)
{
NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
NSAlert *alert = [[NSAlert alloc] init];
[alert addButtonWithTitle:@"OK"];
[alert setMessageText:[NSString stringWithUTF8String:title]];
[alert setInformativeText:[NSString stringWithUTF8String:message]];
[alert setAlertStyle:type];
[alert runModal];
[pool release];
}
