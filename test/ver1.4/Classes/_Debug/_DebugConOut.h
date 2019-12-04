#pragma once
#ifdef  _DEBUG
#include <memory>
#include <Windows.h>

#define TRACE(fmt, ...) printf(fmt, __VA_ARGS__)	// �ݿ�قɕ������\�����邽�߂̒萔

class _DebugConOut
{
public:
	// ���I�ȼݸ����
	static _DebugConOut& GetInstance()
	{
		// �ư��߲���̒��g��Ԃ�
		return (*s_instance);
	}
private:
	// ���g���폜����
	struct _DebugConOutDeleter
	{
		void operator()(_DebugConOut* _debugConOut) const
		{
			delete _debugConOut;
		}
	};
	_DebugConOut();					
	~_DebugConOut();

	FILE* m_debugFp = nullptr;		// ��������,�ǂݍ��ݗp̧���߲����ϐ�

	static std::unique_ptr< _DebugConOut,_DebugConOutDeleter > s_instance;	// �ݸ���݂Ųݽ�ݽ����ϐ�
};
#else
#define TRACE(fmt, ...);
#endif	// _DEBUG