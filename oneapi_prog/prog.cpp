#include <prog.hpp>
#include <CL/sycl.hpp>

using namespace sycl;

queue q;

std::string clComputeModule::_getDeviceInfo(){
    return q.get_device().get_info<info::device::name>();
}

void clComputeModule::vecAdd(vecArr a, vecArr b){
    buffer<int, 1> vectorA_buffer(a, range<1>(vecN));
    buffer<int, 1> vectorB_buffer(b, range<1>(vecN));
    q.submit([&](handler &h) {
        auto vectorA_accessor =
                vectorA_buffer.get_access<access::mode::read_write>(h);
        auto vectorB_accessor = vectorB_buffer.get_access<access::mode::read>(h);
        h.parallel_for<class test>(range<1>(vecN), [=](id<1> index) {
            vectorA_accessor[index] += vectorB_accessor[index];
        });
    });
    q.wait();
    vectorA_buffer.get_access<access::mode::read>();
}


