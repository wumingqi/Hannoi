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

//自定义断言宏
#define ASSERTE(expr) _ASSERTE(expr)

//追踪调试信息，向调试窗口输出信息
struct Trace
{
	const wchar_t* filename;			//源文件名
	const unsigned int line;			//行号

	//构造函数
	Trace(const wchar_t* filename, const unsigned int line) :
		filename{ filename },
		line{ line }
	{

	}

	//重载函数运算符，可变参数输出
	template<typename... Args>
	void operator()(const wchar_t* format, Args...args) const noexcept
	{
		wchar_t buffer[MAX_PATH + 128];		//输出缓冲区大小，比最大文件名长度再多出一点

		auto count = swprintf_s(			//格式化输出文件名和行号
			buffer,
			TEXT("%s(%d):"),
			filename,
			line);

		ASSERTE(count != -1);

		count = swprintf_s(					//格式化输出其他信息
			buffer + count,
			_countof(buffer) - count - 1,
			format,
			args...);

		ASSERTE(count != -1);

		OutputDebugStringW(buffer);			//向调试窗口输出调试信息
	}
};

#define TRACE Trace(__FILEW__, __LINE__)

#else

#define ASSERTE(expr) __noop
#define TRACE(...) __noop

#endif


#endif // !PCH_H
