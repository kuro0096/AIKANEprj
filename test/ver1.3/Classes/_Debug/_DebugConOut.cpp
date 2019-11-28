#ifdef  _DEBUG
#include "_DebugConOut.h"

std::unique_ptr< _DebugConOut, _DebugConOut::_DebugConOutDeleter > _DebugConOut::s_instance(new _DebugConOut);	// •Ï”‚Ì²İ½Àİ½

_DebugConOut::_DebugConOut()
{
	// ÃŞÊŞ¯¸—pºİ¿°Ù‚Ì•\¦
//	HWND hWnd = GetForegroundWindow();

	AllocConsole();	// ºİ¿°Ù‚ğŠJ‚­
	freopen_s(&m_debugFp, "CONOUT$", "w", stdout);
	freopen_s(&m_debugFp, "CONOUT$", "r", stdin);

//	SetForegroundWindow(hWnd);
}

_DebugConOut::~_DebugConOut()
{
	FreeConsole();  // ºİ¿°Ù‚ğ•Â‚¶‚é
}
#endif	// _DEBUG
