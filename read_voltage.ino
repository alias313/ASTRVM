#include <driver/adc.h>

//link to thread: https://stackoverflow.com/questions/56833346/how-to-measure-battery-voltage-with-internal-adc-esp32

float battery_read()
{
    //read battery voltage per %
    long sum = 0;                  // sum of samples taken
    float voltage = 0.0;           // calculated voltage
    float output = 0.0;            //output value
    const float battery_max = 3.6; //maximum voltage of battery
    const float battery_min = 3.3; //minimum voltage of battery before shutdown

    float R1 = 100000.0; // resistance of R1 (100K)
    float R2 = 10000.0;  // resistance of R2 (10K)

    for (int i = 0; i < 500; i++)
    {
        sum += adc1_get_voltage(ADC1_CHANNEL_0);
        delayMicroseconds(1000);
    }
    // calculate the voltage
    voltage = sum / (float)500;
    voltage = (voltage * 1.1) / 4096.0; //for internal 1.1v reference
    // use if added divider circuit
    // voltage = voltage / (R2/(R1+R2));
    //round value by two precision
    voltage = roundf(voltage * 100) / 100;
    Serial.print("voltage: ");
    Serial.println(voltage, 2);
    output = ((voltage - battery_min) / (battery_max - battery_min)) * 100;
    if (output < 100)
        return output;
    else
        return 100.0f;
}

void setup()
{
    adc1_config_width(ADC_WIDTH_12Bit);
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_0db); //set reference voltage to internal
    Serial.begin(9600);
}

void loop()
{
    Serial.print("Battery Level: ");
    Serial.println(battery_read(), 2);
    delay(1000);
}
