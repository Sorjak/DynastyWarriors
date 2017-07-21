#include "Utils.h"

/**
* Log an SDL error with some error message to the output stream of our choice
* @param os The output stream to write the message too
* @param msg The error message to write, format will be msg error: SDL_GetError()
*/
void logSDLError(ostream &os, const string &msg){
	os << msg << " error: " << SDL_GetError() << endl;
}

vector<string> getKeysFromMap(map<string, BaseComponent*> input) {
	vector<string> output;
	for(map<string,BaseComponent*>::iterator it = input.begin(); it != input.end(); ++it) {
	  output.push_back(it->first);
	}

	return output;
}

float smoothGradient(float val, float a, float b) {
    return pow(val, a) / (pow(val, a) + pow(b - b * val, a));
}
