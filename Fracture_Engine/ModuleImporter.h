#ifndef __MODULE_IMPORTER_H__
#define __MODULE_IMPORTER_H__

#include "Module.h"
#include "Globals.h"

#include "Assimp/include/cimport.h"
#include "Assimp/include/scene.h"
#include "Assimp/include/postprocess.h"
#include "Assimp/include/cfileio.h"

#pragma comment (lib, "Assimp/libx86/assimp.lib")

class ModuleImporter : public Module
{
public:
	ModuleImporter(bool start_enabled = true);
	~ModuleImporter();

	bool Init();
	update_status Update(float dt);
	bool CleanUp();
private:

};
#endif /* __MODULE_IMPORTER__ */