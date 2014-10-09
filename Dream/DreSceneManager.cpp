#include "DreSceneManager.h"

#include "DreRenderSystem.h"

#include "DreRenderable.h"
#include "DreLight.h"
#include "DrePass.h"
#include "DreCamera.h"

namespace dream
{

	void SceneManager::RenderSingleObject(CameraPtr& camera, RenderablePtr& rend, 
		PassPtr& pass, const LightList& manualLights)
	{
		mRenderSystem->SetBlendEnable(pass->GetBlendEnable);
		if (pass->GetBlendEnable())
		{
			mRenderSystem->SetSceneColorBlending(
				pass->GetSourceBlendFactorColor(),
				pass->GetDestBlendFactorColor(),
				pass->GetSceneBlendingOperationColor());

			mRenderSystem->SetSceneAlphaBlending(
				pass->GetSourceBlendFactorAlpha(),
				pass->GetDestBlendFactorAlpha(),
				pass->GetSceneBlendingOperationAlpha());
		}

		mRenderSystem->SetCullingMode(pass->GetCullingMode());

		mRenderSystem->SetDepthBufferWriteEnabled(pass->GetDepthWriteEnabled());
		mRenderSystem->SetDepthBufferCheckEnabled(pass->GetDepthCheckEnabled());
		if (pass->GetDepthCheckEnabled())
		{
			mRenderSystem->SetDepthBias(pass->GetDepthBiasConstant(), pass->GetDepthBiasSlopeScale());
			mRenderSystem->SetDepthBiasClamp(pass->GetDepthBiasClamp());
			mRenderSystem->SetDepthBufferFunction(pass->GetDepthFunction());
		}

		RenderParamMap renderParams;
		renderParams.SetMatrix4("_WorldMatrix", rend->GetSceneNode()->GetWorldMatrix());
		renderParams.SetMatrix4("_ViewMatrix", camera->GetViewMatrix());
		renderParams.SetMatrix4("_ProjMatrix", camera->GetProjectionMatrix());

	}

}