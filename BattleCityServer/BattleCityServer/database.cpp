#include "database.h"

using namespace server;

void GameDatabase::Initialize()
{
	m_db.sync_schema();
}
