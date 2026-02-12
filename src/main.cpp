#include "Engine.h"
int main(int argc, char** argv)
{
	Engine engine(argc, argv, 800, 600, "Silnik 3D");
	engine.run();
	return 0;
}