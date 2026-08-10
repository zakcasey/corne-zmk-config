#pragma once

// U_MT is gone. custom_config.h overrides every layer, so no stock alternative
// layer expands, and the base layer uses u_hml and u_hmr from config/corne.keymap.
// If you ever remove a layer override, define U_MT again with a mod-tap behavior.
#define U_LT(LAYER, TAP) &u_lt LAYER TAP
