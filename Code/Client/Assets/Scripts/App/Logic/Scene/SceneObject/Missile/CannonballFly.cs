using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CannonballFly : MonoBehaviour
{
    public Animator animator;
    public float flySecs;
    public Vector2 flySpeed;

    float upSecs = 0.0f;
    float downSecs = 0.0f;

    void Awake()
    {
        animator.speed = 0;
    }
    bool firstUpdate = true;
    float flyedSecs = 0.0f;
	// Update is called once per frame
	void Update ()
    {
        if (firstUpdate)
        {
            firstUpdate = false;
            foreach (AnimationClip clip in animator.runtimeAnimatorController.animationClips)
            {
                if ("Cannonball_Up" == clip.name)
                {
                    upSecs = clip.averageDuration;
                }
                if ("Cannonball_Down" == clip.name)
                {
                    downSecs = clip.averageDuration;
                }
            }
            if (upSecs + downSecs > 0)
            {
                animator.speed = (upSecs + downSecs) / flySecs;
            }
            return;
        }

        if (flyedSecs >= flySecs)
            return;

        float deltaSec = Time.deltaTime;
        if (flyedSecs + deltaSec > flySecs)
            deltaSec = flySecs - flyedSecs;
        flyedSecs += deltaSec;

        Vector2 mvLen = flySpeed * deltaSec;
        Vector3 retPos = this.transform.localPosition + new Vector3(mvLen.x, 0, mvLen.y);
        this.transform.localPosition = retPos;
    }
}
