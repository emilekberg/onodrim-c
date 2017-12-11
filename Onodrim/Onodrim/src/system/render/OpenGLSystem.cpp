#include <algorithm>
#include "./OpenGLSystem.h"
#include "../../utils/Logger.h"

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
		#ifndef __EMSCRIPTEN__
			glewInit();
		#endif
		glfwSetErrorCallback([](int error, const char * msg)
		{
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
		CheckError();
		glEnable(GL_DEPTH_TEST);
		CheckError();
		glDepthFunc(GL_LEQUAL);
		CheckError();
		glEnable(GL_BLEND);
		CheckError();
		// glBlendEquation(GL_FUNC_ADD);
		CheckError();
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		CheckError();
		glViewport(0, 0, m_Width, m_Height);
	}

	void OpenGLSystem::CheckError()
	{
		GLenum err = glGetError();
		if (err != GL_NO_ERROR)
		{ 
			utils::logLine("error");
		}
		// const GLubyte* gluErrorString(GLenum errorCode);

		GLenum errCode;
		const GLubyte *errString;
		if (err != GL_NO_ERROR)
		{
			// errString = gluErrorString(err);
			utils::logLine("error");
		}


	}

	GLuint OpenGLSystem::CreateShader(std::string shaderSource, int shaderType)
	{
		GLuint shader;
		const GLchar* source = (const GLchar*)shaderSource.c_str();
		switch(shaderType)
		{
			case 0:
				shader = glCreateShader(GL_FRAGMENT_SHADER);
				break;
			case 1:
				shader = glCreateShader(GL_VERTEX_SHADER);
				break;
		}
		glShaderSource(shader, 1, &source, 0);
		glCompileShader(shader);
		GLint success = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if(!success)
		{
			utils::logLine("Error when compiling shader");

			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &errorLog[0]);
			// utils::logLine(errorLog);
			glDeleteShader(shader);

			return GL_FALSE;
		}
		return shader;
	}

	void OpenGLSystem::InitShaders()
	{
		GLuint fragShader = CreateShader("", 0);
		GLuint vertShader = CreateShader("", 1);
		GLuint program = glCreateProgram();
		if(!program)
		{
			utils::logLine("error when creating program");
			return;
		}
		glAttachShader(program, vertShader);
		glAttachShader(program, fragShader);
		glLinkProgram(program);
		GLint success = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &success);
		if(!success)
		{
			utils::logLine("error when linking program");
		}
		glUseProgram(program);

		// add hack here for initial uniform matrix;
		
	}

	void OpenGLSystem::Render()
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


		glfwSwapBuffers(m_pWindow);
		glfwPollEvents();
	}
}