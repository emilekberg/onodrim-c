#include <algorithm>
#include "./OpenGLSystem.h"
#include "../../utils/Logger.h"
#include "../../data/GLSLShader.h"
#include <stdio.h>
namespace onodrim::system::render
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
		glfwSetErrorCallback([](int error, const char * msg)
		{
			onodrim::utils::log(msg);
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
		
#ifndef __EMSCRIPTEN__
		int argc = 1;
		char *argv[1] = { (char*)"Something" };
		glutInit(&argc, argv);
		glewInit();
#endif		
		utils::log("OpenGLSystem::InitGL - vendor string: %s", glGetString(GL_VENDOR));
		utils::log("OpenGLSystem::InitGL - renderer string: %s", glGetString(GL_RENDERER));
		utils::log("OpenGLSystem::InitGL - version string: %s", glGetString(GL_VERSION));

		glClearColor(0.39f, 0.58f, 0.92f, 1.0f);
		CheckError();
		glEnable(GL_DEPTH_TEST);
		CheckError();
		glDepthFunc(GL_LEQUAL);
		CheckError();
		glEnable(GL_BLEND);
		CheckError();
		glBlendEquation(GL_FUNC_ADD);
		CheckError();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		CheckError();
		glViewport(0, 0, m_Width, m_Height);

		InitShaders();
	}

	void OpenGLSystem::CheckError()
	{
		GLenum err = glGetError();
		if (err != GL_NO_ERROR)
		{ 
			utils::log("error");
		}
		// const GLubyte* gluErrorString(GLenum errorCode);

		if (err != GL_NO_ERROR)
		{
			// errString = gluErrorString(err);
			utils::log("error");
		}
	}

	void OpenGLSystem::InitShaders()
	{
#ifndef __EMSCRIPTEN__

		std::string vert = R"(
			#version 430 core
			void main(void)
			{
				const vec4 vertices[3] = vec4[3](vec4( 0.25, -0.25, 0.5, 1.0),
				vec4(-0.25, -0.25, 0.5, 1.0),
				vec4( 0.25, 0.25, 0.5, 1.0));
				gl_Position = vertices[gl_VertexID];
			}
		)";

		std::string frag = R"(
			#version 430 core
			out vec4 color;
			void main(void)
			{
				color = vec4(0.0, 1.0, 0.0, 1.0);
			}
		)";
#else
		std::string vert = R"(#version 300 es
			void main(void)
			{
				const vec4 vertices[3] = vec4[3](
					vec4( 0.25, -0.25, 0.5, 1.0),
					vec4(-0.25, -0.25, 0.5, 1.0),
					vec4( 0.25, 0.25, 0.5, 1.0)
				);
				gl_Position = vertices[gl_VertexID];
			}
		)";

		std::string frag = R"(#version 300 es
			precision mediump float;
			out vec4 color;
			void main(void)
			{
				color = vec4(0.0, 1.0, 0.0, 1.0);
			}
		)";
#endif
		
		m_Program = std::make_unique<data::GLSLProgram>();
		m_Frag = std::make_unique<data::GLSLShader>(GL_FRAGMENT_SHADER);
		m_Vert = std::make_unique<data::GLSLShader>(GL_VERTEX_SHADER);
		
		m_Frag->SetSource(frag);
		m_Frag->Compile();
		m_Vert->SetSource(vert);
		m_Vert->Compile();
		m_Program->Init();
		m_Program->AttachShader(*m_Vert);
		m_Program->AttachShader(*m_Frag);
		m_Program->Link();
		m_Program->Use();
		
		utils::log("successfully initiated shaders"); 
	}

	bool OpenGLSystem::Render()
	{
		// utils::logLine("OpenGLSystem::Render()");
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

		//use the created program
		m_Program->Use();

		//draw 3 vertices as triangles
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(m_pWindow);
		glfwPollEvents();

#ifndef __EMSCRIPTEN__
		if (glfwWindowShouldClose(m_pWindow))
		{
			glfwDestroyWindow(m_pWindow);
			glfwTerminate();
			return false;
		}
#endif
		return true;
	}
}