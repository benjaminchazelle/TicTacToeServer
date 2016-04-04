#include "Server.h"
#include "Query\Response.h"
#include "Query\ServerQuery.h"
#include "QueryUtils.h"

void Response::getIdentity(Server* server, getIdentityResponseQuery query) {

	std::string response = "";
		
	QueryUtils::headerBuilding(response);

	QueryUtils::setValue(response, "Response", "getIdentity");

	QueryUtils::setValue(response, "Pseudo", query.pseudo);

	QueryUtils::setErrors(response, query.queryErrors);

	QueryUtils::footerBuilding(response);

	server->sendTo(response, query.clients);

}
