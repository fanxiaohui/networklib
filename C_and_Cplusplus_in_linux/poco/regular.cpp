/*************************************************************************
  > File Name: regular.cpp
  > Author: tiankonguse
  > Mail: i@tiankonguse.com 
  > Created Time: Mon 31 Mar 2014 08:34:31 PM CST
***********************************************************************/

#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<string>
#include<Poco/RegularExpression.h>
#include <Poco/String.h>
using namespace std;
#ifdef __int64
typedef __int64 LL;
#else
typedef long long LL;
#endif
using Poco::RegularExpression;

int test(std::string &sReg,std:: string& str){
    RegularExpression re(sReg);
//    RegularExpression::Match match;
//    re.match(str, match);
//    if(match.length == 0 && match.offset == std::string::npos){
//        std::cout << "not match" << endl;
//    }else{
//        std::string res;
//        re.subst(res, "$1/$2/$3", RegularExpression::RE_GLOBAL);
//        if(res.size() > 0){
//            std::cout << " find " << res<< endl;
//        }else{
//            std::cout << "not find" << endl;
//        }
//    
//    }
    return 0;
}

int main() {
//    RegularExpression re("\\{\"plist_play_count\":\\d+,\"media_play_count\":\\d+,\"plist_score\":\\d+(.\\d+)?,\"plist_count\":\\d+,\"vcomm_count\":\\d+,\"pcomm_count\":\\d+}");
//    std::string str="{\"plist_play_count\":37238246,\"media_play_count\":0,\"plist_score\":9.5,\"plist_count\":168,\"vcomm_count\":0,\"pcomm_count\":1052}";
    
    
   std::string sReg = "/(\\d{4})-(\\d{2})-(\\d{2}/)";
   std::string str="2014-03-31";
    test(sReg, str);




    return 0;
}
