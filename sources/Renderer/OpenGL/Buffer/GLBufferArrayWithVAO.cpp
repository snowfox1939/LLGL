/*
 * GLBufferArrayWithVAO.cpp
 * 
 * This file is part of the "LLGL" project (Copyright (c) 2015-2018 by Lukas Hermanns)
 * See "LICENSE.txt" for license information.
 */

#include "GLBufferArrayWithVAO.h"
#include "GLBufferWithVAO.h"
#include "../RenderState/GLStateManager.h"
#include "../../CheckedCast.h"
#include "../../GLCommon/GLExtensionRegistry.h"


namespace LLGL
{


GLBufferArrayWithVAO::GLBufferArrayWithVAO(long bindFlags) :
    GLBufferArray { bindFlags }
{
}

void GLBufferArrayWithVAO::BuildVertexArray(std::uint32_t numBuffers, Buffer* const * bufferArray)
{
    #ifdef LLGL_GL_ENABLE_OPENGL2X
    if (!HasExtension(GLExt::ARB_vertex_array_object))
    {
        /* Build vertex array with emulator (for GL 2.x compatibility) */
        BuildVertexArrayWithEmulator(numBuffers, bufferArray);
    }
    else
    #endif // /LLGL_GL_ENABLE_OPENGL2X
    {
        /* Build vertex array with native VAO */
        BuildVertexArrayWithVAO(numBuffers, bufferArray);
    }
}


/*
 * ======= Private: =======
 */

[[noreturn]]
static void ThrowNoVertexBufferErr()
{
    throw std::invalid_argument(
        "cannot build vertex array with buffer that was not created with the 'LLGL::BindFlags::VertexBuffer' flag"
    );
}

void GLBufferArrayWithVAO::BuildVertexArrayWithVAO(std::uint32_t numBuffers, Buffer* const * bufferArray)
{
    /* Bind VAO */
    GLStateManager::active->BindVertexArray(GetVaoID());
    {
        for (std::uint32_t i = 0; numBuffers > 0; --numBuffers)
        {
            if (((*bufferArray)->GetBindFlags() & BindFlags::VertexBuffer) != 0)
            {
                auto vertexBufferGL = LLGL_CAST(GLBufferWithVAO*, (*bufferArray++));
                const auto& vertexFormat = vertexBufferGL->GetVertexFormat();

                /* Bind VBO */
                GLStateManager::active->BindBuffer(GLBufferTarget::ARRAY_BUFFER, vertexBufferGL->GetID());

                /* Build each vertex attribute */
                for (std::uint32_t j = 0, n = static_cast<std::uint32_t>(vertexFormat.attributes.size()); j < n; ++j, ++i)
                {
                    vao_.BuildVertexAttribute(
                        vertexFormat.attributes[j],
                        static_cast<GLsizei>(vertexFormat.stride),
                        static_cast<GLuint>(i)
                    );
                }
            }
            else
                ThrowNoVertexBufferErr();
        }
    }
    GLStateManager::active->BindVertexArray(0);
}

#ifdef LLGL_GL_ENABLE_OPENGL2X

void GLBufferArrayWithVAO::BuildVertexArrayWithEmulator(std::uint32_t numBuffers, Buffer* const * bufferArray)
{
    for (std::uint32_t i = 0; numBuffers > 0; --numBuffers)
    {
        if (((*bufferArray)->GetBindFlags() & BindFlags::VertexBuffer) != 0)
        {
            auto vertexBufferGL = LLGL_CAST(GLBufferWithVAO*, (*bufferArray++));
            const auto& vertexFormat = vertexBufferGL->GetVertexFormat();

            /* Build each vertex attribute */
            for (std::uint32_t j = 0, n = static_cast<std::uint32_t>(vertexFormat.attributes.size()); j < n; ++j, ++i)
            {
                vertexArrayGL2X_.BuildVertexAttribute(
                    vertexBufferGL->GetID(),
                    vertexFormat.attributes[j],
                    static_cast<GLsizei>(vertexFormat.stride),
                    static_cast<GLuint>(i)
                );
            }
        }
        else
            ThrowNoVertexBufferErr();
    }
}

#endif // /LLGL_GL_ENABLE_OPENGL2X


} // /namespace LLGL



// ================================================================================
