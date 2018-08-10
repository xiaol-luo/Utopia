
using System.Collections.Generic;

namespace Config
{
    public class SkillConfig
    {
        int id = 0;
        string name = string.Empty;
        bool is_normal_attack;

        public enum UseWay
        {
            target,
            direction,
            postion,
        }
        UseWay use_way = UseWay.target;
        public enum TargetType
        {
            hero,
            soldier,
            monster,
            building,
            effect,
        }
        HashSet<TargetType> target_types = new HashSet<TargetType>();
        
        public enum TargetRelation
        {
            self,
            friend, // not include self?
            enemy,
        }
        HashSet<TargetRelation> target_relations = new HashSet<TargetRelation>();

        List<SkillLevelConfig> level_cfgs = new List<SkillLevelConfig>();
    }

    public class SkillLevelConfig
    {
        int preparing_span;
        int releasing_span;

        List<int> effect_ids = new List<int>();
    }
}
