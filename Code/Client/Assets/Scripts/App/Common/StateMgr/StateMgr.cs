

using System;
using System.Collections.Generic;
using UnityEngine;

public class StateMgr<EId, CState> : IStateMgr<EId> where CState : IState<EId>, new()
{
    Dictionary<EId, CState> m_states = new Dictionary<EId, CState>();

    public bool AddState(CState state)
    {
        if (m_states.ContainsKey(state.Id))
            return false;
        m_states.Add(state.Id, state);
        return true;
    }

    public CState GetState(EId stateId)
    {
        CState ret = this.GetStateHelp(stateId) as CState;
        return ret;
    }

    protected override IState<EId> GetStateHelp(EId stateId)
    {
        CState ret = null;
        m_states.TryGetValue(stateId, out ret);
        return ret;
    }

    public CState activeState
    {
        get
        {
            return m_activeState as CState;
        }
    }

    public CState lastState
    {
        get
        {
            return m_lastState as CState;
        }
    }
}

