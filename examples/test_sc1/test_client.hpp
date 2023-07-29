// Copyright (C) 2015-2017 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
#include <vsomeip/vsomeip.hpp>
#include <iostream>
#include <unistd.h>
#include "Message.hpp"

#if defined ANDROID || defined __ANDROID__
#include "android/log.h"
#define LOG_TAG "test_client"
#define LOG_INF(...) fprintf(stdout, __VA_ARGS__), fprintf(stdout, "\n"), (void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, ##__VA_ARGS__)
#define LOG_ERR(...) fprintf(stderr, __VA_ARGS__), fprintf(stderr, "\n"), (void)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, ##__VA_ARGS__)
#else
#include <cstdio>
#define LOG_INF(...) fprintf(stdout, __VA_ARGS__), fprintf(stdout, "\n")
#define LOG_ERR(...) fprintf(stderr, __VA_ARGS__), fprintf(stderr, "\n")
#endif

static vsomeip::service_t service_id = 0xA701;
static vsomeip::instance_t service_instance_id = 0x2221;
static vsomeip::method_t service_method_id = 0x3333;

class test_client {
public:
    // Get the vSomeIP runtime and
    // create a application via the runtime, we could pass the application name
    // here otherwise the name supplied via the VSOMEIP_APPLICATION_NAME
    // environment variable is used
    test_client() :
                    rtm_(vsomeip::runtime::get()),
                    app_(rtm_->create_application())
    {
    }

    bool init(){
        // init the application
        if (!app_->init()) {
            LOG_ERR ("Couldn't initialize application");
            return false;
        }

        // register a state handler to get called back after registration at the
        // runtime was successful
        app_->register_state_handler(
                std::bind(&test_client::on_state_cbk, this,
                        std::placeholders::_1));

        // register a callback for responses from the service
        app_->register_message_handler(vsomeip::ANY_SERVICE,
                service_instance_id, vsomeip::ANY_METHOD,
                std::bind(&test_client::on_message_cbk, this,
                        std::placeholders::_1));

        // register a callback which is called as soon as the service is available
        app_->register_availability_handler(service_id, service_instance_id,
                std::bind(&test_client::on_availability_cbk, this,
                        std::placeholders::_1, std::placeholders::_2,
                        std::placeholders::_3));
        return true;
    }

    void start()
    {
        // start the application and wait for the on_event callback to be called
        // this method only returns when app_->stop() is called
        app_->start();
    }

    void on_state_cbk(vsomeip::state_type_e _state)
    {
        if(_state == vsomeip::state_type_e::ST_REGISTERED)
        {
            // we are registered at the runtime now we can request the service
            // and wait for the on_availability callback to be called
            app_->request_service(service_id, service_instance_id);
        }
    }

    void on_availability_cbk(vsomeip::service_t _service,
            vsomeip::instance_t _instance, bool _is_available)
    {
        // Check if the available service is the the hello world service
        if(service_id == _service && service_instance_id == _instance
                && _is_available)
        {
            // The service is available then we send the request
            // Create a new request
            std::shared_ptr<vsomeip::message> rq = rtm_->create_request();
            // Set the hello world service as target of the request
            rq->set_service(service_id);
            rq->set_instance(service_instance_id);
            rq->set_method(service_method_id);

            // Create a payload which will be sent to the service
            std::shared_ptr<vsomeip::payload> pl = rtm_->create_payload();

            PathPointType nav_point;
            nav_point.Heading = 31.2;
            nav_point.Latitude =100;
            nav_point.Longitude = 40;
            nav_point.Property = 233;

            std::vector<vsomeip::byte_t> res_data(reinterpret_cast<const uint8_t *>(&nav_point),
                                                   reinterpret_cast<const uint8_t *>(&nav_point) + sizeof(PathPointType));

//            std::string str("World");
//            std::vector<vsomeip::byte_t> pl_data(std::begin(str), std::end(str));

            pl->set_data(res_data);
            rq->set_payload(pl);
            // Send the request to the service. Response will be delivered to the
            // registered message handler
            LOG_INF("Sending: PathPointType");
            app_->send(rq);
        }
    }

    void on_message_cbk(const std::shared_ptr<vsomeip::message> &_response)
    {
        if(service_id == _response->get_service()
                && service_instance_id == _response->get_instance()
                && vsomeip::message_type_e::MT_RESPONSE
                        == _response->get_message_type()
                && vsomeip::return_code_e::E_OK == _response->get_return_code())
        {
            // Get the payload and print it
            std::shared_ptr<vsomeip::payload> pl = _response->get_payload();
            //if ( pl->get_length()== sizeof(PathPointType)) {
                int statue = (int)*(pl->get_data());

                // Now you can use the extracted VehicleData
                std::cout << "...............................Received data....................................."
                          << std::endl;
                std::cout << "statue: " << statue << std::endl;

           // }
            stop();
        }
    }

    void stop()
    {
        // unregister the state handler
        app_->unregister_state_handler();
        // unregister the message handler
        app_->unregister_message_handler(vsomeip::ANY_SERVICE,
                service_instance_id, vsomeip::ANY_METHOD);
        // alternatively unregister all registered handlers at once
        app_->clear_all_handler();
        // release the service
        app_->release_service(service_id, service_instance_id);
        // shutdown the application
        app_->stop();
    }

private:
    std::shared_ptr<vsomeip::runtime> rtm_;
    std::shared_ptr<vsomeip::application> app_;
};
