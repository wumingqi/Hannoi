#ifndef PCH_H
#define PCH_H

#include <d2d1_3.h>
#include <dxgi1_6.h>
#include <d3d11_4.h>
#include <dwrite_3.h>
#include <wincodec.h>
#include <wrl.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dwrite.lib")
#pragma comment(lib, "windowscodecs.lib")

#include <string>
#include <memory>
#include <vector>
#include <stack>
#include <forward_list>

#if defined(_DEBUG)

//�Զ�����Ժ�
#define ASSERTE(expr) _ASSERTE(expr)

//׷�ٵ�����Ϣ������Դ��������Ϣ
struct Trace
{
	const wchar_t* filename;			//Դ�ļ���
	const unsigned int line;			//�к�

	//���캯��
	Trace(const wchar_t* filename, const unsigned int line) :
		filename{ filename },
		line{ line }
	{

	}

	//���غ�����������ɱ�������
	template<typename... Args>
	void operator()(const wchar_t* format, Args...args) const noexcept
	{
		wchar_t buffer[MAX_PATH + 128];		//�����������С��������ļ��������ٶ��һ��

		auto count = swprintf_s(			//��ʽ������ļ������к�
			buffer,
			TEXT("%s(%d):"),
			filename,
			line);

		ASSERTE(count != -1);

		count = swprintf_s(					//��ʽ�����������Ϣ
			buffer + count,
			_countof(buffer) - count - 1,
			format,
			args...);

		ASSERTE(count != -1);

		OutputDebugStringW(buffer);			//����Դ������������Ϣ
	}
};

#define TRACE Trace(__FILEW__, __LINE__)

#else

#define ASSERTE(expr) __noop
#define TRACE(...) __noop

#endif


#endif // !PCH_H
