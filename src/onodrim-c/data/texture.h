#pragma once
#include <string>
#include "../math/rect.h"
class GLTexture
{
public:
	GLTexture()
	{

	}
	virtual ~GLTexture()
	{

	}

protected:
	std::string m_Path;
	Rect<float> m_Rect;
	Rect<float> m_GLRect;

};