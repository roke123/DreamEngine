#ifndef __DREHLSLPROGRAM_H__
#define __DREHLSLPROGRAM_H__

#include "DreRenderDeclaration.h"

#include "DreRenderParam.h"

namespace dream
{
	struct DRE_HLSLPROGRAM_DESC
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

	class DRE_EXPORT_CLASS HLSLProgram
	{
	private:
		HLSLProgram(const HLSLProgram&);
		HLSLProgram& operator = (const HLSLProgram&);
	
	public:
		HLSLProgram() {}

		virtual ~HLSLProgram() {};

		/** 添加一个渲染参数
		* @param paramName 渲染管道使用的参数名
		* @param param 渲染参数
		*/
		void AddRenderParam(const string& paramName, RenderParamPtr param)
		{
			mRenderParamMap.insert(make_pair<string, RenderParamPtr>(paramName, param));
		}
		
		/** 取得一个渲染函数
		*/
		RenderParamPtr GetRenderParam(const string& param)
		{
			return mRenderParamMap.find(param)->second;
		}

		/** 移除一个渲染参数
		* @param paramName 渲染数名
		*/
		void RemoveRenderParam(const string& paramName)
		{
			mRenderParamMap.erase(paramName);
		}

	private:
		/// 渲染参数集
		RenderParamPtrMap mRenderParamMap;

	};	// end class HLSLProgram
	
}	// end namespace dream

#endif	// end of __DREHLSLPROGRAm_H__