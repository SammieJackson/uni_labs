#include <WinSock2.h>
#include "C:\Users\Admin\Documents\MyDocs\UNI\Course II\OOP\Chat\SockUtils.h"

void main()
{
	InitSocketsLib();
	TestServerSocket();

	ReleaseSocketsLib();
}