#include "./OpenGLSystem.h"
#include "../utils/Logger.h"

#ifdef __EMSCRIPTEN__
	#include <emscripten.h>
#endif
namespace onodrim::system
{
	OpenGLSystem::OpenGLSystem()
	{
		m_Width = 800;
		m_Height = 600;
		m_pWindow = NULL;

		InitGL();
	}
	OpenGLSystem::~OpenGLSystem()
	{

	}

	void OpenGLSystem::InitGL()
	{
		glfwSetErrorCallback([](int error, const char * msg){
			onodrim::utils::logLine(msg);
		});
		if(!glfwInit())
		{
			onodrim::utils::log("Failed to initialize GLFW");
			// onodrim::utils::logLine(stderr);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		m_pWindow = glfwCreateWindow(m_Width, m_Height, "Onodrim", NULL, NULL);
		if(!m_pWindow)
		{
			onodrim::utils::log("Failed to create GLFW window");
			// onodrim::utils::logLine(stderr);
			glfwTerminate();
			#ifdef __EMSCRIPTEN__
				emscripten_force_exit(EXIT_FAILURE);
			#endif
			
		}

		glfwMakeContextCurrent(m_pWindow);

		glClearColor(0.39f, 0.58f, 0.92f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_BLEND);
		glBlendEquation(GL_FUNC_ADD);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glViewport(0, 0, m_Width, m_Height);
	}

	void OpenGLSystem::InitShaders()
	{

	}

	void OpenGLSystem::Render()
	{
		float renderDelta = 0.f;
		if(false)
		{
			// check resize and similar
		}
		glViewport(0, 0, m_Width, m_Height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		bool resort = false;
		for (auto it = m_Components.begin(); it != m_Components.end(); it++)
		{
			RenderComponent* renderer = (*it);
			if(!renderer->IsActive())
			{
				continue;
			}
			if(renderer->DoesRequireDepthSort())
			{
				resort = true;
				renderer->SetRequireDepthSort(true);
			}
			renderer->Render(renderDelta);
		}
		// flush spritebatch
		glFlush();
		if(resort)
		{
			std::sort(m_Components.begin(), m_Components.end(), [](RenderComponent* a, RenderComponent* b){
				return a->GetDepth() > b->GetDepth();
			});
		}
	}
}