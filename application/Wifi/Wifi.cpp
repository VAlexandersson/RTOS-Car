
#include "Wifi.h"

namespace WIFI {

char Wifi::mac_address_ctr[]{};

const esp_err_t Wifi::_get_mac(void) {

    uint8_t mac_byte_buffer[6]{};

    const esp_err_t status{esp_efuse_mac_get_default(mac_byte_buffer)};

    snprintf(mac_address_ctr, sizeof(mac_address_ctr), 
            "%02X%02X%02X%02X%02X%02X",
            mac_byte_buffer[0], mac_byte_buffer[1], 
            mac_byte_buffer[2], mac_byte_buffer[3], 
            mac_byte_buffer[4], mac_byte_buffer[5]);

    return status;
}

} // namespace WIFI