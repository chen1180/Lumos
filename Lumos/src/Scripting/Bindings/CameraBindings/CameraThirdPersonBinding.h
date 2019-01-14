#pragma once
#include "JM.h"
#include "Scripting/LuaScript.h"
#include "Scripting/Luna.h"
#include "Graphics/Camera/ThirdPersonCamera.h"
#include "CameraBinding.h"

namespace jm
{
	class JM_EXPORT CameraThirdPersonBinding : public CameraBinding
	{
	public:
		static const char className[];
		static Luna<CameraThirdPersonBinding>::FunctionType methods[];
		static Luna<CameraThirdPersonBinding>::PropertyType properties[];

		explicit CameraThirdPersonBinding(ThirdPersonCamera* camera);
        CameraThirdPersonBinding(lua_State* L);
		~CameraThirdPersonBinding();

		static void Bind();
	};
}

