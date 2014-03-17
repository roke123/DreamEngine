#include <DreRenderSystemFactory.h>
#include <DreRenderDeclaration.h>
#include <DrePixelFormat.h>
#include <DreAdapter.h>
#include <DreRenderSystem.h>
#include <DreRenderWindow.h>

#include <DreIOSystemDeclaration.h>
#include <DreMemoryReadBuffer.h>
#include <DreDataBufferFactory.h>
#include <DreHLSLProgram.h>
#include <DreHardwareVertexBuffer.h>
#include <DreViewport.h>
#include <DreImageLoader.h>
#include <DreTexture.h>
#include <DreSerializer.h>

#include <iostream>
#include <Windows.h>

#include <xnamath.h>

struct VertexPos
{
	XMFLOAT3 Pos;
	XMFLOAT2 Tex;
};

int main()
{
	using namespace dream;
	
	ImageLoader::StartUp();

	AdapterPtr adapter = RenderSystemFactory::GetD3D11RenderAdapter(1);
	for (int i = 2; adapter != nullptr; i++)
	{	
		std::cout << i - 1 << " " << adapter->DriverDescription().c_str() << std::endl;
		adapter = RenderSystemFactory::GetD3D11RenderAdapter(i);
	}
	
	int index = 0;
	std::cin >> index;

	RenderSystemPtr renderSystem = RenderSystemFactory::CreateD3D11RenderSystem(
		RenderSystemFactory::GetD3D11RenderAdapter(index));

	RenderWindowPtr renderWindow = renderSystem->CreateRenderWindow(800, 600, false, true, true, 1, 0);
	VertexPos vertices[] =
    {
        { XMFLOAT3( -1.0f,  1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3(  1.0f,  1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3(  1.0f,  1.0f,  1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f,  1.0f,  1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3(  1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3(  1.0f, -1.0f,  1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f, -1.0f,  1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f,  1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3( -1.0f,  1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f,  1.0f,  1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3(  1.0f, -1.0f,  1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3(  1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3(  1.0f,  1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3(  1.0f,  1.0f,  1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3(  1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3(  1.0f,  1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f,  1.0f, -1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

        { XMFLOAT3( -1.0f, -1.0f,  1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
        { XMFLOAT3(  1.0f, -1.0f,  1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
        { XMFLOAT3(  1.0f,  1.0f,  1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
        { XMFLOAT3( -1.0f,  1.0f,  1.0f ), XMFLOAT2( 0.0f, 1.0f ) },
    };
	renderSystem->BindRenderWindow(0, renderWindow);

	WORD indices[] =
    {
        3,   1,  0,  2,  1,  3,
        6,   4,  5,  7,  4,  6,
        11,  9,  8, 10,  9, 11,
        14, 12, 13, 15, 12, 14,
        19, 17, 16, 18, 17, 19,
        22, 20, 21, 23, 20, 22
    };
	u8Array iBuffer(sizeof(indices));
	memcpy(&iBuffer[0], &indices, sizeof(indices));
	ReadBufferPtr readBuf = DataBufferFactory::CreateMemoryReadBuffer(iBuffer, sizeof(indices));

	HardwareIndexBufferPtr indexBuffer = renderSystem->CreateHardwareIndexBuffer(readBuf,
		DRE_INDEX_ELEMENT_TYPE_U16, 36, DRE_BUFFER_USAGE_DEFAULT);
	renderSystem->SetHardwareIndexBuffer(indexBuffer);

	Viewport vp = {0.0f, 0.0f, 800.0f, 600.0f, 0.0f, 1.0f};
	renderSystem->SetViewport(vp);

	u8Array buffer(sizeof(vertices));
	memcpy(&buffer[0], &vertices, sizeof(vertices));
	readBuf = DataBufferFactory::CreateMemoryReadBuffer(buffer, sizeof(vertices));

	HardwareVertexBufferPtr vertexBuffer = renderSystem->CreateHardwareVertexBuffer(readBuf, sizeof(VertexPos), 24,
		DRE_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP, DRE_BUFFER_USAGE_DEFAULT);
	vertexBuffer->AddElement(MakeVertexElemnt(DRE_VERTEX_EMELENT_TYPE_FLOAT3,
		DRE_VERTEX_ELEMENT_POSITION, 0, sizeof(XMFLOAT3)));
	vertexBuffer->AddElement(std::move(MakeVertexElemnt(DRE_VERTEX_EMELENT_TYPE_FLOAT2,
		DRE_VERTEX_ELEMENT_TEXTURE_COORDINATES, 0, sizeof(XMFLOAT2))));
	renderSystem->SetHardwareVertexBuffer(vertexBuffer);

	DRE_HLSLPROGRAM_DESC hlslDesc = {0};
	hlslDesc.VS_EntryPoint = "main"; hlslDesc.VS_Verson = "vs_4_0"; hlslDesc.VS_File = "vs.hlsl";
	hlslDesc.PS_EntryPoint = "main"; hlslDesc.PS_Verson = "ps_4_0"; hlslDesc.PS_File = "ps.hlsl";
	HLSLProgramPtr hlsl = renderSystem->CreateHLSLProgram(hlslDesc);
	renderSystem->SetHLSLShader(hlsl);


	ImagePtr i = ImageLoader::GetInstance().Load("logo.png");
	ImageLoader::GetInstance().Save(i, "100.png");

	TexturePtr texure1 = renderSystem->CreateTextureFromFile("99.bmp", DRE_BUFFER_USAGE_DEFAULT);
	renderSystem->SetTexture("colorMap", texure1);

	Float::InvSqrt(0.0f);

	//ImageLoader::GetInstance().Save(texure1->ExportAsImage(), "100.bmp");

	TexturePtr texure2 = renderSystem->CreateTextureFromFile("decal2.dds", DRE_BUFFER_USAGE_DEFAULT);
	renderSystem->SetTexture("secondMap", texure2);

	SamplerDesc sampler = {
		DRE_FILTER_MIN_MAG_MIP_LINEAR,
		DRE_TEXTURE_ADDRESS_WRAP,
		DRE_TEXTURE_ADDRESS_WRAP,
		0.0f, 0, 0.0f, 0.0f
	};
	renderSystem->SetSampler("colorSampler", sampler);

	MSG msg = {0};
	while( msg.message != WM_QUIT )
    {
        if( PeekMessage( &msg, 0, 0, 0, PM_REMOVE ) )
        {
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        } else {
			renderSystem->Render();
			//e.Update(0);
		}
    }

	ImageLoader::ShutDown();
}
