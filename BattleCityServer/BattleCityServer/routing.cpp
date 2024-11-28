#include "routing.h"

void http::Routing::Run(server::GameDatabase& gameDatabase)
{
	CROW_ROUTE(m_app, "/")([]() {
		return "Welcome!";
		});

	m_app.port(18080).multithreaded().run();
}
