#ifndef __DRED3D11COMPTR_H__
#define __DRED3D11COMPTR_H__

namespace dream
{

#define SafeAddRef(ptr)			if(ptr) { ptr->AddRef(); }
#define SafeRelease(ptr)		if(ptr) { ptr->Release(); ptr = nullptr; }
#define SafaDelete(ptr)			if(ptr) { delete ptr; ptr = nullptr; }
#define SafeDeleteArray(ptr)	if(ptr) { delete [] ptr; ptr = nullptr; }

	template<class T>
	class D3D11ComPtr final
	{
	public:
		/** ֻ��ʹ��Ĭ�Ϲ��캯�����󶨿�ָ��
		*/
		explicit D3D11ComPtr() : mPtr(nullptr) {}

		~D3D11ComPtr() { SafeRelease(mPtr); }

		D3D11ComPtr<T>& operator = (const D3D11ComPtr<T>& rh)
		{
			// ˳���ܷ�
			SafeAddRef(rh.mPtr);
			SafeRelease(mPtr);
			mPtr = rh.mPtr;;

			return *this;
		}

		D3D11ComPtr(const D3D11ComPtr<T>& rh)
		{
			// ˳���ܷ�
			SafeAddRef(rh.mPtr);
			mPtr = rh.mPtr;
		}

		T* operator-> () { return mPtr; }

		T* Get() { return mPtr; }

		/** ֻ���ڿ�ָ�������²���ͨ��GetReference���ָ��
		*/
		T** GetReference() 
		{ 
			DreAssert(mPtr == nullptr, "ֻ�е�Com����ָ��Ϊ��ָ��ʱ����ȥ����Դָ������");

			return &mPtr;
		}

		void Swap(D3D11ComPtr<T>& rh)
		{
			T* temp = rh.mPtr;
			rh.mPtr = mPtr;
			mPtr = temp;
		}

		void Reset(T* ptr) 
		{ 
			if (ptr == mPtr)
				return;

			SafeRelease(mPtr);
			mPtr = ptr;
		}

		bool operator == (D3D11ComPtr<T> rh) const {
			return mPtr == rh.mPtr
		}
		bool operator == (T* rh) const {
			return mPtr == rh;
		}
		bool operator != (D3D11ComPtr<T> rh) const {
			return mPtr != rh.mPtr;
		}
		bool operator != (T* rh) const {
			return mPtr != rh;
		}

	private:
		T* mPtr;
	};


}	// end namespace dream

#endif	// end __DRED3D11COMPTR_H__