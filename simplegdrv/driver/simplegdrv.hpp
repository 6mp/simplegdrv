#pragma once
#include <Windows.h>
#include <fileapi.h>
#include <handleapi.h>
#include <ioapiset.h>
#include <iostream>


namespace driver_structs
{
	constexpr auto device_path = LR"(\\.\GIO)";

	enum class ioctl_code : uint32_t
	{
		map_physical = 0xC3502004 ,
		unmap_physical = 0xC3502008 ,
	};

	namespace in
	{
		struct map_physical_t
		{
			static constexpr auto ioctl_code = ioctl_code::map_physical;

			uint32_t interface_type;
			uint32_t bus_number;
			uint64_t view_base;
			uint32_t address_space;
			uint32_t view_size;
		};

		struct unmap_physical_t
		{
			static constexpr auto ioctl_code = ioctl_code::unmap_physical;

			uint64_t section_base_address;
		};

	}

	namespace out
	{
		struct map_physical_t
		{
			static constexpr auto ioctl_code = ioctl_code::map_physical;

			uint64_t section_base_address;
		};
	}
}


class simplegdrv
{

private:
	using handle_t = HANDLE;
	using virtual_address_t = std::uintptr_t;
	using physical_address_t = std::uintptr_t;

	handle_t driver_handle_;
	std::wstring_view driver_symbolic_link_ = LR"(\\.\GIO)";

	template <typename InputBuffer , typename OutputBuffer>
	static bool device_io_control( const handle_t handle , InputBuffer* input , OutputBuffer* output )
	{
		return ::DeviceIoControl( handle , static_cast<std::underlying_type_t<driver_structs::ioctl_code>>( InputBuffer::ioctl_code ) ,
								  input , sizeof( InputBuffer ) , output , sizeof( OutputBuffer ) , nullptr , nullptr );
	}

	template <typename InputBuffer>
	static bool device_io_control( const handle_t handle , InputBuffer* input )
	{
		return ::DeviceIoControl( handle , static_cast<std::underlying_type_t<driver_structs::ioctl_code>>( InputBuffer::ioctl_code ) ,
								  input , sizeof( InputBuffer ) , nullptr , 0 , nullptr , nullptr );
	}

public:

	simplegdrv( );
	~simplegdrv( );

	auto map_physical( const physical_address_t physical_base , const uint32_t size ) const -> virtual_address_t;
	auto unmap_physical( const virtual_address_t virtual_base ) const -> bool;
};
