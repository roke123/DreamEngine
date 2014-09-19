#ifndef __DRERENDERSYSTEM_H__
#define __DRERENDERSYSTEM_H__

#include "DreRenderDeclaration.h"

#include "DreRenderSystemCapabilities.h"

namespace dream
{

	class DRE_EXPORT_CLASS RenderSystem
	{
	public:
		/** Ĭ�Ϲ��캯��.
		*/

		RenderSystem(AdapterPtr& adpter) {};

	private:
		RenderSystem(const RenderSystem&);
		RenderSystem& operator = (const RenderSystem&);
		    
	public:

		/** ����������
		*/
		virtual ~RenderSystem() {};

		/** �趨�Ƿ�ȴ���ֱ�հ�(����һ֡����ʱ����ǰ֡δ��դ����ɣ�
		* ��һ���������ϻָ���դ��[���ȴ���ֱ�հ�]�����ǵȴ���ǰ֡��դ�����[�ȴ���ֱ�հ�])
		* @note		�Դ��ڻ�������Ӱ�죬ֻ��ȫ���������Ӱ��
		* @param	enabled trueΪ�ȴ����������ȣ���falseΪ���ȴ����ٶ����ȣ�
		*/
		virtual void SetWaitForVerticalBlank(bool enabled) = 0;

		/** �����Ƿ�ȴ���ֱ�հ�
		*/
		virtual bool GetWaitForVerticalBlank(void) const = 0;

		virtual void _FillRenderParameters(SceneManager* sceneMgr, RenderablePtr rend, PassPtr pass, LightList& manualLights) = 0;

		/** ��Ⱦ����
		*/
		virtual void Render(void) = 0;

		/** ���浱ǰ����Ⱦ״̬
		*/
		virtual void SaveRenderState() = 0;

		/** �ָ���һ���������Ⱦ״̬
		*/
		virtual void ResetRenderState() = 0;

	#pragma region BlendState

		/** ������ɫ����Ƿ���
		*/
		virtual void SetBlendEnable(bool enabled) = 0;

		/** ������ɫ����Ƿ���
		*/
		virtual bool GetBlendEnable(void) const = 0;

		/** ���ó�����ɫ��λ��
		* @param src1 ָ�������ɫsrc1��Դ(ZERO, ONE, from pixel render, from renderTarget)
		* @param src2 ָ�������ɫsrc1��Դ(ZERO, ONE, from pixel render, from renderTarget)
		* @param op   ָ����ϲ���
		*/
		virtual void SetSceneColorBlending(DRE_BLEND_COLOR_FACTOR src1, DRE_BLEND_COLOR_FACTOR src2,
			DRE_BLEND_OPERATION op = DRE_BLEND_ADD_OPERATION) = 0;

		/** ���ó�����ɫ͸������λ��
		* @param srcAlpha1 ָ�����͸����src1��Դ(ZERO, ONE, from pixel render, from renderTarget)
		* @param srcAlpha2 ָ�����͸����src1��Դ(ZERO, ONE, from pixel render, from renderTarget)
		* @param alphaOp   ָ��͸���Ȼ�ϲ���
		*/
		virtual void SetSceneAlphaBlending(DRE_BLEND_ALPHA_FACTOR srcAlpha1, DRE_BLEND_ALPHA_FACTOR srcAlpha2,
			DRE_BLEND_OPERATION alphaOp = DRE_BLEND_ADD_OPERATION) = 0;

		/** ָ����ͨ����alphaֵ��Χ
		* @param func ָ���ȽϺ���
		* @param value ָ��͸���Ȳο�ֵ
		*/
		virtual void SetAlphaRejectSettings(DRE_COMPARISON_FUNC func, f32 value) = 0;

		/** ����͸���ȸ����Ƿ����ʹ��
		* @param enabled trueΪ����
		*/
		virtual void SetAlphaToCoverageEnable(bool enabled) = 0;

		/** �趨��ͨ������ɫ
		* @param red �Ƿ����ͨ����ɫ
		* @param green �Ƿ����ͨ����ɫ
		* @param blue �Ƿ����ͨ����ɫ
		* @param alpha �Ƿ����ͨ��͸����
		*/
		virtual void SetColourBufferWriteEnabled(bool red, bool green, bool blue, bool alpha) = 0;

	#pragma endregion

	#pragma region ViewportState
		/** �趨��Ⱦ�ӿ�
		*/
		virtual void SetViewport(const Viewport& vp) = 0;

		/** ȡ�õ�ǰ��Ⱦ�ӿ�
		*/
		virtual Viewport GetViewport(void) = 0;

	#pragma endregion

	#pragma region DepthStencilState

		/** �Ƿ����ɰ����
		*/
		virtual void SetStencilCheckEnabled(bool enabled) = 0;

		/** �趨ǰ���ɰ���Բ���
		* @param refValue ��ǰ�ɰ�ֵ
		* @param writemask ��ǰд���ɰ�ֵ����
		*/
		virtual void SetStencilBufferParams( u8 refValue, u8 writeMask ) = 0;

		/** �趨ǰ���ɰ���Բ���
		* @param func �ɰ���Ժ���
		* @param stencilFailOp �ɰ����ʧ��ʱ�Ĳ���
		* @param depthFailOp �ɰ���Գɹ�����Ȳ���ʧ��ʱ�Ĳ���
		* @param passOp �ɰ���Ժ���Ȳ��Զ��ɹ�ʱ�Ĳ���
		*/
		virtual void SetStencilBufferFrontFaceOp( 
			DRE_COMPARISON_FUNC func, 
			DRE_STENCIL_OPEARTION stencilFailOp, 
			DRE_STENCIL_OPEARTION depthFailOp,
			DRE_STENCIL_OPEARTION passOp ) = 0;

		/** �趨�����ɰ���Բ���
		* @param func �ɰ���Ժ���
		* @param stencilFailOp �ɰ����ʧ��ʱ�Ĳ���
		* @param depthFailOp �ɰ���Գɹ�����Ȳ���ʧ��ʱ�Ĳ���
		* @param passOp �ɰ���Ժ���Ȳ��Զ��ɹ�ʱ�Ĳ���
		*/
		virtual void SetStencilBufferBackFaceOp(
			DRE_COMPARISON_FUNC func, 
			DRE_STENCIL_OPEARTION stencilFailOp, 
			DRE_STENCIL_OPEARTION depthFailOp,
			DRE_STENCIL_OPEARTION passOp ) = 0;

		/** �Ƿ�ʹ����Ȼ�����
		@param enabled trueΪ�򿪣�falseΪ�ر�
		*/
		virtual void SetZBufferEnabled(bool enabled) = 0;

		/** ���ص�ǰ�Ƿ�ʹ����Ȼ�����
		*/
		virtual bool GetZBufferEnabled(void) const = 0;

		/** �趨��Ȼ������
		* @param depthTest �Ƿ������Ȼ�����ԣ�false�򲻱Ƚ�ֱ��д������
		* @param depthWrite �Ƿ��д����Ȼ��壨���Ƿ�ʹ����Ȼ��壩
		* @param depthFunction ��Ȳ��ԱȽϺ���.
		*/
		virtual void SetDepthBufferParams(bool depthTest = true, bool depthWrite = true,
			DRE_COMPARISON_FUNC depthFunction = DRE_COMPARISON_LESSEQUAL) = 0;

		/** ������Ȳ����Ƿ���
		*/
		virtual void SetDepthBufferCheckEnabled(bool enabled) = 0;

		/** ������Ȼ����Ƿ����
		*/
		virtual void SetDepthBufferWriteEnabled(bool enabled) = 0;

		/** ������Ȳ��Ժ���
		*/
		virtual void SetDepthBufferFunction(DRE_COMPARISON_FUNC func) = 0;

	#pragma endregion

	#pragma region RasterizerState
		/** �������ģʽ
		*/
		virtual void SetFillMode(DRE_FILL_MODE fillMode) = 0;

		virtual DRE_FILL_MODE GetFillMode(void) const = 0;
	
		/** ���òü�ģʽ
		* @param mode �ü�ģʽ��һ��ΪDRE_CULL_BACK��������
		*/
		virtual void SetCullingMode(DRE_CULL_MODE mode) = 0;

		virtual DRE_CULL_MODE GetCullingMode(void) const = 0;
	
		/** �����Ƿ�������ȡ��
		*/
		virtual void SetMultisampleEnabled(bool enabled) = 0;

		virtual bool GetMultisampleEnabled() const = 0;

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
		virtual void SetDepthBias(f32 constantBias, f32 slopeScaleBias) = 0;

		/** �������ֵƫ�����ֵ
		* @param	maxDepthBias depthֵ��������ƫ��ֵ
		*
		* @remark	
		*			if(DepthBiasClamp > 0)
		*				Bias = min(DepthBiasClamp, Bias)
		*			else if(DepthBiasClamp < 0)
		*				Bias = max(DepthBiasClamp, Bias)
		*/
		virtual void SetDepthBiasClamp(f32 maxDepthBias) = 0;

		/** ���òü�������Ƿ���
		* @param enabled True to enable the scissor test, false to disable it.
		*/
		virtual void SetScissorTestEnable(bool enabled) = 0;

		/** ����һ���ü���
		* @note Ҫʹ�ü�����Ч����������setScissorTestEnable
		*/
		virtual void SetScissorTest(u32 left, u32 top, u32 right, u32 bottom) = 0;

	#pragma endregion

	#pragma region InputState

	private:
	
	public:

		/** ���ö�������
		*/
		virtual void SetVertexDeclaration(const VertexDeclaration& declaration) = 0;

		/** ����ͼԪ����
		*/
		virtual void SetPolygonMode(DRE_PRIMITIVE_TOPOLOGY level) = 0;

		/** 
		���ö��㻺����
		*/
		virtual void SetHardwareVertexBuffer(HardwareVertexBufferPtr& vertexBuffer) = 0;

		/** ��������������
		*/
		virtual void SetHardwareIndexBuffer(HardwareIndexBufferPtr& vertexBuffer) = 0;

		virtual void SetMaterial(MaterialPtr& hlslShader) = 0;

	#pragma endregion

	#pragma region OnlyDirectX9
		
		/** �趨��ǰ��Ⱦϵͳ�Ƿ�ʹ�ù̶���Ⱦ�ܵ�
		*/
		virtual void SetFixedPipelineEnabled(bool enabled) = 0;

		/** ���ص�ǰ��Ⱦϵͳ�Ƿ�ʹ�ù̶���Ⱦ�ܵ�
		*/
		virtual bool GetFixedPipelineEnabled(void) const = 0;

		/** ���û�����
		*/
		virtual void SetAmbientLight(f32 r, f32 g, f32 b) = 0;

		/** ���ù�Դ��Ⱦ����Ⱦ��������DX9��Ч��DX11�̶�ΪGouraud��ɫ
		*/
		virtual void SetShadingType(DRE_SHADER_OPTION shaderOption) = 0;

		/** �򿪶�̬��Դ
		* @param enabled trueΪ�򿪣�falseΪ�ر�
		*/
		virtual void SetLightingEnabled(bool enabled) = 0;

		/** ������Ⱦ��Դ
		* @param lights ��Դ�б�
		* @param limit ��Դ����
		*/
		virtual void UseLights(const LightList& lights, unsigned short limit) = 0;
	
		/** ��������ת������ */
		virtual void SetWorldMatrix(const Matrix4 &m) = 0;
		/** �������ת������ */
		virtual void SetViewMatrix(const Matrix4 &m) = 0;
		/** ����ͶӰת������ */
		virtual void SetProjectionMatrix(const Matrix4 &m) = 0;

		/** ������Ⱦ����
		* @param ambient	������ķ���ϵ��
		* @param diffuse	�����ķ���ϵ��
		* @param specular	�����ķ���ϵ��
		* @param emissive	�Է����Դ��ɫ
		* @param shininess	����߹�ϵ��
		* @param options	ʹ�ò�����ɫ�е���Щ���粻ʹ�ò�����ɫ���Զ��ڶ�����ɫ��Ѱ�Ҷ�Ӧ��ɫ
		*/
		virtual void SetSurfaceParams(const Color& ambient,
			const Color& diffuse, const Color& specular,
			const Color& emissive, f32 shininess,
			u32 options) = 0;

		/** �Ƿ���������Ч
		*/	
		virtual void SetPointSpritesEnabled(bool enabled) = 0;

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
		virtual void SetPointParameters(f32 size, bool attenuationEnabled, 
			f32 constant, f32 linear, f32 quadratic, f32 minSize, f32 maxSize) = 0;

		/** ����������
		@param mode ��ģʽ
		@param �����ɫ
		@param expDensity	��DRE_FOG_EXP_MODE��DRE_FOG_EXP2_MODE����Ч��������ο�DRE_FOG_EXP_MODE
		@param linearStart	����DRE_FOG_LINEAR_MODE����Ч����ΧΪ[0.0, 1.0]��depthֵ�ķ�Χ����ʹ��DepthֵΪ��׼
		@param linearEnd	����DRE_FOG_LINEAR_MODE����Ч����ΧΪ[0.0, 1.0]��depthֵ�ķ�Χ����ʹ��DepthֵΪ��׼
		*/
		virtual void SetFog(DRE_FOG_MODE mode, const Color& color, f32 expDensity, f32 linearStart, f32 linearEnd) = 0;


		/** �����Ƿ��Զ����滯
		*/
		virtual void SetNormaliseNormals(bool normalise) = 0;


		/** ����һϵ�вü���
		* @param clipPlanes �ü�ƽ���б�
		* @note ֻ��Dirext9��Ч
		*/
		//virtual void setClipPlanes(const PlaneList& clipPlanes);

		/** ����һ���ü�ƽ��
		*/
		virtual void addClipPlane (const Plane &p) = 0;

		/** �������вü�ƽ��
		*/
		virtual void resetClipPlanes() = 0;

	#pragma endregion

	#pragma region SamplerState
		

	#pragma endregion

	#pragma region BindObject
		
		virtual void BindRenderTarget(u32 index, RenderTargetPtr& ) = 0;

		virtual void UnbindRenderTarget(u32 index) = 0;

		virtual void BindRenderWindow(u32 index, RenderWindowPtr& renderWindow) = 0;

		virtual void UnbindRenderWindow(u32 index) = 0;

	#pragma endregion

	#pragma region CreateResource

		/** ����һ��RenderWindow
		* @param		width			���ڿ��
		* @param		height			���ڸ߶�
		* @param		isFullScreen	�Ƿ�ȫ��
		* @param		hasDepth		�Ƿ�ʹ����Ȼ���
		* @param		hasStencil		�Ƿ�ʹ��ģ�建��
		* @param		fsaa			��������
		* @param		fassQuality		��������
		*/
		virtual RenderWindowPtr CreateRenderWindow(u32 width, u32 height, bool isFullScreen,
			bool hasDepth, bool hasStencil, u32 fsaa, u32 fassQuality) = 0;

		/** ����һ��RenderTarget
		* @param		/		width			��ȾĿ����
		* @param		/		height			��ȾĿ��߶�
		* @param	optional	hasDepth		�Ƿ�ʹ����Ȼ���
		* @param	optional	hasStencil		�Ƿ�ʹ��ģ�建��
		* @param	optional	fsaa			��������
		* @param	optional	fassQuality		��������
		*/
		virtual RenderTargetPtr CreateRenderTarget(u32 width, u32 height, bool hasDepth = false,
			bool hasStencil = false, u32 fsaa = 1, u32 fassQuality = 0) = 0;

		/** ��ͼƬ�д���һ��Texture
		* @param		/		image					���������õ�ͼƬ
		* @param		/		usage					�����ڴ�ʹ�ñ�־
		* @param	optional	isTransparentFigure		�Ƿ�͸��ͨ��ͼ
		* @param	optional	fsaa					��������
		* @param	optional	fassQuality				��������
		* @param	optional	gamma					gammaУ��ֵ
		*/
		virtual TexturePtr CreateTextureFromImage(ImagePtr image, DRE_BUFFER_USAGE usage, bool isTransparentFigure = false,
			u32 fsaa = 1, u32 fsaaQuality = 0, f32 gamma = 1.0f) = 0;

		/** ���ļ��д���һ��Texture
		* @param		/		image					���������õ�ͼƬ
		* @param		/		usage					�����ڴ�ʹ�ñ�־
		* @param	optional	isTransparentFigure		�Ƿ�͸��ͨ��ͼ
		* @param	optional	fsaa					��������
		* @param	optional	fassQuality				��������
		* @param	optional	gamma					gammaУ��ֵ
		*/
		virtual TexturePtr CreateTextureFromFile(const char* fileName, DRE_BUFFER_USAGE usage, bool isTransparentFigure = false,
			u32 fsaa = 1, u32 fsaaQuality = 0, f32 gamma = 1.0f) = 0;

		/** ��readBuffer�ж�ȡ����������HardwareVertexBuffer
		* @param		readBuffer			�ɶ�ȡ������
		* @param		vertexSize			�����С
		*/
		virtual HardwareVertexBufferPtr CreateHardwareVertexBuffer(ReadBufferPtr readBuffer, u32 vertexSize, u32 numVertices,
			DRE_PRIMITIVE_TOPOLOGY primitive,
			DRE_BUFFER_USAGE usage, bool haSinstanceData = false, u32 instanceDataStepRate = 0) = 0;

		/** ��readBuffer�ж�ȡ����������HardwareIndexBuffer
		* @param		readBuffer			�ɶ�ȡ������
		* @param		vertexSize			�����С
		*/
		virtual HardwareIndexBufferPtr CreateHardwareIndexBuffer(ReadBufferPtr readBuffer,
			DRE_INDEX_ELEMENT_TYPE type, u32 numIndices, DRE_BUFFER_USAGE usage) = 0;

		/** �Ӷ�ȡ���м���HLSLProgram
		*/
		virtual ShaderPtr CreateShader(ReadBufferPtr readBuffer, const DRE_SHADER_DESC& desc) = 0;

		/** ���ļ��м���HLSLProgram
		*/
		virtual ShaderPtr CreateShader(const DRE_SHADER_DESC& desc) = 0;

	#pragma endregion

		/** ����һ����Ⱦϵͳ����������
		*/
		const RenderSystemCapabilities& GetRenderSystemCapablities() const
		{
			return mCapabilities;
		}

	protected:
		RenderSystemCapabilities mCapabilities;

	};	// end class RenderSystem

}	// end namespace dream

#endif	// end of __DRERENDERSYSTEM_H__