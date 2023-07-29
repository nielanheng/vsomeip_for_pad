#include <chrono>
#include <condition_variable>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>

#include <vsomeip/vsomeip.hpp>

#define SAMPLE_SERVICE_ID       0xA405
#define SAMPLE_INSTANCE_ID      0x5678
#define SAMPLE_METHOD_ID        0x0421

#define SAMPLE_EVENT_ID_MISSONSTATE 0x8001
#define SAMPLE_EVENT_ID_OBJECTLIST  0x8002
#define SAMPLE_EVENTGROUP_ID    0x0002

class event_client{
public:
    event_client(bool _use_tcp) :
            app_(vsomeip::runtime::get()->create_application()), 
            use_tcp_(_use_tcp) {
    }

    bool init() {
        if (!app_->init()) {
            std::cerr << "Couldn't initialize application" << std::endl;
            return false;
        }
        std::cout << "Client settings [protocol="
                << (use_tcp_ ? "TCP" : "UDP")
                << "]"
                << std::endl;

        app_->register_state_handler(
                std::bind(&event_client::on_state, this,
                        std::placeholders::_1));

        // app_->register_message_handler(
        //         vsomeip::ANY_SERVICE, SAMPLE_INSTANCE_ID, vsomeip::ANY_METHOD,
        //         std::bind(&event_client::on_message, this,
        //                 std::placeholders::_1));
        
        app_->register_message_handler(
                vsomeip::ANY_SERVICE, SAMPLE_INSTANCE_ID, vsomeip::ANY_METHOD,
                std::bind(&event_client::on_message, this,
                        std::placeholders::_1));

        app_->register_availability_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID,
                std::bind(&event_client::on_availability,
                          this,
                          std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

        std::set<vsomeip::eventgroup_t> its_groups;
        its_groups.insert(SAMPLE_EVENTGROUP_ID);
        app_->request_event(
                SAMPLE_SERVICE_ID,
                SAMPLE_INSTANCE_ID,
                SAMPLE_EVENT_ID_MISSONSTATE,
                its_groups,
                vsomeip::event_type_e::ET_EVENT);

        app_->request_event(
                SAMPLE_SERVICE_ID,
                SAMPLE_INSTANCE_ID,
                SAMPLE_EVENT_ID_OBJECTLIST,
                its_groups,
                vsomeip::event_type_e::ET_EVENT);
    
        app_->subscribe(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENTGROUP_ID);

        return true;
    }

    void start() {
       app_->start();
    }

    void on_state(vsomeip::state_type_e _state) {
        if (_state == vsomeip::state_type_e::ST_REGISTERED) {
            app_->request_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
        }
    }

    void on_availability(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available) {
        std::cout << "Service ["
                << std::setw(4) << std::setfill('0') << std::hex << _service << "." << _instance
                << "] is "
                << (_is_available ? "available." : "NOT available.")
                << std::endl;
    }

    void on_message(const std::shared_ptr<vsomeip::message> &_response) {
        std::stringstream its_message;
        its_message << "Received a notification for Event ["
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
        std::shared_ptr<vsomeip::payload> its_payload =
                _response->get_payload();
        its_message << "(" << std::dec << its_payload->get_length() << ") ";
        for (uint32_t i = 0; i < its_payload->get_length(); ++i)
            its_message << std::hex << std::setw(2) << std::setfill('0')
                << (int) its_payload->get_data()[i] << " ";
        std::cout << its_message.str() << std::endl;
    }

private:
    std::shared_ptr< vsomeip::application > app_;
    bool use_tcp_;

};

int main(int argc, char **argv) {
    bool use_tcp = false;

    std::string tcp_enable("--tcp");
    std::string udp_enable("--udp");

    int i = 1;
    while (i < argc) {
        if (tcp_enable == argv[i]) {
            use_tcp = true;
        } else if (udp_enable == argv[i]) {
            use_tcp = false;
        }
        i++;
    }

    event_client its_event_client(use_tcp);

    if (its_event_client.init()) {
        its_event_client.start();
        return 0;
    } else {
        return 1;
    }
}