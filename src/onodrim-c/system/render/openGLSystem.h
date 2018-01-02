#pragma once
#include <memory>
#include "../tickSystem.h"
#include "../../components/renderComponent.h"
#include "../../utils/time.h"
#include "../../data/glslProgram.h"
// #include "./opengl/sprite-batch.h"
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

		virtual void AddComponentInstance(Component* component)
		{
			RenderComponent* casted = dynamic_cast<RenderComponent*>(component);
			m_Components.push_back(casted);
		}

		inline virtual bool Tick()
		{
			return Render();
		}

		bool Render();

		void InitGL();
		void InitShaders();
		void CheckError();


		inline std::shared_ptr<data::GLSLProgram> GetProgram()
		{
			return m_Program;
		}
	protected:
		bool Resize();
		void UpdateViewMatrix();

	private:
		// std::unique_ptr<data::GLSLProgram> m_Program;
		std::unique_ptr<data::GLSLShader> m_Frag;
		std::unique_ptr<data::GLSLShader> m_Vert;
		std::shared_ptr<data::GLSLProgram> m_Program;
		std::vector<RenderComponent*> m_Components;
		int m_Width;
		int m_Height;
		GLFWwindow* m_pWindow;
		// std::shared_ptr<opengl::SpriteBatch> m_SpriteBatch;
	};


}
