
namespace Utopia
{
    public enum LogLevel
    {
        Debug,
        Info,
        Waring,
        Error,
        Exception,
        Assert,
    }
    public class LogModule : CoreModule
    {
        public LogModule(Core _app) : base(_app, EModule.LogModule)
        {
            
        }

        LogLevel m_logLvl = LogLevel.Debug;
        public void SetLogLvl(LogLevel lvl)
        {
            m_logLvl = lvl;
        }
        public LogLevel logLvl { get { return m_logLvl; } }

        public void LogDebug(string format, params object[] args)
        {
            this.Log(LogLevel.Debug, format, args);
        }
        public void LogInfo(string format, params object[] args)
        {
            this.Log(LogLevel.Info, format, args);
        }

        public void LogWarning(string format, params object[] args)
        {
            this.Log(LogLevel.Waring, format, args);
        }

        public void LogError(string format, params object[] args)
        {
            this.Log(LogLevel.Error, format, args);
        }

        public void LogException(System.Exception e)
        {
            this.Log(LogLevel.Exception, "{0}", e.ToString());
        }

        public void LogAssert(bool isTrue, string format, params object[] args)
        {
            if (!isTrue)
            {
                this.Log(LogLevel.Assert, format, args);
            }
        }

        public void Log(LogLevel lvl, string format, params object[] args)
        {
            if (lvl < m_logLvl)
                return;

            switch(lvl)
            {
                case LogLevel.Debug:
                case LogLevel.Info:
                    {
                        UnityEngine.Debug.LogFormat(format, args);
                    }
                    break;
                case LogLevel.Waring:
                    {
                        UnityEngine.Debug.LogWarningFormat(format, args);
                    }
                    break;
                case LogLevel.Error:
                    {
                        UnityEngine.Debug.LogErrorFormat(format, args);
                    }
                    break;
                case LogLevel.Assert:
                    {
                        UnityEngine.Debug.LogAssertionFormat(format, args);
                    }
                    break;
                case LogLevel.Exception:
                    {
                        UnityEngine.Debug.LogErrorFormat(format, args);
                    }
                    break;
            }
        }
    }
}

