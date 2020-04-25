#include "Pch.h"
#include "Application.h"

using namespace D2D1;

void Application::InitializeResources()
{
	m_deviceResources.SetTargetWindow(m_hWnd);
	m_d2dContext = m_deviceResources.GetD2DContext();

	//创建资源
	m_d2dContext->CreateSolidColorBrush(ColorF::ColorF(0x000000), &m_brush);

	auto settings = HannoiSettings::GetInstance();

	m_hannoiN = 5;
	m_hannoi.reset(new Hannoi{ m_hannoiN });

	//初始化金块
	m_hannoiBlocks.resize(m_hannoiN);
	auto delt = (settings.BlockMaxWidth - settings.BlockMinWidth) / m_hannoiN;
	for (unsigned int i = 0; i < m_hannoiBlocks.size(); i++)
	{
		m_hannoiBlocks[i].width = settings.BlockMaxWidth - i * delt;
		m_hannoiBlocks[i].height = settings.BlockHeight;
		m_hannoiBlocks[i].x = (settings.PolarWidth- m_hannoiBlocks[i].width)/2;
		m_hannoiBlocks[i].y = settings.PolarHeight - (i + 1) * settings.BlockHeight;
		m_hannoiBlocks[i].color = (i + 1) * ((0xFF0000 - 0x00FF00)/ m_hannoiBlocks.size());
	}

	//初始化柱子
	m_hannoiPolars.resize(m_hannoiN);

	for (char i = 0; i <m_hannoiN; i++)
	{
		m_hannoiPolars[0].blocks.push(i);
	}
}

void Application::Update()
{
	m_d2dContext->BeginDraw();
	m_d2dContext->Clear(ColorF(0xEEEEEE));
	//m_d2dContext->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
	//开始绘制
	DrawPolar();
	m_d2dContext->EndDraw();
	m_deviceResources.GetSwapChain()->Present(1, 0);
}

void Application::DrawPolar()
{
	auto settings = HannoiSettings::GetInstance();
	m_d2dContext->SetTransform(Matrix3x2F::Translation((
		floorf((float)(INT)(m_width - settings.HannoiWidth) / 2.f)), 
		floorf((float)(INT)((m_height - settings.HannoiHeight) / 2.f)))
	);

	m_brush->SetColor(D2D1::ColorF(D2D1::ColorF::MediumBlue));
	for (unsigned int i = 0u; i < settings.PolarCount; i++)
	{
		//dizuo
		D2D1_POINT_2F p1 = { floorf(i*(settings.PolarWidth + settings.Seperator)), floorf(settings.PolarHeight) };
		D2D1_POINT_2F p2 = { floorf(p1.x+settings.PolarWidth),  floorf(p1.y) };
		m_d2dContext->DrawLine(p1, p2, m_brush.Get());

		//zhuzi
		p1 = { floorf(settings.PolarWidth / 2 + i * (settings.PolarWidth + settings.Seperator)) ,0 };
		p2 = { p1.x,floorf(settings.PolarHeight) };
		m_d2dContext->DrawLine(p1, p2, m_brush.Get());
	}

	for (unsigned int i = 0u; i < m_hannoiN; i++)
	{
		// D2D1_ELLIPSE ellipse = {};
		// ellipse.radiusX = m_hannoiBlocks[i].width / 2;
		// ellipse.radiusY = m_hannoiBlocks[i].height / 2;
		// ellipse.point.x = m_hannoiBlocks[i].x + ellipse.radiusX;
		// ellipse.point.y = m_hannoiBlocks[i].y + ellipse.radiusY;
		// m_d2dContext->FillEllipse(
		// 	ellipse,
		// 	m_brush.Get()
		// );

		D2D1_RECT_F rc = {};
		rc.left = m_hannoiBlocks[i].x;
		rc.top = m_hannoiBlocks[i].y + 2;
		rc.right = rc.left + m_hannoiBlocks[i].width;
		rc.bottom = rc.top + m_hannoiBlocks[i].height - 2;
		m_brush->SetColor(D2D1::ColorF(m_hannoiBlocks[i].color));
		m_d2dContext->FillRectangle(
			rc,
			m_brush.Get()
		);
	}
}

void Application::MoveBlocks(unsigned int from, unsigned int to)
{
	auto settings = HannoiSettings::GetInstance();

	unsigned int blockIndex =  m_hannoiPolars[from].blocks.top();
	m_hannoiPolars[from].blocks.pop();

	m_hannoiBlocks[blockIndex].x += (int)(to - from)*(settings.PolarWidth + settings.Seperator);
	m_hannoiBlocks[blockIndex].y = settings.PolarHeight - ((int)(m_hannoiPolars[to].blocks.size()+1)*settings.BlockHeight);

	m_hannoiPolars[to].blocks.push(blockIndex);
}

DWORD Application::BeginMove(LPVOID param)
{
	Application* app = (Application*)param;

	auto pairs = app->m_hannoi->Get();

	for (auto i = pairs.begin(); i != pairs.end(); i++)
	{
		app->MoveBlocks(i->from, i->to);
		app->Update();
	}
	return 0;
}
