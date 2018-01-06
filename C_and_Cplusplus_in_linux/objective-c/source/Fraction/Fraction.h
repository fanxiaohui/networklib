/*************************************************************************
> File Name: Fraction.h
> Author: tiankonguse
> Mail: i@tiankonguse.com 
> Created Time: 2014年07月08日 星期二 09时59分39秒
***********************************************************************/

#import <Foundation/NSObject.h>
 
@interface Fraction: NSObject {
    int numerator;
    int denominator;
}
 
-(void) print;
-(void) setNumerator: (int) n;
-(void) setDenominator: (int) d;
-(int) numerator;
-(int) denominator;
@end

