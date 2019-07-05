/****************************************************************************

							   WindowsResource.cpp
						Copyright 1998, John J. Bolton

	----------------------------------------------------------------------

	$Header: //depot/Libraries/WindowsResource/WindowsResource.cpp#2 $

	$NoKeywords: $

 ****************************************************************************/

#include "WindowsResource.h"

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <Cassert>

/************************************************************************
 *
 * Name:		WindowsResource::WindowsResource
 *
 * Parameters:	pName -	pName of the resource
 *				pType -	pType of the resource
 *				file -	optional resource file
 *
 * Function:	WindowsResource constructor, if the file parameter is omitted,
 *				the resource is loaded from this .EXE file.
 *
 ************************************************************************/

WindowsResource::WindowsResource( char const * pName, char const * pType, HMODULE file /*= 0*/ )
{
	LockAndLoad( pName, pType, file );
}


/************************************************************************
 *
 * Name:		WindowsResource::WindowsResource
 *
 * Parameters:	pName -	pName of the resource
 *				pType -	pType id of the resource
 *				file -	optional resource file
 *
 * Function:	WindowsResource constructor, if the file parameter is omitted,
 *				the resource is loaded from this .EXE file.
 *
 ************************************************************************/

WindowsResource::WindowsResource( char const * pName, int typeId, HMODULE file /*= 0*/ )
{
	assert( ( typeId & 0xffff0000 ) == 0 );

	LockAndLoad( pName, MAKEINTRESOURCE( typeId ), file );
}


/************************************************************************
 *
 * Name:		WindowsResource::WindowsResource
 *
 * Parameters:	id -	id of the resource
 *				pType -	pType of the resource
 *				file -	optional resource file
 *
 * Function:	WindowsResource constructor, if the file parameter is omitted,
 *				the resource is loaded from this .EXE file.
 *
 ************************************************************************/

WindowsResource::WindowsResource( int id, char const * pType, HMODULE file /*= 0*/ )
{
	assert( ( id & 0xffff0000 ) == 0 );

	LockAndLoad( MAKEINTRESOURCE( id ), pType, file );
}


/************************************************************************
 *
 * Name:		WindowsResource::WindowsResource
 *
 * Parameters:	id -	id of the resource
 *				pType -	pType id of the resource
 *				file -	optional resource file
 *
 * Function:	WindowsResource constructor, if the file parameter is omitted,
 *				the resource is loaded from this .EXE file.
 *
 ************************************************************************/

WindowsResource::WindowsResource( int id, int typeId, HMODULE file /*= 0*/ )
{
	assert( ( id & 0xffff0000 ) == 0 );
	assert( ( typeId & 0xffff0000 ) == 0 );

	LockAndLoad( MAKEINTRESOURCE( id ), MAKEINTRESOURCE( typeId ), file );
}


/************************************************************************
 *
 * Name:		WindowsResource::~WindowsResource
 *
 * Function:	destructor
 *
 ************************************************************************/

WindowsResource::~WindowsResource()
{
}




/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

void WindowsResource::LockAndLoad( char const * pName, char const * pType, HMODULE file )
{
	assert( pName );
	assert( ( reinterpret_cast< int >( pName ) & 0xffff0000 ) != 0 );
	assert( pType );
	assert( ( reinterpret_cast< int >( pType ) & 0xffff0000 ) != 0 );

	m_Data = 0;		// Assume failure

		// Load the resource

	HRSRC const	info	= FindResource( file, pName, pType );
	if ( info != 0 )
	{
		HGLOBAL const	hRes	= LoadResource( file, info );
		if ( hRes != 0 )
		{
			m_Data = LockResource( hRes );
		}
	}
}


