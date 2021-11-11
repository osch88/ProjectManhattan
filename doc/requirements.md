REQUIREMENTS:

- Receive keyboard inputs for start/stop, gas pedal, gear stick, drive mode and emulate the engine and gearbox behaviour, outputting rpm, gear indicator and fault status on CAN.

- keyboard inputs shall be transmitted to engine/gearbox emulator via a virtual CAN network.
- keyboard inputs are: 
    S        for start
    Q        for stop
    P        for gear position Park
    N        for gear position Neutral
    D        for gear position Drive
    R        for gear position Reverse
    UP       for gas pedal increase (acceleration)
    DOWN     for gas pedal decrease (deccelration)
    1        for drive mode normal (default if non selected)
    2        for drive mode sport


- When start key is pressed and gear lever is in Park the engine shall start in idle mode and present the resulting rpm on CAN.
- When stop key is pressed and gear lever is in Park or Neutral the engine shall turn off.
- When acceleration key is pressed and engine is on ẗhe engine shall ramp up rpm correspondingly. One press equals 10% throttle increase. 
    - If gear lever is in Drive the gear box shall change gear corresponding to the rpm and thresholds for gear shifting (TBD)
        - If in drive mode normal shift up at 2000 rpm, shift down at 1000 rpm
        - If in drive mode sport shift up at 3000 rpm, shift down at x rpm
    - If gear lever is in Reverse the gear is constant
- When decelleration key is pressed and engine is on the engine shall ramp down rpm. One press equals 10% throttle decrease. 

- if no CAN message is received by emulator a fault message shall be sent to CAN output.

SPECIFICATION (V60 T4 2020):
- Gear ratios: 
    First Gear 	    5,250 : 1
    Second Gear     3,029 : 1
    Third Gear 	    1,950 : 1
    Fourth Gear     1,457 : 1
    Fifth Gear 	    1,221 : 1
    Sixth Gear 	    1,000 : 1
    Seventh Gear    0,809 : 1
    Eighth Gear 	0,673 : 1
    Reverse Gear 	4,015 : 1
- Max torque 300 / 28 - 67 Nm / rps
- Max output 140 kW (190 hp) / 5000 rpm
- Max engine speed 6000 rpm 
- Engine idle speed 875 rpm ± 50
