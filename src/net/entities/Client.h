#ifndef CLIENT_H
#define CLIENT_H

#include <set>
#include <SFML/Network.hpp>
#include "../Shared.h"

struct Screen;
class ScreenManager;

struct Client
{
	typedef sf::Uint16 ID;

	typedef std::set<Screen*>::iterator screen_iterator;

	static const ID MYSELF = 0;

	bool remESO(Screen* screenToRemove);

	sf::TcpSocket socket;

	Screen *screenOwned, *screenCurrent;
	std::set<Screen*> externalScreenOccupancies;

	ID id;
	ClientParams params;
};

class ClientManager
{
public:
	typedef std::set<Client*> List;
	typedef List::iterator ListIter;

	ClientManager();
	ClientManager(ScreenManager* screenList);
	~ClientManager();

	void setScreenList(ScreenManager* screenList);
	Client* add();
	inline List& getList() { return clients; }
	bool rem(Client::ID id);
	bool rem(Client* c);
	ListIter rem(ListIter it);
	size_t remESOs(Screen* screenToRemove);
	void clear();

private:
	static Client::ID ID_CLIENT;

	ScreenManager* screens;
	List clients;
};

#endif // CLIENT_H