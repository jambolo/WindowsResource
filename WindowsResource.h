#if !defined( WINDOWSRESOURCE_H_INCLUDED )
#define WINDOWSRESOURCE_H_INCLUDED

#pragma once

/*****************************************************************************

                              WindowsResource.h

						Copyright 2001, John J. Bolton
	----------------------------------------------------------------------

	$Header: //depot/Libraries/WindowsResource/WindowsResource.h#2 $

	$NoKeywords: $

*****************************************************************************/

#include <wtypes.h>


class WindowsResource
{
public:
	WindowsResource( char const * pName, char const * pType, HMODULE file = 0 );
	WindowsResource( char const * pName, int typeId,         HMODULE file = 0 );
	WindowsResource( int id,             char const * pType, HMODULE file = 0 );
	WindowsResource( int id,             int typeId,         HMODULE file = 0 );
	virtual ~WindowsResource();

	// Returns a pointer to the resource data, 0 if error
	void const * GetData() const { return m_Data; }

private:

	// Find and load the resource
	void LockAndLoad( char const * pName, char const * pType, HMODULE );

		// Resource data, 0 if error
	void *	m_Data;
};


#endif // !defined( WINDOWSRESOURCE_H_INCLUDED )
