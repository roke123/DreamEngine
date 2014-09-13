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
		Index getIndex(void) const { return mIndex; }

		/** 设置 ambient Color */
		void setAmbient(f32 red, f32 green, f32 blue, f32 alpha);
		/** 设置 ambient Color */
		void setAmbient(const Color& ambient);

		/** 设置 diffuse Color */
		void setDiffuse(f32 red, f32 green, f32 blue, f32 alpha);
		/** 设置 diffuse Color */
		void setDiffuse(const Color& diffuse);

		/** 设置 specular Color */
		void setSpecular(f32 red, f32 green, f32 blue, f32 alpha);
		/** 设置 specular Color */
		void setSpecular(const Color& specular);

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
		DRE_CULL_MODE getCullingMode(void) const;

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

		/** Sets the details of the fragment program to use.
		@remarks
		Only applicable to programmable passes, this sets the details of
		the fragment program to use in this pass. The program will not be
		loaded until the parent Material is loaded.
		@param name The name of the program - this must have been
		created using GpuProgramManager by the time that this Pass
		is loaded. If this parameter is blank, any fragment program in this pass is disabled.
		@param resetParams
		If true, this will create a fresh set of parameters from the
		new program being linked, so if you had previously set parameters
		you will have to set them again. If you set this to false, you must
		be absolutely sure that the parameters match perfectly, and in the
		case of named parameters refers to the indexes underlying them,
		not just the names.
		*/
		void setFragmentProgram(const String& name, bool resetParams = true);
		/** Sets the fragment program parameters.
		@remarks
		Only applicable to programmable passes.
		*/
		void setFragmentProgramParameters(GpuProgramParametersSharedPtr params);
		/** Gets the name of the fragment program used by this pass. */
		const String& getFragmentProgramName(void) const;
		/** Gets the fragment program parameters used by this pass. */
		GpuProgramParametersSharedPtr getFragmentProgramParameters(void) const;
		/** Gets the fragment program used by this pass, only available after _load(). */
		const GpuProgramPtr& getFragmentProgram(void) const;

		/** Sets the details of the geometry program to use.
		@remarks
		Only applicable to programmable passes, this sets the details of
		the geometry program to use in this pass. The program will not be
		loaded until the parent Material is loaded.
		@param name The name of the program - this must have been
		created using GpuProgramManager by the time that this Pass
		is loaded. If this parameter is blank, any geometry program in this pass is disabled.
		@param resetParams
		If true, this will create a fresh set of parameters from the
		new program being linked, so if you had previously set parameters
		you will have to set them again. If you set this to false, you must
		be absolutely sure that the parameters match perfectly, and in the
		case of named parameters refers to the indexes underlying them,
		not just the names.
		*/
		void setGeometryProgram(const String& name, bool resetParams = true);
		/** Sets the geometry program parameters.
		@remarks
		Only applicable to programmable passes.
		*/
		void setGeometryProgramParameters(GpuProgramParametersSharedPtr params);
		/** Gets the name of the geometry program used by this pass. */
		const String& getGeometryProgramName(void) const;
		/** Gets the geometry program parameters used by this pass. */
		GpuProgramParametersSharedPtr getGeometryProgramParameters(void) const;
		/** Gets the geometry program used by this pass, only available after _load(). */
		const GpuProgramPtr& getGeometryProgram(void) const;

		/** Splits this Pass to one which can be handled in the number of
		texture units specified.
		@remarks
		Only works on non-programmable passes, programmable passes cannot be
		split, it's up to the author to ensure that there is a fallback Technique
		for less capable cards.
		@param numUnits The target number of texture units
		@return A new Pass which contains the remaining units, and a scene_blend
		setting appropriate to approximate the multitexture. This Pass will be
		attached to the parent Technique of this Pass.
		*/
		Pass* _split(unsigned short numUnits);

		/** Internal method to adjust pass index. */
		void _notifyIndex(unsigned short index);

		/** Internal method for preparing to load this pass. */
		void _prepare(void);
		/** Internal method for undoing the load preparartion for this pass. */
		void _unprepare(void);
		/** Internal method for loading this pass. */
		void _load(void);
		/** Internal method for unloading this pass. */
		void _unload(void);
		// Is this loaded?
		bool isLoaded(void) const;

		/** Gets the 'hash' of this pass, ie a precomputed number to use for sorting
		@remarks
		This hash is used to sort passes, and for this reason the pass is hashed
		using firstly its index (so that all passes are rendered in order), then
		by the textures which it's TextureUnitState instances are using.
		*/
		uint32 getHash(void) const { return mHash; }
		/// Mark the hash as dirty
		void _dirtyHash(void);
		/** Internal method for recalculating the hash.
		@remarks
		Do not call this unless you are sure the old hash is not still being
		used by anything. If in doubt, call _dirtyHash if you want to force
		recalculation of the has next time.
		*/
		void _recalculateHash(void);
		/** Tells the pass that it needs recompilation. */
		void _notifyNeedsRecompile(void);

		/** Update automatic parameters.
		@param source The source of the parameters
		@param variabilityMask A mask of GpuParamVariability which identifies which autos will need updating
		*/
		void _updateAutoParams(const AutoParamDataSource* source, uint16 variabilityMask) const;

		/** Gets the 'nth' texture which references the given content type.
		@remarks
		If the 'nth' texture unit which references the content type doesn't
		exist, then this method returns an arbitrary high-value outside the
		valid range to index texture units.
		*/
		unsigned short _getTextureUnitWithContentTypeIndex(
			TextureUnitState::ContentType contentType, unsigned short index) const;

		/** Set texture filtering for every texture unit
		@note
		This property actually exists on the TextureUnitState class
		For simplicity, this method allows you to set these properties for
		every current TeextureUnitState, If you need more precision, retrieve the
		TextureUnitState instance and set the property there.
		@see TextureUnitState::setTextureFiltering
		*/
		void setTextureFiltering(TextureFilterOptions filterType);
		/** Sets the anisotropy level to be used for all textures.
		@note
		This property has been moved to the TextureUnitState class, which is accessible via the
		Technique and Pass. For simplicity, this method allows you to set these properties for
		every current TeextureUnitState, If you need more precision, retrieve the Technique,
		Pass and TextureUnitState instances and set the property there.
		@see TextureUnitState::setTextureAnisotropy
		*/
		void setTextureAnisotropy(unsigned int maxAniso);
		/** If set to true, this forces normals to be normalised dynamically
		by the hardware for this pass.
		@remarks
		This option can be used to prevent lighting variations when scaling an
		object - normally because this scaling is hardware based, the normals
		get scaled too which causes lighting to become inconsistent. By default the
		SceneManager detects scaled objects and does this for you, but
		this has an overhead so you might want to turn that off through
		SceneManager::setNormaliseNormalsOnScale(false) and only do it per-Pass
		when you need to.
		*/
		void setNormaliseNormals(bool normalise) { mNormaliseNormals = normalise; }

		/** Returns true if this pass has auto-normalisation of normals set. */
		bool getNormaliseNormals(void) const { return mNormaliseNormals; }

		/** Static method to retrieve all the Passes which need their
		hash values recalculated.
		*/
		static const PassSet& getDirtyHashList(void)
		{
			return msDirtyHashList;
		}
		/** Static method to retrieve all the Passes which are pending deletion.
		*/
		static const PassSet& getPassGraveyard(void)
		{
			return msPassGraveyard;
		}
		/** Static method to reset the list of passes which need their hash
		values recalculated.
		@remarks
		For performance, the dirty list is not updated progressively as
		the hashes are recalculated, instead we expect the processor of the
		dirty hash list to clear the list when they are done.
		*/
		static void clearDirtyHashList(void);

		/** Process all dirty and pending deletion passes. */
		static void processPendingPassUpdates(void);

		/** Queue this pass for deletion when appropriate. */
		void queueForDeletion(void);

		/** Returns whether this pass is ambient only.
		*/
		bool isAmbientOnly(void) const;

		/** Applies texture names to Texture Unit State with matching texture name aliases.
		All Texture Unit States within the pass are checked.
		If matching texture aliases are found then true is returned.

		@param
		aliasList is a map container of texture alias, texture name pairs
		@param
		apply set true to apply the texture aliases else just test to see if texture alias matches are found.
		@return
		True if matching texture aliases were found in the pass.
		*/
		bool applyTextureAliases(const AliasTextureNamePairList& aliasList, const bool apply = true) const;

		/** Sets whether or not this pass will be clipped by a scissor rectangle
		encompassing the lights that are being used in it.
		@remarks
		In order to cut down on fillrate when you have a number of fixed-range
		lights in the scene, you can enable this option to request that
		during rendering, only the region of the screen which is covered by
		the lights is rendered. This region is the screen-space rectangle
		covering the union of the spheres making up the light ranges. Directional
		lights are ignored for this.
		@par
		This is only likely to be useful for multipass additive lighting
		algorithms, where the scene has already been 'seeded' with an ambient
		pass and this pass is just adding light in affected areas.
		@note
		When using SHADOWTYPE_STENCIL_ADDITIVE or SHADOWTYPE_TEXTURE_ADDITIVE,
		this option is implicitly used for all per-light passes and does
		not need to be specified. If you are not using shadows or are using
		a modulative or an integrated shadow technique then this could be useful.

		*/
		void setLightScissoringEnabled(bool enabled) { mLightScissoring = enabled; }
		/** Gets whether or not this pass will be clipped by a scissor rectangle
		encompassing the lights that are being used in it.
		*/
		bool getLightScissoringEnabled() const { return mLightScissoring; }
	};

	/** @} */
	/** @} */

}

#endif
