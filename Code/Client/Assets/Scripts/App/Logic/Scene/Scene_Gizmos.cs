using NetProto;
using Utopia;

namespace Utopia
{
    public partial class Scene
    {
        ViewGridGizmos m_vgg = null;
        void Gizmos_OnSceneLoaded()
        {
            m_vgg = ViewGridGizmos.GetViewGridGizmosFromScene();
            App.instance.net.gameSrv.Add(PID.ViewAllGrids, (int id, ViewAllGrids msg) =>
            {
                m_vgg.SetAllGrids(msg);
            });
            App.instance.net.gameSrv.Add(PID.ViewSnapshot, (int id, ViewSnapshot msg) =>
            {
                m_vgg.SetSnapshot(msg);
            });
            App.instance.net.gameSrv.Add(PID.ViewSnapshotDiff, (int id, ViewSnapshotDiff msg) =>
            {
                m_vgg.SetSnapshotDiff(msg);
            });
        }

        void Gizmos_LeaveScene()
        {
            App.instance.net.gameSrv.Remove(PID.ViewAllGrids);
            App.instance.net.gameSrv.Remove(PID.ViewSnapshot);
            App.instance.net.gameSrv.Remove(PID.ViewSnapshotDiff);
            m_vgg = null;
        }
    }
}
