/*
1. client是在虚拟机上面配置的 192.168.123.52 ens33 虚拟机桥接 复制物理网络接口
   g++ -o client client.cpp -L/usr/local/lib -lvsomeip3
   VSOMEIP_CONFIGURATION=vsomeip_client.json ./client
*/
#include <vsomeip/vsomeip.hpp>
#include <iostream>

#define SERVICE_ID 0x1234
#define INSTANCE_ID 0x5678
#define EVENT_ID 0x8778
#define EVENTGROUP_ID 0x4465

std::shared_ptr<vsomeip::application> app;

void on_message(const std::shared_ptr<vsomeip::message> &msg) {
    std::shared_ptr<vsomeip::payload> payload = msg->get_payload();
    std::string data(reinterpret_cast<const char*>(payload->get_data()), payload->get_length());
    std::cout << "Received: " << data << std::endl;
    std::cout.flush();
}

void on_availability(vsomeip::service_t, vsomeip::instance_t, bool is_available) {
    static bool subscribed = false;
    if (is_available && !subscribed) {
        std::set<vsomeip::eventgroup_t> its_groups;
        its_groups.insert(EVENTGROUP_ID);
        
        // 修改这里：使用 vsomeip::reliability_type_e::RT_RELIABLE 替代 true
        app->request_event(
            SERVICE_ID, 
            INSTANCE_ID, 
            EVENT_ID,
            its_groups, 
            vsomeip::event_type_e::ET_FIELD,
            vsomeip::reliability_type_e::RT_RELIABLE  // 正确的可靠性类型
        );
        
        app->subscribe(SERVICE_ID, INSTANCE_ID, EVENTGROUP_ID);
        subscribed = true;
        std::cout << "Subscribed to event group." << std::endl;
    }
}

int main() {
    app = vsomeip::runtime::get()->create_application("HelloClient");
    app->init();
    
    app->register_availability_handler(SERVICE_ID, INSTANCE_ID, on_availability);
    app->request_service(SERVICE_ID, INSTANCE_ID);
    app->register_message_handler(SERVICE_ID, INSTANCE_ID, EVENT_ID, on_message);
    
    app->start();
    return 0;
}
