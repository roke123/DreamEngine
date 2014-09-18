#ifndef __DRELIGHT_H__
#define __DRELIGHT_H__

#include "DreSceneManagerDeclaration.h"

#include "DreComponent.h"
#include "DreSceneNode.h"

#include "Vector3.h"
#include "DreColor.h"

namespace dream
{

	/** ������Դ���� */
	enum E_LIGHTTYPE
	{
		/// ���Դ
		E_LIGHTPOINT = 0,
		/// �۹�ƹ�Դ
		E_LIGHTSPOT = 1,
		/// ƽ�й�Դ
		E_LIGHTDIRECTIONAL = 2
	};

	///* �������͵������������ڴ���Light */
	struct DRE_EXPORT_CLASS LightDesc
	{
		/// ��������ɫ
		Color mAmbientColor;			
		/// �������ɫ(������ɫ)
		Color mDiffuseColor;		
		/// �������ɫ
		Color mSpecularColor;
		/// ��Դλ��(���ڵ��Դ)
		Vector3 Position;
		/// ��Դ����(����ƽ�й�Դ)
		Vector3 Direction;
		/// ����˥��
		f32 mAttenuationConst;
		/// ����˥��
		f32 mAttenuationLinear;
		/// ����˥��
		f32 mAttenuationQuad;
		/// �۹�Ƶ��ڽ�
		f32 OuterCone;
		/// �۹�Ƶ����
		f32 InnerCone;
		/// �۹�ƵĹ�ǿ�½�����
		f32 Falloff;
		/// ���շ�Χ�뾶
		f32 Radius;
		/// ��������
		E_LIGHTTYPE Type;
	};

	class Light : public Component
	{
	public:
		/** ���캯�� */
		Light( LightDesc desc );

		/** ���ù�Դ���� */
		void ResetLight( LightDesc desc );

		/** ȡ�ù�Դ�������� */
		LightDesc GetLightDesc() const;

		/// ���й�Դ��������
		/** ȡ��������ɫ */
		Color GetAmbientColor() const { return mAmbientColor; };
		void SetAmbientColor(Color color) { mAmbientColor = color; };

		/** ȡ�������ɫ */
		Color GetDiffuseColor() const { return mDiffuseColor; };
		void SetDiffuseColor(Color color) { mDiffuseColor = color;  };

		/** ȡ�������ɫ */
		Color GetSpecularColor() const { return; };
		void SetSpecularColor(Color color) { mSpecularColor = color; };

		/** ȡ�ó���˥�� */
		f32 GetAttenuationConst() const { return mAttenuationConst; };
		void SetAttenuationConst(f32 attenuation) { mAttenuationConst = attenuation; };

		/** ȡ������˥�� */
		f32 GetAttenuationLinear() const { return mAttenuationLinear; };
		void SetAttenuationLinear(f32 attenuation) { mAttenuationLinear = attenuation; };

		/** ȡ�ö���˥�� */
		f32 GetAttenuationQuad() const { return mAttenuationQuad; };
		void SetAttenuationQuad(f32 attenuation) { mAttenuationQuad = attenuation; };

		/** ȡ�ù��շ�Χ�뾶 */
		f32 GetLightRadius() const { return mRadius; };
		void SetLightRadius(f32 radius) { mRadius = radius; };

		/** ȡ�ù������� */
		E_LIGHTTYPE GetLightType() const { return mType; };

		/** ���ù�����Ҫ�� */
		DRE_LIGHT_IMPORTANCE GetLightImportance() const { return mImportance; }
		void SetLightImportance(DRE_LIGHT_IMPORTANCE importance) { mImportance = importance; }

		Vector3 GetPosition() { return mParentNode->_GetFinalPosition(); };

		Vector3 GetDistance() { return mParentNode->Get}

		f32 CalculateAttenFactor(f32 distance) 
		{
			f32 atten = 1.0f;

			switch (mType)
			{
			case dream::E_LIGHTPOINT:
				if (distance > mRadius)
					atten = 0.0f;
				else
				{
					atten = 1.0f / (mAttenuationConst + mAttenuationLinear * distance + mAttenuationQuad * pow(distance, 2.0f));
				}
				break;
			case dream::E_LIGHTSPOT:
				if (distance > mRadius)
					atten = 0.0f;
				else
				{
					atten = 1.0f / (mAttenuationConst + mAttenuationLinear * distance + mAttenuationQuad * pow(distance, 2.0f));
				}
				break;
			case dream::E_LIGHTDIRECTIONAL:
				atten = 1.0f;
			}
		}

		/** ���ù���ǿ�� */
		f32 GetIntensity() const { return mIntensity; }
		void SetIntensity(f32 intensity) { mIntensity = intensity; }

	/// ר���ھ۹�ƹ�Դ���Ǿ۹�ƹ�Դʹ�ûᴥ������
		/** ȡ�þ۹����� */
		f32 GetOuterCone() { return mOuterCone; };
		void SetOuterCone(f32 outerCone) { mOuterCone = outerCone; };

		/** ȡ�þ۹���ڽ� */
		f32 GetInnerCone() { return mInnerCone; };
		void SetInnerCone(f32 innerCone) { mInnerCone = innerCone; };

		/** ȡ�þ۹�ƵĹ�ǿ�½����� */
		f32 GetFalloff() { return mFalloff; };
		void SetFalloff(f32 falloff) { mFalloff = falloff; };

	private:
		/// 

		/// ��������ɫ
		Color mAmbientColor;		
	
		/// �������ɫ(������ɫ)
		Color mDiffuseColor;		

		/// �������ɫ
		Color mSpecularColor;

	/// ��ʽ��Atten = 1 / ( mAttenuationConst + mAttenuationLinear * d + mAttenuationQuad * d^2) 
		/// ����˥��
		f32 mAttenuationConst;
		/// ����˥��
		f32 mAttenuationLinear;
		/// ����˥��
		f32 mAttenuationQuad;

		/// �۹�Ƶ��ڽ�
		f32 mOuterCone;

		/// �۹�Ƶ����
		f32 mInnerCone;

		/// �۹�ƵĹ�ǿ�½�����
		f32 mFalloff;

		/// ��Դλ��(���ڵ��Դ)
		Vector3 mPosition;

		/// ��Դ����(����ƽ�й�Դ)
		Vector3 mDirection;

		/// ���շ�Χ�뾶
		f32 mRadius;

		/// ����ǿ��
		f32 mIntensity;

		/// ��������
		E_LIGHTTYPE mType;

		/// ������Ҫ��
		DRE_LIGHT_IMPORTANCE	mImportance;

		/// �ü���־
		LayerIDList				mCullingMask;
	};

}	// end namespace dream  

#endif	// end of __DRELIGHT_H__