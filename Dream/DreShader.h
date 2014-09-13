#ifndef __DRESHADER_H__
#define __DRESHADER_H__

#include "DreRenderDeclaration.h"

#include "DreRenderParam.h"

namespace dream
{
	struct DRE_SHADER_DESC
	{
		const c8*  VS_EntryPoint;
		const c8*  VS_Verson;
		const c8*  VS_File;
		const c8*  DS_EntryPoint;
		const c8*  DS_Verson;
		const c8*  DS_File;
		const c8*  HS_EntryPoint;
		const c8*  HS_Verson;
		const c8*  HS_File;
		const c8*  GS_EntryPoint;
		const c8*  GS_Verson;
		const c8*  GS_File;
		const c8*  PS_EntryPoint;
		const c8*  PS_Verson;
		const c8*  PS_File;
	};

	class DRE_EXPORT_CLASS Shader
	{
	private:
		Shader(const Shader&);
		Shader& operator = (const Shader&);
	
	public:
		Shader() {}

		virtual ~Shader() {};

	};	// end class Shader
	
}	// end namespace dream

#endif	// end of __DRESHADER_H__