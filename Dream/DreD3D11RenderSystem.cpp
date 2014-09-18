#include "DreD3D11RenderSystem.h"

#include "DreD3D11Adapter.h"
#include "DreD3D11HardwareVertexBuffer.h"
#include "DreD3D11HardwareIndexBuffer.h"
#include "DreD3D11RenderMapping.h"
#include "DreD3D11RenderWindow.h"
#include "DreD3D11RenderTarget.h"
#include "DreD3D11Texture.h"
#include "DreViewport.h"
#include "DreD3D11Sampler.h"
#include "DreD3D11Material.h"
#include "DreD3D11Shader.h"
#include "DreRenderParam.h"

#include "DreImage.h"
#include "DreImageLoader.h"
#include "DreReadBuffer.h"
#include "DreMemoryReadBuffer.h"
#include "DreDataBufferFactory.h"
#include "DreRenderable.h"
#include "DrePass.h"
#include "DreLight.h"

#include "DreSceneManager.h"

#include <boost/smart_ptr.hpp>

namespace dream
{

	D3D11RenderSystem::D3D11RenderSystem(ID3D11DevicePtr d3dDevice, 
		ID3D11DeviceContextPtr d3dContext, AdapterPtr& adapter) : 
	//------------------------------------------------------------------------------
	RenderSystem(adapter),
		mD3D11Device(d3dDevice), mD3D11Context(d3dContext),
		mIsRasterizerStateChange(false), mIsBlendStateChange(false), mIsDepthStencilStateChange(false),
		mIsVertexBufferChange(false), mIsIndexBufferChange(false), mIsMaterialChange(false),
		mPrimitive(D3D11_PRIMITIVE_TRIANGLE), 
		mInputLayout(nullptr)
	{

		// ��ʼ��D3D11RenderSystem
		u32 i = 0;
		for(; i < D3D11_MAX_RENDER_TARGET_NUM; ++ i)
		{
			mRenderTargetList[i] = nullptr;
		}

		for(; i < D3D11_MAX_RENDER_WINDOW_NUM; ++ i)
		{
			mRenderWindowList[i] = nullptr;
		}
		memset(&mRenderState.mBlendColor, 0, sizeof(&mRenderState.mBlendColor));

		mD3DFeature = mD3D11Device->GetFeatureLevel();

		// ������Ⱦϵͳ����
		if(mD3DFeature >= D3D_FEATURE_LEVEL_9_1)
		{
			mCapabilities.AddShaderProfiles("vs_2_0");
			mCapabilities.AddShaderProfiles("ps_2_0");
		}
		if(mD3DFeature >= D3D_FEATURE_LEVEL_9_3)
		{
			mCapabilities.AddShaderProfiles("vs_2_a");
			mCapabilities.AddShaderProfiles("ps_2_x");
		}
		if(mD3DFeature >= D3D_FEATURE_LEVEL_10_0)
		{
			mCapabilities.AddShaderProfiles("vs_4_0");
			mCapabilities.AddShaderProfiles("ps_4_0");
		}
		if(mD3DFeature >= D3D_FEATURE_LEVEL_11_0)
		{
			mCapabilities.AddShaderProfiles("vs_5_0");
			mCapabilities.AddShaderProfiles("ps_5_0");
		}

		D3D11_FEATURE_DATA_FORMAT_SUPPORT feature;
		feature.InFormat = D3D11_RENDER_TARGET_FORMAT;
		mD3D11Device->CheckFeatureSupport(D3D11_FEATURE_FORMAT_SUPPORT, &feature, sizeof(D3D11_FEATURE_DATA_FORMAT_SUPPORT));
		if(feature.OutFormatSupport & D3D11_FORMAT_SUPPORT_MIP_AUTOGEN) { 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_AUTOMIPMAP); }
		if(feature.OutFormatSupport & D3D11_FORMAT_SUPPORT_BLENDABLE) { 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_BLENDING); }
		if(feature.OutFormatSupport & D3D11_FORMAT_SUPPORT_MIP){ 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_ANISOTROPY); }
		/*{ mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_DOT3); }*/
		if(feature.OutFormatSupport & D3D11_FORMAT_SUPPORT_TEXTURECUBE){ 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_CUBEMAPPING); }
		if(feature.OutFormatSupport & D3D11_FORMAT_SUPPORT_DEPTH_STENCIL){ 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_HWSTENCIL); }
		if(	feature.OutFormatSupport & D3D11_FORMAT_SUPPORT_IA_VERTEX_BUFFER &&
			feature.OutFormatSupport & D3D11_FORMAT_SUPPORT_IA_INDEX_BUFFER )
		{ 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_VERTEXANDINDEXBUFFER); }
		if(feature.OutFormatSupport & D3D11_FORMAT_SUPPORT_SHADER_LOAD ){ 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_VERTEX_PROGRAM); }
		if(feature.OutFormatSupport & D3D11_FORMAT_SUPPORT_SHADER_LOAD ){ 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_FRAGMENT_PROGRAM); }
		if(feature.OutFormatSupport & D3D11_FORMAT_SUPPORT_RENDER_TARGET){ 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_SCISSOR_TEST); }
		if(feature.OutFormatSupport & D3D11_FORMAT_SUPPORT_DEPTH_STENCIL){ 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_TWO_SIDED_STENCIL); }
		if(feature.OutFormatSupport & D3D11_FORMAT_SUPPORT_DEPTH_STENCIL){ 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_STENCIL_WRAP); }
		/*{ mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_HWOCCLUSION); }*/
		/*{ mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_USER_CLIP_PLANES); }*/
		if(feature.OutFormatSupport & D3D11_FORMAT_SUPPORT_SHADER_LOAD ){ 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_VERTEX_FORMAT_UBYTE4); }
		if(feature.OutFormatSupport & D3D11_FORMAT_SUPPORT_SHADER_LOAD ){ 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_INFINITE_FAR_PLANE); }
		if(feature.OutFormatSupport & D3D11_FORMAT_SUPPORT_RENDER_TARGET ){ 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_HWRENDER_TO_TEXTURE); }
		if(feature.OutFormatSupport & D3D11_FORMAT_SUPPORT_TEXTURE2D ){ 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_TEXTURE_FLOAT); }
		if(feature.OutFormatSupport & D3D11_FORMAT_SUPPORT_TEXTURE2D ){ 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_NON_POWER_OF_2_TEXTURES); }
		if(feature.OutFormatSupport & D3D11_FORMAT_SUPPORT_TEXTURE3D ){ 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_TEXTURE_3D); }
		/*{ mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_POINT_SPRITES); }*/
		/*{ mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_POINT_EXTENDED_PARAMETERS); }*/
		if(feature.OutFormatSupport & D3D11_FORMAT_SUPPORT_SHADER_LOAD ){ 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_VERTEX_TEXTURE_FETCH); }
		if(feature.OutFormatSupport & D3D11_FORMAT_SUPPORT_MIP ){ 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_MIPMAP_LOD_BIAS); }
		if(feature.OutFormatSupport & D3D11_FORMAT_SUPPORT_SHADER_LOAD ){ 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_GEOMETRY_PROGRAM); }
		if(feature.OutFormatSupport & D3D11_FORMAT_SUPPORT_SO_BUFFER ){ 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_HWRENDER_TO_VERTEX_BUFFER); }
		/* Ĭ��֧�� */ { 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_TEXTURE_COMPRESSION); }
		/* Ĭ��֧�� */ { 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_TEXTURE_COMPRESSION_DXT); }
		/*{ mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_TEXTURE_COMPRESSION_VTC); }*/
		/*{ mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_TEXTURE_COMPRESSION_PVRTC); }*/
		/*{ mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_FIXED_FUNCTION); }*/
		/*{ mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_MRT_DIFFERENT_BIT_DEPTHS); }*/
		if(mD3DFeature >= D3D_FEATURE_LEVEL_10_0 ){ 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_ALPHA_TO_COVERAGE); }
		if(feature.OutFormatSupport & D3D10_FORMAT_SUPPORT_BLENDABLE ){ 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_ADVANCED_BLEND_OPERATIONS); }
		/* Ĭ��֧�� */ { 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_RTT_SEPARATE_DEPTHBUFFER); }
		/* Ĭ��֧�� */ { 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_RTT_MAIN_DEPTHBUFFER_ATTACHABLE); }
		/*{ mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_RTT_DEPTHBUFFER_RESOLUTION_LESSFloat::IsEqual); }*/
		if(feature.OutFormatSupport & D3D11_FORMAT_SUPPORT_IA_VERTEX_BUFFER ){ 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_VERTEX_BUFFER_INSTANCE_DATA); }
		if(feature.OutFormatSupport & D3D11_FORMAT_SUPPORT_SHADER_LOAD ){ 
			mCapabilities.AddSupportedCapabilitie(DRE_CAPABILITIES_CAN_GET_COMPILED_SHADER_BUFFER); }


	}

	D3D11RenderSystem::~D3D11RenderSystem()
	{
		// ����
	}

	void D3D11RenderSystem::SetWaitForVerticalBlank(bool enable)
	{
		mWaitForVerticalBlank = (u32)enable;
	}

	bool D3D11RenderSystem::GetWaitForVerticalBlank(void) const
	{
		return mWaitForVerticalBlank == 0;
	}

	typedef std::pair<f32, LightPtr>																LightAndDistance;
	struct LightAndDistanceLess
	{
		bool operator () (const LightAndDistance& lh, const LightAndDistance& rh)
		{
			return lh.first < rh.first;
		}
	};
	typedef priority_queue<LightAndDistance, vector<LightAndDistance>, LightAndDistanceLess>		VertexLightList;

	void D3D11RenderSystem::_SetPass(PassPtr& pass)
	{

	}

	void D3D11RenderSystem::_FillRenderParameters(SceneManager* sceneMgr, RenderablePtr rend, PassPtr pass, LightList& manualLights)
	{
		// Issue view / projection changes if any
		//useRenderableViewProjMode(rend, passTransformState);

		// mark per-object params as dirty
		//mGpuParamsDirty |= (uint16)GPV_PER_OBJECT;

		this->SetCullingMode(pass->GetCullingMode());
		// �����ǰʹ��pass�����˹���
		if (pass->GetLightingEnabled())
		{

			if (pass->GetLightingMode() == DRE_LIGHTING_FORWARD_ADD)
			{
				// ʹ��ǰ�򸽼ӹ��գ��������ķ����Դ��Forward Base��Ⱦ

				f32 dis = Float::PositiveInfinity;		
				
				LightPtr		brightestDirLightIte = nullptr;
				LightList		importantLightList;
				VertexLightList vertexLightList;
				LightList		lastLightList;

				f32 maxIntensity = 0.0f;
				LightList::iterator ite = manualLights.begin();
				for (; ite != manualLights.end(); ++ite)
				{
					if ((*ite)->GetLightType() == E_LIGHTDIRECTIONAL)
					{
						if (maxIntensity < (*ite)->GetIntensity())
						{
							// �ҵ������ķ����Դ
							brightestDirLightIte = *ite;
						}
						else if ((*ite)->GetLightImportance() == DRE_LIGHT_IMPORTANT) 
						{
							// �ҵ����� important �Ĺ�Դ
							importantLightList.push_back(*ite);
						}
						else if (vertexLightList.size() < MAX_VERTEX_LIGHTING_COUNT) 
						{
							f32 distance = ((*ite)->GetPosition() - rend->GetPosition()).GetLengthPow2();
							vertexLightList.push(make_pair<f32, LightPtr>(std::move(distance), std::move(*ite)));
						}
						else
						{
							f32 distance = ((*ite)->GetPosition() - rend->GetPosition()).GetLengthPow2();
							// ѹ��һ����Դ
							vertexLightList.push(make_pair<f32, LightPtr>(std::move(distance), std::move(*ite)));
							
							LightPtr temp = vertexLightList.top().second;
							vertexLightList.pop();
							lastLightList.push_back(temp);
						}
					}
				}
			}
			else if (pass->GetLightingMode() == DRE_LIGHTING_FORWARD_ADD)
			{
			}

		}
			if (doLightIteration)
			{
				// Create local light list for faster light iteration setup
				static LightList localLightList;


				// Here's where we issue the rendering operation to the render system
				// Note that we may do this once per light, therefore it's in a loop
				// and the light parameters are updated once per traversal through the
				// loop
				const LightList& rendLightList = rend->getLights();

				bool iteratePerLight = pass->getIteratePerLight();

				// deliberately unsigned in case start light exceeds number of lights
				// in which case this pass would be skipped
				int lightsLeft = 1;
				if (iteratePerLight)
				{
					lightsLeft = static_cast<int>(rendLightList.size()) - pass->getStartLight();
					// Don't allow total light count for all iterations to exceed max per pass
					if (lightsLeft > static_cast<int>(pass->getMaxSimultaneousLights()))
					{
						lightsLeft = static_cast<int>(pass->getMaxSimultaneousLights());
					}
				}


				const LightList* pLightListToUse;
				// Start counting from the start light
				size_t lightIndex = pass->getStartLight();
				size_t depthInc = 0;

				while (lightsLeft > 0)
				{
					// Determine light list to use
					if (iteratePerLight)
					{
						// Starting shadow texture index.
						size_t shadowTexIndex = mShadowTextures.size();
						if (mShadowTextureIndexLightList.size() > lightIndex)
							shadowTexIndex = mShadowTextureIndexLightList[lightIndex];

						localLightList.resize(pass->getLightCountPerIteration());

						LightList::iterator destit = localLightList.begin();
						unsigned short numShadowTextureLights = 0;
						for (; destit != localLightList.end()
							&& lightIndex < rendLightList.size();
							++lightIndex, --lightsLeft)
						{
							Light* currLight = rendLightList[lightIndex];

							// Check whether we need to filter this one out
							if ((pass->getRunOnlyForOneLightType() &&
								pass->getOnlyLightType() != currLight->getType()) ||
								(pass->getLightMask() & currLight->getLightMask()) == 0)
							{
								// Skip
								// Also skip shadow texture(s)
								if (isShadowTechniqueTextureBased())
								{
									shadowTexIndex += mShadowTextureCountPerType[currLight->getType()];
								}
								continue;
							}

							*destit++ = currLight;

							// potentially need to update content_type shadow texunit
							// corresponding to this light
							if (isShadowTechniqueTextureBased())
							{
								size_t textureCountPerLight = mShadowTextureCountPerType[currLight->getType()];
								for (size_t j = 0; j < textureCountPerLight && shadowTexIndex < mShadowTextures.size(); ++j)
								{
									// link the numShadowTextureLights'th shadow texture unit
									unsigned short tuindex =
										pass->_getTextureUnitWithContentTypeIndex(
										TextureUnitState::CONTENT_SHADOW, numShadowTextureLights);
									if (tuindex > pass->getNumTextureUnitStates()) break;

									// I know, nasty const_cast
									TextureUnitState* tu =
										const_cast<TextureUnitState*>(
										pass->getTextureUnitState(tuindex));
									const TexturePtr& shadowTex = mShadowTextures[shadowTexIndex];
									tu->_setTexturePtr(shadowTex);
									Camera *cam = shadowTex->getBuffer()->getRenderTarget()->getViewport(0)->getCamera();
									tu->setProjectiveTexturing(!pass->hasVertexProgram(), cam);
									mAutoParamDataSource->setTextureProjector(cam, numShadowTextureLights);
									++numShadowTextureLights;
									++shadowTexIndex;
									// Have to set TU on rendersystem right now, although
									// autoparams will be set later
									mDestRenderSystem->_setTextureUnitSettings(tuindex, *tu);
								}
							}



						}
						// Did we run out of lights before slots? e.g. 5 lights, 2 per iteration
						if (destit != localLightList.end())
						{
							localLightList.erase(destit, localLightList.end());
							lightsLeft = 0;
						}
						pLightListToUse = &localLightList;

						// deal with the case where we found no lights
						// since this is light iteration, we shouldn't render at all
						if (pLightListToUse->empty())
							return;

					}
					else // !iterate per light
					{
						// Use complete light list potentially adjusted by start light
						if (pass->getStartLight() || pass->getMaxSimultaneousLights() != OGRE_MAX_SIMULTANEOUS_LIGHTS ||
							pass->getLightMask() != 0xFFFFFFFF)
						{
							// out of lights?
							// skip manual 2nd lighting passes onwards if we run out of lights, but never the first one
							if (pass->getStartLight() > 0 &&
								pass->getStartLight() >= rendLightList.size())
							{
								break;
							}
							else
							{
								localLightList.clear();
								LightList::const_iterator copyStart = rendLightList.begin();
								std::advance(copyStart, pass->getStartLight());
								// Clamp lights to copy to avoid overrunning the end of the list
								size_t lightsCopied = 0, lightsToCopy = std::min(
									static_cast<size_t>(pass->getMaxSimultaneousLights()),
									rendLightList.size() - pass->getStartLight());

								//localLightList.insert(localLightList.begin(), 
								//	copyStart, copyEnd);

								// Copy lights over
								for (LightList::const_iterator iter = copyStart; iter != rendLightList.end() && lightsCopied < lightsToCopy; ++iter)
								{
									if ((pass->getLightMask() & (*iter)->getLightMask()) != 0)
									{
										localLightList.push_back(*iter);
										lightsCopied++;
									}
								}

								pLightListToUse = &localLightList;
							}
						}
						else
						{
							pLightListToUse = &rendLightList;
						}
						lightsLeft = 0;
					}

					fireRenderSingleObject(rend, pass, mAutoParamDataSource, pLightListToUse, mSuppressRenderStateChanges);

					// Do we need to update GPU program parameters?
					if (pass->isProgrammable())
					{
						useLightsGpuProgram(pass, pLightListToUse);
					}
					// Do we need to update light states? 
					// Only do this if fixed-function vertex lighting applies
					if (pass->getLightingEnabled() && passSurfaceAndLightParams)
					{
						useLights(*pLightListToUse, pass->getMaxSimultaneousLights());
					}
					// optional light scissoring & clipping
					ClipResult scissored = CLIPPED_NONE;
					ClipResult clipped = CLIPPED_NONE;
					if (lightScissoringClipping &&
						(pass->getLightScissoringEnabled() || pass->getLightClipPlanesEnabled()))
					{
						// if there's no lights hitting the scene, then we might as 
						// well stop since clipping cannot include anything
						if (pLightListToUse->empty())
							continue;

						if (pass->getLightScissoringEnabled())
							scissored = buildAndSetScissor(*pLightListToUse, mCameraInProgress);

						if (pass->getLightClipPlanesEnabled())
							clipped = buildAndSetLightClip(*pLightListToUse);

						if (scissored == CLIPPED_ALL || clipped == CLIPPED_ALL)
							continue;
					}
					// issue the render op		
					// nfz: check for gpu_multipass
					mDestRenderSystem->setCurrentPassIterationCount(pass->getPassIterationCount());
					// We might need to update the depth bias each iteration
					if (pass->getIterationDepthBias() != 0.0f)
					{
						float depthBiasBase = pass->getDepthBiasConstant() +
							pass->getIterationDepthBias() * depthInc;
						// depthInc deals with light iteration 

						// Note that we have to set the depth bias here even if the depthInc
						// is zero (in which case you would think there is no change from
						// what was set in _setPass(). The reason is that if there are
						// multiple Renderables with this Pass, we won't go through _setPass
						// again at the start of the iteration for the next Renderable
						// because of Pass state grouping. So set it always

						// Set modified depth bias right away
						mDestRenderSystem->_setDepthBias(depthBiasBase, pass->getDepthBiasSlopeScale());

						// Set to increment internally too if rendersystem iterates
						mDestRenderSystem->setDeriveDepthBias(true,
							depthBiasBase, pass->getIterationDepthBias(),
							pass->getDepthBiasSlopeScale());
					}
					else
					{
						mDestRenderSystem->setDeriveDepthBias(false);
					}
					depthInc += pass->getPassIterationCount();

					// Finalise GPU parameter bindings
					updateGpuProgramParameters(pass);

					if (rend->preRender(this, mDestRenderSystem))
						mDestRenderSystem->_render(ro);
					rend->postRender(this, mDestRenderSystem);

					if (scissored == CLIPPED_SOME)
						resetScissor();
					if (clipped == CLIPPED_SOME)
						resetLightClip();
				} // possibly iterate per light
			}
			else // no automatic light processing
			{
				// Even if manually driving lights, check light type passes
				bool skipBecauseOfLightType = false;
				if (pass->getRunOnlyForOneLightType())
				{
					if (!manualLightList ||
						(manualLightList->size() == 1 &&
						manualLightList->at(0)->getType() != pass->getOnlyLightType()))
					{
						skipBecauseOfLightType = true;
					}
				}

				if (!skipBecauseOfLightType)
				{
					fireRenderSingleObject(rend, pass, mAutoParamDataSource, manualLightList, mSuppressRenderStateChanges);
					// Do we need to update GPU program parameters?
					if (pass->isProgrammable())
					{
						// Do we have a manual light list?
						if (manualLightList)
						{
							useLightsGpuProgram(pass, manualLightList);
						}

					}

					// Use manual lights if present, and not using vertex programs that don't use fixed pipeline
					if (manualLightList &&
						pass->getLightingEnabled() && passSurfaceAndLightParams)
					{
						useLights(*manualLightList, pass->getMaxSimultaneousLights());
					}

					// optional light scissoring
					ClipResult scissored = CLIPPED_NONE;
					ClipResult clipped = CLIPPED_NONE;
					if (lightScissoringClipping && manualLightList && pass->getLightScissoringEnabled())
					{
						scissored = buildAndSetScissor(*manualLightList, mCameraInProgress);
					}
					if (lightScissoringClipping && manualLightList && pass->getLightClipPlanesEnabled())
					{
						clipped = buildAndSetLightClip(*manualLightList);
					}

					// don't bother rendering if clipped / scissored entirely
					if (scissored != CLIPPED_ALL && clipped != CLIPPED_ALL)
					{
						// issue the render op		
						// nfz: set up multipass rendering
						mDestRenderSystem->setCurrentPassIterationCount(pass->getPassIterationCount());
						// Finalise GPU parameter bindings
						updateGpuProgramParameters(pass);

						if (rend->preRender(this, mDestRenderSystem))
							mDestRenderSystem->_render(ro);
						rend->postRender(this, mDestRenderSystem);
					}
					if (scissored == CLIPPED_SOME)
						resetScissor();
					if (clipped == CLIPPED_SOME)
						resetLightClip();

				} // !skipBecauseOfLightType
			}
	}

#	define SetShaderRenderParam(shader, reflect)															\
	if (reflect != nullptr)																					\
	{																										\
		ID3D11ShaderReflectionPtr shaderReflect = reflect;													\
		hr = shaderReflect->GetDesc(&shaderDesc);															\
		D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::Render");												\
		D3D11_SHADER_INPUT_BIND_DESC resourceDesc = {0};													\
		for(u32 i = 0; i < shaderDesc.BoundResources; ++ i)													\
		{																									\
			hr = shaderReflect->GetResourceBindingDesc(i, &resourceDesc);									\
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::Render");											\
			switch (resourceDesc.Type)																		\
			{																								\
			case D3D_SIT_CBUFFER:																			\
				{																							\
				RenderParamPtr renderParam = mCurrentMaterial->GetRenderParam(resourceDesc.Name);			\
					if(renderParam == nullptr)																\
					{																						\
						DRE_EXCEPT(DRE_EXCEPTION_ITEM_NOT_FOUND, "�Ҳ���hlslҪ�����Ⱦ����",				\
							"D3D11RenderSystem::Render");													\
					}																						\
																											\
					D3D11_BUFFER_DESC bufferDesc = {0};														\
					bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;										\
					bufferDesc.CPUAccessFlags = 0;															\
					bufferDesc.ByteWidth = renderParam->GetSize();											\
					bufferDesc.MiscFlags = 0;																\
					bufferDesc.StructureByteStride = 0;														\
					bufferDesc.Usage = D3D11_USAGE_DEFAULT;													\
																											\
					D3D11_SUBRESOURCE_DATA bufferData = {0};												\
					bufferData.pSysMem = renderParam->GetParam();											\
																											\
					ID3D11BufferPtr buffer;																	\
					hr = mD3D11Device->CreateBuffer(&bufferDesc, &bufferData,								\
						buffer.GetReference());																\
					D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::Render");									\
																											\
					ID3D11Buffer* temp = buffer.Get();														\
					mD3D11Context->shader##SetConstantBuffers(resourceDesc.BindPoint,						\
						resourceDesc.BindCount, &temp);														\
				}																							\
				break;																						\
			case D3D_SIT_SAMPLER:																			\
				{																							\
					D3D11SamplerPtr sampler = mCurrentMaterial->mSamplerMap[resourceDesc.Name];				\
					if(sampler == nullptr)																	\
					{																						\
						/*if (mSamplerArray[resourceDesc.BindPoint] == nullptr)	*/							\
						{																					\
							DRE_EXCEPT(DRE_EXCEPTION_ITEM_NOT_FOUND, "�Ҳ���hlslҪ�����Ⱦ����",			\
								"D3D11RenderSystem::Render");												\
						}																					\
						/*else																				\
						{																					\
							sampler = mSamplerArray[resourceDesc.BindPoint];								\
						}*/																					\
					}																						\
																											\
					ID3D11SamplerState* temp = sampler->GetSamplerState().Get();							\
					mD3D11Context->shader##SetSamplers(resourceDesc.BindPoint, resourceDesc.BindCount,		\
						&temp);																				\
				}																							\
				break;																						\
			case D3D_SIT_TEXTURE:																			\
				{																							\
					D3D11TexturePtr texture = mCurrentMaterial->mTextureMap[resourceDesc.Name];				\
					if(texture == nullptr)																	\
					{																						\
						/*if (mTextureArray[resourceDesc.BindPoint] == nullptr)	*/							\
						{																					\
							DRE_EXCEPT(DRE_EXCEPTION_ITEM_NOT_FOUND, "�Ҳ���hlslҪ�����Ⱦ����",			\
								"D3D11RenderSystem::Render");												\
						}																					\
						/*else																				\
						{																					\
							texture = mTextureArray[resourceDesc.BindPoint];								\
						}*/																					\
					}																						\
																											\
					ID3D11ShaderResourceView* temp = texture->GetShaderResource().Get();					\
					mD3D11Context->shader##SetShaderResources(resourceDesc.BindPoint,						\
						resourceDesc.BindCount, &temp);														\
				}																							\
				break;																						\
			default:																						\
				DRE_EXCEPT(DRE_EXCEPTION_ITEM_NOT_FOUND, "�Ҳ���hlslҪ�����Ⱦ����",						\
					"D3D11RenderSystem::Render");															\
			}																								\
		}																									\
	}	

	/** ��Ⱦ����
	*/																								
	void D3D11RenderSystem::Render(void)
	{
		D3D11_SHADER_DESC shaderDesc = {0};																																						
		HRESULT hr = 0;
		D3D11ShaderPtr shaderPtr = mCurrentMaterial->mShader;

		if (mIsMaterialChange)
		{
			// ����HLSL��Ⱦ
			mD3D11Context->VSSetShader(shaderPtr->GetVertexShader().Get(), 0, 0);
			mD3D11Context->DSSetShader(shaderPtr->GetDomainShader().Get(), 0, 0);
			mD3D11Context->HSSetShader(shaderPtr->GetHullShader().Get(), 0, 0);
			mD3D11Context->GSSetShader(shaderPtr->GetGeometryShader().Get(), 0, 0);
			mD3D11Context->PSSetShader(shaderPtr->GetPixelShader().Get(), 0, 0);

			SetShaderRenderParam(VS, shaderPtr->GetVertexShaderReflect());
			SetShaderRenderParam(DS, shaderPtr->GetDomainShaderReflect());
			SetShaderRenderParam(HS, shaderPtr->GetHullShaderReflect());
			SetShaderRenderParam(GS, shaderPtr->GetGeometryShaderReflect());
			SetShaderRenderParam(PS, shaderPtr->GetPixelShaderReflect());

			mIsMaterialChange = false;
		}

		// ���û��״̬
		if (mIsBlendStateChange)
		{
			ID3D11BlendStatePtr newBlendState;
			hr = mD3D11Device->CreateBlendState(&mRenderState.mBlendDesc, newBlendState.GetReference());
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::Render");
			mBlendState = newBlendState;

			mD3D11Context->OMSetBlendState(mBlendState.Get(), mRenderState.mBlendColor, 0xffffffff);

			mIsBlendStateChange = false;
		}	

		// �������ģ��״̬
		if (mIsDepthStencilStateChange)
		{
			ID3D11DepthStencilStatePtr newDepthStencilSate;
			hr = mD3D11Device->CreateDepthStencilState(&mRenderState.mDepthStencilDesc,
				newDepthStencilSate.GetReference());
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::Render");
			mDepthStencilState = newDepthStencilSate;

			mD3D11Context->OMSetDepthStencilState(mDepthStencilState.Get(), mRenderState.mStencilRef);
			mIsDepthStencilStateChange = false;
		}
		
		// ���ù�դ״̬
		if (mIsRasterizerStateChange)
		{
			ID3D11RasterizerStatePtr newRasterizerState;
			mD3D11Device->CreateRasterizerState(&mRenderState.mRasterizerDesc, 
				newRasterizerState.GetReference());
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::Render");
			mRasterizerState = newRasterizerState;
		
			mD3D11Context->RSSetState(mRasterizerState.Get());

			mIsRasterizerStateChange = false;
		}

		if(mIsVertexBufferChange)
		{

			// ���ö��㻺����
			UINT strides = mCurrentVertexBuffer->GetVertexSize();
			UINT offset = 0;
			ID3D11Buffer* ID3D11Buffer = mCurrentVertexBuffer->GetVertexBuffer().Get();
			mD3D11Context->IASetVertexBuffers(0, 1, &ID3D11Buffer, &strides, &offset);

			// ���ö�������
			ID3D11InputLayoutPtr inputLayout;
			hr = mD3D11Device->CreateInputLayout(mInputLayout.get(), mInputLayoutCount, 
				shaderPtr->GetShaderBlob()->GetBufferPointer(),
				shaderPtr->GetShaderBlob()->GetBufferSize(), inputLayout.GetReference());
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::SetHLSLShader");
			mD3D11Context->IASetInputLayout(inputLayout.Get());

			mIsVertexBufferChange = false;
		}

		if(mIsIndexBufferChange)
		{
			// ��������������
			mD3D11Context->IASetIndexBuffer(mCurrentIndexBuffer->GetIndexBuffer().Get(),
				D3D11RenderMapping::Get(mCurrentIndexBuffer->GetIndexType()), 0);

			mIsIndexBufferChange = false;
		}

		// ��ʼ��ȾRenderTarget
		for(u32 i = 0; i < D3D11_MAX_RENDER_TARGET_NUM; ++ i)
		{
			if (mRenderTargetList[i] == nullptr)
				continue;

			ID3D11RenderTargetView* temp = mRenderTargetList[i]->GetRenderTarget().Get();
			mD3D11Context->OMSetRenderTargets(1, &temp, 
				mRenderTargetList[i]->GetDepthStencil().Get());

			float clearColor[] = { 0.0f, 0.0f, 0.25f, 1.0f };
			mD3D11Context->ClearRenderTargetView(temp, clearColor);

			if (mRenderTargetList[i]->GetDepthStencil() != nullptr)
			{
				UINT clearFlags = 0;
				if (mRenderTargetList[i]->HasDepthBuffer())
					clearFlags |= D3D11_CLEAR_DEPTH;
				if (mRenderTargetList[i]->HasStencilBuffer())
					clearFlags |= D3D11_CLEAR_STENCIL;

				mD3D11Context->ClearDepthStencilView(mRenderTargetList[i]->GetDepthStencil().Get(),
					clearFlags, 1.0f, 0);
			}

			if (mCurrentIndexBuffer != nullptr)
				mD3D11Context->DrawIndexed(mCurrentIndexBuffer->GetIndexNum(), 0, 0);
			else if (mCurrentVertexBuffer != nullptr)
				mD3D11Context->Draw(mCurrentVertexBuffer->GetNumVertices(), 0);
		}

		// ��ʼ��ȾRendeWindow
		for(u32 i = 0; i < D3D11_MAX_RENDER_WINDOW_NUM; ++ i)
		{
			if (mRenderWindowList[i] == nullptr)
				continue;

			ID3D11RenderTargetView* temp = mRenderWindowList[i]->GetRenderTarget().Get();
			mD3D11Context->OMSetRenderTargets(1, &temp, 
				mRenderWindowList[i]->GetDepthStencil().Get());

			float clearColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
			mD3D11Context->ClearRenderTargetView(temp, clearColor);

			if (mRenderWindowList[i]->GetDepthStencil() != nullptr)
			{
				UINT clearFlags = 0;
				if (mRenderWindowList[i]->HasDepthBuffer())
					clearFlags |= D3D11_CLEAR_DEPTH;
				if (mRenderWindowList[i]->HasStencilBuffer())
					clearFlags |= D3D11_CLEAR_STENCIL;

				mD3D11Context->ClearDepthStencilView(mRenderWindowList[i]->GetDepthStencil().Get(),
					clearFlags, 1.0f, 0);
			}

			if (mCurrentIndexBuffer != nullptr)
				mD3D11Context->DrawIndexed(mCurrentIndexBuffer->GetIndexNum(), 0, 0);
			else if (mCurrentVertexBuffer != nullptr)
				mD3D11Context->Draw(mCurrentVertexBuffer->GetNumVertices(), 0);
			
			IDXGISwapChain* swapChain = mRenderWindowList[i]->GetSwapChain().Get();
			hr = swapChain->Present(mWaitForVerticalBlank, 0);
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::Render");
		}
	}

	/** ���浱ǰ����Ⱦ״̬
	*/
	void D3D11RenderSystem::SaveRenderState()
	{
		mSavedRenderState = mRenderState;
	}

	/** �ָ���һ���������Ⱦ״̬
	*/
	void D3D11RenderSystem::ResetRenderState()
	{
		mRenderState = mSavedRenderState;

		mIsBlendStateChange			= true;
		mIsDepthStencilStateChange	= true;
		mIsRasterizerStateChange	= true;
	}

#pragma region BlendState

	/** ������ɫ����Ƿ���
	*/
	void D3D11RenderSystem::SetBlendEnable(bool enabled)
	{
		if (!mCapabilities.HasSupportedCapabilitie(DRE_CAPABILITIES_BLENDING))
		{
			DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "��ǰ�Կ���֧��BLENDING����",
				"D3D11RenderSystem::SetBlendEnable");
		}

		if (mRenderState.mBlendDesc.RenderTarget[0].BlendEnable != (BOOL)enabled)
		{
			mIsBlendStateChange = true;
			mRenderState.mBlendDesc.RenderTarget[0].BlendEnable = enabled;
		}
	}

	/** ������ɫ����Ƿ���
	*/
	bool D3D11RenderSystem::GetBlendEnable(void) const
	{
		return mRenderState.mBlendDesc.RenderTarget[0].BlendEnable == TRUE;
	}

	void D3D11RenderSystem::SetSceneColorBlending(DRE_BLEND_COLOR_FACTOR src1, DRE_BLEND_COLOR_FACTOR src2,
			DRE_BLEND_OPERATION op /* = DRE_BLEND_ADD_OPERATION */ )
	{
		mIsBlendStateChange = true;
	
		mRenderState.mBlendDesc.RenderTarget[0].SrcBlend		= D3D11RenderMapping::Get(src1);
		mRenderState.mBlendDesc.RenderTarget[0].DestBlend	= D3D11RenderMapping::Get(src2);
		mRenderState.mBlendDesc.RenderTarget[0].BlendOp		= D3D11RenderMapping::Get(op);
	}

	void D3D11RenderSystem::SetSceneAlphaBlending(DRE_BLEND_ALPHA_FACTOR srcAlpha1, DRE_BLEND_ALPHA_FACTOR srcAlpha2,
			DRE_BLEND_OPERATION alphaOp /* = DRE_BLEND_ADD_OPERATION */)
	{
		mIsBlendStateChange = true;
	
		mRenderState.mBlendDesc.RenderTarget[0].SrcBlend		= D3D11RenderMapping::Get(srcAlpha1);
		mRenderState.mBlendDesc.RenderTarget[0].DestBlend	= D3D11RenderMapping::Get(srcAlpha2);
		mRenderState.mBlendDesc.RenderTarget[0].BlendOp		= D3D11RenderMapping::Get(alphaOp);
	}

	void D3D11RenderSystem::SetAlphaRejectSettings(DRE_COMPARISON_FUNC func, f32 value)
	{
		DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "�޴˺����Ķ�Ӧʵ����ʹ��HLSLʵ��", 
			"D3D11RenderSystem::SetAlphaRejectSettings");
	}

	void D3D11RenderSystem::SetAlphaToCoverageEnable(bool enabled)
	{
		// �����ж�
		if (!mCapabilities.HasSupportedCapabilitie(DRE_CAPABILITIES_ALPHA_TO_COVERAGE))
		{
			DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "��ǰ�Կ���֧��ALPHA_TO_COVERAGE����",
				"D3D11RenderSystem::SetAlphaToCoverageEnable");
		}

		mIsBlendStateChange = true;
	
		mRenderState.mBlendDesc.AlphaToCoverageEnable = enabled;
	}

	void D3D11RenderSystem::SetColourBufferWriteEnabled(bool red, bool green,
		bool blue, bool alpha)
	{
		u32 marks = 0;
		if (red)	{ marks |= D3D11_COLOR_WRITE_ENABLE_RED; }
		if (green)	{ marks |= D3D11_COLOR_WRITE_ENABLE_GREEN; }
		if (blue)	{ marks |= D3D11_COLOR_WRITE_ENABLE_BLUE; }
		if (alpha)	{ marks |= D3D11_COLOR_WRITE_ENABLE_ALPHA; }
	}

#pragma endregion

#pragma region ViewportState
	/** �趨��Ⱦ�ӿ�
	*/
	void D3D11RenderSystem::SetViewport(const Viewport & vp)
	{
		D3D11_VIEWPORT v;
		v.Width = vp.mWidth;
		v.Height = vp.mHeight;
		v.MaxDepth = vp.mMaxDepth;
		v.MinDepth = vp.mMinDepth;
		v.TopLeftX = vp.mTopLeftX;
		v.TopLeftY = vp.mTopLeftY;

		mD3D11Context->RSSetViewports(1, &v);
	}

	/** ȡ�õ�ǰ��Ⱦ�ӿ�
	*/
	Viewport D3D11RenderSystem::GetViewport(void) 
	{
		D3D11_VIEWPORT v;

		UINT num = 0;
		mD3D11Context->RSGetViewports(&num, &v);

		Viewport vp = {v.TopLeftX, v.TopLeftY, v.Width, v.Height,
			v.MinDepth, v.MaxDepth};
		return vp;
	}

#pragma endregion

#pragma region DepthStencilState

	/** �Ƿ����ɰ����
	*/
	void D3D11RenderSystem::SetStencilCheckEnabled(bool enabled)
	{
		if (!mCapabilities.HasSupportedCapabilitie(DRE_CAPABILITIES_HWSTENCIL))
		{
			DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "��ǰ�Կ���֧��HARDWARE_STENCIL����",
				"D3D11RenderSystem::SetStencilCheckEnabled");
		}

		if(mRenderState.mDepthStencilDesc.StencilEnable != (BOOL)enabled)
		{
			mIsDepthStencilStateChange = true;
			mRenderState.mDepthStencilDesc.StencilEnable = enabled;
		}
	}

	/** �趨ǰ���ɰ���Բ���
	* @param refValue ��ǰ�ɰ�ֵ
	* @param writemask ��ǰд���ɰ�ֵ����
	*/
	void D3D11RenderSystem::SetStencilBufferParams( u8 refValue, u8 writeMask )
	{
		mIsDepthStencilStateChange = true;

		mRenderState.mDepthStencilDesc.StencilWriteMask = writeMask;
		mRenderState.mStencilRef = refValue;
	}

	/** �趨ǰ���ɰ���Բ���
	* @param func �ɰ���Ժ���
	* @param stencilFailOp �ɰ����ʧ��ʱ�Ĳ���
	* @param depthFailOp �ɰ���Գɹ�����Ȳ���ʧ��ʱ�Ĳ���
	* @param passOp �ɰ���Ժ���Ȳ��Զ��ɹ�ʱ�Ĳ���
	*/
	void D3D11RenderSystem::SetStencilBufferFrontFaceOp( 
		DRE_COMPARISON_FUNC func, 
		DRE_STENCIL_OPEARTION stencilFailOp, 
		DRE_STENCIL_OPEARTION depthFailOp,
		DRE_STENCIL_OPEARTION passOp )
	{
		mIsDepthStencilStateChange = true;

		mRenderState.mDepthStencilDesc.FrontFace.StencilFunc = D3D11RenderMapping::Get(func);
		mRenderState.mDepthStencilDesc.FrontFace.StencilFailOp = D3D11RenderMapping::Get(stencilFailOp);
		mRenderState.mDepthStencilDesc.FrontFace.StencilDepthFailOp = D3D11RenderMapping::Get(depthFailOp);
		mRenderState.mDepthStencilDesc.FrontFace.StencilPassOp = D3D11RenderMapping::Get(passOp);
	}

	/** �趨�����ɰ���Բ���
	* @param func �ɰ���Ժ���
	* @param stencilFailOp �ɰ����ʧ��ʱ�Ĳ���
	* @param depthFailOp �ɰ���Գɹ�����Ȳ���ʧ��ʱ�Ĳ���
	* @param passOp �ɰ���Ժ���Ȳ��Զ��ɹ�ʱ�Ĳ���
	*/
	void D3D11RenderSystem::SetStencilBufferBackFaceOp(
		DRE_COMPARISON_FUNC func, 
		DRE_STENCIL_OPEARTION stencilFailOp, 
		DRE_STENCIL_OPEARTION depthFailOp,
		DRE_STENCIL_OPEARTION passOp )
	{
		if (!mCapabilities.HasSupportedCapabilitie(DRE_CAPABILITIES_TWO_SIDED_STENCIL))
		{
			DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "��ǰ�Կ���֧��TWO_SIDED_STENCIL����",
				"D3D11RenderSystem::SetStencilBufferBackFaceOp");
		}

		mIsDepthStencilStateChange = true;

		mRenderState.mDepthStencilDesc.BackFace.StencilFunc = D3D11RenderMapping::Get(func);
		mRenderState.mDepthStencilDesc.BackFace.StencilFailOp = D3D11RenderMapping::Get(stencilFailOp);
		mRenderState.mDepthStencilDesc.BackFace.StencilDepthFailOp = D3D11RenderMapping::Get(depthFailOp);
		mRenderState.mDepthStencilDesc.BackFace.StencilPassOp = D3D11RenderMapping::Get(passOp);
	}

	/** �Ƿ�ʹ����Ȼ�����
	@param enabled trueΪ�򿪣�falseΪ�ر�
	*/
	void D3D11RenderSystem::SetZBufferEnabled(bool enabled)
	{
		if(mRenderState.mDepthStencilDesc.DepthEnable != (BOOL)enabled)
		{
			mIsDepthStencilStateChange = true;
			mRenderState.mDepthStencilDesc.DepthEnable = enabled;
		}
	}

	/** ���ص�ǰ�Ƿ�ʹ����Ȼ�����
	*/
	bool D3D11RenderSystem::GetZBufferEnabled(void) const
	{
		return mRenderState.mDepthStencilDesc.DepthEnable == TRUE;
	}

	/** �趨��Ȼ������
	* @param depthTest �Ƿ������Ȼ�����ԣ�false�򲻱Ƚ�ֱ��д������
	* @param depthWrite �Ƿ��д����Ȼ��壨���Ƿ�ʹ����Ȼ��壩
	* @param depthFunction ��Ȳ��ԱȽϺ���.
	*/
	void D3D11RenderSystem::SetDepthBufferParams(bool depthTest /* = true */, bool depthWrite /* = true */,
		DRE_COMPARISON_FUNC depthFunction /* = DRE_COMPARISON_LESSEQUAL */)
	{
		mIsDepthStencilStateChange = true;

		mRenderState.mDepthStencilDesc.DepthEnable = depthTest;
		if (depthWrite)
			mRenderState.mDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		else
			mRenderState.mDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		mRenderState.mDepthStencilDesc.DepthFunc = D3D11RenderMapping::Get(depthFunction);
	}

	/** ������Ȳ����Ƿ���
	*/
	void D3D11RenderSystem::SetDepthBufferCheckEnabled(bool enabled)
	{
		if(mRenderState.mDepthStencilDesc.DepthEnable != (BOOL)enabled)
		{
			mIsDepthStencilStateChange = true;
			mRenderState.mDepthStencilDesc.DepthEnable = enabled;
		}
	}

	/** ������Ȼ����Ƿ����
	*/
	void D3D11RenderSystem::SetDepthBufferWriteEnabled(bool enabled)
	{
		mIsDepthStencilStateChange = true;

		if (enabled)
			mRenderState.mDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		else
			mRenderState.mDepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	}

	/** ������Ȳ��Ժ���
	*/
	void D3D11RenderSystem::SetDepthBufferFunction(DRE_COMPARISON_FUNC func)
	{
		mIsDepthStencilStateChange = true;

		mRenderState.mDepthStencilDesc.DepthFunc = D3D11RenderMapping::Get(func);
	}

#pragma endregion

#pragma region RasterizerState
	/** �������ģʽ
	*/
	void D3D11RenderSystem::SetFillMode(DRE_FILL_MODE fillMode)
	{
		DreAssert(fillMode != DRE_FILL_POINT_MODE, "D3D11����DRE_FILL_POINT_MODE����");

		mIsRasterizerStateChange = true;
		mRenderState.mRasterizerDesc.FillMode = D3D11RenderMapping::Get(fillMode);
	}

	DRE_FILL_MODE D3D11RenderSystem::GetFillMode(void) const
	{
		return D3D11RenderMapping::Get(mRenderState.mRasterizerDesc.FillMode);
	}
	
	/** ���òü�ģʽ
	* @param mode �ü�ģʽ��һ��ΪDRE_CULL_BACK��������
	*/
	void D3D11RenderSystem::SetCullingMode(DRE_CULL_MODE mode)
	{
		mIsRasterizerStateChange = true;

		mRenderState.mRasterizerDesc.CullMode = D3D11RenderMapping::Get(mode);
	}

	DRE_CULL_MODE D3D11RenderSystem::GetCullingMode(void) const
	{
		return D3D11RenderMapping::Get(mRenderState.mRasterizerDesc.CullMode);
	}
	
	/** �����Ƿ�������ȡ��
	*/
	void D3D11RenderSystem::SetMultisampleEnabled(bool enabled)
	{
		if(mRenderState.mRasterizerDesc.MultisampleEnable != (BOOL)enabled)
		{
			mIsRasterizerStateChange = true;
			mRenderState.mRasterizerDesc.MultisampleEnable = enabled;
		}
	}

	bool D3D11RenderSystem::GetMultisampleEnabled() const
	{
		return mRenderState.mRasterizerDesc.MultisampleEnable == TRUE;
	}

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
	void D3D11RenderSystem::SetDepthBias(f32 constantBias, f32 slopeScaleBias)
	{
		mIsRasterizerStateChange = true;

		mRenderState.mRasterizerDesc.DepthBias = static_cast<int>(constantBias);
		mRenderState.mRasterizerDesc.SlopeScaledDepthBias = slopeScaleBias;
	}

	/** �������ֵƫ�����ֵ
	* @param	maxDepthBias depthֵ��������ƫ��ֵ
	*
	* @remark	
	*			if(DepthBiasClamp > 0)
	*				Bias = min(DepthBiasClamp, Bias)
	*			else if(DepthBiasClamp < 0)
	*				Bias = max(DepthBiasClamp, Bias)
	*/
	void D3D11RenderSystem::SetDepthBiasClamp(f32 maxDepthBias)
	{
		mIsRasterizerStateChange = true;

		mRenderState.mRasterizerDesc.DepthBiasClamp = maxDepthBias;
	}

	/** ���òü�������Ƿ���
	* @param enabled True to enable the scissor test, false to disable it.
	*/
	void D3D11RenderSystem::SetScissorTestEnable(bool enabled)
	{
		if (mRenderState.mRasterizerDesc.ScissorEnable != (BOOL)enabled)
		{
			mIsRasterizerStateChange = true;
			mRenderState.mRasterizerDesc.ScissorEnable = enabled;
		}
	}

	/** ����һ���ü���
	* @note Ҫʹ�ü�����Ч����������setScissorTestEnable
	*/
	void D3D11RenderSystem::SetScissorTest(u32 left, u32 top, u32 right, u32 bottom)
	{
		D3D11_RECT rect = {left, top, right, bottom};

		UINT num = 0;
		mD3D11Context->RSGetScissorRects(&num, &rect);
	}

#pragma endregion

#pragma region InputState

	/** ���ö�������
	*/
	void D3D11RenderSystem::SetVertexDeclaration(const VertexDeclaration& declaration)
	{
		VertexElementConstIterator ite = declaration.begin();

		mInputLayout.reset(DREAM_NEW D3D11_INPUT_ELEMENT_DESC[declaration.size()]);
		mInputLayoutCount = declaration.size();

		for(int i = 0; ite != declaration.end(); ++ ite, ++ i)
		{
			mInputLayout[i].SemanticName =			D3D11RenderMapping::Get(ite->mSemantic);
			mInputLayout[i].SemanticIndex =			ite->mIndex;
			mInputLayout[i].Format=					D3D11RenderMapping::Get(ite->mType);
			mInputLayout[i].InputSlot =				0; 
			mInputLayout[i].AlignedByteOffset =		D3D11_APPEND_ALIGNED_ELEMENT;
			mInputLayout[i].InputSlotClass =		D3D11_INPUT_PER_VERTEX_DATA;
			mInputLayout[i].InstanceDataStepRate =	0;
		}
	}

	/** ����ͼԪ����
	*/
	void D3D11RenderSystem::SetPolygonMode(DRE_PRIMITIVE_TOPOLOGY level)
	{
		mD3D11Context->IASetPrimitiveTopology(D3D11RenderMapping::Get(level));
	}

	/** 
	���ö��㻺����
	*/
	void D3D11RenderSystem::SetHardwareVertexBuffer(HardwareVertexBufferPtr& vertexBuffer)
	{
		mIsVertexBufferChange = true;

		mCurrentVertexBuffer = dynamic_pointer_cast<D3D11HardwareVertexBuffer>(vertexBuffer);

		this->SetVertexDeclaration(mCurrentVertexBuffer->GetVertexDeclaration());
		this->SetPolygonMode(mCurrentVertexBuffer->GetVertexType());
	}

	/** ��������������
	*/
	void D3D11RenderSystem::SetHardwareIndexBuffer(HardwareIndexBufferPtr& indexBuffer)
	{
		mISindexBufferChange = true;

		mCurrentIndexBuffer = dynamic_pointer_cast<D3D11HardwareIndexBuffer>(indexBuffer);
	}
	
	void D3D11RenderSystem::SetMaterial(MaterialPtr& material)
	{
		mIsMaterialChange = true;

		mCurrentMaterial = dynamic_pointer_cast<D3D11Material>(material);
	}

#pragma endregion

#pragma region OnlyDirectX9

	void D3D11RenderSystem::SetFixedPipelineEnabled(bool enable)
	{
		DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "�޴˺����Ķ�Ӧʵ��", 
			"D3D11RenderSystem::SetFixedPipelineEnabled");
	}

	bool D3D11RenderSystem::GetFixedPipelineEnabled(void) const
	{
		return false;
	}

	/** ���û�����
	*/
	void D3D11RenderSystem::SetAmbientLight(f32 r, f32 g, f32 b) 
	{
		DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "D3D11RenderSystem�޶�Ӧʵ�֣���ͨ��HLSLʵ�ֶ�ӦЧ��",
			"D3D11RenderSystem::SetAmbientLight");
	}

	/** ���ù�Դ��Ⱦ����Ⱦ��������DX9��Ч��DX11�̶�ΪGouraud��ɫ
	*/
	void D3D11RenderSystem::SetShadingType(DRE_SHADER_OPTION shaderOption)
	{
		DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "D3D11RenderSystem�޶�Ӧʵ�֣���ͨ��HLSLʵ�ֶ�ӦЧ��",
			"D3D11RenderSystem::SetShadingTyp");
	}

	/** �򿪶�̬��Դ
	* @param enabled trueΪ�򿪣�falseΪ�ر�
	*/
	void D3D11RenderSystem::SetLightingEnabled(bool enabled)
	{
		DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "D3D11RenderSystem�޶�Ӧʵ�֣���ͨ��HLSLʵ�ֶ�ӦЧ��",
			"D3D11RenderSystem::SetLightingEnabled");
	}

	/** ������Ⱦ��Դ
	* @param lights ��Դ�б�
	* @param limit ��Դ����
	*/
	void D3D11RenderSystem::UseLights(const LightList& lights, unsigned short limit)
	{
		DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "D3D11RenderSystem�޶�Ӧʵ�֣���ͨ��HLSLʵ�ֶ�ӦЧ��",
			"D3D11RenderSystem::UseLights");
	}
	
	/** ��������ת������ */
	void D3D11RenderSystem::SetWorldMatrix(const Matrix4 &m)
	{
		DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "D3D11RenderSystem�޶�Ӧʵ�֣���ͨ��HLSLʵ�ֶ�ӦЧ��",
			"D3D11RenderSystem::SetWorldMatrix");
	}
	/** �������ת������ */
	void D3D11RenderSystem::SetViewMatrix(const Matrix4 &m)
	{
		DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "D3D11RenderSystem�޶�Ӧʵ�֣���ͨ��HLSLʵ�ֶ�ӦЧ��",
			"D3D11RenderSystem::SetViewMatrix");
	}
	/** ����ͶӰת������ */
	void D3D11RenderSystem::SetProjectionMatrix(const Matrix4 &m)
	{
		DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "D3D11RenderSystem�޶�Ӧʵ�֣���ͨ��HLSLʵ�ֶ�ӦЧ��",
			"D3D11RenderSystem::SetProjectionMatrix");
	}

	/** ������Ⱦ����
	* @param ambient	������ķ���ϵ��
	* @param diffuse	�����ķ���ϵ��
	* @param specular	�����ķ���ϵ��
	* @param emissive	�Է����Դ��ɫ
	* @param shininess	����߹�ϵ��
	* @param options	ʹ�ò�����ɫ�е���Щ���粻ʹ�ò�����ɫ���Զ��ڶ�����ɫ��Ѱ�Ҷ�Ӧ��ɫ
	*/
	void D3D11RenderSystem::SetSurfaceParams(const Color& ambient,
		const Color& diffuse, const Color& specular,
		const Color& emissive, f32 shininess,
		u32 options)
	{
		DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "D3D11RenderSystem�޶�Ӧʵ�֣���ͨ��HLSLʵ�ֶ�ӦЧ��",
			"D3D11RenderSystem::SetSurfaceParams");
	}

	/** �Ƿ���������Ч
	*/	
	void D3D11RenderSystem::SetPointSpritesEnabled(bool enabled)
	{
		DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "D3D11RenderSystem�޶�Ӧʵ�֣���ͨ��HLSLʵ�ֶ�ӦЧ��",
			"D3D11RenderSystem::SetPointSpritesEnabled");
	}

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
	void D3D11RenderSystem::SetPointParameters(f32 size, bool attenuationEnabled, 
		f32 constant, f32 linear, f32 quadratic, f32 minSize, f32 maxSize)
	{
		DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "D3D11RenderSystem�޶�Ӧʵ�֣���ͨ��HLSLʵ�ֶ�ӦЧ��",
			"D3D11RenderSystem::SetPointParameters");
	}

	/** ����������
	@param mode ��ģʽ
	@param �����ɫ
	@param expDensity	��DRE_FOG_EXP_MODE��DRE_FOG_EXP2_MODE����Ч��������ο�DRE_FOG_EXP_MODE
	@param linearStart	����DRE_FOG_LINEAR_MODE����Ч����ΧΪ[0.0, 1.0]��depthֵ�ķ�Χ����ʹ��DepthֵΪ��׼
	@param linearEnd	����DRE_FOG_LINEAR_MODE����Ч����ΧΪ[0.0, 1.0]��depthֵ�ķ�Χ����ʹ��DepthֵΪ��׼
	*/
	void D3D11RenderSystem::SetFog(DRE_FOG_MODE mode, const Color& color, f32 expDensity, f32 linearStart, f32 linearEnd)
	{
		DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "D3D11RenderSystem�޶�Ӧʵ�֣���ͨ��HLSLʵ�ֶ�ӦЧ��",
			"D3D11RenderSystem::SetFog");
	}

	/** �����Ƿ��Զ����滯
	*/
	void D3D11RenderSystem::SetNormaliseNormals(bool normalise)
	{
		DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "D3D11RenderSystem�޶�Ӧʵ�֣���ͨ��HLSLʵ�ֶ�ӦЧ��",
			"D3D11RenderSystem::SetNormaliseNormals");
	}

	/** ����һϵ�вü���
	* @param clipPlanes �ü�ƽ���б�
	* @note ֻ��Dirext9��Ч
	*/
	// void setClipPlanes(const PlaneList& clipPlanes);

	/** ����һ���ü�ƽ��
	*/
	void D3D11RenderSystem::addClipPlane(const Plane &p)
	{
		DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "D3D11RenderSystem�޶�Ӧʵ�֣���ͨ��HLSLʵ�ֶ�ӦЧ��",
			"D3D11RenderSystem::addClipPlane");
	}

	/** �������вü�ƽ��
	*/
	void D3D11RenderSystem::resetClipPlanes()
	{
		DRE_EXCEPT(DRE_EXCEPTION_NOT_IMPLEMENTED, "D3D11RenderSystem�޶�Ӧʵ�֣���ͨ��HLSLʵ�ֶ�ӦЧ��",
			"D3D11RenderSystem::resetClipPlanes");
	}

#pragma endregion

#pragma region SamplerState
	ID3D11SamplerStatePtr D3D11RenderSystem::CreateSampler(const SamplerDesc& sampler)
	{
		D3D11_SAMPLER_DESC samplerDesc;
		ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
		samplerDesc.AddressU =	D3D11RenderMapping::Get(sampler.addressU);
		samplerDesc.AddressV =	D3D11RenderMapping::Get(sampler.addressV);
		samplerDesc.AddressW =	D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		samplerDesc.Filter = D3D11RenderMapping::Get(sampler.filter);
		samplerDesc.MaxAnisotropy = sampler.maxAnisotropy;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
		samplerDesc.MinLOD = sampler.minLOD;
		samplerDesc.MipLODBias = sampler.mipLODBias;

		ID3D11SamplerStatePtr d3dSampler;
		HRESULT hr = mD3D11Device->CreateSamplerState(&samplerDesc, d3dSampler.GetReference());
		D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::Render");

		return d3dSampler;
	}

#pragma endregion

#pragma region BindObject

	void D3D11RenderSystem::BindRenderTarget(u32 index, RenderTargetPtr& renderTarget)
	{
		DreAssert(index < D3D11_MAX_RENDER_TARGET_NUM, "RenderTarget����Խ��");

		mRenderTargetList[index] = D3D11RenderTargetPtr(
			dynamic_pointer_cast<D3D11RenderTarget, RenderTarget>(renderTarget));
	}

	void D3D11RenderSystem::UnbindRenderTarget(u32 index)
	{
		DreAssert(index < D3D11_MAX_RENDER_TARGET_NUM, "RenderTarget����Խ��");

		mRenderTargetList[index] = nullptr;
	}

	void D3D11RenderSystem::BindRenderWindow(u32 index, RenderWindowPtr& renderWindow)
	{
		DreAssert(index < D3D11_MAX_RENDER_WINDOW_NUM, "RenderWindow����Խ��");

		mRenderWindowList[index] = D3D11RenderWindowPtr(
			dynamic_pointer_cast<D3D11RenderWindow, RenderWindow>(renderWindow));
	}

	void D3D11RenderSystem::UnbindRenderWindow(u32 index)
	{
		DreAssert(index < D3D11_MAX_RENDER_WINDOW_NUM, "RenderWindow����Խ��");

		mRenderWindowList[index] = nullptr;
	}

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
	RenderWindowPtr D3D11RenderSystem::CreateRenderWindow(u32 width, u32 height, bool isFullScreen,
		bool hasDepth, bool hasStencil, u32 fsaa, u32 fassQuality)
	{
		// ��ȡ��ǰ���̵�ʵ�����
		HINSTANCE hInstance = GetModuleHandle(0);

		WNDCLASS wndClass = {0};
		wndClass.cbClsExtra = 0;	// ��class��չ
		wndClass.cbWndExtra = 0;	// �޴�����չ
		wndClass.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));		// ȡ�ð�ɫ��ˢ
		wndClass.hCursor = LoadCursor(nullptr, IDI_APPLICATION);			// ȡӦ�ó���Ĭ�Ϲ��
		wndClass.hIcon	= LoadIcon(nullptr, IDC_ICON);						// ȡĬ��ͼ��
		wndClass.hInstance = hInstance;
		wndClass.lpfnWndProc = D3D11RenderSystem::WndProc;
		wndClass.lpszClassName = "D3D11RenderWindow";
		wndClass.lpszMenuName = "";
		wndClass.style = 0;		// Ĭ�ϸ�ʽ

		// ע�ᴰ����
		RegisterClass(&wndClass);

		HWND hwnd = CreateWindow("D3D11RenderWindow", "Dream", WS_VISIBLE | WS_OVERLAPPEDWINDOW, 
			50, 50, width, height, nullptr, nullptr, hInstance, 0);
		if(hwnd == 0)
		{
			DRE_EXCEPT(DRE_EXCEPTION_INTERNAL_ERROR, "��������ʧ��", 
				"D3D11RenderSystem::CreateRenderWindow");
		}

		DXGI_SWAP_CHAIN_DESC swapChainDesc = {0};
		swapChainDesc.BufferCount = D3D11_DOUBLE_SWAP_BUFFER;
		swapChainDesc.BufferDesc.Format = D3D11_RENDER_TARGET_FORMAT;
		swapChainDesc.BufferDesc.Height = height;
		swapChainDesc.BufferDesc.Width = width;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = D3D11_REFRESH_RATE;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 1;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;		// �����л���ȫ��
		swapChainDesc.OutputWindow = hwnd;
		swapChainDesc.SampleDesc.Count = fsaa;
		swapChainDesc.SampleDesc.Quality = fassQuality;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.Windowed = !isFullScreen;

		IDXGIFactoryPtr dxgiFactory;
		// dxgiFactory->AddRef
		HRESULT hr = CreateDXGIFactory1(IID_IDXGIFactory, (void**)dxgiFactory.GetReference());
		D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateRenderWindow");


		IDXGISwapChainPtr dxgiSwapChain;
		// dxgiSwapChain->AddRef
		hr = dxgiFactory->CreateSwapChain(mD3D11Device.Get(), &swapChainDesc, dxgiSwapChain.GetReference());
		D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateRenderWindow");

		ID3D11Texture2DPtr backBuffer;
		// backBuffer->AddRef
		hr = dxgiSwapChain->GetBuffer(0, IID_ID3D11Texture2D, (void**)backBuffer.GetReference());
		D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateRenderWindow");

		// ȡbackBuffer����
		D3D11_TEXTURE2D_DESC backBufferDesc = {0};
		backBuffer->GetDesc(&backBufferDesc);

		D3D11_RENDER_TARGET_VIEW_DESC renderTargetDesc;
		ZeroMemory(&renderTargetDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
		renderTargetDesc.Format = backBufferDesc.Format;
		if(swapChainDesc.SampleDesc.Count > 1)
		{
			renderTargetDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
		}
		else
		{
			renderTargetDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			renderTargetDesc.Texture2D.MipSlice = 0;
		}

		ID3D11RenderTargetViewPtr d3dRenderTarget;
		// d3dRenderTarget->AddRef
		hr = mD3D11Device->CreateRenderTargetView(backBuffer.Get(), &renderTargetDesc,
			d3dRenderTarget.GetReference());
		D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateRenderWindow");

		ID3D11DepthStencilViewPtr d3dDepthStencil;
		if(hasDepth || hasStencil)
		{
			// depthStencil�Ķ�ȡ��־
			u32 flag = 0;
			// Depthλ��
			u32 depthBits = 0;

			D3D11_TEXTURE2D_DESC depthStencilTextureDesc = backBufferDesc;
			depthStencilTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			if(hasDepth && !hasStencil)
			{
				depthStencilTextureDesc.Format = DXGI_FORMAT_D32_FLOAT;
				flag = D3D11_DSV_READ_ONLY_DEPTH;
				depthBits = 32;
			}
			else if(!hasDepth && hasStencil)
			{
				depthStencilTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
				flag = D3D11_DSV_READ_ONLY_STENCIL;
				depthBits = 32;
			}
			else // if(hasDepth && HasStencilBuffer())
			{
				depthStencilTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
				flag = 0;
			}

			ID3D11Texture2DPtr depthStencilTexture;
			// depthStencilTexture->AddRef
			hr = mD3D11Device->CreateTexture2D(&depthStencilTextureDesc, nullptr, 
				depthStencilTexture.GetReference());
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateRenderWindow");

			D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilDesc;
			ZeroMemory(&depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
			depthStencilDesc.Format = depthStencilTextureDesc.Format;
			if(depthStencilTextureDesc.SampleDesc.Count > 1)
			{
				depthStencilDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
			}
			else
			{
				depthStencilDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
				depthStencilDesc.Texture2D.MipSlice = 0;
			}
			depthStencilDesc.Flags = flag;
			
			// d3dDepthStencil->AddRef
			hr = mD3D11Device->CreateDepthStencilView(depthStencilTexture.Get(), &depthStencilDesc,
				d3dDepthStencil.GetReference());
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateRenderWindow");
		}

		return std::move(RenderWindowPtr(
			new D3D11RenderWindow(
			dxgiSwapChain, hwnd, mD3D11Device, d3dRenderTarget,
			d3dDepthStencil, width, height, isFullScreen,
			hasDepth, hasStencil, fsaa, fassQuality
			)
		));
	}

	/** ����һ��RenderTarget
	* @param		/		width			��ȾĿ����
	* @param		/		height			��ȾĿ��߶�
	* @param	optional	hasDepth		�Ƿ�ʹ����Ȼ���
	* @param	optional	hasStencil		�Ƿ�ʹ��ģ�建��
	* @param	optional	fsaa			��������
	* @param	optional	fassQuality		��������
	*/
	RenderTargetPtr D3D11RenderSystem::CreateRenderTarget(u32 width, u32 height, bool hasDepth /* = false */,
		bool hasStencil /* = false */, u32 fsaa /* = 1 */, u32 fassQuality /* = 0 */)
	{
		ID3D11Texture2DPtr renderTexture;

		// ȡrenderTexture����
		D3D11_TEXTURE2D_DESC renderTextureDesc = {0};
		renderTextureDesc.Width = width;
		renderTextureDesc.Height = height;
		renderTextureDesc.ArraySize = 1;
		renderTextureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		renderTextureDesc.CPUAccessFlags = 0;
		renderTextureDesc.Format = D3D11_RENDER_TARGET_FORMAT;
		renderTextureDesc.MipLevels = 0;
		renderTextureDesc.MiscFlags = 0;
		renderTextureDesc.SampleDesc.Count = fsaa;
		renderTextureDesc.SampleDesc.Quality = fassQuality;
		renderTextureDesc.Usage = D3D11_USAGE_DEFAULT;

		// renderTexture->AddRef
		HRESULT hr = mD3D11Device->CreateTexture2D(&renderTextureDesc, 0, renderTexture.GetReference());
		D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateRenderTarget");

		// ȡrenderTarget����
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetDesc;
		ZeroMemory(&renderTargetDesc, sizeof(D3D11_RENDER_TARGET_VIEW_DESC));
		renderTargetDesc.Format = renderTextureDesc.Format;
		if(renderTextureDesc.SampleDesc.Count > 1)
		{
			renderTargetDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;
		}
		else
		{
			renderTargetDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			renderTargetDesc.Texture2D.MipSlice = 0;
		}

		ID3D11RenderTargetViewPtr d3dRenderTarget;
		// d3dRenderTarget->AddRef
		hr = mD3D11Device->CreateRenderTargetView(renderTexture.Get(), &renderTargetDesc,
			d3dRenderTarget.GetReference());
		D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateRenderTarget");

		ID3D11DepthStencilViewPtr d3dDepthStencil;
		if(hasDepth || hasStencil)
		{
			DXGI_FORMAT depthStencilFormat = DXGI_FORMAT_UNKNOWN;
			u32 flag = 0;
			if (hasDepth && !hasStencil)
			{
				depthStencilFormat = DXGI_FORMAT_D32_FLOAT;
				flag = D3D11_DSV_READ_ONLY_DEPTH;
			}
			if (!hasDepth && hasStencil)
			{
				depthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
				flag = D3D11_DSV_READ_ONLY_STENCIL;
			}
			else // if(hasDepth && hasStencil)
			{
				depthStencilFormat = DXGI_FORMAT_D24_UNORM_S8_UINT;
				flag = 0;
			}

			D3D11_TEXTURE2D_DESC depthStencilTextureDesc = {0};
			depthStencilTextureDesc.Usage = D3D11_USAGE_DEFAULT;
			depthStencilTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			depthStencilTextureDesc.CPUAccessFlags = 0;
			depthStencilTextureDesc.ArraySize = 0;
			depthStencilTextureDesc.Format = depthStencilFormat;
			depthStencilTextureDesc.Height = height;
			depthStencilTextureDesc.Width = width;
			depthStencilTextureDesc.MipLevels = 0;
			depthStencilTextureDesc.MiscFlags = 0;
			depthStencilTextureDesc.SampleDesc = renderTextureDesc.SampleDesc;

			// renderTexture->AddRef
			HRESULT hr = mD3D11Device->CreateTexture2D(&renderTextureDesc, 0,
				renderTexture.GetReference());
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateRenderTarget");


			// ����depthStencil����
			D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilDesc;
			ZeroMemory( &depthStencilDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC) );
			depthStencilDesc.Format = depthStencilFormat;
			if(depthStencilTextureDesc.SampleDesc.Count > 1)
				depthStencilDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
			else
			{
				depthStencilDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
				depthStencilDesc.Texture2D.MipSlice = 0;
			}

			// d3dDepthStencil->AddRef
			hr = mD3D11Device->CreateDepthStencilView(renderTexture.Get(), &depthStencilDesc,
				d3dDepthStencil.GetReference());
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateRenderTarget");

		}
		
		return std::move(RenderTargetPtr (
			new D3D11RenderTarget(
				d3dRenderTarget, d3dDepthStencil, mD3D11Device,
				width, height, hasDepth, hasStencil, fsaa, fassQuality
			)
		));
	}

	/** ����һ��Texture
	* @param		/		image					���������õ�ͼƬ
	* @param		/		usage					�����ڴ�ʹ�ñ�־
	* @param	optional	isTransparentFigure		�Ƿ�͸��ͨ��ͼ
	* @param	optional	fsaa					��������
	* @param	optional	fassQuality				��������
	* @param	optional	gamma					gammaУ��ֵ
	*/
	TexturePtr D3D11RenderSystem::CreateTextureFromImage(ImagePtr image, DRE_BUFFER_USAGE usage, 
		bool isTransparentFigure /* = false */, u32 fsaa /* = 1 */,
		u32 fsaaQuality /* = 0 */, f32 gamma /* = 1.0f */)
	{

		DRE_PIXEL_FORMAT closesetFormat = image->GetPixelFormat();
		u32 textureSize = image->GetSize();
		const u8* subResource = image->GetDataPtr();
		u8Array autoDelete(0);
		DXGI_FORMAT supportedFormat = D3D11RenderMapping::Get(image->GetPixelFormat());
		
		// �粻��ֱ��ת��ͼƬ��D3D11֧�ֵ����ظ�ʽ
		if (supportedFormat == DRE_PIXEL_FORMAT_UNKNOWN)
		{
			// ȡ��ӽ�Դ���ص�D3D11֧������
			closesetFormat = 
				D3D11RenderMapping::GetClosestSupportFormat(image->GetPixelFormat());
			// ����ת��������ݳ���
			textureSize = image->GetWidth() * image->GetHeight() *
				PixelUtil::GetPixelFormatBpp(closesetFormat);
			// ���·���ռ�
			autoDelete->resize(textureSize);
			// ת��ͼƬ���ظ�ʽ����ӽ���֧�ָ�ʽ
			PixelUtil::Convert((u8*)image->GetDataPtr(), image->GetPixelFormat(), image->GetPixelNums(),
				&autoDelete[0], closesetFormat);
			subResource = &autoDelete[0];
			
			supportedFormat = D3D11RenderMapping::Get(closesetFormat);
		}

		// ���������Gammaֵ�������GammaУ��
		if (!Float::IsEqual(gamma, 1.0f))
		{
			// ��û�����·���ռ�
			if (subResource == image->GetDataPtr())
			{
				autoDelete->resize(image->GetSize());
				memcpy(&autoDelete[0], image->GetDataPtr(), image->GetSize());
			}

			PixelUtil::ApplyGamma(autoDelete, closesetFormat, textureSize, gamma);

			subResource = &autoDelete[0];
		}

		// �����������
		D3D11_TEXTURE2D_DESC textureDesc = {0};
		textureDesc.Width = image->GetWidth();
		textureDesc.Height = image->GetHeight();
		textureDesc.ArraySize = 1;
		// ����D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE����GenerateMips
		textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = D3D11RenderMapping::GetCPUAccess(usage);
		textureDesc.Format = supportedFormat;
		// �粻��miplevel = 1���ⲻ�ܳ�ʼ��mutilsamplerTexture����Ҫ������ṩmip����
		textureDesc.MipLevels = 1;
		textureDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;
		textureDesc.SampleDesc.Count = fsaa;
		textureDesc.SampleDesc.Quality = fsaaQuality;
		textureDesc.Usage = D3D11RenderMapping::Get(usage);

		// ������������
		D3D11_SUBRESOURCE_DATA textureData = {0};
		textureData.pSysMem = subResource;
		// ע������Ҫ��������ֽڶ�������Ϊ��λ�Ŀ�ȣ�
		textureData.SysMemPitch = image->GetWidth() * PixelUtil::GetPixelFormatBpp(closesetFormat) / 8;

		ID3D11Texture2DPtr d3dTexture;
		// texture->AddRef
		HRESULT hr = mD3D11Device->CreateTexture2D(&textureDesc, &textureData, d3dTexture.GetReference());
		D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateTextureFromImage");

		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceDesc;
		ZeroMemory(&shaderResourceDesc, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		shaderResourceDesc.Format = textureDesc.Format;
		if (textureDesc.SampleDesc.Count > 1)
		{
			shaderResourceDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
		}
		else
		{
			shaderResourceDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			shaderResourceDesc.Texture2D.MipLevels = textureDesc.MipLevels;
			shaderResourceDesc.Texture2D.MostDetailedMip = 0;
		}
		
		ID3D11ShaderResourceViewPtr d3dShaderResource;
		// d3dShaderResource->AddRef
		hr = mD3D11Device->CreateShaderResourceView(d3dTexture.Get(), &shaderResourceDesc,
			d3dShaderResource.GetReference());
		D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateTextureFromImage");

		// �Զ�����mip����ֻ��ΪshaderResource����
		mD3D11Context->GenerateMips(d3dShaderResource.Get());

		return std::move(TexturePtr (
			new D3D11Texture( 
				d3dTexture, d3dShaderResource, mD3D11Device,
				textureSize, usage, isTransparentFigure, 
				fsaa, fsaaQuality, gamma
			)
		));
	}

	TexturePtr D3D11RenderSystem::CreateTextureFromFile(
		const char* fileName, DRE_BUFFER_USAGE usage, bool isTransparentFigure /* = false */,
		u32 fsaa /* = 1 */, u32 fsaaQuality /* = 0 */, f32 gamma /* = 1.0f */)
	{
		ImagePtr image = ImageLoader::GetInstance().Load(fileName);

		return std::move(this->CreateTextureFromImage(image, usage, isTransparentFigure, fsaa,
			fsaaQuality, gamma));
	}

	HardwareVertexBufferPtr D3D11RenderSystem::CreateHardwareVertexBuffer(
		const u8Array data, u32 vertexSize, u32 numVertices,
		DRE_PRIMITIVE_TOPOLOGY primitive,
		DRE_BUFFER_USAGE usage, bool haSinstanceData /* = false */, u32 instanceDataStepRate /* = 0 */)
	{
		D3D11_BUFFER_DESC bufferDesc = {0};
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.ByteWidth = vertexSize * numVertices;
		bufferDesc.CPUAccessFlags = D3D11RenderMapping::GetCPUAccess(usage);
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;
		bufferDesc.Usage = D3D11RenderMapping::Get(usage);

		D3D11_SUBRESOURCE_DATA bufferData = {0};
		bufferData.pSysMem = &data[0];

		ID3D11BufferPtr vertexBuffer;
		// vertexBuffer->AddRef
		HRESULT hr = mD3D11Device->CreateBuffer(&bufferDesc, &bufferData, vertexBuffer.GetReference());
		D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateHardwareVertexBuffer");

		return std::move(HardwareVertexBufferPtr(
			new D3D11HardwareVertexBuffer(
			vertexBuffer, mD3D11Device, vertexSize, numVertices,
			primitive,
			usage, haSinstanceData, instanceDataStepRate
			)
		));
	}

	HardwareVertexBufferPtr D3D11RenderSystem::CreateHardwareVertexBuffer(
		ReadBufferPtr readBuffer,
		u32 vertexSize, u32 numVertices,
		DRE_PRIMITIVE_TOPOLOGY primitive,
		DRE_BUFFER_USAGE usage, 
		bool haSinstanceData /* = false */, u32 instanceDataStepRate /* = 0 */)
	{
		u8Array tempData(readBuffer->Size());
		readBuffer->Read(tempData, readBuffer->Size());

		return std::move(
			this->CreateHardwareVertexBuffer(
			tempData, vertexSize, numVertices,
			primitive,
			usage, haSinstanceData, instanceDataStepRate));
	}

	/** ��readBuffer�ж�ȡ����������HardwareIndexBuffer
	* @param		readBuffer			�ɶ�ȡ������
	* @param		vertexSize			�����С
	*/
	HardwareIndexBufferPtr D3D11RenderSystem::CreateHardwareIndexBuffer(ReadBufferPtr readBuffer,
		DRE_INDEX_ELEMENT_TYPE type, u32 numIndices, DRE_BUFFER_USAGE usage)
	{
		u8Array tempData(readBuffer->Size());
		readBuffer->Read(tempData, readBuffer->Size());

		return std::move(this->CreateHardwareIndexBuffer(tempData, type,
			numIndices, usage));
	}

	/** CreateHardwareIndexBuffer�ľ���ʵ��
	*/
	HardwareIndexBufferPtr D3D11RenderSystem::CreateHardwareIndexBuffer(u8Array data,
		DRE_INDEX_ELEMENT_TYPE type, u32 numIndices, DRE_BUFFER_USAGE usage)
	{
		D3D11_BUFFER_DESC bufferDesc = {0};
		bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bufferDesc.ByteWidth = (u32)type * numIndices;
		bufferDesc.CPUAccessFlags = D3D11RenderMapping::GetCPUAccess(usage);
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;
		bufferDesc.Usage = D3D11RenderMapping::Get(usage);

		D3D11_SUBRESOURCE_DATA bufferData = {0};
		bufferData.pSysMem = &(*data)[0];

		ID3D11BufferPtr indexBuffer;
		// indexBuffer->AddRef
		HRESULT hr = mD3D11Device->CreateBuffer(&bufferDesc, &bufferData, indexBuffer.GetReference());
		D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateHardwareVertexBufferindexBuffer");

		return std::move(HardwareIndexBufferPtr(
			new D3D11HardwareIndexBuffer(
				indexBuffer, mD3D11Device, type, numIndices,
				usage
			)
		));
	}

	/** �Ӷ�ȡ���м���HLSLProgram
	*/
	ShaderPtr D3D11RenderSystem::CreateShader(ReadBufferPtr readBuffer, const DRE_SHADER_DESC& desc)
	{
	//	u8Array tempData(readBuffer->Size());
	//	readBuffer->Read(tempData, readBuffer->Size());

	//	ID3D10BlobPtr vertexShaderBlob;
	//	// ����vertexshader
	//	ID3D11VertexShaderPtr vertexShader;
	//	ID3D11ShaderReflectionPtr vertexShaderReflect;
	//	if (desc.VS_EntryPoint)
	//	{
	//		vertexShaderBlob = this->CreateShaderFromMemory(&tempData[0],
	//			readBuffer->Size(), desc.VS_EntryPoint, desc.VS_Verson);
	//		HRESULT hr = mD3D11Device->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), 
	//			vertexShaderBlob->GetBufferSize(), nullptr, vertexShader.GetReference());
	//		D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateHLSLProgram");
	//		hr = D3DReflect(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(),
	//			IID_ID3D11ShaderReflection, (void**)vertexShaderReflect.GetReference());
	//		D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateHLSLProgram");
	//	}
	//	// ����domainshader
	//	ID3D11DomainShaderPtr domainShader;
	//	ID3D11ShaderReflectionPtr domainShaderReflect;
	//	if (desc.DS_EntryPoint)
	//	{
	//		ID3D10BlobPtr shaderBlob = this->CreateShaderFromMemory(&tempData[0],
	//			readBuffer->Size(), desc.DS_EntryPoint, desc.DS_Verson);
	//		HRESULT hr = mD3D11Device->CreateDomainShader(shaderBlob->GetBufferPointer(), 
	//			shaderBlob->GetBufferSize(), nullptr, domainShader.GetReference());
	//		D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateHLSLProgram");
	//		hr = D3DReflect(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(),
	//			IID_ID3D11ShaderReflection, (void**)domainShaderReflect.GetReference());
	//		D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateHLSLProgram");
	//	}
	//	// ����hullshader
	//	ID3D11HullShaderPtr hullShader;
	//	ID3D11ShaderReflectionPtr hullShaderReflect;
	//	if (desc.HS_EntryPoint)
	//	{
	//		ID3D10BlobPtr shaderBlob = this->CreateShaderFromMemory(&tempData[0],
	//			readBuffer->Size(), desc.HS_EntryPoint, desc.HS_Verson);
	//		HRESULT hr = mD3D11Device->CreateHullShader(shaderBlob->GetBufferPointer(), 
	//			shaderBlob->GetBufferSize(), nullptr, hullShader.GetReference());
	//		D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateHLSLProgram");
	//		hr = D3DReflect(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(),
	//			IID_ID3D11ShaderReflection, (void**)hullShaderReflect.GetReference());
	//		D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateHLSLProgram");
	//	}
	//	// ����geometryshader
	//	ID3D11GeometryShaderPtr geometryShader;
	//	ID3D11ShaderReflectionPtr geometryShaderReflect;
	//	if (desc.GS_EntryPoint)
	//	{
	//		ID3D10BlobPtr shaderBlob = this->CreateShaderFromMemory(&tempData[0],
	//			readBuffer->Size(), desc.GS_EntryPoint, desc.GS_Verson);
	//		HRESULT hr = mD3D11Device->CreateGeometryShader(shaderBlob->GetBufferPointer(), 
	//			shaderBlob->GetBufferSize(), nullptr, geometryShader.GetReference());
	//		D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateHLSLProgram");
	//		hr = D3DReflect(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(),
	//			IID_ID3D11ShaderReflection, (void**)geometryShaderReflect.GetReference());
	//		D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateHLSLProgram");
	//	}
	//	// ����pixelshader
	//	ID3D11PixelShaderPtr pixelShader;
	//	ID3D11ShaderReflectionPtr pixelShaderReflect;
	//	if (desc.PS_EntryPoint)
	//	{
	//		ID3D10BlobPtr shaderBlob = this->CreateShaderFromMemor(&tempData[0],
	//			readBuffer->Size(), desc.PS_EntryPoint, desc.PS_Verson);
	//		HRESULT hr = mD3D11Device->CreatePixelShader(shaderBlob->GetBufferPointer(), 
	//			shaderBlob->GetBufferSize(), nullptr, pixelShader.GetReference());
	//		D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateHLSLProgram");
	//		hr = D3DReflect(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(),
	//			IID_ID3D11ShaderReflection, (void**)pixelShaderReflect.GetReference());
	//		D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateHLSLProgram");
	//	}

	//	return HLSLProgramPtr(
	//		new D3D11HLSLProgram(
	//			vertexShaderBlob, 
	//			vertexShader, vertexShaderReflect,
	//			domainShader, domainShaderReflect,
	//			hullShader, hullShaderReflect, 
	//			geometryShader, geometryShaderReflect,
	//			pixelShader, pixelShaderReflect
	//			)
	//		);
		return nullptr;
	}

	/** ���ļ��м���HLSLProgram
	*/
	ShaderPtr D3D11RenderSystem::CreateShader(const DRE_SHADER_DESC& desc)
	{
		ID3D10BlobPtr vertexShaderBlob;
		// ����vertexshader
		ID3D11VertexShaderPtr vertexShader;
		ID3D11ShaderReflectionPtr vertexShaderReflect;
		if (desc.VS_EntryPoint)
		{
			DreAssert(desc.VS_File && desc.VS_EntryPoint && desc.VS_Verson,
				"HLSL��������");

			vertexShaderBlob = std::move(this->CreateShaderFromFile(desc.VS_File,
				desc.VS_EntryPoint, desc.VS_Verson));
			HRESULT hr = mD3D11Device->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), 
				vertexShaderBlob->GetBufferSize(), nullptr, vertexShader.GetReference());
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateHLSLProgram");
			hr = D3DReflect(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(),
				IID_ID3D11ShaderReflection, (void**)vertexShaderReflect.GetReference());
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateHLSLProgram");
		}
		// ����domainshader
		ID3D11DomainShaderPtr domainShader;
		ID3D11ShaderReflectionPtr domainShaderReflect;
		if (desc.DS_EntryPoint)
		{
			DreAssert(desc.DS_File && desc.DS_EntryPoint && desc.DS_Verson,
				"HLSL��������");

			ID3D10BlobPtr shaderBlob = std::move(this->CreateShaderFromFile(desc.DS_File,
				desc.DS_EntryPoint, desc.DS_Verson));
			HRESULT hr = mD3D11Device->CreateDomainShader(shaderBlob->GetBufferPointer(), 
				shaderBlob->GetBufferSize(), nullptr, domainShader.GetReference());
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateHLSLProgram");
			hr = D3DReflect(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(),
				IID_ID3D11ShaderReflection, (void**)domainShaderReflect.GetReference());
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateHLSLProgram");
		}
		// ����hullshader
		ID3D11HullShaderPtr hullShader;
		ID3D11ShaderReflectionPtr hullShaderReflect;
		if (desc.HS_EntryPoint)
		{
			DreAssert(desc.HS_File && desc.HS_EntryPoint && desc.HS_Verson,
				"HLSL��������");

			ID3D10BlobPtr shaderBlob = std::move(this->CreateShaderFromFile(desc.HS_File,
				desc.HS_EntryPoint, desc.HS_Verson));
			HRESULT hr = mD3D11Device->CreateHullShader(shaderBlob->GetBufferPointer(), 
				shaderBlob->GetBufferSize(), nullptr, hullShader.GetReference());
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateHLSLProgram");
			hr = D3DReflect(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(),
				IID_ID3D11ShaderReflection, (void**)hullShaderReflect.GetReference());
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateHLSLProgram");
		}
		// ����geometryshader
		ID3D11GeometryShaderPtr geometryShader;
		ID3D11ShaderReflectionPtr geometryShaderReflect;
		if (desc.GS_EntryPoint)
		{
			DreAssert(desc.GS_File && desc.GS_EntryPoint && desc.GS_Verson,
				"HLSL��������");

			ID3D10BlobPtr shaderBlob = std::move(this->CreateShaderFromFile(desc.GS_File,
				desc.GS_EntryPoint, desc.GS_Verson));
			HRESULT hr = mD3D11Device->CreateGeometryShader(shaderBlob->GetBufferPointer(), 
				shaderBlob->GetBufferSize(), nullptr, geometryShader.GetReference());
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateHLSLProgram");
			hr = D3DReflect(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(),
				IID_ID3D11ShaderReflection, (void**)geometryShaderReflect.GetReference());
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateHLSLProgram");
		}
		// ����pixelshader
		ID3D11PixelShaderPtr pixelShader;
		ID3D11ShaderReflectionPtr pixelShaderReflect;
		if (desc.PS_EntryPoint)
		{
			DreAssert(desc.PS_File && desc.PS_EntryPoint && desc.PS_Verson,
				"HLSL��������");

			ID3D10BlobPtr shaderBlob = std::move(this->CreateShaderFromFile(desc.PS_File,
				desc.PS_EntryPoint, desc.PS_Verson));
			HRESULT hr = mD3D11Device->CreatePixelShader(shaderBlob->GetBufferPointer(), 
				shaderBlob->GetBufferSize(), nullptr, pixelShader.GetReference());
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateHLSLProgram");
			hr = D3DReflect(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(),
				IID_ID3D11ShaderReflection, (void**)pixelShaderReflect.GetReference());
			D3D11_IF_FAILED_THROW(hr, "D3D11RenderSystem::CreateHLSLProgram");
		}

		return std::move(D3D11ShaderPtr(
			new D3D11Shader(
				vertexShaderBlob, 
				vertexShader, vertexShaderReflect,
				domainShader, domainShaderReflect,
				hullShader, hullShaderReflect, 
				geometryShader, geometryShaderReflect,
				pixelShader, pixelShaderReflect
				)
			));
	}

	ID3D10BlobPtr D3D11RenderSystem::CreateShaderFromFile(const c8* shaderFile, const c8* shaderName, 
		const c8* shaderVerson)
	{
		// ������������粻���þ�����뵹��һ��
		u32 shaderFlag = D3D10_SHADER_PACK_MATRIX_COLUMN_MAJOR;
#		if defined(DEBUG) || defined(_DEBUG)
			// ����״̬�£�Ҫ��shader����Debug��Ϣ���������Ż�����shader�������ٶ���죩
			shaderFlag |= D3D10_SHADER_DEBUG;
			shaderFlag |= D3D10_SHADER_SKIP_OPTIMIZATION;
#		else
			// release�汾��ʹ����߼����Ż�
			shaderFlag |= D3D10_SHADER_OPTIMIZATION_LEVEL3;
#		endif

		ID3D10BlobPtr shaderBlob;
		ID3D10BlobPtr errorBlob;
		HRESULT temp = 0;
		HRESULT hr = D3DX11CompileFromFile(shaderFile,
			nullptr, nullptr, shaderName, shaderVerson,
			shaderFlag, 0, nullptr, shaderBlob.GetReference(),
			errorBlob.GetReference(), &temp);
		if (FAILED(hr))
		{
			DRE_EXCEPT(DRE_EXCEPTION_RENDERINGAPI_ERROR, (c8*)errorBlob->GetBufferPointer(),
				"D3D11RenderSystem::CreateShaderFromMemory");
		}

		return shaderBlob;
	}

	/** ���ļ��м���HLSLProgram
	*/
	D3D11ShaderPtr CreateHLSLProgram(const c8* fileName);

#pragma endregion

	LRESULT CALLBACK D3D11RenderSystem::WndProc( HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
	{
		switch( uMsg )
		{
		case WM_DESTROY :
			PostQuitMessage( 0 );
			break;
		}

		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

}	// end namespace dream