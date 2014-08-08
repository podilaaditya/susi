/*
 * Copyright (c) 2014, webvariants GmbH, http://www.webvariants.de
 *
 * This file is released under the terms of the MIT license. You can find the
 * complete text in the attached LICENSE file or online at:
 *
 * http://www.opensource.org/licenses/mit-license.php
 * 
 * @author: Tino Rusch (tino.rusch@webvariants.de)
 */

#ifndef __TCPCLIENT__
#define __TCPCLIENT__

#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/dns.h>

#include <arpa/inet.h>
#include <thread>

namespace Susi{
namespace Api{

class TCPClient {
protected:
	struct event_base *base;
    struct bufferevent *bev;
    std::thread runloop;
    std::string _sessionID;
    
public:

    virtual void onConnect(){};
    virtual void onData(std::string & data) = 0;
    virtual void onClose(){};
	
	TCPClient(std::string host, unsigned short port);
	
	void send(std::string & data);
	void close();
	void join();
	void stop();

	virtual ~TCPClient();

};

}
}

#endif // __TCPCLIENT__