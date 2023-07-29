#include <vsomeip/vsomeip.hpp>
#include <iostream>
#include <chrono>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <cstdio>

#define SAMPLE_EVENT_ID 0x8001
#define SAMPLE_EVENTGROUP_ID 0x0001

std::shared_ptr<vsomeip::application> rtm_(vsomeip::runtime::get());
app_(rtm_->create_application());

const vsomeip::byte_t its_data[] = { 0x01 };
std::shared_ptr<vsomeip::payload> payload;
payload = vsomeip::runtime::get()->create_payload();

payload->set_data(its_data, sizeof(its_data));

std::set<vsomeip::eventgroup_t> its_groups;
its_groups.insert(SAMPLE_EVENTGROUP_ID);
app_->offer_service(service_id, instance_id, its_groups 
