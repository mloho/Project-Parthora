#ifndef CLIENT_H
#define CLIENT_H

#include <set>
#include <SFML/Network.hpp>
#include "../Shared.h"
#include "../entities/Screen.h"

struct Client
{
	typedef std::set<Screen*> ESOList;
	typedef ESOList::iterator ESOListIter;

	static const EntityID MYSELF = 0;

	bool remESO(Screen* screenToRemove);

	sf::TcpSocket socket;

	Screen *screenOwned, *screenCurrent;
	ESOList externalScreenOccupancies;

	EntityID id;
	ClientParams params;
};

class ClientManager
{
public:
	typedef std::set<Client*> List;
	typedef List::iterator ListIter;

	ClientManager();
	~ClientManager();

	Client* add();
	inline List& getList() { return clients; }
	bool rem(EntityID id);
	bool rem(Client* c);
	ListIter rem(ListIter it);
	size_t remESOs(Screen* screenToRemove);
	void clear();

private:
	static EntityID ID_ENTITY;

	ScreenManager screens;
	List clients;
};

#endif // CLIENT_H
