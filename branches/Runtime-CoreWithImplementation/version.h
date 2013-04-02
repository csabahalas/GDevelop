#ifndef VERSION_H
#define VERSION_H

namespace AutoVersion{
	
	//Date Version Types
	static const char DATE[] = "19";
	static const char MONTH[] = "02";
	static const char YEAR[] = "2013";
	static const char UBUNTU_VERSION_STYLE[] = "13.02";
	
	//Software Status
	static const char STATUS[] = "Alpha";
	static const char STATUS_SHORT[] = "a";
	
	//Standard Version Type
	static const long MAJOR = 1;
	static const long MINOR = 0;
	static const long BUILD = 262;
	static const long REVISION = 1332;
	
	//Miscellaneous Version Types
	static const long BUILDS_COUNT = 1238;
	#define RC_FILEVERSION 1,0,262,1332
	#define RC_FILEVERSION_STRING "1, 0, 262, 1332\0"
	static const char FULLVERSION_STRING[] = "1.0.262.1332";
	
	//These values are to keep track of your versioning state, don't modify them.
	static const long BUILD_HISTORY = 0;
	

}
#endif //VERSION_H