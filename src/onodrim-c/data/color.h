#pragma once
namespace onodrim 
{
	class Color 
	{
	public:
		Color()
		{
			SetHex(0xFFFFFF);
			SetAlpha(1);
		}
		Color(int hex)
		{
			SetHex(hex);
			SetAlpha(1);
		}
		Color(float r, float g, float b, float a = 1.0f)
		{
			SetRGBA(r,g,b,a);
		}
		~Color()
		{

		}

		inline void SetHex(int hex)
		{
			values[0] = ((hex >> 16) & 0xFF) / 255.f;
			values[1] = ((hex >> 8) & 0xFF) / 255.f;
			values[2] = ((hex) & 0xFF) / 255.f;
		}
		inline void SetRGBA(float r, float g, float b, float a = 1.0f)
		{
			values[0] = r;
			values[1] = g;
			values[2] = b;
			values[3] = a;
		}
		inline void SetAlpha(float a)
		{
			values[3] = a;
		}

		float values[4];
	};
}
