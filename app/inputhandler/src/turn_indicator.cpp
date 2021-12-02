#include "turn_indicator.hpp"

    TurnIndicator::TurnIndicator() {
        indicator_input_request_ = database_type::Indicator::kOff;
        indicator_status_ = database_type::Indicator::kOff;
        timer_ = 0;
    }

    void TurnIndicator::UpdateIndicator(const database_type::Database &data) {
        if (indicator_input_request_ != data.indicator_request) {
            timer_ = 0;
            indicator_input_request_ = data.indicator_request;
            indicator_status_ = indicator_input_request_;
        } else {
            timer_ ++;
        }

        if (timer_ == 1000) {
            timer_ = 0;
            if (indicator_status_ != database_type::Indicator::kOff) {
                indicator_status_ = database_type::Indicator::kOff;
            } else {
                indicator_status_ = indicator_input_request_;
            }
        }
    }

    database_type::Indicator TurnIndicator::GetIndicatorStatus() const {
        return indicator_input_request_; // indicator_status_; // As cluster is generating pulse by itself we are returning input request instead of status
    }