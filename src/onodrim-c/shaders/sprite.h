#pragma once
#include <string>
namespace onodrim::shaders::sprite
{
#ifndef __EMSCRIPTEN__

	static const std::string vert = R"(
			#version 430 core
			in vec2 vertex;

			in mat3 in_matrix;
			in vec4 in_color;
			out vec4 v_color;
			uniform mat4 u_projection;
			void main(void)
			{
				vec3 pos = in_matrix * vec3(vertex, 1);
				gl_Position = u_projection*vec4(pos, 1);
				v_color = in_color;
			}
		)";
	static const std::string frag = R"(
			#version 430 core
			in vec4 v_color;
			out vec4 color;
			void main(void)
			{
				color = v_color;
			}
		)";
#else
	static const std::string vert = R"(#version 300 es
			in vec2 vertex;
			in mat3 in_matrix;
			in vec4 in_color;
			out vec4 v_color;
uniform mat3 u_projection;
			void main(void)
			{
				vec3 pos = in_matrix * vec3(vertex, 1);
				gl_Position = vec4(u_projection * pos, 1);
				v_color = in_color;
			}
		)";

	static const std::string frag = R"(#version 300 es
			precision mediump float;
			in vec4 v_color;
			out vec4 color;
			void main(void)
			{
				color = v_color;
			}
		)";
#endif
}