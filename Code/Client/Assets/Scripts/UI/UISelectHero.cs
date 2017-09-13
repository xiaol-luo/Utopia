using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class UISelectHero : MonoBehaviour {

    [SerializeField]
    Button redHeroBtn;
    [SerializeField]
    Button blueHeroBtn;

    const int RED_HERO_ID = 1;
    const int BLUE_HERO_ID = 2;

    void SetHeroCanSelect(bool canRedHero, bool canBlueHero)
    {
        redHeroBtn.gameObject.SetActive(canRedHero);
        blueHeroBtn.gameObject.SetActive(canBlueHero);
    }

	// Use this for initialization
	void Start ()
    {
        redHeroBtn.onClick.AddListener(() => { this.OnClickBtn(RED_HERO_ID); });
        redHeroBtn.onClick.AddListener(() => { this.OnClickBtn(BLUE_HERO_ID); });
    }
	
	// Update is called once per frame
	void Update ()
    {
		
	}
    void OnClickBtn(int heroId)
    {
    }
}
