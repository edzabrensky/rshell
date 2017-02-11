#include <string>
using namespace std;
class Connector {
	public:
	Connector();
	bool success;
	virtual void runCommand(string cmd);	
};
