#include <stdio.h>
#include <stdlib.h>
#include "esp_log.h"
#include "led_strip.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/temp_sensor.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

static const char *TAG = "TempSensor";

#define BLINK_GPIO CONFIG_BLINK_GPIO

static led_strip_t *pStrip_a;

void initLED() {
    pStrip_a = led_strip_init(CONFIG_BLINK_LED_RMT_CHANNEL, BLINK_GPIO, 1);
    // Clear the LED from previous activations.
    pStrip_a->clear(pStrip_a, 50);
}

void initTempSensor(void) {
    ESP_LOGI(TAG, "Initializing Temperature sensor");
    temp_sensor_config_t temp_sensor = TSENS_CONFIG_DEFAULT();
    temp_sensor_get_config(&temp_sensor);
    ESP_LOGI(TAG, "default dac %d, clk_div %d", temp_sensor.dac_offset, temp_sensor.clk_div);
    temp_sensor.dac_offset = TSENS_DAC_DEFAULT; // DEFAULT: range:-10℃ ~  80℃, error < 1℃.
    temp_sensor_set_config(temp_sensor);

    temp_sensor_start();
    ESP_LOGI(TAG, "Temperature sensor started");
}

void tempsensor(void *arg)
{
    // Clear the LED from previous activations.
    pStrip_a = led_strip_init(CONFIG_BLINK_LED_RMT_CHANNEL, BLINK_GPIO, 1);
    pStrip_a->clear(pStrip_a, 50);

    // Check the temperature continuously.
    float tsens_out;
    initTempSensor();

    while (1) {
        vTaskDelay(1000 / portTICK_RATE_MS);
        temp_sensor_read_celsius(&tsens_out);

        // Log the temperature to serial output.
        ESP_LOGI(TAG, "Temperature is %f°C", tsens_out);

        // Change the colour of the LED based on the temp.
        if (tsens_out < 30) {
            // Set the colour to green.
            pStrip_a->set_pixel(pStrip_a, 0, 0, 100, 0);
            pStrip_a->refresh(pStrip_a, 100);

            ESP_LOGI(TAG, "This is below 30°C");
        } else {
            // Set the colour to red.
            pStrip_a->set_pixel(pStrip_a, 0, 100, 0, 0);
            pStrip_a->refresh(pStrip_a, 100);

            ESP_LOGI(TAG, "This is above 30°C");
        }
    }
    vTaskDelete(NULL);
}

void app_main(void)
{
    xTaskCreate(tempsensor, "temp", 2048, NULL, 5, NULL);
}