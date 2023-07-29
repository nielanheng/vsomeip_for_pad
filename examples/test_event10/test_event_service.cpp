#include <chrono>
#include <condition_variable>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>
#include"Message.hpp"

#include <vsomeip/vsomeip.hpp>

#define SAMPLE_SERVICE_ID       0xA405
#define SAMPLE_INSTANCE_ID      0x5678
#define SAMPLE_METHOD_ID        0x0421

#define SAMPLE_EVENT_ID_MISSONSTATE 0x8001
#define SAMPLE_EVENT_ID_OBJECTLIST  0x8002
#define EVENT_ID_GETGENERAL 0x8001
#define EVENT_ID_GETREALTIME 0x8002
#define EVENT_ID_GEGENERALEXT 0x8003
// #define SAMPLE_GET_METHOD_ID    0x0001
//#define SAMPLE_SET_METHOD_ID    0x0002

#define SAMPLE_EVENTGROUP_ID    0x0002

class event_service{

public:
    event_service(bool _use_tcp, uint32_t _cycle) :
            app_(vsomeip::runtime::get()->create_application("Event_Service")),
            is_registered_(false),
            use_tcp_(_use_tcp),
            cycle_(_cycle),
            blocked_(false),
            running_(true),
            is_offered_(false),
            offer_thread_(std::bind(&event_service::run, this)),
            notify_thread1_(std::bind(&event_service::notify_mission, this)),
            notify_thread2_(std::bind(&event_service::notify_objectlist, this)),
            notify_thread3_(std::bind(&event_service::notify_getgeneralext, this))
            {
            }

    bool init() {
        std::lock_guard<std::mutex> its_lock(mutex_);

        if (!app_->init()) {
            std::cerr << "Couldn't initialize application" << std::endl;
            return false;
        }
        app_->register_state_handler(
                std::bind(&event_service::on_state, this,
                        std::placeholders::_1));

        std::set<vsomeip::eventgroup_t> its_groups;
        its_groups.insert(SAMPLE_EVENTGROUP_ID);
        app_->offer_event(
                SAMPLE_SERVICE_ID,
                SAMPLE_INSTANCE_ID,
                SAMPLE_EVENT_ID_MISSONSTATE,
                its_groups,
                vsomeip::event_type_e::ET_EVENT, std::chrono::milliseconds::zero(),
                false, false, nullptr, vsomeip::reliability_type_e::RT_UNKNOWN);

        app_->offer_event(
                SAMPLE_SERVICE_ID,
                SAMPLE_INSTANCE_ID,
                SAMPLE_EVENT_ID_OBJECTLIST,
                its_groups,
                vsomeip::event_type_e::ET_EVENT, std::chrono::milliseconds::zero(),
                false, false, nullptr, vsomeip::reliability_type_e::RT_UNKNOWN);

        app_->offer_event(
                SAMPLE_SERVICE_ID,
                SAMPLE_INSTANCE_ID,
                EVENT_ID_GEGENERALEXT,
                its_groups,
                vsomeip::event_type_e::ET_EVENT, std::chrono::milliseconds::zero(),
                false, false, nullptr, vsomeip::reliability_type_e::RT_UNKNOWN);

        {
            std::lock_guard<std::mutex> its_lock(payload_mutex_);
            payload_ = vsomeip::runtime::get()->create_payload();
        }

        blocked_ = true;
        condition_.notify_one();
        return true;
    }

    void start() {
        app_->start();
    }

#ifndef VSOMEIP_ENABLE_SIGNAL_HANDLING
    /*
     * Handle signal to shutdown
     */
    void stop() {
        running_ = false;
        blocked_ = true;
        condition_.notify_one();
        notify_condition_.notify_one();
        app_->clear_all_handler();
        stop_offer();
        offer_thread_.join();
        notify_thread1_.join();
        notify_thread2_.join();
        app_->stop();
    }
#endif

    void on_state(vsomeip::state_type_e _state) {
        std::cout << "Application " << app_->get_name() << " is "
        << (_state == vsomeip::state_type_e::ST_REGISTERED ?
                "registered." : "deregistered.") << std::endl;

        if (_state == vsomeip::state_type_e::ST_REGISTERED) {
            if (!is_registered_) {
                is_registered_ = true;
            }
        } else {
            is_registered_ = false;
        }
    }

    void run() {
        std::unique_lock<std::mutex> its_lock(mutex_);
        while (!blocked_)
            condition_.wait(its_lock);

        bool is_offer(true);
        while (running_) {
            if (is_offer)
                offer();
            else
                stop_offer();

            for (int i = 0; i < 10 && running_; i++)
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            is_offer = !is_offer;
        }
    }

    void notify_mission() {
        std::shared_ptr<vsomeip::message> its_message
            = vsomeip::runtime::get()->create_request(use_tcp_);

        its_message->set_service(SAMPLE_SERVICE_ID);
        its_message->set_instance(SAMPLE_INSTANCE_ID);
        its_message->set_method(SAMPLE_EVENT_ID_MISSONSTATE);

        vsomeip::byte_t its_data[10]={1,2,3,4,5,6,7,8};
        uint32_t its_size = 1;

        while (running_) {
            std::unique_lock<std::mutex> its_lock(notify_mutex_);
            while (!is_offered_ && running_)
                notify_condition_.wait(its_lock);
            while (is_offered_ && running_) {
                if (its_size == sizeof(its_data))
                    its_size = 1;

                for (uint32_t i = 0; i < its_size; ++i)
                    its_data[i] = static_cast<uint8_t>(i);

                {
                    std::lock_guard<std::mutex> its_lock(payload_mutex_);
                    payload_->set_data(its_data, its_size);

                    std::cout << "Setting event (Length=" << std::dec << its_size << ")." << std::endl;
                    std::cout << "The mission event data is " << int(its_data[1]) << "." << std::endl;
                    app_->notify(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENT_ID_MISSONSTATE, payload_);
                }

                its_size++;

                std::this_thread::sleep_for(std::chrono::milliseconds(cycle_));
            }
        }
    }

    void notify_objectlist() {
        std::shared_ptr<vsomeip::message> its_message
            = vsomeip::runtime::get()->create_request(use_tcp_);

        its_message->set_service(SAMPLE_SERVICE_ID);
        its_message->set_instance(SAMPLE_INSTANCE_ID);
        its_message->set_method(SAMPLE_EVENT_ID_OBJECTLIST);

        vsomeip::byte_t its_data[10];
        uint32_t its_size = 1;

        while (running_) {
            std::unique_lock<std::mutex> its_lock(notify_mutex_);
            while (!is_offered_ && running_)
                notify_condition_.wait(its_lock);
            while (is_offered_ && running_) {
                if (its_size == sizeof(its_data))
                    its_size = 1;

                for (uint32_t i = 0; i < its_size; ++i)
                    its_data[i] = static_cast<uint8_t>(i);

                {
                    std::lock_guard<std::mutex> its_lock(payload_mutex_);
                    payload_->set_data(its_data, its_size);

                    std::cout << "Setting event (Length=" << std::dec << its_size << ")." << std::endl;
                    std::cout << "The objectlist event data is " << int(its_data[2]) << "." << std::endl;
                    app_->notify(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENT_ID_MISSONSTATE, payload_);
                }

                its_size++;

                std::this_thread::sleep_for(std::chrono::milliseconds(cycle_));
            }
        }
    }


    void notify_getgeneralext() {
        std::shared_ptr<vsomeip::message> its_message
            = vsomeip::runtime::get()->create_request(use_tcp_);

        its_message->set_service(SAMPLE_SERVICE_ID);
        its_message->set_instance(SAMPLE_INSTANCE_ID);
        its_message->set_method(EVENT_ID_GEGENERALEXT);

        vsomeip::byte_t its_data[10];
        uint32_t its_size = 1;

        while (running_) {
            std::unique_lock<std::mutex> its_lock(notify_mutex_);
            while (!is_offered_ && running_)
                notify_condition_.wait(its_lock);
            while (is_offered_ && running_) {
                if (its_size == sizeof(its_data))
                    its_size = 1;

                for (uint32_t i = 0; i < its_size; ++i)
                    its_data[i] = static_cast<uint8_t>(i);

                {
                    std::lock_guard<std::mutex> its_lock(payload_mutex_);

                    std::cout << "Setting event (Length=" << std::dec << its_size << ")." << std::endl;
                    std::cout << "The getgeneralext event data is " << int(its_data[2]) << "." << std::endl;

                    General_Ext_StsType test_sample;
                    test_sample.SystemMode=1;
                    test_sample.HighVoltage=2;
                    test_sample.LowVoltage=3;
                    test_sample.LowVoltagePower=4;
                    test_sample.HighVoltagePower=5;
                    test_sample.EquipmentNo=6;
                    test_sample.EmergencyStopSts=7;
                    test_sample.EngineTemp=8;
                    test_sample.IsgMotorTemp=9;
                    test_sample.LeftMotorTemp=10;
                    test_sample.LeftMotorControllerTemp=11;
                    test_sample.RightMotorTemp=12;
                    test_sample.RightMotorControllerTemp=13;
                    test_sample.Longitude=14;
                    test_sample.Latitude=15;
                    test_sample.Course=16;
                    test_sample.EngineSpeed=17;
                    test_sample.ReqGenerationPower=18;
                    test_sample.ActGenerationPower=19;
                    test_sample.ActBrakePressure=20;
                    test_sample.TotalMileage=21;
                    test_sample.RemainMileagePureElectricity=22;
                    test_sample.TotalRemainMileage=23;
                    test_sample.RemainOil=24;
                    test_sample.RemainElectricity=25;
                    test_sample.SteerMode=26;
                    test_sample.HornOnOffSts=27;
                    test_sample.CornerLamp=28;
                    test_sample.DippedHeadLightl=29;
                    test_sample.HighBeam=30;
                    test_sample.EmergencyLamp=31;
                    test_sample.Altitude=32;
                    test_sample.ErrorCode=33;
                    test_sample.AngelPitch=34;
                    test_sample.AngleRoll=35;
                    test_sample.IMU_STS=36;
                    test_sample.Package_a=37;
                    test_sample.b=38;
                    test_sample.c=39;
                    test_sample.d=40;
                    test_sample.e=41;
                    test_sample.f=42;
                    test_sample.g=43;
                    test_sample.h=44;
                    test_sample.i=45;
                    test_sample.k=46;
                    test_sample.l=47;
                    test_sample.m=48;
                    std::vector<vsomeip::byte_t> res_data(reinterpret_cast<const uint8_t *>(&test_sample),
                                                   reinterpret_cast<const uint8_t *>(&test_sample) + sizeof(General_Ext_StsType));
                    payload_->set_data(res_data);
                    app_->notify(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, EVENT_ID_GEGENERALEXT, payload_);
                }

                its_size++;

                std::this_thread::sleep_for(std::chrono::milliseconds(cycle_));
            }
        }
    }


    void offer() {
        std::lock_guard<std::mutex> its_lock(notify_mutex_);
        app_->offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
        is_offered_ = true;
        notify_condition_.notify_one();
    }

    void stop_offer() {
        app_->stop_offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
        is_offered_ = false;
    }
    

private:
    std::shared_ptr<vsomeip::application> app_;
    bool is_registered_;
    bool use_tcp_;
    uint32_t cycle_;

    std::mutex mutex_;
    std::condition_variable condition_;
    bool blocked_;
    bool running_;

    std::mutex notify_mutex_;
    std::condition_variable notify_condition_;
    bool is_offered_;

    std::mutex payload_mutex_;
    std::shared_ptr<vsomeip::payload> payload_;

    // blocked_ / is_offered_ must be initialized before starting the threads!
    std::thread offer_thread_;
    std::thread notify_thread1_;
    std::thread notify_thread2_;
    std::thread notify_thread3_;


};

int main(int argc, char **argv) {
    bool use_tcp = false;
    uint32_t cycle = 1000; // default 1s,单位是毫秒

    std::string tcp_enable("--tcp");
    std::string udp_enable("--udp");
    std::string cycle_arg("--cycle");

    for (int i = 1; i < argc; i++) {
        if (tcp_enable == argv[i]) {
            use_tcp = true;
            break;
        }
        if (udp_enable == argv[i]) {
            use_tcp = false;
            break;
        }

        if (cycle_arg == argv[i] && i + 1 < argc) {
            i++;
            std::stringstream converter;
            converter << argv[i];
            converter >> cycle;
        }
    }

    event_service its_sample(use_tcp, cycle);

    if (its_sample.init()) {
        its_sample.start();
        return 0;
    } else {
        return 1;
    }
}
