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


	/** ָ������ render ��Ҫ���ݵ����в���
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
		/// �Ƿ���л�ϲ���
		bool							mBlendEnabled;
		/// �Ƿ������ȱȽ�
		bool							mDepthCheckEnabled;
		/// �Ƿ����д����Ȼ���
		bool							mDepthWriteEnabled;
		/// �Ƿ����д���ɫͨ��
		bool							mRedColorWriteEnabled;
		/// �Ƿ����д����ɫͨ��
		bool							mGreenColorWriteEnabled;
		/// �Ƿ����д����ɫͨ��
		bool							mBlueColorWriteEnabled;
		/// �Ƿ����д��͸����ͨ��
		bool							mAlphaWriteEnabled;
		/// �Ƿ��ڶ���ȡ�������������͸���ȸ���
		/// @note
		///		ʹ�ú� AlphaToCoverage �����������ͨ multisample �õ��� pixel shader output
		bool							mAlphaToCoverageEnabled;
		/// �Ƿ�������
		bool							mLightingEnabled;
		/// �Ƿ����Ͷ����Ӱ��ʹ����Ӱ���ͼ��
		bool							mShadowCasterEnabled;
		/// �Ƿ����Ͷ����Ӱ��ʹ����Ӱ���ͼ��
		bool							mShadowReciverEnabled;
		/// �Ƿ�����
		bool							mFogEnabled;
		//-------------------------------------------------------------------------

		/// �� technique �е�������pass �� Render ˳������������ͬ
		u16								mIndex;
		/// ������ technique
		Technique*						mParent;
		/// pass �� hash�룬���� pass ֮��ıȽϲ���
		u32								mHash; 
		bool mHashDirtyQueued; // needs to be dirtied when next loaded

		//-------------------------------------------------------------------------
		/// ��ϲ�������
		DRE_BLEND_COLOR_FACTOR			mSourceBlendFactorColor;
		DRE_BLEND_COLOR_FACTOR			mDestBlendFactorColor;
		DRE_BLEND_ALPHA_FACTOR			mSourceBlendFactorAlpha;
		DRE_BLEND_ALPHA_FACTOR			mDestBlendFactorAlpha;
		/// ��ϲ���
		DRE_BLEND_OPERATION				mBlendOperationColor;
		DRE_BLEND_OPERATION				mBlendOperationAlpha;
		//-------------------------------------------------------------------------

		//-------------------------------------------------------------------------
		/// ��ȱȽϲ���
		DRE_COMPARISON_FUNC				mDepthFunc;
		/// ��ȳ�����ʵ����ȵ��� 
		///		depth = clmap(_depth + mDepthBiasSlopeScale * mDepthSlopeMax + mDepthBiasConstant, mDepthBiasClamp)
		f32								mDepthBiasConstant;
		/// ����ݶȷŴ�����ʵ����ȵ��� 
		///		depth = clmap(_depth + mDepthBiasSlopeScale * mDepthSlopeMax + mDepthBiasConstant, mDepthBiasClamp)
		f32								mDepthBiasSlopeScale;
		/// ������ֵ��ʵ����ȵ��� 
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
		// ������
		DRE_FOG_MODE					mFogMode;
		Color							mFogColor;
		f32								mFogStart;
		f32								mFogEnd;
		f32								mFogDensity;
		//-------------------------------------------------------------------------

		/// passʹ�õ�shader
		ShaderPtr						mShader;

	public:

		/// ȡ�� pass �� technique �е�����
		Index getIndex(void) const { return mIndex; }

		/** ���� ambient Color */
		void setAmbient(f32 red, f32 green, f32 blue, f32 alpha);
		/** ���� ambient Color */
		void setAmbient(const Color& ambient);

		/** ���� diffuse Color */
		void setDiffuse(f32 red, f32 green, f32 blue, f32 alpha);
		/** ���� diffuse Color */
		void setDiffuse(const Color& diffuse);

		/** ���� specular Color */
		void setSpecular(f32 red, f32 green, f32 blue, f32 alpha);
		/** ���� specular Color */
		void setSpecular(const Color& specular);

		/** ���ø߹��� */
		void SetShininess(f32 val);

		/** ȡ�� ambient Color */
		const Color& getAmbient(void) const;

		/** ȡ�� diffuse Color */
		const Color& getDiffuse(void) const;

		/** ȡ�� specular Color */
		const Color& getSpecular(void) const;

		/** ȡ�ø߹��� */
		f32 GetShininess(void) const;

		/** ����͸���Ȼ������ */
		void SetBlendEnable(bool enable) { mBlendEnabled = enable; };

		/** ����͸���Ȼ������ */
		void SetBlendAlphaFactor(const DRE_BLEND_ALPHA_FACTOR srcFactor, const DRE_BLEND_ALPHA_FACTOR destFactor);

		/** ������ɫ������� */
		void SetBlendColorFactor(const DRE_BLEND_COLOR_FACTOR srcFactor, const DRE_BLEND_COLOR_FACTOR destFactor);

		/** ������ɫ��ϲ��� */
		void SetBlendColorOperation(const DRE_BLEND_OPERATION op) { mBlendOperationColor = op; }

		/** ������ɫ��ϲ��� */
		void SetBlendAlphaOperation(const DRE_BLEND_OPERATION op) { mBlendOperationAlpha = op; }

		/** Return true if this pass uses separate scene blending */
		bool GetBlendEnable() const { return mBlendEnabled; };

		/** ȡ����ɫ���Դ���� */
		DRE_BLEND_COLOR_FACTOR GetSourceBlendFactorColor() const { return mSourceBlendFactorColor; };

		/** ȡ����ɫ���Ŀ������ */
		DRE_BLEND_COLOR_FACTOR GetDestBlendFactorColor() const { return mDestBlendFactorColor; };

		/** ȡ��͸���Ȼ��Դ���� */
		DRE_BLEND_ALPHA_FACTOR GetSourceBlendFactorAlpha() const { return mSourceBlendFactorAlpha; };

		/** ȡ��͸���Ȼ��Ŀ������ */
		DRE_BLEND_ALPHA_FACTOR GetDestBlendFactorAlpha() const { return mDestBlendFactorAlpha; };

		/** ȡ����ɫ��ϲ��� */
		DRE_BLEND_OPERATION GetSceneBlendingOperationColor() const { return mBlendOperationColor; };

		/** Returns the current alpha blending operation */
		DRE_BLEND_OPERATION GetSceneBlendingOperationAlpha() const { return mBlendOperationAlpha; };

		/** ������Ȼ�������� */
		void SetDepthCheckEnabled(bool enabled) { mDepthCheckEnabled = enabled; }

		/** ȡ����Ȼ������Ƿ���� */
		bool GetDepthCheckEnabled(void) const { return mDepthCheckEnabled; }

		/** ������Ȼ���д����� */
		void SetDepthWriteEnabled(bool enabled) { mDepthWriteEnabled = enabled; }

		/** ȡ����Ȼ���д����� */
		bool GetDepthWriteEnabled(void) const { return mDepthWriteEnabled; }

		/** ������ȱȽϷ��� */
		void SetDepthFunction(DRE_COMPARISON_FUNC func) { mDepthFunc = func; }
		/** ȡ����ȱȽϷ��� */
		DRE_COMPARISON_FUNC GetDepthFunction(void) const { return mDepthFunc; }

		/** ������ɫͨ���Ƿ���� */
		void SetColourWriteEnabled(bool redEnabled, bool greenEnabled, bool blueEnabled, bool alphaEnable);
		/** ȡ�ú�ɫͨ���Ƿ���� */
		bool GetRedColorWriteEnabled(void) const { return mRedColorWriteEnabled; }
		/** ȡ�ú�ɫͨ���Ƿ���� */
		bool GetGreenColorWriteEnabled(void) const { return mGreenColorWriteEnabled; }
		/** ȡ�ú�ɫͨ���Ƿ���� */
		bool GetBlueColorWriteEnabled(void) const { return mBlueColorWriteEnabled; }
		/** ȡ�ú�ɫͨ���Ƿ���� */
		bool GetAlphaWriteEnabled(void) const { return mAlphaWriteEnabled; }

		/** ����������ʽ */
		void SetCullingMode(DRE_CULL_MODE mode) { mCullMode = mode; };

		/** ȡ��������ʽ */
		DRE_CULL_MODE getCullingMode(void) const;

		/** ���ù�����Ⱦ�Ƿ��� */
		void SetLightingEnabled(bool enabled) { mLightingEnabled = enabled; }

		/** ȡ�ù�����Ⱦ�Ƿ��� */
		bool GetLightingEnabled(void) const { return mLightingEnabled; };

		/** ���������� */
		void SetFog(bool fogEnable, DRE_FOG_MODE mode = DRE_FOG_NONE_MODE,
			const Color& color = Color::WHITE,
			f32 expDensity = 0.001f, f32 linearStart = 0.0f, f32 linearEnd = 1.0f);
		/** ȡ����ģʽ */
		DRE_FOG_MODE GetFogMode(void) const { return mFogMode; };
		/** ȡ������ɫ */
		const Color& GetFogColor(void) const { return mFogColor; };
		/** ȡ������ʼ���루��ΧΪ0.0 ~ 1.0�� */
		f32 GetFogStart(void) const { return mFogStart; };
		/** ȡ�����������루��ΧΪ0.0 ~ 1.0�� */
		f32 GetFogEnd(void) const { return mFogEnd; };
		/** ȡ�����ܶ� */
		f32 GetFogDensity(void) const { return mFogDensity; };

		/** �������ֵƫ������ */
		void SetDepthBias(f32 constantBias, f32 slopeScaleBias = 0.0f);
		/** ������ȿ������ֵ */
		void SetDepthBiasClamp(f32 depthBiasClamp){ mDepthBiasClamp = depthBiasClamp; };
		/** ȡ�����ֵ����ֵ */
		f32 GetDepthBiasConstant(void) const { return mDepthBiasConstant; };
		/** ȡ������ݶȷŴ�������������������ˣ� */
		f32 GetDepthBiasSlopeScale(void) const { return mDepthBiasSlopeScale; };
		/** ������ȿ������ֵ */
		f32 GetDepthBiasClamp(void) const { return mDepthBiasClamp; };

		/** ����͸���ȸ����Ƿ���� */
		void SetAlphaToCoverageEnabled(bool enabled) { mAlphaToCoverageEnabled = enabled; };
		/** ����͸���ȸ����Ƿ���� */
		bool GetAlphaToCoverageEnabled() const { return mAlphaToCoverageEnabled; }

		/** ȡ�ô����� technique */
		Technique* GetParent(void) const { return mParent; }

		/** ȡ����Ⱦ�� shader */
		ShaderPtr GetRenderShader(void) const { return mShader; }

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
		void SetLightScissoringEnabled(bool enabled) { mLightScissoring = enabled; }
		/** Gets whether or not this pass will be clipped by a scissor rectangle
		encompassing the lights that are being used in it.
		*/
		bool GetLightScissoringEnabled() const { return mLightScissoring; }
	};

	/** @} */
	/** @} */

}

#endif
