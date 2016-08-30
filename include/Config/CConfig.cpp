#include "CConfig.h"

BYTE CConfig::Read(DBCONFIG& dbconf)
{
	XMLDocument doc;

	if (doc.LoadFile("DBConfig.xml") != XML_SUCCESS) {
		printf(KRED "Cannot open DBConfig.xml. (%s)\n" KNRM, doc.ErrorName());
		return READ_ERROR;
	}

	XMLElement *pRoot = doc.RootElement();
	if (!pRoot) {
		printf("Cannot find root element inside DBConfig.xml.\n");
		return READ_ERROR;
	}

	XMLElement *pMysql = pRoot->FirstChildElement("mysql");
	if (!pMysql) {
		printf("Cannot find MySQL configuration.\n");
		return READ_ERROR;
	}

	XMLElement *pEle = pMysql->FirstChildElement("hostname");
	if (pEle)
		dbconf.szHostname = pEle->GetText() ? std::string(pEle->GetText()) : "";

	pEle = pMysql->FirstChildElement("port");
	if (pEle)
		dbconf.szPort = pEle->GetText() ? std::string(pEle->GetText()) : "";

	pEle = pMysql->FirstChildElement("user");
	if (pEle)
		dbconf.szUser = pEle->GetText() ? std::string(pEle->GetText()) : "";

	pEle = pMysql->FirstChildElement("password");
	if (pEle)
		dbconf.szPassword = pEle->GetText() ? std::string(pEle->GetText()) : "";

	pEle = pMysql->FirstChildElement("schema");
	if (pEle)
		dbconf.szSchema = pEle->GetText() ? std::string(pEle->GetText()) : "";

	XMLElement *pListen = pRoot->FirstChildElement("listen");
	if (!pMysql) {
		printf("Cannot find Listen configuration.\n");
		return READ_ERROR;
	}

	pEle = pListen->FirstChildElement("port");
	if (pEle)
		dbconf.wListenPort = pEle->GetText() ? atoi(pEle->GetText()) : 0;

	return READ_SUCCESS;
}

BYTE CConfig::Read(MAINCONFIG& mainconf)
{
	XMLDocument doc;

	if (doc.LoadFile("MainConfig.xml") != XML_SUCCESS) {
		printf(KRED "Cannot open MainConfig.xml. (%s)\n" KNRM, doc.ErrorName());
		return READ_ERROR;
	}

	XMLElement *pRoot = doc.RootElement();
	if (!pRoot) {
		printf("Cannot find root element inside MainConfig.xml.\n");
		return READ_ERROR;
	}

	XMLElement *pDBSrv = pRoot->FirstChildElement("dbserver");
	if (!pDBSrv) {
		printf("Cannot find DBServer Listen configuration.\n");
		return READ_ERROR;
	}

	XMLElement *pEle = pDBSrv->FirstChildElement("port");
	if (pEle)
		mainconf.wDBPort = pEle->GetText() ? atoi(pEle->GetText()) : 0;

	XMLElement *pMainSrv = pRoot->FirstChildElement("mainserver");
	if (!pMainSrv) {
		printf("Cannot find MainServer Listen configuration.\n");
		return READ_ERROR;
	}

	pEle = pMainSrv->FirstChildElement("port");
	if (pEle)
		mainconf.wMainPort = pEle->GetText() ? atoi(pEle->GetText()) : 0;

	return READ_SUCCESS;
}