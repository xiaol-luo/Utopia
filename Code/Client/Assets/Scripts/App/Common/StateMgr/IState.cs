
public abstract class IState
{
    public IState(IStateMgr stateMgr, int id)
    {
        m_stateMgr = stateMgr;
        Id = id;
    }

    public abstract void Enter(object param);
    public abstract void Exit();
    public abstract void Update();

    protected IStateMgr m_stateMgr;
    public int Id { get; protected set; }
}
