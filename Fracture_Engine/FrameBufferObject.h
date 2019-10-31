#ifndef __RENDER_TEXTURE_H__
#define __RENDER_TEXTURE_H__

#include "Imgui/imgui.h"

#include "Globals.h"

class FrameBufferObject
{
public:
	FrameBufferObject();
	~FrameBufferObject();

	void GenerateFBO();

	void BindAndOperateOnFBO(const ImVec2& viewport_size);
	void UnbindFBO();
	
	void DeleteFBO();

public:
	void GenerateDRB();
	void CreateTexture();

	/* At update/resize for now */
	void SetCamera(const ImVec2& size);
	void SetDepthBuffer(const ImVec2& size);
	void SetTexture(const ImVec2& size);

public:
	/* Frame Buffer Object */
	uint fbo_id = 0;

	// We also need a Depth and Stencil buffers to operate correctly on the FBO

	/* Depth Render Buffer */
	uint drb_id = 0;
	/* Stencil Buffer */
	uint sb_id = 0;

	/* Texture to render scene */
	uint texture_id = 0;
};

#endif /* __RENDER_TEXTURE_H__ */
