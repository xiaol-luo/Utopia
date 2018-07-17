
public abstract class IState
{
    public IState(IStateMgr stateMgr, int id)
    {
        m_stateMgr = stateMgr;
        Id = id;
    }

    public abstract void Enter(params object[] objs);
    public abstract void Exit(params object[] objs);
    public abstract void Update(params object[] objs);

    protected IStateMgr m_stateMgr;
    public int Id { get; protected set; }
}
