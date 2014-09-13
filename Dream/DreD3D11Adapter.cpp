#include "DreD3D11Adapter.h"

#include "DreMemoryAllocatorConfig.h"

#include <Windows.h>

namespace dream
{
	D3D11Adapter::D3D11Adapter(IDXGIAdapterPtr adapter) :
		mAdapter(adapter),mDescription(nullptr), mDriverName(nullptr)
	{
		using namespace std;

		mAdapter->GetDesc(&mAdapterDesc);
		
		// ×ª»»¿í×Ö·ûµ½¶à×Ö·û
		u32 length = WideCharToMultiByte(CP_ACP, 0, mAdapterDesc.Description, wcslen(mAdapterDesc.Description),
			nullptr, 0, nullptr, nullptr);
		mDescription = DREAM_NEW c8[length + 1];
		WideCharToMultiByte(CP_ACP, 0, mAdapterDesc.Description, wcslen(mAdapterDesc.Description),
			mDescription, length, nullptr, nullptr);
		mDescription[length] = '\0';
	}

	D3D11Adapter::~D3D11Adapter()
	{
		SafeDeleteArray(mDescription);
		SafeDeleteArray(mDriverName);
	}

	string D3D11Adapter::DriverDescription() const
	{
		return string(mDescription);
	}

	string D3D11Adapter::DriverName() const
	{
		return string(mDriverName);
	}

}	// end namespace dream