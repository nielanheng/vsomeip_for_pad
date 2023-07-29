// Copyright (C) 2015-2017 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#include <vsomeip/vsomeip.hpp>
#include <chrono>
#include <thread>
#include <condition_variable>
#include <mutex>
#include "Message.hpp"

/*#if defined ANDROID || defined __ANDROID__
#include "android/log.h"
#define LOG_TAG "hello_world_service"
#define LOG_INF(...) fprintf(stdout, __VA_ARGS__), fprintf(stdout, "\n"), (void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, ##__VA_ARGS__)
#define LOG_ERR(...) fprintf(stderr, __VA_ARGS__), fprintf(stderr, "\n"), (void)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, ##__VA_ARGS__)
#else
#include <cstdio>
#define LOG_INF(...) fprintf(stdout, __VA_ARGS__), fprintf(stdout, "\n")
#define LOG_ERR(...) fprintf(stderr, __VA_ARGS__), fprintf(stderr, "\n")
#endif
*/

static vsomeip::service_t service_id = 0xA701;
static vsomeip::instance_t service_instance_id = 0x0001;

static vsomeip::method_t service_method_id_pathpoint = 0x3333;
static vsomeip::method_t service_method_id_trajectoryfollow = 0x0001;
static vsomeip::method_t service_method_id_objectfollow = 0x0002;
static vsomeip::method_t service_method_id_targetpointnavi = 0x0003;
static vsomeip::method_t service_method_id_returnhome = 0x0004;
static vsomeip::method_t service_method_id_patrol = 0x0005;
static vsomeip::method_t service_method_id_missioncontrol = 0x0006;
static vsomeip::method_t service_method_id_videoconfig = 0x0007;
static vsomeip::method_t service_method_id_mission = 0x3334;
static vsomeip::method_t service_method_id_objectinfo = 0x3335;
static vsomeip::method_t service_method_id_objectlist = 0x3336;

class   test_service {
public:
    // Get the vSomeIP runtime and
    // create a application via the runtime, we could pass the application name
    // here otherwise the name supplied via the VSOMEIP_APPLICATION_NAME
    // environment variable is used
    test_service() :
                    rtm_(vsomeip::runtime::get()),
                    app_(rtm_->create_application()),
                    stop_(false)
//                    stop_thread_(std::bind(&test_service::stop, this))
    {
    }

    ~test_service()
    {
        stop_thread_.join();
    }

    bool init()
    {
        // init the application
        if (!app_->init()) {
            // LOG_ERR("Couldn't initialize application");
            return false;
        }

        // register a message handler callback for messages sent to our service
        // app_->register_message_handler(service_id, service_instance_id,
                // service_method_id,
                // std::bind(&hello_world_service::on_message_cbk, this,
                //         std::placeholders::_1));

        // register a state handler to get called back after registration at the
        // runtime was successful
        app_->register_state_handler(
                std::bind(&test_service::on_state_cbk, this,
                        std::placeholders::_1));

        // PathPoint
        app_->register_message_handler(service_id, service_instance_id,
                service_method_id_pathpoint,
                std::bind(&test_service::on_message_cbk_pathpoint, this,
                        std::placeholders::_1));

        // TrajectoryFollow
        app_->register_message_handler(service_id, service_instance_id,
                service_method_id_trajectoryfollow,
                std::bind(&test_service::on_message_cbk_trajectoryfollow, this,
                        std::placeholders::_1));
        
        // ObjectFollow
        app_->register_message_handler(service_id, service_instance_id,
                service_method_id_objectfollow,
                std::bind(&test_service::on_message_cbk_objectfollow, this,
                        std::placeholders::_1));
        
        // TargetPointNavi
        app_->register_message_handler(service_id, service_instance_id,
                service_method_id_targetpointnavi,
                std::bind(&test_service::on_message_cbk_targetpointnavi, this,
                        std::placeholders::_1));
        
        // ReturnHomeType
        app_->register_message_handler(service_id, service_instance_id,
                service_method_id_returnhome,
                std::bind(&test_service::on_message_cbk_returnhome, this,
                        std::placeholders::_1));
        
        // PatrolType
        app_->register_message_handler(service_id, service_instance_id,
                service_method_id_patrol,
                std::bind(&test_service::on_message_cbk_patrol, this,
                        std::placeholders::_1));
        
        // MissionControlType
        app_->register_message_handler(service_id, service_instance_id,
                service_method_id_missioncontrol,
                std::bind(&test_service::on_message_cbk_missioncontrol, this,
                        std::placeholders::_1));
        
        // VideoConfigType
        app_->register_message_handler(service_id, service_instance_id,
                service_method_id_videoconfig,
                std::bind(&test_service::on_message_cbk_videoconfig, this,
                        std::placeholders::_1));
        
        // MissionType
        app_->register_message_handler(service_id, service_instance_id,
                service_method_id_mission,
                std::bind(&test_service::on_message_cbk_mission, this,
                        std::placeholders::_1));
        
        // ObjectInfo
        app_->register_message_handler(service_id, service_instance_id,
                service_method_id_objectinfo,
                std::bind(&test_service::on_message_cbk_objectinfo, this,
                        std::placeholders::_1));
                             
        // ObjectList
        app_->register_message_handler(service_id, service_instance_id,
                service_method_id_objectlist,
                std::bind(&test_service::on_message_cbk_objectlist, this,
                        std::placeholders::_1));

        return true;
    }

    void start()
    {
        // start the application and wait for the on_event callback to be called
        // this method only returns when app_->stop() is called
        app_->start();
    }

    void stop()
    {
        std::unique_lock<std::mutex> its_lock(mutex_);
        while(!stop_) {
            condition_.wait(its_lock);
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
        // Stop offering the service
        app_->stop_offer_service(service_id, service_instance_id);
        // unregister the state handler
        app_->unregister_state_handler();
        // unregister the message handler
        // app_->unregister_message_handler(service_id, service_instance_id,
        //        service_method_id);
        
        // PathPoint
        app_->unregister_message_handler(service_id, service_instance_id,
                service_method_id_pathpoint);

        // TrajectoryFollow
        app_->unregister_message_handler(service_id, service_instance_id,
                service_method_id_trajectoryfollow);


        // ObjectFollow
        app_->unregister_message_handler(service_id, service_instance_id,
                service_method_id_objectfollow);


        // TargetPointNavi
        app_->unregister_message_handler(service_id, service_instance_id,
                service_method_id_targetpointnavi);


        // ReturnHomeType
        app_->unregister_message_handler(service_id, service_instance_id,
                service_method_id_returnhome);


        // PatrolType
        app_->unregister_message_handler(service_id, service_instance_id,
                service_method_id_patrol);

        // MissionControlType
        app_->unregister_message_handler(service_id, service_instance_id,
                service_method_id_missioncontrol);

        // VideoConfigType
        app_->unregister_message_handler(service_id, service_instance_id,
                service_method_id_videoconfig);

        // MissionType
        app_->unregister_message_handler(service_id, service_instance_id,
                service_method_id_mission);

        // ObjectInfo
        app_->unregister_message_handler(service_id, service_instance_id,
                service_method_id_objectinfo);

        //ObjectList
        app_->unregister_message_handler(service_id, service_instance_id,
                service_method_id_objectlist);
        

        // shutdown the application
        app_->stop();
    }

    void terminate() {
        std::lock_guard<std::mutex> its_lock(mutex_);
        stop_ = true;
        condition_.notify_one();
    }

    void on_state_cbk(vsomeip::state_type_e _state)
    {
        if(_state == vsomeip::state_type_e::ST_REGISTERED)
        {
            // we are registered at the runtime and can offer our service
            app_->offer_service(service_id, service_instance_id);
        }
    }

// PathPoint
    void on_message_cbk_pathpoint(const std::shared_ptr<vsomeip::message> &_request)
    {
        // Create a response based upon the request
        std::shared_ptr<vsomeip::message> resp = rtm_->create_response(_request);

        // make the action of serialize
        const PathPointType *recive_point = reinterpret_cast<const PathPointType *>(_request->get_payload()->get_data());

        // use the extracted VehicleData
        std::cout << "...............................Received pathpoint data nlh....................................."
                  << std::endl;
        std::cout << "Received Longitude:" << recive_point->Longitude << std::endl;
        std::cout << "Received Latitude:" << recive_point->Latitude << std::endl;
        std::cout << "Received Heading:" << recive_point->Heading << std::endl;
        std::cout << "Received Property:" << int(recive_point->Property) << std::endl;

        // Construct string to send back
        // Creatr a payload which will be sent back to the client
        std::shared_ptr<vsomeip::payload> resp_pl = rtm_->create_payload();
        std::vector<vsomeip::byte_t> res_data;
        uint8_t Std_ReturnCodeType = 0x1;
        res_data.push_back(Std_ReturnCodeType);

        resp_pl->set_data(res_data);
        resp->set_payload(resp_pl);

        // Send the response back
        app_->send(resp);
        // we have finished
        // terminate();
    }

// TrajectoryFollow
    void on_message_cbk_trajectoryfollow(const std::shared_ptr<vsomeip::message> &_request)
    {
        // Create a response based upon the request
        std::shared_ptr<vsomeip::message> resp = rtm_->create_response(_request);

        // make the action of serialize
        const TrajectoryFollowType *recive_point = reinterpret_cast<const TrajectoryFollowType *>(_request->get_payload()->get_data());

        // use the extracted VehicleData
        std::cout << "...............................Received trajectoryfollow data....................................."
                  << std::endl;
        std::cout << "Received MissionID:" << int(recive_point->MissionID) << std::endl;
        std::cout << "Received MissionPoints:" << recive_point->MissionPoints << std::endl;

        // Construct string to send back
        // Creatr a payload which will be sent back to the client
        std::shared_ptr<vsomeip::payload> resp_pl = rtm_->create_payload();
        std::vector<vsomeip::byte_t> res_data;
        uint8_t Std_ReturnCodeType = 0x1;
        res_data.push_back(Std_ReturnCodeType);

        resp_pl->set_data(res_data);
        resp->set_payload(resp_pl);

        // Send the response back
        app_->send(resp);
        // we have finished
        // terminate();
    }

// ObjectFollow
    void on_message_cbk_objectfollow(const std::shared_ptr<vsomeip::message> &_request)
    {
        // Create a response based upon the request
        std::shared_ptr<vsomeip::message> resp = rtm_->create_response(_request);

        // make the action of serialize
        const ObjectFollowType *recive_point = reinterpret_cast<const ObjectFollowType *>(_request->get_payload()->get_data());

        // use the extracted VehicleData
        std::cout << "...............................Received objectfollow data....................................."
                  << std::endl;
        std::cout << "Received MissionID:" << int(recive_point->MissionID) << std::endl;
        std::cout << "Received ObjectID:" << int(recive_point->ObjectID) << std::endl;
        std::cout << "Received Distance:" << recive_point->Distance << std::endl;
        std::cout << "Received Mode:" << int(recive_point->Mode) << std::endl;

        // Construct string to send back
        // Creatr a payload which will be sent back to the client
        std::shared_ptr<vsomeip::payload> resp_pl = rtm_->create_payload();
        std::vector<vsomeip::byte_t> res_data;
        uint8_t Std_ReturnCodeType = 0x1;
        res_data.push_back(Std_ReturnCodeType);

        resp_pl->set_data(res_data);
        resp->set_payload(resp_pl);

        // Send the response back
        app_->send(resp);
        // we have finished
        // terminate();
    }

// TargetPointNavi    
    void on_message_cbk_targetpointnavi(const std::shared_ptr<vsomeip::message> &_request)
    {
        // Create a response based upon the request
        std::shared_ptr<vsomeip::message> resp = rtm_->create_response(_request);

        // make the action of serialize
        const TargetPointNaviType *recive_point = reinterpret_cast<const TargetPointNaviType *>(_request->get_payload()->get_data());


        // use the extracted VehicleData
        std::cout << "...............................Received targetpointnavi data....................................."
                  << std::endl;
        std::cout << "Received MissionID:" << int(recive_point->MissionID) << std::endl;
        std::cout << "Received MissionPoints.Longitude:" << double(recive_point->MissionPoints[0].Longitude) << std::endl;
        std::cout << "Received MissionPoints.Latitude:" << double(recive_point->MissionPoints[0].Latitude) << std::endl;
        std::cout << "Received MissionPoints.Heading:" << double(recive_point->MissionPoints[0].Heading) << std::endl;
        std::cout << "Received MissionPoints.Property:" << int(recive_point->MissionPoints[0].Property) << std::endl;

        // Construct string to send back
        // Creatr a payload which will be sent back to the client
        std::shared_ptr<vsomeip::payload> resp_pl = rtm_->create_payload();
        std::vector<vsomeip::byte_t> res_data;
        uint8_t Std_ReturnCodeType = 0x1;
        res_data.push_back(Std_ReturnCodeType);

        resp_pl->set_data(res_data);
        resp->set_payload(resp_pl);

        // Send the response back
        app_->send(resp);
        // we have finished
        // terminate();
    }

// ReturnHomeType
    void on_message_cbk_returnhome(const std::shared_ptr<vsomeip::message> &_request)
    {
        // Create a response based upon the request
        std::shared_ptr<vsomeip::message> resp = rtm_->create_response(_request);

        // make the action of serialize
        const ReturnHomeType *recive_point = reinterpret_cast<const ReturnHomeType *>(_request->get_payload()->get_data());

        // use the extracted VehicleData
        std::cout << "...............................Received returnhome data....................................."
                  << std::endl;
        std::cout << "Received MissionID:" << int(recive_point->MissionID) << std::endl;
        std::cout << "Received Mode:" << int(recive_point->Mode) << std::endl;


        // Construct string to send back
        // Creatr a payload which will be sent back to the client
        std::shared_ptr<vsomeip::payload> resp_pl = rtm_->create_payload();
        std::vector<vsomeip::byte_t> res_data;
        uint8_t Std_ReturnCodeType = 0x1;
        res_data.push_back(Std_ReturnCodeType);

        resp_pl->set_data(res_data);
        resp->set_payload(resp_pl);

        // Send the response back
        app_->send(resp);
        // we have finished
        // terminate();
    }

// PatrolType
    void on_message_cbk_patrol(const std::shared_ptr<vsomeip::message> &_request)
    {
        // Create a response based upon the request
        std::shared_ptr<vsomeip::message> resp = rtm_->create_response(_request);

        // make the action of serialize
        const PatrolType *recive_point = reinterpret_cast<const PatrolType *>(_request->get_payload()->get_data());

        // use the extracted VehicleData
        std::cout << "...............................Received patrol data....................................."
                  << std::endl;
        std::cout << "Received MissionID:" << int(recive_point->MissionID) << std::endl;
        std::cout << "Received PatrolNum:" << int(recive_point->PatrolNum) << std::endl;
        std::cout << "Received Mode:" << int(recive_point->Mode) << std::endl;
        std::cout << "Received MissionPoints:" << recive_point->MissionPoints << std::endl;

        // Construct string to send back
        // Creatr a payload which will be sent back to the client
        std::shared_ptr<vsomeip::payload> resp_pl = rtm_->create_payload();
        std::vector<vsomeip::byte_t> res_data;
        uint8_t Std_ReturnCodeType = 0x1;
        res_data.push_back(Std_ReturnCodeType);

        resp_pl->set_data(res_data);
        resp->set_payload(resp_pl);

        // Send the response back
        app_->send(resp);
        // we have finished
        // terminate();
    }

// MissionControlType
    void on_message_cbk_missioncontrol(const std::shared_ptr<vsomeip::message> &_request)
    {
        // Create a response based upon the request
        std::shared_ptr<vsomeip::message> resp = rtm_->create_response(_request);

        // make the action of serialize
        const MissionControlType *recive_point = reinterpret_cast<const MissionControlType *>(_request->get_payload()->get_data());

        // use the extracted VehicleData
        std::cout << "...............................Received missioncontrol data....................................."
                  << std::endl;
        std::cout << "Received MissionID:" << int(recive_point->MissionID) << std::endl;
        std::cout << "Received ControlCommand:" << int(recive_point->ControlCommand) << std::endl;


        // Construct string to send back
        // Creatr a payload which will be sent back to the client
        std::shared_ptr<vsomeip::payload> resp_pl = rtm_->create_payload();
        std::vector<vsomeip::byte_t> res_data;
        uint8_t Std_ReturnCodeType = 0x1;
        res_data.push_back(Std_ReturnCodeType);

        resp_pl->set_data(res_data);
        resp->set_payload(resp_pl);

        // Send the response back
        app_->send(resp);
        // we have finished
        // terminate();
    }

// VideoConfigType
    void on_message_cbk_videoconfig(const std::shared_ptr<vsomeip::message> &_request)
    {
        // Create a response based upon the request
        std::shared_ptr<vsomeip::message> resp = rtm_->create_response(_request);

        // make the action of serialize
        const VideoConfigType *recive_point = reinterpret_cast<const VideoConfigType *>(_request->get_payload()->get_data());

        // use the extracted VehicleData
        std::cout << "...............................Received videoconfig data....................................."
                  << std::endl;
        std::cout << "Received Switch:" << int(recive_point->Switch) << std::endl;
        std::cout << "Received Mode:" << int(recive_point->Mode) << std::endl;
        std::cout << "Received Stream:" << int(recive_point->Stream) << std::endl;
        std::cout << "Received Resolution:" << int(recive_point->Resolution) << std::endl;
        std::cout << "Received Source:" << int(recive_point->Source) << std::endl;

        // Construct string to send back
        // Creatr a payload which will be sent back to the client
        std::shared_ptr<vsomeip::payload> resp_pl = rtm_->create_payload();
        std::vector<vsomeip::byte_t> res_data;
        uint8_t Std_ReturnCodeType = 0x1;
        res_data.push_back(Std_ReturnCodeType);

        resp_pl->set_data(res_data);
        resp->set_payload(resp_pl);

        // Send the response back
        app_->send(resp);
        // we have finished
        // terminate();
    }

// MissionType
    void on_message_cbk_mission(const std::shared_ptr<vsomeip::message> &_request)
    {
        // Create a response based upon the request
        std::shared_ptr<vsomeip::message> resp = rtm_->create_response(_request);

        // make the action of serialize
        const MissionType *recive_point = reinterpret_cast<const MissionType *>(_request->get_payload()->get_data());

        // use the extracted VehicleData
        std::cout << "...............................Received mission data....................................."
                  << std::endl;
        std::cout << "Received MissionID:" << int(recive_point->MissionID) << std::endl;
        std::cout << "Received Type:" << int(recive_point->Type) << std::endl;
        std::cout << "Received State:" << int(recive_point->State) << std::endl;
        std::cout << "Received Process:" << int(recive_point->Process) << std::endl;

        // Construct string to send back
        // Creatr a payload which will be sent back to the client
        std::shared_ptr<vsomeip::payload> resp_pl = rtm_->create_payload();
        std::vector<vsomeip::byte_t> res_data;
        uint8_t Std_ReturnCodeType = 0x1;
        res_data.push_back(Std_ReturnCodeType);

        resp_pl->set_data(res_data);
        resp->set_payload(resp_pl);

        // Send the response back
        app_->send(resp);
        // we have finished
        // terminate();
    }

// ObjectInfo
    void on_message_cbk_objectinfo(const std::shared_ptr<vsomeip::message> &_request)
    {
        // Create a response based upon the request
        std::shared_ptr<vsomeip::message> resp = rtm_->create_response(_request);

        // make the action of serialize
        const ObjectInfo *recive_point = reinterpret_cast<const ObjectInfo *>(_request->get_payload()->get_data());

        // use the extracted VehicleData
        std::cout << "...............................Received objectinfo data....................................."
                  << std::endl;
        std::cout << "Received ID:" << int(recive_point->ID) << std::endl;
        std::cout << "Received Type:" << int(recive_point->Type) << std::endl;
        std::cout << "Received LeftTopX:" << int(recive_point->LeftTopX) << std::endl;
        std::cout << "Received LeftTopY:" << int(recive_point->LeftTopY) << std::endl;
        std::cout << "Received RightBottomX:" << int(recive_point->RightBottomX) << std::endl;
        std::cout << "Received RightBottomY:" << int(recive_point->RightBottomY) << std::endl;
        std::cout << "Received LocolX:" << recive_point->LocolX << std::endl;
        std::cout << "Received LocolY:" << recive_point->LocolY << std::endl;
        std::cout << "Received LocolZ:" << recive_point->LocolZ << std::endl;
        std::cout << "Received VelocityX:" << recive_point->VelocityX << std::endl;
        std::cout << "Received VelocityY:" << recive_point->VelocityY << std::endl;
        std::cout << "Received VelocityZ:" << recive_point->VelocityZ << std::endl;
        std::cout << "Received Longitude:" << recive_point->Longitude << std::endl;
        std::cout << "Received Latitude:" << recive_point->Latitude << std::endl;
        std::cout << "Received Altitude:" << recive_point->Altitude << std::endl;
        std::cout << "Received VelocityE:" << recive_point->VelocityE << std::endl;
        std::cout << "Received VelocityN:" << recive_point->VelocityN << std::endl;
        std::cout << "Received VelocityU:" << recive_point->VelocityU << std::endl;
        std::cout << "Received CameraID:" << int(recive_point->CameraID) << std::endl;

        // Construct string to send back
        // Creatr a payload which will be sent back to the client
        std::shared_ptr<vsomeip::payload> resp_pl = rtm_->create_payload();
        std::vector<vsomeip::byte_t> res_data;
        uint8_t Std_ReturnCodeType = 0x1;
        res_data.push_back(Std_ReturnCodeType);

        resp_pl->set_data(res_data);
        resp->set_payload(resp_pl);

        // Send the response back
        app_->send(resp);
        // we have finished
        // terminate();
    }


// ObjectList
    void on_message_cbk_objectlist(const std::shared_ptr<vsomeip::message> &_request)
    {
        // Create a response based upon the request
        std::shared_ptr<vsomeip::message> resp = rtm_->create_response(_request);

        // make the action of serialize
        const ObjectList *recive_point = reinterpret_cast<const ObjectList *>(_request->get_payload()->get_data());

        // use the extracted VehicleData
        std::cout << "...............................Received objectlist data....................................."
                  << std::endl;
        std::cout << "Received TimeStamp:" << int(recive_point->TimeStamp) << std::endl;
//        std::cout << "Received ObjList:" << recive_point->ObjList << std::endl;


        // Construct string to send back
        // Creatr a payload which will be sent back to the client
        std::shared_ptr<vsomeip::payload> resp_pl = rtm_->create_payload();
        std::vector<vsomeip::byte_t> res_data;
        uint8_t Std_ReturnCodeType = 0x1;
        res_data.push_back(Std_ReturnCodeType);

        resp_pl->set_data(res_data);
        resp->set_payload(resp_pl);

        // Send the response back
        app_->send(resp);
        // we have finished
        // terminate();
    }


private:
    std::shared_ptr<vsomeip::runtime> rtm_;
    std::shared_ptr<vsomeip::application> app_;
    bool stop_;
    std::mutex mutex_;
    std::condition_variable condition_;
    std::thread stop_thread_;
};
