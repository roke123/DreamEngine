#ifndef __DRELIGHT_H__
#define __DRELIGHT_H__

#include "DreSceneManagerDeclaration.h"

#include "DreComponent.h"
#include "DreSceneNode.h"

#include "Vector3.h"
#include "DreColor.h"

namespace dream
{

	/** 描述光源类型 */
	enum E_LIGHTTYPE
	{
		/// 点光源
		E_LIGHTPOINT = 0,
		/// 聚光灯光源
		E_LIGHTSPOT = 1,
		/// 平行光源
		E_LIGHTDIRECTIONAL = 2
	};

	///* 光线类型的描述数据用于创建Light */
	struct DRE_EXPORT_CLASS LightDesc
	{
		/// 环境光颜色
		Color mAmbientColor;			
		/// 漫射光颜色(物理颜色)
		Color mDiffuseColor;		
		/// 放射光颜色
		Color mSpecularColor;
		/// 光源位置(用于点光源)
		Vector3 Position;
		/// 光源方向(用于平行光源)
		Vector3 Direction;
		/// 常量衰减
		f32 mAttenuationConst;
		/// 线性衰减
		f32 mAttenuationLinear;
		/// 二次衰减
		f32 mAttenuationQuad;
		/// 聚光灯的内角
		f32 OuterCone;
		/// 聚光灯的外角
		f32 InnerCone;
		/// 聚光灯的光强下降幅度
		f32 Falloff;
		/// 光照范围半径
		f32 Radius;
		/// 光线类型
		E_LIGHTTYPE Type;
	};

	class Light : public Component
	{
	public:
		/** 构造函数 */
		Light( LightDesc desc );

		/** 重置光源属性 */
		void ResetLight( LightDesc desc );

		/** 取得光源属性描述 */
		LightDesc GetLightDesc() const;

		/// 所有光源公用属性
		/** 取环境光颜色 */
		Color GetAmbientColor() const { return mAmbientColor; };
		void SetAmbientColor(Color color) { mAmbientColor = color; };

		/** 取漫射光颜色 */
		Color GetDiffuseColor() const { return mDiffuseColor; };
		void SetDiffuseColor(Color color) { mDiffuseColor = color;  };

		/** 取放射光颜色 */
		Color GetSpecularColor() const { return; };
		void SetSpecularColor(Color color) { mSpecularColor = color; };

		/** 取得常量衰减 */
		f32 GetAttenuationConst() const { return mAttenuationConst; };
		void SetAttenuationConst(f32 attenuation) { mAttenuationConst = attenuation; };

		/** 取得线性衰减 */
		f32 GetAttenuationLinear() const { return mAttenuationLinear; };
		void SetAttenuationLinear(f32 attenuation) { mAttenuationLinear = attenuation; };

		/** 取得二次衰减 */
		f32 GetAttenuationQuad() const { return mAttenuationQuad; };
		void SetAttenuationQuad(f32 attenuation) { mAttenuationQuad = attenuation; };

		/** 取得光照范围半径 */
		f32 GetLightRadius() const { return mRadius; };
		void SetLightRadius(f32 radius) { mRadius = radius; };

		/** 取得光线类型 */
		E_LIGHTTYPE GetLightType() const { return mType; };

		/** 设置光线重要性 */
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

		/** 设置光照强度 */
		f32 GetIntensity() const { return mIntensity; }
		void SetIntensity(f32 intensity) { mIntensity = intensity; }

	/// 专用于聚光灯光源，非聚光灯光源使用会触发断言
		/** 取得聚光灯外角 */
		f32 GetOuterCone() { return mOuterCone; };
		void SetOuterCone(f32 outerCone) { mOuterCone = outerCone; };

		/** 取得聚光灯内角 */
		f32 GetInnerCone() { return mInnerCone; };
		void SetInnerCone(f32 innerCone) { mInnerCone = innerCone; };

		/** 取得聚光灯的光强下降幅度 */
		f32 GetFalloff() { return mFalloff; };
		void SetFalloff(f32 falloff) { mFalloff = falloff; };

	private:
		/// 

		/// 环境光颜色
		Color mAmbientColor;		
	
		/// 漫射光颜色(物理颜色)
		Color mDiffuseColor;		

		/// 放射光颜色
		Color mSpecularColor;

	/// 公式：Atten = 1 / ( mAttenuationConst + mAttenuationLinear * d + mAttenuationQuad * d^2) 
		/// 常量衰减
		f32 mAttenuationConst;
		/// 线性衰减
		f32 mAttenuationLinear;
		/// 二次衰减
		f32 mAttenuationQuad;

		/// 聚光灯的内角
		f32 mOuterCone;

		/// 聚光灯的外角
		f32 mInnerCone;

		/// 聚光灯的光强下降幅度
		f32 mFalloff;

		/// 光源位置(用于点光源)
		Vector3 mPosition;

		/// 光源方向(用于平行光源)
		Vector3 mDirection;

		/// 光照范围半径
		f32 mRadius;

		/// 光照强度
		f32 mIntensity;

		/// 光线类型
		E_LIGHTTYPE mType;

		/// 光线重要性
		DRE_LIGHT_IMPORTANCE	mImportance;

		/// 裁剪标志
		LayerIDList				mCullingMask;
	};

}	// end namespace dream  

#endif	// end of __DRELIGHT_H__