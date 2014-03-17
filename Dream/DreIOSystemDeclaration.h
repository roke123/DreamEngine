#ifndef __DREIOSYSTEMDECLARATION_H__
#define __DREIOSYSTEMDECLARATION_H__

#include "DreTypes.h"
#include "DreContainer.h"
#include "DreComplieConfig.h"
#include "DreException.h"

#include "DreDataBufferEnums.h"

#include <fstream>

namespace dream
{
	typedef shared_ptr<std::ifstream>			ifstreamPtr;

	typedef shared_ptr<std::ofstream>			ofstreamPtr;

	class DataBufferFactory;;

	class ReadBuffer;
	typedef shared_ptr<ReadBuffer>				ReadBufferPtr;

	class WriteBuffer;
	typedef shared_ptr<WriteBuffer>				WriteBufferPtr;

	class FileReadBuffer;
	typedef shared_ptr<FileReadBuffer>			FileReadBufferPtr;

	class FileWriteBuffer;
	typedef shared_ptr<FileWriteBuffer>			FileWriteBufferPtr;

	class MemoryReadBuffer;
	typedef shared_ptr<MemoryReadBuffer>		MemoryReadBufferPtr;

	class BaseMemoryReadBuffer;
	typedef shared_ptr<BaseMemoryReadBuffer>	BaseMemoryReadBufferPtr;

	class MemoryWriteBuffer;
	typedef shared_ptr<MemoryWriteBuffer>		MemoryWriteBufferPtr;

	class BaseMemoryWriteBuffer;
	typedef shared_ptr<BaseMemoryWriteBuffer>	BaseMemoryWriteBufferPtr;

	class ImageLoader;
	typedef shared_ptr<ImageLoader>				ImageLoaderPtr;

	class Image;
	typedef shared_ptr<Image>					ImagePtr;

	class NormalImage;
	typedef shared_ptr<NormalImage>				NormalImagePtr;

	class Serializer;

	class Serializable;
	typedef shared_ptr<Serializable>			SerializablePtr;

	class Logger;

}	// end namespace dream

#endif	// end __DREIOSYSTEMDECLARATION_H__