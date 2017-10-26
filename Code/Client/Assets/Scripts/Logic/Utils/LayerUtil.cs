

using System;
using System.Collections.Generic;
using UnityEngine;

public enum ELayerType
{
    // built in 
    Default,
    TransparentFX,
    IgnoreRaycast,
    Water,
    UI,

    // self define
    Ground,
    SceneObject,
    Obstacle,
}

public static class LayerUtil
{
    static Dictionary<ELayerType, string> s_layerTypeNameMap = new Dictionary<ELayerType, string>()
    {
        { ELayerType.Default, "Default"},
        { ELayerType.TransparentFX, "TransparentFX"},
        { ELayerType.IgnoreRaycast, "Ignore Raycast"},
        { ELayerType.Water, "Water"},
        { ELayerType.UI, "UI"},
        { ELayerType.Ground, "Ground"},
        { ELayerType.SceneObject, "SceneObject"},
        { ELayerType.Obstacle, "Obstacle"},
    };

    public static int allMask { get; private set; }
    public static int noneMask { get; private set; }
    public static int uiMask { get; private set; }
    public static int groundMask { get; private set; }
    public static int terrianMask { get; private set; }
    public static int sceneObjectMask { get; private set; }

    public static void Init()
    {
        allMask = GetMaskExcept();
        noneMask = GetMask();
        uiMask = GetMask(ELayerType.UI);
        groundMask = GetMask(ELayerType.Ground);
        sceneObjectMask = GetMask(ELayerType.SceneObject);
        terrianMask = GetMask(ELayerType.Ground, ELayerType.Obstacle);

    }
    public static int GetMask(params ELayerType[] layers)
    {
        int mask = 0;
        if (null != layers && layers.Length > 0)
        {
            foreach (ELayerType layer in layers)
            {
                int layerIdx = LayerMask.NameToLayer(s_layerTypeNameMap[layer]);
                mask |= 1 << layerIdx;
            }
        }
        return mask;
    }
    public static int GetMaskExcept(params ELayerType[] layers)
    {
        if (null == layers || layers.Length <= 0)
            return -1;

        int mask = 0;
        HashSet<ELayerType> exceptLayers = new HashSet<ELayerType>(layers);
        foreach (var kvPair in s_layerTypeNameMap)
        {
            if (exceptLayers.Contains(kvPair.Key))
                continue;
            int layerIdx = LayerMask.NameToLayer(kvPair.Value);
            mask |= 1 << layerIdx;
        }
        return mask;
    }
}
