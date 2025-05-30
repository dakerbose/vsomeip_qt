/*
2. service是在树莓派 wlan0上面配置的192.168.123.154
   g++ -std=c++11 server.cpp -o server -lvsomeip3 -pthread
   VSOMEIP_CONFIGURATION=vsomeip_server.json ./server

*/
#include <vsomeip/vsomeip.hpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <csignal>
#define SERVICE_ID 0x1234
#define INSTANCE_ID 0x5678
#define EVENT_ID 0x8778
#define EVENTGROUP_ID 0x4465
std::shared_ptr<vsomeip::application> app;
std::atomic<bool> running(true);


int main() {

    app = vsomeip::runtime::get()->create_application("HelloServer");
    app->init();
    
    // 注册服务
    app->offer_service(SERVICE_ID, INSTANCE_ID);
    
    // 提供事件
    std::set<vsomeip::eventgroup_t> its_groups;
    its_groups.insert(EVENTGROUP_ID);
    app->offer_event(SERVICE_ID, INSTANCE_ID, EVENT_ID, its_groups, vsomeip::event_type_e::ET_FIELD);
    
    std::thread sender([&]() {
        uint8_t counter = 0;
        while (running) {  // 使用原子变量控制循环
            std::shared_ptr<vsomeip::payload> payload = vsomeip::runtime::get()->create_payload();
            std::string msg = "Hello World " + std::to_string(++counter);
            payload->set_data(reinterpret_cast<const vsomeip::byte_t*>(msg.c_str()), msg.size());
            
            // 添加发送状态检查
            if (!app->is_available(SERVICE_ID, INSTANCE_ID)) {
                std::cerr << "Service not available, retrying..." << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                continue;
            }
            
            app->notify(SERVICE_ID, INSTANCE_ID, EVENT_ID, payload);
            std::cout << "Sent: " << msg << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));  // 确保严格间隔
        }
    });
    
    app->start();
    return 0;
}
