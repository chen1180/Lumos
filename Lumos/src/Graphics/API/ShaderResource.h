#pragma once

#include "JM.h"

namespace jm
{

	class ShaderResourceDeclaration
	{
	public:
		virtual ~ShaderResourceDeclaration() = default;
		virtual const String& GetName() const = 0;
		virtual uint GetRegister() const = 0;
		virtual uint GetCount() const = 0;
	};

	typedef std::vector<ShaderResourceDeclaration*> ShaderResourceList;
}