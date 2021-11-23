#include <gtest/gtest.h>
#include "hal_monitor.hpp"

class TestHalMonitor : public ::testing::Test {
    protected:
        //TestHalMonitor() ;
        void SetUp() override;
        void TearDown() override;

        HalMonitor* hal_monitor_;    
          
};
