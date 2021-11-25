#include "test_hal_monitor.hpp"
#include "hal_monitor.hpp"

void TestHalMonitor::SetUp() {
    hal_monitor_ = new HalMonitor();
}

void TestHalMonitor::TearDown() {
    delete hal_monitor_;
}

TEST_F(TestHalMonitor, testing_read) {
    SocketCan socket_can;
    bool ret = hal_monitor_->ReadFromCan(socket_can);
    reo_type::Database data;
    hal_monitor_->GetCanData(data);
    EXPECT_EQ(data.drive_mode, reo_type::DriveMode::kEco);
    EXPECT_EQ(data.gas, 0);
    EXPECT_EQ(data.gear, reo_type::Gear::kPark);
    EXPECT_EQ(data.ignition, reo_type::Ignition::kStop);
    EXPECT_EQ(ret, false);
}

TEST_F(TestHalMonitor, testing_get_can_data) {
    reo_type::Database data;
    hal_monitor_->GetCanData(data);
    EXPECT_EQ(data.drive_mode, reo_type::DriveMode::kEco);
    EXPECT_EQ(data.gas, 0);
    EXPECT_EQ(data.gear, reo_type::Gear::kPark);
    EXPECT_EQ(data.ignition, reo_type::Ignition::kStop);
}