#pragma  once 

class GameLogicModule;

namespace GameLogic
{
	class PlayerMgr
	{
	public: 
		PlayerMgr(GameLogicModule *logic_module);
		~PlayerMgr();

	protected:
		GameLogicModule *m_logic_module = nullptr;
	};
}