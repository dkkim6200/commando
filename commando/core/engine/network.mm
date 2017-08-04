#include "main.h"

#include <Foundation/Foundation.h>

void Network::sendRequest(string operation, string userId, string password) {
    NSMutableURLRequest *request = [[NSMutableURLRequest alloc] initWithURL:[NSURL URLWithString:@"http://localhost:8080/galaga_server/MerchantServer"]];
    
    //	NSString *jsonString = @"{\"id\": \"" + self.id.text + "\", \"pwd\": \"qwe123\"}";
    
    NSString *jsonString = [NSString stringWithFormat: @"%@%@%@%@%@%@%@",
                            @"{\"operation\":\"",[NSString stringWithUTF8String:operation.c_str()],@"\", \"id\":\"",[NSString stringWithUTF8String:userId.c_str()],@"\", \"pwd\":\"",[NSString stringWithUTF8String:password.c_str()], @"\"}"];
    
    [request setHTTPMethod:@"POST"];
    [request setValue:@"application/json" forHTTPHeaderField:@"Content-type"];
    [request setValue:[NSString stringWithFormat:@"%lu", (unsigned long)[jsonString length]] forHTTPHeaderField:@"Content-length"];
    [request setHTTPBody:[jsonString dataUsingEncoding:NSUTF8StringEncoding]];
    
    //	NSURLConnection *conn = [[NSURLConnection alloc] initWithRequest:request delegate:self];
    NSOperationQueue *queue = [[NSOperationQueue alloc] init];
    [NSURLConnection sendAsynchronousRequest:request queue:queue completionHandler:^(NSURLResponse *response, NSData *data, NSError *error)
     {
     NSString *responseString = [[NSString alloc] initWithData:data encoding:NSASCIIStringEncoding];
     NSLog(@"sendAsynchronousRequest(): %@", responseString);
     if (error) {
     NSLog(@"Error,%@", [error localizedDescription]);
     }
     
     if([[[NSString alloc] initWithData:data encoding:NSASCIIStringEncoding]  isEqual: @""]){
     
     NSLog(@"invalid username or password!");
     }
     else{
     NSLog(@"Login Successful!");
     }
     
     }];
    
    NSLog(@"===== TEST =====");
}