/*
 * D3D11ModuleInterface.h
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include "../ModuleInterface.h"
#include "D3D11RenderSystem.h"


extern "C"
{

LLGL_EXPORT int LLGL_RenderSystem_BuildID()
{
    return LLGL_BUILD_ID;
}

LLGL_EXPORT int LLGL_RenderSystem_RendererID()
{
    return LLGL::RendererID::Direct3D11;
}

LLGL_EXPORT const char* LLGL_RenderSystem_Name()
{
    return "Direct3D 11";
}

LLGL_EXPORT void* LLGL_RenderSystem_Alloc()
{
    return new LLGL::D3D11RenderSystem();
}

}



// ================================================================================
