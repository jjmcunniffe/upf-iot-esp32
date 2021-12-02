#include <stdio.h>
#include <stdlib.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/temp_sensor.h"

static const char *TAG = "TempSensor";

void tempsensor(void *arg)
{
    // Initialize the temperature sensor.
    ESP_LOGI(TAG, "Initializing Temperature sensor");
    float tsens_out;
    temp_sensor_config_t temp_sensor = TSENS_CONFIG_DEFAULT();
    temp_sensor_get_config(&temp_sensor);
    ESP_LOGI(TAG, "default dac %d, clk_div %d", temp_sensor.dac_offset, temp_sensor.clk_div);
    temp_sensor.dac_offset = TSENS_DAC_DEFAULT; // DEFAULT: range:-10℃ ~  80℃, error < 1℃.
    temp_sensor_set_config(temp_sensor);
    temp_sensor_start();
    ESP_LOGI(TAG, "Temperature sensor started");

    // Check the temperature continuosly.
    while (1) {
        vTaskDelay(1000 / portTICK_RATE_MS);
        temp_sensor_read_celsius(&tsens_out);

        // Log the temperature to serial output.
        ESP_LOGI(TAG, "Temperature is %f°C", tsens_out);

        // Change the colour of the LED based on the temp.
        if (tsens_out < 26) {
            ESP_LOGI(TAG, "This is below 30°C");
        } else {
            ESP_LOGI(TAG, "This is above 30°C");
        }
    }
    vTaskDelete(NULL);
}

void app_main(void)
{
    xTaskCreate(tempsensor, "temp", 2048, NULL, 5, NULL);
}