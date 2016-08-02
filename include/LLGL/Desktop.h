/*
 * Desktop.h
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#ifndef __LLGL_DESKTOP_H__
#define __LLGL_DESKTOP_H__


#include "Export.h"
#include "Types.h"
#include "RenderContextDescriptor.h"


namespace LLGL
{

namespace Desktop
{


//! Returns the desktop resolution.
LLGL_EXPORT Size GetResolution();

//! Returns the desktop color depth (bits per pixel).
LLGL_EXPORT int GetColorDepth();

//! Sets the new specified video mode for the desktop (resolution and fullscreen mode).
LLGL_EXPORT bool ChangeVideoMode(const VideoModeDescriptor& videoMode);

//! Restes the standard video mode for the desktop.
LLGL_EXPORT bool ResetVideoMode();


} // /namespace Desktop

} // /namespace LLGL


#endif



// ================================================================================