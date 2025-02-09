#include "iv3.h"
#include "Wire.h"

void IV3_clock::i2c_trans(uint8_t* data, uint8_t length)
{
    Wire.begin();
    Wire.beginTransmission(I2C_address);

    for(int i=0; i<length; i++)
        Wire.write(data[i]);

    Wire.endTransmission();
}

void IV3_clock::set_time(void)
{
    uint8_t TX[7] = {SET_TIME, this->time.year, this->time.month, this->time.day, this->time.hour, this->time.minute, this->time.second};

    i2c_trans(TX, 7);
}

void IV3_clock::get_time(void)
{
    uint8_t RX[6];
    uint8_t TX[1] = {READ_TIME};
    uint8_t i = 0;

    i2c_trans(TX, 1);
    delay(1);

    Wire.requestFrom(I2C_address, 6);
    while(Wire.available())
    {
        RX[i] = Wire.read();
        i++;
    }

    this->time.year = RX[0];
    this->time.month = RX[1];
    this->time.day = RX[2];
    this->time.hour = RX[3];
    this->time.minute = RX[4];
    this->time.second = RX[5];
}

void IV3_clock::print_time(void)
{
    Serial.print(this->time.day);
    Serial.print(":");
    Serial.print(this->time.month);
    Serial.print(":");
    Serial.print(20);
    Serial.print(this->time.year);
    Serial.print(" ");
    Serial.print(this->time.hour);
    Serial.print(":");
    Serial.print(this->time.minute);
    Serial.print(":");
    Serial.print(this->time.second);
    Serial.println("");
}

void IV3_clock::clock_mode(void)
{
    uint8_t TX[1] = {CLOCK_MODE};
    i2c_trans(TX, 1);
}

void IV3_clock::user_display(uint8_t *data)
{
    uint8_t TX[5];
    uint8_t i;

    TX[0] = USER_DISPLAY;
    for(i=0; i<4; i++)
        TX[i+1] = data[i];

    i2c_trans(TX, 5);
}

void IV3_clock::set_hour_mode(bool mode)
{
    uint8_t TX[2];

    TX[0] = HOUR_MODE;
    if(mode == true)
        TX[1] = 1;
    else
        TX[1] = 0;

    i2c_trans(TX, 2);
}

void IV3_clock::set_brightness(uint8_t brightness)
{
    uint8_t TX[2];

    if(brightness > MAX_TUBE_BRIGHTNESS)
        brightness = MAX_TUBE_BRIGHTNESS;

    TX[0] = SET_BRIGHTNESS;
    TX[1] = brightness;

    i2c_trans(TX, 2);
}

void IV3_clock::set_night_fade(bool mode)
{
    uint8_t TX[2];

    TX[0] = NIGHT_FADE;
    if(mode == true)
        TX[1] = 1;
    else
        TX[1] = 0;

    i2c_trans(TX, 2);
}

void IV3_clock::reset(void)
{
    uint8_t TX[1] = {SFT_RST};

    i2c_trans(TX, 1);
}

void IV3_clock::get_status(void)
{
    uint8_t TX[1] = {GET_STATUS};

    i2c_trans(TX, 2);
    delay(10);

    Wire.requestFrom(I2C_address, 1);
    while(Wire.available())
    {
        IV3_status = Wire.read();
    }
}

bool IV3_clock::get_hour_mode(void)
{
    this->get_status();
    if((IV3_status & 0x80) == 0x80)
        return true;
    else
        return false;
}

bool IV3_clock::get_fade_mode(void)
{
    this->get_status();
    if((IV3_status & 0x40) == 0x40)
        return true;
    else
        return false;
}

uint8_t IV3_clock::get_brightness(void)
{
    this->get_status();
    IV3_status &= 0x1F;
    return IV3_status;
}