///////////////////////////////////////////
// date: 2014/9/11 17:14
// author: zou lei
//////////////////////////////////////////

#ifndef __DRE_PASS_H__
#define __DRE_PASS_H__

#include "DreRenderDeclaration.h"

#include "DreColor.h"
#include "DreShader.h"

namespace dream {

	/** \addtogroup Core
	*  @{
	*/

	/** \addtogroup Materials
	*  @{
	*/


	/** 指定单次 render 需要传递的所有参数
	@remarks
	Rendering can be repeated with many passes for more complex effects.
	Each pass is either a fixed-function pass (meaning it does not use
	a vertex or fragment program) or a programmable pass (meaning it does
	use either a vertex and fragment program, or both).
	@par
	Programmable passes are complex to define, because they require custom
	programs and you have to set all constant inputs to the programs (like
	the position of lights, any base material colours you wish to use etc), but
	they do give you much total flexibility over the algorithms used to render your
	pass, and you can create some effects which are impossible with a fixed-function pass.
	On the other hand, you can define a fixed-function pass in very little time, and
	you can use a range of fixed-function effects like environment mapping very
	easily, plus your pass will be more likely to be compatible with older hardware.
	There are pros and cons to both, just remember that if you use a programmable
	pass to create some great effects, allow more time for definition and testing.
	*/
	class DRE_EXPORT_CLASS Pass
	{
	public:
		typedef u8						Index;
		typedef u32						HashID;

	protected:
		//-------------------------------------------------------------------------
		/// 是否进行混合操作
		bool							mBlendEnabled;
		/// 是否进行深度比较
		bool							mDepthCheckEnabled;
		/// 是否可以写入深度缓存
		bool							mDepthWriteEnabled;
		/// 是否可以写入红色通道
		bool							mRedColorWriteEnabled;
		/// 是否可以写入绿色通道
		bool							mGreenColorWriteEnabled;
		/// 是否可以写入蓝色通道
		bool							mBlueColorWriteEnabled;
		/// 是否可以写入透明度通道
		bool							mAlphaWriteEnabled;
		/// 是否在多重取样抗锯齿中启用透明度覆盖
		/// @note
		///		使用后 AlphaToCoverage 会调整基于普通 multisample 得到的 pixel shader output
		bool							mAlphaToCoverageEnabled;
		/// 是否开启光照
		bool							mLightingEnabled;
		/// 是否可以投射阴影（使用阴影深度图）
		bool							mShadowCasterEnabled;
		/// 是否可以投射阴影（使用阴影深度图）
		bool							mShadowReciverEnabled;
		/// 是否开启雾化
		bool							mFogEnabled;
		//-------------------------------------------------------------------------

		/// 在 technique 中的索引，pass 的 Render 顺序与索引号相同
		u16								mIndex;
		/// 从属的 technique
		Technique*						mParent;
		/// pass 的 hash码，用于 pass 之间的比较操作
		u32								mHash; 
		bool mHashDirtyQueued; // needs to be dirtied when next loaded

		//-------------------------------------------------------------------------
		/// 混合操作因子
		DRE_BLEND_COLOR_FACTOR			mSourceBlendFactorColor;
		DRE_BLEND_COLOR_FACTOR			mDestBlendFactorColor;
		DRE_BLEND_ALPHA_FACTOR			mSourceBlendFactorAlpha;
		DRE_BLEND_ALPHA_FACTOR			mDestBlendFactorAlpha;
		/// 混合操作
		DRE_BLEND_OPERATION				mBlendOperationColor;
		DRE_BLEND_OPERATION				mBlendOperationAlpha;
		//-------------------------------------------------------------------------

		//-------------------------------------------------------------------------
		/// 深度比较操作
		DRE_COMPARISON_FUNC				mDepthFunc;
		/// 深度常量，实际深度等于 
		///		depth = clmap(_depth + mDepthBiasSlopeScale * mDepthSlopeMax + mDepthBiasConstant, mDepthBiasClamp)
		f32								mDepthBiasConstant;
		/// 深度梯度放大倍数，实际深度等于 
		///		depth = clmap(_depth + mDepthBiasSlopeScale * mDepthSlopeMax + mDepthBiasConstant, mDepthBiasClamp)
		f32								mDepthBiasSlopeScale;
		/// 深度最大值，实际深度等于 
		///		depth = clmap(_depth + mDepthBiasSlopeScale * mDepthSlopeMax + mDepthBiasConstant, mDepthBiasClamp)
		f32								mDepthBiasClamp;
		//-------------------------------------------------------------------------

		//-------------------------------------------------------------------------
		Color							mAmbient;
		Color							mDiffuse;
		Color							mSpecular;
		f32								mShinness;
		//-------------------------------------------------------------------------

		//-------------------------------------------------------------------------
		DRE_CULL_MODE					mCullMode;
		DRE_LIGHTING_MODE				mLightingMode;
		//-------------------------------------------------------------------------
	
		//-------------------------------------------------------------------------
		// 雾化属性
		DRE_FOG_MODE					mFogMode;
		Color							mFogColor;
		f32								mFogStart;
		f32								mFogEnd;
		f32								mFogDensity;
		//-------------------------------------------------------------------------

		/// pass使用的shader
		ShaderPtr						mShader;

	public:

		/// 取得 pass 在 technique 中的索引
		Index GetIndex(void) const { return mIndex; }

		/// 取得 pass 的 hashID
		HashID GetHash(void) const { return mHash; }

		Technique* GetParent() { return mParent; }

		/** 设置 ambient Color */
		void SetAmbient(f32 red, f32 green, f32 blue, f32 alpha);
		/** 设置 ambient Color */
		void SetAmbient(const Color& ambient);

		/** 设置 diffuse Color */
		void SetDiffuse(f32 red, f32 green, f32 blue, f32 alpha);
		/** 设置 diffuse Color */
		void SetDiffuse(const Color& diffuse);

		/** 设置 specular Color */
		void SetSpecular(f32 red, f32 green, f32 blue, f32 alpha);
		/** 设置 specular Color */
		void SetSpecular(const Color& specular);

		/** 设置高光率 */
		void SetShininess(f32 val);

		/** 取得 ambient Color */
		const Color& getAmbient(void) const;

		/** 取得 diffuse Color */
		const Color& getDiffuse(void) const;

		/** 取得 specular Color */
		const Color& getSpecular(void) const;

		/** 取得高光率 */
		f32 GetShininess(void) const;

		/** 设置透明度混合因子 */
		void SetBlendEnable(bool enable) { mBlendEnabled = enable; };

		/** 设置透明度混合因子 */
		void SetBlendAlphaFactor(const DRE_BLEND_ALPHA_FACTOR srcFactor, const DRE_BLEND_ALPHA_FACTOR destFactor);

		/** 设置颜色混合因子 */
		void SetBlendColorFactor(const DRE_BLEND_COLOR_FACTOR srcFactor, const DRE_BLEND_COLOR_FACTOR destFactor);

		/** 设置颜色混合操作 */
		void SetBlendColorOperation(const DRE_BLEND_OPERATION op) { mBlendOperationColor = op; }

		/** 设置颜色混合操作 */
		void SetBlendAlphaOperation(const DRE_BLEND_OPERATION op) { mBlendOperationAlpha = op; }

		/** Return true if this pass uses separate scene blending */
		bool GetBlendEnable() const { return mBlendEnabled; };

		/** 取得颜色混合源因子 */
		DRE_BLEND_COLOR_FACTOR GetSourceBlendFactorColor() const { return mSourceBlendFactorColor; };

		/** 取得颜色混合目标因子 */
		DRE_BLEND_COLOR_FACTOR GetDestBlendFactorColor() const { return mDestBlendFactorColor; };

		/** 取得透明度混合源因子 */
		DRE_BLEND_ALPHA_FACTOR GetSourceBlendFactorAlpha() const { return mSourceBlendFactorAlpha; };

		/** 取得透明度混合目标因子 */
		DRE_BLEND_ALPHA_FACTOR GetDestBlendFactorAlpha() const { return mDestBlendFactorAlpha; };

		/** 取得颜色混合操作 */
		DRE_BLEND_OPERATION GetSceneBlendingOperationColor() const { return mBlendOperationColor; };

		/** Returns the current alpha blending operation */
		DRE_BLEND_OPERATION GetSceneBlendingOperationAlpha() const { return mBlendOperationAlpha; };

		/** 设置深度缓存检查可用 */
		void SetDepthCheckEnabled(bool enabled) { mDepthCheckEnabled = enabled; }

		/** 取得深度缓存检查是否可用 */
		bool GetDepthCheckEnabled(void) const { return mDepthCheckEnabled; }

		/** 设置深度缓存写入可用 */
		void SetDepthWriteEnabled(bool enabled) { mDepthWriteEnabled = enabled; }

		/** 取得深度缓存写入可用 */
		bool GetDepthWriteEnabled(void) const { return mDepthWriteEnabled; }

		/** 设置深度比较方法 */
		void SetDepthFunction(DRE_COMPARISON_FUNC func) { mDepthFunc = func; }
		/** 取得深度比较方法 */
		DRE_COMPARISON_FUNC GetDepthFunction(void) const { return mDepthFunc; }

		/** 设置颜色通道是否可用 */
		void SetColourWriteEnabled(bool redEnabled, bool greenEnabled, bool blueEnabled, bool alphaEnable);
		/** 取得红色通道是否可用 */
		bool GetRedColorWriteEnabled(void) const { return mRedColorWriteEnabled; }
		/** 取得红色通道是否可用 */
		bool GetGreenColorWriteEnabled(void) const { return mGreenColorWriteEnabled; }
		/** 取得红色通道是否可用 */
		bool GetBlueColorWriteEnabled(void) const { return mBlueColorWriteEnabled; }
		/** 取得红色通道是否可用 */
		bool GetAlphaWriteEnabled(void) const { return mAlphaWriteEnabled; }

		/** 设置消除方式 */
		void SetCullingMode(DRE_CULL_MODE mode) { mCullMode = mode; };

		/** 取得消除方式 */
		DRE_CULL_MODE GetCullingMode(void) const;

		/** 取得光照模式 */
		DRE_LIGHTING_MODE GetLightingMode() const { return mLightingMode; }

		/** 设置光照模式 */
		void SetLightingMode(DRE_LIGHTING_MODE mode) { mLightingMode = mode; }

		/** 设置光照渲染是否开启 */
		void SetLightingEnabled(bool enabled) { mLightingEnabled = enabled; }

		/** 取得光照渲染是否开启 */
		bool GetLightingEnabled(void) const { return mLightingEnabled; };

		/** 设置雾化属性 */
		void SetFog(bool fogEnable, DRE_FOG_MODE mode = DRE_FOG_NONE_MODE,
			const Color& color = Color::WHITE,
			f32 expDensity = 0.001f, f32 linearStart = 0.0f, f32 linearEnd = 1.0f);
		/** 取得雾化模式 */
		DRE_FOG_MODE GetFogMode(void) const { return mFogMode; };
		/** 取得雾化颜色 */
		const Color& GetFogColor(void) const { return mFogColor; };
		/** 取得雾化开始距离（范围为0.0 ~ 1.0） */
		f32 GetFogStart(void) const { return mFogStart; };
		/** 取得雾化结束距离（范围为0.0 ~ 1.0） */
		f32 GetFogEnd(void) const { return mFogEnd; };
		/** 取得雾化密度 */
		f32 GetFogDensity(void) const { return mFogDensity; };

		/** 设置深度值偏移属性 */
		void SetDepthBias(f32 constantBias, f32 slopeScaleBias = 0.0f);
		/** 设置深度可能最大值 */
		void SetDepthBiasClamp(f32 depthBiasClamp){ mDepthBiasClamp = depthBiasClamp; };
		/** 取得深度值常量值 */
		f32 GetDepthBiasConstant(void) const { return mDepthBiasConstant; };
		/** 取得深度梯度放大倍数（用于与最大深度相乘） */
		f32 GetDepthBiasSlopeScale(void) const { return mDepthBiasSlopeScale; };
		/** 设置深度可能最大值 */
		f32 GetDepthBiasClamp(void) const { return mDepthBiasClamp; };

		/** 设置透明度覆盖是否可用 */
		void SetAlphaToCoverageEnabled(bool enabled) { mAlphaToCoverageEnabled = enabled; };
		/** 设置透明度覆盖是否可用 */
		bool GetAlphaToCoverageEnabled() const { return mAlphaToCoverageEnabled; }

		/** 取得从属的 technique */
		Technique* GetParent(void) const { return mParent; }

		/** 取得渲染用 shader */
		ShaderPtr GetRenderShader(void) const { return mShader; }
	};

	/** @} */
	/** @} */

}

#endif
