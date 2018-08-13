using Config;
using System.Collections.Generic;
using UnityEditor;
using UnityEngine;

namespace Tool.Skill
{
    public partial class SkillEditorWindow : EditorWindow
    {
        void SceneTabLogicImpl()
        {
            SceneTabData sceneTabData = editorData.sceneTabData;
            using (new GUILayout.HorizontalScope())
            {
                {
                    var sceneNames = sceneTabData.GetSceneNames().ToArray();
                    var sceneIds = sceneTabData.GetSceneIds().ToArray();
                    sceneTabData.selecteds.sceneId = EditorGUILayout.IntPopup(sceneTabData.selecteds.sceneId, sceneNames, sceneIds);
                }

                if (GUILayout.Button("new scene"))
                {
                    int nextId = sceneTabData.GetNextSceneId();
                    var newCfg = new Config.SceneConfig()
                    {
                        id = nextId,
                        name = string.Format("scene_{0}", nextId)
                    };
                    sceneTabData.sceneConfig.cfgs.Add(newCfg);
                    sceneTabData.selecteds.sceneId = newCfg.id;
                }
                if (GUILayout.Button("delete scene"))
                {
                    SceneConfig sceneCfg = sceneTabData.GetSceneConfig(sceneTabData.selecteds.sceneId);
                    if (null != sceneCfg)
                    {
                        sceneTabData.sceneConfig.cfgs.Remove(sceneCfg);
                    }
                }
            }

            SceneConfig currSceneCfg = sceneTabData.GetSceneConfig(sceneTabData.selecteds.sceneId);
            if (null == currSceneCfg)
                return;

            using (new GUILayout.VerticalScope())
            {
                float defaultLabelWidth = EditorGUIUtility.labelWidth;
                EditorGUIUtility.labelWidth = 120;
                currSceneCfg.name = EditorGUILayout.TextField("name", currSceneCfg.name);

                var suNames = editorData.suTabData.GetSuNames().ToArray();
                var suIds = editorData.suTabData.GetSuIds().ToArray();

                currSceneCfg.red_side_hero = EditorGUILayout.IntPopup("red hero", currSceneCfg.red_side_hero, suNames, suIds);
                currSceneCfg.blue_side_hero = EditorGUILayout.IntPopup("blue hero", currSceneCfg.blue_side_hero, suNames, suIds);

                EditorGUIUtility.labelWidth = defaultLabelWidth;
            }
        }
    }
}