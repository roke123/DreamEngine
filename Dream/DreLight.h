#ifndef __DRELIGHT_H__
#define __DRELIGHT_H__

#include "DreRenderDeclaration.h"

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

	class Light
	{
	public:
		/** 构造函数 */
		Light( LightDesc desc );

		/** 重置光源属性 */
		void ResetLight( LightDesc desc );

		/** 取得光源属性描述 */
		LightDesc GetLightDesc();

	/// 所有光源公用属性
		/** 取环境光颜色 */
		Color GetAmbientColor();

		/** 设置环境光颜色 */
		void SetAmbientColor( Color Color );

		/** 取漫射光颜色 */
		Color GetDiffuseColor();

		/** 设置漫射光颜色 */
		void SetDiffuseColor( Color Color );

		/** 取放射光颜色 */
		Color GetSpecularColor();

		/** 设置放射光颜色 */
		void SetSpecularColor( Color Color );

		/** 取得常量衰减 */
		f32 GetAttenuationConst();

		/** 设置常量衰减 */
		void SetAttenuationConst( f32 attenuation );

		/** 取得线性衰减 */
		f32 GetmAttenuationLinear();

		/** 设置线性衰减 */
		void SetmAttenuationLinear( f32 attenuation );

		/** 取得二次衰减 */
		f32 GetAttenuationQuad();

		/** 设置二次衰减 */
		void SetAttenuationQuad( f32 attenuation );

		/** 取得光照范围半径 */
		f32 GetLightRadius();

		/** 设置光照范围半径 */
		void SetLightRadius( f32 radius );

		/** 取得光线类型 */
		E_LIGHTTYPE GetLightType();

	/// 专用于聚光灯光源，非聚光灯光源使用会触发断言
		/** 取得聚光灯外角 */
		f32 GetOuterCone();

		/** 设置聚光灯外角 */
		void SetOuterCone( f32 outerCone );

		/** 取得聚光灯内角 */
		f32 GetInnerCone();

		/** 设置聚光灯内角 */
		void SetInnerCone( f32 innerCone );

		/** 取得聚光灯的光强下降幅度 */
		f32 GetFalloff();

		/** 设置聚光灯的光强下降幅度 */
		void SetFalloff( f32 falloff );

	/// 专用于点光源，非点光源使用会触发断言
		/** 取得光源位置 */
		Vector3 GetPosition();

		/** 设置光源位置 */
		void GetPosition( Vector3 position );

	/// 专用于平行光源，非平行光源使用会触发断言
		/** 取得光源方向 */
		Vector3 GetDirection();

		/** 设置光源方向 */
		void GetDirection( Vector3 direction );

	private:
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

		/// 光线类型
		E_LIGHTTYPE mType;
	};

}	// end namespace dream  

#endif	// end of __DRELIGHT_H__