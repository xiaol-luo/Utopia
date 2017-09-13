
public class GameConfig
{
    public Config.CsvConfigSets csvCfgSet { get; protected set; }
    public string errMsg { get; protected set; }
    public int errno { get; protected set; }
    public GameConfig()
    {
        this.ClearError();
    }

    public void ClearError()
    {
        errno = 0;
        errMsg = string.Empty;
    }

    public void Awake()
    {
        csvCfgSet = new Config.CsvConfigSets();
    }
    public bool Start()
    {
        bool ret = false;
        do
        {
            if (!csvCfgSet.Load("Resources/Config/AutoCsvConfig"))
            {
                errno = 1;
                errMsg = csvCfgSet.errMsg;
                break;
            }

            ret = true;

        } while (false);

        return ret;
    }   
}