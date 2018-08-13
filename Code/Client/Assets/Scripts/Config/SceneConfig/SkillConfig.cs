
using System.Collections.Generic;

namespace Config
{
    public class SkillConfig
    {
        public int id = 0;
        public string name = string.Empty;
        public bool is_normal_attack;

        public enum UseWay
        {
            target = 1,
            direction,
            postion,
        }
        public UseWay use_way = UseWay.target;
        public enum TargetType
        {
            hero,
            soldier,
            monster,
            building,
            effect,
        }
        public TargetType target_type_flag = 0;

        
        public enum TargetRelation
        {
            self,
            friend, // not include self?
            enemy,
        }
        public TargetRelation target_relation_flag;

        public List<SkillLevelConfig> lvl_cfgs = new List<SkillLevelConfig>();
    }

    public class SkillLevelConfig
    {
        public int preparing_span;
        public int releasing_span;
        public int lasting_span;
        public int consume_mp;
        public int cd;
        public float cast_distance;
        public bool can_move;
        public int effect_id;

        public SkillLevelConfig CloneSelf()
        {
            SkillLevelConfig ret = new SkillLevelConfig();
            ret.preparing_span = this.preparing_span;
            ret.releasing_span = this.releasing_span;
            ret.lasting_span = this.lasting_span;
            ret.consume_mp = this.consume_mp;
            ret.cd = this.cd;
            ret.cast_distance = this.cast_distance;
            ret.can_move = this.can_move;
            ret.effect_id = this.effect_id;
            return ret;
        }
    }
}
