deps_config := \
	/home/raul/esp32/esp-idf/components/app_trace/Kconfig \
	/home/raul/esp32/esp-idf/components/aws_iot/Kconfig \
	/home/raul/esp32/esp-idf/components/bt/Kconfig \
	/home/raul/esp32/esp-idf/components/driver/Kconfig \
	/home/raul/esp32/esp-idf/components/esp32/Kconfig \
	/home/raul/esp32/esp-idf/components/esp_adc_cal/Kconfig \
	/home/raul/esp32/esp-idf/components/esp_http_client/Kconfig \
	/home/raul/esp32/esp-idf/components/ethernet/Kconfig \
	/home/raul/esp32/esp-idf/components/fatfs/Kconfig \
	/home/raul/esp32/esp-idf/components/freertos/Kconfig \
	/home/raul/esp32/esp-idf/components/heap/Kconfig \
	/home/raul/esp32/esp-idf/components/libsodium/Kconfig \
	/home/raul/esp32/esp-idf/components/log/Kconfig \
	/home/raul/esp32/esp-idf/components/lwip/Kconfig \
	/home/raul/esp32/esp-idf/components/mbedtls/Kconfig \
	/home/raul/esp32/esp-idf/components/nvs_flash/Kconfig \
	/home/raul/esp32/esp-idf/components/openssl/Kconfig \
	/home/raul/esp32/esp-idf/components/pthread/Kconfig \
	/home/raul/esp32/esp-idf/components/spi_flash/Kconfig \
	/home/raul/esp32/esp-idf/components/spiffs/Kconfig \
	/home/raul/esp32/esp-idf/components/tcpip_adapter/Kconfig \
	/home/raul/esp32/esp-idf/components/vfs/Kconfig \
	/home/raul/esp32/esp-idf/components/wear_levelling/Kconfig \
	/home/raul/esp32/esp-idf/components/bootloader/Kconfig.projbuild \
	/home/raul/esp32/esp-idf/components/esptool_py/Kconfig.projbuild \
	/home/raul/esp32/esp-idf/components/partition_table/Kconfig.projbuild \
	/home/raul/esp32/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)

ifneq "$(IDF_CMAKE)" "n"
include/config/auto.conf: FORCE
endif

$(deps_config): ;
