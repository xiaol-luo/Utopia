using Google.Protobuf;
using System.Collections.Generic;

namespace Utopia.Net
{
    public class GameSrvNetProxy : CommonNetProxy
    {
        public void Add<T>(NetProto.PID protocolId, System.Action<int, T> action) where T : IMessage, new()
        {
            NetMsgHandler<T> handler = new NetMsgHandler<T>(action);
            msgHandlers.Add((int)protocolId, handler);
        }
        public void Add(NetProto.PID protocolId, System.Action<int> action)
        {
            NetMsgHandler handler = new NetMsgHandler(action);
            msgHandlers.Add((int)protocolId, handler);
        }
        public void Add<T>(NetProto.PID protocolId) where T : IMessage, new()
        {
            NetMsgHandler<T> handler = new NetMsgHandler<T>(DefaultMsgHandlerAction);
            msgHandlers.Add((int)protocolId, handler);
        }
        public void Add(NetProto.PID protocolId)
        {
            NetMsgHandler handler = new NetMsgHandler(DefaultMsgHandlerAction);
            msgHandlers.Add((int)protocolId, handler);
        }

        public static string ProtoEventName(NetProto.PID protoId)
        {
            string ret = string.Format(NetModuleEventDef.ProtocolEventKeyFormat, protoId);
            return ret;
        }
        public override void DefaultMsgHandlerAction(int protocolId)
        {
            string evKey = ProtoEventName((NetProto.PID)protocolId);
            m_evProxy.Fire(evKey);
        }
        public override void DefaultMsgHandlerAction<T>(int protocolId, T msg)
        {
            string evKey = ProtoEventName((NetProto.PID)protocolId);
            m_evProxy.Fire(evKey, msg);
        }

        public void Remove(NetProto.PID protocolId)
        {
            this.Remove((int)protocolId);
        }
    }
}