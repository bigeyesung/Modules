#include "SessionInterface.h"

using namespace ci;
using namespace std;

string SessionInterface::bufferToString( const BufferRef& buffer )
{
	string s( static_cast<const char*>( buffer->getData() ) );
	if ( s.length() > buffer->getSize() ) {
		s.resize( buffer->getSize() );
	}
	return s;
}

BufferRef SessionInterface::stringToBuffer( string& value )
{
	return Buffer::create( &value[ 0 ], value.size() );
}

SessionInterface::SessionInterface( asio::io_service& io )
: DispatcherInterface( io ), mBufferSize( 0 ), mReadCompleteEventHandler( nullptr ), 
mReadEventHandler( nullptr ), mWriteEventHandler( nullptr )
{
}

SessionInterface::~SessionInterface()
{
	mReadCompleteEventHandler	= nullptr;
	mReadEventHandler			= nullptr;
	mWriteEventHandler			= nullptr;
    mRequest.consume( mRequest.size() );
	mResponse.consume( mResponse.size() );
}

void SessionInterface::onRead( const asio::error_code& err, size_t bytesTransferred )
{
	if ( err ) 
	{
		if ( err == asio::error::eof ) {
			if ( mReadCompleteEventHandler != nullptr ) {
				mReadCompleteEventHandler();
			}
            } else {
			if ( mErrorEventHandler != nullptr ) {
				mErrorEventHandler( err.message(), bytesTransferred );
			}
		}
	}
    else
	{
		if ( mReadEventHandler != nullptr ) 
		{
			char* data = new char[ bytesTransferred + 1 ]();
			data[ bytesTransferred ] = 0;
			mResponse.commit( bytesTransferred );
			istream stream( &mResponse );
			stream.read( data, bytesTransferred );
			mReadEventHandler( Buffer::create( data, bytesTransferred ) );
			delete [] data;
		}
        if ( mReadCompleteEventHandler != nullptr && 
			mBufferSize > 0 && bytesTransferred < mBufferSize ) {
			mReadCompleteEventHandler();
		}
	}
	mResponse.consume( mResponse.size() );
}

void SessionInterface::onWrite( const asio::error_code& err, size_t bytesTransferred )
{
	if ( err ) {
		if ( mErrorEventHandler != nullptr ) {
			mErrorEventHandler( err.message(), bytesTransferred );
		}
	} else {