#include "matrix_helper.h"

using std::cout;
using std::endl;

void multiply_matrix_vector(void *matrix, void *vector, void *result, const uint16_t N = 64, const uint16_t K = 128)
{
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);
    auto devices = mtlpp::Device::CopyAllDevices();
    //mtlpp::Device device = mtlpp::Device::CreateSystemDefaultDevice();
    std::cout << "I found " << sizeof(devices) / sizeof(devices[0]) << " devices" << endl;
    for (uint8_t idev = 0; idev < devices.GetSize(); idev++)
    {
        auto dev = devices[idev];
        cout << dev.GetName().GetCStr() << endl;
        cout << "It is " << (dev.IsLowPower() ? "" : " not ") << "low power" << endl;
        cout << "It is " << (dev.IsRemovable() ? "" : " not ") << "removable" << endl;
        cout << "It has " << (dev.HasUnifiedMemory() ? "" : " not ") << "unified memory" << endl;
    }

    auto device = devices[0];
    assert(device);

    const char shadersSrc[] = R"""(
        #include "shaders/matrixvector.metal"
    )""";

    mtlpp::Library library = device.NewLibrary(shadersSrc, mtlpp::CompileOptions(), nullptr);
    assert(library);
    mtlpp::Function matmul = library.NewFunction("matvecmul");
    assert(matmul);

    mtlpp::ComputePipelineState computePipelineState = device.NewComputePipelineState(matmul, nullptr);
    assert(computePipelineState);

    mtlpp::CommandQueue commandQueue = device.NewCommandQueue();
    assert(commandQueue);

    mtlpp::Buffer aBuffer = device.NewBuffer(sizeof(float) * N * K, mtlpp::ResourceOptions::StorageModeManaged);
    assert(aBuffer);
    mtlpp::Buffer bBuffer = device.NewBuffer(sizeof(float) * K, mtlpp::ResourceOptions::StorageModeManaged);
    assert(bBuffer);
    mtlpp::Buffer paramsBuffer = device.NewBuffer(sizeof(uint16_t) * 2, mtlpp::ResourceOptions::StorageModeManaged);
    assert(paramsBuffer);

    mtlpp::Buffer outBuffer = device.NewBuffer(sizeof(float) * N, mtlpp::ResourceOptions::StorageModeManaged);
    assert(outBuffer);

    // update input data
    {
        float *aData = static_cast<float *>(aBuffer.GetContents());
        float *bData = static_cast<float *>(bBuffer.GetContents());
        uint16_t *paramsData = static_cast<uint16_t *>(paramsBuffer.GetContents());

        std::memcpy(aData, matrix, N * K * sizeof(float));
        std::memcpy(bData, vector, K * sizeof(float));

        paramsData[0] = N;
        paramsData[1] = K;
        aBuffer.DidModify(ns::Range(0, sizeof(float) * N * K));
        bBuffer.DidModify(ns::Range(0, sizeof(float) * K));
        paramsBuffer.DidModify(ns::Range(0, sizeof(uint16_t) * 2));
    }

    auto gpu_start = std::chrono::steady_clock::now();
    mtlpp::CommandBuffer commandBuffer = commandQueue.CommandBuffer();
    assert(commandBuffer);

    mtlpp::ComputeCommandEncoder commandEncoder = commandBuffer.ComputeCommandEncoder();
    commandEncoder.SetBuffer(aBuffer, 0, 0);
    commandEncoder.SetBuffer(bBuffer, 0, 1);
    commandEncoder.SetBuffer(outBuffer, 0, 2);
    commandEncoder.SetBuffer(paramsBuffer, 0, 3);
    commandEncoder.SetComputePipelineState(computePipelineState);
    commandEncoder.DispatchThreadgroups(
        mtlpp::Size(1, 1, 1),
        mtlpp::Size(N, 1, 1));
    commandEncoder.EndEncoding();

    mtlpp::BlitCommandEncoder blitCommandEncoder = commandBuffer.BlitCommandEncoder();
    blitCommandEncoder.Synchronize(outBuffer);
    blitCommandEncoder.EndEncoding();

    commandBuffer.Commit();
    commandBuffer.WaitUntilCompleted();

    auto gpu_end = std::chrono::steady_clock::now();

    {
        float *outData = static_cast<float *>(outBuffer.GetContents());
        std::memmove(result, outData, N * sizeof(float));
    }

    auto gpu_time = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(gpu_end - gpu_start).count());
    std::cout << "Time (GPU[Metal]) = " << gpu_time << "[ms]" << std::endl;
}

void multiply_matrix_matrix(void *matrix_first, void *matrix_second, void *result, const uint16_t N, const uint16_t K, const uint16_t M)
{
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(2s);
    auto devices = mtlpp::Device::CopyAllDevices();
    //mtlpp::Device device = mtlpp::Device::CreateSystemDefaultDevice();
    std::cout << "I found " << sizeof(devices) / sizeof(devices[0]) << " devices" << endl;
    for (uint8_t idev = 0; idev < devices.GetSize(); idev++)
    {
        auto dev = devices[idev];
        cout << dev.GetName().GetCStr() << endl;
        cout << "It is " << (dev.IsLowPower() ? "" : " not ") << "low power" << endl;
        cout << "It is " << (dev.IsRemovable() ? "" : " not ") << "removable" << endl;
        cout << "It has " << (dev.HasUnifiedMemory() ? "" : " not ") << "unified memory" << endl;
    }

    auto device = devices[0];
    assert(device);

    const char shadersSrc[] = R"""(
        #include "shaders/matrix.metal"
    )""";

    mtlpp::Library library = device.NewLibrary(shadersSrc, mtlpp::CompileOptions(), nullptr);
    assert(library);
    mtlpp::Function matmul = library.NewFunction("matmul");
    assert(matmul);

    mtlpp::ComputePipelineState computePipelineState = device.NewComputePipelineState(matmul, nullptr);
    assert(computePipelineState);

    mtlpp::CommandQueue commandQueue = device.NewCommandQueue();
    assert(commandQueue);

    mtlpp::Buffer aBuffer = device.NewBuffer(sizeof(float) * N * K, mtlpp::ResourceOptions::StorageModeManaged);
    assert(aBuffer);
    mtlpp::Buffer bBuffer = device.NewBuffer(sizeof(float) * K * M, mtlpp::ResourceOptions::StorageModeManaged);
    assert(bBuffer);
    mtlpp::Buffer paramsBuffer = device.NewBuffer(sizeof(uint16_t) * 3, mtlpp::ResourceOptions::StorageModeManaged);
    assert(paramsBuffer);

    mtlpp::Buffer outBuffer = device.NewBuffer(sizeof(float) * N * M, mtlpp::ResourceOptions::StorageModeManaged);
    assert(outBuffer);

    // update input data
    {

        float *aData = static_cast<float *>(aBuffer.GetContents());
        float *bData = static_cast<float *>(bBuffer.GetContents());
        uint16_t *paramsData = static_cast<uint16_t *>(paramsBuffer.GetContents());

        std::memcpy(aData, matrix_first, N * K * sizeof(float));
        std::memcpy(bData, matrix_second, K * M * sizeof(float));

        paramsData[0] = N;
        paramsData[1] = K;
        paramsData[2] = M;
        aBuffer.DidModify(ns::Range(0, sizeof(float) * N * K));
        bBuffer.DidModify(ns::Range(0, sizeof(float) * K * M));
        paramsBuffer.DidModify(ns::Range(0, sizeof(uint16_t) * 3));
    }

    auto gpu_start = std::chrono::steady_clock::now();
    mtlpp::CommandBuffer commandBuffer = commandQueue.CommandBuffer();
    assert(commandBuffer);

    mtlpp::ComputeCommandEncoder commandEncoder = commandBuffer.ComputeCommandEncoder();
    commandEncoder.SetBuffer(aBuffer, 0, 0);
    commandEncoder.SetBuffer(bBuffer, 0, 1);
    commandEncoder.SetBuffer(outBuffer, 0, 2);
    commandEncoder.SetBuffer(paramsBuffer, 0, 3);
    commandEncoder.SetComputePipelineState(computePipelineState);
    commandEncoder.DispatchThreadgroups(
        mtlpp::Size(1, 1, 1),
        mtlpp::Size(N * M, 1, 1));
    commandEncoder.EndEncoding();

    mtlpp::BlitCommandEncoder blitCommandEncoder = commandBuffer.BlitCommandEncoder();
    blitCommandEncoder.Synchronize(outBuffer);
    blitCommandEncoder.EndEncoding();

    commandBuffer.Commit();
    commandBuffer.WaitUntilCompleted();

    auto gpu_end = std::chrono::steady_clock::now();

    {
        float *outData = static_cast<float *>(outBuffer.GetContents());
        std::memmove((float *)result, outData, N * M * sizeof(float));
    }

    auto gpu_time = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(gpu_end - gpu_start).count());
    std::cout << "Time (GPU[Metal]) = " << gpu_time << "[ms]" << std::endl;
}