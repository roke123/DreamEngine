#ifndef __DRED3D11ADAPTER_H__
#define __DRED3D11ADAPTER_H__

#include "DreD3D11RenderDeclaration.h"

#include "DreAdapter.h"

namespace dream
{

	class D3D11Adapter : public Adapter
	{
	private:
		/// D3D11显卡设备描述
		IDXGIAdapterPtr			mAdapter;
		/// 描述
		DXGI_ADAPTER_DESC		mAdapterDesc;
		/// 转换后设备描述
		c8*						mDescription;
		/// 转换后的设备名
		c8*						mDriverName;

	public:
		D3D11Adapter(IDXGIAdapterPtr adapter);

		~D3D11Adapter();

		/** 返回设备名
		* @return 设备名
		*/
		string DriverName() const override ;
		
		/** 返回设备描述
		* @return 设备描述
		*/
		string DriverDescription() const override ;

		/** 返回IDXGIAdapter
		*/
		IDXGIAdapterPtr GetDXGIAdapter() const { return mAdapter; }

	};	// end class D3D11Adapter

}	// end namespace dream

#endif	// end __DRED3D11ADAPTER_H__