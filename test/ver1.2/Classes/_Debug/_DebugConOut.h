#pragma once
#ifdef  _DEBUG
#include <memory>
#include <Windows.h>

#define TRACE(fmt, ...) printf(fmt, __VA_ARGS__)	// ｺﾝｿｰﾙに文字列を表示するための定数

class _DebugConOut
{
public:
	// 動的なｼﾝｸﾞﾙﾄﾝ
	static _DebugConOut& GetInstance()
	{
		// ﾕﾆｰｸﾎﾟｲﾝﾀの中身を返す
		return (*s_instance);
	}
private:
	// 中身を削除する
	struct _DebugConOutDeleter
	{
		void operator()(_DebugConOut* _debugConOut) const
		{
			delete _debugConOut;
		}
	};
	_DebugConOut();					
	~_DebugConOut();

	FILE* m_debugFp = nullptr;		// 書き込み,読み込み用ﾌｧｲﾙﾎﾟｲﾝﾀｰ変数

	static std::unique_ptr< _DebugConOut,_DebugConOutDeleter > s_instance;	// ｼﾝｸﾞﾙﾄﾝでｲﾝｽﾀﾝｽする変数
};
#else
#define TRACE(fmt, ...);
#endif	// _DEBUG