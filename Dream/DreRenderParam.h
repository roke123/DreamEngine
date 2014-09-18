#ifndef __DRERENDERPARAM_H__
#define __DRERENDERPARAM_H__

#include "DreRenderDeclaration.h"

#include "DreMemoryAllocatorConfig.h"

namespace dream
{
	/**
	* ������Ⱦ�Ĳ���
	*/
	class DRE_EXPORT_CLASS RenderParam
	{
	public:
		enum FORMAT : u8
		{
			RP_FORMAT_FLOAT,
			RP_FORMAT_INT,
			RP_FORMAT_TEXTURE,
			RP_FORMAT_MIX
		};

	public:
		/** ���캯��
		* @param param �������Ⱦ����
		* @param size ��Ⱦ���ݳ���
		* @param isCopy �Ƿ����·����ڴ沢��������
		*/
		RenderParam(void * param, u32 sizeInByte, FORMAT format, bool isCopy = true )
			: mIsCopy(isCopy), mSizeInByte(sizeInByte), mFormat(format)
		{
			if (isCopy)
			{
				param = DREAM_MALLOC(sizeInByte);
				if(param == nullptr)
				{
					DRE_EXCEPT(DRE_EXCEPTION_OUT_OF_MEMORY, "��ʣ��ɷ����ڴ�", "RenderParam::RenderParam");
				}

				memcpy(mParam, param, sizeInByte);
			}
			else
			{
				mParam = param;
			}
		}

	private:
		RenderParam(const RenderParam&);
		RenderParam& operator = (const RenderParam&);

	public:
		/** ��������
		*/
		~RenderParam()
		{
			if(mIsCopy)
			{
				DREAM_FREE(mParam);
			}
		}

		template<class T>
		void _SetParam(const T& value)
		{
			DreAssert(sizeof(T) == mSizeInByte, "������Ⱦ�����ĳ������ʼ���Ȳ�һ��");

			if (mIsCopy)
			{
				memcpy_s(mParam, mSizeInByte, value, sizeof(T));
			}
			else
			{
				mIsCopy = true;
				mParam = DREAM_MALLOC(sizeInByte);
				if (mParam == nullptr)
				{
					DRE_EXCEPT(DRE_EXCEPTION_OUT_OF_MEMORY, "��ʣ��ɷ����ڴ�", "RenderParam::RenderParam");
				}

				memcpy_s(mParam, sizeInByte, value, sizeof(T));
			}
			
		}

		void _SetParam(void* value, u32 sizeInByte, bool isCopy = true)
		{
			DreAssert(sizeInByte == mSizeInByte, "������Ⱦ�����ĳ������ʼ���Ȳ�һ��");

			if (mIsCopy && isCopy)
			{
				// ֱ�Ӹ���
				memcpy_s(mParam, mSizeInByte, value, sizeInByte);
			}
			else if (mIsCopy && !isCopy)
			{
				DREAM_FREE(mParam);
				mParam = value;
			}
			else if (!mIsCopy && isCopy)
			{
				mIsCopy = isCopy;
				mParam = DREAM_MALLOC(sizeInByte);
				if (mParam == nullptr)
				{
					DRE_EXCEPT(DRE_EXCEPTION_OUT_OF_MEMORY, "��ʣ��ɷ����ڴ�", "RenderParam::RenderParam");
				}

				memcpy_s(mParam, sizeInByte, value, sizeInByte);
			}
			else
			{
				mParam = value;
			}
		}

		/** ȡ������ָ��
		* @return �������Ⱦ����
		*/
		template<class T>
		T* GetParamAs() const { return static_cast<T*>(mParam); }

		void* GetParam() const { return mParam; }

		u32 GetSize() const { return mSizeInByte; }

		FORMAT GetFormat() const { return mFormat; }

	private:
		/// �Ƿ�����ݽ��и��Ʊ�־
		bool		mIsCopy;
		/// ������ʽ
		FORMAT		mFormat;
		/// ��Ⱦ������
		void*		mParam;
		/// ��Ⱦ�����ݳ���
		u32			mSizeInByte;
		
	};	// end class RenderParam

	class RenderParamMap
	{
	public:
		typedef map<string, RenderParam>			RenderParamMapImp;
		typedef RenderParamMapImp::iterator			iterator;

	private:
		RenderParamMapImp							mRenderParamMap;

	private:
		template<class T, RenderParam::FORMAT _Format>
		void _SetValue(const string& name, T& value)
		{
			RenderParamMapImp::iterator ite = mRenderParamMap.find(name);
			if (ite != mRenderParamMap.end())
			{
				ite->second._SetParam(value);
			}
			else
			{
				string _name = name;
				mRenderParamMap.insert(make_pair<string, RenderParam>(
					std::move(_name),
					std::move(RenderParam(&value, sizeof(T), _Format))
					));
			}
		}

		template<class T>
		const T* _GetValue(const string& name) const
		{
			RenderParamMapImp::const_iterator ite = mRenderParamMap.find(name);
			if (ite != mRenderParamMap.end())
			{
				return ite->second.GetParamAs<T>();
			}

			return nullptr;
		}

		void _RemoveValue(const string& name)
		{
			RenderParamMapImp::const_iterator ite = mRenderParamMap.find(name);
			if (ite != mRenderParamMap.end())
			{
				mRenderParamMap.erase(ite);
			}
		}

	public:
		void SetMatrix4(const string& name, Matrix4& matrix)
		{
			_SetValue<Matrix4, RenderParam::RP_FORMAT_FLOAT>(name, matrix);
		}

		void SetMatrix4WithNull(const string& name)
		{
			_RemoveValue(name);
		}

		const Matrix4* GetMatrix4(const string& name) const
		{
			return _GetValue<Matrix4>(name);
		}

		void SetFloat(const string& name, f32& value)
		{
			_SetValue<f32, RenderParam::RP_FORMAT_FLOAT>(name, value);
		}

		void SetFloatWithNull(const string& name)
		{
			_RemoveValue(name);
		}

		const f32* GetFloat(const string& name) const
		{
			return _GetValue<f32>(name);
		}

		void SetColor(const string& name, Color color)
		{
			_SetValue<Color, RenderParam::RP_FORMAT_FLOAT>(name, color);
		}

		void SetColorWithNull(const string& name)
		{
			_RemoveValue(name);
		}

		const Color* GetColor(const string& name) const
		{
			return _GetValue<Color>(name);
		}

		void SetVector3(const string& name, Vector3& vector)
		{
			_SetValue<Vector3, RenderParam::RP_FORMAT_FLOAT>(name, vector);
		}

		void SetVector3WithNull(const string& name)
		{
			_RemoveValue(name);
		}

		const Vector3* GetVector3(const string& name) const
		{
			return _GetValue<Vector3>(name);
		}

		void SetFloat4(const string& name, f32 values[4])
		{
			RenderParamMapImp::iterator ite = mRenderParamMap.find(name);
			if (ite != mRenderParamMap.end())
			{
				ite->second._SetParam(values, sizeof(f32[4]));
			}
			else
			{
				string _name = name;
				mRenderParamMap.insert(make_pair<string, RenderParam>(
					std::move(_name),
					std::move(RenderParam(values, sizeof(f32[4]), RenderParam::RP_FORMAT_FLOAT))
					));
			}
		}

		void SetFloat4WithNull(const string& name)
		{
			_RemoveValue(name);
		}

		const f32* GetFloat4(const string& name) const
		{
			return _GetValue<f32>(name);
		}
	};

}	// end namespace dream

#endif	// end og __DREMATERIAL_H__