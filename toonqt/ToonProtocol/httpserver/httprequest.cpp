//#include "stdafx.h"
#include "httprequest.h"

#include "httpconnection.h"

HttpRequest::HttpRequest(HttpConnection *connection, QObject *parent)
    : QObject(parent)
    , m_connection(connection)
    , m_url("http://localhost/")
    , m_remotePort(0)
{
}

HttpRequest::~HttpRequest()
{
}

