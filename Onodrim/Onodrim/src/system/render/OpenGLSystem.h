#pragma once
#include "../TickSystem.h"
#include "../../components/RenderComponent.h"
#include "../../utils/Time.h"


#ifdef __EMSCRIPTEN__
	#include <emscripten.h>
	#define GLFW_INCLUDE_ES3
	#include <GLFW/glfw3.h>
	#include <GLES3/gl3.h>
#else
	#include <GL\glew.h>
	#include <GL\gl.h>
	#include <GLFW/glfw3.h>
	#include <GL\freeglut.h>
#endif
#include <string>
#include <iostream>
namespace onodrim::system::render {
	class OpenGLSystem : public TickSystem
	{
	public:
		OpenGLSystem();
		~OpenGLSystem();

		virtual inline bool CanProcessComponent(Component* component)
		{
			return dynamic_cast<RenderComponent*>(component) != nullptr;
		}

		inline virtual void Tick()
		{
			Render();
		}

		void Render();

		void InitGL();
		void InitShaders();
		void CheckError();

	protected:
		GLuint CreateShader(std::string source, int shaderType);

	private:
		std::vector<RenderComponent*> m_Components;
		int m_Width;
		int m_Height;
		GLFWwindow* m_pWindow;
	};


}
