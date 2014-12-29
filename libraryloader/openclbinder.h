#ifndef OPENCLBINDER_H
#define OPENCLBINDER_H

#include "libraryloader.h"

#include <CL/opencl.h>



#define PROCESS_CL_1_0_FUNCTIONS(action) \
        action(clGetPlatformIDs) \
        action(clGetPlatformInfo) \
        action(clGetDeviceIDs) \
        action(clGetDeviceInfo) \
        action(clCreateContext) \
        action(clCreateContextFromType) \
        action(clRetainContext) \
        action(clReleaseContext) \
        action(clGetContextInfo) \
        action(clCreateCommandQueue) \
        action(clRetainCommandQueue) \
        action(clReleaseCommandQueue) \
        action(clGetCommandQueueInfo) \
        action(clCreateBuffer) \
        action(clCreateImage2D) \
        action(clCreateImage3D) \
        action(clRetainMemObject) \
        action(clReleaseMemObject) \
        action(clGetSupportedImageFormats) \
        action(clGetMemObjectInfo) \
        action(clGetImageInfo) \
        action(clCreateSampler) \
        action(clRetainSampler) \
        action(clReleaseSampler) \
        action(clGetSamplerInfo) \
        action(clCreateProgramWithSource) \
        action(clCreateProgramWithBinary) \
        action(clRetainProgram) \
        action(clReleaseProgram) \
        action(clBuildProgram) \
        action(clGetProgramInfo) \
        action(clGetProgramBuildInfo) \
        action(clCreateKernel) \
        action(clCreateKernelsInProgram) \
        action(clRetainKernel) \
        action(clReleaseKernel) \
        action(clSetKernelArg) \
        action(clGetKernelInfo) \
        action(clGetKernelWorkGroupInfo) \
        action(clWaitForEvents) \
        action(clGetEventInfo) \
        action(clRetainEvent) \
        action(clReleaseEvent) \
        action(clGetEventProfilingInfo) \
        action(clFlush) \
        action(clFinish) \
        action(clEnqueueReadBuffer) \
        action(clEnqueueWriteBuffer) \
        action(clEnqueueCopyBuffer) \
        action(clEnqueueReadImage) \
        action(clEnqueueWriteImage) \
        action(clEnqueueCopyImage) \
        action(clEnqueueCopyImageToBuffer) \
        action(clEnqueueCopyBufferToImage) \
        action(clEnqueueMapBuffer) \
        action(clEnqueueMapImage) \
        action(clEnqueueUnmapMemObject) \
        action(clEnqueueNDRangeKernel) \
        action(clEnqueueNativeKernel) \
        action(clEnqueueMarker) \
        action(clEnqueueWaitForEvents) \
        action(clEnqueueBarrier) \
        action(clEnqueueTask) \
        action(clUnloadCompiler) \
        action(clGetExtensionFunctionAddress)

#define PROCESS_CL_1_1_FUNCTIONS(action) \
        action(clCreateSubBuffer) \
        action(clSetMemObjectDestructorCallback) \
        action(clCreateUserEvent) \
        action(clSetUserEventStatus) \
        action(clSetEventCallback) \
        action(clEnqueueReadBufferRect) \
        action(clEnqueueWriteBufferRect) \
        action(clEnqueueCopyBufferRect)

#define PROCESS_CL_1_2_FUNCTIONS(action) \
        action(clCreateSubDevices) \
        action(clRetainDevice) \
        action(clReleaseDevice) \
        action(clCreateImage) \
        action(clCreateProgramWithBuiltInKernels) \
        action(clCompileProgram) \
        action(clLinkProgram) \
        action(clUnloadPlatformCompiler) \
        action(clGetKernelArgInfo) \
        action(clEnqueueFillBuffer) \
        action(clEnqueueFillImage) \
        action(clEnqueueMigrateMemObjects) \
        action(clEnqueueMarkerWithWaitList) \
        action(clEnqueueBarrierWithWaitList) \
        action(clGetExtensionFunctionAddressForPlatform)

#define PROCESS_CL_2_0_FUNCTIONS(action) \
        action(clCreateCommandQueueWithProperties) \
        action(clCreatePipe) \
        action(clGetPipeInfo) \
        action(clSVMAlloc) \
        action(clSVMFree) \
        action(clCreateSamplerWithProperties) \
        action(clSetKernelArgSVMPointer) \
        action(clSetKernelExecInfo) \
        action(clEnqueueSVMFree) \
        action(clEnqueueSVMMemcpy) \
        action(clEnqueueSVMMemFill) \
        action(clEnqueueSVMMap) \
        action(clEnqueueSVMUnmap)



/**
 * Provides access to OpenCL functions loaded dynamically in runtime.
 * @note If the construction of a subclass object succeeds, then functions from
 * that OpenCL version are guaranteed to be usable.
 */
class OpenCl_1_0_Binder
{
protected:
    LibraryLoader* loader;
public:
    PROCESS_CL_1_0_FUNCTIONS(DECLARE_POINTER)
    OpenCl_1_0_Binder(LibraryLoader& libraryLoader):
        loader(&libraryLoader)
        PROCESS_CL_1_0_FUNCTIONS(BIND_POINTER)
    {}
    virtual ~OpenCl_1_0_Binder() = default;
};



/**
 * @see OpenCl_1_0_Binder
 */
class OpenCl_1_1_Binder: public OpenCl_1_0_Binder
{
public:
    PROCESS_CL_1_1_FUNCTIONS(DECLARE_POINTER)
    OpenCl_1_1_Binder(LibraryLoader& libraryLoader):
        OpenCl_1_0_Binder(libraryLoader)
        PROCESS_CL_1_1_FUNCTIONS(BIND_POINTER)
    {}
};



/**
 * @see OpenCl_1_0_Binder
 */
class OpenCl_1_2_Binder: public OpenCl_1_1_Binder
{
public:
    PROCESS_CL_1_2_FUNCTIONS(DECLARE_POINTER)
    OpenCl_1_2_Binder(LibraryLoader& libraryLoader):
        OpenCl_1_1_Binder(libraryLoader)
        PROCESS_CL_1_2_FUNCTIONS(BIND_POINTER)
    {}
};



/**
 * @see OpenCl_1_0_Binder
 */
class OpenCl_2_0_Binder: public OpenCl_1_2_Binder
{
public:
    PROCESS_CL_2_0_FUNCTIONS(DECLARE_POINTER)
    OpenCl_2_0_Binder(LibraryLoader& libraryLoader):
        OpenCl_1_2_Binder(libraryLoader)
        PROCESS_CL_2_0_FUNCTIONS(BIND_POINTER)
    {}
};



#endif // OPENCLBINDER_H
