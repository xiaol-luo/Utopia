namespace GameLogic
{
	class NavMgr;
	class Scene;

	class MoveMgr
	{
	public:
		MoveMgr(Scene *scene);
		virtual ~MoveMgr();

		bool Awake();
		void Update();

	protected:
		Scene *m_scene = nullptr;
		NavMgr *m_navMgr = nullptr;
	};
}
