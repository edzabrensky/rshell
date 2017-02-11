#include "CommandComponent.h"
#include <vector>
class CommandComposite : public CommandComponent {
	protected:
	vector<CommandComponent *> v;
	public:
	CommandComposite();
	void add(CommandComponent *);
	void remove(int );

};
