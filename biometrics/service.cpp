/*
 * Copyright (C) 2022 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define LOG_TAG "android.hardware.biometrics.fingerprint@2.1-service.xiaomi_holi"

#include <android/log.h>
#include <hidl/HidlSupport.h>
#include <hidl/HidlTransportSupport.h>
#include <android/hardware/biometrics/fingerprint/2.1/IBiometricsFingerprint.h>
#include <android/hardware/biometrics/fingerprint/2.1/types.h>
#include <vendor/xiaomi/hardware/fingerprintextension/1.0/IXiaomiFingerprint.h>
#include "BiometricsFingerprint.h"

using android::hardware::biometrics::fingerprint::V2_1::IBiometricsFingerprint;
using android::hardware::biometrics::fingerprint::V2_1::implementation::BiometricsFingerprint;
using android::hardware::configureRpcThreadpool;
using android::hardware::joinRpcThreadpool;
using android::sp;
using vendor::xiaomi::hardware::fingerprintextension::V1_0::IXiaomiFingerprint;

int main() {
    android::sp<IBiometricsFingerprint> bio = BiometricsFingerprint::getInstance();
    android::sp<IXiaomiFingerprint> xfe = BiometricsFingerprint::getXiaomiInstance();

    configureRpcThreadpool(1, true /*callerWillJoin*/);

    if (bio != nullptr) {
        if (::android::OK != bio->registerAsService()) {
            return 1;
        }
    } else {
        ALOGE("Can't create instance of BiometricsFingerprint, nullptr");
    }

    if (xfe != nullptr) {
        if (::android::OK != xfe->registerAsService()) {
            return 1;
        }
    } else {
        ALOGE("Can't create instance of XiaomiFingerprint, nullptr");
    }

    joinRpcThreadpool();

    return 0; // should never get here
}
