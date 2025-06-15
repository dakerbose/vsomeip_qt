/*
 * Function : init_communication
 * Description : Initialising SomeIP communication
 * Returns : Nothing
 * Param : void
 * Author: Athul PK
 */

#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
#include "csignal"
#endif

#include "communication.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <cluster.h>
#include <QThread>
#include <vsomeip/vsomeip.hpp>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>

extern Cluster *cluster;
s_vehicle_data_t data;
std::shared_ptr<vsomeip::application> app;

std::mutex mutex;
std::condition_variable condition;
bool service_available = false; // 共享标志

void on_message(const std::shared_ptr<vsomeip::message> &_response) {
    std::stringstream its_message;
    its_message << "CLIENT: received a notification for event ["
                << std::setw(4) << std::setfill('0') << std::hex
                << _response->get_service() << "."
                << std::setw(4) << std::setfill('0') << std::hex
                << _response->get_instance() << "."
                << std::setw(4) << std::setfill('0') << std::hex
                << _response->get_method() << "] to Client/Session ["
                << std::setw(4) << std::setfill('0') << std::hex
                << _response->get_client() << "/"
                << std::setw(4) << std::setfill('0') << std::hex
                << _response->get_session()
                << "] = ";

    std::shared_ptr<vsomeip::payload> its_payload = _response->get_payload();
    vsomeip::length_t l = its_payload->get_length();
    its_message << "(" << std::dec << l << ") ";

    for (uint32_t i = 0; i < l; ++i) {
        its_message << std::hex << std::setw(2) << std::setfill('0')
                    << (int)its_payload->get_data()[i] << " ";
    }
    std::cout << its_message.str() << std::endl;

    // 数据解析
    if (l < 3) { // 确保 payload 至少有 3 个字节
        std::cerr << "Received payload is too short!" << std::endl;
        return; // 处理错误
    }

    // 解析数据
    const vsomeip::byte_t* data_ptr = its_payload->get_data();
    data.type = static_cast<int>(data_ptr[0]); // 第 1 字节为 type
    data.message = (static_cast<int>(data_ptr[1]) << 8) | static_cast<int>(data_ptr[2]); // 高低字节组合

    std::cout << "CLIENT: Parsed message: type=" << data.type
              << ", value=" << data.message << std::endl;

    // 根据数据类型更新 cluster
    switch (data.type) {
        case TYPE_DATA_SPEED:
            cluster->setSpeed(QVariant(data.message));
            break;
        case TYPE_DATA_RPM:
            cluster->setRpm(data.message);
            break;
        case TYPE_DATA_FUEL:
            cluster->setFuel(data.message);
            break;
        case TYPE_DATA_TEMP:
            cluster->setTemp(data.message);
            break;
        case TYPE_DATA_LI:
            cluster->set_l_value(data.message);
            break;
        case TYPE_DATA_RI:
            cluster->set_r_value(data.message);
            break;
        default:
            std::cerr << "Unknown data type received!" << std::endl;
            break;
    }
}

void on_availability(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available) {
    std::cout << "CLIENT: Service [" << std::hex << _service << "." << _instance
              << "] is " << (_is_available ? "available." : "NOT available.") << std::endl;

    std::unique_lock<std::mutex> lock(mutex);
    service_available = _is_available; // 设置服务可用标志
    condition.notify_one(); // 通知等待的线程
    std::cout << "_is_available: " <<_is_available;
}

void run() {
    std::unique_lock<std::mutex> its_lock(mutex);
    condition.wait(its_lock, [] { return service_available; }); // 等待服务可用

    // 服务可用后请求事件和订阅
    std::set<vsomeip::eventgroup_t> its_groups;
    its_groups.insert(SAMPLE_EVENTGROUP_ID);
    app->request_event(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENT_ID, its_groups, vsomeip::event_type_e::ET_FIELD);
    app->subscribe(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENTGROUP_ID);
    std::cout << "CLIENT: Event requested and subscribed successfully." << std::endl;
}

void *init_communication(void *) {
    // 强制加载配置文件
    setenv("VSOMEIP_CONFIGURATION", "../config/vsomeip_client.json", 1);
    // setenv("VSOMEIP_CONFIGURATION", JSON_CONFIG_FILE, 1);
    QThread::sleep(2); // 等待服务初始化
    
    app = vsomeip::runtime::get()->create_application("Dashboard");
    app->init();
    app->register_availability_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, on_availability);
    app->request_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
    app->register_message_handler(vsomeip::ANY_SERVICE, vsomeip::ANY_INSTANCE, vsomeip::ANY_METHOD, on_message);

    std::thread sender(run); // 启动事件处理线程
    app->start(); // 启动应用

    return nullptr;
}
