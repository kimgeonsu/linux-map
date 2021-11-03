#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <linux/types.h>
#include <linux/ioctl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <iostream>
#include <fstream>
#include <cmath>

#include "../Header/MapDrawEngine.h "

extern "C" {
#include "../include/type.h"
#include "../include/pen.h"
#include "../include/brush.h"
#include "../include/graphics.h"
}

int main(int argc, char *argv[])
{
	Graphics 	*graphics;

	graphics = new Graphics("/dev/fb0");
	
    std::cout << "Hello World!\n";

    std::string dataFilePath = "linux-map/geminit_gn_gdi-examples-master/src/Output";

    ////---------------------------------------------------
    CMapDrawEngine *engine = new CMapDrawEngine;

    engine->Init();
    engine->SetMapDataPath(dataFilePath);

    cout << engine->GetDeviceRect().left << endl;
    
    Graphics* graphics = new Graphics("dev/fb0");
    if (engine->  DrawMap(graphics))
        cout << "I'm True hahahaha\n";

    return 0;

	return 0;
}
