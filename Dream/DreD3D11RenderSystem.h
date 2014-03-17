#ifndef __DRED3D11RENDERSYSTEM_H__
#define __DRED3D11RENDERSYSTEM_H__

#include "DreD3D11RenderDeclaration.h"
#include "DreRenderSystem.h"

namespace dream
{
	
	class D3D11RenderSystem : public RenderSystem
	{
	private:
		struct D3D11RenderState
		{
			/// D3D11��Ⱦ״̬
			D3D11_RASTERIZER_DESC		mRasterizerDesc;
			D3D11_BLEND_DESC			mBlendDesc;
			D3D11_DEPTH_STENCIL_DESC	mDepthStencilDesc;
			// ��Ⱦ����
			f32							mBlendColor[4];
			UINT						mStencilRef;
		};

	private:
		/// ���붥��Ԫ�ص���������
		unique_ptr<D3D11_INPUT_ELEMENT_DESC[]> mInputLayout;
		/// ������ӳ����
		D3D11SamplerMap				mSamplerMap;
		/// D3D11����ӳ����
		D3D11TexturePtrMap			mTextureMap;
		/// D3D11��������
		D3D11TexturePtr				mTextureArray[D3D11_MAX_TEXTURE_NUM];
		/// ����������
		ID3D11SamplerStatePtr		mSamplerArray[D3D11_MAX_SAMPLER_NUM];

		/// D3D11�豸
		ID3D11DevicePtr				mD3D11Device;
		ID3D11DeviceContextPtr		mD3D11Context;
		/// ��ǰ����������
		D3D11HardwareIndexBufferPtr		mCurrentIndexBuffer;
		/// ��ǰ���㻺����
		D3D11HardwareVertexBufferPtr	mCurrentVertexBuffer;

		ID3D11RasterizerStatePtr	mRasterizerState;
		ID3D11BlendStatePtr			mBlendState;
		ID3D11DepthStencilStatePtr	mDepthStencilState;
		/// �󶨵�RenderTarget�б�
		D3D11RenderTargetPtr		mRenderTargetList[D3D11_MAX_RENDER_TARGET_NUM];
		/// �󶨵�RenderWindow�б�
		D3D11RenderWindowPtr		mRenderWindowList[D3D11_MAX_RENDER_WINDOW_NUM];
		/// ��ǰ�󶨵�HLSL��Ⱦ
		D3D11HLSLProgramPtr			mCurrentHLSLProgram;

		D3D11RenderState			mRenderState;
		D3D11RenderState			mSavedRenderState;

		/// D3D���Եȼ�
		D3D_FEATURE_LEVEL			mD3DFeature;
		/// ͼԪ����
		D3D11_PRIMITIVE				mPrimitive;
		/// ���붥��Ԫ�ص����������С
		u32							mInputLayoutCount;
		/// �Ƿ�ȴ���ֱ�հ�
		u32							mWaitForVerticalBlank;
		
		/// ��ʾ��Ⱦ״̬��һ֡���Ƿ�ı��
		bool						mIsRasterizerStateChange;
		bool						mIsBlendStateChange;
		bool						mIsDepthStencilStateChange;
		bool						mIsVertexBufferChange;
		bool						mIsIndexBufferChange;
		bool						mIsHLSLProgramChange;

	public:
		/** Ĭ�Ϲ��캯��.
		*/
		D3D11RenderSystem(ID3D11DevicePtr d3dDevice, ID3D11DeviceContextPtr d3dContext,
			AdapterPtr& adapter);

		/** ��������
		*/
		~D3D11RenderSystem() override;

		/** �趨�Ƿ�ȴ���ֱ�հ�(����һ֡����ʱ����ǰ֡δ��դ����ɣ�
		* ��һ���������ϻָ���դ��[���ȴ���ֱ�հ�]�����ǵȴ���ǰ֡��դ�����[�ȴ���ֱ�հ�])
		* @note		�Դ��ڻ�������Ӱ�죬ֻ��ȫ���������Ӱ��
		* @param	enabled trueΪ�ȴ����������ȣ���falseΪ���ȴ����ٶ����ȣ�
		*/
		void SetWaitForVerticalBlank(bool enabled) override;

		/** �����Ƿ�ȴ���ֱ�հ�
		*/
		bool GetWaitForVerticalBlank(void) const override;

		/** ��Ⱦ����
		*/
		void Render(void) override;

		/** ���浱ǰ����Ⱦ״̬
		*/
		void SaveRenderState() override;

		/** �ָ���һ���������Ⱦ״̬
		*/
		void ResetRenderState() override;

	#pragma region BlendState

		/** ������ɫ����Ƿ���
		*/
		void SetBlendEnable(bool enabled) override;

		/** ������ɫ����Ƿ���
		*/
		bool GetBlendEnable(void) const override;

		/** ���ó�����ɫ��λ��
		* @param src1 ָ�������ɫsrc1��Դ(ZERO, ONE, from pixel render, from renderTarget)
		* @param src2 ָ�������ɫsrc1��Դ(ZERO, ONE, from pixel render, from renderTarget)
		* @param op   ָ����ϲ���
		*/
		void SetSceneColorBlending(DRE_BLEND_COLOR_FACTOR src1, DRE_BLEND_COLOR_FACTOR src2,
			DRE_BLEND_OPERATION op = DRE_BLEND_ADD_OPERATION) override;

		/** ���ó�����ɫ͸������λ��
		* @param srcAlpha1 ָ�����͸����src1��Դ(ZERO, ONE, from pixel render, from renderTarget)
		* @param srcAlpha2 ָ�����͸����src1��Դ(ZERO, ONE, from pixel render, from renderTarget)
		* @param alphaOp   ָ��͸���Ȼ�ϲ���
		*/
		void SetSceneAlphaBlending(DRE_BLEND_ALPHA_FACTOR srcAlpha1, DRE_BLEND_ALPHA_FACTOR srcAlpha2,
			DRE_BLEND_OPERATION alphaOp = DRE_BLEND_ADD_OPERATION) override;

		/** ָ����ͨ����alphaֵ��Χ
		* @param func ָ���ȽϺ���
		* @param value ָ��͸���Ȳο�ֵ
		*/
		void SetAlphaRejectSettings(DRE_COMPARISON_FUNC func, f32 value) override;

		/** ����͸���ȸ����Ƿ����ʹ��
		* @param enabled trueΪ����
		*/
		void SetAlphaToCoverageEnable(bool enabled) override;

		/** �趨��ͨ������ɫ
		* @param red �Ƿ����ͨ����ɫ
		* @param green �Ƿ����ͨ����ɫ
		* @param blue �Ƿ����ͨ����ɫ
		* @param alpha �Ƿ����ͨ��͸����
		*/
		void SetColourBufferWriteEnabled(bool red, bool green, bool blue, bool alpha) override;

	#pragma endregion

	#pragma region ViewportState
		/** �趨��Ⱦ�ӿ�
		*/
		void SetViewport(const Viewport & vp) override;

		/** ȡ�õ�ǰ��Ⱦ�ӿ�
		*/
		Viewport GetViewport(void) override;

	#pragma endregion

	#pragma region DepthStencilState

		/** �Ƿ����ɰ����
		*/
		void SetStencilCheckEnabled(bool enabled) override;

		/** �趨ǰ���ɰ���Բ���
		* @param refValue ��ǰ�ɰ�ֵ
		* @param writemask ��ǰд���ɰ�ֵ����
		*/
		void SetStencilBufferParams(u8 refValue, u8 writeMask) override;

		/** �趨ǰ���ɰ���Բ���
		* @param func �ɰ���Ժ���
		* @param stencilFailOp �ɰ����ʧ��ʱ�Ĳ���
		* @param depthFailOp �ɰ���Գɹ�����Ȳ���ʧ��ʱ�Ĳ���
		* @param passOp �ɰ���Ժ���Ȳ��Զ��ɹ�ʱ�Ĳ���
		*/
		void SetStencilBufferFrontFaceOp( 
			DRE_COMPARISON_FUNC func, 
			DRE_STENCIL_OPEARTION stencilFailOp, 
			DRE_STENCIL_OPEARTION depthFailOp,
			DRE_STENCIL_OPEARTION passOp ) override;

		/** �趨�����ɰ���Բ���
		* @param func �ɰ���Ժ���
		* @param stencilFailOp �ɰ����ʧ��ʱ�Ĳ���
		* @param depthFailOp �ɰ���Գɹ�����Ȳ���ʧ��ʱ�Ĳ���
		* @param passOp �ɰ���Ժ���Ȳ��Զ��ɹ�ʱ�Ĳ���
		*/
		void SetStencilBufferBackFaceOp(
			DRE_COMPARISON_FUNC func, 
			DRE_STENCIL_OPEARTION stencilFailOp, 
			DRE_STENCIL_OPEARTION depthFailOp,
			DRE_STENCIL_OPEARTION passOp ) override;

		/** �Ƿ�ʹ����Ȼ�����
		@param enabled trueΪ�򿪣�falseΪ�ر�
		*/
		void SetZBufferEnabled(bool enabled) override;

		/** ���ص�ǰ�Ƿ�ʹ����Ȼ�����
		*/
		bool GetZBufferEnabled(void) const override;

		/** �趨��Ȼ������
		* @param depthTest �Ƿ������Ȼ�����ԣ�false�򲻱Ƚ�ֱ��д������
		* @param depthWrite �Ƿ��д����Ȼ��壨���Ƿ�ʹ����Ȼ��壩
		* @param depthFunction ��Ȳ��ԱȽϺ���.
		*/
		void SetDepthBufferParams(bool depthTest = true, bool depthWrite = true,
			DRE_COMPARISON_FUNC depthFunction = DRE_COMPARISON_LESSEQUAL) override;

		/** ������Ȳ����Ƿ���
		*/
		void SetDepthBufferCheckEnabled(bool enabled) override;

		/** ������Ȼ����Ƿ����
		*/
		void SetDepthBufferWriteEnabled(bool enabled) override;

		/** ������Ȳ��Ժ���
		*/
		void SetDepthBufferFunction(DRE_COMPARISON_FUNC func) override;

	#pragma endregion

	#pragma region RasterizerState
		/** �������ģʽ
		*/
		void SetFillMode(DRE_FILL_MODE fillMode) override;

		DRE_FILL_MODE GetFillMode(void) const override;
	
		/** ���òü�ģʽ
		* @param mode �ü�ģʽ��һ��ΪDRE_CULL_BACK��������
		*/
		void SetCullingMode(DRE_CULL_MODE mode) override;

		DRE_CULL_MODE GetCullingMode(void) const override;
	
		/** �����Ƿ�������ȡ��
		*/
		void SetMultisampleEnabled(bool enabled) override;

		bool GetMultisampleEnabled() const override;

		/** �������ֵƫ�Ʋ���
		* @param	constantBias depthֵ�ĳ���ƫ��
		* @param	slopeScaleBias depthֵ�����ֵ����
		*
		* @remark	bias = constantBias * r + slopeScaleBias * MaxDepthSlope;
		*			where r is the minimum representable value > 0 in the 
		*			depth-buffer format converted to float32. The remaining values are structure members. 
		*			r -			��depth buffer formatת����f32����С����0����Чֵ
		*			MaxDepth -	��depth buffer formatת����f32��������Чֵ
		*			
		*			�������ֵ zValue = zValue + bias
		*/
		void SetDepthBias(f32 constantBias, f32 slopeScaleBias) override;

		/** �������ֵƫ�����ֵ
		* @param	maxDepthBias depthֵ��������ƫ��ֵ
		*
		* @remark	
		*			if(DepthBiasClamp > 0)
		*				Bias = min(DepthBiasClamp, Bias)
		*			else if(DepthBiasClamp < 0)
		*				Bias = max(DepthBiasClamp, Bias)
		*/
		void SetDepthBiasClamp(f32 maxDepthBias) override;

		/** ���òü�������Ƿ���
		* @param enabled True to enable the scissor test, false to disable it.
		*/
		void SetScissorTestEnable(bool enabled) override;

		/** ����һ���ü���
		* @note Ҫʹ�ü�����Ч����������setScissorTestEnable
		*/
		void SetScissorTest(u32 left, u32 top, u32 right, u32 bottom) override;

	#pragma endregion

	#pragma region InputState
	
	public:
		/** ���ö�������
		*/
		void SetVertexDeclaration(const VertexDeclaration& declaration) override;

		/** ����ͼԪ����
		*/
		void SetPolygonMode(DRE_PRIMITIVE_TOPOLOGY level) override;

		/** 
		���ö��㻺����
		*/
		void SetHardwareVertexBuffer(HardwareVertexBufferPtr& vertexBuffer) override;

		/** ��������������
		*/
		void SetHardwareIndexBuffer(HardwareIndexBufferPtr& indexBuffer) override;

		/** ����HLSL��Ⱦ
		*/
		void SetHLSLShader(HLSLProgramPtr& hlslShader) override;

	#pragma endregion

	#pragma region OnlyDirectX9
		
		/** �趨��ǰ��Ⱦϵͳ�Ƿ�ʹ�ù̶���Ⱦ�ܵ�
		*/
		void SetFixedPipelineEnabled(bool enabled) override;

		/** ���ص�ǰ��Ⱦϵͳ�Ƿ�ʹ�ù̶���Ⱦ�ܵ�
		*/
		bool GetFixedPipelineEnabled(void) const override;

		/** ���û�����
		*/
		 void SetAmbientLight(f32 r, f32 g, f32 b) override;

		/** ���ù�Դ��Ⱦ����Ⱦ��������DX9��Ч��DX11�̶�ΪGouraud��ɫ
		*/
		 void SetShadingType(DRE_SHADER_OPTION shaderOption) override;

		/** �򿪶�̬��Դ
		* @param enabled trueΪ�򿪣�falseΪ�ر�
		*/
		 void SetLightingEnabled(bool enabled) override;

		/** ������Ⱦ��Դ
		* @param lights ��Դ�б�
		* @param limit ��Դ����
		*/
		 void UseLights(const LightList& lights, unsigned short limit) override;
	
		/** ��������ת������ */
		 void SetWorldMatrix(const Matrix4 &m) override;
		/** �������ת������ */
		 void SetViewMatrix(const Matrix4 &m) override;
		/** ����ͶӰת������ */
		 void SetProjectionMatrix(const Matrix4 &m) override;

		/** ������Ⱦ����
		* @param ambient	������ķ���ϵ��
		* @param diffuse	�����ķ���ϵ��
		* @param specular	�����ķ���ϵ��
		* @param emissive	�Է����Դ��ɫ
		* @param shininess	����߹�ϵ��
		* @param options	ʹ�ò�����ɫ�е���Щ���粻ʹ�ò�����ɫ���Զ��ڶ�����ɫ��Ѱ�Ҷ�Ӧ��ɫ
		*/
		 void SetSurfaceParams(const Color& ambient,
			const Color& diffuse, const Color& specular,
			const Color& emissive, f32 shininess,
			u32 options) override;

		/** �Ƿ���������Ч
		*/	
		 void SetPointSpritesEnabled(bool enabled) override;

		/** ����������Ч����
		* @remarks	����attenuationEnabledʱ�����Ӵ�С�������˥����˥������ʽΪattenuation =
		*			1 / (constant + linear * dist + quadratic * d^2) .
		* @param size			���ӳ�ʼ��С
		* @param attenuation	�Ƿ���˥��
		* @param constant		����˥��
		* @param linear			����˥��
		* @param quadratic		����˥��
		* @param minSize		������С��С
		* @param maxSize		��������С
		*/
		 void SetPointParameters(f32 size, bool attenuationEnabled, 
			f32 constant, f32 linear, f32 quadratic, f32 minSize, f32 maxSize) override;

		/** ����������
		@param mode ��ģʽ
		@param �����ɫ
		@param expDensity	��DRE_FOG_EXP_MODE��DRE_FOG_EXP2_MODE����Ч��������ο�DRE_FOG_EXP_MODE
		@param linearStart	����DRE_FOG_LINEAR_MODE����Ч����ΧΪ[0.0, 1.0]��depthֵ�ķ�Χ����ʹ��DepthֵΪ��׼
		@param linearEnd	����DRE_FOG_LINEAR_MODE����Ч����ΧΪ[0.0, 1.0]��depthֵ�ķ�Χ����ʹ��DepthֵΪ��׼
		*/
		 void SetFog(DRE_FOG_MODE mode, const Color& color, f32 expDensity, f32 linearStart, f32 linearEnd) override;


		/** �����Ƿ��Զ����滯
		*/
		 void SetNormaliseNormals(bool normalise) override;


		/** ����һϵ�вü���
		* @param clipPlanes �ü�ƽ���б�
		* @note ֻ��Dirext9��Ч
		*/
		// void setClipPlanes(const PlaneList& clipPlanes);

		/** ����һ���ü�ƽ��
		*/
		 void addClipPlane (const Plane &p) override;

		/** �������вü�ƽ��
		*/
		 void resetClipPlanes() override;

	#pragma endregion

	#pragma region SamplerState

		/** ����һ���Ĵ�����Ϊindex��sampler
		* @param	index		����ļĴ�������
		* @param	sampler		������
		*/
		void SetSampler(u32 index, const SamplerDesc& sampler) override;

		/** ����һ������Ϊsematics��sampler
		* @param	index		hlsl����
		* @param	sampler		������
		*/
		void SetSampler(const c8* sematics, const SamplerDesc& sampler) override;

	private:
		/** ͨ��SamplerDesc����ID3D11Sampler
		*/
		ID3D11SamplerStatePtr CreateSampler(const SamplerDesc& sampler);

	public:
		/** ����һ���Ĵ�����Ϊindex��texture
		* @param	index		����ļĴ�������
		* @param	texture		����
		*/
		void SetTexture(u32 texIndex, TexturePtr& texture) override;

		/** ����һ������Ϊsematics��texture
		* @param	index		hlsl����
		* @param	texture		����
		*/
		void SetTexture(const c8* sematics, TexturePtr& texture) override;

	#pragma endregion

	#pragma region BindObject

		void BindRenderTarget(u32 index, RenderTargetPtr& ) override;

		void UnbindRenderTarget(u32 index) override;

		void BindRenderWindow(u32 index, RenderWindowPtr& renderWindow) override;

		void UnbindRenderWindow(u32 index) override; 

	#pragma endregion

	#pragma region CreateResource
	
	public:
		/** ����һ��RenderWindow
		* @param		width			���ڿ��
		* @param		height			���ڸ߶�
		* @param		isFullScreen	�Ƿ�ȫ��
		* @param		hasDepth		�Ƿ�ʹ����Ȼ���
		* @param		hasStencil		�Ƿ�ʹ��ģ�建��
		* @param		fsaa			��������
		* @param		fassQuality		��������
		*/
		RenderWindowPtr CreateRenderWindow(u32 width, u32 height, bool isFullScreen,
			bool hasDepth, bool hasStencil, u32 fsaa, u32 fassQuality) override;

		/** ����һ��RenderTarget
		* @param		/		width			��ȾĿ����
		* @param		/		height			��ȾĿ��߶�
		* @param	optional	hasDepth		�Ƿ�ʹ����Ȼ���
		* @param	optional	hasStencil		�Ƿ�ʹ��ģ�建��
		* @param	optional	fsaa			��������
		* @param	optional	fassQuality		��������
		*/
		RenderTargetPtr CreateRenderTarget(u32 width, u32 height, bool hasDepth = false,
			bool hasStencil = false, u32 fsaa = 1, u32 fassQuality = 0) override;

		/** ��ͼƬ�д���һ��Texture
		* @param		/		image					���������õ�ͼƬ
		* @param		/		usage					�����ڴ�ʹ�ñ�־
		* @param	optional	isTransparentFigure		�Ƿ�͸��ͨ��ͼ
		* @param	optional	fsaa					��������
		* @param	optional	fassQuality				��������
		* @param	optional	gamma					gammaУ��ֵ
		*/
		TexturePtr CreateTextureFromImage(ImagePtr image, DRE_BUFFER_USAGE usage, bool isTransparentFigure = false,
			u32 fsaa = 1, u32 fsaaQuality = 0, f32 gamma = 1.0f) override;

		/** ���ļ��д���һ��Texture
		* @param		/		image					���������õ�ͼƬ
		* @param		/		usage					�����ڴ�ʹ�ñ�־
		* @param	optional	isTransparentFigure		�Ƿ�͸��ͨ��ͼ
		* @param	optional	fsaa					��������
		* @param	optional	fassQuality				��������
		* @param	optional	gamma					gammaУ��ֵ
		*/
		TexturePtr CreateTextureFromFile(const char* fileName, DRE_BUFFER_USAGE usage, bool isTransparentFigure = false,
			u32 fsaa = 1, u32 fsaaQuality = 0, f32 gamma = 1.0f) override;

		/** ��readBuffer�ж�ȡ����������HardwareVertexBuffer
		* @param		readBuffer			�ɶ�ȡ������
		* @param		vertexSize			�����С
		*/
		HardwareVertexBufferPtr CreateHardwareVertexBuffer(ReadBufferPtr readBuffer, u32 vertexSize, u32 numVertices,
			DRE_PRIMITIVE_TOPOLOGY primitive,
			DRE_BUFFER_USAGE usage, bool hasInstanceData = false, u32 instanceDataStepRate = 0) override;

		/** CreateHardwareVertexBuffer�ľ���ʵ��
		*/
		HardwareVertexBufferPtr CreateHardwareVertexBuffer(const u8Array data, u32 vertexSize, u32 numVertices,
			DRE_PRIMITIVE_TOPOLOGY primitive,
			DRE_BUFFER_USAGE usage, bool hasInstanceData = false, u32 instanceDataStepRate = 0);

		/** ��readBuffer�ж�ȡ����������HardwareIndexBuffer
		* @param		readBuffer			�ɶ�ȡ������
		* @param		vertexSize			�����С
		*/
		HardwareIndexBufferPtr CreateHardwareIndexBuffer(ReadBufferPtr readBuffer,
			DRE_INDEX_ELEMENT_TYPE type, u32 numIndices, DRE_BUFFER_USAGE usage) override;

		/** CreateHardwareIndexBuffer�ľ���ʵ��
		*/
		HardwareIndexBufferPtr CreateHardwareIndexBuffer(const u8Array data,
			DRE_INDEX_ELEMENT_TYPE type, u32 numIndices, DRE_BUFFER_USAGE usage);

		/** �Ӷ�ȡ���м���HLSLProgram
		*/
		HLSLProgramPtr CreateHLSLProgram(ReadBufferPtr readBuffer, const DRE_HLSLPROGRAM_DESC &desc) override;

		/** ���ļ��м���HLSLProgram
		*/
		HLSLProgramPtr CreateHLSLProgram(const DRE_HLSLPROGRAM_DESC& desc) override;

	private:
		ID3D10BlobPtr CreateShaderFromFile(const c8* shaderFile, const c8* shaderName, 
			const c8* shaderVerson);
	
	#pragma endregion

	public:
		// �������г���
		static LRESULT CALLBACK WndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	};	// end class D3D11RenderSystem

}	// end namespace dream

#endif	// end __DRED3D11RENDERSYSTEM_H__