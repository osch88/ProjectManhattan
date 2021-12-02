#ifndef TURN_INDICATOR_HPP_
#define TURN_INDICATOR_HPP_

#include "database.hpp"
#include <cstdint>

class TurnIndicator {
    private:
        database_type::Indicator indicator_input_request_;
        database_type::Indicator indicator_status_; // blinking pattern on/off
        uint16_t timer_;

    public:
        TurnIndicator();
        void UpdateIndicator(const database_type::Database &data);
        database_type::Indicator GetIndicatorStatus() const;
};

#endif
