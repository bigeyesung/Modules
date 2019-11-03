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