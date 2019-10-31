#ifdef  _DEBUG
#include "_DebugConOut.h"

std::unique_ptr< _DebugConOut, _DebugConOut::_DebugConOutDeleter > _DebugConOut::s_Instance(new _DebugConOut);	// 変数のｲﾝｽﾀﾝｽ

_DebugConOut::_DebugConOut()
{
	// ﾃﾞﾊﾞｯｸ用ｺﾝｿｰﾙの表示
//	HWND hWnd = GetForegroundWindow();

	AllocConsole();	// ｺﾝｿｰﾙを開く
	freopen_s(&m_debugFp, "CONOUT$", "w", stdout);
	freopen_s(&m_debugFp, "CONOUT$", "r", stdin);

//	SetForegroundWindow(hWnd);
}

_DebugConOut::~_DebugConOut()
{
	FreeConsole();  // ｺﾝｿｰﾙを閉じる
}
#endif	// _DEBUG
