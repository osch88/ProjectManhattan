#include "test_hal_monitor.hpp"
#include "hal_monitor.hpp"

void TestHalMonitor::SetUp() {
    hal_monitor_ = new HalMonitor();
}

void TestHalMonitor::TearDown() {
    delete hal_monitor_;
}

TEST_F(TestHalMonitor, testing_read) {
    //TestHalMonitor *test_hal_monitor;
    SocketCan socket_can;
    bool ret = hal_monitor_->ReadFromCan(socket_can);
    
    
    EXPECT_EQ(ret, false);
}