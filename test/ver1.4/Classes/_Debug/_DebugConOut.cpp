#ifdef  _DEBUG
#include "_DebugConOut.h"

std::unique_ptr< _DebugConOut, _DebugConOut::_DebugConOutDeleter > _DebugConOut::s_instance(new _DebugConOut);	// �ϐ��̲ݽ�ݽ

_DebugConOut::_DebugConOut()
{
	// ���ޯ��p�ݿ�ق̕\��
//	HWND hWnd = GetForegroundWindow();

	AllocConsole();	// �ݿ�ق��J��
	freopen_s(&m_debugFp, "CONOUT$", "w", stdout);
	freopen_s(&m_debugFp, "CONOUT$", "r", stdin);

//	SetForegroundWindow(hWnd);
}

_DebugConOut::~_DebugConOut()
{
	FreeConsole();  // �ݿ�ق����
}
#endif	// _DEBUG
