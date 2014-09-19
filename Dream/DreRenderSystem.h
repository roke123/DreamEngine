#ifndef __DRERENDERSYSTEM_H__
#define __DRERENDERSYSTEM_H__

#include "DreRenderDeclaration.h"

#include "DreRenderSystemCapabilities.h"

namespace dream
{

	class DRE_EXPORT_CLASS RenderSystem
	{
	public:
		/** 默认构造函数.
		*/

		RenderSystem(AdapterPtr& adpter) {};

	private:
		RenderSystem(const RenderSystem&);
		RenderSystem& operator = (const RenderSystem&);
		    
	public:

		/** 虚析构函数
		*/
		virtual ~RenderSystem() {};

		/** 设定是否等待垂直空白(在下一帧到来时，当前帧未光栅化完成，
		* 下一动作是马上恢复光栅器[不等待垂直空白]，还是等待当前帧光栅化完成[等待垂直空白])
		* @note		对窗口化程序无影响，只对全屏程序造成影响
		* @param	enabled true为等待（质量优先），false为不等待（速度优先）
		*/
		virtual void SetWaitForVerticalBlank(bool enabled) = 0;

		/** 返回是否等待垂直空白
		*/
		virtual bool GetWaitForVerticalBlank(void) const = 0;

		virtual void _FillRenderParameters(SceneManager* sceneMgr, RenderablePtr rend, PassPtr pass, LightList& manualLights) = 0;

		/** 渲染函数
		*/
		virtual void Render(void) = 0;

		/** 保存当前的渲染状态
		*/
		virtual void SaveRenderState() = 0;

		/** 恢复上一个保存的渲染状态
		*/
		virtual void ResetRenderState() = 0;

	#pragma region BlendState

		/** 设置颜色混合是否开启
		*/
		virtual void SetBlendEnable(bool enabled) = 0;

		/** 返回颜色混合是否开启
		*/
		virtual bool GetBlendEnable(void) const = 0;

		/** 设置场景颜色如何混合
		* @param src1 指定混合颜色src1来源(ZERO, ONE, from pixel render, from renderTarget)
		* @param src2 指定混合颜色src1来源(ZERO, ONE, from pixel render, from renderTarget)
		* @param op   指定混合操作
		*/
		virtual void SetSceneColorBlending(DRE_BLEND_COLOR_FACTOR src1, DRE_BLEND_COLOR_FACTOR src2,
			DRE_BLEND_OPERATION op = DRE_BLEND_ADD_OPERATION) = 0;

		/** 设置场景颜色透明度如何混合
		* @param srcAlpha1 指定混合透明度src1来源(ZERO, ONE, from pixel render, from renderTarget)
		* @param srcAlpha2 指定混合透明度src1来源(ZERO, ONE, from pixel render, from renderTarget)
		* @param alphaOp   指定透明度混合操作
		*/
		virtual void SetSceneAlphaBlending(DRE_BLEND_ALPHA_FACTOR srcAlpha1, DRE_BLEND_ALPHA_FACTOR srcAlpha2,
			DRE_BLEND_OPERATION alphaOp = DRE_BLEND_ADD_OPERATION) = 0;

		/** 指定可通过的alpha值范围
		* @param func 指定比较函数
		* @param value 指定透明度参考值
		*/
		virtual void SetAlphaRejectSettings(DRE_COMPARISON_FUNC func, f32 value) = 0;

		/** 设置透明度覆盖是否可以使用
		* @param enabled true为开启
		*/
		virtual void SetAlphaToCoverageEnable(bool enabled) = 0;

		/** 设定可通过的颜色
		* @param red 是否可以通过红色
		* @param green 是否可以通过绿色
		* @param blue 是否可以通过蓝色
		* @param alpha 是否可以通过透明度
		*/
		virtual void SetColourBufferWriteEnabled(bool red, bool green, bool blue, bool alpha) = 0;

	#pragma endregion

	#pragma region ViewportState
		/** 设定渲染视口
		*/
		virtual void SetViewport(const Viewport& vp) = 0;

		/** 取得当前渲染视口
		*/
		virtual Viewport GetViewport(void) = 0;

	#pragma endregion

	#pragma region DepthStencilState

		/** 是否开启蒙版测试
		*/
		virtual void SetStencilCheckEnabled(bool enabled) = 0;

		/** 设定前面蒙版测试参数
		* @param refValue 当前蒙板值
		* @param writemask 当前写入蒙版值掩码
		*/
		virtual void SetStencilBufferParams( u8 refValue, u8 writeMask ) = 0;

		/** 设定前面蒙版测试参数
		* @param func 蒙版测试函数
		* @param stencilFailOp 蒙版测试失败时的操作
		* @param depthFailOp 蒙版测试成功，深度测试失败时的操作
		* @param passOp 蒙版测试和深度测试都成功时的操作
		*/
		virtual void SetStencilBufferFrontFaceOp( 
			DRE_COMPARISON_FUNC func, 
			DRE_STENCIL_OPEARTION stencilFailOp, 
			DRE_STENCIL_OPEARTION depthFailOp,
			DRE_STENCIL_OPEARTION passOp ) = 0;

		/** 设定背面蒙版测试参数
		* @param func 蒙版测试函数
		* @param stencilFailOp 蒙版测试失败时的操作
		* @param depthFailOp 蒙版测试成功，深度测试失败时的操作
		* @param passOp 蒙版测试和深度测试都成功时的操作
		*/
		virtual void SetStencilBufferBackFaceOp(
			DRE_COMPARISON_FUNC func, 
			DRE_STENCIL_OPEARTION stencilFailOp, 
			DRE_STENCIL_OPEARTION depthFailOp,
			DRE_STENCIL_OPEARTION passOp ) = 0;

		/** 是否使用深度缓冲区
		@param enabled true为打开，false为关闭
		*/
		virtual void SetZBufferEnabled(bool enabled) = 0;

		/** 返回当前是否使用深度缓冲区
		*/
		virtual bool GetZBufferEnabled(void) const = 0;

		/** 设定深度缓冲参数
		* @param depthTest 是否进行深度缓冲测试，false则不比较直接写入像素
		* @param depthWrite 是否可写入深度缓冲（及是否使用深度缓冲）
		* @param depthFunction 深度测试比较函数.
		*/
		virtual void SetDepthBufferParams(bool depthTest = true, bool depthWrite = true,
			DRE_COMPARISON_FUNC depthFunction = DRE_COMPARISON_LESSEQUAL) = 0;

		/** 设置深度测试是否开启
		*/
		virtual void SetDepthBufferCheckEnabled(bool enabled) = 0;

		/** 设置深度缓冲是否可用
		*/
		virtual void SetDepthBufferWriteEnabled(bool enabled) = 0;

		/** 设置深度测试函数
		*/
		virtual void SetDepthBufferFunction(DRE_COMPARISON_FUNC func) = 0;

	#pragma endregion

	#pragma region RasterizerState
		/** 设置填充模式
		*/
		virtual void SetFillMode(DRE_FILL_MODE fillMode) = 0;

		virtual DRE_FILL_MODE GetFillMode(void) const = 0;
	
		/** 设置裁剪模式
		* @param mode 裁剪模式，一般为DRE_CULL_BACK背面消隐
		*/
		virtual void SetCullingMode(DRE_CULL_MODE mode) = 0;

		virtual DRE_CULL_MODE GetCullingMode(void) const = 0;
	
		/** 设置是否开启多重取样
		*/
		virtual void SetMultisampleEnabled(bool enabled) = 0;

		virtual bool GetMultisampleEnabled() const = 0;

		/** 设置深度值偏移参数
		* @param	constantBias depth值的常量偏移
		* @param	slopeScaleBias depth值的最大值比重
		*
		* @remark	bias = constantBias * r + slopeScaleBias * MaxDepthSlope;
		*			where r is the minimum representable value > 0 in the 
		*			depth-buffer format converted to float32. The remaining values are structure members. 
		*			r -			当depth buffer format转换成f32的最小大于0的有效值
		*			MaxDepth -	当depth buffer format转换成f32的最大的有效值
		*			
		*			最终深度值 zValue = zValue + bias
		*/
		virtual void SetDepthBias(f32 constantBias, f32 slopeScaleBias) = 0;

		/** 设置深度值偏移最大值
		* @param	maxDepthBias depth值的最大可能偏移值
		*
		* @remark	
		*			if(DepthBiasClamp > 0)
		*				Bias = min(DepthBiasClamp, Bias)
		*			else if(DepthBiasClamp < 0)
		*				Bias = max(DepthBiasClamp, Bias)
		*/
		virtual void SetDepthBiasClamp(f32 maxDepthBias) = 0;

		/** 设置裁剪框测试是否开启
		* @param enabled True to enable the scissor test, false to disable it.
		*/
		virtual void SetScissorTestEnable(bool enabled) = 0;

		/** 设置一个裁剪框
		* @note 要使裁剪框有效必须先设置setScissorTestEnable
		*/
		virtual void SetScissorTest(u32 left, u32 top, u32 right, u32 bottom) = 0;

	#pragma endregion

	#pragma region InputState

	private:
	
	public:

		/** 设置顶点描述
		*/
		virtual void SetVertexDeclaration(const VertexDeclaration& declaration) = 0;

		/** 设置图元类型
		*/
		virtual void SetPolygonMode(DRE_PRIMITIVE_TOPOLOGY level) = 0;

		/** 
		设置顶点缓冲区
		*/
		virtual void SetHardwareVertexBuffer(HardwareVertexBufferPtr& vertexBuffer) = 0;

		/** 设置索引缓冲区
		*/
		virtual void SetHardwareIndexBuffer(HardwareIndexBufferPtr& vertexBuffer) = 0;

		virtual void SetMaterial(MaterialPtr& hlslShader) = 0;

	#pragma endregion

	#pragma region OnlyDirectX9
		
		/** 设定当前渲染系统是否使用固定渲染管道
		*/
		virtual void SetFixedPipelineEnabled(bool enabled) = 0;

		/** 返回当前渲染系统是否使用固定渲染管道
		*/
		virtual bool GetFixedPipelineEnabled(void) const = 0;

		/** 设置环境光
		*/
		virtual void SetAmbientLight(f32 r, f32 g, f32 b) = 0;

		/** 设置光源渲染的渲染方法，对DX9有效，DX11固定为Gouraud着色
		*/
		virtual void SetShadingType(DRE_SHADER_OPTION shaderOption) = 0;

		/** 打开动态光源
		* @param enabled true为打开，false为关闭
		*/
		virtual void SetLightingEnabled(bool enabled) = 0;

		/** 设置渲染光源
		* @param lights 光源列表
		* @param limit 光源数量
		*/
		virtual void UseLights(const LightList& lights, unsigned short limit) = 0;
	
		/** 设置世界转换矩阵 */
		virtual void SetWorldMatrix(const Matrix4 &m) = 0;
		/** 设置相机转换矩阵 */
		virtual void SetViewMatrix(const Matrix4 &m) = 0;
		/** 设置投影转换矩阵 */
		virtual void SetProjectionMatrix(const Matrix4 &m) = 0;

		/** 设置渲染材质
		* @param ambient	环境光的反射系数
		* @param diffuse	漫射光的反射系数
		* @param specular	镜面光的反射系数
		* @param emissive	自发光光源颜色
		* @param shininess	反射高光系数
		* @param options	使用材质颜色中的那些，如不使用材质颜色则自动在顶点颜色中寻找对应颜色
		*/
		virtual void SetSurfaceParams(const Color& ambient,
			const Color& diffuse, const Color& specular,
			const Color& emissive, f32 shininess,
			u32 options) = 0;

		/** 是否开启粒子特效
		*/	
		virtual void SetPointSpritesEnabled(bool enabled) = 0;

		/** 设置粒子特效参数
		* @remarks	当打开attenuationEnabled时，粒子大小会随距离衰减，衰减量公式为attenuation =
		*			1 / (constant + linear * dist + quadratic * d^2) .
		* @param size			粒子初始大小
		* @param attenuation	是否开启衰减
		* @param constant		常量衰减
		* @param linear			线性衰减
		* @param quadratic		二次衰减
		* @param minSize		粒子最小大小
		* @param maxSize		粒子最大大小
		*/
		virtual void SetPointParameters(f32 size, bool attenuationEnabled, 
			f32 constant, f32 linear, f32 quadratic, f32 minSize, f32 maxSize) = 0;

		/** 设置雾化参数
		@param mode 雾化模式
		@param 雾的颜色
		@param expDensity	在DRE_FOG_EXP_MODE和DRE_FOG_EXP2_MODE中有效，具体请参考DRE_FOG_EXP_MODE
		@param linearStart	仅在DRE_FOG_LINEAR_MODE中有效，范围为[0.0, 1.0]（depth值的范围），使用Depth值为标准
		@param linearEnd	仅在DRE_FOG_LINEAR_MODE中有效，范围为[0.0, 1.0]（depth值的范围），使用Depth值为标准
		*/
		virtual void SetFog(DRE_FOG_MODE mode, const Color& color, f32 expDensity, f32 linearStart, f32 linearEnd) = 0;


		/** 设置是否自动正规化
		*/
		virtual void SetNormaliseNormals(bool normalise) = 0;


		/** 设置一系列裁剪面
		* @param clipPlanes 裁剪平面列表
		* @note 只对Dirext9有效
		*/
		//virtual void setClipPlanes(const PlaneList& clipPlanes);

		/** 增加一个裁剪平面
		*/
		virtual void addClipPlane (const Plane &p) = 0;

		/** 重置所有裁剪平面
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

		/** 创建一个RenderWindow
		* @param		width			窗口宽度
		* @param		height			窗口高度
		* @param		isFullScreen	是否全屏
		* @param		hasDepth		是否使用深度缓冲
		* @param		hasStencil		是否使用模板缓冲
		* @param		fsaa			采样次数
		* @param		fassQuality		采样质量
		*/
		virtual RenderWindowPtr CreateRenderWindow(u32 width, u32 height, bool isFullScreen,
			bool hasDepth, bool hasStencil, u32 fsaa, u32 fassQuality) = 0;

		/** 创建一个RenderTarget
		* @param		/		width			渲染目标宽度
		* @param		/		height			渲染目标高度
		* @param	optional	hasDepth		是否使用深度缓冲
		* @param	optional	hasStencil		是否使用模板缓冲
		* @param	optional	fsaa			采样次数
		* @param	optional	fassQuality		采样质量
		*/
		virtual RenderTargetPtr CreateRenderTarget(u32 width, u32 height, bool hasDepth = false,
			bool hasStencil = false, u32 fsaa = 1, u32 fassQuality = 0) = 0;

		/** 从图片中创建一个Texture
		* @param		/		image					创建纹理用的图片
		* @param		/		usage					纹理内存使用标志
		* @param	optional	isTransparentFigure		是否透明通道图
		* @param	optional	fsaa					采样次数
		* @param	optional	fassQuality				采样质量
		* @param	optional	gamma					gamma校正值
		*/
		virtual TexturePtr CreateTextureFromImage(ImagePtr image, DRE_BUFFER_USAGE usage, bool isTransparentFigure = false,
			u32 fsaa = 1, u32 fsaaQuality = 0, f32 gamma = 1.0f) = 0;

		/** 从文件中创建一个Texture
		* @param		/		image					创建纹理用的图片
		* @param		/		usage					纹理内存使用标志
		* @param	optional	isTransparentFigure		是否透明通道图
		* @param	optional	fsaa					采样次数
		* @param	optional	fassQuality				采样质量
		* @param	optional	gamma					gamma校正值
		*/
		virtual TexturePtr CreateTextureFromFile(const char* fileName, DRE_BUFFER_USAGE usage, bool isTransparentFigure = false,
			u32 fsaa = 1, u32 fsaaQuality = 0, f32 gamma = 1.0f) = 0;

		/** 从readBuffer中读取数据来生成HardwareVertexBuffer
		* @param		readBuffer			可读取缓冲区
		* @param		vertexSize			顶点大小
		*/
		virtual HardwareVertexBufferPtr CreateHardwareVertexBuffer(ReadBufferPtr readBuffer, u32 vertexSize, u32 numVertices,
			DRE_PRIMITIVE_TOPOLOGY primitive,
			DRE_BUFFER_USAGE usage, bool haSinstanceData = false, u32 instanceDataStepRate = 0) = 0;

		/** 从readBuffer中读取数据来生成HardwareIndexBuffer
		* @param		readBuffer			可读取缓冲区
		* @param		vertexSize			顶点大小
		*/
		virtual HardwareIndexBufferPtr CreateHardwareIndexBuffer(ReadBufferPtr readBuffer,
			DRE_INDEX_ELEMENT_TYPE type, u32 numIndices, DRE_BUFFER_USAGE usage) = 0;

		/** 从读取流中加载HLSLProgram
		*/
		virtual ShaderPtr CreateShader(ReadBufferPtr readBuffer, const DRE_SHADER_DESC& desc) = 0;

		/** 从文件中加载HLSLProgram
		*/
		virtual ShaderPtr CreateShader(const DRE_SHADER_DESC& desc) = 0;

	#pragma endregion

		/** 返回一个渲染系统的能力描述
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