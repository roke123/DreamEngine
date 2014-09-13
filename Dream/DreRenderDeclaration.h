#ifndef __DRERENDERDECLARATION_H__
#define __DRERENDERDECLARATION_H__

#include "DreContainer.h"
#include "DreTypes.h"
#include "DreComplieConfig.h"
#include "DreException.h"

#include "DreIOSystemDeclaration.h"
#include "DreMathDeclaration.h"

#include "DreRenderSystemConfig.h"
#include "DreRenderSystemEnums.h"
#include "DrePixelFormat.h"

namespace dream
{
	class Adapter;
	typedef shared_ptr<Adapter>							AdapterPtr;
	typedef list<AdapterPtr>							AdapterList;

	struct Viewport;

	class Color;

	class Light;
	typedef shared_ptr<Light>							LightPtr;

	class Texture;
	typedef shared_ptr<Texture>							TexturePtr;

	class RenderTarget;
	typedef shared_ptr<RenderTarget>					RenderTargetPtr;

	struct DRE_SHADER_DESC;

	class RenderSystem;
	typedef shared_ptr<RenderSystem>					RenderSystemPtr;

	class HardwareVertexBuffer;
	typedef shared_ptr<HardwareVertexBuffer>			HardwareVertexBufferPtr;

	class HardwareIndexBuffer;
	typedef shared_ptr<HardwareIndexBuffer>				HardwareIndexBufferPtr;

	struct VertexElement;
	typedef list<VertexElement>							VertexDeclaration;
	typedef VertexDeclaration::iterator					VertexElementIterator;
	typedef VertexDeclaration::const_iterator			VertexElementConstIterator;

	struct SamplerDesc;
	typedef map<string, SamplerDesc>					SamplerDescMap;

	class RenderWindow;
	typedef shared_ptr<RenderWindow>					RenderWindowPtr;

	class RenderParam;
	typedef shared_ptr<RenderParam>						RenderParamPtr;

	class Material;
	typedef shared_ptr<Material>						MaterialPtr;

	class Technique;
	typedef shared_ptr<Technique>						TechniquePtr;

	class Shader;
	typedef shared_ptr<Shader>							ShaderPtr;

	class Sampler;
	typedef shared_ptr<Sampler>							SamplerPtr;

	class Image;
	typedef shared_ptr<Image>							ImagePtr;

	class Light;
	typedef shared_ptr<Light>							LightPtr;
	typedef list<LightPtr>								LightList;

	class Renderable;
	typedef shared_ptr<Renderable>						RenderablePtr;
	typedef vector<RenderablePtr>						RenderableList;

	class Pass;
	typedef shared_ptr<Pass>							PassPtr;

	class RenderSystemCapabilities;

	typedef	map<string, RenderParamPtr>					RenderParamPtrMap;

	typedef set<string>									ShaderProfileSet;

}	// end namespace dream

#endif	// end __DRERENDERDECLARATION_H__