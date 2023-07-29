#include <iomanip>
#include <iostream>
#include <sstream>
#include <vsomeip/vsomeip.hpp>

#define SAMPLE_EVENTGROUP_ID 0x3333
#define SAMPLE_SERVICE_ID 0x1234
#define SAMPLE_INSTANCE_ID 0x5678
#define SAMPLE_EVENT_ID 0x4444

std::shared_ptr<vsomeip::application> app_;

int main() 
{
app_ = vsomeip::runtime::get()->create_application("World");
app_->init();
app_->offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);

const vsomeip::byte_t its_data[] = { 0x22 };
std::shared_ptr<vsomeip::payload> payload = vsomeip::runtime::get()->create_payload();
payload->set_data(its_data, sizeof(its_data));
std::set<vsomeip::eventgroup_t> its_groups;


its_groups.insert(SAMPLE_EVENTGROUP_ID);
app_->offer_event(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENT_ID, its_groups);
app_->notify(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_EVENT_ID, payload);
app_->start();
}