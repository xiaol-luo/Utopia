

using System;
using System.Collections.Generic;
using UnityEngine;

public abstract class IStateMgr
{
    protected abstract IState GetStateHelp(int stateId);
    public void ChangeState<T>(T stateId, bool isForce = false)
    {
        this.ChangeState((int)Convert.ChangeType(stateId, typeof(int)), isForce);
    }

    public void ChangeState(int stateId, bool isForce = false)
    {
        IState nextState = this.GetStateHelp(stateId);
        if (null == nextState)
        {
            Debug.LogError(string.Format("stateId {0} is null", stateId));
            return;
        }
        if (!isForce && null != m_activeState && m_activeState.Id == stateId)
            return;

        if (null != m_activeState)
            m_activeState.Exit();
        m_activeState = nextState;
        m_activeState.Enter();
    }

    public void UpdateState()
    {
        if (null != m_activeState)
            m_activeState.Update();
    }
    public IState GetState<T>(T stateId)
    {
        return this.GetStateHelp((int)Convert.ChangeType(stateId, typeof(int)));
    }

    protected IState m_activeState = null;
}
public class StateMgr<T> : IStateMgr where T : IState, new()
{
    Dictionary<int, IState> m_states = new Dictionary<int, IState>();
    protected override IState GetStateHelp(int stateId)
    {
        IState state = null;
        m_states.TryGetValue(stateId, out state);
        return state;
    }
    public bool AddState(T state)
    {
        if (m_states.ContainsKey(state.Id))
            return false;
        m_states.Add(state.Id, state);
        return true;
    }
}

