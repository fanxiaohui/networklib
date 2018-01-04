/*
 * base_string.hpp
 *
 *  Created on: 2013-10-25
 *      Author: tiankonguse
 */

#include <string>
using namespace std;

#ifndef BASE_STRING_HPP_
#define BASE_STRING_HPP_

/*
http_method + "&" +
url_encode( base_uri ) + "&" +
url_encode(
        “&”.join(
                sort( [url_encode ( k ) + "=" +url_encode ( v ) for k, v in paramesters.items() ]
        )
)
*/

std::string  _UrlEncode(const std::string& src){
	return UrlEncode(src);
}

string join(const vector<Parame>&parames, string joinChar){
	string output = "";

	int size = parames.size();
	output += _UrlEncode(parames[0].getName()) + "=" + _UrlEncode(parames[0].getVal());

	for(int i=1;i<size;i++){
		output += joinChar + _UrlEncode(parames[i].getName()) + "=" + _UrlEncode(parames[i].getVal());
	}

	return output;
}


string base_string(Url& url){
	string output = "";

	url.sortParames();

	output += url.getMethod();

	output += "&";

	output += _UrlEncode(url.getBaseUri());

	output += "&";
	const vector<Parame>&parames =  url.getParames();
	string joinedParames = join(parames, string("&"));

	output += _UrlEncode(joinedParames);

	return output;
}



#endif /* BASE_STRING_HPP_ */
