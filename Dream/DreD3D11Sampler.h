///////////////////////////////////
// date: 2014/9/3 10:26
// author: zoulei
///////////////////////////////////

#ifndef __DRED3D11SAMPLER_H__
#define __DRED3D11SAMPLER_H__

#include "DreD3D11RenderDeclaration.h"

#include "DreSampler.h"

namespace dream
{

	class D3D11Sampler :public  Sampler
	{
	private:
		ID3D11SamplerStatePtr mSamplerState;

	public :
		D3D11Sampler(ID3D11SamplerStatePtr samplerState, SamplerDesc desc)
			: Sampler(desc), mSamplerState(samplerState)
		{
			// Áô¿Õ
		}

		ID3D11SamplerStatePtr GetSamplerState() { return mSamplerState;  }
	};

}

#endif // end of __DRED3D11SAMPLER_H__