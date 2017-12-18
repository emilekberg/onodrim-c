#pragma once
#include <memory>
#include "./instance-batch.h"
#include "../../../data/glslProgram.h"

namespace onodrim::opengl
{
	struct IAttribute;
	class SpriteBatch : public InstanceBatch
	{
	public:
		SpriteBatch(std::shared_ptr<data::GLSLProgram> program, int size) : InstanceBatch(program, size)
		{
		}
		virtual ~SpriteBatch();
	};

}