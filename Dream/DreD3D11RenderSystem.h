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
			/// D3D11渲染状态
			D3D11_RASTERIZER_DESC		mRasterizerDesc;
			D3D11_BLEND_DESC			mBlendDesc;
			D3D11_DEPTH_STENCIL_DESC	mDepthStencilDesc;
			// 渲染参数
			f32							mBlendColor[4];
			UINT						mStencilRef;
		};

	private:
		/// 输入顶点元素的描述数组
		unique_ptr<D3D11_INPUT_ELEMENT_DESC[]> mInputLayout;
		/// 采样器映射组
		D3D11SamplerMap				mSamplerMap;
		/// D3D11纹理映射组
		D3D11TexturePtrMap			mTextureMap;
		/// D3D11纹理数组
		D3D11TexturePtr				mTextureArray[D3D11_MAX_TEXTURE_NUM];
		/// 采样器数组
		ID3D11SamplerStatePtr		mSamplerArray[D3D11_MAX_SAMPLER_NUM];

		/// D3D11设备
		ID3D11DevicePtr				mD3D11Device;
		ID3D11DeviceContextPtr		mD3D11Context;
		/// 当前索引缓冲区
		D3D11HardwareIndexBufferPtr		mCurrentIndexBuffer;
		/// 当前顶点缓冲区
		D3D11HardwareVertexBufferPtr	mCurrentVertexBuffer;

		ID3D11RasterizerStatePtr	mRasterizerState;
		ID3D11BlendStatePtr			mBlendState;
		ID3D11DepthStencilStatePtr	mDepthStencilState;
		/// 绑定的RenderTarget列表
		D3D11RenderTargetPtr		mRenderTargetList[D3D11_MAX_RENDER_TARGET_NUM];
		/// 绑定的RenderWindow列表
		D3D11RenderWindowPtr		mRenderWindowList[D3D11_MAX_RENDER_WINDOW_NUM];
		/// 当前绑定的HLSL渲染
		D3D11HLSLProgramPtr			mCurrentHLSLProgram;

		D3D11RenderState			mRenderState;
		D3D11RenderState			mSavedRenderState;

		/// D3D特性等级
		D3D_FEATURE_LEVEL			mD3DFeature;
		/// 图元类型
		D3D11_PRIMITIVE				mPrimitive;
		/// 输入顶点元素的描述数组大小
		u32							mInputLayoutCount;
		/// 是否等待垂直空白
		u32							mWaitForVerticalBlank;
		
		/// 表示渲染状态在一帧内是否改变过
		bool						mIsRasterizerStateChange;
		bool						mIsBlendStateChange;
		bool						mIsDepthStencilStateChange;
		bool						mIsVertexBufferChange;
		bool						mIsIndexBufferChange;
		bool						mIsHLSLProgramChange;

	public:
		/** 默认构造函数.
		*/
		D3D11RenderSystem(ID3D11DevicePtr d3dDevice, ID3D11DeviceContextPtr d3dContext,
			AdapterPtr& adapter);

		/** 析构函数
		*/
		~D3D11RenderSystem() override;

		/** 设定是否等待垂直空白(在下一帧到来时，当前帧未光栅化完成，
		* 下一动作是马上恢复光栅器[不等待垂直空白]，还是等待当前帧光栅化完成[等待垂直空白])
		* @note		对窗口化程序无影响，只对全屏程序造成影响
		* @param	enabled true为等待（质量优先），false为不等待（速度优先）
		*/
		void SetWaitForVerticalBlank(bool enabled) override;

		/** 返回是否等待垂直空白
		*/
		bool GetWaitForVerticalBlank(void) const override;

		/** 渲染函数
		*/
		void Render(void) override;

		/** 保存当前的渲染状态
		*/
		void SaveRenderState() override;

		/** 恢复上一个保存的渲染状态
		*/
		void ResetRenderState() override;

	#pragma region BlendState

		/** 设置颜色混合是否开启
		*/
		void SetBlendEnable(bool enabled) override;

		/** 返回颜色混合是否开启
		*/
		bool GetBlendEnable(void) const override;

		/** 设置场景颜色如何混合
		* @param src1 指定混合颜色src1来源(ZERO, ONE, from pixel render, from renderTarget)
		* @param src2 指定混合颜色src1来源(ZERO, ONE, from pixel render, from renderTarget)
		* @param op   指定混合操作
		*/
		void SetSceneColorBlending(DRE_BLEND_COLOR_FACTOR src1, DRE_BLEND_COLOR_FACTOR src2,
			DRE_BLEND_OPERATION op = DRE_BLEND_ADD_OPERATION) override;

		/** 设置场景颜色透明度如何混合
		* @param srcAlpha1 指定混合透明度src1来源(ZERO, ONE, from pixel render, from renderTarget)
		* @param srcAlpha2 指定混合透明度src1来源(ZERO, ONE, from pixel render, from renderTarget)
		* @param alphaOp   指定透明度混合操作
		*/
		void SetSceneAlphaBlending(DRE_BLEND_ALPHA_FACTOR srcAlpha1, DRE_BLEND_ALPHA_FACTOR srcAlpha2,
			DRE_BLEND_OPERATION alphaOp = DRE_BLEND_ADD_OPERATION) override;

		/** 指定可通过的alpha值范围
		* @param func 指定比较函数
		* @param value 指定透明度参考值
		*/
		void SetAlphaRejectSettings(DRE_COMPARISON_FUNC func, f32 value) override;

		/** 设置透明度覆盖是否可以使用
		* @param enabled true为开启
		*/
		void SetAlphaToCoverageEnable(bool enabled) override;

		/** 设定可通过的颜色
		* @param red 是否可以通过红色
		* @param green 是否可以通过绿色
		* @param blue 是否可以通过蓝色
		* @param alpha 是否可以通过透明度
		*/
		void SetColourBufferWriteEnabled(bool red, bool green, bool blue, bool alpha) override;

	#pragma endregion

	#pragma region ViewportState
		/** 设定渲染视口
		*/
		void SetViewport(const Viewport & vp) override;

		/** 取得当前渲染视口
		*/
		Viewport GetViewport(void) override;

	#pragma endregion

	#pragma region DepthStencilState

		/** 是否开启蒙版测试
		*/
		void SetStencilCheckEnabled(bool enabled) override;

		/** 设定前面蒙版测试参数
		* @param refValue 当前蒙板值
		* @param writemask 当前写入蒙版值掩码
		*/
		void SetStencilBufferParams(u8 refValue, u8 writeMask) override;

		/** 设定前面蒙版测试参数
		* @param func 蒙版测试函数
		* @param stencilFailOp 蒙版测试失败时的操作
		* @param depthFailOp 蒙版测试成功，深度测试失败时的操作
		* @param passOp 蒙版测试和深度测试都成功时的操作
		*/
		void SetStencilBufferFrontFaceOp( 
			DRE_COMPARISON_FUNC func, 
			DRE_STENCIL_OPEARTION stencilFailOp, 
			DRE_STENCIL_OPEARTION depthFailOp,
			DRE_STENCIL_OPEARTION passOp ) override;

		/** 设定背面蒙版测试参数
		* @param func 蒙版测试函数
		* @param stencilFailOp 蒙版测试失败时的操作
		* @param depthFailOp 蒙版测试成功，深度测试失败时的操作
		* @param passOp 蒙版测试和深度测试都成功时的操作
		*/
		void SetStencilBufferBackFaceOp(
			DRE_COMPARISON_FUNC func, 
			DRE_STENCIL_OPEARTION stencilFailOp, 
			DRE_STENCIL_OPEARTION depthFailOp,
			DRE_STENCIL_OPEARTION passOp ) override;

		/** 是否使用深度缓冲区
		@param enabled true为打开，false为关闭
		*/
		void SetZBufferEnabled(bool enabled) override;

		/** 返回当前是否使用深度缓冲区
		*/
		bool GetZBufferEnabled(void) const override;

		/** 设定深度缓冲参数
		* @param depthTest 是否进行深度缓冲测试，false则不比较直接写入像素
		* @param depthWrite 是否可写入深度缓冲（及是否使用深度缓冲）
		* @param depthFunction 深度测试比较函数.
		*/
		void SetDepthBufferParams(bool depthTest = true, bool depthWrite = true,
			DRE_COMPARISON_FUNC depthFunction = DRE_COMPARISON_LESSEQUAL) override;

		/** 设置深度测试是否开启
		*/
		void SetDepthBufferCheckEnabled(bool enabled) override;

		/** 设置深度缓冲是否可用
		*/
		void SetDepthBufferWriteEnabled(bool enabled) override;

		/** 设置深度测试函数
		*/
		void SetDepthBufferFunction(DRE_COMPARISON_FUNC func) override;

	#pragma endregion

	#pragma region RasterizerState
		/** 设置填充模式
		*/
		void SetFillMode(DRE_FILL_MODE fillMode) override;

		DRE_FILL_MODE GetFillMode(void) const override;
	
		/** 设置裁剪模式
		* @param mode 裁剪模式，一般为DRE_CULL_BACK背面消隐
		*/
		void SetCullingMode(DRE_CULL_MODE mode) override;

		DRE_CULL_MODE GetCullingMode(void) const override;
	
		/** 设置是否开启多重取样
		*/
		void SetMultisampleEnabled(bool enabled) override;

		bool GetMultisampleEnabled() const override;

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
		void SetDepthBias(f32 constantBias, f32 slopeScaleBias) override;

		/** 设置深度值偏移最大值
		* @param	maxDepthBias depth值的最大可能偏移值
		*
		* @remark	
		*			if(DepthBiasClamp > 0)
		*				Bias = min(DepthBiasClamp, Bias)
		*			else if(DepthBiasClamp < 0)
		*				Bias = max(DepthBiasClamp, Bias)
		*/
		void SetDepthBiasClamp(f32 maxDepthBias) override;

		/** 设置裁剪框测试是否开启
		* @param enabled True to enable the scissor test, false to disable it.
		*/
		void SetScissorTestEnable(bool enabled) override;

		/** 设置一个裁剪框
		* @note 要使裁剪框有效必须先设置setScissorTestEnable
		*/
		void SetScissorTest(u32 left, u32 top, u32 right, u32 bottom) override;

	#pragma endregion

	#pragma region InputState
	
	public:
		/** 设置顶点描述
		*/
		void SetVertexDeclaration(const VertexDeclaration& declaration) override;

		/** 设置图元类型
		*/
		void SetPolygonMode(DRE_PRIMITIVE_TOPOLOGY level) override;

		/** 
		设置顶点缓冲区
		*/
		void SetHardwareVertexBuffer(HardwareVertexBufferPtr& vertexBuffer) override;

		/** 设置索引缓冲区
		*/
		void SetHardwareIndexBuffer(HardwareIndexBufferPtr& indexBuffer) override;

		/** 设置HLSL渲染
		*/
		void SetHLSLShader(HLSLProgramPtr& hlslShader) override;

	#pragma endregion

	#pragma region OnlyDirectX9
		
		/** 设定当前渲染系统是否使用固定渲染管道
		*/
		void SetFixedPipelineEnabled(bool enabled) override;

		/** 返回当前渲染系统是否使用固定渲染管道
		*/
		bool GetFixedPipelineEnabled(void) const override;

		/** 设置环境光
		*/
		 void SetAmbientLight(f32 r, f32 g, f32 b) override;

		/** 设置光源渲染的渲染方法，对DX9有效，DX11固定为Gouraud着色
		*/
		 void SetShadingType(DRE_SHADER_OPTION shaderOption) override;

		/** 打开动态光源
		* @param enabled true为打开，false为关闭
		*/
		 void SetLightingEnabled(bool enabled) override;

		/** 设置渲染光源
		* @param lights 光源列表
		* @param limit 光源数量
		*/
		 void UseLights(const LightList& lights, unsigned short limit) override;
	
		/** 设置世界转换矩阵 */
		 void SetWorldMatrix(const Matrix4 &m) override;
		/** 设置相机转换矩阵 */
		 void SetViewMatrix(const Matrix4 &m) override;
		/** 设置投影转换矩阵 */
		 void SetProjectionMatrix(const Matrix4 &m) override;

		/** 设置渲染材质
		* @param ambient	环境光的反射系数
		* @param diffuse	漫射光的反射系数
		* @param specular	镜面光的反射系数
		* @param emissive	自发光光源颜色
		* @param shininess	反射高光系数
		* @param options	使用材质颜色中的那些，如不使用材质颜色则自动在顶点颜色中寻找对应颜色
		*/
		 void SetSurfaceParams(const Color& ambient,
			const Color& diffuse, const Color& specular,
			const Color& emissive, f32 shininess,
			u32 options) override;

		/** 是否开启粒子特效
		*/	
		 void SetPointSpritesEnabled(bool enabled) override;

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
		 void SetPointParameters(f32 size, bool attenuationEnabled, 
			f32 constant, f32 linear, f32 quadratic, f32 minSize, f32 maxSize) override;

		/** 设置雾化参数
		@param mode 雾化模式
		@param 雾的颜色
		@param expDensity	在DRE_FOG_EXP_MODE和DRE_FOG_EXP2_MODE中有效，具体请参考DRE_FOG_EXP_MODE
		@param linearStart	仅在DRE_FOG_LINEAR_MODE中有效，范围为[0.0, 1.0]（depth值的范围），使用Depth值为标准
		@param linearEnd	仅在DRE_FOG_LINEAR_MODE中有效，范围为[0.0, 1.0]（depth值的范围），使用Depth值为标准
		*/
		 void SetFog(DRE_FOG_MODE mode, const Color& color, f32 expDensity, f32 linearStart, f32 linearEnd) override;


		/** 设置是否自动正规化
		*/
		 void SetNormaliseNormals(bool normalise) override;


		/** 设置一系列裁剪面
		* @param clipPlanes 裁剪平面列表
		* @note 只对Dirext9有效
		*/
		// void setClipPlanes(const PlaneList& clipPlanes);

		/** 增加一个裁剪平面
		*/
		 void addClipPlane (const Plane &p) override;

		/** 重置所有裁剪平面
		*/
		 void resetClipPlanes() override;

	#pragma endregion

	#pragma region SamplerState

		/** 设置一个寄存器号为index的sampler
		* @param	index		分配的寄存器索引
		* @param	sampler		采样器
		*/
		void SetSampler(u32 index, const SamplerDesc& sampler) override;

		/** 设置一个语义为sematics的sampler
		* @param	index		hlsl语义
		* @param	sampler		采样器
		*/
		void SetSampler(const c8* sematics, const SamplerDesc& sampler) override;

	private:
		/** 通过SamplerDesc创建ID3D11Sampler
		*/
		ID3D11SamplerStatePtr CreateSampler(const SamplerDesc& sampler);

	public:
		/** 设置一个寄存器号为index的texture
		* @param	index		分配的寄存器索引
		* @param	texture		纹理
		*/
		void SetTexture(u32 texIndex, TexturePtr& texture) override;

		/** 设置一个语义为sematics的texture
		* @param	index		hlsl语义
		* @param	texture		纹理
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
		/** 创建一个RenderWindow
		* @param		width			窗口宽度
		* @param		height			窗口高度
		* @param		isFullScreen	是否全屏
		* @param		hasDepth		是否使用深度缓冲
		* @param		hasStencil		是否使用模板缓冲
		* @param		fsaa			采样次数
		* @param		fassQuality		采样质量
		*/
		RenderWindowPtr CreateRenderWindow(u32 width, u32 height, bool isFullScreen,
			bool hasDepth, bool hasStencil, u32 fsaa, u32 fassQuality) override;

		/** 创建一个RenderTarget
		* @param		/		width			渲染目标宽度
		* @param		/		height			渲染目标高度
		* @param	optional	hasDepth		是否使用深度缓冲
		* @param	optional	hasStencil		是否使用模板缓冲
		* @param	optional	fsaa			采样次数
		* @param	optional	fassQuality		采样质量
		*/
		RenderTargetPtr CreateRenderTarget(u32 width, u32 height, bool hasDepth = false,
			bool hasStencil = false, u32 fsaa = 1, u32 fassQuality = 0) override;

		/** 从图片中创建一个Texture
		* @param		/		image					创建纹理用的图片
		* @param		/		usage					纹理内存使用标志
		* @param	optional	isTransparentFigure		是否透明通道图
		* @param	optional	fsaa					采样次数
		* @param	optional	fassQuality				采样质量
		* @param	optional	gamma					gamma校正值
		*/
		TexturePtr CreateTextureFromImage(ImagePtr image, DRE_BUFFER_USAGE usage, bool isTransparentFigure = false,
			u32 fsaa = 1, u32 fsaaQuality = 0, f32 gamma = 1.0f) override;

		/** 从文件中创建一个Texture
		* @param		/		image					创建纹理用的图片
		* @param		/		usage					纹理内存使用标志
		* @param	optional	isTransparentFigure		是否透明通道图
		* @param	optional	fsaa					采样次数
		* @param	optional	fassQuality				采样质量
		* @param	optional	gamma					gamma校正值
		*/
		TexturePtr CreateTextureFromFile(const char* fileName, DRE_BUFFER_USAGE usage, bool isTransparentFigure = false,
			u32 fsaa = 1, u32 fsaaQuality = 0, f32 gamma = 1.0f) override;

		/** 从readBuffer中读取数据来生成HardwareVertexBuffer
		* @param		readBuffer			可读取缓冲区
		* @param		vertexSize			顶点大小
		*/
		HardwareVertexBufferPtr CreateHardwareVertexBuffer(ReadBufferPtr readBuffer, u32 vertexSize, u32 numVertices,
			DRE_PRIMITIVE_TOPOLOGY primitive,
			DRE_BUFFER_USAGE usage, bool hasInstanceData = false, u32 instanceDataStepRate = 0) override;

		/** CreateHardwareVertexBuffer的具体实现
		*/
		HardwareVertexBufferPtr CreateHardwareVertexBuffer(const u8Array data, u32 vertexSize, u32 numVertices,
			DRE_PRIMITIVE_TOPOLOGY primitive,
			DRE_BUFFER_USAGE usage, bool hasInstanceData = false, u32 instanceDataStepRate = 0);

		/** 从readBuffer中读取数据来生成HardwareIndexBuffer
		* @param		readBuffer			可读取缓冲区
		* @param		vertexSize			顶点大小
		*/
		HardwareIndexBufferPtr CreateHardwareIndexBuffer(ReadBufferPtr readBuffer,
			DRE_INDEX_ELEMENT_TYPE type, u32 numIndices, DRE_BUFFER_USAGE usage) override;

		/** CreateHardwareIndexBuffer的具体实现
		*/
		HardwareIndexBufferPtr CreateHardwareIndexBuffer(const u8Array data,
			DRE_INDEX_ELEMENT_TYPE type, u32 numIndices, DRE_BUFFER_USAGE usage);

		/** 从读取流中加载HLSLProgram
		*/
		HLSLProgramPtr CreateHLSLProgram(ReadBufferPtr readBuffer, const DRE_HLSLPROGRAM_DESC &desc) override;

		/** 从文件中加载HLSLProgram
		*/
		HLSLProgramPtr CreateHLSLProgram(const DRE_HLSLPROGRAM_DESC& desc) override;

	private:
		ID3D10BlobPtr CreateShaderFromFile(const c8* shaderFile, const c8* shaderName, 
			const c8* shaderVerson);
	
	#pragma endregion

	public:
		// 窗口运行程序
		static LRESULT CALLBACK WndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

	};	// end class D3D11RenderSystem

}	// end namespace dream

#endif	// end __DRED3D11RENDERSYSTEM_H__