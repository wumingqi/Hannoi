#pragma once

//����һ���ƶ�
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
	const unsigned int PolarCount = 3;			//���Ӹ���
	
	const float PolarHeight = 360.f;			//���Ӹ߶�
	const float PolarWidth = 480.f;				//�ײ����
	const float Seperator = 200.f;				//���Ӽ��

	const float HannoiWidth = PolarWidth * 3 + Seperator * 2;		//������
	const float HannoiHeight = PolarHeight;							//����߶�

	const float BlockMaxWidth = PolarWidth * 0.9f;					//���������
	const float BlockMinWidth = PolarWidth * 0.1f;					//������С���
	const float BlockHeight = 20.f;									//���ĸ߶�
	//const float BlockDecreace = 0.2f;

	const unsigned int BrickColor = 0xFF2244;
	const unsigned int PolarColor = 0xDD55CC;

	static const HannoiSettings& GetInstance() { return instance; }
private:
	HannoiSettings() {}
	static HannoiSettings instance;
};

//��ŵ�����
struct HannoiBlock
{
	float x;				//λ��xƫ����
	float y;				//λ��yƫ����
	float width;			//���Ŀ��
	float height;			//����ĸ߶�

	unsigned int color;		//������ɫ
};

//��ŵ������
struct HannoiPolar
{
	std::stack<int> blocks;	//��������Ľ������
};