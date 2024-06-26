// Copyright 2022 Jay Greco (@jaygreco)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C1 FALSE

#undef RP_SIO_USE_UART0
#define RP_SIO_USE_UART0 FALSE

#undef RP_PWM_USE_PWM0
#define RP_PWM_USE_PWM0 TRUE
#undef RP_PWM_USE_PWM1
#define RP_PWM_USE_PWM1 TRUE
#undef RP_PWM_USE_PWM2
#define RP_PWM_USE_PWM2 TRUE
#undef RP_PWM_USE_PWM3
#define RP_PWM_USE_PWM3 TRUE
