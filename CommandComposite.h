#include "CommandComponent.h"
#include <vector>
class CommandComposite : public CommandComponent {
	private:
	vector<CommandComponent *> v;
	public:
	CommandComposite();
	void add(CommandComponent *);
	void remove(int );

};
