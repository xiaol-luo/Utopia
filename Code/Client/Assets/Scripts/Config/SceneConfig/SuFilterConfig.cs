
using System.Collections.Generic;
using UnityEngine;

namespace Config
{
    public enum EEffectFilterLimitNumPriority
    {
        None = 0,
        NearCaster,
        AwayCaster,
        NearTarget,
        AwayTarget,
    };

    public enum EEffectFilterAnchor
    {
        Caster,
        CastPos,
        TargetPos,
        TargetUnit,
        EffectTargetUnit,
        EffectTargetPos,
    };

    public enum EEffectFilterShape
    {
        None = 0,
        Circle,
        Rect,
        Sector,
    };

    public class JsonVector2
    {
        public JsonVector2() { }
        public JsonVector2(Vector2 val)
        {
            x = val.x;
            y = val.y;
        }

        public Vector2 MakeVector2()
        {
            return new Vector2(x, y);
        }

        public float x;
        public float y;
    }

    public class SuFilterConfig
    {
        public int id;
        public string name;
        public int limit_num;
        public EEffectFilterLimitNumPriority limit_num_priority;
        public SceneUnitType unit_type_flag;
        public SceneUnitRelation relation_flag;
        public EEffectFilterAnchor anchor;
        public EEffectFilterShape shape_type;
        public float shape_circle;
        public JsonVector2 shape_rect = new JsonVector2();
        public JsonVector2 shape_sector = new JsonVector2();
    }
}
