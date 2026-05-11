/*
 * SecureNode — Multi-board Zephyr template
 * Supports: STM32F407 Discovery, ESP32 DevKitC
 */
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
#include "securenode.h"

LOG_MODULE_REGISTER(main, CONFIG_SECURENODE_LOG_LEVEL);

#define LED0_NODE DT_ALIAS(led0)
static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED0_NODE, gpios);

int main(void)
{
    int ret;

    LOG_INF("SecureNode starting on %s", CONFIG_BOARD);
    LOG_INF("Zephyr version: %s", KERNEL_VERSION_STRING);

    if (!gpio_is_ready_dt(&led)) {
        LOG_ERR("LED device not ready");
        return -ENODEV;
    }

    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        LOG_ERR("Failed to configure LED: %d", ret);
        return ret;
    }

    LOG_INF("SecureNode ready. Blinking LED...");

    while (1) {
        gpio_pin_toggle_dt(&led);
        LOG_DBG("LED toggled");
        k_sleep(K_MSEC(CONFIG_SECURENODE_BLINK_MS));
    }

    return 0;
}
