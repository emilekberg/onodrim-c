#include <algorithm>
#include "./openGLSystem.h"
#include "../../utils/logger.h"
#include "../../data/glslShader.h"
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
			LOG_ERROR("gl error number:%i msg:%s", error, msg);
		});
		if(!glfwInit())
		{
			LOG_ERROR("Failed to initialize GLFW");
			// onodrim::utils::logLine(stderr);
		}

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		m_pWindow = glfwCreateWindow(m_Width, m_Height, "Onodrim", NULL, NULL);
		if(!m_pWindow)
		{
			LOG_ERROR("Failed to create GLFW window");
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
		LOG_INFO("OpenGLSystem::InitGL \n\t \
				vendor string: %s \n\t \
				renderer string: %s \n\t \
				version string: %s", glGetString(GL_VENDOR), glGetString(GL_RENDERER), glGetString(GL_VERSION));

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
			LOG_ERROR("error");
		}
		// const GLubyte* gluErrorString(GLenum errorCode);

		if (err != GL_NO_ERROR)
		{
			// errString = gluErrorString(err);
			LOG_ERROR("error");
		}
	}

	void OpenGLSystem::InitShaders()
	{
		// TODO: read from external file or insert compiletime
#ifndef __EMSCRIPTEN__

		std::string vert = R"(
			#version 430 core
			in vec2 vertex;
			void main(void)
			{
				gl_Position = vec4(vertex, 0, 1);
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
			in vec2 vertex;
			void main(void)
			{
				gl_Position = vec4(vertex, 0, 1);
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
		
		m_Program = std::make_shared<data::GLSLProgram>();
		m_Frag = std::make_unique<data::GLSLShader>(GL_FRAGMENT_SHADER);
		m_Vert = std::make_unique<data::GLSLShader>(GL_VERTEX_SHADER);
		m_Program->Init();
		
		m_Frag->SetSource(frag);
		m_Frag->Compile();
		m_Vert->SetSource(vert);
		m_Vert->Compile();
		
		m_Program->AttachShader(*m_Vert);
		m_Program->AttachShader(*m_Frag);
		
		m_Program->Link();
		m_Program->Use();
		
		// TODO: fixed projection matrix.
		LOG_INFO("successfully initiated shaders"); 
	}

	bool OpenGLSystem::Render()
	{
		// utils::logLine("OpenGLSystem::Render()");
		float renderDelta = 0.f;
		// TODO: see if this can be here
		// const delta = (Time.now()-this.fixedUpdateSystem.currentUpdateTime)/this.fixedUpdateSystem.updateRate;

		if(Resize() || false)	// false is Camerasystem.MAIN.isDirty
		{
			// TODO: Implement
			// CameraSystem.MAIN.interpolateMatrix(delta);
			UpdateViewMatrix();
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

	bool OpenGLSystem::Resize()
	{
		return false;
		/*#ifdef __EMSCRIPTEN__
		double ratio = emscripten_get_device_pixel_ratio();
		int width;
		int height;
		int fullscreen;
		emscripten_get_canvas_size(&width, &height, &fullscreen);

		#endif*/
		// TODO: implement
		/*
			const ratio = window.devicePixelRatio || 1;
			const canvas = gl.canvas;
			const width = Math.floor(canvas.clientWidth * ratio);
			const height = Math.floor(canvas.clientHeight * ratio);
			if (canvas.width !== width || canvas.height !== height) {
				canvas.width = width;
				canvas.height = height;
				CameraSystem.MAIN.setViewport(width, height);
				return true;
			}
			return false;
		*/
		return false;
	}

	void OpenGLSystem::UpdateViewMatrix()
	{
		// TODO: implement
		// gl.uniformMatrix3fv(this._projectionMatrixLocation, false, CameraSystem.MAIN.matrix.values);
	}
}