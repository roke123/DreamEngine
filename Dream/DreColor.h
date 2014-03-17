#ifndef __DRECOLOR_H__
#define __DRECOLOR_H__

#include "DreRenderDeclaration.h"

namespace dream
{

	class DRE_EXPORT_CLASS Color
	{
	public:
		/// ��ɫ����
		const static Color ZERO;
		const static Color WHITE;
		const static Color BLACK;
		const static Color RED;
		const static Color GREEN;
		const static Color BLUE;

	private:
		// Ĭ��ΪFORMAT_RGBA
		union 
		{
			f32 r, g, b, a;
			f32 mColorValue[4];
		};

	public:
		Color(f32 r, f32 g, f32 b, f32 a);

		/// �Ƚ� 
		bool operator == ( const Color& c );
		bool operator != ( const Color& c );

		/// ��ɫ����
		Color operator * ( const Color& c );
		Color operator *= ( const Color& c );
		Color operator *= ( f32 fScale );

		Color operator + ( const Color& c );
		Color operator += ( const Color& c );
		Color operator += ( f32 fInc );

		friend Color operator * ( Color c, f32 fScale);
		friend Color operator + ( Color c, f32 fInc );

		/// ȡ��ɫͨ��
		f32 GetRedValue() const;
		f32 GetGreenValue () const;
		f32 GetBlueValue() const;
		f32 GetAlphaValue() const;

		void SetRedValue( f32 fRedValue );
		void SetGreenValue( f32 fGreenValue );
		void SetBlueValue( f32 fBlueValue );
		void SetAlphaValue( f32 fAlphaValue );

	};	// end class Color

}	// end namesapce dream

#endif	// end of __DRECOLOR_H__	