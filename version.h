#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "18";
	static const char MONTH[] = "07";
	static const char YEAR[] = "2019";
	static const char UBUNTU_VERSION_STYLE[] =  "19.07";
	
	//Software Status
	static const char STATUS[] =  "Alpha";
	static const char STATUS_SHORT[] =  "a";
	
	//Standard Version Type
	static const long MAJOR  = 1;
	static const long MINOR  = 71;
	static const long BUILD  = 6037;
	static const long REVISION  = 32831;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT  = 13365;
	#define RC_FILEVERSION 1,71,6037,32831
	#define RC_FILEVERSION_STRING "1, 71, 6037, 32831\0"
	static const char FULLVERSION_STRING [] = "1.71.6037.32831";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY  = 37;
	

}
#endif //VERSION_H
