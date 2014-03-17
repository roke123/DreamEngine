#ifndef __DRED3D11ADAPTER_H__
#define __DRED3D11ADAPTER_H__

#include "DreD3D11RenderDeclaration.h"

#include "DreAdapter.h"

namespace dream
{

	class D3D11Adapter : public Adapter
	{
	private:
		/// D3D11�Կ��豸����
		IDXGIAdapterPtr			mAdapter;
		/// ����
		DXGI_ADAPTER_DESC		mAdapterDesc;
		/// ת�����豸����
		c8*						mDescription;
		/// ת������豸��
		c8*						mDriverName;

	public:
		D3D11Adapter(IDXGIAdapterPtr adapter);

		~D3D11Adapter();

		/** �����豸��
		* @return �豸��
		*/
		string DriverName() const override ;
		
		/** �����豸����
		* @return �豸����
		*/
		string DriverDescription() const override ;

		/** ����IDXGIAdapter
		*/
		IDXGIAdapterPtr GetDXGIAdapter() const { return mAdapter; }

	};	// end class D3D11Adapter

}	// end namespace dream

#endif	// end __DRED3D11ADAPTER_H__