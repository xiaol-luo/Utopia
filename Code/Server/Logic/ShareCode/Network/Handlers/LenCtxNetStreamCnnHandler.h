#pragma once
#include "CommonModules/Network/INetworkHandler.h"
#include "Network/Utils/LenCtxStreamParserEx.h"
#include "Common/Macro/AllMacro.h"

class LenCtxNetStreamCnnHandler : public INetConnectHander
{
	NewDelOperaDeclaration;
public:
	LenCtxNetStreamCnnHandler(uint32_t max_per_ctx_len) 
		: m_parser(max_per_ctx_len) {}
	virtual ~LenCtxNetStreamCnnHandler() {}
	virtual void OnClose(int err_num) = 0;
	virtual void OnOpen(int err_num) = 0;
	virtual void OnRecvData(char *data, uint32_t len)
	{
		if (m_parser.AppendBuffer(data, len))
		{
			while (m_parser.ParseNext())
				this->OnParseSuccess(m_parser.Content(), m_parser.ContentLen());
			if (m_parser.IsFail())
				this->OnParseFail();
		}
	}

protected:
	virtual void OnParseSuccess(char *data, uint32_t len) = 0;
	virtual void OnParseFail() = 0;
	LenCtxStreamParserEx<uint32_t, NetSteamLenPraser<uint32_t, sizeof(uint32_t)>> m_parser;
};
