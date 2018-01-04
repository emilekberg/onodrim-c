#pragma once
#include <memory>
#include "../tickSystem.h"
#include "../../components/renderComponent.h"
#include "../../utils/time.h"
#include "../../shaders/program.h"
#include "./spritebatch.h"
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
	class RenderSystem : public TickSystem
	{
	public:
		RenderSystem();
		~RenderSystem();

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


		inline std::shared_ptr<shaders::Program> GetProgram()
		{
			return m_Spritebatch->GetProgram();
		}
	protected:
		bool Resize();
		void UpdateViewMatrix();

	private:
		std::shared_ptr<Spritebatch> m_Spritebatch;
		std::vector<RenderComponent*> m_Components;
		int m_Width;
		int m_Height;
		GLFWwindow* m_pWindow;
	};


}
