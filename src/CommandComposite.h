#include "CommandComponent.h"
#include <vector>
class CommandComposite : public CommandComponent {
	//protected:
	//vector<CommandComponent *> v;
	public:
	vector<CommandComponent* > v;
	CommandComposite();
	Connector * getConnector();
	void add(CommandComponent *);
	void remove(int );

};
