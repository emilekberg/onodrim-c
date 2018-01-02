#pragma once
namespace onodrim 
{
	class Color 
	{
	public:
		Color()
		{
			SetHex(0xFFFFFF);
			A = 1;
		}
		Color(int hex)
		{
			SetHex(hex);
			A = 1;
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
			R = ((hex >> 16) & 0xFF) / 255.f;
			G = ((hex >> 8) & 0xFF) / 255.f;
			B = ((hex) & 0xFF) / 255.f;
		}
		inline void SetRGBA(float r, float g, float b, float a)
		{
			R = r;
			G = g;
			B = b;
			A = a;
		}

		float R;
		float G;
		float B;
		float A;
	};
}
