#!/usr/bin/env bash
set -euo pipefail

# Patch known build-breakers in the upstream MCUX SDK checkout.
# This repo aims to be "clone + run scripts" reproducible without manual edits.

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
WS_DIR="${1:-${WS_DIR:-$ROOT_DIR/mcuxsdk_ws}}"

KISS_FASTFIR_C="$WS_DIR/mcuxsdk/middleware/eiq/tensorflow-lite/third_party/kissfft/tools/kiss_fastfir.c"
EDGEAI_CMAKELISTS="$WS_DIR/mcuxsdk/examples/demo_apps/edgeai_smart_pong_demo/CMakeLists.txt"
EIQ_CMAKELISTS="$WS_DIR/mcuxsdk/middleware/eiq/CMakeLists.txt"
MCXN947_LD="$WS_DIR/mcuxsdk/devices/MCX/MCXN/MCXN947/gcc/MCXN947_cm33_core0_flash.ld"

echo "[patch] ws: $WS_DIR"

if [[ -f "$KISS_FASTFIR_C" ]]; then
  # GCC -Werror + -Wunused-variable can make this upstream "tools" source fail.
  # Make it deterministic and idempotent.
  if grep -q "__attribute__\\s*(([[:space:]]*unused[[:space:]]*))" "$KISS_FASTFIR_C"; then
    echo "[patch] ok: kiss_fastfir.c already patched"
  else
    if grep -qE '^static int verbose=0;[[:space:]]*$' "$KISS_FASTFIR_C"; then
      echo "[patch] fix: kiss_fastfir.c unused verbose"
      perl -0777 -pi -e 's|^static int verbose=0;\\s*$|/* Patched by EdgeAI_smart_pong_demo: MCUX SDK builds with -Werror; mark unused. */\\nstatic int verbose __attribute__((unused)) = 0;|m' "$KISS_FASTFIR_C"
    else
      echo "[patch] warn: kiss_fastfir.c verbose line not found; leaving unmodified"
    fi
  fi
else
  echo "[patch] skip: not found: $KISS_FASTFIR_C"
fi

if [[ -f "$EIQ_CMAKELISTS" ]]; then
  # Some manifest revisions do not provide the MPP project contents, but the
  # eIQ top-level CMakeLists includes it unconditionally. Mark it OPTIONAL so
  # builds do not hard-fail when MPP isn't present.
  if grep -q "middleware/eiq/mpp OPTIONAL" "$EIQ_CMAKELISTS"; then
    echo "[patch] ok: eiq mpp include already OPTIONAL"
  else
    echo "[patch] fix: make eiq mpp include OPTIONAL"
    # Upstream form:
    #   mcux_add_cmakelists(${SdkRootDirPath}/middleware/eiq/mpp)
    perl -0777 -pi -e 's|^mcux_add_cmakelists\\((\\$\\{SdkRootDirPath\\}/middleware/eiq/mpp)\\)\\s*$|mcux_add_cmakelists($1 OPTIONAL)|m' "$EIQ_CMAKELISTS" || true

    # Cleanup: previous buggy patch attempts could have introduced a conditional
    # block with an absolute path. Replace that with the OPTIONAL form.
    perl -0777 -pi -e 's|^if\\(EXISTS[^\\n]*middleware/eiq/mpp/CMakeLists\\.txt\\)\\s*\\nmcux_add_cmakelists\\([^\\n]*middleware/eiq/mpp\\)\\s*\\nendif\\(\\)\\s*$|mcux_add_cmakelists(\${SdkRootDirPath}/middleware/eiq/mpp OPTIONAL)|m' "$EIQ_CMAKELISTS" || true
  fi
fi

if [[ -f "$MCXN947_LD" ]]; then
  # NPU-converted model blobs are placed in section ".model".
  # Add a dedicated flash mapping so ".model" does not become an orphan section
  # in the default linker script.
  if grep -q "*(.model)" "$MCXN947_LD"; then
    echo "[patch] ok: MCXN947 linker script already maps .model section"
  else
    echo "[patch] fix: add .model section mapping to MCXN947 linker script"
    tmp_ld="$(mktemp)"
    awk '
      BEGIN { inserted = 0 }
      /^\}$/ {
        if (!inserted) {
          print ""
          print "  .model :"
          print "  {"
          print "    *(.model)"
          print "  } > m_flash1"
          inserted = 1
        }
      }
      { print }
    ' "$MCXN947_LD" > "$tmp_ld" && mv "$tmp_ld" "$MCXN947_LD"
  fi
fi

# Ensure the example wrapper pulls in repo sources (when the workspace was created
# before adding new files).
if [[ -f "$EDGEAI_CMAKELISTS" ]]; then
  echo "[patch] fix: normalize edgeai_smart_pong_demo CMakeLists sources"
  perl -0777 -pi -e 's|(mcux_add_source\\(\\s+BASE_PATH \\$\\{EDGEAI_ROOT\\}\\s+SOURCES)(.*?)(\\)\\s+mcux_add_include)|$1\\n            src\\/edgeai_smart_pong_demo\\.c\\n            src\\/accel_proc\\.c\\n            src\\/fxls8974cf\\.c\\n            src\\/par_lcd_s035\\.c\\n            src\\/text5x7\\.c\\n            src\\/sw_render\\.c\\n            src\\/platform\\/display_hal\\.c\\n            src\\/platform\\/input_hal\\.c\\n            src\\/platform\\/time_hal\\.c\\n            src\\/platform\\/touch_hal_stub\\.c\\n            src\\/platform\\/npu_hal_stub\\.c\\n            src\\/platform\\/npu_hal_tflm_neutron\\.cpp\\n            src\\/game\\/ai\\.c\\n            src\\/game\\/game\\.c\\n            src\\/game\\/input\\.c\\n            src\\/game\\/modes\\.c\\n            src\\/game\\/physics\\.c\\n            src\\/game\\/render\\.c\\n)\\n\\nmcux_add_include|ms' "$EDGEAI_CMAKELISTS" || true

  if grep -q "components/touch/gt911/fsl_gt911.c" "$EDGEAI_CMAKELISTS"; then
    echo "[patch] ok: gt911 component already present"
  else
    echo "[patch] fix: add gt911 component to edgeai_smart_pong_demo CMakeLists"
    perl -0777 -pi -e 's|(mcux_add_include\\(\\s+BASE_PATH \\$\\{EDGEAI_ROOT\\}\\s+INCLUDES src\\s+\\)\\s*)|$1\\n\\n# Touch controller (GT911) for LCD-PAR-S035 touch panel.\\nmcux_add_source(\\n    BASE_PATH \\$\\{SdkRootDirPath\\}\\n    SOURCES components\\/touch\\/gt911\\/fsl_gt911.c\\n)\\n\\nmcux_add_include(\\n    BASE_PATH \\$\\{SdkRootDirPath\\}\\n    INCLUDES components\\/touch\\/gt911\\n)\\n\\n|ms' "$EDGEAI_CMAKELISTS" || true
  fi

  if grep -q '__stack_size__=0x8000' "$EDGEAI_CMAKELISTS"; then
    echo "[patch] ok: edgeai_smart_pong_demo stack size already 0x8000"
  else
    echo "[patch] fix: force edgeai_smart_pong_demo stack size to 0x8000"
    perl -0777 -pi -e 's|if\\(DEFINED EDGEAI_ENABLE_NPU_INFERENCE AND EDGEAI_ENABLE_NPU_INFERENCE\\)\\s*mcux_add_linker_symbol\\(SYMBOLS \"__stack_size__=0x[0-9a-fA-F]+\"\\)\\s*endif\\(\\)|mcux_add_linker_symbol(SYMBOLS \"__stack_size__=0x8000\")|ms' "$EDGEAI_CMAKELISTS" || true

    if ! grep -q '__stack_size__=0x8000' "$EDGEAI_CMAKELISTS"; then
      perl -0777 -pi -e 's|(include\\(\\$\\{SdkRootDirPath\\}/\\$\\{board_root\\}/\\$\\{board\\}/demo_apps/edgeai_smart_pong_demo/reconfig\\.cmake OPTIONAL\\))|mcux_add_linker_symbol(SYMBOLS \"__stack_size__=0x8000\")\\n\\n$1|ms' "$EDGEAI_CMAKELISTS" || true
    fi
  fi
fi
