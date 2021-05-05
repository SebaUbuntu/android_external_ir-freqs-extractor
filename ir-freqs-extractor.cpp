/*
 * Copyright (C) 2021 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdio.h>

#include <hardware/hardware.h>
#include <hardware/consumerir.h>

int main() {
    consumerir_device_t *dev;
    const hw_module_t *hw_module = NULL;
    consumerir_freq_range_t *rangeAr;
    int32_t len;
    int i;

    int ret = hw_get_module(CONSUMERIR_HARDWARE_MODULE_ID, &hw_module);
    if (ret != 0) {
        printf("hw_get_module %s failed: %d", CONSUMERIR_HARDWARE_MODULE_ID, ret);
        goto exit;
    }

    ret = hw_module->methods->open(hw_module, CONSUMERIR_TRANSMITTER, (hw_device_t **) &dev);
    if (ret < 0) {
        printf("Can't open consumer IR transmitter, error: %d", ret);
        goto exit;
    }

    ret = dev->get_num_carrier_freqs(dev);
    if (ret < 0) {
        goto exit;
    }
    len = ret;
    rangeAr = new consumerir_freq_range_t[len];

    ret = dev->get_carrier_freqs(dev, len, rangeAr);
    if (ret < 0) {
        printf("Can't get carrier freqs, error: %d", ret);
        goto exit;
    }

    printf("static hidl_vec<ConsumerIrFreqRange> rangeVec {\n");
    for (i=0; i<len; i++) {
        printf("    {.min = %d, .max = %d},\n", rangeAr[i].min, rangeAr[i].max);
    }
    printf("};\n");

exit:
    return ret;
}
