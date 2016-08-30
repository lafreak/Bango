#ifndef _CCONFIG_
#define _CCONFIG_

#include <string>

#include <minwindef.h>

#include <TinyXML2/tinyxml2.h>

using namespace tinyxml2;

struct DBCONFIG
{
	std::string szHostname;
	std::string szPort;
	std::string szUser;
	std::string szPassword;
	std::string szSchema;
	WORD wListenPort;
};

struct MAINCONFIG
{
	WORD wDBPort;
	WORD wMainPort;
};

class CConfig
{

public:
	static BYTE Read(DBCONFIG& dbconf);
	static BYTE Read(MAINCONFIG& mainconf);

	enum {
		READ_ERROR,
		READ_SUCCESS,
	};
};

#endif