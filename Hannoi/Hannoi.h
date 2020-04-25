#pragma once

//保存一次移动
struct HannoiPair
{
	unsigned char from;
	unsigned char to;
};

class Hannoi
{
	using num_type = unsigned char;
	num_type m_n;
	std::forward_list<HannoiPair> m_pairs;

	void hannoi(num_type n, num_type p1, num_type p2, num_type p3)
	{
		if (n == 1)
		{
			m_pairs.push_front({ p1,p3 });
		}
		else
		{
			hannoi(n - 1, p1, p3, p2);
			m_pairs.push_front({ p1,p3 });
			hannoi(n - 1, p2, p1, p3);
		}
	}

public:
	Hannoi(num_type n):
		m_n{n}
	{
		ASSERTE(n >= 3);
		hannoi(n, 0, 1, 2);
		m_pairs.reverse();
	}

	const std::forward_list<HannoiPair>& Get() const
	{
		return m_pairs;
	}

};

struct HannoiSettings
{
	const unsigned int PolarCount = 3;			//柱子个数
	
	const float PolarHeight = 360.f;			//柱子高度
	const float PolarWidth = 480.f;				//底部宽度
	const float Seperator = 200.f;				//柱子间隔

	const float HannoiWidth = PolarWidth * 3 + Seperator * 2;		//整体宽度
	const float HannoiHeight = PolarHeight;							//整体高度

	const float BlockMaxWidth = PolarWidth * 0.9f;					//金块的最大宽度
	const float BlockMinWidth = PolarWidth * 0.1f;					//金块的最小宽度
	const float BlockHeight = 20.f;									//金块的高度
	//const float BlockDecreace = 0.2f;

	const unsigned int BrickColor = 0xFF2244;
	const unsigned int PolarColor = 0xDD55CC;

	static const HannoiSettings& GetInstance() { return instance; }
private:
	HannoiSettings() {}
	static HannoiSettings instance;
};

//汉诺塔金块
struct HannoiBlock
{
	float x;				//位置x偏移量
	float y;				//位置y偏移量
	float width;			//金块的宽度
	float height;			//尽快的高度

	unsigned int color;		//金块的颜色
};

//汉诺塔柱子
struct HannoiPolar
{
	std::stack<int> blocks;	//柱子上面的金块索引
};