#ifndef __DRED3D11TEXTURE_H__
#define __DRED3D11TEXTURE_H__

#include "DreD3D11RenderDeclaration.h"

#include "DreTexture.h"

namespace dream
{

	class D3D11Texture final : public Texture
	{
		friend class D3D11RenderSystem;
		friend class D3D11RenderWindow;
		friend class D3D11RenderTarget;
	private:
		D3D11Texture(ID3D11Texture2DPtr texture, ID3D11ShaderResourceViewPtr shaderResource,
			ID3D11DevicePtr d3dDevice, u32 sizeInByte,
			DRE_BUFFER_USAGE usage, bool isTransparentFigure = false,
			u32 fsaa = 1, u32 fsaaQuality = 0, f32 gamma = 1.0f);

	public:
		~D3D11Texture();

		/** ���������ɶ�����Image
		*/
		ImagePtr ExportAsImage() override;

		/** ������������ʵ�ַ���
		* @param offset �����������Ŀ�ʼ��ƫ��
		* @param length ��������������
		* @param options ������������ʽ
		*/
		void * LockImpl(size_t offset, size_t length, DRE_LOCK_OPTIONS options) override;

		/** ����ͨ��lockImpl�����Ļ�����
		*/
		void UnlockImpl(void) override;

		/** ��ȡD3D11��Ⱦ��Դ
		*/
		ID3D11ShaderResourceViewPtr GetShaderResource() { return mShaderResource; };

		/** ��ȡD3D11�ж�ӦTexture��ʵ��
		*/
		ID3D11Texture2DPtr GetTexture() { return mTexture; };

	private:
		/** ��2D�������ݸ��Ƶ�Ӱ�ӻ�����
		* @remark	��ΪD3D11_USAGE_DEFAULT��D3D11_USAGE_DYNAM
		*			IC�Ļ������в��ֶ�д��������ֱ����ɣ�����ͨ
		*			��һ����ӵ�Ӱ�ӻ��������
		*/
		void CopyToShadowResource();

	private:
		/// D3D11��2D����
		ID3D11Texture2DPtr mTexture;
		/// D3D11��������Ⱦ��Դ
		ID3D11ShaderResourceViewPtr mShaderResource;
		/// D3D11��2D�����Ӱ�ӻ���
		ID3D11Texture2DPtr mShadowTexture;
		/// D3D11��Ⱦ�豸
		ID3D11DevicePtr mD3D11Device;
		/// D3D11��Ⱦ�豸����
		ID3D11DeviceContextPtr mD3D11Context;
		/// ӳ�䵽CPU����
		D3D11_MAPPED_SUBRESOURCE mSubResource;
		// ��ǰ����ѡ��
		DRE_LOCK_OPTIONS mLockOption;

	};	// end class D3D11Texture

}	// end namespace dream

#endif	// end __DRED3D11TEXTURE_H__