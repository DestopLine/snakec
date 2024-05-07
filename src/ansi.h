#pragma once

#define ESC "\x1B"
#define ANSI_PREFIX "\x1B["
#define ANSI_ENABLE_ALT_BUF ANSI_PREFIX "?1049h"
#define ANSI_DISABLE_ALT_BUF ANSI_PREFIX "?1049l"
