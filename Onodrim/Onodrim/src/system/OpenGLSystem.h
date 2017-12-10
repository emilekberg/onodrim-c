#pragma once
#include "./TickSystem.h"
#include "../components/RenderComponent.h"
#include "../utils/Time.h"
#define GLFW_INCLUDE_ES3
#include <GLFW/glfw3.h>
#include <GLES3/gl3.h>
namespace onodrim::system {
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

	private:
		std::vector<RenderComponent*> m_Components;
		int m_Width;
		int m_Height;
		GLFWwindow* m_pWindow;
	};


}
