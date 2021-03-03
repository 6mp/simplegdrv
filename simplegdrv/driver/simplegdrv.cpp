#include "simplegdrv.hpp"

simplegdrv::simplegdrv( ) : driver_handle_( nullptr )
{
	this->driver_handle_ = CreateFile( this->driver_symbolic_link_.data( ) ,
						GENERIC_READ | GENERIC_WRITE ,
						FILE_SHARE_READ | FILE_SHARE_WRITE ,
						0 ,
						OPEN_EXISTING ,
						FILE_ATTRIBUTE_NORMAL ,
						NULL );

	if ( this->driver_handle_ == INVALID_HANDLE_VALUE )
		std::cout << "[" << __FUNCTION__ << "] " << "failed to open handle to driver" << std::endl;
}

simplegdrv::~simplegdrv( )
{
	std::cout << "[" << __FUNCTION__ << "] " << "closing driver handle" << std::endl;
	CloseHandle( this->driver_handle_ );
}

auto simplegdrv::map_physical( const physical_address_t physical_base , const uint32_t size ) const -> virtual_address_t
{
	driver_structs::in::map_physical_t in = { 0, 0, physical_base, 0, size };
	driver_structs::out::map_physical_t out = { 0 };

	if ( !device_io_control( this->driver_handle_ , &in , &out ) )
	{
		std::cout << "[" << __FUNCTION__ << "] " << "map physical IOCTL failed" << std::endl;
		return 0;
	}

	std::cout << "[" << __FUNCTION__ << "] " << "mapped physcial memory at 0x" << physical_base << " , VA : 0x" << std::hex << out.section_base_address << std::endl;
	return out.section_base_address;
}

auto simplegdrv::unmap_physical( const virtual_address_t virtual_base ) const -> bool
{
	driver_structs::in::unmap_physical_t in = { virtual_base };

	return device_io_control( this->driver_handle_ , &in );
}
