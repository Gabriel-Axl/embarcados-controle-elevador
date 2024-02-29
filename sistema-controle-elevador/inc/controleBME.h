#ifndef CONTROLEBME_H
#define CONTROLEBME_H

#include "bme280.h"

/* Structure that contains identifier details used in example */
struct identifier
{
    /* Variable to hold device address */
    uint8_t dev_addr;

    /* Variable that contains file descriptor */
    int8_t fd;
};

extern struct bme280_dev dev;  // Declaração extern da estrutura dev

struct bme280_dev setup_bme280(int fd);

void user_delay_us(uint32_t period, void *intf_ptr);
int8_t user_i2c_read(uint8_t reg_addr, uint8_t *data, uint32_t len, void *intf_ptr);
int8_t user_i2c_write(uint8_t reg_addr, const uint8_t *data, uint32_t len, void *intf_ptr);
void print_sensor_data(struct bme280_data *comp_data);
int8_t stream_sensor_data_forced_mode(struct bme280_dev *dev);
struct bme280_data read_and_print_temperature(struct bme280_dev *dev);
#endif /* CONTROLEBME_H */