//
// httpget.cpp
//
// This sample demonstrates the HTTPClientSession and the HTTPCredentials classes.
//
// Copyright (c) 2005-2012, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include <Poco/Net/HTTPCredentials.h>
#include "Poco/StreamCopier.h"
#include "Poco/NullStream.h"
#include "Poco/Path.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"
#include "Poco/Net/HTMLForm.h"
#include <iostream>



bool doRequest(Poco::Net::HTTPClientSession& session, Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response)
{
	session.sendRequest(request);
	std::istream& rs = session.receiveResponse(response);
	std::cout << response.getStatus() << " " << response.getReason() << std::endl;
	if (response.getStatus() != Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED)
	{
		Poco::StreamCopier::copyStream(rs, std::cout);
		return true;
	}
	else
	{
		Poco::NullOutputStream null;
		Poco::StreamCopier::copyStream(rs, null);
		return false;
	}
}


int main(int argc, char** argv)
{
    try
    {
        // json
        std::string body("{key:value}");

        // uri
        //Poco::URI uri("http://www.baidu.com/test");
        Poco::URI uri("http://127.0.0.1:3000/");
        // session
        Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());
        session.setKeepAlive(true);

        // request
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, uri.getPathAndQuery(), Poco::Net::HTTPRequest::HTTP_1_1);
        request.setContentType("application/text");
        request.add("Accept", "Agent-007");
        request.add("User-Agent", "xxxxoooo");
        request.setContentLength(body.length());
        //
        session.sendRequest(request) << body;


        // response
        Poco::Net::HTTPResponse res;
        std::string recv_string;
        std::istream & is = session.receiveResponse(res);
        int result = (int)res.getStatus();
        std::cout << "result:" << result << ", reason:" << res.getReason() << std::endl;
        Poco::StreamCopier::copyToString(is, recv_string);
        std::cout << "recv : " << std::endl << recv_string << std::endl;

        std::string recv_body = res.get("body");
        std::cout << "body : " << std::endl << recv_body << std::endl;
    }
	catch (Poco::Exception& exc)
	{
		std::cerr << exc.displayText() << std::endl;
		return 1;
	}
	return 0;
}

