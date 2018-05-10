
#if __has_include(<React/RCTBridgeModule.h>)
#import <React/RCTBridgeModule.h>
#else
#import "RCTBridgeModule.h"
#endif
#if __has_include(<React/RCTEventEmitter.h>)
#import <React/RCTEventEmitter.h>
#else
#import "RCTEventEmitter.h"
#endif
//#import "RCTEventEmitter.h"
#import "sdk/headers/PaymentsSDK.h"
@interface RNPayTm : RCTEventEmitter <RCTBridgeModule>

@end
  
