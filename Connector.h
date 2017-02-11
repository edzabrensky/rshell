#include <string>
using namespace std;
class Connector {
	public:
	Connector();
	bool success;
	virtual int runCommand(string cmd);	
};
