#pragma once
#include <string>
namespace onodrim::shaders::sprite
{
#ifndef __EMSCRIPTEN__

	static const std::string vert = R"(
			#version 430 core
			in vec2 vertex;

			in mat3 matrix;
			void main(void)
			{
				vec3 pos = matrix * vec3(vertex, 1);
				gl_Position = vec4(pos, 1);
			}
		)";
	static const std::string frag = R"(
			#version 430 core
			out vec4 color;
			void main(void)
			{
				color = vec4(0.0, 1.0, 0.0, 1.0);
			}
		)";
#else
	static const std::string vert = R"(#version 300 es
			in vec2 vertex;
			in mat3 matrix;
			void main(void)
			{
				vec3 pos = matrix * vec3(vertex, 1);
				gl_Position = vec4(pos, 1);
			}
		)";

	static const std::string frag = R"(#version 300 es
			precision mediump float;
			out vec4 color;
			void main(void)
			{
				color = vec4(0.0, 1.0, 0.0, 1.0);
			}
		)";
#endif
}