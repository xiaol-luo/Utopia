
namespace Tool.Skill
{
    public struct TopTabIdx
    {
        public const int SCENE = 0;
        public const int SCENE_UNIT = 1;
        public const int SKILL = 2;
        public const int EFFECT = 3;

        public const int COUNT = 4;
    }

    public class SkillEditorTabSetting
    {
        public int tabIdx;
        public string tabName;
        public System.Action logicImpl;
    }

    public partial class SkillEditorWindowData
    {
        public const int WINDOW_FIX_WIDTH = 960;
        public const int WINDOW_MIN_HEIGHT = 640;

        public int topToobardx = 0;
        public SkillEditorTabSetting[] tabSettings = null;
    }
}