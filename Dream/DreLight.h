#ifndef __DRELIGHT_H__
#define __DRELIGHT_H__

#include "DreRenderDeclaration.h"

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

	class Light
	{
	public:
		/** ���캯�� */
		Light( LightDesc desc );

		/** ���ù�Դ���� */
		void ResetLight( LightDesc desc );

		/** ȡ�ù�Դ�������� */
		LightDesc GetLightDesc();

	/// ���й�Դ��������
		/** ȡ��������ɫ */
		Color GetAmbientColor();

		/** ���û�������ɫ */
		void SetAmbientColor( Color Color );

		/** ȡ�������ɫ */
		Color GetDiffuseColor();

		/** �����������ɫ */
		void SetDiffuseColor( Color Color );

		/** ȡ�������ɫ */
		Color GetSpecularColor();

		/** ���÷������ɫ */
		void SetSpecularColor( Color Color );

		/** ȡ�ó���˥�� */
		f32 GetAttenuationConst();

		/** ���ó���˥�� */
		void SetAttenuationConst( f32 attenuation );

		/** ȡ������˥�� */
		f32 GetmAttenuationLinear();

		/** ��������˥�� */
		void SetmAttenuationLinear( f32 attenuation );

		/** ȡ�ö���˥�� */
		f32 GetAttenuationQuad();

		/** ���ö���˥�� */
		void SetAttenuationQuad( f32 attenuation );

		/** ȡ�ù��շ�Χ�뾶 */
		f32 GetLightRadius();

		/** ���ù��շ�Χ�뾶 */
		void SetLightRadius( f32 radius );

		/** ȡ�ù������� */
		E_LIGHTTYPE GetLightType();

	/// ר���ھ۹�ƹ�Դ���Ǿ۹�ƹ�Դʹ�ûᴥ������
		/** ȡ�þ۹����� */
		f32 GetOuterCone();

		/** ���þ۹����� */
		void SetOuterCone( f32 outerCone );

		/** ȡ�þ۹���ڽ� */
		f32 GetInnerCone();

		/** ���þ۹���ڽ� */
		void SetInnerCone( f32 innerCone );

		/** ȡ�þ۹�ƵĹ�ǿ�½����� */
		f32 GetFalloff();

		/** ���þ۹�ƵĹ�ǿ�½����� */
		void SetFalloff( f32 falloff );

	/// ר���ڵ��Դ���ǵ��Դʹ�ûᴥ������
		/** ȡ�ù�Դλ�� */
		Vector3 GetPosition();

		/** ���ù�Դλ�� */
		void GetPosition( Vector3 position );

	/// ר����ƽ�й�Դ����ƽ�й�Դʹ�ûᴥ������
		/** ȡ�ù�Դ���� */
		Vector3 GetDirection();

		/** ���ù�Դ���� */
		void GetDirection( Vector3 direction );

	private:
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

		/// ��������
		E_LIGHTTYPE mType;
	};

}	// end namespace dream  

#endif	// end of __DRELIGHT_H__