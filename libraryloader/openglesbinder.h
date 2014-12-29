#ifndef OPENGLESBINDER_H
#define OPENGLESBINDER_H

#include "libraryloader.h"

#include <GLES3/gl31.h>



#define PROCESS_GLES_2_0_FUNCTIONS(action) \
        action(glActiveTexture) \
        action(glAttachShader) \
        action(glBindAttribLocation) \
        action(glBindBuffer) \
        action(glBindFramebuffer) \
        action(glBindRenderbuffer) \
        action(glBindTexture) \
        action(glBlendColor) \
        action(glBlendEquation) \
        action(glBlendEquationSeparate) \
        action(glBlendFunc) \
        action(glBlendFuncSeparate) \
        action(glBufferData) \
        action(glBufferSubData) \
        action(glCheckFramebufferStatus) \
        action(glClear) \
        action(glClearColor) \
        action(glClearDepthf) \
        action(glClearStencil) \
        action(glColorMask) \
        action(glCompileShader) \
        action(glCompressedTexImage2D) \
        action(glCompressedTexSubImage2D) \
        action(glCopyTexImage2D) \
        action(glCopyTexSubImage2D) \
        action(glCreateProgram) \
        action(glCreateShader) \
        action(glCullFace) \
        action(glDeleteBuffers) \
        action(glDeleteFramebuffers) \
        action(glDeleteProgram) \
        action(glDeleteRenderbuffers) \
        action(glDeleteShader) \
        action(glDeleteTextures) \
        action(glDepthFunc) \
        action(glDepthMask) \
        action(glDepthRangef) \
        action(glDetachShader) \
        action(glDisable) \
        action(glDisableVertexAttribArray) \
        action(glDrawArrays) \
        action(glDrawElements) \
        action(glEnable) \
        action(glEnableVertexAttribArray) \
        action(glFinish) \
        action(glFlush) \
        action(glFramebufferRenderbuffer) \
        action(glFramebufferTexture2D) \
        action(glFrontFace) \
        action(glGenBuffers) \
        action(glGenerateMipmap) \
        action(glGenFramebuffers) \
        action(glGenRenderbuffers) \
        action(glGenTextures) \
        action(glGetActiveAttrib) \
        action(glGetActiveUniform) \
        action(glGetAttachedShaders) \
        action(glGetAttribLocation) \
        action(glGetBooleanv) \
        action(glGetBufferParameteriv) \
        action(glGetError) \
        action(glGetFloatv) \
        action(glGetFramebufferAttachmentParameteriv) \
        action(glGetIntegerv) \
        action(glGetProgramiv) \
        action(glGetProgramInfoLog) \
        action(glGetRenderbufferParameteriv) \
        action(glGetShaderiv) \
        action(glGetShaderInfoLog) \
        action(glGetShaderPrecisionFormat) \
        action(glGetShaderSource) \
        action(glGetString) \
        action(glGetTexParameterfv) \
        action(glGetTexParameteriv) \
        action(glGetUniformfv) \
        action(glGetUniformiv) \
        action(glGetUniformLocation) \
        action(glGetVertexAttribfv) \
        action(glGetVertexAttribiv) \
        action(glGetVertexAttribPointerv) \
        action(glHint) \
        action(glIsBuffer) \
        action(glIsEnabled) \
        action(glIsFramebuffer) \
        action(glIsProgram) \
        action(glIsRenderbuffer) \
        action(glIsShader) \
        action(glIsTexture) \
        action(glLineWidth) \
        action(glLinkProgram) \
        action(glPixelStorei) \
        action(glPolygonOffset) \
        action(glReadPixels) \
        action(glReleaseShaderCompiler) \
        action(glRenderbufferStorage) \
        action(glSampleCoverage) \
        action(glScissor) \
        action(glShaderBinary) \
        action(glShaderSource) \
        action(glStencilFunc) \
        action(glStencilFuncSeparate) \
        action(glStencilMask) \
        action(glStencilMaskSeparate) \
        action(glStencilOp) \
        action(glStencilOpSeparate) \
        action(glTexImage2D) \
        action(glTexParameterf) \
        action(glTexParameterfv) \
        action(glTexParameteri) \
        action(glTexParameteriv) \
        action(glTexSubImage2D) \
        action(glUniform1f) \
        action(glUniform1fv) \
        action(glUniform1i) \
        action(glUniform1iv) \
        action(glUniform2f) \
        action(glUniform2fv) \
        action(glUniform2i) \
        action(glUniform2iv) \
        action(glUniform3f) \
        action(glUniform3fv) \
        action(glUniform3i) \
        action(glUniform3iv) \
        action(glUniform4f) \
        action(glUniform4fv) \
        action(glUniform4i) \
        action(glUniform4iv) \
        action(glUniformMatrix2fv) \
        action(glUniformMatrix3fv) \
        action(glUniformMatrix4fv) \
        action(glUseProgram) \
        action(glValidateProgram) \
        action(glVertexAttrib1f) \
        action(glVertexAttrib1fv) \
        action(glVertexAttrib2f) \
        action(glVertexAttrib2fv) \
        action(glVertexAttrib3f) \
        action(glVertexAttrib3fv) \
        action(glVertexAttrib4f) \
        action(glVertexAttrib4fv) \
        action(glVertexAttribPointer) \
        action(glViewport)

#define PROCESS_GLES_3_0_FUNCTIONS(action) \
        action(glReadBuffer) \
        action(glDrawRangeElements) \
        action(glTexImage3D) \
        action(glTexSubImage3D) \
        action(glCopyTexSubImage3D) \
        action(glCompressedTexImage3D) \
        action(glCompressedTexSubImage3D) \
        action(glGenQueries) \
        action(glDeleteQueries) \
        action(glIsQuery) \
        action(glBeginQuery) \
        action(glEndQuery) \
        action(glGetQueryiv) \
        action(glGetQueryObjectuiv) \
        action(glUnmapBuffer) \
        action(glGetBufferPointerv) \
        action(glDrawBuffers) \
        action(glUniformMatrix2x3fv) \
        action(glUniformMatrix3x2fv) \
        action(glUniformMatrix2x4fv) \
        action(glUniformMatrix4x2fv) \
        action(glUniformMatrix3x4fv) \
        action(glUniformMatrix4x3fv) \
        action(glBlitFramebuffer) \
        action(glRenderbufferStorageMultisample) \
        action(glFramebufferTextureLayer) \
        action(glMapBufferRange) \
        action(glFlushMappedBufferRange) \
        action(glBindVertexArray) \
        action(glDeleteVertexArrays) \
        action(glGenVertexArrays) \
        action(glIsVertexArray) \
        action(glGetIntegeri_v) \
        action(glBeginTransformFeedback) \
        action(glEndTransformFeedback) \
        action(glBindBufferRange) \
        action(glBindBufferBase) \
        action(glTransformFeedbackVaryings) \
        action(glGetTransformFeedbackVarying) \
        action(glVertexAttribIPointer) \
        action(glGetVertexAttribIiv) \
        action(glGetVertexAttribIuiv) \
        action(glVertexAttribI4i) \
        action(glVertexAttribI4ui) \
        action(glVertexAttribI4iv) \
        action(glVertexAttribI4uiv) \
        action(glGetUniformuiv) \
        action(glGetFragDataLocation) \
        action(glUniform1ui) \
        action(glUniform2ui) \
        action(glUniform3ui) \
        action(glUniform4ui) \
        action(glUniform1uiv) \
        action(glUniform2uiv) \
        action(glUniform3uiv) \
        action(glUniform4uiv) \
        action(glClearBufferiv) \
        action(glClearBufferuiv) \
        action(glClearBufferfv) \
        action(glClearBufferfi) \
        action(glGetStringi) \
        action(glCopyBufferSubData) \
        action(glGetUniformIndices) \
        action(glGetActiveUniformsiv) \
        action(glGetUniformBlockIndex) \
        action(glGetActiveUniformBlockiv) \
        action(glGetActiveUniformBlockName) \
        action(glUniformBlockBinding) \
        action(glDrawArraysInstanced) \
        action(glDrawElementsInstanced) \
        action(glFenceSync) \
        action(glIsSync) \
        action(glDeleteSync) \
        action(glClientWaitSync) \
        action(glWaitSync) \
        action(glGetInteger64v) \
        action(glGetSynciv) \
        action(glGetInteger64i_v) \
        action(glGetBufferParameteri64v) \
        action(glGenSamplers) \
        action(glDeleteSamplers) \
        action(glIsSampler) \
        action(glBindSampler) \
        action(glSamplerParameteri) \
        action(glSamplerParameteriv) \
        action(glSamplerParameterf) \
        action(glSamplerParameterfv) \
        action(glGetSamplerParameteriv) \
        action(glGetSamplerParameterfv) \
        action(glVertexAttribDivisor) \
        action(glBindTransformFeedback) \
        action(glDeleteTransformFeedbacks) \
        action(glGenTransformFeedbacks) \
        action(glIsTransformFeedback) \
        action(glPauseTransformFeedback) \
        action(glResumeTransformFeedback) \
        action(glGetProgramBinary) \
        action(glProgramBinary) \
        action(glProgramParameteri) \
        action(glInvalidateFramebuffer) \
        action(glInvalidateSubFramebuffer) \
        action(glTexStorage2D) \
        action(glTexStorage3D) \
        action(glGetInternalformativ)

#define PROCESS_GLES_3_1_FUNCTIONS(action) \
        action(glDispatchCompute) \
        action(glDispatchComputeIndirect) \
        action(glDrawArraysIndirect) \
        action(glDrawElementsIndirect) \
        action(glFramebufferParameteri) \
        action(glGetFramebufferParameteriv) \
        action(glGetProgramInterfaceiv) \
        action(glGetProgramResourceIndex) \
        action(glGetProgramResourceName) \
        action(glGetProgramResourceiv) \
        action(glGetProgramResourceLocation) \
        action(glUseProgramStages) \
        action(glActiveShaderProgram) \
        action(glCreateShaderProgramv) \
        action(glBindProgramPipeline) \
        action(glDeleteProgramPipelines) \
        action(glGenProgramPipelines) \
        action(glIsProgramPipeline) \
        action(glGetProgramPipelineiv) \
        action(glProgramUniform1i) \
        action(glProgramUniform2i) \
        action(glProgramUniform3i) \
        action(glProgramUniform4i) \
        action(glProgramUniform1ui) \
        action(glProgramUniform2ui) \
        action(glProgramUniform3ui) \
        action(glProgramUniform4ui) \
        action(glProgramUniform1f) \
        action(glProgramUniform2f) \
        action(glProgramUniform3f) \
        action(glProgramUniform4f) \
        action(glProgramUniform1iv) \
        action(glProgramUniform2iv) \
        action(glProgramUniform3iv) \
        action(glProgramUniform4iv) \
        action(glProgramUniform1uiv) \
        action(glProgramUniform2uiv) \
        action(glProgramUniform3uiv) \
        action(glProgramUniform4uiv) \
        action(glProgramUniform1fv) \
        action(glProgramUniform2fv) \
        action(glProgramUniform3fv) \
        action(glProgramUniform4fv) \
        action(glProgramUniformMatrix2fv) \
        action(glProgramUniformMatrix3fv) \
        action(glProgramUniformMatrix4fv) \
        action(glProgramUniformMatrix2x3fv) \
        action(glProgramUniformMatrix3x2fv) \
        action(glProgramUniformMatrix2x4fv) \
        action(glProgramUniformMatrix4x2fv) \
        action(glProgramUniformMatrix3x4fv) \
        action(glProgramUniformMatrix4x3fv) \
        action(glValidateProgramPipeline) \
        action(glGetProgramPipelineInfoLog) \
        action(glBindImageTexture) \
        action(glGetBooleani_v) \
        action(glMemoryBarrier) \
        action(glMemoryBarrierByRegion) \
        action(glTexStorage2DMultisample) \
        action(glGetMultisamplefv) \
        action(glSampleMaski) \
        action(glGetTexLevelParameteriv) \
        action(glGetTexLevelParameterfv) \
        action(glBindVertexBuffer) \
        action(glVertexAttribFormat) \
        action(glVertexAttribIFormat) \
        action(glVertexAttribBinding) \
        action(glVertexBindingDivisor)



/**
 * Provides access to OpenGL ES functions loaded dynamically in runtime.
 * @note If the construction of a subclass object succeeds, then functions from
 * that OpenGL ES version are guaranteed to be usable.
 */
class OpenGles_2_0_Binder
{
protected:
    GLint majorVersion;
    GLint minorVersion;
public:
    PROCESS_GLES_2_0_FUNCTIONS(DECLARE_POINTER)
    OpenGles_2_0_Binder(LibraryLoader& libraryLoader):
        majorVersion(0),
        minorVersion(0)
        PROCESS_GLES_2_0_FUNCTIONS(BIND_POINTER)
    {
        glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
        glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
        if (majorVersion < 2) {
            throw LibraryLoaderException("OpenGL ES 2.0 not supported.");
        }
    }
    virtual ~OpenGles_2_0_Binder() = default;
};



/**
 * @see OpenGles_2_0_Binder
 */
class OpenGles_3_0_Binder: public OpenGles_2_0_Binder
{
public:
    PROCESS_GLES_3_0_FUNCTIONS(DECLARE_POINTER)
    OpenGles_3_0_Binder(LibraryLoader& libraryLoader):
        OpenGles_2_0_Binder(libraryLoader)
        PROCESS_GLES_3_0_FUNCTIONS(BIND_POINTER)
    {
        if (majorVersion < 3) {
            throw LibraryLoaderException("OpenGL ES 3.0 not supported.");
        }
    }
};



/**
 * @see OpenGles_2_0_Binder
 */
class OpenGles_3_1_Binder: public OpenGles_3_0_Binder
{
public:
    PROCESS_GLES_3_1_FUNCTIONS(DECLARE_POINTER)
    OpenGles_3_1_Binder(LibraryLoader& libraryLoader):
        OpenGles_3_0_Binder(libraryLoader)
        PROCESS_GLES_3_1_FUNCTIONS(BIND_POINTER)
    {
        if ((majorVersion < 3) || ((majorVersion == 3) && (minorVersion < 1))) {
            throw LibraryLoaderException("OpenGL ES 3.1 not supported.");
        }
    }
};



#endif // OPENGLESBINDER_H
