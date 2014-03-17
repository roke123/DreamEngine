#ifndef __DREENUMS_H__
#define __DREENUMS_H__

namespace dream
{

	/// ��С�����Ŵ���������mip��������
	enum DRE_FILTER_OPTION
	{
		DRE_FILTER_MIN_MAG_MIP_POINT,               
		DRE_FILTER_MIN_MAG_POINT_MIP_LINEAR,        
		DRE_FILTER_MIN_POINT_MAG_LINEAR_MIP_POINT,  
		DRE_FILTER_MIN_POINT_MAG_MIP_LINEAR,        
		DRE_FILTER_MIN_LINEAR_MAG_MIP_POINT,        
		DRE_FILTER_MIN_LINEAR_MAG_POINT_MIP_LINEAR, 
		DRE_FILTER_MIN_MAG_LINEAR_MIP_POINT,        
		DRE_FILTER_MIN_MAG_MIP_LINEAR,     
		/// ��������ȡ��
		DRE_FILTER_ANISOTROPIC,                     
	};	// end enum DRE_FILTER_OPTION

	/// ��������Ѱַ��ʽ
	enum DRE_TEXTURE_ADDRESS_MODE 
	{
		DRE_TEXTURE_ADDRESS_WRAP          = 1,
		DRE_TEXTURE_ADDRESS_MIRROR        = 2,
		DRE_TEXTURE_ADDRESS_CLAMP         = 3,
		DRE_TEXTURE_ADDRESS_BORDER        = 4,
		DRE_TEXTURE_ADDRESS_MIRROR_ONCE   = 5                   
	};	// end enum DRE_TEXTURE_ADDRESS_MODE

	/// ��Ⱦ������ɫ��ʽ
	enum DRE_SHADER_OPTION
	{
		DRE_SHADER_FLAT,
		/// �������ɫ��DirectX11���õķ���
		DRE_SHADER_GOURAUD,
		/// Phong��ɫ�������Gouraud��ɫ���ӣ���Ч����ǰ�߱���
		DRE_SHADER_PHONG
	};	// end enum DRE_SHADER_OPTION

	/// �ȽϺ���ö��
	enum DRE_COMPARISON_FUNC : unsigned int 
	{
		/// �Ӳ��Ƚ�
		DRE_COMPARISON_NEVER,
		/// С�ڵ���ʱ�Ƚϳɹ�
		DRE_COMPARISON_LESSEQUAL,
		/// ����ʱ�Ƚϳɹ�
		DRE_COMPARISON_EQUAL,
		/// С��ʱ�Ƚϳɹ�
		DRE_COMPARISON_LESS,
		/// �����ʱ�Ƚϳɹ�
		DRE_COMPARISON_NOTEQUAL,
		/// ���ڵ���ʱ�Ƚϳɹ�
		DRE_COMPARISON_GREATEREQUAL,
		/// ����ʱ�Ƚϳɹ�
		DRE_COMPARISON_GREATER,
		/// ���ǳɹ�
		DRE_COMPARISON_ALWAYS
	};	// end enum DRE_COMPARISON_FUNC

	/// ��ɫ�������
	enum DRE_BLEND_COLOR_FACTOR : unsigned int
	{
		/// �ѻ����ɫ��Ϊ(0, 0, 0, 0)
		DRE_BLEND_ZERO_COLOR,		
		/// �ѻ����ɫ��Ϊ(1, 1, 1, 1)
		DRE_BLEND_ONE_COLOR,
		/// �ѻ����ɫ��ΪDest(from RenderTarget)
		DRE_BLEND_COLOR_FROM_RENDER_TARGET, 		
		/// �ѻ����ɫ��Ϊ1 - Dest(from RenderTarget)
		DRE_BLEND_INV_COLOR_FROM_RENDER_TARGET,
		/// �ѻ����ɫ��ΪSrc(from PixelOutput)
		DRE_BLEND_COLOR_FROM_PIXEL_SHADER,
		/// �ѻ����ɫ��Ϊ1 - Src(from PixelOutput)
		DRE_BLEND_INV_COLOR_FROM_PIXEL_SHADER, 
	};	// end enum DRE_BLEND_COLOR_FACTOR

	/// ͸���Ȼ������
	enum DRE_BLEND_ALPHA_FACTOR : unsigned int
	{
		/// �ѻ��͸������Ϊ0
		DRE_BLEND_ZERO_ALPHA,		
		/// �ѻ��͸������Ϊ1
		DRE_BLEND_ONE_ALPHA,
		/// �ѻ��͸������ΪSrc(form PixelOutput)
		DRE_BLEND_ALPHA_FROM_RENDER_TARGET,
		/// �ѻ��͸������ΪSrc(form PixelOutput)
		DRE_BLEND_INV_ALPHA_FROM_RENDER_TARGET,
		/// �ѻ��͸������ΪDest(form RenderTarget)
		DRE_BLEND_ALPHA_FROM_PIXEL_SHADER,
		/// �ѻ����ɫ��Ϊ1 - Dest(form RenderTarget)
		DRE_BLEND_INV_ALPHA_FROM_PIXEL_SHADER,
	};	// end enum DRE_BLEND_ALPHA_FACTOR

	enum DRE_BLEND_OPERATION : unsigned int
	{
		/// src1 + src2 
		DRE_BLEND_ADD_OPERATION,
		/// src2 - src1
		DRE_BLEND_SUBTRACT_OPERATION,
		/// src1 - src2
		DRE_BLEND_REVERSE_SUBTRACT_OPERATION,
		/// min(src1, src2)
		DRE_BLEND_MIN_OPERATION,
		/// max(src1, src2)
		DRE_BLEND_MAX_OPERATION,
	};	// end enum DRE_BLEND_OPERATION

	enum DRE_COLOR_CHANNEL
	{
		/// �հ�ͨ�����������κ���ɫͨ��
		DRE_COLOR_NONE_CHANNEL = 0,
		/// ��ɫͨ����ֻ�����ɫͨ��
		DRE_COLOR_RED_CHANNEL = 1,
		/// ��ɫͨ����ֻ������ɫͨ��
		DRE_COLOR_GREEN_CHANNEL = 2,
		/// ��ɫͨ����ֻ�����ɫͨ��
		DRE_COLOR_BLUE_CHANNEL = 4,
		/// ͸����ͨ����ֻ����͸����ͨ��
		DRE_COLOR_ALPHA_CHANNEL = 8,
		/// RGBͨ����ֻ����RGBͨ��
		DRE_COLOR_RGB_CHANNEL = 14,
		/// ȫ
		DRE_COLOR_ALL_CHANNEL = 15
	};	// end enum DRE_COLOR_CHANNEL

	enum DRE_CULL_MODE
	{
		/// ������
		DRE_CULL_NONE    = 1,
		/// ǰ������
		DRE_CULL_FRONT   = 2,
		/// ��������
		DRE_CULL_BACK    = 3 
	};	// end enum DRE_CULL_MODE

	/// �ɰ滺���������readMask��writeMask���ʹ��
	enum DRE_STENCIL_OPEARTION
	{
		/// ���浱ǰ��stencil value
		DRE_STENCIL_OPEARTION_KEEP       = 1,
		/// ʹstencil valueΪ0
		DRE_STENCIL_OPEARTION_ZERO       = 2,
		/// �õ�ǰ��stencil value�滻
		DRE_STENCIL_OPEARTION_REPLACE    = 3,
		DRE_STENCIL_OPEARTION_INCR_SAT   = 4,
		DRE_STENCIL_OPEARTION_DECR_SAT   = 5,
		DRE_STENCIL_OPEARTION_INVERT     = 6,
		DRE_STENCIL_OPEARTION_INCR       = 7,
		DRE_STENCIL_OPEARTION_DECR       = 8 
	};	// end enum DRE_STENCIL_OPERATION

	enum DRE_PRIMITIVE_TOPOLOGY 
	{
		DRE_PRIMITIVE_TOPOLOGY_UNDEFINED                    = 0,
		/// ͼ����������Ϊ���б�ֻ����
		DRE_PRIMITIVE_TOPOLOGY_POINTLIST                    = 1,
		/// ͼ����������Ϊ���б�ÿ����֮����һ����
		DRE_PRIMITIVE_TOPOLOGY_LINELIST                     = 2,
		/// ͼ����������Ϊ���������֮����һ���ߣ���һ���ߵ��յ�����һ���ߵ����
		DRE_PRIMITIVE_TOPOLOGY_LINESTRIP                    = 3,
		/// ͼ����������Ϊ�������б�ÿ����֮������һ��������
		DRE_PRIMITIVE_TOPOLOGY_TRIANGLELIST                 = 4,
		/// ͼ����������Ϊ�����δ�������֮������һ�������Σ���һ�����ε��յ�����һ�����ε����
		DRE_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP                = 5,
		/// ���²���ֻ��D3D11���ṩ�����ݲ�֧��
		/*DRE_PRIMITIVE_TOPOLOGY_LINELIST_ADJ                 = 10,
		DRE_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ                = 11,
		DRE_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ             = 12,
		DRE_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ            = 13,*/
	};

	/// ����������ڴ�ռ䱻���ʹ��
	enum DRE_BUFFER_USAGE
	{
		/// Ĭ��GPU�ڴ�ռ䣬CPU���ɶ�д
		DRE_BUFFER_USAGE_DEFAULT = 0,
		/// ��̬�ڴ�ռ䣬���ڴ��GPU���Ƶ�CPU�ڴ�ռ�����ݣ��ɶ�д
		DRE_BUFFER_USAGE_STATIC = 1,
		/// ��̬�ڴ�ռ䣬���ڴ��GPU��Ⱦ�ܵ�ʹ�õ����ݣ��ɶ�д
		DRE_BUFFER_USAGE_DYNAMIC = 2,
		/// ֻ����־
		DRE_BUFFER_USAGE_WRITEONLY = 4,
		/// �ɶ�����־��lock����ԴʧЧ����GPU��Ⱦ�ܵ����ɼ���ʹ�ã�������ֻʹ��һ�ε���Դ
		DRE_BUFFER_USAGE_DISCARDABLE = 8,
		/// ֻ���ľ�̬�ڴ�ռ�
		DRE_BUFFER_USAGE_STATIC_WRITE_ONLY = 5,
		/// ��̬�ڴ�ռ䣬������CPU�ڴ�ռ��޿ɶ�������
		/// DRE_BUFFER_USAGE_STATIC_WRITE_ONLY_DISCARDABLE = 13
		/// ֻ���Ķ�̬�ڴ�ռ�
		DRE_BUFFER_USAGE_DYNAMIC_WRITE_ONLY = 6,
		/// �ɶ�����ֻ���Ķ�̬�ڴ�ռ�
		DRE_BUFFER_USAGE_DYNAMIC_WRITE_ONLY_DISCARDABLE = 14
	};

	/// �����ڴ�ռ��ѡ��粻��ʹ�����׳��쳣
	enum DRE_LOCK_OPTIONS
	{
		/// ��д����
		DRE_LOCK_READWRITE,
		/// ��д������������������Դ
		DRE_LOCK_DISCARD,
		/// ֻ������
		HDRE_LOCK_READ_ONLY,
		/// ֻд����
		DRE_LOCK_WRITE_ONLY,
		/// ��ʾ�ò�����Դ�ڵ�ǰ֡��Ⱦ(IAʹ�����ú�)�ڲ��ᱻ��д
		DRE_LOCK_NO_OVERWRITE,			
	};

	/// ��ģʽ��dest = src * fog + fogColor * (1 - fog)
	enum DRE_FOG_MODE
	{
		/// ��������
		DRE_FOG_NONE_MODE,
		/// �������� fog = (end - d) / (end - start)
		DRE_FOG_LINEAR_MODE,
		/// Exp���� fog = 1 / e^(d * density)
		DRE_FOG_EXP_MODE,
		/// Exp2���� fog = 1 / e^((d * density)^2)
		DRE_FOG_EXP2_MODE,
	};	// enum enum DRE_FOG_MODE

	/// ���ģʽ
	enum DRE_FILL_MODE
	{
		/// ����䣬ֻ����ÿ����
		DRE_FILL_POINT_MODE         = 1,
		/// �߿���䣬ֻ����ÿ����
		DRE_FILL_WIREFRAME_MODE     = 2,
		/// ʵ����䣬����ÿ������
		DRE_FILL_SOLID_MODE         = 3,
	};	// end enum DRE_FILL_MODE

	   /// ����Ԫ������
	enum DRE_VERTEX_EMELENT_SEMANTICS {
		/// λ�����ݣ�3 float per vertex
		DRE_VERTEX_ELEMENT_POSITION = 0,
		/// ��ϱ���
		DRE_VERTEX_ELEMENT_BLEND_WEIGHTS = 1,
        /// �������
        DRE_VERTEX_ELEMENT_BLEND_INDICES = 2,
		/// ��������, 3 float per vertex
		DRE_VERTEX_ELEMENT_NORMAL = 3,
		/// ��������ɫ
		DRE_VERTEX_ELEMENT_DIFFUSE = 4,
		/// ���淴����ɫ
		DRE_VERTEX_ELEMENT_SPECULAR = 5,
		/// ��������
		DRE_VERTEX_ELEMENT_TEXTURE_COORDINATES = 6,
        /// ����������
        DRE_VERTEX_ELEMENT_BINORMAL = 7,
        /// ��������
        DRE_VERTEX_ELEMENT_TANGENT = 8,
		/// �Զ�������
		DRE_VERTEX_ELEMENT_CUSTOM = 9,
	};

    /// ����Ԫ������
    enum DRE_VERTEX_ELEMENT_TYPE
    {
        DRE_VERTEX_EMELENT_TYPE_FLOAT1 = 0,
        DRE_VERTEX_EMELENT_TYPE_FLOAT2 = 1,
        DRE_VERTEX_EMELENT_TYPE_FLOAT3 = 2,
        DRE_VERTEX_EMELENT_TYPE_FLOAT4 = 3,
		DRE_VERTEX_EMELENT_TYPE_SHORT1 = 4,
		DRE_VERTEX_EMELENT_TYPE_SHORT2 = 5,
		DRE_VERTEX_EMELENT_TYPE_SHORT3 = 6,
		DRE_VERTEX_EMELENT_TYPE_SHORT4 = 7,
        DRE_VERTEX_EMELENT_TYPE_UBYTE4 = 8,
        /// D3D style compact colour
        DRE_VERTEX_EMELENT_TYPE_COLOUR_ARGB = 9,
        /// GL style compact colour
        DRE_VERTEX_EMELENT_TYPE_COLOUR_ABGR = 10
    };

	/// ����Ԫ������
	enum DRE_INDEX_ELEMENT_TYPE
	{
		/// 16λ����
		DRE_INDEX_ELEMENT_TYPE_U16 = sizeof(u16),
		/// 32λ����
		DRE_INDEX_ELEMENT_TYPE_U32 = sizeof(u32),
	};

	enum DRE_MATERIAL_COLOR_OPTIONS
	{
		/// ��ʹ���κβ�����ɫ
        DRE_MATERIAL_COLOR_NONE			= 0x0,
		/// ��ambient�������ⷴ��ϵ����ʹ�ò�����ɫ
        DRE_MATERIAL_COLOR_AMBIENT		= 0x1,     
		/// ��duffuse������ⷴ��ϵ����ʹ�ò�����ɫ
        DRE_MATERIAL_COLOR_DIFFUSE		= 0x2,
		/// ��specular������ⷴ��ϵ����ʹ�ò�����ɫ
        DRE_MATERIAL_COLOR_SPECULAR		= 0x4,
		/// ��emissive���Է��⣩ʹ�ò�����ɫ
        DRE_MATERIAL_COLOR_EMISSIVE		= 0x8,
		/// use all
		DRE_MATERIAL_COLOR_ALL			= DRE_MATERIAL_COLOR_AMBIENT | DRE_MATERIAL_COLOR_DIFFUSE | 
										  DRE_MATERIAL_COLOR_SPECULAR | DRE_MATERIAL_COLOR_EMISSIVE,
    };

//------------------------------------------------- ��Ⱦ���� --------------------------------------------------//

	enum DRE_CAPABILITIES_CATEGORY
	{
		DRE_CAPABILITIES_CATEGORY_COMMON	= 0,
		DRE_CAPABILITIES_CATEGORY_COMMON_2	= 1,
		DRE_CAPABILITIES_CATEGORY_D3D		= 2,
		DRE_CAPABILITIES_CATEGORY_GL		= 3,
		DRE_CAPABILITIES_CATEGORY_COUNT		= 4,
	};

	#define CAPS_BITSHIFT (32 - DRE_CAPABILITIES_CATEGORY_COUNT)
	#define CAPS_CATEGORY_MASK (((1 << DRE_CAPABILITIES_CATEGORY_COUNT) - 1) << CAPS_BITSHIFT)
	#define CAPS_SET_VALUE(cat, val) ((cat << CAPS_BITSHIFT) | (1 << val))

	enum DRE_CAPABILITIES_FEATURE
	{
		/// ֧��Ӳ������map
		DRE_CAPABILITIES_AUTOMIPMAP              = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 0),
		DRE_CAPABILITIES_BLENDING                = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 1),
		/// ֧�ָ������Թ���
		DRE_CAPABILITIES_ANISOTROPY              = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 2),
		/// ֧��DOT3������
		DRE_CAPABILITIES_DOT3                    = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 3),
		/// ֧��CubeMapping
		DRE_CAPABILITIES_CUBEMAPPING             = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 4),
		/// ֧��StencilBuffer
		DRE_CAPABILITIES_HWSTENCIL               = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 5),
		/// ֧�ֶ������������
		DRE_CAPABILITIES_VERTEXANDINDEXBUFFER	= CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 7),
		/// ֧�ֶ�����Ⱦ
		DRE_CAPABILITIES_VERTEX_PROGRAM          = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 9),
		/// ֧��������Ⱦ
		DRE_CAPABILITIES_FRAGMENT_PROGRAM        = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 10),
		/// ֧���ӿڵĲü�����(͸�ӱ任����ü�)
		DRE_CAPABILITIES_SCISSOR_TEST            = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 11),
		/// ֧��˫��ģ��
		DRE_CAPABILITIES_TWO_SIDED_STENCIL       = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 12),
		/// ֧���޶�ģ��ֵ��Χ
		DRE_CAPABILITIES_STENCIL_WRAP            = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 13),
		/// Supports hardware occlusion queries
		DRE_CAPABILITIES_HWOCCLUSION             = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 14),
		/// ֧���Զ���ü���
		DRE_CAPABILITIES_USER_CLIP_PLANES        = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 15),
		/// ����ṹ�Ƿ�֧��4byte������
		DRE_CAPABILITIES_VERTEX_FORMAT_UBYTE4    = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 16),
		/// ֧������Զƽ���ͶӰ
		DRE_CAPABILITIES_INFINITE_FAR_PLANE      = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 17),
		/// ֧��textureΪ��ȾĿ��
		DRE_CAPABILITIES_HWRENDER_TO_TEXTURE     = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 18),
		/// ֧��float����(0.0 - 1.0)��texture
		DRE_CAPABILITIES_TEXTURE_FLOAT           = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 19),
		/// ֧�ֳ����2�ı�����texture
		DRE_CAPABILITIES_NON_POWER_OF_2_TEXTURES = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 20),
		/// ֧��3Dtexture
		DRE_CAPABILITIES_TEXTURE_3D              = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 21),
		/// ֧�ֵ�sprites(����)��Ⱦ
		DRE_CAPABILITIES_POINT_SPRITES           = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 22),
		/// ֧�ֵ���չ���� (minsize, maxsize, attenuation)
		DRE_CAPABILITIES_POINT_EXTENDED_PARAMETERS = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 23),
		/// ֧�ֶ�������ץȡ
		DRE_CAPABILITIES_VERTEX_TEXTURE_FETCH = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 24),
		/// ֧��mipmap levelƫ��
		DRE_CAPABILITIES_MIPMAP_LOD_BIAS = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 25),
		/// ֧��geometry��Ⱦ
		DRE_CAPABILITIES_GEOMETRY_PROGRAM = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 26),
		/// ֧����Ⱦ�����㻺��
		DRE_CAPABILITIES_HWRENDER_TO_VERTEX_BUFFER = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON, 27),

		/// ֧������ѹ��
		DRE_CAPABILITIES_TEXTURE_COMPRESSION = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON_2, 0),
		/// ֧��DXT/ST3C��ʽ������ѹ��
		DRE_CAPABILITIES_TEXTURE_COMPRESSION_DXT = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON_2, 1),
		/// ֧��VTC��ʽ��ѹ������
		DRE_CAPABILITIES_TEXTURE_COMPRESSION_VTC = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON_2, 2),
		/// ֧��PVRTC��ʽ��ѹ������
		DRE_CAPABILITIES_TEXTURE_COMPRESSION_PVRTC = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON_2, 3),
		/// ֧�̶ֹ���Ⱦ�ܵ�
		DRE_CAPABILITIES_FIXED_FUNCTION = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON_2, 4),
		/// ֧�ֶ����ȾĿ��ʹ�ò�ͬ����Ȼ���
		DRE_CAPABILITIES_MRT_DIFFERENT_BIT_DEPTHS = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON_2, 5),
		/// ֧��͸����ͨ��
		DRE_CAPABILITIES_ALPHA_TO_COVERAGE = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON_2, 6),
		/// ֧�ֶ��ֻ�Ϸ���
		DRE_CAPABILITIES_ADVANCED_BLEND_OPERATIONS = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON_2, 7),
		/// ֧����ȾĿ�����Ȼ������
		DRE_CAPABILITIES_RTT_SEPARATE_DEPTHBUFFER = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON_2, 8),
		/// ֧��ʹ������Ȼ���
		DRE_CAPABILITIES_RTT_MAIN_DEPTHBUFFER_ATTACHABLE = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON_2, 9),
		/// ֧����Ȼ���С����ȾĿ��
		DRE_CAPABILITIES_RTT_DEPTHBUFFER_RESOLUTION_LESSEQUAL = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON_2, 10),
		/// ֧��ʵ�����ݵĶ��㻺��
		DRE_CAPABILITIES_VERTEX_BUFFER_INSTANCE_DATA = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON_2, 11),
		/// ֧�ֱ���shader����
		DRE_CAPABILITIES_CAN_GET_COMPILED_SHADER_BUFFER = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_COMMON_2, 12),

		// ***** DirectX specific caps *****
		/// Is DirectX feature "per stage constants" supported
		DRE_CAPABILITIES_PERSTAGECONSTANT = CAPS_SET_VALUE(DRE_CAPABILITIES_CATEGORY_D3D, 0),
	};

};	// end namespace dream

#endif	// end __DREENUMS_H__