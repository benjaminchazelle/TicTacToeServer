#ifndef QUERYUTILH
#define QUERYUTILH

#include <string>
#include <vector>
//#include "Player.h"
//#include "Query.h"
//#include "Server.h"

#include "Query/RequestQuery.h"

#include "Errors.h"
/*
class Server;
struct RequestQuery;
*/

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////Ensemble de fonctions permettant de mettre en forme les requêtes et les utiliser/////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
struct ParsedEntity{
	bool error;
	std::string key;
	T value;
};




class QueryUtils
{
private:
	static std::string getLine(std::string &buffer);
public:

	//static void nextLine(std::string &line);
	static bool headerParsing(std::string &buffer);
	static bool footerParsing(std::string &buffer);
	static ParsedEntity<std::string> getStringParsing(std::string &buffer);
	static ParsedEntity<int> getIntParsing(std::string &buffer);
	static ParsedEntity<bool> getBoolParsing(std::string &buffer);
	static ParsedEntity<std::vector<std::string> > getPseudoPlayersParsing(std::string &buffer);


	static void headerBuilding(std::string &response);

	static void setValue(std::string &response, std::string key, std::string value);
	static void setValue(std::string &response, std::string key, int value);

	static void setErrors(std::string &response, Errors);

	static void footerBuilding(std::string &response);

/*
static RequestQuery parseRequest (Server* server, std::string query);
static std::string buildResponse (Server* server, std::string query);
static std::string buildNotify (Server* server, std::string query);
*/
};

#endif