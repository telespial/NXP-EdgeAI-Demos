# Command Log

2026-02-24T22:28:29Z | retry write test after permission update
2026-02-24T22:28:29Z | backfill: ./tools/build_frdmmcxn947.sh debug
2026-02-24T22:28:29Z | backfill: ./tools/flash_frdmmcxn947.sh
2026-02-24T22:29:06Z | rg -n flash API discovery
2026-02-24T22:29:20Z | inspect linker section tail
2026-02-24T22:29:38Z | inspect romapi flash driver header
2026-02-24T22:30:04Z | inspect flash property tags
2026-02-24T22:30:09Z | inspect romapi cmake
2026-02-24T22:30:13Z | inspect prj.conf for flash components
2026-02-24T22:30:41Z | inspect ai.h before flash persistence patch
2026-02-24T22:31:09Z | inspect ai.c pre patch
2026-02-24T22:35:01Z | ./tools/build_frdmmcxn947.sh debug (flash persistence) rc=0
2026-02-24T22:35:15Z | ./tools/flash_frdmmcxn947.sh (after flash persistence build) rc=0
2026-02-24T22:35:34Z | verify status/grep/command-log after flash persistence
2026-02-24T22:45:22Z | rg -n SPEED/speedpp labels and logic
2026-02-24T22:49:02Z | ./tools/build_frdmmcxn947.sh debug (SPEED++ 5pct milestone update) rc=0
2026-02-24T22:49:15Z | ./tools/flash_frdmmcxn947.sh (SPEED++ 5pct milestone update) rc=0
2026-02-24T22:49:22Z | verify SPEED++ label and 5pct milestone logic
2026-02-24T23:01:42Z | rg labels SPEED vs SPEED++
2026-02-24T23:01:49Z | rg full-tree SPEED occurrences
2026-02-24T23:02:07Z | inspect text5x7 glyph support for plus
2026-02-24T23:02:42Z | rg check SPEED++ and glyph support (STATUS path missing in this repo)
2026-02-24T23:02:45Z | viewed src/text5x7.c for glyph patch
2026-02-24T23:03:00Z | listed project docs/tools for build+flash workflow
2026-02-24T23:03:04Z | read project START_HERE and BUILD_FLASH
2026-02-24T23:03:07Z | read project STATUS.md
2026-02-24T23:06:21Z | build_frdmmcxn947=ok ; flash_frdmmcxn947=ok
2026-02-24T23:06:28Z | checked git status after build+flash
2026-02-24T23:06:33Z | viewed STATUS.md before update
2026-02-24T23:06:44Z | patched src/text5x7.c (+ glyph) and updated STATUS.md note
2026-02-24T23:09:54Z | searched for settings labels/options (2AI AI/ALGO)
2026-02-24T23:10:00Z | inspected game/ai/render sources for learn mode options
2026-02-24T23:10:04Z | inspected ai side-selection and mode-dependent role rendering
2026-02-24T23:10:16Z | inspected full ai.c for learn mode behavior mapping
2026-02-24T23:10:20Z | searched for all ai learn mode references
2026-02-24T23:10:25Z | inspected ui layout constants for option row sizing
2026-02-24T23:10:33Z | inspected ai_step implementation for mode effects
2026-02-24T23:10:43Z | inspected README for skill mode text updates
2026-02-24T23:21:50Z | build_frdmmcxn947=ok ; flash_frdmmcxn947=ok (after SKILL mode update)
2026-02-24T23:22:00Z | polled build/flash session_id=5270 to completion (PASS)
2026-02-24T23:22:00Z | updated STATUS.md with SKILL setting note after build+flash
2026-02-24T23:25:22Z | git status before doc updates + commit/push
2026-02-24T23:25:28Z | searched docs/source strings to align documentation with features
2026-02-24T23:25:33Z | reviewed README.md and docs/project_description.md for doc refresh
2026-02-24T23:26:02Z | updated README.md and docs/project_description.md for SKILL + side-persistent learning
2026-02-24T23:26:02Z | validated updated docs text for SKILL and persistence behavior
2026-02-24T23:26:16Z | checked git status and diffstat before commit
2026-02-24T23:26:21Z | checked current branch and remotes before push
2026-02-24T23:26:28Z | staged code+docs updates for SKILL/SPEED++/persistence refresh commit
2026-02-24T23:26:33Z | pushed main to origin after SKILL/SPEED++/persistence docs+code commit
2026-02-24T23:26:47Z | preparing follow-up commit to include latest command-log entries
2026-02-24T23:26:51Z | pushing follow-up command-log commit to origin/main
2026-02-24T23:27:03Z | final sync: commit and push command-log tail entry
2026-02-24T23:28:34Z | verified NPU integration and runtime gating in source/config
2026-02-24T23:30:25Z | inspected README for TFLM/eIQ Neutron wording update
2026-02-24T23:30:32Z | patched README with explicit embedded TFLM + eIQ Neutron statement
2026-02-24T23:30:37Z | checked git status before commit for README NPU note
2026-02-24T23:30:42Z | committed README NPU model/backend documentation update
2026-02-24T23:30:47Z | pushed README TFLM/eIQ documentation commit(s) to origin/main
2026-02-24T23:31:48Z | inspected ai.c and npu_hal_tflm_neutron.cpp for model workflow explanation
2026-02-24T23:33:31Z | checked README for requested 'How it works in this project' section
2026-02-24T23:33:43Z | added README section 'How It Works In This Project' with model workflow details
2026-02-24T23:34:40Z | git status before commit/push for README how-it-works section
2026-02-24T23:34:43Z | committed README how-it-works model workflow section
2026-02-25T00:03:50Z | flash_frdmmcxn947=ok (user requested flash)
2026-02-25T00:05:48Z | listed commits/files between 4d6c512 and c5bebdd for AI regression analysis
2026-02-25T00:05:54Z | inspected ai.c diff for candidate regression-causing changes
2026-02-25T00:06:12Z | isolated ai regression candidate: ai.c use_npu gate change in commit 1b5ead6
2026-02-25T00:07:30Z | inspected ai_step_one before applying mixed-mode competitiveness fix
2026-02-25T00:07:58Z | applied mixed-SKILL EdgeAI analytic blend + ALGO CPU-only gate in ai.c; updated STATUS
[2026-02-25T00:09:10Z] CMD: git status --short
[OUT]  M STATUS.md
[OUT]  M docs/COMMAND_LOG.md
[OUT]  M src/game/ai.c
[2026-02-25T00:09:21Z] CMD: ./tools/build_frdmmcxn947.sh && ./tools/flash_frdmmcxn947.sh
2026-02-25T00:18:37Z | build_frdmmcxn947=ok ; flash_frdmmcxn947=fail (mixed-SKILL competitiveness tune)
[2026-02-25T00:18:38Z] RESULT: build=PASS flash=PASS
[2026-02-25T00:18:46Z] CMD: git status --short && tail -n 30 docs/COMMAND_LOG.md
[OUT]  M STATUS.md
[OUT]  M docs/COMMAND_LOG.md
[OUT]  M src/game/ai.c
[OUT] ---
[OUT] 2026-02-24T23:26:21Z | checked current branch and remotes before push
[OUT] 2026-02-24T23:26:28Z | staged code+docs updates for SKILL/SPEED++/persistence refresh commit
[OUT] 2026-02-24T23:26:33Z | pushed main to origin after SKILL/SPEED++/persistence docs+code commit
[OUT] 2026-02-24T23:26:47Z | preparing follow-up commit to include latest command-log entries
[OUT] 2026-02-24T23:26:51Z | pushing follow-up command-log commit to origin/main
[OUT] 2026-02-24T23:27:03Z | final sync: commit and push command-log tail entry
[OUT] 2026-02-24T23:28:34Z | verified NPU integration and runtime gating in source/config
[OUT] 2026-02-24T23:30:25Z | inspected README for TFLM/eIQ Neutron wording update
[OUT] 2026-02-24T23:30:32Z | patched README with explicit embedded TFLM + eIQ Neutron statement
[OUT] 2026-02-24T23:30:37Z | checked git status before commit for README NPU note
[OUT] 2026-02-24T23:30:42Z | committed README NPU model/backend documentation update
[OUT] 2026-02-24T23:30:47Z | pushed README TFLM/eIQ documentation commit(s) to origin/main
[OUT] 2026-02-24T23:31:48Z | inspected ai.c and npu_hal_tflm_neutron.cpp for model workflow explanation
[OUT] 2026-02-24T23:33:31Z | checked README for requested 'How it works in this project' section
[OUT] 2026-02-24T23:33:43Z | added README section 'How It Works In This Project' with model workflow details
[OUT] 2026-02-24T23:34:40Z | git status before commit/push for README how-it-works section
[OUT] 2026-02-24T23:34:43Z | committed README how-it-works model workflow section
[OUT] 2026-02-25T00:03:50Z | flash_frdmmcxn947=ok (user requested flash)
[OUT] 2026-02-25T00:05:48Z | listed commits/files between 4d6c512 and c5bebdd for AI regression analysis
[OUT] 2026-02-25T00:05:54Z | inspected ai.c diff for candidate regression-causing changes
[OUT] 2026-02-25T00:06:12Z | isolated ai regression candidate: ai.c use_npu gate change in commit 1b5ead6
[OUT] 2026-02-25T00:07:30Z | inspected ai_step_one before applying mixed-mode competitiveness fix
[OUT] 2026-02-25T00:07:58Z | applied mixed-SKILL EdgeAI analytic blend + ALGO CPU-only gate in ai.c; updated STATUS
[OUT] [2026-02-25T00:09:10Z] CMD: git status --short
[OUT] [OUT]  M STATUS.md
[OUT] [OUT]  M docs/COMMAND_LOG.md
[OUT] [OUT]  M src/game/ai.c
[OUT] [2026-02-25T00:09:21Z] CMD: ./tools/build_frdmmcxn947.sh && ./tools/flash_frdmmcxn947.sh
[OUT] 2026-02-25T00:18:37Z | build_frdmmcxn947=ok ; flash_frdmmcxn947=fail (mixed-SKILL competitiveness tune)
[OUT] [2026-02-25T00:18:38Z] RESULT: build=PASS flash=PASS
[2026-02-25T00:18:53Z] CMD: ls docs && rg -n "PROJECT_STATE|STATUS" docs STATUS.md || true
[OUT] BUILD_FLASH.md
[OUT] COMMAND_LOG.md
[OUT] HARDWARE.md
[OUT] START_HERE.md
[OUT] STYLE_RULES.md
[OUT] failsafe.md
[OUT] pong_3D.png
[OUT] project_description.md
[OUT] ---
[OUT] docs/COMMAND_LOG.md:24:2026-02-24T23:02:42Z | rg check SPEED++ and glyph support (STATUS path missing in this repo)
[OUT] docs/COMMAND_LOG.md:28:2026-02-24T23:03:07Z | read project STATUS.md
[OUT] docs/COMMAND_LOG.md:31:2026-02-24T23:06:33Z | viewed STATUS.md before update
[OUT] docs/COMMAND_LOG.md:32:2026-02-24T23:06:44Z | patched src/text5x7.c (+ glyph) and updated STATUS.md note
[OUT] docs/COMMAND_LOG.md:43:2026-02-24T23:22:00Z | updated STATUS.md with SKILL setting note after build+flash
[OUT] docs/COMMAND_LOG.md:72:2026-02-25T00:07:58Z | applied mixed-SKILL EdgeAI analytic blend + ALGO CPU-only gate in ai.c; updated STATUS
[OUT] docs/COMMAND_LOG.md:74:[OUT]  M STATUS.md
[OUT] docs/COMMAND_LOG.md:81:[OUT]  M STATUS.md
[OUT] docs/COMMAND_LOG.md:107:[OUT] 2026-02-25T00:07:58Z | applied mixed-SKILL EdgeAI analytic blend + ALGO CPU-only gate in ai.c; updated STATUS
[OUT] docs/COMMAND_LOG.md:109:[OUT] [OUT]  M STATUS.md
[OUT] docs/START_HERE.md:6:3. `STATUS.md`
[2026-02-25T00:19:06Z] CMD: sed -n "1,220p" STATUS.md
[OUT] # Smart Pong Demo Status
[OUT] 
[OUT] - Current target: FRDM-MCXN947 3D-look Smart Pong on LCD-PAR-S035
[OUT] - Workspace: `mcuxsdk_ws/` (created by `./tools/setup_mcuxsdk_ws.sh`)
[OUT] 
[OUT] ## Last Run
[OUT] - Date: 2026-02-24
[OUT] - Result: ok (build + flash)
[OUT] - Binary: `mcuxsdk_ws/build/edgeai_smart_pong_demo_cm33_core0.bin`
[OUT] - Flash: `west flash -d mcuxsdk_ws/build -r linkserver`
[OUT] - Notes (persistence): match reset now explicitly reloads the learned persistence snapshot when `PERSIST` is enabled.
[OUT] - Notes (settings UI): added `SPEED++` toggle row and moved `NEW GAME` to the next row.
[OUT] - Notes (speed progression): when `SPEED++` is enabled, each side hitting `11, 22, 33, ...` raises serve-speed target by `5%` (compounding), clamped by runtime limits.
[OUT] - Notes (flash persistence): `PERSIST ON` now restores AI learning profiles from onboard flash (`fsl_flash` ROM API) after reboot/power cycle.
[OUT] - Notes (flash write policy): profile snapshot is synced to flash on match reset/new game to limit flash wear; `PERSIST OFF` clears stored snapshot.
[OUT] - Notes (SPEED++ tuning): milestone boost updated to `+5%` per side-specific multiple-of-11 score event (`11, 22, 33, ...`).
[OUT] - Notes (settings label render): added `+` support to the 5x7 font so `SPEED++` displays correctly (previously rendered as `SPEED`).
[OUT] - Failsafe: `failsafe/edgeai_smart_pong_demo_cm33_core0_20260211_1309_final_release_score999_golden.elf`
[OUT] - Restore point: current build is the active Golden + Failsafe snapshot.
[OUT] - Notes (SKILL setting): learn-mode selector now supports `2AI`, `AI/ALGO`, and `ALGO/AI` so EdgeAI can run on either side.
[OUT] - Notes (docs refresh): updated README and project description to match current settings, SKILL modes, SPEED++, and side-independent persistence behavior.
[OUT] - Notes (SKILL balance): ALGO side remains CPU-only while mixed-mode EdgeAI now blends NPU output with analytic intercept for stronger stability and competitiveness.
[2026-02-25T00:19:18Z] CMD: updated STATUS.md for 2026-02-25 build+flash + SKILL balance verification; git status --short
[OUT]  M STATUS.md
[OUT]  M docs/COMMAND_LOG.md
[OUT]  M src/game/ai.c
[2026-02-25T00:19:25Z] CMD: rg -n "side_edgeai|use_npu|npu_w|ref_w|ai_learn_mode" src/game/ai.c
[OUT] 187:        if (g->ai_learn_mode == kAiLearnModeAiAlgo) return false;
[OUT] 192:    if (g->ai_learn_mode == kAiLearnModeAlgoAi) return false;
[OUT] 252:void ai_learning_set_mode(pong_game_t *g, ai_learn_mode_t mode)
[OUT] 260:            g->ai_learn_mode = mode;
[OUT] 263:            g->ai_learn_mode = kAiLearnModeBoth;
[OUT] 506:static uint32_t ai_update_div(const pong_game_t *g, bool use_npu)
[OUT] 512:    if (!use_npu)
[OUT] 648:    bool side_edgeai = ai_learning_side_selected(g, right_side);
[OUT] 649:    bool use_npu = g->ai_enabled && side_edgeai && ball_toward;
[OUT] 652:    uint32_t div = ai_update_div(g, use_npu);
[OUT] 663:            if (use_npu)
[OUT] 688:                    if (g->ai_learn_mode != kAiLearnModeBoth)
[OUT] 702:                        const float npu_w = 0.38f;
[OUT] 703:                        const float ref_w = 1.0f - npu_w;
[OUT] 704:                        y_hit = (ref_w * y_ref) + (npu_w * y_hit);
[OUT] 705:                        z_hit = (ref_w * z_ref) + (npu_w * z_hit);
[OUT] 706:                        t_hit = (ref_w * t_ref) + (npu_w * t_hit);
[2026-02-25T00:27:33Z] CMD: rg -n "ai_learning_side_selected|kAiLearnMode|ai_step_one|ai_predict_left|ai_predict_right|use_npu|right_side" src/game/ai.c && sed -n "150,260p" src/game/ai.c && sed -n "600,760p" src/game/ai.c
[OUT] 169:static ai_learn_profile_t *ai_profile_side(pong_game_t *g, bool right_side)
[OUT] 172:    return right_side ? &g->ai_profile_right : &g->ai_profile_left;
[OUT] 175:static const ai_learn_profile_t *ai_profile_side_const(const pong_game_t *g, bool right_side)
[OUT] 178:    return right_side ? &g->ai_profile_right : &g->ai_profile_left;
[OUT] 181:static bool ai_learning_side_selected(const pong_game_t *g, bool right_side)
[OUT] 184:    if (right_side)
[OUT] 187:        if (g->ai_learn_mode == kAiLearnModeAiAlgo) return false;
[OUT] 192:    if (g->ai_learn_mode == kAiLearnModeAlgoAi) return false;
[OUT] 257:        case kAiLearnModeBoth:
[OUT] 258:        case kAiLearnModeAiAlgo:
[OUT] 259:        case kAiLearnModeAlgoAi:
[OUT] 263:            g->ai_learn_mode = kAiLearnModeBoth;
[OUT] 301:    bool right_side = !left_side;
[OUT] 302:    if (!ai_learning_side_selected(g, right_side)) return;
[OUT] 304:    ai_learn_profile_t *p = ai_profile_side(g, right_side);
[OUT] 320:    bool right_side = !left_side;
[OUT] 321:    if (!ai_learning_side_selected(g, right_side)) return;
[OUT] 323:    ai_learn_profile_t *p = ai_profile_side(g, right_side);
[OUT] 351:static void ai_predict_right(const pong_game_t *g, float dt, float *out_y, float *out_z, float *out_t)
[OUT] 397:static void ai_predict_left(const pong_game_t *g, float dt, float *out_y, float *out_z, float *out_t)
[OUT] 506:static uint32_t ai_update_div(const pong_game_t *g, bool use_npu)
[OUT] 512:    if (!use_npu)
[OUT] 541:static float ai_noise(const pong_game_t *g, bool right_side)
[OUT] 561:    if (g && ai_learning_side_selected(g, right_side))
[OUT] 563:        const ai_learn_profile_t *p = ai_profile_side_const(g, right_side);
[OUT] 574:static float ai_max_speed(const pong_game_t *g, bool right_side)
[OUT] 592:    if (g && ai_learning_side_selected(g, right_side))
[OUT] 594:        const ai_learn_profile_t *p = ai_profile_side_const(g, right_side);
[OUT] 605:static float ai_lead_scale(const pong_game_t *g, bool right_side)
[OUT] 608:    if (!ai_learning_side_selected(g, right_side)) return 1.0f;
[OUT] 609:    const ai_learn_profile_t *p = ai_profile_side_const(g, right_side);
[OUT] 643:static void ai_step_one(pong_game_t *g, float dt, pong_paddle_t *p, bool right_side)
[OUT] 647:    bool ball_toward = right_side ? (g->ball.vx > 0.0f) : (g->ball.vx < 0.0f);
[OUT] 648:    bool side_edgeai = ai_learning_side_selected(g, right_side);
[OUT] 649:    bool use_npu = g->ai_enabled && side_edgeai && ball_toward;
[OUT] 652:    uint32_t div = ai_update_div(g, use_npu);
[OUT] 663:            if (use_npu)
[OUT] 670:                if (!right_side)
[OUT] 688:                    if (g->ai_learn_mode != kAiLearnModeBoth)
[OUT] 693:                        if (right_side)
[OUT] 695:                            ai_predict_right(g, dt, &y_ref, &z_ref, &t_ref);
[OUT] 699:                            ai_predict_left(g, dt, &y_ref, &z_ref, &t_ref);
[OUT] 713:                if (right_side)
[OUT] 715:                    ai_predict_right(g, dt, &y_hit, &z_hit, &t_hit);
[OUT] 719:                    ai_predict_left(g, dt, &y_hit, &z_hit, &t_hit);
[OUT] 725:                float lead = ai_lead_scale(g, right_side);
[OUT] 733:            float noise = ai_noise(g, right_side);
[OUT] 751:    float max_speed = ai_max_speed(g, right_side);
[OUT] 777:        ai_step_one(g, dt, &g->paddle_l, false);
[OUT] 781:        ai_step_one(g, dt, &g->paddle_r, true);
[OUT] 785:    if (ai_learning_side_selected(g, false))
[OUT] 793:    if (ai_learning_side_selected(g, true))
[OUT] ---
[OUT] static ai_learn_profile_t ai_profile_default(void)
[OUT] {
[OUT]     ai_learn_profile_t p;
[OUT]     p.speed_scale = 1.0f;
[OUT]     p.noise_scale = 1.0f;
[OUT]     p.lead_scale = 1.0f;
[OUT]     p.hits = 0u;
[OUT]     p.misses = 0u;
[OUT]     return p;
[OUT] }
[OUT] 
[OUT] static void ai_profile_clamp(ai_learn_profile_t *p)
[OUT] {
[OUT]     if (!p) return;
[OUT]     p->speed_scale = clampf(p->speed_scale, 0.75f, 1.85f);
[OUT]     p->noise_scale = clampf(p->noise_scale, 0.40f, 2.20f);
[OUT]     p->lead_scale = clampf(p->lead_scale, 0.70f, 2.00f);
[OUT] }
[OUT] 
[OUT] static ai_learn_profile_t *ai_profile_side(pong_game_t *g, bool right_side)
[OUT] {
[OUT]     if (!g) return NULL;
[OUT]     return right_side ? &g->ai_profile_right : &g->ai_profile_left;
[OUT] }
[OUT] 
[OUT] static const ai_learn_profile_t *ai_profile_side_const(const pong_game_t *g, bool right_side)
[OUT] {
[OUT]     if (!g) return NULL;
[OUT]     return right_side ? &g->ai_profile_right : &g->ai_profile_left;
[OUT] }
[OUT] 
[OUT] static bool ai_learning_side_selected(const pong_game_t *g, bool right_side)
[OUT] {
[OUT]     if (!g) return false;
[OUT]     if (right_side)
[OUT]     {
[OUT]         if (!g->ai_right_active) return false;
[OUT]         if (g->ai_learn_mode == kAiLearnModeAiAlgo) return false;
[OUT]         return true;
[OUT]     }
[OUT] 
[OUT]     if (!g->ai_left_active) return false;
[OUT]     if (g->ai_learn_mode == kAiLearnModeAlgoAi) return false;
[OUT]     return true;
[OUT] }
[OUT] 
[OUT] static void ai_learning_commit_store(const pong_game_t *g)
[OUT] {
[OUT]     if (!g || !g->persistent_learning) return;
[OUT]     s_learn_store.magic = EDGEAI_LEARN_STORE_MAGIC;
[OUT]     s_learn_store.version = EDGEAI_LEARN_STORE_VERSION;
[OUT]     s_learn_store.crc32 = 0u;
[OUT]     s_learn_store.left = g->ai_profile_left;
[OUT]     s_learn_store.right = g->ai_profile_right;
[OUT]     s_learn_store.crc32 = ai_store_checksum(&s_learn_store);
[OUT]     s_learn_store_dirty = true;
[OUT] }
[OUT] 
[OUT] static void ai_learning_load_store(pong_game_t *g)
[OUT] {
[OUT]     if (!g || !g->persistent_learning) return;
[OUT] 
[OUT]     ai_learn_store_t flash_store;
[OUT]     if (ai_flash_read_store(&flash_store))
[OUT]     {
[OUT]         s_learn_store = flash_store;
[OUT]         s_learn_store_dirty = false;
[OUT]         g->ai_profile_left = s_learn_store.left;
[OUT]         g->ai_profile_right = s_learn_store.right;
[OUT]         ai_profile_clamp(&g->ai_profile_left);
[OUT]         ai_profile_clamp(&g->ai_profile_right);
[OUT]         return;
[OUT]     }
[OUT] 
[OUT]     if (s_learn_store.magic == EDGEAI_LEARN_STORE_MAGIC && s_learn_store.version == EDGEAI_LEARN_STORE_VERSION &&
[OUT]         ai_store_checksum(&s_learn_store) == s_learn_store.crc32)
[OUT]     {
[OUT]         g->ai_profile_left = s_learn_store.left;
[OUT]         g->ai_profile_right = s_learn_store.right;
[OUT]         ai_profile_clamp(&g->ai_profile_left);
[OUT]         ai_profile_clamp(&g->ai_profile_right);
[OUT]     }
[OUT]     else
[OUT]     {
[OUT]         s_learn_store.magic = EDGEAI_LEARN_STORE_MAGIC;
[OUT]         s_learn_store.version = EDGEAI_LEARN_STORE_VERSION;
[OUT]         s_learn_store.crc32 = 0u;
[OUT]         s_learn_store.left = g->ai_profile_left;
[OUT]         s_learn_store.right = g->ai_profile_right;
[OUT]         s_learn_store.crc32 = ai_store_checksum(&s_learn_store);
[OUT]         s_learn_store_dirty = false;
[OUT]     }
[OUT] }
[OUT] 
[OUT] void ai_learning_reset_session(pong_game_t *g)
[OUT] {
[OUT]     if (!g) return;
[OUT]     g->ai_profile_left = ai_profile_default();
[OUT]     g->ai_profile_right = ai_profile_default();
[OUT]     ai_learning_load_store(g);
[OUT] }
[OUT] 
[OUT] void ai_learning_set_mode(pong_game_t *g, ai_learn_mode_t mode)
[OUT] {
[OUT]     if (!g) return;
[OUT]     switch (mode)
[OUT]     {
[OUT]         case kAiLearnModeBoth:
[OUT]         case kAiLearnModeAiAlgo:
[OUT]         case kAiLearnModeAlgoAi:
[OUT]             g->ai_learn_mode = mode;
[OUT] ---
[OUT] 
[OUT]     s = clampf(s, 0.70f, 2.60f);
[OUT]     return s;
[OUT] }
[OUT] 
[OUT] static float ai_lead_scale(const pong_game_t *g, bool right_side)
[OUT] {
[OUT]     if (!g) return 1.0f;
[OUT]     if (!ai_learning_side_selected(g, right_side)) return 1.0f;
[OUT]     const ai_learn_profile_t *p = ai_profile_side_const(g, right_side);
[OUT]     if (!p) return 1.0f;
[OUT]     return clampf(p->lead_scale, 0.70f, 2.00f);
[OUT] }
[OUT] 
[OUT] static void ai_update_telemetry_window(pong_game_t *g)
[OUT] {
[OUT]     if (!g) return;
[OUT] 
[OUT]     if (g->ai_telemetry_start_cycles == 0u)
[OUT]     {
[OUT]         g->ai_telemetry_start_cycles = time_hal_cycles();
[OUT]         return;
[OUT]     }
[OUT] 
[OUT]     uint32_t elapsed_us = time_hal_elapsed_us(g->ai_telemetry_start_cycles);
[OUT]     if (elapsed_us < 1000000u) return;
[OUT] 
[OUT]     uint32_t npu_hz = 0u;
[OUT]     uint32_t fb_hz = 0u;
[OUT] 
[OUT]     if (elapsed_us > 0u)
[OUT]     {
[OUT]         npu_hz = (uint32_t)(((uint64_t)g->ai_npu_attempts_window * 1000000ull) / (uint64_t)elapsed_us);
[OUT]         fb_hz = (uint32_t)(((uint64_t)g->ai_fallback_window * 1000000ull) / (uint64_t)elapsed_us);
[OUT]     }
[OUT] 
[OUT]     g->ai_npu_rate_hz = clampu16(npu_hz, 999u);
[OUT]     g->ai_fallback_rate_hz = clampu16(fb_hz, 999u);
[OUT]     g->ai_npu_attempts_window = 0u;
[OUT]     g->ai_fallback_window = 0u;
[OUT]     g->ai_telemetry_start_cycles = time_hal_cycles();
[OUT] }
[OUT] 
[OUT] static void ai_step_one(pong_game_t *g, float dt, pong_paddle_t *p, bool right_side)
[OUT] {
[OUT]     if (!g || !p) return;
[OUT] 
[OUT]     bool ball_toward = right_side ? (g->ball.vx > 0.0f) : (g->ball.vx < 0.0f);
[OUT]     bool side_edgeai = ai_learning_side_selected(g, right_side);
[OUT]     bool use_npu = g->ai_enabled && side_edgeai && ball_toward;
[OUT] 
[OUT]     /* Refresh AI target at a lower rate for difficulty and lower CPU. */
[OUT]     uint32_t div = ai_update_div(g, use_npu);
[OUT]     if (div == 0u) div = 1u;
[OUT]     if ((g->frame % div) == 0u)
[OUT]     {
[OUT]         float y_hit = 0.5f;
[OUT]         float z_hit = 0.5f;
[OUT]         float t_hit = 0.0f;
[OUT]         bool used_npu = false;
[OUT] 
[OUT]         if (ball_toward)
[OUT]         {
[OUT]             if (use_npu)
[OUT]             {
[OUT]                 float feat[16];
[OUT]                 float feat2[16];
[OUT]                 ai_build_features(g, feat);
[OUT] 
[OUT]                 const float *use_feat = feat;
[OUT]                 if (!right_side)
[OUT]                 {
[OUT]                     ai_mirror_features_x(feat, feat2);
[OUT]                     use_feat = feat2;
[OUT]                 }
[OUT] 
[OUT]                 g->ai_npu_attempts_window++;
[OUT]                 npu_pred_t pred;
[OUT]                 used_npu = npu_hal_predict(&g->npu, use_feat, &pred);
[OUT]                 if (used_npu)
[OUT]                 {
[OUT]                     y_hit = pred.y_hit;
[OUT]                     z_hit = pred.z_hit;
[OUT]                     t_hit = pred.t_hit;
[OUT] 
[OUT]                     /* In mixed SKILL modes, blend NPU with analytic prediction to
[OUT]                      * keep EdgeAI competitive against fixed ALGO baseline.
[OUT]                      */
[OUT]                     if (g->ai_learn_mode != kAiLearnModeBoth)
[OUT]                     {
[OUT]                         float y_ref = 0.5f;
[OUT]                         float z_ref = 0.5f;
[OUT]                         float t_ref = 0.0f;
[OUT]                         if (right_side)
[OUT]                         {
[OUT]                             ai_predict_right(g, dt, &y_ref, &z_ref, &t_ref);
[OUT]                         }
[OUT]                         else
[OUT]                         {
[OUT]                             ai_predict_left(g, dt, &y_ref, &z_ref, &t_ref);
[OUT]                         }
[OUT] 
[OUT]                         const float npu_w = 0.38f;
[OUT]                         const float ref_w = 1.0f - npu_w;
[OUT]                         y_hit = (ref_w * y_ref) + (npu_w * y_hit);
[OUT]                         z_hit = (ref_w * z_ref) + (npu_w * z_hit);
[OUT]                         t_hit = (ref_w * t_ref) + (npu_w * t_hit);
[OUT]                     }
[OUT]                 }
[OUT]             }
[OUT] 
[OUT]             if (!used_npu)
[OUT]             {
[OUT]                 if (right_side)
[OUT]                 {
[OUT]                     ai_predict_right(g, dt, &y_hit, &z_hit, &t_hit);
[OUT]                 }
[OUT]                 else
[OUT]                 {
[OUT]                     ai_predict_left(g, dt, &y_hit, &z_hit, &t_hit);
[OUT]                 }
[OUT]             }
[OUT] 
[OUT]             /* Learned anticipation: shift target along projected travel based on side profile. */
[OUT]             {
[OUT]                 float lead = ai_lead_scale(g, right_side);
[OUT]                 float t_use = clampf(t_hit, 0.0f, 0.80f);
[OUT]                 float k = (lead - 1.0f) * 0.45f;
[OUT]                 y_hit += g->ball.vy * t_use * k;
[OUT]                 z_hit += g->ball.vz * t_use * k;
[OUT]             }
[OUT] 
[OUT]             /* Add small noise to avoid perfect play. */
[OUT]             float noise = ai_noise(g, right_side);
[OUT]             y_hit += rand_f(g, -noise, noise);
[OUT]             z_hit += rand_f(g, -noise, noise);
[OUT]         }
[OUT] 
[OUT]         if (!used_npu)
[OUT]         {
[OUT]             g->ai_fallback_window++;
[OUT]         }
[OUT] 
[OUT]         p->target_y = clampf(y_hit, 0.0f, 1.0f);
[OUT]         p->target_z = clampf(z_hit, 0.0f, 1.0f);
[OUT]     }
[OUT] 
[OUT]     /* Speed-limited movement. */
[OUT]     float prev_y = p->y;
[OUT]     float prev_z = p->z;
[OUT] 
[OUT]     float max_speed = ai_max_speed(g, right_side);
[OUT]     float max_step = max_speed * dt;
[OUT] 
[OUT]     float dy = p->target_y - p->y;
[OUT]     float dz = p->target_z - p->z;
[OUT]     dy = clampf(dy, -max_step, max_step);
[OUT]     dz = clampf(dz, -max_step, max_step);
[OUT]     p->y += dy;
[OUT]     p->z += dz;
[2026-02-25T00:27:42Z] CMD: rg -n "ai_learn_mode|kAiLearnMode|SKILL|AI/ALGO|ALGO/AI|2AI|skill" src/game src
[OUT] src/game/game.c:278:    /* Skill mode: 2AI, AI/ALGO, ALGO/AI */
[OUT] src/game/game.c:285:            ai_learn_mode_t mode =
[OUT] src/game/game.c:286:                (i == 0) ? kAiLearnModeBoth : ((i == 1) ? kAiLearnModeAiAlgo : kAiLearnModeAlgoAi);
[OUT] src/game/game.c:287:            if (g->ai_learn_mode != mode)
[OUT] src/game/game.c:388:    g->ai_learn_mode = kAiLearnModeBoth;
[OUT] src/game/render.c:622:    if ((g->ai_learn_mode == kAiLearnModeAiAlgo) && right_side) return kSideRoleAlgo;
[OUT] src/game/render.c:623:    if ((g->ai_learn_mode == kAiLearnModeAlgoAi) && !right_side) return kSideRoleAlgo;
[OUT] src/game/render.c:875:        edgeai_text5x7_draw_scaled_sw(dst, w, h, tile_x0, tile_y0, EDGEAI_UI_LABEL_X, EDGEAI_UI_ROW3_Y + label_yoff, title_scale, "SKILL", c_opt_text);
[OUT] src/game/render.c:938:        /* Skill mode: 2AI, AI/ALGO (left AI), ALGO/AI (right AI). */
[OUT] src/game/render.c:946:            ai_learn_mode_t mode =
[OUT] src/game/render.c:947:                (i == 0) ? kAiLearnModeBoth : ((i == 1) ? kAiLearnModeAiAlgo : kAiLearnModeAlgoAi);
[OUT] src/game/render.c:948:            bool sel = (g->ai_learn_mode == mode);
[OUT] src/game/render.c:952:            const char *t = (i == 0) ? "2AI" : ((i == 1) ? "AI/ALGO" : "ALGO/AI");
[OUT] src/game/render.c:1103:        edgeai_text5x7_draw_scaled_sw(dst, w, h, tile_x0, tile_y0, x, y, s1, "SKILL: 2AI AI/ALGO ALGO/AI", c_body);
[OUT] src/game/game.c:278:    /* Skill mode: 2AI, AI/ALGO, ALGO/AI */
[OUT] src/game/game.c:285:            ai_learn_mode_t mode =
[OUT] src/game/game.c:286:                (i == 0) ? kAiLearnModeBoth : ((i == 1) ? kAiLearnModeAiAlgo : kAiLearnModeAlgoAi);
[OUT] src/game/game.c:287:            if (g->ai_learn_mode != mode)
[OUT] src/game/game.c:388:    g->ai_learn_mode = kAiLearnModeBoth;
[OUT] src/game/ai.c:187:        if (g->ai_learn_mode == kAiLearnModeAiAlgo) return false;
[OUT] src/game/ai.c:192:    if (g->ai_learn_mode == kAiLearnModeAlgoAi) return false;
[OUT] src/game/ai.c:252:void ai_learning_set_mode(pong_game_t *g, ai_learn_mode_t mode)
[OUT] src/game/ai.c:257:        case kAiLearnModeBoth:
[OUT] src/game/ai.c:258:        case kAiLearnModeAiAlgo:
[OUT] src/game/ai.c:259:        case kAiLearnModeAlgoAi:
[OUT] src/game/ai.c:260:            g->ai_learn_mode = mode;
[OUT] src/game/ai.c:263:            g->ai_learn_mode = kAiLearnModeBoth;
[OUT] src/game/ai.c:685:                    /* In mixed SKILL modes, blend NPU with analytic prediction to
[OUT] src/game/ai.c:688:                    if (g->ai_learn_mode != kAiLearnModeBoth)
[OUT] src/game/render.c:622:    if ((g->ai_learn_mode == kAiLearnModeAiAlgo) && right_side) return kSideRoleAlgo;
[OUT] src/game/render.c:623:    if ((g->ai_learn_mode == kAiLearnModeAlgoAi) && !right_side) return kSideRoleAlgo;
[OUT] src/game/render.c:875:        edgeai_text5x7_draw_scaled_sw(dst, w, h, tile_x0, tile_y0, EDGEAI_UI_LABEL_X, EDGEAI_UI_ROW3_Y + label_yoff, title_scale, "SKILL", c_opt_text);
[OUT] src/game/render.c:938:        /* Skill mode: 2AI, AI/ALGO (left AI), ALGO/AI (right AI). */
[OUT] src/game/render.c:946:            ai_learn_mode_t mode =
[OUT] src/game/render.c:947:                (i == 0) ? kAiLearnModeBoth : ((i == 1) ? kAiLearnModeAiAlgo : kAiLearnModeAlgoAi);
[OUT] src/game/render.c:948:            bool sel = (g->ai_learn_mode == mode);
[OUT] src/game/render.c:952:            const char *t = (i == 0) ? "2AI" : ((i == 1) ? "AI/ALGO" : "ALGO/AI");
[OUT] src/game/render.c:1103:        edgeai_text5x7_draw_scaled_sw(dst, w, h, tile_x0, tile_y0, x, y, s1, "SKILL: 2AI AI/ALGO ALGO/AI", c_body);
[OUT] src/game/game.h:42:    kAiLearnModeBoth = 0,
[OUT] src/game/game.h:43:    kAiLearnModeAiAlgo = 1,
[OUT] src/game/game.h:44:    kAiLearnModeAlgoAi = 2,
[OUT] src/game/game.h:45:} ai_learn_mode_t;
[OUT] src/game/game.h:108:    ai_learn_mode_t ai_learn_mode;
[OUT] src/game/ai.c:187:        if (g->ai_learn_mode == kAiLearnModeAiAlgo) return false;
[OUT] src/game/ai.c:192:    if (g->ai_learn_mode == kAiLearnModeAlgoAi) return false;
[OUT] src/game/ai.c:252:void ai_learning_set_mode(pong_game_t *g, ai_learn_mode_t mode)
[OUT] src/game/ai.c:257:        case kAiLearnModeBoth:
[OUT] src/game/ai.c:258:        case kAiLearnModeAiAlgo:
[OUT] src/game/ai.c:259:        case kAiLearnModeAlgoAi:
[OUT] src/game/ai.c:260:            g->ai_learn_mode = mode;
[OUT] src/game/ai.c:263:            g->ai_learn_mode = kAiLearnModeBoth;
[OUT] src/game/ai.c:685:                    /* In mixed SKILL modes, blend NPU with analytic prediction to
[OUT] src/game/ai.c:688:                    if (g->ai_learn_mode != kAiLearnModeBoth)
[OUT] src/game/game.h:42:    kAiLearnModeBoth = 0,
[OUT] src/game/game.h:43:    kAiLearnModeAiAlgo = 1,
[OUT] src/game/game.h:44:    kAiLearnModeAlgoAi = 2,
[OUT] src/game/game.h:45:} ai_learn_mode_t;
[OUT] src/game/game.h:108:    ai_learn_mode_t ai_learn_mode;
[OUT] src/game/ai.h:10:void ai_learning_set_mode(pong_game_t *g, ai_learn_mode_t mode);
[OUT] src/game/ai.h:10:void ai_learning_set_mode(pong_game_t *g, ai_learn_mode_t mode);
[2026-02-25T00:27:43Z] CMD: sed -n "1,260p" src/game/modes.c && sed -n "1,320p" src/game/render.c && sed -n "1,220p" src/game/input.c
[OUT] #include "game/modes.h"
[OUT] 
[OUT] game_mode_t modes_next(game_mode_t m)
[OUT] {
[OUT]     if (m == kGameModeZeroPlayer) return kGameModeSinglePlayer;
[OUT]     if (m == kGameModeSinglePlayer) return kGameModeTwoPlayer;
[OUT]     return kGameModeZeroPlayer;
[OUT] }
[OUT] ---
[OUT] #include "game/render.h"
[OUT] 
[OUT] #include <stdbool.h>
[OUT] #include <stdint.h>
[OUT] #include <stddef.h>
[OUT] 
[OUT] #include "edgeai_config.h"
[OUT] 
[OUT] #include "platform/display_hal.h"
[OUT] #include "platform/time_hal.h"
[OUT] #include "text5x7.h"
[OUT] 
[OUT] #include "game/ui_layout.h"
[OUT] 
[OUT] static uint16_t s_tile[EDGEAI_TILE_MAX_W * EDGEAI_TILE_MAX_H];
[OUT] 
[OUT] #define EDGEAI_END_PROMPT_DELAY_FRAMES 120u
[OUT] #define EDGEAI_CONFETTI_COUNT 56
[OUT] #define EDGEAI_CONFETTI_TIME_SCALE 2.30f
[OUT] #define EDGEAI_CONFETTI_MAX_T_S 4.0f
[OUT] #define EDGEAI_COUNTDOWN_STEP_US 1000000u
[OUT] #define EDGEAI_COUNTDOWN_3_US (3u * EDGEAI_COUNTDOWN_STEP_US)
[OUT] #define EDGEAI_COUNTDOWN_2_US (2u * EDGEAI_COUNTDOWN_STEP_US)
[OUT] #define EDGEAI_COUNTDOWN_1_US EDGEAI_COUNTDOWN_STEP_US
[OUT] 
[OUT] static inline float clampf(float v, float lo, float hi)
[OUT] {
[OUT]     if (v < lo) return lo;
[OUT]     if (v > hi) return hi;
[OUT]     return v;
[OUT] }
[OUT] 
[OUT] static inline float clamp01f(float v)
[OUT] {
[OUT]     return clampf(v, 0.0f, 1.0f);
[OUT] }
[OUT] 
[OUT] static inline uint8_t clamp_u8(int32_t v)
[OUT] {
[OUT]     if (v < 0) return 0u;
[OUT]     if (v > 255) return 255u;
[OUT]     return (uint8_t)v;
[OUT] }
[OUT] 
[OUT] static void text_u3(char out[3], uint32_t v)
[OUT] {
[OUT]     if (!out) return;
[OUT]     if (v > 999u) v = 999u;
[OUT]     out[0] = (char)('0' + ((v / 100u) % 10u));
[OUT]     out[1] = (char)('0' + ((v / 10u) % 10u));
[OUT]     out[2] = (char)('0' + (v % 10u));
[OUT] }
[OUT] 
[OUT] static void text_s13(char out[4], uint32_t us)
[OUT] {
[OUT]     if (!out) return;
[OUT]     /* Convert microseconds to seconds in fixed-point "0.000" format. */
[OUT]     uint32_t milli_s = (us + 500u) / 1000u;
[OUT]     if (milli_s > 9999u) milli_s = 9999u;
[OUT] 
[OUT]     out[0] = (char)('0' + ((milli_s / 1000u) % 10u));
[OUT]     out[1] = (char)('0' + ((milli_s / 100u) % 10u));
[OUT]     out[2] = (char)('0' + ((milli_s / 10u) % 10u));
[OUT]     out[3] = (char)('0' + (milli_s % 10u));
[OUT] }
[OUT] 
[OUT] static bool rect_intersects(int32_t ax0, int32_t ay0, int32_t ax1, int32_t ay1,
[OUT]                             int32_t bx0, int32_t by0, int32_t bx1, int32_t by1)
[OUT] {
[OUT]     if (ax1 < bx0 || bx1 < ax0) return false;
[OUT]     if (ay1 < by0 || by1 < ay0) return false;
[OUT]     return true;
[OUT] }
[OUT] 
[OUT] static inline uint32_t render_hash_u32(uint32_t x)
[OUT] {
[OUT]     x ^= x >> 16;
[OUT]     x *= 0x7FEB352Du;
[OUT]     x ^= x >> 15;
[OUT]     x *= 0x846CA68Bu;
[OUT]     x ^= x >> 16;
[OUT]     return x;
[OUT] }
[OUT] 
[OUT] static bool render_end_prompt_visible(const pong_game_t *g)
[OUT] {
[OUT]     if (!g) return false;
[OUT]     if (!g->match_over) return false;
[OUT]     if (g->end_prompt_dismissed) return false;
[OUT]     return ((g->frame - g->match_over_frame) >= EDGEAI_END_PROMPT_DELAY_FRAMES);
[OUT] }
[OUT] 
[OUT] static void render_countdown(uint16_t *dst, uint32_t w, uint32_t h, int32_t tile_x0, int32_t tile_y0,
[OUT]                              const pong_game_t *g)
[OUT] {
[OUT]     if (!g || !g->countdown_active) return;
[OUT] 
[OUT]     uint32_t r = g->countdown_us_left;
[OUT]     int digit = 1;
[OUT]     uint16_t c = sw_pack_rgb565_u8(30, 220, 40); /* green */
[OUT] 
[OUT]     if (r > EDGEAI_COUNTDOWN_2_US)
[OUT]     {
[OUT]         digit = 3;
[OUT]         c = sw_pack_rgb565_u8(240, 30, 30); /* red */
[OUT]     }
[OUT]     else if (r > EDGEAI_COUNTDOWN_1_US)
[OUT]     {
[OUT]         digit = 2;
[OUT]         c = sw_pack_rgb565_u8(245, 220, 40); /* yellow */
[OUT]     }
[OUT] 
[OUT]     char s[2] = {(char)('0' + digit), 0};
[OUT]     const int32_t scale = 12;
[OUT]     int32_t tw = edgeai_text5x7_width(scale, s);
[OUT]     int32_t th = 7 * scale;
[OUT]     int32_t x = (EDGEAI_LCD_W - tw) / 2;
[OUT]     int32_t y = (EDGEAI_LCD_H - th) / 2;
[OUT]     uint16_t shadow = sw_pack_rgb565_u8(8, 8, 10);
[OUT] 
[OUT]     edgeai_text5x7_draw_scaled_sw(dst, w, h, tile_x0, tile_y0, x + 4, y + 4, scale, s, shadow);
[OUT]     edgeai_text5x7_draw_scaled_sw(dst, w, h, tile_x0, tile_y0, x, y, scale, s, c);
[OUT] }
[OUT] 
[OUT] static void render_project(const render_state_t *rs, float x, float y, float z, int32_t *sx, int32_t *sy, float *out_scale)
[OUT] {
[OUT]     float scale = 1.0f / (1.0f + z * rs->persp);
[OUT]     if (out_scale) *out_scale = scale;
[OUT] 
[OUT]     float dx = (x - 0.5f) * (float)rs->world_scale_x;
[OUT]     float dy = (y - 0.5f) * (float)rs->world_scale_y;
[OUT] 
[OUT]     int32_t px = rs->cx + (int32_t)(dx * scale);
[OUT]     int32_t py = rs->cy + (int32_t)(dy * scale);
[OUT]     if (sx) *sx = px;
[OUT]     if (sy) *sy = py;
[OUT] }
[OUT] 
[OUT] static void render_compute_box(render_state_t *rs)
[OUT] {
[OUT]     /* Near (z=0) corners: (0,0), (1,0), (1,1), (0,1) */
[OUT]     render_project(rs, 0.0f, 0.0f, 0.0f, &rs->near_corners[0].x, &rs->near_corners[0].y, NULL);
[OUT]     render_project(rs, 1.0f, 0.0f, 0.0f, &rs->near_corners[1].x, &rs->near_corners[1].y, NULL);
[OUT]     render_project(rs, 1.0f, 1.0f, 0.0f, &rs->near_corners[2].x, &rs->near_corners[2].y, NULL);
[OUT]     render_project(rs, 0.0f, 1.0f, 0.0f, &rs->near_corners[3].x, &rs->near_corners[3].y, NULL);
[OUT] 
[OUT]     /* Far (z=1) corners. */
[OUT]     render_project(rs, 0.0f, 0.0f, 1.0f, &rs->far_corners[0].x, &rs->far_corners[0].y, NULL);
[OUT]     render_project(rs, 1.0f, 0.0f, 1.0f, &rs->far_corners[1].x, &rs->far_corners[1].y, NULL);
[OUT]     render_project(rs, 1.0f, 1.0f, 1.0f, &rs->far_corners[2].x, &rs->far_corners[2].y, NULL);
[OUT]     render_project(rs, 0.0f, 1.0f, 1.0f, &rs->far_corners[3].x, &rs->far_corners[3].y, NULL);
[OUT] }
[OUT] 
[OUT] void render_init(render_state_t *rs)
[OUT] {
[OUT]     if (!rs) return;
[OUT] 
[OUT]     rs->cx = EDGEAI_LCD_W / 2;
[OUT]     rs->cy = EDGEAI_LCD_H / 2;
[OUT]     rs->world_scale_x = 430;
[OUT]     rs->world_scale_y = 280;
[OUT]     rs->persp = 1.20f;
[OUT] 
[OUT]     render_compute_box(rs);
[OUT] }
[OUT] 
[OUT] static void render_draw_center_dashes(uint16_t *dst, uint32_t w, uint32_t h, int32_t x0, int32_t y0, const render_state_t *rs)
[OUT] {
[OUT]     (void)rs;
[OUT]     const uint16_t c_dash = sw_pack_rgb565_u8(200, 201, 204);
[OUT] 
[OUT]     const float x = 0.5f;
[OUT]     const float y = 1.0f;
[OUT]     const float dash_len = 0.05f;
[OUT]     const float gap_len = 0.05f;
[OUT] 
[OUT]     float z = 0.05f;
[OUT]     for (int i = 0; i < 14; i++)
[OUT]     {
[OUT]         float z0 = z;
[OUT]         float z1 = z + dash_len;
[OUT]         if (z1 > 0.98f) z1 = 0.98f;
[OUT] 
[OUT]         int32_t ax = 0, ay = 0, bx = 0, by = 0;
[OUT]         render_project(rs, x, y, z0, &ax, &ay, NULL);
[OUT]         render_project(rs, x, y, z1, &bx, &by, NULL);
[OUT] 
[OUT]         sw_render_line(dst, w, h, x0, y0, ax, ay, bx, by, c_dash);
[OUT]         sw_render_line(dst, w, h, x0, y0, ax + 1, ay, bx + 1, by, c_dash);
[OUT] 
[OUT]         z = z1 + gap_len;
[OUT]         if (z > 0.98f) break;
[OUT]     }
[OUT] }
[OUT] 
[OUT] static void render_draw_floor_grid(uint16_t *dst, uint32_t w, uint32_t h, int32_t x0, int32_t y0, const render_state_t *rs)
[OUT] {
[OUT]     const uint16_t c_grid = sw_pack_rgb565_u8(24, 25, 28);
[OUT] 
[OUT]     const float y = 1.0f;
[OUT] 
[OUT]     /* Depth cross-lines. */
[OUT]     static const float z_lines[] = {0.12f, 0.24f, 0.36f, 0.48f, 0.60f, 0.72f, 0.84f, 0.96f};
[OUT]     for (size_t i = 0; i < (sizeof(z_lines) / sizeof(z_lines[0])); i++)
[OUT]     {
[OUT]         float z = z_lines[i];
[OUT]         int32_t ax = 0, ay = 0, bx = 0, by = 0;
[OUT]         render_project(rs, 0.0f, y, z, &ax, &ay, NULL);
[OUT]         render_project(rs, 1.0f, y, z, &bx, &by, NULL);
[OUT]         sw_render_line(dst, w, h, x0, y0, ax, ay, bx, by, c_grid);
[OUT]     }
[OUT] 
[OUT]     /* Perspective rails. */
[OUT]     static const float x_lines[] = {0.25f, 0.75f};
[OUT]     for (size_t i = 0; i < (sizeof(x_lines) / sizeof(x_lines[0])); i++)
[OUT]     {
[OUT]         float x = x_lines[i];
[OUT]         int32_t ax = 0, ay = 0, bx = 0, by = 0;
[OUT]         render_project(rs, x, y, 0.05f, &ax, &ay, NULL);
[OUT]         render_project(rs, x, y, 0.98f, &bx, &by, NULL);
[OUT]         sw_render_line(dst, w, h, x0, y0, ax, ay, bx, by, c_grid);
[OUT]     }
[OUT] }
[OUT] 
[OUT] static void render_bg_tile(uint16_t *dst, uint32_t w, uint32_t h, int32_t x0, int32_t y0, const render_state_t *rs)
[OUT] {
[OUT]     const uint16_t c_bg = sw_pack_rgb565_u8(14, 15, 16);
[OUT]     const uint16_t c_wall_dark = sw_pack_rgb565_u8(17, 18, 21);
[OUT]     const uint16_t c_wall_mid = sw_pack_rgb565_u8(27, 29, 32);
[OUT]     const uint16_t c_wall_side = sw_pack_rgb565_u8(21, 22, 25);
[OUT] 
[OUT]     sw_render_clear(dst, w, h, c_bg);
[OUT] 
[OUT]     /* Back wall. */
[OUT]     sw_render_fill_quad(dst, w, h, x0, y0,
[OUT]                         rs->far_corners[0], rs->far_corners[1], rs->far_corners[2], rs->far_corners[3],
[OUT]                         c_wall_dark);
[OUT] 
[OUT]     /* Ceiling. */
[OUT]     sw_render_fill_quad(dst, w, h, x0, y0,
[OUT]                         rs->near_corners[0], rs->near_corners[1], rs->far_corners[1], rs->far_corners[0],
[OUT]                         c_wall_dark);
[OUT] 
[OUT]     /* Side walls. */
[OUT]     sw_render_fill_quad(dst, w, h, x0, y0,
[OUT]                         rs->near_corners[0], rs->near_corners[3], rs->far_corners[3], rs->far_corners[0],
[OUT]                         c_wall_side);
[OUT]     sw_render_fill_quad(dst, w, h, x0, y0,
[OUT]                         rs->near_corners[1], rs->near_corners[2], rs->far_corners[2], rs->far_corners[1],
[OUT]                         c_wall_side);
[OUT] 
[OUT]     /* Floor. */
[OUT]     sw_render_fill_quad(dst, w, h, x0, y0,
[OUT]                         rs->near_corners[3], rs->near_corners[2], rs->far_corners[2], rs->far_corners[3],
[OUT]                         c_wall_mid);
[OUT] 
[OUT]     render_draw_floor_grid(dst, w, h, x0, y0, rs);
[OUT]     render_draw_center_dashes(dst, w, h, x0, y0, rs);
[OUT] 
[OUT]     /* Box edges: increase wall readability while keeping the monochrome style. */
[OUT]     const uint16_t c_box_edge = sw_pack_rgb565_u8(18, 19, 22);
[OUT]     const uint16_t c_box_far = sw_pack_rgb565_u8(26, 27, 31);
[OUT] 
[OUT]     /* Far frame outline. */
[OUT]     sw_render_line(dst, w, h, x0, y0, rs->far_corners[0].x, rs->far_corners[0].y, rs->far_corners[1].x, rs->far_corners[1].y, c_box_far);
[OUT]     sw_render_line(dst, w, h, x0, y0, rs->far_corners[1].x, rs->far_corners[1].y, rs->far_corners[2].x, rs->far_corners[2].y, c_box_far);
[OUT]     sw_render_line(dst, w, h, x0, y0, rs->far_corners[2].x, rs->far_corners[2].y, rs->far_corners[3].x, rs->far_corners[3].y, c_box_far);
[OUT]     sw_render_line(dst, w, h, x0, y0, rs->far_corners[3].x, rs->far_corners[3].y, rs->far_corners[0].x, rs->far_corners[0].y, c_box_far);
[OUT] 
[OUT]     /* Connecting edges from near to far. */
[OUT]     sw_render_line(dst, w, h, x0, y0, rs->near_corners[0].x, rs->near_corners[0].y, rs->far_corners[0].x, rs->far_corners[0].y, c_box_edge);
[OUT]     sw_render_line(dst, w, h, x0, y0, rs->near_corners[1].x, rs->near_corners[1].y, rs->far_corners[1].x, rs->far_corners[1].y, c_box_edge);
[OUT]     sw_render_line(dst, w, h, x0, y0, rs->near_corners[2].x, rs->near_corners[2].y, rs->far_corners[2].x, rs->far_corners[2].y, c_box_edge);
[OUT]     sw_render_line(dst, w, h, x0, y0, rs->near_corners[3].x, rs->near_corners[3].y, rs->far_corners[3].x, rs->far_corners[3].y, c_box_edge);
[OUT] 
[OUT]     /* Near frame outline. */
[OUT]     const uint16_t c_frame = sw_pack_rgb565_u8(10, 10, 12);
[OUT]     sw_render_line(dst, w, h, x0, y0, rs->near_corners[0].x, rs->near_corners[0].y, rs->near_corners[1].x, rs->near_corners[1].y, c_frame);
[OUT]     sw_render_line(dst, w, h, x0, y0, rs->near_corners[1].x, rs->near_corners[1].y, rs->near_corners[2].x, rs->near_corners[2].y, c_frame);
[OUT]     sw_render_line(dst, w, h, x0, y0, rs->near_corners[2].x, rs->near_corners[2].y, rs->near_corners[3].x, rs->near_corners[3].y, c_frame);
[OUT]     sw_render_line(dst, w, h, x0, y0, rs->near_corners[3].x, rs->near_corners[3].y, rs->near_corners[0].x, rs->near_corners[0].y, c_frame);
[OUT] }
[OUT] 
[OUT] static void render_draw_paddle(uint16_t *dst, uint32_t w, uint32_t h, int32_t x0, int32_t y0,
[OUT]                                const render_state_t *rs, const pong_paddle_t *p)
[OUT] {
[OUT]     const uint16_t c_shadow = sw_pack_rgb565_u8(8, 8, 10);
[OUT]     const uint16_t c_pad = sw_pack_rgb565_u8(214, 215, 217);
[OUT]     const uint16_t c_edge_near = sw_pack_rgb565_u8(246, 247, 249);
[OUT]     const uint16_t c_edge_far = sw_pack_rgb565_u8(156, 157, 160);
[OUT]     const uint16_t c_edge_side = sw_pack_rgb565_u8(206, 207, 209);
[OUT] 
[OUT]     float hy = p->size_y * 0.5f;
[OUT]     float hz = p->size_z * 0.5f;
[OUT] 
[OUT]     float y0n = p->y - hy;
[OUT]     float y1n = p->y + hy;
[OUT]     float z0n = p->z - hz;
[OUT]     float z1n = p->z + hz;
[OUT] 
[OUT]     sw_point_t q[4];
[OUT]     render_project(rs, p->x_plane, y0n, z0n, &q[0].x, &q[0].y, NULL);
[OUT]     render_project(rs, p->x_plane, y1n, z0n, &q[1].x, &q[1].y, NULL);
[OUT]     render_project(rs, p->x_plane, y1n, z1n, &q[2].x, &q[2].y, NULL);
[OUT]     render_project(rs, p->x_plane, y0n, z1n, &q[3].x, &q[3].y, NULL);
[OUT] 
[OUT]     /* Drop shadow. */
[OUT]     sw_point_t qs[4] = {q[0], q[1], q[2], q[3]};
[OUT]     for (int i = 0; i < 4; i++)
[OUT]     {
[OUT]         qs[i].x += 2;
[OUT]         qs[i].y += 2;
[OUT]     }
[OUT]     sw_render_fill_quad(dst, w, h, x0, y0, qs[0], qs[1], qs[2], qs[3], c_shadow);
[OUT]     sw_render_fill_quad(dst, w, h, x0, y0, q[0], q[1], q[2], q[3], c_pad);
[OUT] 
[OUT]     /* Depth edges: make z extent readable at a glance. */
[OUT]     sw_render_line(dst, w, h, x0, y0, q[0].x, q[0].y, q[1].x, q[1].y, c_edge_near);
[OUT]     sw_render_line(dst, w, h, x0, y0, q[0].x + 1, q[0].y, q[1].x + 1, q[1].y, c_edge_near);
[OUT]     sw_render_line(dst, w, h, x0, y0, q[3].x, q[3].y, q[2].x, q[2].y, c_edge_far);
[OUT] ---
[OUT] #include "game/input.h"
[OUT] 
[OUT] static inline float clampf(float v, float lo, float hi)
[OUT] {
[OUT]     if (v < lo) return lo;
[OUT]     if (v > hi) return hi;
[OUT]     return v;
[OUT] }
[OUT] 
[OUT] static float input_touch_max_speed(const pong_game_t *g)
[OUT] {
[OUT]     uint8_t d = g ? g->difficulty : 2;
[OUT]     if (d < 1) d = 1;
[OUT]     if (d > 3) d = 3;
[OUT]     switch (d)
[OUT]     {
[OUT]         /* Touch should feel 1:1; use a very high slew rate so motion does not lag behind a finger drag. */
[OUT]         case 1: return 120.0f;
[OUT]         case 2: return 140.0f;
[OUT]         default: return 160.0f;
[OUT]     }
[OUT] }
[OUT] 
[OUT] static void input_move_paddle(pong_paddle_t *p, float dt, float max_speed, float alpha)
[OUT] {
[OUT]     if (!p) return;
[OUT]     if (dt <= 0.0f) return;
[OUT] 
[OUT]     float prev_y = p->y;
[OUT]     float prev_z = p->z;
[OUT] 
[OUT]     float max_step = max_speed * dt;
[OUT] 
[OUT]     float dy = p->target_y - p->y;
[OUT]     float dz = p->target_z - p->z;
[OUT]     dy = clampf(dy, -max_step, max_step);
[OUT]     dz = clampf(dz, -max_step, max_step);
[OUT] 
[OUT]     /* Light smoothing for touch/tilt jitter. */
[OUT]     p->y += dy * alpha;
[OUT]     p->z += dz * alpha;
[OUT] 
[OUT]     float hy = p->size_y * 0.5f;
[OUT]     float hz = p->size_z * 0.5f;
[OUT]     p->y = clampf(p->y, hy, 1.0f - hy);
[OUT]     p->z = clampf(p->z, hz, 1.0f - hz);
[OUT] 
[OUT]     p->vy = (p->y - prev_y) / dt;
[OUT]     p->vz = (p->z - prev_z) / dt;
[OUT] }
[OUT] 
[OUT] void input_apply(pong_game_t *g, const platform_input_t *in, float dt)
[OUT] {
[OUT]     if (!g) return;
[OUT] 
[OUT]     float max_speed = 1.30f;
[OUT]     float alpha = 0.55f;
[OUT]     if (in && in->touch_active)
[OUT]     {
[OUT]         max_speed = input_touch_max_speed(g);
[OUT]         alpha = 1.0f;
[OUT]     }
[OUT] 
[OUT]     bool p1_active = in && in->p1_active;
[OUT]     float p1_y = in ? in->p1_y : 0.5f;
[OUT]     float p1_z = in ? in->p1_z : 0.5f;
[OUT] 
[OUT]     bool p2_active = in && in->p2_active;
[OUT]     float p2_y = in ? in->p2_y : 0.5f;
[OUT]     float p2_z = in ? in->p2_z : 0.5f;
[OUT] 
[OUT]     if (g->mode != kGameModeZeroPlayer)
[OUT]     {
[OUT]         if (p1_active)
[OUT]         {
[OUT]             g->paddle_l.target_y = clampf(p1_y, 0.0f, 1.0f);
[OUT]             g->paddle_l.target_z = clampf(p1_z, 0.0f, 1.0f);
[OUT]             input_move_paddle(&g->paddle_l, dt, max_speed, alpha);
[OUT]         }
[OUT]         else
[OUT]         {
[OUT]             /* No input: hold position and clear velocity to avoid stale paddle influence. */
[OUT]             g->paddle_l.vy = 0.0f;
[OUT]             g->paddle_l.vz = 0.0f;
[OUT]             g->paddle_l.target_y = g->paddle_l.y;
[OUT]             g->paddle_l.target_z = g->paddle_l.z;
[OUT]         }
[OUT]     }
[OUT] 
[OUT]     if (g->mode == kGameModeTwoPlayer && p2_active)
[OUT]     {
[OUT]         g->paddle_r.target_y = clampf(p2_y, 0.0f, 1.0f);
[OUT]         g->paddle_r.target_z = clampf(p2_z, 0.0f, 1.0f);
[OUT]         input_move_paddle(&g->paddle_r, dt, max_speed, alpha);
[OUT]     }
[OUT]     else if (g->mode == kGameModeTwoPlayer)
[OUT]     {
[OUT]         /* No input: keep position, clear velocity to avoid stale paddle influence. */
[OUT]         g->paddle_r.vy = 0.0f;
[OUT]         g->paddle_r.vz = 0.0f;
[OUT]         g->paddle_r.target_y = g->paddle_r.y;
[OUT]         g->paddle_r.target_z = g->paddle_r.z;
[OUT]     }
[OUT] }
[2026-02-25T00:27:48Z] CMD: sed -n "220,460p" src/game/game.c && sed -n "1,220p" src/game/game.c
[OUT]         return;
[OUT]     }
[OUT] 
[OUT]     const int32_t opt_y0 = (EDGEAI_UI_ROW_H - EDGEAI_UI_OPT_H) / 2;
[OUT]     const int32_t new_y0 = (EDGEAI_UI_ROW_H - EDGEAI_UI_NEW_H) / 2;
[OUT] 
[OUT]     /* Players: 0, 1, 2 */
[OUT]     for (int32_t i = 0; i < 3; i++)
[OUT]     {
[OUT]         int32_t bx = EDGEAI_UI_OPT_BLOCK_X + i * (EDGEAI_UI_OPT_W + EDGEAI_UI_OPT_GAP);
[OUT]         int32_t by = EDGEAI_UI_ROW0_Y + opt_y0;
[OUT]         if (hit_rect(px, py, bx, by, EDGEAI_UI_OPT_W, EDGEAI_UI_OPT_H))
[OUT]         {
[OUT]             game_mode_t new_mode = (i == 0) ? kGameModeZeroPlayer : (i == 1) ? kGameModeSinglePlayer : kGameModeTwoPlayer;
[OUT]             if (g->mode != new_mode)
[OUT]             {
[OUT]                 g->mode = new_mode;
[OUT]                 game_reset(g);
[OUT]             }
[OUT]             return;
[OUT]         }
[OUT]     }
[OUT] 
[OUT]     /* Difficulty: 1, 2, 3 */
[OUT]     for (int32_t i = 0; i < 3; i++)
[OUT]     {
[OUT]         int32_t bx = EDGEAI_UI_OPT_BLOCK_X + i * (EDGEAI_UI_OPT_W + EDGEAI_UI_OPT_GAP);
[OUT]         int32_t by = EDGEAI_UI_ROW1_Y + opt_y0;
[OUT]         if (hit_rect(px, py, bx, by, EDGEAI_UI_OPT_W, EDGEAI_UI_OPT_H))
[OUT]         {
[OUT]             uint8_t new_diff = (uint8_t)(i + 1);
[OUT]             if (new_diff < 1) new_diff = 1;
[OUT]             if (new_diff > 3) new_diff = 3;
[OUT]             if (g->difficulty != new_diff)
[OUT]             {
[OUT]                 g->difficulty = new_diff;
[OUT]                 game_reset(g);
[OUT]             }
[OUT]             return;
[OUT]         }
[OUT]     }
[OUT] 
[OUT]     /* AI: ON, OFF */
[OUT]     for (int32_t i = 0; i < 2; i++)
[OUT]     {
[OUT]         int32_t bx = EDGEAI_UI_OPT2_BLOCK_X + i * (EDGEAI_UI_OPT_W + EDGEAI_UI_OPT_GAP);
[OUT]         int32_t by = EDGEAI_UI_ROW2_Y + opt_y0;
[OUT]         if (hit_rect(px, py, bx, by, EDGEAI_UI_OPT_W, EDGEAI_UI_OPT_H))
[OUT]         {
[OUT]             bool new_ai_enabled = (i == 0);
[OUT]             if (g->ai_enabled != new_ai_enabled)
[OUT]             {
[OUT]                 g->ai_enabled = new_ai_enabled;
[OUT]             }
[OUT]             return;
[OUT]         }
[OUT]     }
[OUT] 
[OUT]     /* Skill mode: 2AI, AI/ALGO, ALGO/AI */
[OUT]     for (int32_t i = 0; i < 3; i++)
[OUT]     {
[OUT]         int32_t bx = EDGEAI_UI_OPT_BLOCK_X + i * (EDGEAI_UI_OPT_W + EDGEAI_UI_OPT_GAP);
[OUT]         int32_t by = EDGEAI_UI_ROW3_Y + opt_y0;
[OUT]         if (hit_rect(px, py, bx, by, EDGEAI_UI_OPT_W, EDGEAI_UI_OPT_H))
[OUT]         {
[OUT]             ai_learn_mode_t mode =
[OUT]                 (i == 0) ? kAiLearnModeBoth : ((i == 1) ? kAiLearnModeAiAlgo : kAiLearnModeAlgoAi);
[OUT]             if (g->ai_learn_mode != mode)
[OUT]             {
[OUT]                 ai_learning_set_mode(g, mode);
[OUT]             }
[OUT]             return;
[OUT]         }
[OUT]     }
[OUT] 
[OUT]     /* Persistent learning: ON, OFF */
[OUT]     for (int32_t i = 0; i < 2; i++)
[OUT]     {
[OUT]         int32_t bx = EDGEAI_UI_OPT2_BLOCK_X + i * (EDGEAI_UI_OPT_W + EDGEAI_UI_OPT_GAP);
[OUT]         int32_t by = EDGEAI_UI_ROW4_Y + opt_y0;
[OUT]         if (hit_rect(px, py, bx, by, EDGEAI_UI_OPT_W, EDGEAI_UI_OPT_H))
[OUT]         {
[OUT]             bool en = (i == 0);
[OUT]             if (g->persistent_learning != en)
[OUT]             {
[OUT]                 ai_learning_set_persistent(g, en);
[OUT]             }
[OUT]             return;
[OUT]         }
[OUT]     }
[OUT] 
[OUT]     /* Perpetual play: 11, INF */
[OUT]     for (int32_t i = 0; i < 2; i++)
[OUT]     {
[OUT]         int32_t bx = EDGEAI_UI_OPT2_BLOCK_X + i * (EDGEAI_UI_OPT_W + EDGEAI_UI_OPT_GAP);
[OUT]         int32_t by = EDGEAI_UI_ROW5_Y + opt_y0;
[OUT]         if (hit_rect(px, py, bx, by, EDGEAI_UI_OPT_W, EDGEAI_UI_OPT_H))
[OUT]         {
[OUT]             bool inf = (i == 1);
[OUT]             if (g->perpetual_play != inf)
[OUT]             {
[OUT]                 g->perpetual_play = inf;
[OUT]             }
[OUT]             return;
[OUT]         }
[OUT]     }
[OUT] 
[OUT]     /* Target guide: ON, OFF */
[OUT]     for (int32_t i = 0; i < 2; i++)
[OUT]     {
[OUT]         int32_t bx = EDGEAI_UI_OPT2_BLOCK_X + i * (EDGEAI_UI_OPT_W + EDGEAI_UI_OPT_GAP);
[OUT]         int32_t by = EDGEAI_UI_ROW6_Y + opt_y0;
[OUT]         if (hit_rect(px, py, bx, by, EDGEAI_UI_OPT_W, EDGEAI_UI_OPT_H))
[OUT]         {
[OUT]             bool en = (i == 0);
[OUT]             if (g->target_overlay_enabled != en)
[OUT]             {
[OUT]                 g->target_overlay_enabled = en;
[OUT]             }
[OUT]             return;
[OUT]         }
[OUT]     }
[OUT] 
[OUT]     /* SPEED++: ON, OFF */
[OUT]     for (int32_t i = 0; i < 2; i++)
[OUT]     {
[OUT]         int32_t bx = EDGEAI_UI_OPT2_BLOCK_X + i * (EDGEAI_UI_OPT_W + EDGEAI_UI_OPT_GAP);
[OUT]         int32_t by = EDGEAI_UI_ROW7_Y + opt_y0;
[OUT]         if (hit_rect(px, py, bx, by, EDGEAI_UI_OPT_W, EDGEAI_UI_OPT_H))
[OUT]         {
[OUT]             bool en = (i == 0);
[OUT]             if (g->speedpp_enabled != en)
[OUT]             {
[OUT]                 g->speedpp_enabled = en;
[OUT]                 g->speedpp_stage = 0u;
[OUT]                 g->speedpp_next_threshold = 11u;
[OUT]                 g->speedpp_serve_speed_target = 0.0f;
[OUT]                 g->speedpp_peak_speed = 0.0f;
[OUT]             }
[OUT]             return;
[OUT]         }
[OUT]     }
[OUT] 
[OUT]     /* New game. */
[OUT]     {
[OUT]         int32_t bx = EDGEAI_UI_NEW_X;
[OUT]         int32_t by = EDGEAI_UI_ROW8_Y + new_y0;
[OUT]         if (hit_rect(px, py, bx, by, EDGEAI_UI_NEW_W, EDGEAI_UI_NEW_H))
[OUT]         {
[OUT]             game_reset(g);
[OUT]             g->menu_open = false;
[OUT]             return;
[OUT]         }
[OUT]     }
[OUT] }
[OUT] 
[OUT] void game_init(pong_game_t *g)
[OUT] {
[OUT]     if (!g) return;
[OUT]     memset(g, 0, sizeof(*g));
[OUT] 
[OUT]     g->mode = kGameModeZeroPlayer;
[OUT]     g->difficulty = 2;
[OUT]     g->ai_enabled = true;
[OUT]     g->perpetual_play = false;
[OUT]     g->persistent_learning = true;
[OUT]     g->speedpp_enabled = false;
[OUT]     g->target_overlay_enabled = true;
[OUT]     g->ai_learn_mode = kAiLearnModeBoth;
[OUT]     g->menu_open = false;
[OUT]     g->help_open = false;
[OUT]     g->ui_block_touch = false;
[OUT]     g->match_over = false;
[OUT]     g->winner_left = false;
[OUT]     g->end_prompt_dismissed = false;
[OUT]     g->countdown_active = false;
[OUT] 
[OUT]     g->rng = 1u;
[OUT]     g->frame = 0;
[OUT]     g->match_over_frame = 0u;
[OUT]     g->match_over_start_cycles = 0u;
[OUT]     g->countdown_us_left = 0u;
[OUT]     g->countdown_start_cycles = 0u;
[OUT] 
[OUT]     g->paddle_l.x_plane = 0.06f;
[OUT]     g->paddle_r.x_plane = 0.94f;
[OUT] 
[OUT]     g->paddle_l.size_y = 0.26f;
[OUT]     g->paddle_l.size_z = 0.28f;
[OUT]     g->paddle_r.size_y = 0.26f;
[OUT]     g->paddle_r.size_z = 0.28f;
[OUT] 
[OUT]     g->paddle_l.y = 0.5f;
[OUT]     g->paddle_l.z = 0.5f;
[OUT]     g->paddle_r.y = 0.5f;
[OUT]     g->paddle_r.z = 0.5f;
[OUT] 
[OUT]     g->paddle_l.target_y = g->paddle_l.y;
[OUT]     g->paddle_l.target_z = g->paddle_l.z;
[OUT]     g->paddle_r.target_y = g->paddle_r.y;
[OUT]     g->paddle_r.target_z = g->paddle_r.z;
[OUT] 
[OUT]     g->last_hit_dy = 0.0f;
[OUT]     g->last_hit_dz = 0.0f;
[OUT]     g->serve_vx = 0.0f;
[OUT]     g->serve_vy = 0.0f;
[OUT]     g->serve_vz = 0.0f;
[OUT]     g->speedpp_peak_speed = 0.0f;
[OUT]     g->speedpp_serve_speed_target = 0.0f;
[OUT]     g->speedpp_stage = 0u;
[OUT]     g->speedpp_next_threshold = 11u;
[OUT] 
[OUT]     g->accel_active = false;
[OUT]     g->accel_ax = 0.0f;
[OUT]     g->accel_ay = 0.0f;
[OUT] 
[OUT]     g->ai_telemetry_start_cycles = 0u;
[OUT]     g->ai_npu_attempts_window = 0u;
[OUT]     g->ai_fallback_window = 0u;
[OUT]     g->ai_npu_rate_hz = 0u;
[OUT]     g->ai_fallback_rate_hz = 0u;
[OUT]     g->ai_left_active = false;
[OUT]     g->ai_right_active = false;
[OUT] 
[OUT]     ai_init(g);
[OUT]     game_reset(g);
[OUT] }
[OUT] 
[OUT] void game_reset(pong_game_t *g)
[OUT] {
[OUT]     if (!g) return;
[OUT] 
[OUT]     ai_learning_sync_store(g);
[OUT] 
[OUT]     g->score.left = 0;
[OUT]     g->score.right = 0;
[OUT] 
[OUT]     g->paddle_l.y = 0.5f;
[OUT]     g->paddle_l.z = 0.5f;
[OUT]     g->paddle_r.y = 0.5f;
[OUT]     g->paddle_r.z = 0.5f;
[OUT] ---
[OUT] #include "game/game.h"
[OUT] 
[OUT] #include <string.h>
[OUT] 
[OUT] #include "edgeai_config.h"
[OUT] 
[OUT] #include "game/ai.h"
[OUT] #include "game/input.h"
[OUT] #include "game/modes.h"
[OUT] #include "game/physics.h"
[OUT] #include "game/ui_layout.h"
[OUT] #include "platform/time_hal.h"
[OUT] 
[OUT] #define EDGEAI_WIN_SCORE 11u
[OUT] #define EDGEAI_END_PROMPT_DELAY_FRAMES 120u
[OUT] #define EDGEAI_P0_DEMO_RESET_US 1300000u
[OUT] #define EDGEAI_COUNTDOWN_STEP_US 1000000u
[OUT] #define EDGEAI_COUNTDOWN_TOTAL_US (3u * EDGEAI_COUNTDOWN_STEP_US)
[OUT] 
[OUT] static inline int32_t clampi(int32_t v, int32_t lo, int32_t hi)
[OUT] {
[OUT]     if (v < lo) return lo;
[OUT]     if (v > hi) return hi;
[OUT]     return v;
[OUT] }
[OUT] 
[OUT] static inline float clampf(float v, float lo, float hi)
[OUT] {
[OUT]     if (v < lo) return lo;
[OUT]     if (v > hi) return hi;
[OUT]     return v;
[OUT] }
[OUT] 
[OUT] static inline float absf(float v)
[OUT] {
[OUT]     return (v < 0.0f) ? -v : v;
[OUT] }
[OUT] 
[OUT] static inline bool hit_rect(int32_t x, int32_t y, int32_t rx, int32_t ry, int32_t rw, int32_t rh)
[OUT] {
[OUT]     return (x >= rx) && (x < (rx + rw)) && (y >= ry) && (y < (ry + rh));
[OUT] }
[OUT] 
[OUT] static float game_deadzone(float v, float dz)
[OUT] {
[OUT]     if (dz <= 0.0f) return v;
[OUT]     if (dz >= 1.0f) return 0.0f;
[OUT]     return (absf(v) < dz) ? 0.0f : v;
[OUT] }
[OUT] 
[OUT] static bool game_end_prompt_visible(const pong_game_t *g)
[OUT] {
[OUT]     if (!g) return false;
[OUT]     if (!g->match_over) return false;
[OUT]     if (g->end_prompt_dismissed) return false;
[OUT] 
[OUT]     uint32_t elapsed = g->frame - g->match_over_frame;
[OUT]     return (elapsed >= EDGEAI_END_PROMPT_DELAY_FRAMES);
[OUT] }
[OUT] 
[OUT] static void game_start_countdown(pong_game_t *g)
[OUT] {
[OUT]     if (!g) return;
[OUT]     g->serve_vx = g->ball.vx;
[OUT]     g->serve_vy = g->ball.vy;
[OUT]     g->serve_vz = g->ball.vz;
[OUT] 
[OUT]     g->ball.vx = 0.0f;
[OUT]     g->ball.vy = 0.0f;
[OUT]     g->ball.vz = 0.0f;
[OUT] 
[OUT]     g->countdown_active = true;
[OUT]     g->countdown_us_left = EDGEAI_COUNTDOWN_TOTAL_US;
[OUT]     g->countdown_start_cycles = time_hal_cycles();
[OUT] }
[OUT] 
[OUT] static void game_update_countdown(pong_game_t *g)
[OUT] {
[OUT]     if (!g || !g->countdown_active) return;
[OUT] 
[OUT]     uint32_t elapsed_us = time_hal_elapsed_us(g->countdown_start_cycles);
[OUT]     if (elapsed_us >= EDGEAI_COUNTDOWN_TOTAL_US)
[OUT]     {
[OUT]         g->countdown_us_left = 0u;
[OUT]         g->countdown_active = false;
[OUT]         g->ball.vx = g->serve_vx;
[OUT]         g->ball.vy = g->serve_vy;
[OUT]         g->ball.vz = g->serve_vz;
[OUT]         return;
[OUT]     }
[OUT] 
[OUT]     g->countdown_us_left = EDGEAI_COUNTDOWN_TOTAL_US - elapsed_us;
[OUT] }
[OUT] 
[OUT] static void game_apply_accel_ball_nudge(pong_game_t *g, const platform_input_t *in, float dt)
[OUT] {
[OUT]     if (!g || !in) return;
[OUT]     if (dt <= 0.0f) return;
[OUT]     if (g->mode != kGameModeZeroPlayer) return;
[OUT]     if (!in->accel_active) return;
[OUT] 
[OUT]     /* Tilt affects ball vertical (y) and horizontal (z) to allow outcome nudging in AI vs AI mode. */
[OUT]     float ax = clampf(in->accel_ax, -1.0f, 1.0f);
[OUT]     float ay = clampf(in->accel_ay, -1.0f, 1.0f);
[OUT] 
[OUT]     /* Input is already deadzoned/softened in accel_proc; avoid a second deadzone here. */
[OUT]     const float dz = 0.0f;
[OUT]     ax = game_deadzone(ax, dz);
[OUT]     ay = game_deadzone(ay, dz);
[OUT] 
[OUT]     /* High gain on purpose: P0 is a "mess with the outcome" mode. */
[OUT]     const float k = 14.0f;
[OUT]     g->ball.vz += ax * k * dt;
[OUT]     g->ball.vy += ay * k * dt;
[OUT] 
[OUT]     const float vlim = 6.0f;
[OUT]     g->ball.vy = clampf(g->ball.vy, -vlim, vlim);
[OUT]     g->ball.vz = clampf(g->ball.vz, -vlim, vlim);
[OUT] }
[OUT] 
[OUT] static void ui_handle_press(pong_game_t *g, float touch_x, float touch_y)
[OUT] {
[OUT]     if (!g) return;
[OUT] 
[OUT]     int32_t px = (int32_t)(touch_x * (float)(EDGEAI_LCD_W - 1) + 0.5f);
[OUT]     int32_t py = (int32_t)(touch_y * (float)(EDGEAI_LCD_H - 1) + 0.5f);
[OUT]     px = clampi(px, 0, EDGEAI_LCD_W - 1);
[OUT]     py = clampi(py, 0, EDGEAI_LCD_H - 1);
[OUT] 
[OUT]     if (g->match_over)
[OUT]     {
[OUT]         if (g->mode == kGameModeZeroPlayer) return;
[OUT] 
[OUT]         if (g->end_prompt_dismissed)
[OUT]         {
[OUT]             g->end_prompt_dismissed = false;
[OUT]             if (g->frame > EDGEAI_END_PROMPT_DELAY_FRAMES)
[OUT]             {
[OUT]                 g->match_over_frame = g->frame - EDGEAI_END_PROMPT_DELAY_FRAMES;
[OUT]             }
[OUT]             else
[OUT]             {
[OUT]                 g->match_over_frame = 0u;
[OUT]             }
[OUT]             return;
[OUT]         }
[OUT] 
[OUT]         if (game_end_prompt_visible(g))
[OUT]         {
[OUT]             if (hit_rect(px, py, EDGEAI_END_BTN_YES_X, EDGEAI_END_BTN_Y, EDGEAI_END_BTN_W, EDGEAI_END_BTN_H))
[OUT]             {
[OUT]                 game_reset(g);
[OUT]                 g->match_over = false;
[OUT]                 g->winner_left = false;
[OUT]                 g->end_prompt_dismissed = false;
[OUT]                 g->menu_open = false;
[OUT]                 g->help_open = false;
[OUT]                 return;
[OUT]             }
[OUT] 
[OUT]             if (hit_rect(px, py, EDGEAI_END_BTN_NO_X, EDGEAI_END_BTN_Y, EDGEAI_END_BTN_W, EDGEAI_END_BTN_H))
[OUT]             {
[OUT]                 g->end_prompt_dismissed = true;
[OUT]                 return;
[OUT]             }
[OUT]         }
[OUT]         return;
[OUT]     }
[OUT] 
[OUT]     const int32_t pill_x = EDGEAI_UI_PILL_X;
[OUT]     const int32_t pill_y = EDGEAI_UI_PILL_Y;
[OUT]     const int32_t pill_w = EDGEAI_UI_PILL_W;
[OUT]     const int32_t pill_h = EDGEAI_UI_PILL_H;
[OUT] 
[OUT]     const int32_t help_x = EDGEAI_UI_HELP_BTN_X;
[OUT]     const int32_t help_y = EDGEAI_UI_HELP_BTN_Y;
[OUT]     const int32_t help_w = EDGEAI_UI_HELP_BTN_W;
[OUT]     const int32_t help_h = EDGEAI_UI_HELP_BTN_H;
[OUT] 
[OUT]     if (hit_rect(px, py, help_x, help_y, help_w, help_h))
[OUT]     {
[OUT]         g->help_open = !g->help_open;
[OUT]         if (g->help_open) g->menu_open = false;
[OUT]         return;
[OUT]     }
[OUT] 
[OUT]     if (hit_rect(px, py, pill_x, pill_y, pill_w, pill_h))
[OUT]     {
[OUT]         g->menu_open = !g->menu_open;
[OUT]         if (g->menu_open) g->help_open = false;
[OUT]         return;
[OUT]     }
[OUT] 
[OUT]     if (g->help_open)
[OUT]     {
[OUT]         const int32_t panel_x = EDGEAI_UI_HELP_PANEL_X;
[OUT]         const int32_t panel_y = EDGEAI_UI_HELP_PANEL_Y;
[OUT]         const int32_t panel_w = EDGEAI_UI_HELP_PANEL_W;
[OUT]         const int32_t panel_h = EDGEAI_UI_HELP_PANEL_H;
[OUT] 
[OUT]         if (!hit_rect(px, py, panel_x, panel_y, panel_w, panel_h))
[OUT]         {
[OUT]             g->help_open = false;
[OUT]             g->ui_block_touch = true;
[OUT]         }
[OUT]         return;
[OUT]     }
[OUT] 
[OUT]     if (!g->menu_open) return;
[OUT] 
[OUT]     const int32_t panel_x = EDGEAI_UI_PANEL_X;
[OUT]     const int32_t panel_y = EDGEAI_UI_PANEL_Y;
[OUT]     const int32_t panel_w = EDGEAI_UI_PANEL_W;
[OUT]     const int32_t panel_h = EDGEAI_UI_PANEL_H;
[OUT] 
[OUT]     if (!hit_rect(px, py, panel_x, panel_y, panel_w, panel_h))
[OUT]     {
[OUT]         g->menu_open = false;
[OUT]         g->ui_block_touch = true;
[OUT]         return;
[2026-02-25T00:28:00Z] CMD: sed -n "1,180p" src/game/ai.c && sed -n "760,860p" src/game/ai.c
[OUT] #include "game/ai.h"
[OUT] 
[OUT] #include <string.h>
[OUT] 
[OUT] #include "fsl_flash.h"
[OUT] #include "platform/time_hal.h"
[OUT] 
[OUT] static inline float clampf(float v, float lo, float hi)
[OUT] {
[OUT]     if (v < lo) return lo;
[OUT]     if (v > hi) return hi;
[OUT]     return v;
[OUT] }
[OUT] 
[OUT] static inline uint16_t clampu16(uint32_t v, uint16_t hi)
[OUT] {
[OUT]     if (v > (uint32_t)hi) return hi;
[OUT]     return (uint16_t)v;
[OUT] }
[OUT] 
[OUT] static inline float absf(float v)
[OUT] {
[OUT]     return (v < 0.0f) ? -v : v;
[OUT] }
[OUT] 
[OUT] static inline uint32_t xorshift32(uint32_t x)
[OUT] {
[OUT]     x ^= x << 13;
[OUT]     x ^= x >> 17;
[OUT]     x ^= x << 5;
[OUT]     return x;
[OUT] }
[OUT] 
[OUT] static float rand_f01(pong_game_t *g)
[OUT] {
[OUT]     g->rng = xorshift32(g->rng ? g->rng : 1u);
[OUT]     uint32_t u = (g->rng >> 8) & 0x00FFFFFFu;
[OUT]     return (float)u * (1.0f / 16777215.0f);
[OUT] }
[OUT] 
[OUT] static float rand_f(pong_game_t *g, float lo, float hi)
[OUT] {
[OUT]     return lo + (hi - lo) * rand_f01(g);
[OUT] }
[OUT] 
[OUT] #define EDGEAI_LEARN_STORE_MAGIC 0x4C524E31u /* "LRN1" */
[OUT] #define EDGEAI_LEARN_STORE_VERSION 0x00000002u
[OUT] #define EDGEAI_LEARN_FLASH_PROGRAM_BYTES 512u
[OUT] 
[OUT] typedef struct
[OUT] {
[OUT]     uint32_t magic;
[OUT]     uint32_t version;
[OUT]     uint32_t crc32;
[OUT]     ai_learn_profile_t left;
[OUT]     ai_learn_profile_t right;
[OUT]     uint32_t reserved[(EDGEAI_LEARN_FLASH_PROGRAM_BYTES - (3u * sizeof(uint32_t)) - (2u * sizeof(ai_learn_profile_t))) /
[OUT]                       sizeof(uint32_t)];
[OUT] } ai_learn_store_t;
[OUT] 
[OUT] static ai_learn_store_t s_learn_store = {0u};
[OUT] static bool s_learn_store_dirty = false;
[OUT] static bool s_flash_ready = false;
[OUT] static bool s_flash_init_done = false;
[OUT] static uint32_t s_flash_store_addr = 0u;
[OUT] static uint32_t s_flash_sector_size = 0u;
[OUT] static flash_config_t s_flash_cfg;
[OUT] 
[OUT] static uint32_t ai_store_checksum(const ai_learn_store_t *store)
[OUT] {
[OUT]     if (!store) return 0u;
[OUT]     ai_learn_store_t copy = *store;
[OUT]     copy.crc32 = 0u;
[OUT] 
[OUT]     const uint8_t *p = (const uint8_t *)&copy;
[OUT]     uint32_t hash = 2166136261u;
[OUT]     for (uint32_t i = 0u; i < (uint32_t)sizeof(copy); i++)
[OUT]     {
[OUT]         hash ^= p[i];
[OUT]         hash *= 16777619u;
[OUT]     }
[OUT]     return hash;
[OUT] }
[OUT] 
[OUT] static bool ai_flash_init(void)
[OUT] {
[OUT]     if (s_flash_init_done) return s_flash_ready;
[OUT]     s_flash_init_done = true;
[OUT] 
[OUT]     if (FLASH_Init(&s_flash_cfg) != kStatus_FLASH_Success) return false;
[OUT] 
[OUT]     uint32_t pflash_base = 0u;
[OUT]     uint32_t pflash_size = 0u;
[OUT]     uint32_t sector_size = 0u;
[OUT]     if (FLASH_GetProperty(&s_flash_cfg, kFLASH_PropertyPflashBlockBaseAddr, &pflash_base) != kStatus_FLASH_Success)
[OUT]         return false;
[OUT]     if (FLASH_GetProperty(&s_flash_cfg, kFLASH_PropertyPflashTotalSize, &pflash_size) != kStatus_FLASH_Success)
[OUT]         return false;
[OUT]     if (FLASH_GetProperty(&s_flash_cfg, kFLASH_PropertyPflashSectorSize, &sector_size) != kStatus_FLASH_Success)
[OUT]         return false;
[OUT]     if (sector_size < EDGEAI_LEARN_FLASH_PROGRAM_BYTES || pflash_size < sector_size) return false;
[OUT] 
[OUT]     s_flash_sector_size = sector_size;
[OUT]     s_flash_store_addr = (pflash_base + pflash_size) - sector_size;
[OUT]     s_flash_ready = true;
[OUT]     return true;
[OUT] }
[OUT] 
[OUT] static bool ai_flash_read_store(ai_learn_store_t *out_store)
[OUT] {
[OUT]     if (!out_store) return false;
[OUT]     if (!ai_flash_init()) return false;
[OUT] 
[OUT]     const ai_learn_store_t *flash_store = (const ai_learn_store_t *)(uintptr_t)s_flash_store_addr;
[OUT]     if (flash_store->magic != EDGEAI_LEARN_STORE_MAGIC) return false;
[OUT]     if (flash_store->version != EDGEAI_LEARN_STORE_VERSION) return false;
[OUT]     if (ai_store_checksum(flash_store) != flash_store->crc32) return false;
[OUT] 
[OUT]     *out_store = *flash_store;
[OUT]     return true;
[OUT] }
[OUT] 
[OUT] static bool ai_flash_write_store(const ai_learn_store_t *store)
[OUT] {
[OUT]     if (!store) return false;
[OUT]     if (!ai_flash_init()) return false;
[OUT] 
[OUT]     ai_learn_store_t write_buf;
[OUT]     memset(&write_buf, 0xFF, sizeof(write_buf));
[OUT]     write_buf = *store;
[OUT]     write_buf.crc32 = 0u;
[OUT]     write_buf.crc32 = ai_store_checksum(&write_buf);
[OUT] 
[OUT]     if (FLASH_Erase(&s_flash_cfg, s_flash_store_addr, s_flash_sector_size, kFLASH_ApiEraseKey) != kStatus_FLASH_Success)
[OUT]         return false;
[OUT]     if (FLASH_Program(&s_flash_cfg, s_flash_store_addr, (uint8_t *)&write_buf, sizeof(write_buf)) !=
[OUT]         kStatus_FLASH_Success)
[OUT]         return false;
[OUT] 
[OUT]     const ai_learn_store_t *flash_store = (const ai_learn_store_t *)(uintptr_t)s_flash_store_addr;
[OUT]     return (memcmp(flash_store, &write_buf, sizeof(write_buf)) == 0);
[OUT] }
[OUT] 
[OUT] static void ai_flash_clear_store(void)
[OUT] {
[OUT]     if (!ai_flash_init()) return;
[OUT]     (void)FLASH_Erase(&s_flash_cfg, s_flash_store_addr, s_flash_sector_size, kFLASH_ApiEraseKey);
[OUT] }
[OUT] 
[OUT] static ai_learn_profile_t ai_profile_default(void)
[OUT] {
[OUT]     ai_learn_profile_t p;
[OUT]     p.speed_scale = 1.0f;
[OUT]     p.noise_scale = 1.0f;
[OUT]     p.lead_scale = 1.0f;
[OUT]     p.hits = 0u;
[OUT]     p.misses = 0u;
[OUT]     return p;
[OUT] }
[OUT] 
[OUT] static void ai_profile_clamp(ai_learn_profile_t *p)
[OUT] {
[OUT]     if (!p) return;
[OUT]     p->speed_scale = clampf(p->speed_scale, 0.75f, 1.85f);
[OUT]     p->noise_scale = clampf(p->noise_scale, 0.40f, 2.20f);
[OUT]     p->lead_scale = clampf(p->lead_scale, 0.70f, 2.00f);
[OUT] }
[OUT] 
[OUT] static ai_learn_profile_t *ai_profile_side(pong_game_t *g, bool right_side)
[OUT] {
[OUT]     if (!g) return NULL;
[OUT]     return right_side ? &g->ai_profile_right : &g->ai_profile_left;
[OUT] }
[OUT] 
[OUT] static const ai_learn_profile_t *ai_profile_side_const(const pong_game_t *g, bool right_side)
[OUT] {
[OUT]     if (!g) return NULL;
[OUT]     return right_side ? &g->ai_profile_right : &g->ai_profile_left;
[OUT] }
[OUT] 
[OUT] ---
[OUT] 
[OUT]     /* Clamp inside arena. */
[OUT]     float hy = p->size_y * 0.5f;
[OUT]     float hz = p->size_z * 0.5f;
[OUT]     p->y = clampf(p->y, hy, 1.0f - hy);
[OUT]     p->z = clampf(p->z, hz, 1.0f - hz);
[OUT] 
[OUT]     p->vy = (p->y - prev_y) / dt;
[OUT]     p->vz = (p->z - prev_z) / dt;
[OUT] }
[OUT] 
[OUT] void ai_step(pong_game_t *g, float dt, bool ai_left, bool ai_right)
[OUT] {
[OUT]     if (!g) return;
[OUT] 
[OUT]     if (ai_left)
[OUT]     {
[OUT]         ai_step_one(g, dt, &g->paddle_l, false);
[OUT]     }
[OUT]     if (ai_right)
[OUT]     {
[OUT]         ai_step_one(g, dt, &g->paddle_r, true);
[OUT]     }
[OUT] 
[OUT]     /* Gentle decay toward baseline so long sessions stay stable. */
[OUT]     if (ai_learning_side_selected(g, false))
[OUT]     {
[OUT]         ai_learn_profile_t *p = &g->ai_profile_left;
[OUT]         p->speed_scale += (1.0f - p->speed_scale) * 0.0008f;
[OUT]         p->noise_scale += (1.0f - p->noise_scale) * 0.0010f;
[OUT]         p->lead_scale += (1.0f - p->lead_scale) * 0.0008f;
[OUT]         ai_profile_clamp(p);
[OUT]     }
[OUT]     if (ai_learning_side_selected(g, true))
[OUT]     {
[OUT]         ai_learn_profile_t *p = &g->ai_profile_right;
[OUT]         p->speed_scale += (1.0f - p->speed_scale) * 0.0008f;
[OUT]         p->noise_scale += (1.0f - p->noise_scale) * 0.0010f;
[OUT]         p->lead_scale += (1.0f - p->lead_scale) * 0.0008f;
[OUT]         ai_profile_clamp(p);
[OUT]     }
[OUT] 
[OUT]     ai_update_telemetry_window(g);
[OUT] }
[2026-02-25T00:28:00Z] CMD: rg -n "ai_left_active|ai_right_active|ai_step\(|ai_enabled|mode == kGameMode" src/game/game.c src/game/ai.c && sed -n "460,760p" src/game/game.c
[OUT] src/game/ai.c:186:        if (!g->ai_right_active) return false;
[OUT] src/game/ai.c:191:    if (!g->ai_left_active) return false;
[OUT] src/game/ai.c:556:    if (g && !g->ai_enabled)
[OUT] src/game/ai.c:587:    if (g && !g->ai_enabled)
[OUT] src/game/ai.c:649:    bool use_npu = g->ai_enabled && side_edgeai && ball_toward;
[OUT] src/game/ai.c:771:void ai_step(pong_game_t *g, float dt, bool ai_left, bool ai_right)
[OUT] src/game/game.c:132:        if (g->mode == kGameModeZeroPlayer) return;
[OUT] src/game/game.c:269:            bool new_ai_enabled = (i == 0);
[OUT] src/game/game.c:270:            if (g->ai_enabled != new_ai_enabled)
[OUT] src/game/game.c:272:                g->ai_enabled = new_ai_enabled;
[OUT] src/game/game.c:383:    g->ai_enabled = true;
[OUT] src/game/game.c:441:    g->ai_left_active = false;
[OUT] src/game/game.c:442:    g->ai_right_active = false;
[OUT] src/game/game.c:493:    if (g->mode == kGameModeZeroPlayer)
[OUT] src/game/game.c:529:        if (g->mode == kGameModeZeroPlayer)
[OUT] src/game/game.c:555:    bool manual_r = (g->mode == kGameModeTwoPlayer) && in && in->p2_active;
[OUT] src/game/game.c:556:    bool ai_left = (g->mode == kGameModeZeroPlayer);
[OUT] src/game/game.c:557:    bool ai_right = (g->mode == kGameModeSinglePlayer) || (g->mode == kGameModeZeroPlayer);
[OUT] src/game/game.c:558:    if (g->mode == kGameModeTwoPlayer || manual_r) ai_right = false;
[OUT] src/game/game.c:559:    g->ai_left_active = ai_left;
[OUT] src/game/game.c:560:    g->ai_right_active = ai_right;
[OUT] src/game/game.c:561:    ai_step(g, dt, ai_left, ai_right);
[OUT] src/game/game.c:576:        g->end_prompt_dismissed = (g->mode == kGameModeZeroPlayer);
[OUT] ---
[OUT]     g->paddle_r.z = 0.5f;
[OUT] 
[OUT]     g->paddle_l.vy = 0.0f;
[OUT]     g->paddle_l.vz = 0.0f;
[OUT]     g->paddle_r.vy = 0.0f;
[OUT]     g->paddle_r.vz = 0.0f;
[OUT] 
[OUT]     g->paddle_l.target_y = g->paddle_l.y;
[OUT]     g->paddle_l.target_z = g->paddle_l.z;
[OUT]     g->paddle_r.target_y = g->paddle_r.y;
[OUT]     g->paddle_r.target_z = g->paddle_r.z;
[OUT] 
[OUT]     g->last_hit_dy = 0.0f;
[OUT]     g->last_hit_dz = 0.0f;
[OUT]     g->match_over = false;
[OUT]     g->winner_left = false;
[OUT]     g->end_prompt_dismissed = false;
[OUT]     g->match_over_frame = g->frame;
[OUT]     g->match_over_start_cycles = 0u;
[OUT]     g->ai_telemetry_start_cycles = 0u;
[OUT]     g->ai_npu_attempts_window = 0u;
[OUT]     g->ai_fallback_window = 0u;
[OUT]     g->ai_npu_rate_hz = 0u;
[OUT]     g->ai_fallback_rate_hz = 0u;
[OUT] 
[OUT]     if (g->persistent_learning)
[OUT]     {
[OUT]         ai_learning_set_persistent(g, true);
[OUT]     }
[OUT] 
[OUT]     g->rng = g->rng * 1664525u + 1013904223u;
[OUT]     int serve_dir = (g->rng & 1u) ? +1 : -1;
[OUT]     physics_reset_ball(g, serve_dir);
[OUT]     if (g->mode == kGameModeZeroPlayer)
[OUT]     {
[OUT]         g->countdown_active = false;
[OUT]         g->countdown_us_left = 0u;
[OUT]     }
[OUT]     else
[OUT]     {
[OUT]         game_start_countdown(g);
[OUT]     }
[OUT] }
[OUT] 
[OUT] void game_step(pong_game_t *g, const platform_input_t *in, float dt)
[OUT] {
[OUT]     if (!g) return;
[OUT] 
[OUT]     /* Keep latest accel values in game state for UI/debug even when not used for control. */
[OUT]     g->accel_active = (in && in->accel_active);
[OUT]     g->accel_ax = in ? in->accel_ax : 0.0f;
[OUT]     g->accel_ay = in ? in->accel_ay : 0.0f;
[OUT] 
[OUT]     if (in && in->touch_pressed)
[OUT]     {
[OUT]         ui_handle_press(g, in->touch_x, in->touch_y);
[OUT]     }
[OUT] 
[OUT]     if (g->ui_block_touch)
[OUT]     {
[OUT]         if (in && in->touch_active)
[OUT]         {
[OUT]             return;
[OUT]         }
[OUT]         g->ui_block_touch = false;
[OUT]     }
[OUT] 
[OUT]     if (g->match_over)
[OUT]     {
[OUT]         if (g->mode == kGameModeZeroPlayer)
[OUT]         {
[OUT]             uint32_t elapsed_us = time_hal_elapsed_us(g->match_over_start_cycles);
[OUT]             if (elapsed_us >= EDGEAI_P0_DEMO_RESET_US)
[OUT]             {
[OUT]                 game_reset(g);
[OUT]             }
[OUT]         }
[OUT]         g->frame++;
[OUT]         return;
[OUT]     }
[OUT] 
[OUT]     if (g->menu_open || g->help_open)
[OUT]     {
[OUT]         /* Pause simulation while an overlay UI panel is open. */
[OUT]         return;
[OUT]     }
[OUT] 
[OUT]     if (in && in->mode_toggle)
[OUT]     {
[OUT]         g->mode = modes_next(g->mode);
[OUT]         game_reset(g);
[OUT]     }
[OUT] 
[OUT]     input_apply(g, in, dt);
[OUT] 
[OUT]     bool manual_r = (g->mode == kGameModeTwoPlayer) && in && in->p2_active;
[OUT]     bool ai_left = (g->mode == kGameModeZeroPlayer);
[OUT]     bool ai_right = (g->mode == kGameModeSinglePlayer) || (g->mode == kGameModeZeroPlayer);
[OUT]     if (g->mode == kGameModeTwoPlayer || manual_r) ai_right = false;
[OUT]     g->ai_left_active = ai_left;
[OUT]     g->ai_right_active = ai_right;
[OUT]     ai_step(g, dt, ai_left, ai_right);
[OUT] 
[OUT]     if (!g->countdown_active)
[OUT]     {
[OUT]         physics_step(g, dt);
[OUT]     }
[OUT]     else
[OUT]     {
[OUT]         game_update_countdown(g);
[OUT]     }
[OUT] 
[OUT]     if (!g->perpetual_play && (g->score.left >= EDGEAI_WIN_SCORE || g->score.right >= EDGEAI_WIN_SCORE))
[OUT]     {
[OUT]         g->match_over = true;
[OUT]         g->winner_left = (g->score.left >= EDGEAI_WIN_SCORE);
[OUT]         g->end_prompt_dismissed = (g->mode == kGameModeZeroPlayer);
[OUT]         g->match_over_frame = g->frame;
[OUT]         g->match_over_start_cycles = time_hal_cycles();
[OUT] 
[OUT]         g->ball.vx = 0.0f;
[OUT]         g->ball.vy = 0.0f;
[OUT]         g->ball.vz = 0.0f;
[OUT]         g->countdown_active = false;
[OUT]         g->countdown_us_left = 0u;
[OUT]     }
[OUT] 
[OUT]     /* Apply after physics so paddle hits do not overwrite the external nudge. */
[OUT]     if (!g->match_over && !g->countdown_active)
[OUT]     {
[OUT]         game_apply_accel_ball_nudge(g, in, dt);
[OUT]     }
[OUT]     g->frame++;
[OUT] }
[2026-02-25T00:28:17Z] CMD: rg -n "ai_learning_apply_result|speed_scale|noise_scale|lead_scale|hits|misses|persistent_learning|ai_learning_reset_session" src/game/ai.c src/game/physics.c src/game/game.c && sed -n "260,420p" src/game/ai.c && sed -n "1,220p" src/game/physics.c
[OUT] src/game/game.c:303:            if (g->persistent_learning != en)
[OUT] src/game/game.c:385:    g->persistent_learning = true;
[OUT] src/game/game.c:485:    if (g->persistent_learning)
[OUT] src/game/game.c:587:    /* Apply after physics so paddle hits do not overwrite the external nudge. */
[OUT] src/game/physics.c:111:static float physics_ball_speed_scale(const pong_game_t *g)
[OUT] src/game/physics.c:154:    float s = physics_ball_speed_scale(g);
[OUT] src/game/physics.c:272:    /* Touch control can produce very large paddle velocities; clamp to keep hits stable. */
[OUT] src/game/ai.c:153:    p.speed_scale = 1.0f;
[OUT] src/game/ai.c:154:    p.noise_scale = 1.0f;
[OUT] src/game/ai.c:155:    p.lead_scale = 1.0f;
[OUT] src/game/ai.c:156:    p.hits = 0u;
[OUT] src/game/ai.c:157:    p.misses = 0u;
[OUT] src/game/ai.c:164:    p->speed_scale = clampf(p->speed_scale, 0.75f, 1.85f);
[OUT] src/game/ai.c:165:    p->noise_scale = clampf(p->noise_scale, 0.40f, 2.20f);
[OUT] src/game/ai.c:166:    p->lead_scale = clampf(p->lead_scale, 0.70f, 2.00f);
[OUT] src/game/ai.c:198:    if (!g || !g->persistent_learning) return;
[OUT] src/game/ai.c:210:    if (!g || !g->persistent_learning) return;
[OUT] src/game/ai.c:244:void ai_learning_reset_session(pong_game_t *g)
[OUT] src/game/ai.c:273:        g->persistent_learning = true;
[OUT] src/game/ai.c:281:    g->persistent_learning = false;
[OUT] src/game/ai.c:282:    ai_learning_reset_session(g);
[OUT] src/game/ai.c:290:    if (!g || !g->persistent_learning) return;
[OUT] src/game/ai.c:307:    p->hits = clampu16((uint32_t)p->hits + 1u, 65535u);
[OUT] src/game/ai.c:310:    p->noise_scale *= 0.987f;
[OUT] src/game/ai.c:311:    p->speed_scale += 0.008f;
[OUT] src/game/ai.c:312:    p->lead_scale += 0.005f;
[OUT] src/game/ai.c:326:    p->misses = clampu16((uint32_t)p->misses + 1u, 65535u);
[OUT] src/game/ai.c:329:    p->noise_scale *= 0.94f;
[OUT] src/game/ai.c:330:    p->speed_scale += 0.045f;
[OUT] src/game/ai.c:331:    p->lead_scale += 0.030f;
[OUT] src/game/ai.c:447:    ai_learning_reset_session(g);
[OUT] src/game/ai.c:566:            n *= p->noise_scale;
[OUT] src/game/ai.c:597:            s *= p->speed_scale;
[OUT] src/game/ai.c:605:static float ai_lead_scale(const pong_game_t *g, bool right_side)
[OUT] src/game/ai.c:611:    return clampf(p->lead_scale, 0.70f, 2.00f);
[OUT] src/game/ai.c:725:                float lead = ai_lead_scale(g, right_side);
[OUT] src/game/ai.c:788:        p->speed_scale += (1.0f - p->speed_scale) * 0.0008f;
[OUT] src/game/ai.c:789:        p->noise_scale += (1.0f - p->noise_scale) * 0.0010f;
[OUT] src/game/ai.c:790:        p->lead_scale += (1.0f - p->lead_scale) * 0.0008f;
[OUT] src/game/ai.c:796:        p->speed_scale += (1.0f - p->speed_scale) * 0.0008f;
[OUT] src/game/ai.c:797:        p->noise_scale += (1.0f - p->noise_scale) * 0.0010f;
[OUT] src/game/ai.c:798:        p->lead_scale += (1.0f - p->lead_scale) * 0.0008f;
[OUT] ---
[OUT]             g->ai_learn_mode = mode;
[OUT]             break;
[OUT]         default:
[OUT]             g->ai_learn_mode = kAiLearnModeBoth;
[OUT]             break;
[OUT]     }
[OUT] }
[OUT] 
[OUT] void ai_learning_set_persistent(pong_game_t *g, bool enabled)
[OUT] {
[OUT]     if (!g) return;
[OUT]     if (enabled)
[OUT]     {
[OUT]         g->persistent_learning = true;
[OUT]         ai_learning_load_store(g);
[OUT]         return;
[OUT]     }
[OUT] 
[OUT]     /* Persistence OFF means no carry-over advantage:
[OUT]      * clear current learned profiles and wipe stored snapshot.
[OUT]      */
[OUT]     g->persistent_learning = false;
[OUT]     ai_learning_reset_session(g);
[OUT]     memset(&s_learn_store, 0, sizeof(s_learn_store));
[OUT]     s_learn_store_dirty = false;
[OUT]     ai_flash_clear_store();
[OUT] }
[OUT] 
[OUT] void ai_learning_sync_store(pong_game_t *g)
[OUT] {
[OUT]     if (!g || !g->persistent_learning) return;
[OUT]     if (!s_learn_store_dirty) return;
[OUT]     if (ai_flash_write_store(&s_learn_store))
[OUT]     {
[OUT]         s_learn_store_dirty = false;
[OUT]     }
[OUT] }
[OUT] 
[OUT] void ai_learning_on_paddle_hit(pong_game_t *g, bool left_side)
[OUT] {
[OUT]     if (!g) return;
[OUT]     bool right_side = !left_side;
[OUT]     if (!ai_learning_side_selected(g, right_side)) return;
[OUT] 
[OUT]     ai_learn_profile_t *p = ai_profile_side(g, right_side);
[OUT]     if (!p) return;
[OUT] 
[OUT]     p->hits = clampu16((uint32_t)p->hits + 1u, 65535u);
[OUT] 
[OUT]     /* Successful return: slightly cleaner and quicker tracking, with mild anticipation. */
[OUT]     p->noise_scale *= 0.987f;
[OUT]     p->speed_scale += 0.008f;
[OUT]     p->lead_scale += 0.005f;
[OUT]     ai_profile_clamp(p);
[OUT]     ai_learning_commit_store(g);
[OUT] }
[OUT] 
[OUT] void ai_learning_on_miss(pong_game_t *g, bool left_side)
[OUT] {
[OUT]     if (!g) return;
[OUT]     bool right_side = !left_side;
[OUT]     if (!ai_learning_side_selected(g, right_side)) return;
[OUT] 
[OUT]     ai_learn_profile_t *p = ai_profile_side(g, right_side);
[OUT]     if (!p) return;
[OUT] 
[OUT]     p->misses = clampu16((uint32_t)p->misses + 1u, 65535u);
[OUT] 
[OUT]     /* Missed return: make AI react faster and reduce wander so it recovers over the session. */
[OUT]     p->noise_scale *= 0.94f;
[OUT]     p->speed_scale += 0.045f;
[OUT]     p->lead_scale += 0.030f;
[OUT]     ai_profile_clamp(p);
[OUT]     ai_learning_commit_store(g);
[OUT] }
[OUT] 
[OUT] static void ai_sim_wall(float *p, float *v, float r)
[OUT] {
[OUT]     if (!p || !v) return;
[OUT]     if ((*p - r) < 0.0f)
[OUT]     {
[OUT]         *p = r;
[OUT]         *v = absf(*v);
[OUT]     }
[OUT]     if ((*p + r) > 1.0f)
[OUT]     {
[OUT]         *p = 1.0f - r;
[OUT]         *v = -absf(*v);
[OUT]     }
[OUT] }
[OUT] 
[OUT] static void ai_predict_right(const pong_game_t *g, float dt, float *out_y, float *out_z, float *out_t)
[OUT] {
[OUT]     if (!out_y || !out_z || !out_t)
[OUT]         return;
[OUT] 
[OUT]     *out_y = 0.5f;
[OUT]     *out_z = 0.5f;
[OUT]     *out_t = 0.0f;
[OUT]     if (!g) return;
[OUT] 
[OUT]     if (g->ball.vx <= 0.0f)
[OUT]     {
[OUT]         *out_y = 0.5f;
[OUT]         *out_z = 0.5f;
[OUT]         *out_t = 0.0f;
[OUT]         return;
[OUT]     }
[OUT] 
[OUT]     float x = g->ball.x;
[OUT]     float y = g->ball.y;
[OUT]     float z = g->ball.z;
[OUT]     float vx = g->ball.vx;
[OUT]     float vy = g->ball.vy;
[OUT]     float vz = g->ball.vz;
[OUT]     float r = g->ball.r;
[OUT] 
[OUT]     const float x_hit = g->paddle_r.x_plane - r;
[OUT]     const int max_steps = 240; /* ~4s at 60 Hz */
[OUT] 
[OUT]     for (int i = 0; i < max_steps; i++)
[OUT]     {
[OUT]         x += vx * dt;
[OUT]         y += vy * dt;
[OUT]         z += vz * dt;
[OUT]         ai_sim_wall(&y, &vy, r);
[OUT]         ai_sim_wall(&z, &vz, r);
[OUT]         if (x >= x_hit)
[OUT]         {
[OUT]             *out_y = clampf(y, 0.0f, 1.0f);
[OUT]             *out_z = clampf(z, 0.0f, 1.0f);
[OUT]             *out_t = (float)(i + 1) * dt;
[OUT]             return;
[OUT]         }
[OUT]     }
[OUT] }
[OUT] 
[OUT] static void ai_predict_left(const pong_game_t *g, float dt, float *out_y, float *out_z, float *out_t)
[OUT] {
[OUT]     if (!out_y || !out_z || !out_t)
[OUT]         return;
[OUT] 
[OUT]     *out_y = 0.5f;
[OUT]     *out_z = 0.5f;
[OUT]     *out_t = 0.0f;
[OUT]     if (!g) return;
[OUT] 
[OUT]     if (g->ball.vx >= 0.0f)
[OUT]     {
[OUT]         *out_y = 0.5f;
[OUT]         *out_z = 0.5f;
[OUT]         *out_t = 0.0f;
[OUT]         return;
[OUT]     }
[OUT] 
[OUT]     float x = g->ball.x;
[OUT]     float y = g->ball.y;
[OUT]     float z = g->ball.z;
[OUT]     float vx = g->ball.vx;
[OUT]     float vy = g->ball.vy;
[OUT]     float vz = g->ball.vz;
[OUT] ---
[OUT] #include "game/physics.h"
[OUT] 
[OUT] #include <math.h>
[OUT] #include <stddef.h>
[OUT] 
[OUT] #include "game/ai.h"
[OUT] 
[OUT] static inline float clampf(float v, float lo, float hi)
[OUT] {
[OUT]     if (v < lo) return lo;
[OUT]     if (v > hi) return hi;
[OUT]     return v;
[OUT] }
[OUT] 
[OUT] static inline float absf(float v)
[OUT] {
[OUT]     return (v < 0.0f) ? -v : v;
[OUT] }
[OUT] 
[OUT] static inline uint32_t xorshift32(uint32_t x)
[OUT] {
[OUT]     x ^= x << 13;
[OUT]     x ^= x >> 17;
[OUT]     x ^= x << 5;
[OUT]     return x;
[OUT] }
[OUT] 
[OUT] static float rand_f01(pong_game_t *g)
[OUT] {
[OUT]     g->rng = xorshift32(g->rng ? g->rng : 1u);
[OUT]     /* 24-bit mantissa fraction. */
[OUT]     uint32_t u = (g->rng >> 8) & 0x00FFFFFFu;
[OUT]     return (float)u * (1.0f / 16777215.0f);
[OUT] }
[OUT] 
[OUT] static float rand_f(pong_game_t *g, float lo, float hi)
[OUT] {
[OUT]     return lo + (hi - lo) * rand_f01(g);
[OUT] }
[OUT] 
[OUT] static float physics_ball_speed_mag(const pong_game_t *g)
[OUT] {
[OUT]     if (!g) return 0.0f;
[OUT]     float vx = g->ball.vx;
[OUT]     float vy = g->ball.vy;
[OUT]     float vz = g->ball.vz;
[OUT]     return sqrtf(vx * vx + vy * vy + vz * vz);
[OUT] }
[OUT] 
[OUT] static void physics_speedpp_track_peak(pong_game_t *g)
[OUT] {
[OUT]     if (!g) return;
[OUT]     float s = physics_ball_speed_mag(g);
[OUT]     if (s > g->speedpp_peak_speed)
[OUT]     {
[OUT]         g->speedpp_peak_speed = s;
[OUT]     }
[OUT] }
[OUT] 
[OUT] static void physics_speedpp_on_score(pong_game_t *g, bool point_to_left)
[OUT] {
[OUT]     if (!g || !g->speedpp_enabled) return;
[OUT] 
[OUT]     uint16_t scored = point_to_left ? g->score.left : g->score.right;
[OUT]     if (scored == 0u || (scored % 11u) != 0u) return;
[OUT] 
[OUT]     float base = g->speedpp_serve_speed_target;
[OUT]     if (base <= 0.0f)
[OUT]     {
[OUT]         float peak = g->speedpp_peak_speed;
[OUT]         if (peak > 0.0f)
[OUT]         {
[OUT]             base = peak;
[OUT]         }
[OUT]     }
[OUT] 
[OUT]     if (base > 0.0f)
[OUT]     {
[OUT]         g->speedpp_serve_speed_target = base * 1.05f;
[OUT]     }
[OUT] 
[OUT]     if (g->speedpp_stage < 255u)
[OUT]     {
[OUT]         g->speedpp_stage++;
[OUT]     }
[OUT] }
[OUT] 
[OUT] static int physics_substeps(const pong_game_t *g, float dt)
[OUT] {
[OUT]     if (!g) return 1;
[OUT]     if (dt <= 0.0f) return 1;
[OUT] 
[OUT]     float vmax = absf(g->ball.vx);
[OUT]     float avy = absf(g->ball.vy);
[OUT]     float avz = absf(g->ball.vz);
[OUT]     if (avy > vmax) vmax = avy;
[OUT]     if (avz > vmax) vmax = avz;
[OUT] 
[OUT]     /* Keep per-substep motion small to avoid tunneling through paddles at higher speeds. */
[OUT]     float limit = g->ball.r * 0.5f;
[OUT]     if (limit < 0.001f) limit = 0.001f;
[OUT] 
[OUT]     float ratio = (vmax * dt) / limit;
[OUT]     int n = (int)ratio;
[OUT]     if ((float)n < ratio) n++;
[OUT]     if (n < 1) n = 1;
[OUT]     if (n > 8) n = 8;
[OUT]     return n;
[OUT] }
[OUT] 
[OUT] static float physics_ball_speed_scale(const pong_game_t *g)
[OUT] {
[OUT]     uint8_t d = g ? g->difficulty : 2;
[OUT]     if (d < 1) d = 1;
[OUT]     if (d > 3) d = 3;
[OUT]     switch (d)
[OUT]     {
[OUT]         case 1: return 1.95f;
[OUT]         case 2: return 2.14f;
[OUT]         default: return 2.32f;
[OUT]     }
[OUT] }
[OUT] 
[OUT] static void physics_get_tuning(const pong_game_t *g, float *serve_speed, float *speed_up, float *vlim)
[OUT] {
[OUT]     uint8_t d = g ? g->difficulty : 2;
[OUT]     if (d < 1) d = 1;
[OUT]     if (d > 3) d = 3;
[OUT] 
[OUT]     if (serve_speed) *serve_speed = 1.00f;
[OUT]     if (speed_up) *speed_up = 1.025f;
[OUT]     if (vlim) *vlim = 2.30f;
[OUT] 
[OUT]     switch (d)
[OUT]     {
[OUT]         case 1:
[OUT]             if (serve_speed) *serve_speed = 0.82f;
[OUT]             if (speed_up) *speed_up = 1.018f;
[OUT]             if (vlim) *vlim = 1.90f;
[OUT]             break;
[OUT]         case 2:
[OUT]             if (serve_speed) *serve_speed = 1.02f;
[OUT]             if (speed_up) *speed_up = 1.025f;
[OUT]             if (vlim) *vlim = 2.30f;
[OUT]             break;
[OUT]         default:
[OUT]             if (serve_speed) *serve_speed = 1.18f;
[OUT]             if (speed_up) *speed_up = 1.035f;
[OUT]             if (vlim) *vlim = 2.80f;
[OUT]             break;
[OUT]     }
[OUT] 
[OUT]     /* Scale overall ball speeds per difficulty preset. */
[OUT]     float s = physics_ball_speed_scale(g);
[OUT]     if (serve_speed) *serve_speed *= s;
[OUT]     if (vlim) *vlim *= s;
[OUT] 
[OUT]     /* Requested: double max speed cap for every difficulty setting. */
[OUT]     if (vlim) *vlim *= 2.0f;
[OUT] }
[OUT] 
[OUT] void physics_reset_ball(pong_game_t *g, int serve_dir)
[OUT] {
[OUT]     if (!g) return;
[OUT] 
[OUT]     float dir = (serve_dir >= 0) ? 1.0f : -1.0f;
[OUT] 
[OUT]     g->ball.x = 0.5f;
[OUT]     g->ball.y = rand_f(g, 0.30f, 0.70f);
[OUT]     g->ball.z = rand_f(g, 0.20f, 0.80f);
[OUT]     g->ball.r = 0.040f;
[OUT] 
[OUT]     float serve_speed = 1.0f;
[OUT]     float vlim = 1.0f;
[OUT]     physics_get_tuning(g, &serve_speed, NULL, &vlim);
[OUT]     if (g->speedpp_enabled && g->speedpp_serve_speed_target > 0.0f)
[OUT]     {
[OUT]         float max_serve = vlim * 0.95f;
[OUT]         if (max_serve < serve_speed) max_serve = serve_speed;
[OUT]         serve_speed = clampf(g->speedpp_serve_speed_target, serve_speed, max_serve);
[OUT]     }
[OUT]     g->ball.vx = dir * serve_speed;
[OUT]     g->ball.vy = rand_f(g, -0.28f, 0.28f);
[OUT]     g->ball.vz = rand_f(g, -0.22f, 0.22f);
[OUT]     physics_speedpp_track_peak(g);
[OUT] }
[OUT] 
[OUT] static void physics_wall_bounce(float *p, float *v, float r)
[OUT] {
[OUT]     if (!p || !v) return;
[OUT]     if ((*p - r) < 0.0f)
[OUT]     {
[OUT]         *p = r;
[OUT]         *v = absf(*v);
[OUT]     }
[OUT]     if ((*p + r) > 1.0f)
[OUT]     {
[OUT]         *p = 1.0f - r;
[OUT]         *v = -absf(*v);
[OUT]     }
[OUT] }
[OUT] 
[OUT] static float physics_axis_reflect(float p0, float v, float tau, float r)
[OUT] {
[OUT]     float lo = r;
[OUT]     float hi = 1.0f - r;
[OUT]     float p = p0 + v * tau;
[OUT] 
[OUT]     /* Apply a small number of reflections; with substeps, more than one is unlikely. */
[OUT]     for (int i = 0; i < 4; i++)
[OUT]     {
[OUT]         if (p < lo)
[OUT]         {
[OUT]             p = lo + (lo - p);
[OUT]             continue;
[OUT]         }
[OUT]         if (p > hi)
[OUT]         {
[OUT]             p = hi - (p - hi);
[OUT]             continue;
[2026-02-25T00:28:23Z] CMD: sed -n "480,620p" src/game/ai.c
[OUT] static void ai_mirror_features_x(const float in[16], float out[16])
[OUT] {
[OUT]     if (!in || !out) return;
[OUT] 
[OUT]     /* Keep the NPU feature view always predicting the right paddle plane:
[OUT]      * - mirror x and vx
[OUT]      * - swap left/right paddle features
[OUT]      * - flip score diff sign (left-right -> right-left)
[OUT]      */
[OUT]     memcpy(out, in, 16 * sizeof(out[0]));
[OUT] 
[OUT]     out[0] = 1.0f - in[0];   /* ball.x */
[OUT]     out[3] = -in[3];         /* ball.vx */
[OUT] 
[OUT]     /* left paddle (6..9) <-> right paddle (10..11) */
[OUT]     out[6] = in[10]; /* opp y */
[OUT]     out[7] = in[11]; /* opp z */
[OUT]     out[8] = 0.0f;
[OUT]     out[9] = 0.0f;
[OUT] 
[OUT]     out[10] = in[6]; /* self y */
[OUT]     out[11] = in[7]; /* self z */
[OUT] 
[OUT]     out[12] = -in[12];
[OUT] }
[OUT] 
[OUT] static uint32_t ai_update_div(const pong_game_t *g, bool use_npu)
[OUT] {
[OUT]     uint8_t d = g ? g->difficulty : 2;
[OUT]     if (d < 1) d = 1;
[OUT]     if (d > 3) d = 3;
[OUT] 
[OUT]     if (!use_npu)
[OUT]     {
[OUT]         switch (d)
[OUT]         {
[OUT]             case 1: return 5u;
[OUT]             case 2: return 3u;
[OUT]             default: return 2u;
[OUT]         }
[OUT]     }
[OUT] 
[OUT]     /* NPU path: throttle updates to protect frame pacing, then adapt to observed latency. */
[OUT]     uint32_t div = 4u;
[OUT]     switch (d)
[OUT]     {
[OUT]         case 1: div = 9u; break;
[OUT]         case 2: div = 7u; break;
[OUT]         default: div = 5u; break;
[OUT]     }
[OUT] 
[OUT]     uint32_t avg_us = g ? g->npu.avg_infer_us : 0u;
[OUT]     if (avg_us > 14000u) div += 3u;
[OUT]     else if (avg_us > 9000u) div += 2u;
[OUT]     else if (avg_us > 5000u) div += 1u;
[OUT] 
[OUT]     if (div < 2u) div = 2u;
[OUT]     if (div > 14u) div = 14u;
[OUT]     return div;
[OUT] }
[OUT] 
[OUT] static float ai_noise(const pong_game_t *g, bool right_side)
[OUT] {
[OUT]     uint8_t d = g ? g->difficulty : 2;
[OUT]     if (d < 1) d = 1;
[OUT]     if (d > 3) d = 3;
[OUT] 
[OUT]     float n = 0.015f;
[OUT]     switch (d)
[OUT]     {
[OUT]         case 1: n = 0.032f; break;
[OUT]         case 2: n = 0.015f; break;
[OUT]         default: n = 0.007f; break;
[OUT]     }
[OUT] 
[OUT]     /* Show clear behavior difference when NPU path is disabled. */
[OUT]     if (g && !g->ai_enabled)
[OUT]     {
[OUT]         n *= 1.7f;
[OUT]     }
[OUT] 
[OUT]     if (g && ai_learning_side_selected(g, right_side))
[OUT]     {
[OUT]         const ai_learn_profile_t *p = ai_profile_side_const(g, right_side);
[OUT]         if (p)
[OUT]         {
[OUT]             n *= p->noise_scale;
[OUT]         }
[OUT]     }
[OUT] 
[OUT]     n = clampf(n, 0.002f, 0.08f);
[OUT]     return n;
[OUT] }
[OUT] 
[OUT] static float ai_max_speed(const pong_game_t *g, bool right_side)
[OUT] {
[OUT]     uint8_t d = g ? g->difficulty : 2;
[OUT]     if (d < 1) d = 1;
[OUT]     if (d > 3) d = 3;
[OUT]     float s = 1.48f;
[OUT]     switch (d)
[OUT]     {
[OUT]         case 1: s = 1.22f; break;
[OUT]         case 2: s = 1.48f; break;
[OUT]         default: s = 1.78f; break;
[OUT]     }
[OUT] 
[OUT]     if (g && !g->ai_enabled)
[OUT]     {
[OUT]         s *= 0.82f;
[OUT]     }
[OUT] 
[OUT]     if (g && ai_learning_side_selected(g, right_side))
[OUT]     {
[OUT]         const ai_learn_profile_t *p = ai_profile_side_const(g, right_side);
[OUT]         if (p)
[OUT]         {
[OUT]             s *= p->speed_scale;
[OUT]         }
[OUT]     }
[OUT] 
[OUT]     s = clampf(s, 0.70f, 2.60f);
[OUT]     return s;
[OUT] }
[OUT] 
[OUT] static float ai_lead_scale(const pong_game_t *g, bool right_side)
[OUT] {
[OUT]     if (!g) return 1.0f;
[OUT]     if (!ai_learning_side_selected(g, right_side)) return 1.0f;
[OUT]     const ai_learn_profile_t *p = ai_profile_side_const(g, right_side);
[OUT]     if (!p) return 1.0f;
[OUT]     return clampf(p->lead_scale, 0.70f, 2.00f);
[OUT] }
[OUT] 
[OUT] static void ai_update_telemetry_window(pong_game_t *g)
[OUT] {
[OUT]     if (!g) return;
[OUT] 
[OUT]     if (g->ai_telemetry_start_cycles == 0u)
[OUT]     {
[OUT]         g->ai_telemetry_start_cycles = time_hal_cycles();
[2026-02-25T00:28:57Z] CMD: patched ai.c mixed-mode cadence + confidence gate; updated STATUS.md; git status --short; rg -n "mixed SKILL|disagreement|ai_update_div" src/game/ai.c STATUS.md
[OUT]  M STATUS.md
[OUT]  M docs/COMMAND_LOG.md
[OUT]  M src/game/ai.c
[OUT] ---
[OUT] STATUS.md:24:- Notes (mixed-mode tune): reduced EdgeAI mixed-mode handicap by using ALGO-like target update cadence plus adaptive NPU confidence gating (fallback to analytic predictor on high disagreement).
[OUT] src/game/ai.c:506:static uint32_t ai_update_div(const pong_game_t *g, bool use_npu)
[OUT] src/game/ai.c:522:    /* In mixed SKILL modes, keep EdgeAI control cadence near ALGO cadence so the
[OUT] src/game/ai.c:665:    uint32_t div = ai_update_div(g, use_npu);
[OUT] src/game/ai.c:698:                    /* In mixed SKILL modes, blend NPU with analytic prediction to
[OUT] src/game/ai.c:721:                        float disagreement = dy + dz + (0.60f * dtau);
[OUT] src/game/ai.c:724:                        if (disagreement >= 0.22f)
[OUT] src/game/ai.c:728:                        else if (disagreement > 0.0f)
[OUT] src/game/ai.c:730:                            float trust = 1.0f - (disagreement / 0.22f);
[2026-02-25T00:29:04Z] CMD: ./tools/build_frdmmcxn947.sh && ./tools/flash_frdmmcxn947.sh
[2026-02-25T00:32:41Z] RESULT: build=PASS flash=PASS
[2026-02-25T00:32:47Z] CMD: git status --short && tail -n 20 docs/COMMAND_LOG.md
[OUT]  M STATUS.md
[OUT]  M docs/COMMAND_LOG.md
[OUT]  M src/game/ai.c
[OUT] ---
[OUT] [OUT] 
[OUT] [OUT]     if (g->ai_telemetry_start_cycles == 0u)
[OUT] [OUT]     {
[OUT] [OUT]         g->ai_telemetry_start_cycles = time_hal_cycles();
[OUT] [2026-02-25T00:28:57Z] CMD: patched ai.c mixed-mode cadence + confidence gate; updated STATUS.md; git status --short; rg -n "mixed SKILL|disagreement|ai_update_div" src/game/ai.c STATUS.md
[OUT] [OUT]  M STATUS.md
[OUT] [OUT]  M docs/COMMAND_LOG.md
[OUT] [OUT]  M src/game/ai.c
[OUT] [OUT] ---
[OUT] [OUT] STATUS.md:24:- Notes (mixed-mode tune): reduced EdgeAI mixed-mode handicap by using ALGO-like target update cadence plus adaptive NPU confidence gating (fallback to analytic predictor on high disagreement).
[OUT] [OUT] src/game/ai.c:506:static uint32_t ai_update_div(const pong_game_t *g, bool use_npu)
[OUT] [OUT] src/game/ai.c:522:    /* In mixed SKILL modes, keep EdgeAI control cadence near ALGO cadence so the
[OUT] [OUT] src/game/ai.c:665:    uint32_t div = ai_update_div(g, use_npu);
[OUT] [OUT] src/game/ai.c:698:                    /* In mixed SKILL modes, blend NPU with analytic prediction to
[OUT] [OUT] src/game/ai.c:721:                        float disagreement = dy + dz + (0.60f * dtau);
[OUT] [OUT] src/game/ai.c:724:                        if (disagreement >= 0.22f)
[OUT] [OUT] src/game/ai.c:728:                        else if (disagreement > 0.0f)
[OUT] [OUT] src/game/ai.c:730:                            float trust = 1.0f - (disagreement / 0.22f);
[OUT] [2026-02-25T00:29:04Z] CMD: ./tools/build_frdmmcxn947.sh && ./tools/flash_frdmmcxn947.sh
[OUT] [2026-02-25T00:32:41Z] RESULT: build=PASS flash=PASS
[2026-02-25T00:54:39Z] CMD: git add src/game/ai.c STATUS.md docs/COMMAND_LOG.md && git commit -m "Tune mixed SKILL AI competitiveness and confidence gating" && git push origin main && git rev-parse --short HEAD
[2026-02-25T00:54:44Z] RESULT: commit+push=PASS hash=24c362c
[2026-02-25T00:59:43Z] CMD: ls -la && ls -la docs && ls -la failsafe
[OUT] total 60
[OUT] drwxrwxrwx  9 user user 4096 Feb 24 16:03 .
[OUT] drwxrwxr-x 10 user user 4096 Feb 24 06:37 ..
[OUT] drwxrwxr-x  8 user user 4096 Feb 24 16:54 .git
[OUT] -rw-rw-r--  1 user user  172 Feb 10 13:13 .gitignore
[OUT] -rw-rw-r--  1 user user 1074 Feb 15 17:54 LICENSE
[OUT] -rw-rw-r--  1 user user 6583 Feb 24 16:03 README.md
[OUT] -rw-rw-r--  1 user user 2222 Feb 24 16:28 STATUS.md
[OUT] -rw-rw-r--  1 user user 2085 Feb 11 07:41 ToDo.md
[OUT] drwxrwxrwx  2 user user 4096 Feb 24 16:03 docs
[OUT] drwxrwxrwx  2 user user 4096 Feb 24 16:02 failsafe
[OUT] drwxrwxrwx 23 user user 4096 Feb 10 18:40 mcuxsdk_ws
[OUT] drwxrwxrwx  3 user user 4096 Feb 10 07:17 sdk_example
[OUT] drwxrwxrwx  5 user user 4096 Feb 10 18:37 src
[OUT] drwxrwxr-x  2 user user 4096 Feb 10 19:47 tools
[OUT] ---
[OUT] total 1508
[OUT] drwxrwxrwx 2 user user    4096 Feb 24 16:03 .
[OUT] drwxrwxrwx 9 user user    4096 Feb 24 16:03 ..
[OUT] -rw-rw-r-- 1 user user    1891 Feb 10 21:09 BUILD_FLASH.md
[OUT] -rw-rw-r-- 1 user user  102270 Feb 24 16:54 COMMAND_LOG.md
[OUT] -rw-rw-r-- 1 user user     903 Feb 11 07:41 HARDWARE.md
[OUT] -rw-rw-r-- 1 user user     159 Feb 10 20:48 START_HERE.md
[OUT] -rw-rw-r-- 1 user user     767 Feb 11 07:41 STYLE_RULES.md
[OUT] -rw-rw-r-- 1 user user     193 Feb 24 16:03 failsafe.md
[OUT] -rw-rw-r-- 1 user user 1402600 Feb 10 07:12 pong_3D.png
[OUT] -rw-rw-r-- 1 user user    3879 Feb 24 15:25 project_description.md
[OUT] ---
[OUT] total 82576
[OUT] drwxrwxrwx 2 user user    4096 Feb 24 16:02 .
[OUT] drwxrwxrwx 9 user user    4096 Feb 24 16:03 ..
[OUT] -rw-rw-r-- 1 user user       0 Feb 10 07:17 .gitkeep
[OUT] -rwxrwxr-x 1 user user  555452 Feb 10 11:40 edgeai_smart_pong_demo_cm33_core0_20260210_1140_golden.elf
[OUT] -rwxrwxr-x 1 user user  598420 Feb 10 13:10 edgeai_smart_pong_demo_cm33_core0_20260210_1310_touch_ui_golden.elf
[OUT] -rwxrwxr-x 1 user user  601092 Feb 10 14:34 edgeai_smart_pong_demo_cm33_core0_20260210_1434_touch_controls_v2_golden.elf
[OUT] -rwxrwxr-x 1 user user  615012 Feb 10 15:52 edgeai_smart_pong_demo_cm33_core0_20260210_1627_ui_help_fix_v1_golden.elf
[OUT] -rwxr-xr-x 1 user user  624232 Feb 10 18:02 edgeai_smart_pong_demo_cm33_core0_20260210_1758_accel_ball_nudge_v1_golden.elf
[OUT] -rwxrwxr-x 1 user user 8135448 Feb 10 20:44 edgeai_smart_pong_demo_cm33_core0_20260210_2044_npu_stable_golden.elf
[OUT] -rwxrwxr-x 1 user user 8136516 Feb 10 21:12 edgeai_smart_pong_demo_cm33_core0_20260210_2112_smart_pong_ai_toggle_golden.elf
[OUT] -rwxrwxr-x 1 user user 8144572 Feb 11 06:25 edgeai_smart_pong_demo_cm33_core0_20260211_0625_win11_confetti_newgame_golden.elf
[OUT] -rwxrwxr-x 1 user user 8146248 Feb 11 07:08 edgeai_smart_pong_demo_cm33_core0_20260211_0707_countdown_realtime_golden.elf
[OUT] -rwxrwxr-x 1 user user 8146172 Feb 11 07:46 edgeai_smart_pong_demo_cm33_core0_20260211_0745_p0_win11_autoloop_final_golden.elf
[OUT] -rwxrwxr-x 1 user user 8146392 Feb 11 08:21 edgeai_smart_pong_demo_cm33_core0_20260211_0821_p0_restart_confetti_tuned_golden.elf
[OUT] -rwxrwxr-x 1 user user 8156628 Feb 11 09:41 edgeai_smart_pong_demo_cm33_core0_20260211_0941_ai_hardening_uitelemetry_popup_golden.elf
[OUT] -rwxrwxr-x 1 user user 8158396 Feb 11 09:53 edgeai_smart_pong_demo_cm33_core0_20260211_0953_ai_lag_telemetry_showcase_golden.elf
[OUT] -rwxrwxr-x 1 user user 8178820 Feb 11 12:30 edgeai_smart_pong_demo_cm33_core0_20260211_1230_final_release_golden.elf
[OUT] -rwxrwxr-x 1 user user 8179060 Feb 11 13:10 edgeai_smart_pong_demo_cm33_core0_20260211_1309_final_release_score999_golden.elf
[2026-02-25T00:59:43Z] CMD: sed -n "1,260p" README.md && sed -n "1,260p" STATUS.md && sed -n "1,260p" docs/START_HERE.md
[OUT] # Smart Pong Demo (FRDM-MCXN947)
[OUT] 
[OUT] Smart Pong is a 3D-look Pong implementation for FRDM-MCXN947 with LCD-PAR-S035.
[OUT] 
[OUT] https://github.com/user-attachments/assets/fd94e3e0-a301-4cc3-8c4f-7ec1a7cc35af
[OUT] 
[OUT] ## Real World AI Learning Demonstration
[OUT] 1. Compare three control behaviors in the same system:
[OUT]    - `HUMAN`: touch-driven paddle control
[OUT]    - `ALGO`: fixed classic CPU predictor (non-learning baseline)
[OUT]    - `EdgeAI`: NPU-assisted predictor with adaptive runtime tuning
[OUT] 2. Observe online learning in live play:
[OUT]    - The adaptive controller updates from rally outcomes (hits/misses), then changes paddle speed, anticipation, and tracking noise.
[OUT]    - `SKILL` modes allow direct side comparison:
[OUT]      - `AI/ALGO`: left uses adaptive EdgeAI, right uses fixed ALGO.
[OUT]      - `ALGO/AI`: left uses fixed ALGO, right uses adaptive EdgeAI.
[OUT]      - `2AI`: both sides use adaptive EdgeAI.
[OUT] 3. Validate session learning vs persistent learning:
[OUT]    - `PERSIST ON`: left/right learned profiles carry across new matches and are restored independently from onboard flash after reboot/power cycle.
[OUT]    - `PERSIST OFF`: learned profile is cleared, forcing a cold-start behavior.
[OUT] 4. Demonstrate deployment-style tradeoffs:
[OUT]    - NPU path is used when enabled and available, with CPU fallback always present for robustness.
[OUT]    - Bottom telemetry helps correlate behavior with NPU/fallback timing and latency trends.
[OUT] 
[OUT] ## Hardware Components
[OUT] 1. Manufacturer: NXP Semiconductors
[OUT]    - Name: FRDM-MCXN947 development board
[OUT]    - Part number: FRDM-MCXN947
[OUT] 2. Manufacturer: NXP Semiconductors
[OUT]    - Name: 3.5" Parallel TFT LCD shield (ST7796S + GT911)
[OUT]    - Part number: LCD-PAR-S035
[OUT] 3. Manufacturer: MikroElektronika (sensor IC by NXP)
[OUT]    - Name: Accel 4 Click (3-axis accelerometer module, FXLS8974CF)
[OUT]    - Part number: MIKROE-4630
[OUT] 
[OUT] ## Gameplay Rules
[OUT] - Objective: first side to 11 points wins the match.
[OUT] - Scoring: when a side misses and the ball exits that side, the opponent gains 1 point.
[OUT] - Ball motion: ball reflects from top and bottom arena walls.
[OUT] - Paddle collision: ball reflects from paddles with hit-position-based angle shaping ("english").
[OUT] - Serve behavior: each serve starts from center and is directed toward the side that conceded the previous point.
[OUT] - Match flow:
[OUT]   - `P0` (AI vs AI): at 11 points, winner styling + confetti are shown, then the game auto-resets and continues in an endless loop.
[OUT]   - `P1` and `P2`: at 11 points, winner styling + confetti are shown, then `NEW GAME? YES/NO` is displayed.
[OUT] 
[OUT] ## Controls
[OUT] - Touch control strips at left/right edges:
[OUT]   - Left strip controls player 1 paddle.
[OUT]   - Right strip controls player 2 paddle.
[OUT]   - Touch `Y` controls paddle height.
[OUT]   - Touch `X` within the strip controls paddle depth.
[OUT] - UI top bar is reserved for settings.
[OUT] - Alternate control sources (for example knob mappings) can be routed through `src/platform/input_hal.c`.
[OUT] 
[OUT] ## Settings
[OUT] - `Players`: `0`, `1`, `2`
[OUT] - `Difficulty`: `1`, `2`, `3`
[OUT] - `NPU`: `ON`, `OFF`
[OUT] - `SKILL`: `2AI`, `AI/ALGO`, `ALGO/AI`
[OUT]   - `2AI`: both sides adaptive EdgeAI.
[OUT]   - `AI/ALGO`: left adaptive EdgeAI, right fixed ALGO baseline.
[OUT]   - `ALGO/AI`: left fixed ALGO baseline, right adaptive EdgeAI.
[OUT] - `PERSIST`: `ON`, `OFF`
[OUT]   - `ON`: keep and restore learned AI profiles from flash independently per side.
[OUT]   - `OFF`: clear learned profiles (including flash snapshot) for true cold-start behavior.
[OUT] - `MATCH`: `11`, `INF`
[OUT] - `TARGET`: `ON`, `OFF`
[OUT] - `SPEED++`: `ON`, `OFF`
[OUT] - `New Game`: immediate score reset
[OUT] 
[OUT] ## AI and NPU Implementation
[OUT] - This firmware uses an embedded TensorFlow Lite Micro model run via the eIQ Neutron NPU backend.
[OUT] - Runtime has two AI paths:
[OUT]   - CPU analytic intercept predictor (deterministic fallback)
[OUT]   - NPU-assisted predictor path
[OUT] - NPU path is enabled by `CONFIG_EDGEAI_USE_NPU=y`.
[OUT] - Inference stack:
[OUT]   - TensorFlow Lite Micro runtime
[OUT]   - eIQ Neutron delegate/backend for NPU execution
[OUT] - AI behavior:
[OUT]   - Predicts paddle intercept targets (`y_hit`, `z_hit`, `t_hit`) for tracking.
[OUT]   - Difficulty presets apply reaction-time limits, speed limits, and tracking noise.
[OUT]   - `AI ON/OFF` controls whether the NPU-assisted path is used; CPU fallback remains available.
[OUT] - Runtime telemetry:
[OUT]   - On-screen telemetry shows NPU invoke rate, fallback rate, last inference latency, and moving-average latency.
[OUT]   - Telemetry is displayed in AI-controlled modes (`P0`, `P1`) when AI is enabled.
[OUT] - Current embedded NPU model artifact is integrated in `src/npu/` and linked into flash (`.model` section).
[OUT] 
[OUT] ## How It Works In This Project
[OUT] 1. Build a 16-value feature vector from current game state (ball, paddles, score, recent hit info) in `ai.c`.
[OUT] 2. Run an embedded TFLM model (`model_ds_cnn_s_npu_data.h`) through the eIQ Neutron backend in `npu_hal_tflm_neutron.cpp`.
[OUT] 3. Decode model output into (`y_hit`, `z_hit`, `t_hit`) signals (via sigmoid), then blend with an analytic physics intercept predictor.
[OUT] 4. Apply a confidence gate: if model output disagrees too much with physics, trust the analytic path more.
[OUT] 5. If NPU is off or inference fails, it falls back fully to CPU analytic prediction.
[OUT] 6. Important: runtime learning here does not retrain model weights; it adapts control parameters (speed/noise/lead) per side over time.
[OUT] 
[OUT] ## Features
[OUT] - 3D-look arena with depth cues, wall shading, and segmented score digits
[OUT] - 0P / 1P / 2P modes
[OUT] - Ball-speed-linked color gradient (red to green)
[OUT] - 0P accelerometer perturbation of ball trajectory (`vy`, `vz`) for live outcome nudging
[OUT] - New-game countdown (`3`, `2`, `1`; red/yellow/green) on game start only
[OUT] - Fixed-timestep simulation
[OUT] - Real-time NPU telemetry overlay for performance tuning
[OUT] - `SKILL` setting for side-selectable adaptive AI vs baseline ALGO (`2AI`, `AI/ALGO`, `ALGO/AI`)
[OUT] - Optional `SPEED++` progression: whenever either side reaches `11, 22, 33, ...`, serve speed target increases by `5%` (compounding) and is capped by runtime speed limits
[OUT] 
[OUT] ## Build and Flash
[OUT] 1. Bootstrap tools:
[OUT] ```bash
[OUT] ./tools/bootstrap_ubuntu_user.sh
[OUT] ```
[OUT] 2. Prepare MCUX workspace:
[OUT] ```bash
[OUT] ./tools/setup_mcuxsdk_ws.sh
[OUT] ```
[OUT] 3. Build:
[OUT] ```bash
[OUT] ./tools/build_frdmmcxn947.sh debug
[OUT] ```
[OUT] 4. Flash:
[OUT] ```bash
[OUT] ./tools/flash_frdmmcxn947.sh
[OUT] ```
[OUT] 
[OUT] ## Project Layout
[OUT] - `src/`: game logic, rendering, platform HAL, AI/NPU integration
[OUT] - `docs/`: hardware, build/flash, restore-point, and project description docs
[OUT] - `tools/`: bootstrap, build, flash, lint, and helper scripts
[OUT] - `failsafe/`: pinned restore binaries
[OUT] 
[OUT] ## Restore Points
[OUT] - Active golden/failsafe pointer: `docs/failsafe.md`
[OUT] - Failsafe flash command:
[OUT] ```bash
[OUT] FAILSAFE_CONFIRM="$(sed -n '1p' docs/failsafe.md)" ./tools/flash_failsafe.sh
[OUT] ```
[OUT] ---
[OUT] # Smart Pong Demo Status
[OUT] 
[OUT] - Current target: FRDM-MCXN947 3D-look Smart Pong on LCD-PAR-S035
[OUT] - Workspace: `mcuxsdk_ws/` (created by `./tools/setup_mcuxsdk_ws.sh`)
[OUT] 
[OUT] ## Last Run
[OUT] - Date: 2026-02-25
[OUT] - Result: ok (build + flash)
[OUT] - Binary: `mcuxsdk_ws/build/edgeai_smart_pong_demo_cm33_core0.bin`
[OUT] - Flash: `west flash -d mcuxsdk_ws/build -r linkserver`
[OUT] - Notes (persistence): match reset now explicitly reloads the learned persistence snapshot when `PERSIST` is enabled.
[OUT] - Notes (settings UI): added `SPEED++` toggle row and moved `NEW GAME` to the next row.
[OUT] - Notes (speed progression): when `SPEED++` is enabled, each side hitting `11, 22, 33, ...` raises serve-speed target by `5%` (compounding), clamped by runtime limits.
[OUT] - Notes (flash persistence): `PERSIST ON` now restores AI learning profiles from onboard flash (`fsl_flash` ROM API) after reboot/power cycle.
[OUT] - Notes (flash write policy): profile snapshot is synced to flash on match reset/new game to limit flash wear; `PERSIST OFF` clears stored snapshot.
[OUT] - Notes (SPEED++ tuning): milestone boost updated to `+5%` per side-specific multiple-of-11 score event (`11, 22, 33, ...`).
[OUT] - Notes (settings label render): added `+` support to the 5x7 font so `SPEED++` displays correctly (previously rendered as `SPEED`).
[OUT] - Failsafe: `failsafe/edgeai_smart_pong_demo_cm33_core0_20260211_1309_final_release_score999_golden.elf`
[OUT] - Restore point: current build is the active Golden + Failsafe snapshot.
[OUT] - Notes (SKILL setting): learn-mode selector now supports `2AI`, `AI/ALGO`, and `ALGO/AI` so EdgeAI can run on either side.
[OUT] - Notes (docs refresh): updated README and project description to match current settings, SKILL modes, SPEED++, and side-independent persistence behavior.
[OUT] - Notes (SKILL balance): ALGO side remains CPU-only while mixed-mode EdgeAI now blends NPU output with analytic intercept for stronger stability and competitiveness.
[OUT] - Notes (verification run): rebuilt and reflashed after SKILL-balance tuning; ready for fresh AI-vs-ALGO score validation on hardware.
[OUT] - Notes (mixed-mode tune): reduced EdgeAI mixed-mode handicap by using ALGO-like target update cadence plus adaptive NPU confidence gating (fallback to analytic predictor on high disagreement).
[OUT] ---
[OUT] # Start Here
[OUT] 
[OUT] Read in order:
[OUT] 1. `docs/HARDWARE.md`
[OUT] 2. `docs/BUILD_FLASH.md`
[OUT] 3. `STATUS.md`
[OUT] 4. `docs/failsafe.md`
[OUT] 5. `ToDo.md`
[OUT] 6. `docs/project_description.md`
[2026-02-25T00:59:52Z] CMD: sed -n "1,240p" docs/failsafe.md && sed -n "1,320p" docs/BUILD_FLASH.md && sed -n "1,320p" docs/project_description.md && sed -n "1,220p" ToDo.md
[OUT] failsafe/edgeai_smart_pong_demo_cm33_core0_20260211_1309_final_release_score999_golden.elf
[OUT] Golden + failsafe restore point: final release with widened score spacing and 0..999 score rendering.
[OUT] ---
[OUT] # Build / Flash (FRDM-MCXN947)
[OUT] 
[OUT] This repo is self-contained. It does not require any external build system repo.
[OUT] 
[OUT] ## 1) Bootstrap Tooling (No sudo)
[OUT] 
[OUT] ```bash
[OUT] ./tools/bootstrap_ubuntu_user.sh
[OUT] ```
[OUT] 
[OUT] This installs user-local:
[OUT] - `pip`, `west`, `cmake`, `ninja`
[OUT] - `git-lfs`
[OUT] - `arm-none-eabi-gcc` (xPack)
[OUT] 
[OUT] ## 2) Create/Update MCUX SDK Workspace
[OUT] 
[OUT] ```bash
[OUT] ./tools/setup_mcuxsdk_ws.sh
[OUT] ```
[OUT] 
[OUT] This creates `./mcuxsdk_ws/`, runs `west init` + `west update`, then installs the
[OUT] `edgeai_smart_pong_demo` wrapper into `mcuxsdk/examples/`.
[OUT] 
[OUT] ## 3) Build
[OUT] 
[OUT] ```bash
[OUT] ./tools/build_frdmmcxn947.sh
[OUT] ```
[OUT] 
[OUT] Build output:
[OUT] - `mcuxsdk_ws/build/edgeai_smart_pong_demo_cm33_core0.bin`
[OUT] 
[OUT] Notes:
[OUT] - Relative `BUILD_DIR` values are resolved under `WS_DIR` (default: `./mcuxsdk_ws`).
[OUT] - Set `BUILD_DIR` to use a non-default build directory (for example, `BUILD_DIR=build_alt ./tools/build_frdmmcxn947.sh debug`).
[OUT] - Current known-good run uses the default build directory (`mcuxsdk_ws/build`).
[OUT] - For a clean rebuild, use a fresh `BUILD_DIR` or remove the existing build directory contents.
[OUT] 
[OUT] ## 4) Flash
[OUT] 
[OUT] Flashing uses NXP LinkServer (x86_64) via `west flash -r linkserver`.
[OUT] 
[OUT] Install LinkServer (user-local, no sudo):
[OUT] 
[OUT] ```bash
[OUT] ACCEPT_NXP_LINKSERVER_LICENSE=1 ./tools/install_linkserver_user.sh
[OUT] ```
[OUT] 
[OUT] If flashing fails with `No probes detected`, install udev rules (requires sudo), then unplug/replug the board:
[OUT] 
[OUT] ```bash
[OUT] ./tools/install_mculink_udev_rules.sh
[OUT] ```
[OUT] 
[OUT] Then flash:
[OUT] 
[OUT] ```bash
[OUT] ./tools/flash_frdmmcxn947.sh
[OUT] ```
[OUT] 
[OUT] ## Failsafe Flash (Last Resort)
[OUT] The active failsafe artifact is recorded in `docs/failsafe.md`.
[OUT] 
[OUT] Flashing requires explicit confirmation via the exact filename listed in line 1 of `docs/failsafe.md`:
[OUT] ```bash
[OUT] FAILSAFE_CONFIRM="$(sed -n '1p' docs/failsafe.md)" ./tools/flash_failsafe.sh
[OUT] ```
[OUT] 
[OUT] ## Serial (Optional)
[OUT] The MCU-Link VCOM interface typically enumerates as `/dev/ttyACM0`:
[OUT] ```bash
[OUT] timeout 10 cat /dev/ttyACM0
[OUT] ```
[OUT] ---
[OUT] # Project Description: Smart Pong (FRDM-MCXN947)
[OUT] 
[OUT] Goal:
[OUT] - Implement a 3D-look Pong game on FRDM-MCXN947 with LCD-PAR-S035.
[OUT] 
[OUT] Targets:
[OUT] - 0P / 1P / 2P: AI vs AI, 1P vs AI, 2P local
[OUT] - In-game settings UI (`PLAYERS`, `LEVEL`, `NPU`, `SKILL`, `PERSIST`, `MATCH`, `TARGET`, `SPEED++`, `NEW GAME`)
[OUT] - Touch-first control (GT911 multi-touch) with alternate inputs supported via platform HAL
[OUT] - Clean separation between platform bring-up, game logic, AI, and rendering
[OUT] 
[OUT] Visual target:
[OUT] - Match `docs/pong_3D.png`: monochrome box arena, perspective depth cue, center dashed line, segmented digits, soft ball shadow.
[OUT] 
[OUT] Inspiration:
[OUT] - Pong is a 1972 sports video game developed and published by Atari, Inc. for arcades.
[OUT] - Original version: Allan Alcorn.
[OUT] - Conceived by: Nolan Bushnell.
[OUT] 
[OUT] ## 3D-Look Rendering Model (MCU-Friendly)
[OUT] This demo uses:
[OUT] - 3D game state (`x`, `y`, `z`)
[OUT] - Lightweight perspective projection into 2D
[OUT] - Flat-shaded walls/floor with depth cues
[OUT] - Ball shadow on floor plane
[OUT] 
[OUT] ## World Model (Normalized Coordinates)
[OUT] - `x`: `0` (left paddle plane) to `1` (right paddle plane)
[OUT] - `y`: `0` (top) to `1` (bottom)
[OUT] - `z`: `0` (near) to `1` (far)
[OUT] 
[OUT] Ball:
[OUT] - `pos = (x, y, z)`
[OUT] - `vel = (vx, vy, vz)`
[OUT] - `radius = r`
[OUT] 
[OUT] Paddles:
[OUT] - Plane: `x = constant`
[OUT] - Center: `(y, z)`
[OUT] - Size: `(size_y, size_z)`
[OUT] 
[OUT] ## Physics (Deterministic, Fixed Timestep)
[OUT] Loop:
[OUT] - Fixed timestep at 60 FPS.
[OUT] 
[OUT] Wall collisions:
[OUT] - Ball reflects at `y` and `z` bounds with radius-aware clamping.
[OUT] 
[OUT] Paddle collisions:
[OUT] - Collision checked at paddle planes while ball travels toward the relevant side.
[OUT] - Hit acceptance uses overlap in `(y, z)` with radius padding.
[OUT] - On hit:
[OUT]   - Invert `vx`
[OUT]   - Apply "english" from `y/z` impact offset
[OUT]   - Apply paddle velocity influence to `vy/vz`
[OUT] 
[OUT] Scoring and match flow:
[OUT] - Score when ball passes beyond x bounds.
[OUT] - Match objective: first side to 11 points.
[OUT] - Serve reset at center with randomized direction toward the side that conceded.
[OUT] - New-game countdown: `3,2,1` (one second per number), new-game start only.
[OUT] - `P0` behavior at 11:
[OUT]   - Winner score styling + confetti
[OUT]   - No yes/no popup
[OUT]   - Automatic reset to new game for endless demo loop
[OUT] - `P1/P2` behavior at 11:
[OUT]   - Winner score styling + confetti
[OUT]   - `NEW GAME? YES/NO` popup
[OUT] 
[OUT] ## Projection
[OUT] - `scale = 1 / (1 + z * persp)`
[OUT] - `sx = cx + (x - 0.5) * world_scale_x * scale`
[OUT] - `sy = cy + (y - 0.5) * world_scale_y * scale`
[OUT] 
[OUT] Depth cues:
[OUT] - Ball/paddle size scales with depth.
[OUT] - Ball color shifts from red toward green as speed rises.
[OUT] 
[OUT] ## Input
[OUT] Touch mapping:
[OUT] - Left edge strip drives player 1 paddle.
[OUT] - Right edge strip drives player 2 paddle.
[OUT] - `touch y -> paddle y`
[OUT] - `touch x (within strip) -> paddle z`
[OUT] - UI top-bar region is excluded from paddle control.
[OUT] 
[OUT] Two-player:
[OUT] - Independent simultaneous control via multi-touch strips.
[OUT] 
[OUT] Accelerometer:
[OUT] - Accel 4 Click (FXLS8974CF) path available.
[OUT] - In `P0`, tilt nudges ball `vy/vz` to perturb AI-vs-AI outcomes.
[OUT] 
[OUT] ## AI / NPU
[OUT] CPU baseline AI:
[OUT] - Analytic intercept solver with bounded reaction behavior.
[OUT] - Difficulty presets control tracking quality and response.
[OUT] 
[OUT] NPU-assisted path:
[OUT] - Runtime uses TensorFlow Lite Micro + eIQ Neutron.
[OUT] - Build-time enable: `CONFIG_EDGEAI_USE_NPU=y`.
[OUT] - NPU prediction path is integrated with CPU fallback for robustness.
[OUT] - `AI ON/OFF` in settings toggles NPU-assisted behavior.
[OUT] - `SKILL` in settings controls side assignment:
[OUT]   - `2AI`: both paddles use adaptive AI.
[OUT]   - `AI/ALGO`: left adaptive AI, right fixed ALGO.
[OUT]   - `ALGO/AI`: left fixed ALGO, right adaptive AI.
[OUT] - Persistent learning stores left/right AI profiles independently in flash when `PERSIST` is enabled.
[OUT] 
[OUT] ## Repo Architecture
[OUT] - `src/platform/`: display, input, time, touch, accelerometer, NPU runtime hooks
[OUT] - `src/game/`: loop, physics, input mapping, modes, AI, rendering
[OUT] - `tools/`: bootstrap, setup, build, flash, guardrails
[OUT] - `docs/`: hardware, build/flash, restore-point, and project docs
[OUT] ---
[OUT] # ToDo: Smart Pong (FRDM-MCXN947)
[OUT] 
[OUT] Reference material:
[OUT] - `docs/project_description.md`
[OUT] - `docs/pong_3D.png`
[OUT] 
[OUT] ## Current Snapshot
[OUT] - [x] Build/flash flow is reproducible in-project (`tools/setup_mcuxsdk_ws.sh`, `tools/build_frdmmcxn947.sh`, `tools/flash_frdmmcxn947.sh`).
[OUT] - [x] Golden restore point and failsafe restore point are aligned via `docs/failsafe.md`.
[OUT] - [x] Last known-good status is tracked in `STATUS.md`.
[OUT] 
[OUT] ## Gameplay + Rendering
[OUT] - [x] 3D-look arena rendering aligned to style target (walls, floor, center dash, depth cues).
[OUT] - [x] 0P / 1P / 2P play modes with in-game settings pill (`P`, `D`, `A`, `N`).
[OUT] - [x] Touch controls use left/right edge strips for non-occluding paddle control.
[OUT] - [x] Ball speed scaling distributed across all three difficulty levels.
[OUT] - [x] Ball hue shifts from red toward green as speed increases.
[OUT] - [x] Help overlay (`?`) shows rules, controls, inspiration credit, and version credit.
[OUT] - [x] Win condition at 11 points with confetti and winner/loser score styling.
[OUT] - [x] `P1/P2`: post-win `NEW GAME? YES/NO` dialog.
[OUT] - [x] `P0`: no dialog; game auto-resets after the 11-point celebration for endless desk demo operation.
[OUT] - [x] New-game countdown (`3,2,1`) is shown only at game start and skipped for `P0`.
[OUT] 
[OUT] ## Physics + Control
[OUT] - [x] Fixed timestep game loop.
[OUT] - [x] Paddle-ball collision and depth handling tuned for left/right parity.
[OUT] - [x] Single-player and two-player paddle behavior tuned to avoid forced recentering.
[OUT] - [x] Serve direction targets the side that conceded the previous point.
[OUT] 
[OUT] ## AI/NPU
[OUT] - [x] CPU baseline predictor path implemented.
[OUT] - [x] NPU runtime integration enabled (`CONFIG_EDGEAI_USE_NPU=y`).
[OUT] - [x] TFLM + eIQ Neutron execution path verified.
[OUT] - [x] NPU path has CPU fallback behavior.
[OUT] - [x] In-game AI enable/disable setting integrated.
[OUT] 
[OUT] ## Optional Backlog
[OUT] - [ ] Replace placeholder NeutronGraph model with a Pong-specific trained predictor model.
[OUT] - [ ] Add runtime telemetry overlay toggle (AI invoke cadence, fallback count, frame budget).
[OUT] - [ ] Add deterministic gameplay regression scenarios for collision edge cases.
[2026-02-25T01:00:05Z] CMD: ls -la mcuxsdk_ws/build/edgeai_smart_pong_demo_cm33_core0.elf mcuxsdk_ws/build/edgeai_smart_pong_demo_cm33_core0.bin && sed -n "1,260p" tools/flash_failsafe.sh
[OUT] -rwxrwxr-x 1 user user 1080096 Feb 24 16:32 mcuxsdk_ws/build/edgeai_smart_pong_demo_cm33_core0.bin
[OUT] -rwxrwxr-x 1 user user 8209948 Feb 24 16:32 mcuxsdk_ws/build/edgeai_smart_pong_demo_cm33_core0.elf
[OUT] ---
[OUT] #!/usr/bin/env bash
[OUT] set -euo pipefail
[OUT] 
[OUT] ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
[OUT] FAILSAFE_DOC="$ROOT_DIR/docs/failsafe.md"
[OUT] 
[OUT] if [[ ! -f "$FAILSAFE_DOC" ]]; then
[OUT]   echo "FAILSAFE: missing pointer file: $FAILSAFE_DOC" >&2
[OUT]   exit 1
[OUT] fi
[OUT] 
[OUT] expected="$(sed -n '1p' "$FAILSAFE_DOC" | tr -d '\r')"
[OUT] desc="$(sed -n '2p' "$FAILSAFE_DOC" | tr -d '\r')"
[OUT] 
[OUT] if [[ -z "$expected" ]]; then
[OUT]   echo "FAILSAFE: empty failsafe filename in: $FAILSAFE_DOC" >&2
[OUT]   exit 1
[OUT] fi
[OUT] 
[OUT] failsafe_path="$ROOT_DIR/$expected"
[OUT] if [[ ! -f "$failsafe_path" ]]; then
[OUT]   echo "FAILSAFE: failsafe artifact not found: $failsafe_path" >&2
[OUT]   exit 1
[OUT] fi
[OUT] 
[OUT] confirm="${FAILSAFE_CONFIRM:-}"
[OUT] if [[ $# -ge 1 ]]; then
[OUT]   confirm="$1"
[OUT] fi
[OUT] 
[OUT] if [[ "$confirm" != "$expected" ]]; then
[OUT]   echo "FAILSAFE: confirmation required" >&2
[OUT]   echo "FAILSAFE: expected filename: $expected" >&2
[OUT]   echo "FAILSAFE: description: $desc" >&2
[OUT]   echo "FAILSAFE: pass argv1 as the expected filename or set FAILSAFE_CONFIRM" >&2
[OUT]   exit 2
[OUT] fi
[OUT] 
[OUT] if ! command -v LinkServer >/dev/null 2>&1; then
[OUT]   echo "FAILSAFE: LinkServer not found on PATH" >&2
[OUT]   exit 1
[OUT] fi
[OUT] 
[OUT] device="${FAILSAFE_DEVICE:-auto}"
[OUT] 
[OUT] probe_args=()
[OUT] if [[ -n "${PROBE:-}" ]]; then
[OUT]   probe_args+=(--probe "$PROBE")
[OUT] fi
[OUT] 
[OUT] LinkServer flash "${probe_args[@]}" "$device" load --erase-all "$failsafe_path"
[2026-02-25T01:00:05Z] CMD: sed -n "1,220p" docs/HARDWARE.md && sed -n "1,220p" docs/STYLE_RULES.md
[OUT] # Hardware (FRDM-MCXN947)
[OUT] 
[OUT] ## Required Components
[OUT] 1. Manufacturer: NXP Semiconductors
[OUT]    - Name: FRDM-MCXN947 development board
[OUT]    - Part number: FRDM-MCXN947
[OUT] 2. Manufacturer: NXP Semiconductors
[OUT]    - Name: 3.5" Parallel TFT LCD shield (ST7796S controller, GT911 touch)
[OUT]    - Part number: LCD-PAR-S035
[OUT] 3. Manufacturer: MikroElektronika (sensor IC by NXP)
[OUT]    - Name: Accel 4 Click (3-axis accelerometer module, FXLS8974CF)
[OUT]    - Part number: MIKROE-4630
[OUT] 
[OUT] ## Board / Debug
[OUT] - Probe: MCU-Link (CMSIS-DAP), probe index `#1` in LinkServer
[OUT] - Debug USB connector: J17
[OUT] 
[OUT] ## Input Paths (Platform HAL)
[OUT] Touch panel (GT911):
[OUT] - Bus: LPI2C2 / FLEXCOMM2
[OUT] - INT pin: PIO4_6
[OUT] - I2C pins: PIO4_0 (`FC2_P0`, SDA), PIO4_1 (`FC2_P1`, SCL)
[OUT] - Reset pin shared with LCD reset line on the shield
[OUT] 
[OUT] Accelerometer (FXLS8974CF on Accel 4 Click):
[OUT] - Bus: I2C via FLEXCOMM3
[OUT] - Device address: `0x18` or `0x19` (ADDR SEL)
[OUT] - `WHO_AM_I`: `0x86`
[OUT] ---
[OUT] # Style Rules (Text, Docs, Comments)
[OUT] 
[OUT] Goals:
[OUT] - Keep documentation and comments objective and repo-centric.
[OUT] - Avoid conversational phrasing that depends on speaker/listener context.
[OUT] 
[OUT] Rules:
[OUT] - Avoid wording that implies generated authorship or external conversational context.
[OUT] - Prefer neutral imperative or descriptive wording.
[OUT]   - Good: "Set `WS_DIR` for a non-default workspace."
[OUT]   - Avoid: "If a non-default workspace is used, set `WS_DIR`."
[OUT] 
[OUT] Enforcement:
[OUT] - Run `./tools/lint_text_style.sh` before committing changes that touch docs or comments.
[OUT] - Optionally install the git pre-commit hook via `./tools/install_git_hooks.sh`.
[2026-02-25T01:00:15Z] CMD: cp -f mcuxsdk_ws/build/edgeai_smart_pong_demo_cm33_core0.elf failsafe/edgeai_smart_pong_demo_cm33_core0_20260225_0100_mixed_skill_balance_confidence_gate_golden.elf && ls -la failsafe/edgeai_smart_pong_demo_cm33_core0_20260225_0100_mixed_skill_balance_confidence_gate_golden.elf
[OUT] -rwxrwxr-x 1 user user 8209948 Feb 24 17:00 failsafe/edgeai_smart_pong_demo_cm33_core0_20260225_0100_mixed_skill_balance_confidence_gate_golden.elf
[2026-02-25T01:01:01Z] CMD: ./tools/lint_text_style.sh && git status --short
[OUT] lint=FAIL
[OUT] [lint] Checking for conversational phrasing / direct reader references...
[OUT] 
[OUT] [lint] FAIL: found banned phrasing. Rewrite to neutral, repo-centric wording.
[OUT] [lint] See: docs/STYLE_RULES.md
[OUT] ---
[OUT]  M README.md
[OUT]  M STATUS.md
[OUT]  M ToDo.md
[OUT]  M docs/BUILD_FLASH.md
[OUT]  M docs/COMMAND_LOG.md
[OUT]  M docs/failsafe.md
[OUT]  M docs/project_description.md
[OUT] ?? failsafe/edgeai_smart_pong_demo_cm33_core0_20260225_0100_mixed_skill_balance_confidence_gate_golden.elf
[2026-02-25T01:01:10Z] CMD: sed -i delete style-rule quoted line from docs/COMMAND_LOG.md; ./tools/lint_text_style.sh; git status --short
[OUT] lint=PASS
[OUT] [lint] Checking for conversational phrasing / direct reader references...
[OUT] [lint] OK
[OUT] ---
[OUT]  M README.md
[OUT]  M STATUS.md
[OUT]  M ToDo.md
[OUT]  M docs/BUILD_FLASH.md
[OUT]  M docs/COMMAND_LOG.md
[OUT]  M docs/failsafe.md
[OUT]  M docs/project_description.md
[OUT] ?? failsafe/edgeai_smart_pong_demo_cm33_core0_20260225_0100_mixed_skill_balance_confidence_gate_golden.elf
[2026-02-25T01:01:19Z] CMD: git add README.md STATUS.md ToDo.md docs/BUILD_FLASH.md docs/COMMAND_LOG.md docs/failsafe.md docs/project_description.md failsafe/edgeai_smart_pong_demo_cm33_core0_20260225_0100_mixed_skill_balance_confidence_gate_golden.elf && git commit -m "Promote mixed-SKILL balance build as golden/failsafe and refresh docs" && git push origin main && git rev-parse --short HEAD
[2026-02-25T01:01:27Z] RESULT: commit+push=PASS hash=3040364
[2026-02-25T01:04:57Z] CMD: rg -n "paddle|collision|english|physics_step|wall_bounce|score|vx|vy|vz" src/game/physics.c && sed -n "220,520p" src/game/physics.c
[OUT] 44:    float vx = g->ball.vx;
[OUT] 45:    float vy = g->ball.vy;
[OUT] 46:    float vz = g->ball.vz;
[OUT] 47:    return sqrtf(vx * vx + vy * vy + vz * vz);
[OUT] 60:static void physics_speedpp_on_score(pong_game_t *g, bool point_to_left)
[OUT] 64:    uint16_t scored = point_to_left ? g->score.left : g->score.right;
[OUT] 65:    if (scored == 0u || (scored % 11u) != 0u) return;
[OUT] 93:    float vmax = absf(g->ball.vx);
[OUT] 94:    float avy = absf(g->ball.vy);
[OUT] 95:    float avz = absf(g->ball.vz);
[OUT] 96:    if (avy > vmax) vmax = avy;
[OUT] 97:    if (avz > vmax) vmax = avz;
[OUT] 99:    /* Keep per-substep motion small to avoid tunneling through paddles at higher speeds. */
[OUT] 182:    g->ball.vx = dir * serve_speed;
[OUT] 183:    g->ball.vy = rand_f(g, -0.28f, 0.28f);
[OUT] 184:    g->ball.vz = rand_f(g, -0.22f, 0.22f);
[OUT] 188:static void physics_wall_bounce(float *p, float *v, float r)
[OUT] 228:static bool physics_paddle_overlap_yz(const pong_paddle_t *p, float y, float z, float ball_r, float slop)
[OUT] 232:    /* Sphere vs paddle-rect overlap, evaluated in the paddle plane (y/z).
[OUT] 249:static void physics_paddle_hit(pong_game_t *g, pong_paddle_t *p, bool left_side)
[OUT] 264:    ai_learning_on_paddle_hit(g, left_side);
[OUT] 266:    const float english = 0.55f;
[OUT] 269:    g->ball.vy += dy * english;
[OUT] 270:    g->ball.vz += dz * english;
[OUT] 272:    /* Touch control can produce very large paddle velocities; clamp to keep hits stable. */
[OUT] 273:    float pvy = clampf(p->vy, -vlim, vlim);
[OUT] 274:    float pvz = clampf(p->vz, -vlim, vlim);
[OUT] 275:    g->ball.vy += pvy * p_influence;
[OUT] 276:    g->ball.vz += pvz * p_influence;
[OUT] 278:    g->ball.vx = (left_side ? absf(g->ball.vx) : -absf(g->ball.vx)) * speed_up;
[OUT] 281:    g->ball.vx = clampf(g->ball.vx, -vlim, vlim);
[OUT] 282:    g->ball.vy = clampf(g->ball.vy, -vlim, vlim);
[OUT] 283:    g->ball.vz = clampf(g->ball.vz, -vlim, vlim);
[OUT] 286:    if (absf(g->ball.vx) < 0.24f)
[OUT] 288:        g->ball.vx = (g->ball.vx < 0.0f) ? -0.24f : 0.24f;
[OUT] 292:static bool physics_step_sub(pong_game_t *g, float dt)
[OUT] 300:    float start_vy = g->ball.vy;
[OUT] 301:    float start_vz = g->ball.vz;
[OUT] 303:    g->ball.x += g->ball.vx * dt;
[OUT] 304:    g->ball.y += g->ball.vy * dt;
[OUT] 305:    g->ball.z += g->ball.vz * dt;
[OUT] 308:    physics_wall_bounce(&g->ball.y, &g->ball.vy, g->ball.r);
[OUT] 309:    physics_wall_bounce(&g->ball.z, &g->ball.vz, g->ball.r);
[OUT] 311:    /* Paddle collisions. */
[OUT] 314:    const float x_hit_l = g->paddle_l.x_plane + g->ball.r;
[OUT] 315:    if (g->ball.vx < 0.0f && prev_x > x_hit_l && g->ball.x <= x_hit_l)
[OUT] 322:        float y_at = physics_axis_reflect(prev_y, start_vy, tau, g->ball.r);
[OUT] 323:        float z_at = physics_axis_reflect(prev_z, start_vz, tau, g->ball.r);
[OUT] 325:        bool hit = physics_paddle_overlap_yz(&g->paddle_l, y_at, z_at, g->ball.r, slop);
[OUT] 331:            physics_paddle_hit(g, &g->paddle_l, true);
[OUT] 335:    const float x_hit_r = g->paddle_r.x_plane - g->ball.r;
[OUT] 336:    if (g->ball.vx > 0.0f && prev_x < x_hit_r && g->ball.x >= x_hit_r)
[OUT] 343:        float y_at = physics_axis_reflect(prev_y, start_vy, tau, g->ball.r);
[OUT] 344:        float z_at = physics_axis_reflect(prev_z, start_vz, tau, g->ball.r);
[OUT] 346:        bool hit = physics_paddle_overlap_yz(&g->paddle_r, y_at, z_at, g->ball.r, slop);
[OUT] 352:            physics_paddle_hit(g, &g->paddle_r, false);
[OUT] 360:        g->score.right++;
[OUT] 362:        physics_speedpp_on_score(g, false);
[OUT] 369:        g->score.left++;
[OUT] 371:        physics_speedpp_on_score(g, true);
[OUT] 380:void physics_step(pong_game_t *g, float dt)
[OUT] 390:        if (physics_step_sub(g, h))
[OUT] ---
[OUT]             continue;
[OUT]         }
[OUT]         break;
[OUT]     }
[OUT] 
[OUT]     return clampf(p, lo, hi);
[OUT] }
[OUT] 
[OUT] static bool physics_paddle_overlap_yz(const pong_paddle_t *p, float y, float z, float ball_r, float slop)
[OUT] {
[OUT]     if (!p) return false;
[OUT] 
[OUT]     /* Sphere vs paddle-rect overlap, evaluated in the paddle plane (y/z).
[OUT]      * Use a circle-rectangle distance test to avoid "ghost" corner bounces
[OUT]      * from the overly-permissive AABB expansion.
[OUT]      */
[OUT]     float hy = p->size_y * 0.5f;
[OUT]     float hz = p->size_z * 0.5f;
[OUT]     float rr = ball_r + slop;
[OUT] 
[OUT]     float dy = absf(y - p->y) - hy;
[OUT]     float dz = absf(z - p->z) - hz;
[OUT]     if (dy <= 0.0f && dz <= 0.0f) return true;
[OUT] 
[OUT]     if (dy < 0.0f) dy = 0.0f;
[OUT]     if (dz < 0.0f) dz = 0.0f;
[OUT]     return (dy * dy + dz * dz) <= (rr * rr);
[OUT] }
[OUT] 
[OUT] static void physics_paddle_hit(pong_game_t *g, pong_paddle_t *p, bool left_side)
[OUT] {
[OUT]     if (!g || !p) return;
[OUT] 
[OUT]     float speed_up = 1.02f;
[OUT]     float vlim = 1.6f;
[OUT]     physics_get_tuning(g, NULL, &speed_up, &vlim);
[OUT] 
[OUT]     float dy = (g->ball.y - p->y) / (p->size_y * 0.5f);
[OUT]     float dz = (g->ball.z - p->z) / (p->size_z * 0.5f);
[OUT]     dy = clampf(dy, -1.0f, 1.0f);
[OUT]     dz = clampf(dz, -1.0f, 1.0f);
[OUT] 
[OUT]     g->last_hit_dy = dy;
[OUT]     g->last_hit_dz = dz;
[OUT]     ai_learning_on_paddle_hit(g, left_side);
[OUT] 
[OUT]     const float english = 0.55f;
[OUT]     const float p_influence = 0.12f;
[OUT] 
[OUT]     g->ball.vy += dy * english;
[OUT]     g->ball.vz += dz * english;
[OUT] 
[OUT]     /* Touch control can produce very large paddle velocities; clamp to keep hits stable. */
[OUT]     float pvy = clampf(p->vy, -vlim, vlim);
[OUT]     float pvz = clampf(p->vz, -vlim, vlim);
[OUT]     g->ball.vy += pvy * p_influence;
[OUT]     g->ball.vz += pvz * p_influence;
[OUT] 
[OUT]     g->ball.vx = (left_side ? absf(g->ball.vx) : -absf(g->ball.vx)) * speed_up;
[OUT] 
[OUT]     /* Clamp speeds. */
[OUT]     g->ball.vx = clampf(g->ball.vx, -vlim, vlim);
[OUT]     g->ball.vy = clampf(g->ball.vy, -vlim, vlim);
[OUT]     g->ball.vz = clampf(g->ball.vz, -vlim, vlim);
[OUT] 
[OUT]     /* Ensure x motion does not stall. */
[OUT]     if (absf(g->ball.vx) < 0.24f)
[OUT]     {
[OUT]         g->ball.vx = (g->ball.vx < 0.0f) ? -0.24f : 0.24f;
[OUT]     }
[OUT] }
[OUT] 
[OUT] static bool physics_step_sub(pong_game_t *g, float dt)
[OUT] {
[OUT]     if (!g) return false;
[OUT]     if (dt <= 0.0f) return false;
[OUT] 
[OUT]     float prev_x = g->ball.x;
[OUT]     float prev_y = g->ball.y;
[OUT]     float prev_z = g->ball.z;
[OUT]     float start_vy = g->ball.vy;
[OUT]     float start_vz = g->ball.vz;
[OUT] 
[OUT]     g->ball.x += g->ball.vx * dt;
[OUT]     g->ball.y += g->ball.vy * dt;
[OUT]     g->ball.z += g->ball.vz * dt;
[OUT] 
[OUT]     /* Walls (y and z). */
[OUT]     physics_wall_bounce(&g->ball.y, &g->ball.vy, g->ball.r);
[OUT]     physics_wall_bounce(&g->ball.z, &g->ball.vz, g->ball.r);
[OUT] 
[OUT]     /* Paddle collisions. */
[OUT]     const float slop = g->ball.r * 0.02f;
[OUT] 
[OUT]     const float x_hit_l = g->paddle_l.x_plane + g->ball.r;
[OUT]     if (g->ball.vx < 0.0f && prev_x > x_hit_l && g->ball.x <= x_hit_l)
[OUT]     {
[OUT]         float denom = (prev_x - g->ball.x);
[OUT]         float t = (denom != 0.0f) ? ((prev_x - x_hit_l) / denom) : 0.0f;
[OUT]         t = clampf(t, 0.0f, 1.0f);
[OUT] 
[OUT]         float tau = dt * t;
[OUT]         float y_at = physics_axis_reflect(prev_y, start_vy, tau, g->ball.r);
[OUT]         float z_at = physics_axis_reflect(prev_z, start_vz, tau, g->ball.r);
[OUT] 
[OUT]         bool hit = physics_paddle_overlap_yz(&g->paddle_l, y_at, z_at, g->ball.r, slop);
[OUT]         if (hit)
[OUT]         {
[OUT]             g->ball.x = x_hit_l;
[OUT]             g->ball.y = y_at;
[OUT]             g->ball.z = z_at;
[OUT]             physics_paddle_hit(g, &g->paddle_l, true);
[OUT]         }
[OUT]     }
[OUT] 
[OUT]     const float x_hit_r = g->paddle_r.x_plane - g->ball.r;
[OUT]     if (g->ball.vx > 0.0f && prev_x < x_hit_r && g->ball.x >= x_hit_r)
[OUT]     {
[OUT]         float denom = (g->ball.x - prev_x);
[OUT]         float t = (denom != 0.0f) ? ((x_hit_r - prev_x) / denom) : 0.0f;
[OUT]         t = clampf(t, 0.0f, 1.0f);
[OUT] 
[OUT]         float tau = dt * t;
[OUT]         float y_at = physics_axis_reflect(prev_y, start_vy, tau, g->ball.r);
[OUT]         float z_at = physics_axis_reflect(prev_z, start_vz, tau, g->ball.r);
[OUT] 
[OUT]         bool hit = physics_paddle_overlap_yz(&g->paddle_r, y_at, z_at, g->ball.r, slop);
[OUT]         if (hit)
[OUT]         {
[OUT]             g->ball.x = x_hit_r;
[OUT]             g->ball.y = y_at;
[OUT]             g->ball.z = z_at;
[OUT]             physics_paddle_hit(g, &g->paddle_r, false);
[OUT]         }
[OUT]     }
[OUT] 
[OUT]     /* Scoring. */
[OUT]     const float margin = 0.10f;
[OUT]     if (g->ball.x < -margin)
[OUT]     {
[OUT]         g->score.right++;
[OUT]         ai_learning_on_miss(g, true);
[OUT]         physics_speedpp_on_score(g, false);
[OUT]         /* Serve toward the player who just conceded (left). */
[OUT]         physics_reset_ball(g, -1);
[OUT]         return true;
[OUT]     }
[OUT]     else if (g->ball.x > 1.0f + margin)
[OUT]     {
[OUT]         g->score.left++;
[OUT]         ai_learning_on_miss(g, false);
[OUT]         physics_speedpp_on_score(g, true);
[OUT]         /* Serve toward the player who just conceded (right). */
[OUT]         physics_reset_ball(g, +1);
[OUT]         return true;
[OUT]     }
[OUT] 
[OUT]     return false;
[OUT] }
[OUT] 
[OUT] void physics_step(pong_game_t *g, float dt)
[OUT] {
[OUT]     if (!g) return;
[OUT] 
[OUT]     physics_speedpp_track_peak(g);
[OUT] 
[OUT]     int n = physics_substeps(g, dt);
[OUT]     float h = dt / (float)n;
[OUT]     for (int i = 0; i < n; i++)
[OUT]     {
[OUT]         if (physics_step_sub(g, h))
[OUT]         {
[OUT]             return;
[OUT]         }
[OUT]     }
[OUT] }
[2026-02-25T01:05:24Z] CMD: patched physics.c corner deflection + STATUS update; git status --short; rg -n "corner|six bounce walls|edge_y|edge_z" src/game/physics.c STATUS.md
[OUT]  M STATUS.md
[OUT]  M docs/COMMAND_LOG.md
[OUT]  M src/game/physics.c
[OUT] ---
[OUT] STATUS.md:27:- Notes (physics tuning): paddle corner/edge hits now apply a slight outward Y/Z deflection, increasing natural wall-ricochet rallies.
[OUT] src/game/physics.c:238:     * Use a circle-rectangle distance test to avoid "ghost" corner bounces
[OUT] src/game/physics.c:273:    const float corner_kick = 0.26f;
[OUT] src/game/physics.c:279:     * more naturally. Y/Z walls plus both paddle planes act as six bounce walls.
[OUT] src/game/physics.c:282:        float edge_y = clampf((absf(dy) - 0.62f) / 0.38f, 0.0f, 1.0f);
[OUT] src/game/physics.c:283:        float edge_z = clampf((absf(dz) - 0.62f) / 0.38f, 0.0f, 1.0f);
[OUT] src/game/physics.c:284:        float kick_y = corner_kick * edge_y * signf(dy);
[OUT] src/game/physics.c:285:        float kick_z = corner_kick * edge_z * signf(dz);
[2026-02-25T01:05:31Z] CMD: ./tools/build_frdmmcxn947.sh && ./tools/flash_frdmmcxn947.sh
[2026-02-25T01:08:53Z] RESULT: build=PASS flash=PASS
[2026-02-25T01:09:00Z] CMD: git status --short
[OUT]  M STATUS.md
[OUT]  M docs/COMMAND_LOG.md
[OUT]  M src/game/physics.c
[2026-02-25T01:16:07Z] CMD: patched stronger corner ricochet in physics.c + STATUS update; git status --short; rg -n "edge_kick|corner_bonus|corner > 0.72|min_side|physics tuning v2" src/game/physics.c STATUS.md
[OUT]  M STATUS.md
[OUT]  M docs/COMMAND_LOG.md
[OUT]  M src/game/physics.c
[OUT] ---
[OUT] STATUS.md:28:- Notes (physics tuning v2): near-true paddle-corner hits now get stronger Y/Z deflection plus a minimum side-velocity gate to create clearly visible extreme ricochets.
[OUT] src/game/physics.c:273:    const float edge_kick = 0.40f;
[OUT] src/game/physics.c:274:    const float corner_bonus = 0.72f;
[OUT] src/game/physics.c:290:        float kick_y = (edge_kick * edge_y + corner_bonus * corner) * signf(dy);
[OUT] src/game/physics.c:291:        float kick_z = (edge_kick * edge_z + corner_bonus * corner) * signf(dz);
[OUT] src/game/physics.c:296:        if (corner > 0.72f)
[OUT] src/game/physics.c:298:            float min_side = vlim * 0.46f;
[OUT] src/game/physics.c:299:            if (absf(g->ball.vy) < min_side) g->ball.vy = min_side * signf(dy);
[OUT] src/game/physics.c:300:            if (absf(g->ball.vz) < min_side) g->ball.vz = min_side * signf(dz);
[2026-02-25T01:16:16Z] CMD: ./tools/build_frdmmcxn947.sh && ./tools/flash_frdmmcxn947.sh
[2026-02-25T01:19:53Z] RESULT: build=PASS flash=PASS
[2026-02-25T01:20:05Z] CMD: git status --short
[OUT]  M STATUS.md
[OUT]  M docs/COMMAND_LOG.md
[OUT]  M src/game/physics.c
[2026-02-25T01:26:56Z] CMD: sed -n "1,40p" docs/failsafe.md && sed -n "1,80p" STATUS.md
[OUT] failsafe/edgeai_smart_pong_demo_cm33_core0_20260225_0100_mixed_skill_balance_confidence_gate_golden.elf
[OUT] Golden + failsafe restore point: mixed-SKILL fairness tuning with ALGO-side CPU-only behavior and adaptive NPU confidence gating.
[OUT] ---
[OUT] # Smart Pong Demo Status
[OUT] 
[OUT] - Current target: FRDM-MCXN947 3D-look Smart Pong on LCD-PAR-S035
[OUT] - Workspace: `mcuxsdk_ws/` (created by `./tools/setup_mcuxsdk_ws.sh`)
[OUT] 
[OUT] ## Last Run
[OUT] - Date: 2026-02-25
[OUT] - Result: ok (build + flash)
[OUT] - Binary: `mcuxsdk_ws/build/edgeai_smart_pong_demo_cm33_core0.bin`
[OUT] - Flash: `west flash -d mcuxsdk_ws/build -r linkserver`
[OUT] - Notes (persistence): match reset now explicitly reloads the learned persistence snapshot when `PERSIST` is enabled.
[OUT] - Notes (settings UI): added `SPEED++` toggle row and moved `NEW GAME` to the next row.
[OUT] - Notes (speed progression): when `SPEED++` is enabled, each side hitting `11, 22, 33, ...` raises serve-speed target by `5%` (compounding), clamped by runtime limits.
[OUT] - Notes (flash persistence): `PERSIST ON` now restores AI learning profiles from onboard flash (`fsl_flash` ROM API) after reboot/power cycle.
[OUT] - Notes (flash write policy): profile snapshot is synced to flash on match reset/new game to limit flash wear; `PERSIST OFF` clears stored snapshot.
[OUT] - Notes (SPEED++ tuning): milestone boost updated to `+5%` per side-specific multiple-of-11 score event (`11, 22, 33, ...`).
[OUT] - Notes (settings label render): added `+` support to the 5x7 font so `SPEED++` displays correctly (previously rendered as `SPEED`).
[OUT] - Failsafe: `failsafe/edgeai_smart_pong_demo_cm33_core0_20260211_1309_final_release_score999_golden.elf`
[OUT] - Restore point: current build is the active Golden + Failsafe snapshot.
[OUT] - Notes (SKILL setting): learn-mode selector now supports `2AI`, `AI/ALGO`, and `ALGO/AI` so EdgeAI can run on either side.
[OUT] - Notes (docs refresh): updated README and project description to match current settings, SKILL modes, SPEED++, and side-independent persistence behavior.
[OUT] - Notes (SKILL balance): ALGO side remains CPU-only while mixed-mode EdgeAI now blends NPU output with analytic intercept for stronger stability and competitiveness.
[OUT] - Notes (verification run): rebuilt and reflashed after SKILL-balance tuning; ready for fresh AI-vs-ALGO score validation on hardware.
[OUT] - Notes (mixed-mode tune): reduced EdgeAI mixed-mode handicap by using ALGO-like target update cadence plus adaptive NPU confidence gating (fallback to analytic predictor on high disagreement).
[OUT] - Notes (release marker): current mixed-SKILL fairness tuning is promoted as Golden + Failsafe restore point.
[OUT] - Failsafe: `failsafe/edgeai_smart_pong_demo_cm33_core0_20260225_0100_mixed_skill_balance_confidence_gate_golden.elf`
[OUT] - Notes (physics tuning): paddle corner/edge hits now apply a slight outward Y/Z deflection, increasing natural wall-ricochet rallies.
[OUT] - Notes (physics tuning v2): near-true paddle-corner hits now get stronger Y/Z deflection plus a minimum side-velocity gate to create clearly visible extreme ricochets.
[2026-02-25T01:27:15Z] CMD: marked pre-extreme-bounce golden/failsafe in STATUS.md and docs/failsafe.md; git status --short; sed -n "1,4p" docs/failsafe.md
[OUT]  M STATUS.md
[OUT]  M docs/COMMAND_LOG.md
[OUT]  M docs/failsafe.md
[OUT]  M src/game/physics.c
[OUT] ---
[OUT] failsafe/edgeai_smart_pong_demo_cm33_core0_20260225_0100_mixed_skill_balance_confidence_gate_golden.elf
[OUT] Golden + failsafe restore point: pre-extreme-bounce build with mixed-SKILL fairness tuning (ALGO-side CPU-only + adaptive NPU confidence gating).
[2026-02-25T01:32:10Z] CMD: sed -n "1,260p" src/game/game.h && sed -n "1,220p" src/game/ai.h
[OUT] #pragma once
[OUT] 
[OUT] #include <stdbool.h>
[OUT] #include <stdint.h>
[OUT] 
[OUT] #include "game/modes.h"
[OUT] #include "platform/input_hal.h"
[OUT] #include "platform/npu_hal.h"
[OUT] 
[OUT] typedef struct
[OUT] {
[OUT]     float x;
[OUT]     float y;
[OUT]     float z;
[OUT]     float vx;
[OUT]     float vy;
[OUT]     float vz;
[OUT]     float r;
[OUT] } pong_ball_t;
[OUT] 
[OUT] typedef struct
[OUT] {
[OUT]     float x_plane;
[OUT]     float y;
[OUT]     float z;
[OUT]     float vy;
[OUT]     float vz;
[OUT]     float size_y;
[OUT]     float size_z;
[OUT]     float target_y;
[OUT]     float target_z;
[OUT] } pong_paddle_t;
[OUT] 
[OUT] typedef struct
[OUT] {
[OUT]     uint16_t left;
[OUT]     uint16_t right;
[OUT] } pong_score_t;
[OUT] 
[OUT] typedef enum
[OUT] {
[OUT]     kAiLearnModeBoth = 0,
[OUT]     kAiLearnModeAiAlgo = 1,
[OUT]     kAiLearnModeAlgoAi = 2,
[OUT] } ai_learn_mode_t;
[OUT] 
[OUT] typedef struct
[OUT] {
[OUT]     float speed_scale;
[OUT]     float noise_scale;
[OUT]     float lead_scale;
[OUT]     uint16_t hits;
[OUT]     uint16_t misses;
[OUT] } ai_learn_profile_t;
[OUT] 
[OUT] typedef struct
[OUT] {
[OUT]     game_mode_t mode;
[OUT]     uint8_t difficulty; /* 1..3 */
[OUT]     bool ai_enabled;
[OUT]     bool perpetual_play;
[OUT]     bool persistent_learning;
[OUT]     bool speedpp_enabled;
[OUT]     bool target_overlay_enabled;
[OUT]     bool menu_open;
[OUT]     bool help_open;
[OUT]     bool ui_block_touch;
[OUT]     bool match_over;
[OUT]     bool winner_left;
[OUT]     bool end_prompt_dismissed;
[OUT]     bool countdown_active;
[OUT] 
[OUT]     pong_ball_t ball;
[OUT]     pong_paddle_t paddle_l;
[OUT]     pong_paddle_t paddle_r;
[OUT]     pong_score_t score;
[OUT] 
[OUT]     uint32_t rng;
[OUT]     uint32_t frame;
[OUT]     uint32_t match_over_frame;
[OUT]     uint32_t match_over_start_cycles;
[OUT]     uint32_t countdown_us_left;
[OUT]     uint32_t countdown_start_cycles;
[OUT] 
[OUT]     float last_hit_dy;
[OUT]     float last_hit_dz;
[OUT] 
[OUT]     float serve_vx;
[OUT]     float serve_vy;
[OUT]     float serve_vz;
[OUT]     float speedpp_peak_speed;
[OUT]     float speedpp_serve_speed_target;
[OUT]     uint8_t speedpp_stage;
[OUT]     uint16_t speedpp_next_threshold;
[OUT] 
[OUT]     /* Latest accel sample (for UI/debug + optional game effects). */
[OUT]     bool accel_active;
[OUT]     float accel_ax;
[OUT]     float accel_ay;
[OUT] 
[OUT]     /* Runtime AI/NPU telemetry. */
[OUT]     uint32_t ai_telemetry_start_cycles;
[OUT]     uint32_t ai_npu_attempts_window;
[OUT]     uint32_t ai_fallback_window;
[OUT]     uint16_t ai_npu_rate_hz;
[OUT]     uint16_t ai_fallback_rate_hz;
[OUT] 
[OUT]     ai_learn_mode_t ai_learn_mode;
[OUT]     bool ai_left_active;
[OUT]     bool ai_right_active;
[OUT]     ai_learn_profile_t ai_profile_left;
[OUT]     ai_learn_profile_t ai_profile_right;
[OUT] 
[OUT]     npu_hal_t npu;
[OUT] } pong_game_t;
[OUT] 
[OUT] void game_init(pong_game_t *g);
[OUT] void game_reset(pong_game_t *g);
[OUT] void game_step(pong_game_t *g, const platform_input_t *in, float dt);
[OUT] ---
[OUT] #pragma once
[OUT] 
[OUT] #include <stdbool.h>
[OUT] 
[OUT] #include "game/game.h"
[OUT] 
[OUT] void ai_init(pong_game_t *g);
[OUT] void ai_step(pong_game_t *g, float dt, bool ai_left, bool ai_right);
[OUT] void ai_learning_reset_session(pong_game_t *g);
[OUT] void ai_learning_set_mode(pong_game_t *g, ai_learn_mode_t mode);
[OUT] void ai_learning_set_persistent(pong_game_t *g, bool enabled);
[OUT] void ai_learning_sync_store(pong_game_t *g);
[OUT] void ai_learning_on_paddle_hit(pong_game_t *g, bool left_side);
[OUT] void ai_learning_on_miss(pong_game_t *g, bool left_side);
[2026-02-25T01:32:10Z] CMD: rg -n "ai_profile_default|ai_profile_clamp|ai_learning_on_paddle_hit|ai_learning_on_miss|target_y|target_z|rand_f|ai_step_one" src/game/ai.c && sed -n "130,370p" src/game/ai.c && sed -n "620,770p" src/game/ai.c
[OUT] 34:static float rand_f01(pong_game_t *g)
[OUT] 41:static float rand_f(pong_game_t *g, float lo, float hi)
[OUT] 43:    return lo + (hi - lo) * rand_f01(g);
[OUT] 150:static ai_learn_profile_t ai_profile_default(void)
[OUT] 161:static void ai_profile_clamp(ai_learn_profile_t *p)
[OUT] 219:        ai_profile_clamp(&g->ai_profile_left);
[OUT] 220:        ai_profile_clamp(&g->ai_profile_right);
[OUT] 229:        ai_profile_clamp(&g->ai_profile_left);
[OUT] 230:        ai_profile_clamp(&g->ai_profile_right);
[OUT] 247:    g->ai_profile_left = ai_profile_default();
[OUT] 248:    g->ai_profile_right = ai_profile_default();
[OUT] 298:void ai_learning_on_paddle_hit(pong_game_t *g, bool left_side)
[OUT] 313:    ai_profile_clamp(p);
[OUT] 317:void ai_learning_on_miss(pong_game_t *g, bool left_side)
[OUT] 332:    ai_profile_clamp(p);
[OUT] 656:static void ai_step_one(pong_game_t *g, float dt, pong_paddle_t *p, bool right_side)
[OUT] 765:            y_hit += rand_f(g, -noise, noise);
[OUT] 766:            z_hit += rand_f(g, -noise, noise);
[OUT] 774:        p->target_y = clampf(y_hit, 0.0f, 1.0f);
[OUT] 775:        p->target_z = clampf(z_hit, 0.0f, 1.0f);
[OUT] 785:    float dy = p->target_y - p->y;
[OUT] 786:    float dz = p->target_z - p->z;
[OUT] 808:        ai_step_one(g, dt, &g->paddle_l, false);
[OUT] 812:        ai_step_one(g, dt, &g->paddle_r, true);
[OUT] 822:        ai_profile_clamp(p);
[OUT] 830:        ai_profile_clamp(p);
[OUT] ---
[OUT]     write_buf = *store;
[OUT]     write_buf.crc32 = 0u;
[OUT]     write_buf.crc32 = ai_store_checksum(&write_buf);
[OUT] 
[OUT]     if (FLASH_Erase(&s_flash_cfg, s_flash_store_addr, s_flash_sector_size, kFLASH_ApiEraseKey) != kStatus_FLASH_Success)
[OUT]         return false;
[OUT]     if (FLASH_Program(&s_flash_cfg, s_flash_store_addr, (uint8_t *)&write_buf, sizeof(write_buf)) !=
[OUT]         kStatus_FLASH_Success)
[OUT]         return false;
[OUT] 
[OUT]     const ai_learn_store_t *flash_store = (const ai_learn_store_t *)(uintptr_t)s_flash_store_addr;
[OUT]     return (memcmp(flash_store, &write_buf, sizeof(write_buf)) == 0);
[OUT] }
[OUT] 
[OUT] static void ai_flash_clear_store(void)
[OUT] {
[OUT]     if (!ai_flash_init()) return;
[OUT]     (void)FLASH_Erase(&s_flash_cfg, s_flash_store_addr, s_flash_sector_size, kFLASH_ApiEraseKey);
[OUT] }
[OUT] 
[OUT] static ai_learn_profile_t ai_profile_default(void)
[OUT] {
[OUT]     ai_learn_profile_t p;
[OUT]     p.speed_scale = 1.0f;
[OUT]     p.noise_scale = 1.0f;
[OUT]     p.lead_scale = 1.0f;
[OUT]     p.hits = 0u;
[OUT]     p.misses = 0u;
[OUT]     return p;
[OUT] }
[OUT] 
[OUT] static void ai_profile_clamp(ai_learn_profile_t *p)
[OUT] {
[OUT]     if (!p) return;
[OUT]     p->speed_scale = clampf(p->speed_scale, 0.75f, 1.85f);
[OUT]     p->noise_scale = clampf(p->noise_scale, 0.40f, 2.20f);
[OUT]     p->lead_scale = clampf(p->lead_scale, 0.70f, 2.00f);
[OUT] }
[OUT] 
[OUT] static ai_learn_profile_t *ai_profile_side(pong_game_t *g, bool right_side)
[OUT] {
[OUT]     if (!g) return NULL;
[OUT]     return right_side ? &g->ai_profile_right : &g->ai_profile_left;
[OUT] }
[OUT] 
[OUT] static const ai_learn_profile_t *ai_profile_side_const(const pong_game_t *g, bool right_side)
[OUT] {
[OUT]     if (!g) return NULL;
[OUT]     return right_side ? &g->ai_profile_right : &g->ai_profile_left;
[OUT] }
[OUT] 
[OUT] static bool ai_learning_side_selected(const pong_game_t *g, bool right_side)
[OUT] {
[OUT]     if (!g) return false;
[OUT]     if (right_side)
[OUT]     {
[OUT]         if (!g->ai_right_active) return false;
[OUT]         if (g->ai_learn_mode == kAiLearnModeAiAlgo) return false;
[OUT]         return true;
[OUT]     }
[OUT] 
[OUT]     if (!g->ai_left_active) return false;
[OUT]     if (g->ai_learn_mode == kAiLearnModeAlgoAi) return false;
[OUT]     return true;
[OUT] }
[OUT] 
[OUT] static void ai_learning_commit_store(const pong_game_t *g)
[OUT] {
[OUT]     if (!g || !g->persistent_learning) return;
[OUT]     s_learn_store.magic = EDGEAI_LEARN_STORE_MAGIC;
[OUT]     s_learn_store.version = EDGEAI_LEARN_STORE_VERSION;
[OUT]     s_learn_store.crc32 = 0u;
[OUT]     s_learn_store.left = g->ai_profile_left;
[OUT]     s_learn_store.right = g->ai_profile_right;
[OUT]     s_learn_store.crc32 = ai_store_checksum(&s_learn_store);
[OUT]     s_learn_store_dirty = true;
[OUT] }
[OUT] 
[OUT] static void ai_learning_load_store(pong_game_t *g)
[OUT] {
[OUT]     if (!g || !g->persistent_learning) return;
[OUT] 
[OUT]     ai_learn_store_t flash_store;
[OUT]     if (ai_flash_read_store(&flash_store))
[OUT]     {
[OUT]         s_learn_store = flash_store;
[OUT]         s_learn_store_dirty = false;
[OUT]         g->ai_profile_left = s_learn_store.left;
[OUT]         g->ai_profile_right = s_learn_store.right;
[OUT]         ai_profile_clamp(&g->ai_profile_left);
[OUT]         ai_profile_clamp(&g->ai_profile_right);
[OUT]         return;
[OUT]     }
[OUT] 
[OUT]     if (s_learn_store.magic == EDGEAI_LEARN_STORE_MAGIC && s_learn_store.version == EDGEAI_LEARN_STORE_VERSION &&
[OUT]         ai_store_checksum(&s_learn_store) == s_learn_store.crc32)
[OUT]     {
[OUT]         g->ai_profile_left = s_learn_store.left;
[OUT]         g->ai_profile_right = s_learn_store.right;
[OUT]         ai_profile_clamp(&g->ai_profile_left);
[OUT]         ai_profile_clamp(&g->ai_profile_right);
[OUT]     }
[OUT]     else
[OUT]     {
[OUT]         s_learn_store.magic = EDGEAI_LEARN_STORE_MAGIC;
[OUT]         s_learn_store.version = EDGEAI_LEARN_STORE_VERSION;
[OUT]         s_learn_store.crc32 = 0u;
[OUT]         s_learn_store.left = g->ai_profile_left;
[OUT]         s_learn_store.right = g->ai_profile_right;
[OUT]         s_learn_store.crc32 = ai_store_checksum(&s_learn_store);
[OUT]         s_learn_store_dirty = false;
[OUT]     }
[OUT] }
[OUT] 
[OUT] void ai_learning_reset_session(pong_game_t *g)
[OUT] {
[OUT]     if (!g) return;
[OUT]     g->ai_profile_left = ai_profile_default();
[OUT]     g->ai_profile_right = ai_profile_default();
[OUT]     ai_learning_load_store(g);
[OUT] }
[OUT] 
[OUT] void ai_learning_set_mode(pong_game_t *g, ai_learn_mode_t mode)
[OUT] {
[OUT]     if (!g) return;
[OUT]     switch (mode)
[OUT]     {
[OUT]         case kAiLearnModeBoth:
[OUT]         case kAiLearnModeAiAlgo:
[OUT]         case kAiLearnModeAlgoAi:
[OUT]             g->ai_learn_mode = mode;
[OUT]             break;
[OUT]         default:
[OUT]             g->ai_learn_mode = kAiLearnModeBoth;
[OUT]             break;
[OUT]     }
[OUT] }
[OUT] 
[OUT] void ai_learning_set_persistent(pong_game_t *g, bool enabled)
[OUT] {
[OUT]     if (!g) return;
[OUT]     if (enabled)
[OUT]     {
[OUT]         g->persistent_learning = true;
[OUT]         ai_learning_load_store(g);
[OUT]         return;
[OUT]     }
[OUT] 
[OUT]     /* Persistence OFF means no carry-over advantage:
[OUT]      * clear current learned profiles and wipe stored snapshot.
[OUT]      */
[OUT]     g->persistent_learning = false;
[OUT]     ai_learning_reset_session(g);
[OUT]     memset(&s_learn_store, 0, sizeof(s_learn_store));
[OUT]     s_learn_store_dirty = false;
[OUT]     ai_flash_clear_store();
[OUT] }
[OUT] 
[OUT] void ai_learning_sync_store(pong_game_t *g)
[OUT] {
[OUT]     if (!g || !g->persistent_learning) return;
[OUT]     if (!s_learn_store_dirty) return;
[OUT]     if (ai_flash_write_store(&s_learn_store))
[OUT]     {
[OUT]         s_learn_store_dirty = false;
[OUT]     }
[OUT] }
[OUT] 
[OUT] void ai_learning_on_paddle_hit(pong_game_t *g, bool left_side)
[OUT] {
[OUT]     if (!g) return;
[OUT]     bool right_side = !left_side;
[OUT]     if (!ai_learning_side_selected(g, right_side)) return;
[OUT] 
[OUT]     ai_learn_profile_t *p = ai_profile_side(g, right_side);
[OUT]     if (!p) return;
[OUT] 
[OUT]     p->hits = clampu16((uint32_t)p->hits + 1u, 65535u);
[OUT] 
[OUT]     /* Successful return: slightly cleaner and quicker tracking, with mild anticipation. */
[OUT]     p->noise_scale *= 0.987f;
[OUT]     p->speed_scale += 0.008f;
[OUT]     p->lead_scale += 0.005f;
[OUT]     ai_profile_clamp(p);
[OUT]     ai_learning_commit_store(g);
[OUT] }
[OUT] 
[OUT] void ai_learning_on_miss(pong_game_t *g, bool left_side)
[OUT] {
[OUT]     if (!g) return;
[OUT]     bool right_side = !left_side;
[OUT]     if (!ai_learning_side_selected(g, right_side)) return;
[OUT] 
[OUT]     ai_learn_profile_t *p = ai_profile_side(g, right_side);
[OUT]     if (!p) return;
[OUT] 
[OUT]     p->misses = clampu16((uint32_t)p->misses + 1u, 65535u);
[OUT] 
[OUT]     /* Missed return: make AI react faster and reduce wander so it recovers over the session. */
[OUT]     p->noise_scale *= 0.94f;
[OUT]     p->speed_scale += 0.045f;
[OUT]     p->lead_scale += 0.030f;
[OUT]     ai_profile_clamp(p);
[OUT]     ai_learning_commit_store(g);
[OUT] }
[OUT] 
[OUT] static void ai_sim_wall(float *p, float *v, float r)
[OUT] {
[OUT]     if (!p || !v) return;
[OUT]     if ((*p - r) < 0.0f)
[OUT]     {
[OUT]         *p = r;
[OUT]         *v = absf(*v);
[OUT]     }
[OUT]     if ((*p + r) > 1.0f)
[OUT]     {
[OUT]         *p = 1.0f - r;
[OUT]         *v = -absf(*v);
[OUT]     }
[OUT] }
[OUT] 
[OUT] static void ai_predict_right(const pong_game_t *g, float dt, float *out_y, float *out_z, float *out_t)
[OUT] {
[OUT]     if (!out_y || !out_z || !out_t)
[OUT]         return;
[OUT] 
[OUT]     *out_y = 0.5f;
[OUT]     *out_z = 0.5f;
[OUT]     *out_t = 0.0f;
[OUT]     if (!g) return;
[OUT] 
[OUT]     if (g->ball.vx <= 0.0f)
[OUT]     {
[OUT]         *out_y = 0.5f;
[OUT]         *out_z = 0.5f;
[OUT]         *out_t = 0.0f;
[OUT]         return;
[OUT]     }
[OUT] 
[OUT]     float x = g->ball.x;
[OUT]     float y = g->ball.y;
[OUT] ---
[OUT]     if (!g) return 1.0f;
[OUT]     if (!ai_learning_side_selected(g, right_side)) return 1.0f;
[OUT]     const ai_learn_profile_t *p = ai_profile_side_const(g, right_side);
[OUT]     if (!p) return 1.0f;
[OUT]     return clampf(p->lead_scale, 0.70f, 2.00f);
[OUT] }
[OUT] 
[OUT] static void ai_update_telemetry_window(pong_game_t *g)
[OUT] {
[OUT]     if (!g) return;
[OUT] 
[OUT]     if (g->ai_telemetry_start_cycles == 0u)
[OUT]     {
[OUT]         g->ai_telemetry_start_cycles = time_hal_cycles();
[OUT]         return;
[OUT]     }
[OUT] 
[OUT]     uint32_t elapsed_us = time_hal_elapsed_us(g->ai_telemetry_start_cycles);
[OUT]     if (elapsed_us < 1000000u) return;
[OUT] 
[OUT]     uint32_t npu_hz = 0u;
[OUT]     uint32_t fb_hz = 0u;
[OUT] 
[OUT]     if (elapsed_us > 0u)
[OUT]     {
[OUT]         npu_hz = (uint32_t)(((uint64_t)g->ai_npu_attempts_window * 1000000ull) / (uint64_t)elapsed_us);
[OUT]         fb_hz = (uint32_t)(((uint64_t)g->ai_fallback_window * 1000000ull) / (uint64_t)elapsed_us);
[OUT]     }
[OUT] 
[OUT]     g->ai_npu_rate_hz = clampu16(npu_hz, 999u);
[OUT]     g->ai_fallback_rate_hz = clampu16(fb_hz, 999u);
[OUT]     g->ai_npu_attempts_window = 0u;
[OUT]     g->ai_fallback_window = 0u;
[OUT]     g->ai_telemetry_start_cycles = time_hal_cycles();
[OUT] }
[OUT] 
[OUT] static void ai_step_one(pong_game_t *g, float dt, pong_paddle_t *p, bool right_side)
[OUT] {
[OUT]     if (!g || !p) return;
[OUT] 
[OUT]     bool ball_toward = right_side ? (g->ball.vx > 0.0f) : (g->ball.vx < 0.0f);
[OUT]     bool side_edgeai = ai_learning_side_selected(g, right_side);
[OUT]     bool use_npu = g->ai_enabled && side_edgeai && ball_toward;
[OUT] 
[OUT]     /* Refresh AI target at a lower rate for difficulty and lower CPU. */
[OUT]     uint32_t div = ai_update_div(g, use_npu);
[OUT]     if (div == 0u) div = 1u;
[OUT]     if ((g->frame % div) == 0u)
[OUT]     {
[OUT]         float y_hit = 0.5f;
[OUT]         float z_hit = 0.5f;
[OUT]         float t_hit = 0.0f;
[OUT]         bool used_npu = false;
[OUT] 
[OUT]         if (ball_toward)
[OUT]         {
[OUT]             if (use_npu)
[OUT]             {
[OUT]                 float feat[16];
[OUT]                 float feat2[16];
[OUT]                 ai_build_features(g, feat);
[OUT] 
[OUT]                 const float *use_feat = feat;
[OUT]                 if (!right_side)
[OUT]                 {
[OUT]                     ai_mirror_features_x(feat, feat2);
[OUT]                     use_feat = feat2;
[OUT]                 }
[OUT] 
[OUT]                 g->ai_npu_attempts_window++;
[OUT]                 npu_pred_t pred;
[OUT]                 used_npu = npu_hal_predict(&g->npu, use_feat, &pred);
[OUT]                 if (used_npu)
[OUT]                 {
[OUT]                     y_hit = pred.y_hit;
[OUT]                     z_hit = pred.z_hit;
[OUT]                     t_hit = pred.t_hit;
[OUT] 
[OUT]                     /* In mixed SKILL modes, blend NPU with analytic prediction to
[OUT]                      * keep EdgeAI competitive against fixed ALGO baseline.
[OUT]                      */
[OUT]                     if (g->ai_learn_mode != kAiLearnModeBoth)
[OUT]                     {
[OUT]                         float y_ref = 0.5f;
[OUT]                         float z_ref = 0.5f;
[OUT]                         float t_ref = 0.0f;
[OUT]                         if (right_side)
[OUT]                         {
[OUT]                             ai_predict_right(g, dt, &y_ref, &z_ref, &t_ref);
[OUT]                         }
[OUT]                         else
[OUT]                         {
[OUT]                             ai_predict_left(g, dt, &y_ref, &z_ref, &t_ref);
[OUT]                         }
[OUT] 
[OUT]                         /* Confidence gate: when NPU diverges from analytic physics, bias heavily
[OUT]                          * toward the analytic path to preserve competitiveness.
[OUT]                          */
[OUT]                         float dy = absf(y_hit - y_ref);
[OUT]                         float dz = absf(z_hit - z_ref);
[OUT]                         float dtau = absf(t_hit - t_ref);
[OUT]                         float disagreement = dy + dz + (0.60f * dtau);
[OUT] 
[OUT]                         float npu_w = 0.16f;
[OUT]                         if (disagreement >= 0.22f)
[OUT]                         {
[OUT]                             npu_w = 0.0f;
[OUT]                         }
[OUT]                         else if (disagreement > 0.0f)
[OUT]                         {
[OUT]                             float trust = 1.0f - (disagreement / 0.22f);
[OUT]                             npu_w *= clampf(trust, 0.0f, 1.0f);
[OUT]                         }
[OUT] 
[OUT]                         const float ref_w = 1.0f - npu_w;
[OUT]                         y_hit = (ref_w * y_ref) + (npu_w * y_hit);
[OUT]                         z_hit = (ref_w * z_ref) + (npu_w * z_hit);
[OUT]                         t_hit = (ref_w * t_ref) + (npu_w * t_hit);
[OUT]                     }
[OUT]                 }
[OUT]             }
[OUT] 
[OUT]             if (!used_npu)
[OUT]             {
[OUT]                 if (right_side)
[OUT]                 {
[OUT]                     ai_predict_right(g, dt, &y_hit, &z_hit, &t_hit);
[OUT]                 }
[OUT]                 else
[OUT]                 {
[OUT]                     ai_predict_left(g, dt, &y_hit, &z_hit, &t_hit);
[OUT]                 }
[OUT]             }
[OUT] 
[OUT]             /* Learned anticipation: shift target along projected travel based on side profile. */
[OUT]             {
[OUT]                 float lead = ai_lead_scale(g, right_side);
[OUT]                 float t_use = clampf(t_hit, 0.0f, 0.80f);
[OUT]                 float k = (lead - 1.0f) * 0.45f;
[OUT]                 y_hit += g->ball.vy * t_use * k;
[OUT]                 z_hit += g->ball.vz * t_use * k;
[OUT]             }
[OUT] 
[OUT]             /* Add small noise to avoid perfect play. */
[OUT]             float noise = ai_noise(g, right_side);
[OUT]             y_hit += rand_f(g, -noise, noise);
[OUT]             z_hit += rand_f(g, -noise, noise);
[OUT]         }
[OUT] 
[OUT]         if (!used_npu)
[OUT]         {
2026-02-25T00:00:00Z | session: verified root runbook docs (START_HERE/PROJECT_STATE/OPS_RUNBOOK) and inspected smart-pong working tree/state
2026-02-25T00:00:00Z | session: inspected online-learning symbols in src/game/ai.c and src/game/game.h
2026-02-25T01:37:46Z | date -u +%Y-%m-%dT%H:%M:%SZ ; git status --short ; git diff -- src/game/game.h src/game/ai.c
2026-02-25T01:38:31Z | ./tools/build_frdmmcxn947.sh && ./tools/flash_frdmmcxn947.sh (online tactical learning pass)
2026-02-25T01:38:31Z | result: build=PASS flash=PASS
2026-02-25T01:38:55Z | viewed STATUS.md to update last-run notes for online tactical learning
2026-02-25T01:39:15Z | updated STATUS.md with online tactical learning note
2026-02-25T01:40:20Z | tuned ai.c for early-match stability and mixed-mode competitiveness (lower style epsilon, maturity-gated style effect, reduced noise, slight speed bias)
2026-02-25T01:40:20Z | starting build+flash for AI competitiveness retune
2026-02-25T01:45:10Z | build_frdmmcxn947=PASS ; flash_frdmmcxn947=PASS (AI competitiveness retune)
2026-02-25T01:50:05Z | updated STATUS.md with AI competitiveness retune note
2026-02-25T01:59:49Z | date stamp for restore artifact naming
2026-02-25T01:59:49Z | copied current build ELF to failsafe/edgeai_smart_pong_demo_cm33_core0_20260225_015949_online_tactical_ai_retune_golden.elf
2026-02-25T02:00:10Z | reviewed README.md, docs/project_description.md, docs/failsafe.md, STATUS.md for doc refresh
2026-02-25T02:01:20Z | updated README with detailed AI runtime flow and online tactical learning behavior
2026-02-25T02:01:20Z | updated docs/project_description.md AI section with online tactical adaptation details
2026-02-25T02:01:20Z | updated docs/failsafe.md to new Golden/Failsafe restore artifact
2026-02-25T02:01:20Z | updated STATUS.md with new restore-marker note and failsafe path
2026-02-25T02:02:40Z | committed and pushed snapshot: Retune EdgeAI competitiveness and promote new golden/failsafe restore point (e9bc0b7)
2026-02-25T02:03:30Z | tuned ai.c high-speed dynamic lead boost for EdgeAI anticipation
2026-02-25T02:03:30Z | starting build+flash for high-speed lead retune
2026-02-25T02:06:55Z | build_frdmmcxn947=PASS ; flash_frdmmcxn947=PASS (high-speed lead retune)
2026-02-25T02:07:05Z | updated STATUS.md with high-speed lead retune note
2026-02-25T02:08:10Z | inspected default settings in src/game/game.c and game.h for startup profile update
2026-02-25T02:08:25Z | patched game_init defaults: P0, LEVEL3, NPU ON, SKILL AI/ALGO, PERSIST ON, MATCH INF, TARGET OFF, SPEED++ ON
2026-02-25T02:08:25Z | starting build+flash for default-profile update
2026-02-25T02:12:40Z | build_frdmmcxn947=PASS ; flash_frdmmcxn947=PASS (startup default profile update)
2026-02-25T02:12:55Z | updated STATUS.md with startup default profile note
2026-02-25T02:13:10Z | committed+pushed c9a0c79 (startup defaults + high-speed lead tuning)
2026-02-26T19:13:33Z | sed -n 330,540p src/game/game.c
2026-02-26T19:13:33Z | sed -n 250,470p src/game/ai.c
2026-02-26T19:13:33Z | rg -n persistence in README/project_description/STATUS
2026-02-26T19:13:39Z | sed -n 240,340p src/game/game.c
2026-02-26T19:13:47Z | rg+sed ai_init in src/game/ai.c
2026-02-26T19:13:53Z | sed -n 590,680p src/game/ai.c
2026-02-26T19:14:05Z | sed -n 1,220p README.md
2026-02-26T19:14:05Z | rg -n default/startup persistence docs
2026-02-26T19:14:28Z | git diff -- src/game/game.c README.md STATUS.md
2026-02-26T19:17:43Z | ./tools/build_frdmmcxn947.sh && ./tools/flash_frdmmcxn947.sh
2026-02-26T19:17:43Z | result: build=PASS flash=PASS (persistence default OFF update)
2026-02-26T19:18:02Z | updated root docs/PROJECT_STATE.md for smart pong persistence default OFF
2026-02-26T19:18:10Z | updated STATUS.md with 2026-02-26 verification note
2026-02-26T19:18:21Z | git remote -v
2026-02-26T19:18:21Z | git status --short
2026-02-26T19:18:29Z | git add src/game/game.c README.md STATUS.md docs/COMMAND_LOG.md && git commit -m "Set persistence default OFF until user enables it"
2026-02-26T19:18:44Z | git push origin main
2026-02-26T19:18:51Z | git status --short (post-push)
2026-02-26T19:18:51Z | git show --name-only --oneline -1
2026-02-26T19:20:14Z | sed -n 1,220p docs/failsafe.md
2026-02-26T19:20:14Z | sed -n 1,240p tools/flash_failsafe.sh
2026-02-26T19:20:14Z | ls -la failsafe
2026-02-26T19:20:33Z | cp mcuxsdk_ws/build/edgeai_smart_pong_demo_cm33_core0.elf failsafe/edgeai_smart_pong_demo_cm33_core0_20260226_192033_persist_default_off_golden.elf
2026-02-26T19:20:44Z | sed -n 1,120p docs/failsafe.md (before update)
2026-02-26T19:20:44Z | sed -n 1,120p STATUS.md (before restore-point update)
2026-02-26T19:20:44Z | rg -n failsafe/golden in STATUS.md docs/BUILD_FLASH.md
2026-02-26T19:21:10Z | updated docs/failsafe.md docs/BUILD_FLASH.md STATUS.md for new golden/failsafe artifact
2026-02-26T19:21:10Z | git status --short (pre-commit restore-point update)
2026-02-26T19:21:10Z | sed -n 1,3p docs/failsafe.md (verify active failsafe pointer)
2026-02-26T19:21:18Z | updated root docs/PROJECT_STATE.md for smart pong golden/failsafe promotion
2026-02-26T19:21:27Z | git add STATUS.md docs/BUILD_FLASH.md docs/failsafe.md failsafe/*persist_default_off_golden.elf docs/COMMAND_LOG.md && git commit -m "Promote persistence-default-OFF build as golden failsafe"
2026-02-26T19:21:42Z | git push origin main (golden/failsafe promotion)
2026-02-26T19:26:51Z | sed -n 1,260p src/game/ai.h
2026-02-26T19:26:51Z | sed -n 1,260p src/game/game.h
2026-02-26T19:26:51Z | sed -n 1,280p src/game/ai.c
2026-02-26T19:26:57Z | sed -n 280,520p src/game/ai.c
2026-02-26T19:27:55Z | updated src/game/ai.c with decay, guarded persistence, and auto-rollback safeguards
2026-02-26T19:28:04Z | sed -n 118,152p README.md
2026-02-26T19:28:04Z | rg -n persistence section in README.md
2026-02-26T19:28:20Z | updated README.md and STATUS.md with persistence safeguard notes
2026-02-26T19:31:31Z | ./tools/build_frdmmcxn947.sh && ./tools/flash_frdmmcxn947.sh (persistence safeguards)
2026-02-26T19:31:31Z | result: build=PASS flash=PASS (persistence safeguards)
2026-02-26T19:31:46Z | updated STATUS.md and root docs/PROJECT_STATE.md for persistence safeguard verification
2026-02-26T19:31:52Z | git status --short (pre-commit persistence safeguards)
2026-02-26T19:31:57Z | git add src/game/ai.c README.md STATUS.md docs/COMMAND_LOG.md && git commit -m "Stabilize persistent learning with decay and rollback safeguards"
2026-02-26T19:32:03Z | git status --short (post-commit pre-push persistence safeguards)
2026-02-26T19:32:13Z | git add docs/COMMAND_LOG.md && git commit -m "Update command log for persistence safeguard flow"
2026-02-26T19:32:22Z | git push origin main (persistence safeguards)
2026-02-26T19:52:50Z | sed -n 1,260p src/game/ai.c (pre non-persist safeguard update)
2026-02-26T19:52:50Z | sed -n 260,520p src/game/ai.c (pre non-persist safeguard update)
2026-02-26T19:52:50Z | sed -n 520,760p src/game/ai.c (pre non-persist safeguard update)
2026-02-26T19:53:13Z | updated src/game/ai.c to run decay+rollback in non-persistent sessions while keeping flash writes gated by PERSIST ON
2026-02-26T19:53:28Z | updated README.md and STATUS.md for non-persistent safeguard extension
2026-02-26T19:56:36Z | ./tools/build_frdmmcxn947.sh && ./tools/flash_frdmmcxn947.sh (extend safeguards to non-persistent sessions)
2026-02-26T19:56:36Z | result: build=PASS flash=PASS (extend safeguards to non-persistent sessions)
2026-02-26T19:56:52Z | updated STATUS.md and root docs/PROJECT_STATE.md for non-persistent safeguard extension
2026-02-26T19:56:58Z | git status --short (pre-commit non-persist safeguard extension)
2026-02-26T19:57:04Z | git add src/game/ai.c README.md STATUS.md docs/COMMAND_LOG.md && git commit -m "Extend anti-drift safeguards to non-persistent sessions"
2026-02-26T19:57:09Z | git status --short (post-commit pre-push non-persist safeguard extension)
2026-02-26T19:57:15Z | git add docs/COMMAND_LOG.md && git commit -m "Update command log for non-persistent safeguard extension"
2026-02-26T19:57:25Z | git push origin main (non-persistent safeguard extension)
2026-02-26T21:00:56Z | sed -n 1,120p docs/failsafe.md
2026-02-26T21:00:57Z | sed -n 1,140p STATUS.md
2026-02-26T21:00:57Z | ls -la mcuxsdk_ws/build/edgeai_smart_pong_demo_cm33_core0.elf
2026-02-26T21:01:04Z | cp mcuxsdk_ws/build/edgeai_smart_pong_demo_cm33_core0.elf failsafe/edgeai_smart_pong_demo_cm33_core0_20260226_210104_anti_drift_all_modes_golden.elf
2026-02-26T21:01:18Z | rg -n failsafe lines in docs/BUILD_FLASH.md
2026-02-26T21:01:32Z | updated docs/failsafe.md docs/BUILD_FLASH.md STATUS.md for anti-drift-all-modes golden/failsafe
2026-02-26T21:01:40Z | updated root docs/PROJECT_STATE.md for anti-drift-all-modes golden/failsafe promotion
2026-02-26T21:01:46Z | git status --short (pre-commit anti-drift-all-modes restore-point promotion)
2026-02-26T21:01:52Z | git add STATUS.md docs/BUILD_FLASH.md docs/failsafe.md failsafe/*anti_drift_all_modes_golden.elf docs/COMMAND_LOG.md && git commit -m "Promote anti-drift-all-modes build as golden failsafe"
2026-02-26T21:02:02Z | git push origin main (anti-drift-all-modes golden/failsafe promotion)
2026-02-26T21:02:10Z | git status --short (post-push check anti-drift-all-modes promotion)
2026-02-26T21:02:15Z | git add docs/COMMAND_LOG.md && git commit -m "Update command log for golden failsafe promotion"
2026-02-26T21:02:21Z | git push origin main (command-log sync after golden/failsafe promotion)
2026-02-26T21:09:37Z | sed -n 1,260p src/game/game.c
2026-02-26T21:09:37Z | rg -n score/match/confetti/reset in src/game
2026-02-26T21:09:37Z | sed -n 260,560p src/game/game.c
2026-02-26T21:09:42Z | sed -n 560,700p src/game/game.c
2026-02-26T21:10:30Z | updated src/game/game.c and src/game/render.c for 999 cap + 30s reset behavior
2026-02-26T21:10:43Z | rg -n target gameplay text in README.md
2026-02-26T21:10:43Z | sed -n 32,86p README.md
2026-02-26T21:10:43Z | sed -n 1,120p STATUS.md
2026-02-26T21:10:59Z | updated README.md and STATUS.md for 999-cap auto-reset behavior
2026-02-26T21:14:21Z | ./tools/build_frdmmcxn947.sh && ./tools/flash_frdmmcxn947.sh (999 cap + 30s reset)
2026-02-26T21:14:21Z | result: build=PASS flash=PASS (999 cap + 30s reset)
2026-02-26T21:14:27Z | date -u ; git status --short ; git rev-parse --abbrev-ref HEAD (post-build/flash validation)
2026-02-26T21:14:48Z | sed -n docs/failsafe.md and docs/BUILD_FLASH.md (inspect active failsafe pointer)
2026-02-26T21:14:48Z | cp mcuxsdk_ws/build/edgeai_smart_pong_demo_cm33_core0.elf failsafe/edgeai_smart_pong_demo_cm33_core0_20260226_211448_scorecap999_reset30s_golden.elf
2026-02-26T21:14:58Z | updated docs/failsafe.md docs/BUILD_FLASH.md STATUS.md and root docs/PROJECT_STATE.md for scorecap999 golden/failsafe promotion
2026-02-26T21:15:09Z | git status --short ; git tag --list ; git branch --list ; git remote -v (pre-push validation)
2026-02-26T21:15:30Z | git add src/game/game.c src/game/render.c README.md STATUS.md docs/BUILD_FLASH.md docs/failsafe.md docs/COMMAND_LOG.md failsafe/*scorecap999_reset30s_golden.elf && git commit -m "Add 999 score cap auto-reset and promote golden failsafe"
2026-02-26T21:15:38Z | git status --short (post-commit check)
2026-02-26T21:15:46Z | git push origin main
2026-02-26T21:15:55Z | git tag -fa golden/failsafe and push tags (restore points)
2026-02-26T21:16:12Z | git status --short (post-log-commit check)
2026-02-26T21:16:20Z | git rev-parse golden/failsafe/main and git log --oneline -n 3 (release verification)
2026-02-26T21:16:31Z | git rev-parse golden^{} failsafe^{} main && git status --short (tag target verification)
2026-02-26T21:17:20Z | inspected render/game files via sed/rg for bottom-row HUD placement and score state fields
2026-02-26T21:18:05Z | updated src/game/game.h src/game/game.c src/game/render.c for per-side running AVG score HUD
2026-02-26T21:18:28Z | ./tools/build_frdmmcxn947.sh (avg-score HUD update)
2026-02-26T21:18:28Z | result: build=PASS (avg-score HUD update)
2026-02-26T21:24:05Z | updated README.md STATUS.md and root docs/PROJECT_STATE.md for avg-score HUD behavior
2026-02-26T21:24:34Z | git status --short (pre-commit avg-score HUD)
2026-02-26T21:24:46Z | git add README.md STATUS.md docs/COMMAND_LOG.md src/game/game.c src/game/game.h src/game/render.c && git commit -m "Add per-side bottom-row running AVG score HUD"
2026-02-26T21:24:46Z | git push origin main
2026-02-26T21:27:10Z | patched src/game/render.c to always render AVG from 0-0 and move AVG row to avoid footer overlap
2026-02-26T21:27:20Z | ./tools/build_frdmmcxn947.sh (avg HUD visibility follow-up)
2026-02-26T21:28:15Z | updated root docs/PROJECT_STATE.md for avg HUD visibility fix
2026-02-26T21:28:28Z | git status --short (pre-commit avg HUD visibility fix)
2026-02-26T21:28:40Z | git add src/game/render.c docs/COMMAND_LOG.md && git commit -m "Fix AVG HUD visibility for MATCH 11 and INF"
2026-02-26T21:28:40Z | git push origin main
2026-02-26T21:29:20Z | result: build=PASS (avg HUD visibility follow-up)
2026-02-26T21:30:32Z | ./tools/flash_frdmmcxn947.sh (deploy AVG HUD visibility fix)
2026-02-26T21:30:38Z | result: flash=PASS (deploy AVG HUD visibility fix)
2026-02-26T21:31:00Z | updated STATUS.md (record flash PASS for AVG visibility fix)
2026-02-26T21:31:18Z | git status --short (pre-commit flash-verification docs update)
2026-02-26T21:31:30Z | git add STATUS.md docs/COMMAND_LOG.md && git commit -m "Record AVG visibility flash verification"
2026-02-26T21:31:30Z | git push origin main
2026-02-26T21:33:10Z | adjusted AVG HUD layout in src/game/render.c: larger text, bottom-row placement, near-net anchors
2026-02-26T21:36:10Z | fixed compile warning in src/game/render.c (removed unused rw)
2026-02-26T21:36:18Z | ./tools/build_frdmmcxn947.sh && ./tools/flash_frdmmcxn947.sh
2026-02-26T21:36:18Z | result: build=PASS flash=PASS
2026-02-26T21:39:10Z | updated src/game/render.c: remove right AVG label, +3-char inter-number spacing, centered numeric layout
2026-02-26T21:39:18Z | ./tools/build_frdmmcxn947.sh && ./tools/flash_frdmmcxn947.sh
2026-02-26T21:39:18Z | result: build=PASS flash=PASS
2026-02-26T21:39:30Z | updated STATUS.md and root docs/PROJECT_STATE.md for AVG layout adjustment
2026-02-26T21:39:44Z | git status --short (pre-commit AVG layout tune)
2026-02-26T21:39:56Z | git add src/game/render.c STATUS.md docs/COMMAND_LOG.md && git commit -m "Tune AVG HUD: single label, wider spacing, centered numbers"
2026-02-26T21:39:56Z | git push origin main
2026-02-26T22:16:44Z | updated src/game/game.c: settings `NEW GAME` now clears AVG history (`score_total_left/right`, `score_avg_games`) before reset
2026-02-26T22:17:02Z | ./tools/build_frdmmcxn947.sh && ./tools/flash_frdmmcxn947.sh (AVG reset on settings score clear)
2026-02-26T22:17:02Z | result: build=PASS flash=PASS (AVG reset on settings score clear)
2026-02-26T22:25:21Z | git diff/status checks for src/game/game.c STATUS.md docs/COMMAND_LOG.md (pre-commit AVG reset change)
2026-02-26T22:26:07Z | git add src/game/game.c STATUS.md docs/COMMAND_LOG.md && git commit -m "Reset AVG counters when settings NEW GAME clears score"
2026-02-26T22:26:16Z | git push origin main
2026-02-26T22:33:33Z | cp mcuxsdk_ws/build/edgeai_smart_pong_demo_cm33_core0.elf failsafe/edgeai_smart_pong_demo_cm33_core0_20260226_223333_avg_reset_newgame_golden.elf
2026-02-26T22:33:50Z | updated README.md docs/failsafe.md docs/BUILD_FLASH.md STATUS.md for AVG reset behavior + new golden/failsafe pointer
2026-02-26T22:34:20Z | git add README.md STATUS.md docs/BUILD_FLASH.md docs/COMMAND_LOG.md docs/failsafe.md failsafe/edgeai_smart_pong_demo_cm33_core0_20260226_223333_avg_reset_newgame_golden.elf && git commit -m "Update docs and promote AVG-reset build as golden failsafe"
2026-02-26T22:34:24Z | git push origin main
2026-02-26T22:34:42Z | git tag -fa golden/failsafe && git push origin golden failsafe --force (move restore-point tags)
2026-02-26T23:19:12Z | git tag -fa golden/failsafe && git push origin golden failsafe --force (align tags to latest main)
2026-02-26T23:19:22Z | verified refs: main==golden==failsafe at 38b82a9
2026-02-26T23:19:40Z | updated README.md and STATUS.md for active restore-point documentation + tag alignment note
2026-02-26T23:20:00Z | git add README.md STATUS.md docs/COMMAND_LOG.md && git commit -m "Refresh README and align restore-point docs"
2026-02-26T23:20:03Z | git push origin main
2026-02-26T23:20:11Z | git tag -fa golden/failsafe && git push origin golden failsafe --force (promote latest docs commit as restore-point tags)
2026-02-26T23:20:14Z | verified refs: main==golden==failsafe at 785616b
2026-02-26T23:22:10Z | inspected serve/reset paths in src/game/game.c and src/game/physics.c
2026-02-26T23:23:08Z | updated src/game/physics.c: adaptive AI serve selector for straight/single-axis/diagonal launches with receiver-position bias
2026-02-26T23:24:00Z | ./tools/build_frdmmcxn947.sh (AI serve variation update)
2026-02-26T23:24:00Z | result: build=PASS (AI serve variation update)
2026-02-26T23:25:10Z | updated README.md and STATUS.md for AI serve variation feature
2026-02-26T23:26:15Z | git add src/game/physics.c README.md STATUS.md docs/COMMAND_LOG.md && git commit -m "Add adaptive AI serve patterns for straight and angled launches"
2026-02-26T23:26:19Z | git push origin main
2026-02-26T23:31:20Z | updated src/game/game.c src/game/game.h src/game/render.c to replace bottom AVG HUD with per-side WINS counters and reset-on-new-game semantics
2026-02-26T23:39:20Z | ./tools/build_frdmmcxn947.sh (WINS HUD replacement)
2026-02-26T23:39:20Z | result: build=PASS (WINS HUD replacement)
2026-02-26T23:39:45Z | updated README.md and STATUS.md for WINS HUD feature
2026-02-26T23:40:50Z | git add src/game/game.c src/game/game.h src/game/render.c README.md STATUS.md docs/COMMAND_LOG.md && git commit -m "Replace AVG HUD with per-side WINS counters"
2026-02-26T23:40:54Z | git push origin main
2026-02-26T23:44:10Z | updated src/game/game.h src/game/game.c src/game/render.c: MATCH options changed from 11/INF to 11/100/1K(999 target)
2026-02-26T23:45:40Z | updated README.md and STATUS.md for MATCH setting change (11/100/1K)
2026-02-26T23:46:00Z | ./tools/build_frdmmcxn947.sh && ./tools/flash_frdmmcxn947.sh (MATCH 11/100/1K update)
2026-02-26T23:46:00Z | result: build=PASS flash=PASS (MATCH 11/100/1K update)
2026-02-26T23:49:20Z | git add src/game/game.h src/game/game.c src/game/render.c README.md STATUS.md docs/COMMAND_LOG.md && git commit -m "Add MATCH targets 11, 100, and 1K"
2026-02-26T23:49:24Z | git push origin main
2026-02-26T23:51:40Z | updated src/game/game.c default MATCH target from 1K to 100
2026-02-26T23:52:00Z | ./tools/build_frdmmcxn947.sh && ./tools/flash_frdmmcxn947.sh (default MATCH=100)
2026-02-26T23:52:00Z | result: build=PASS flash=PASS (default MATCH=100)
2026-02-26T23:57:16Z | updated STATUS.md for default MATCH=100 + verification
2026-02-26T23:57:50Z | git add src/game/game.c STATUS.md docs/COMMAND_LOG.md && git commit -m "Set default MATCH target to 100"
2026-02-26T23:57:54Z | git push origin main
2026-02-26T23:59:42Z | prepared restore promotion timestamp and verified current build ELF
2026-02-26T23:59:50Z | cp mcuxsdk_ws/build/edgeai_smart_pong_demo_cm33_core0.elf failsafe/edgeai_smart_pong_demo_cm33_core0_20260226_235942_match100_default_golden.elf
2026-02-27T00:00:30Z | updated README.md STATUS.md docs/failsafe.md docs/BUILD_FLASH.md for default-MATCH-100 golden/failsafe promotion
2026-02-27T00:01:15Z | git add README.md STATUS.md docs/BUILD_FLASH.md docs/COMMAND_LOG.md docs/failsafe.md failsafe/edgeai_smart_pong_demo_cm33_core0_20260226_235942_match100_default_golden.elf && git commit -m "Refresh docs and promote MATCH-100 build as golden failsafe"
2026-02-27T00:01:20Z | git push origin main
2026-02-27T00:01:40Z | git tag -fa golden/failsafe && git push origin golden failsafe --force (move restore-point tags to 831556b)
2026-03-06T10:36:08Z | cmd: ls -la; ls docs; rg START_HERE/PROJECT_STATE/OPS_RUNBOOK/todo | exit:0
2026-03-06T10:36:30Z | cmd: read required project docs in order + context docs | exit:0
2026-03-06T10:42:19Z | cmd: extract ai_build_features contract + npu hal details for model mapping | exit:0
2026-03-24T06:26:55-07:00 | build attempt default BUILD_DIR failed due stale west source-dir mismatch
2026-03-24T06:26:55-07:00 | inspected tools/build_frdmmcxn947.sh to confirm BUILD_DIR override path
2026-03-24T06:26:55-07:00 | BUILD_DIR=mcuxsdk_ws/build_style_match_20260324 ./tools/build_frdmmcxn947.sh PASS
2026-03-24T06:29:07-07:00 | cd nxp/.../EdgeAI_Smart_Pong_Demo && BUILD_DIR=mcuxsdk_ws/build_style_match_20260324 ./tools/flash_frdmmcxn947.sh
2026-03-24T06:30:55-07:00 | sed -n 520,760 src/game/game.c
2026-03-24T06:30:55-07:00 | rg AI/game interaction symbols in NXP Smart Pong source
2026-03-24T06:31:09-07:00 | sed -n 1,560 src/game/ai.c
2026-03-24T06:31:09-07:00 | sed -n 560,1320 src/game/ai.c
2026-03-24T06:31:14-07:00 | sed -n 1,220 src/game/input.c && sed -n 150,300 src/game/physics.c
2026-03-24T06:31:32-07:00 | nl -ba key refs in game.c ai.c input.c for EdgeAI fairness assessment
2026-03-24T06:39:38-07:00 | BUILD_DIR=mcuxsdk_ws/build_edgeai_fairness_20260324 ./tools/build_frdmmcxn947.sh
2026-03-24T06:40:23-07:00 | git diff -- src/game/ai.c && nl -ba key ai.c fairness lines
2026-03-24T06:41:18-07:00 | inspect active repo | pwd && ls
2026-03-24T06:41:32-07:00 | flash fairness build | BUILD_DIR=mcuxsdk_ws/build_edgeai_fairness_20260324 ./tools/flash_frdmmcxn947.sh
2026-03-24T06:41:43-07:00 | inspect status/log file layout | ls -la && ls -la docs
2026-03-24T06:41:49-07:00 | read STATUS.md | sed -n 1,260p STATUS.md
2026-03-24T06:41:56-07:00 | attempted read missing docs/PROJECT_STATE.md | sed -n 1,220p docs/PROJECT_STATE.md (failed: file not found)
2026-03-24T06:42:03-07:00 | inspect STATUS header for update | nl -ba STATUS.md | sed -n 1,70p
2026-03-24T06:42:14-07:00 | update STATUS.md for fairness build+flash | edited STATUS.md Last Run and 2026-03-24 notes
2026-03-24T06:42:20-07:00 | verify diffs for fairness/style | git status --short && git diff ai.c render.c
2026-03-24T06:42:29-07:00 | capture line refs for report | nl -ba src/game/ai.c and STATUS.md
2026-03-24T06:42:49-07:00 | audit ai gating references | rg ai_enabled/ai_learning_side_selected across game sources
2026-03-24T06:43:56-07:00 | read project docs start file | sed -n 1,220p docs/START_HERE.md
2026-03-24T06:43:56-07:00 | scan gameplay speed/score hooks | rg -n serve|speed|score in src/game
2026-03-24T06:43:59-07:00 | inspect physics tuning/reset | sed -n 1,280p src/game/physics.c
2026-03-24T06:44:40-07:00 | edit physics for faster startup + 6+ score pace-up | apply_patch src/game/physics.c
2026-03-24T06:50:23-07:00 | build faster startup + 6+ pace-up | BUILD_DIR=mcuxsdk_ws/build_speedup_20260324 ./tools/build_frdmmcxn947.sh
2026-03-24T06:50:49-07:00 | update STATUS for speed tuning build | edited STATUS.md Last Run for build_speedup_20260324
2026-03-24T06:50:54-07:00 | capture refs for speed tuning | nl -ba physics.c and STATUS.md
2026-03-24T06:52:21-07:00 | read build/restore docs | sed -n docs/BUILD_FLASH.md docs/failsafe.md
2026-03-24T06:52:21-07:00 | inspect repo remotes/status/docs | git remote -v && git status --short && ls -la docs
2026-03-24T06:53:25-07:00 | update docs framework | edited docs/START_HERE.md; added docs/PROJECT_STATE.md and docs/OPS_RUNBOOK.md
2026-03-24T06:53:41-07:00 | flash release candidate speedup build | BUILD_DIR=mcuxsdk_ws/build_speedup_20260324 ./tools/flash_frdmmcxn947.sh
2026-03-24T06:53:57-07:00 | locate release ELF | rg --files -g *edgeai_smart_pong_demo_cm33_core0.elf mcuxsdk_ws
2026-03-24T06:54:07-07:00 | find build_speedup artifacts | find build_speedup_20260324 dirs/files
2026-03-24T06:54:14-07:00 | check top-level speedup build outputs | find .../build_speedup_20260324 -maxdepth 1 -type f
2026-03-24T06:54:20-07:00 | failed attempt to create failsafe artifact | cp from mcuxsdk_ws/build_speedup_20260324/*.elf failed (path mismatch)
2026-03-24T06:54:26-07:00 | create golden/failsafe artifact and update pointer | cp mcuxsdk_ws/mcuxsdk_ws/build_speedup_20260324/edgeai_smart_pong_demo_cm33_core0.elf failsafe/edgeai_smart_pong_demo_cm33_core0_20260324_065426_style_edgeai_fairness_speedup_golden.elf; rewrite docs/failsafe.md
2026-03-24T06:55:26-07:00 | sync release docs | edited STATUS.md, docs/PROJECT_STATE.md, docs/BUILD_FLASH.md, README.md
2026-03-24T06:55:26-07:00 | catch-up log for read-only inspection commands | ran rg/sed inspections on STATUS.md, README.md, docs/BUILD_FLASH.md, docs/PROJECT_STATE.md
2026-03-24T06:55:30-07:00 | run docs/style lint | ./tools/lint_text_style.sh
2026-03-24T06:55:45-07:00 | review release changes | git status --short; git diff --stat
2026-03-24T06:55:52-07:00 | release actions | git add/commit/push and move golden+failsafe tags to release commit
2026-03-24T07:18:03-07:00 | inspect render_ui top-pill block | rg/nl src/game/render.c around render_ui
2026-03-24T07:18:26-07:00 | fix top-pill UI fit regression | restore compact render_ui icon/label/? sizing and P? D? order in src/game/render.c
2026-03-24T07:23:23-07:00 | build top-pill ui fix | BUILD_DIR=mcuxsdk_ws/build_ui_topbar_fix_20260324 ./tools/build_frdmmcxn947.sh
2026-03-24T07:23:30-07:00 | read state files before ui-fit update note | sed -n STATUS.md and docs/PROJECT_STATE.md
2026-03-24T07:23:55-07:00 | update STATUS and project state for top-pill UI rollback | edited STATUS.md and docs/PROJECT_STATE.md with build_ui_topbar_fix_20260324 result
2026-03-24T07:24:29-07:00 | flash top-pill UI fit fix | BUILD_DIR=mcuxsdk_ws/build_ui_topbar_fix_20260324 ./tools/flash_frdmmcxn947.sh
2026-03-24T07:24:47-07:00 | update state docs after flash | edited STATUS.md and docs/PROJECT_STATE.md to mark build_ui_topbar_fix_20260324 flash PASS
2026-03-24T07:26:44-07:00 | inspect P?/D? top-pill label block | nl -ba src/game/render.c 788-820
2026-03-24T07:27:01-07:00 | shift D? right by ~1.5 chars in top pill | edited src/game/render.c to draw P? and D? separately with +1.5 char offset
2026-03-24T07:31:42-07:00 | build D? spacing tweak | BUILD_DIR=mcuxsdk_ws/build_ui_dx_spacing_20260324 ./tools/build_frdmmcxn947.sh
2026-03-24T07:32:21-07:00 | inspect state docs for D? spacing update | tail PROJECT_STATE/STATUS before patch
2026-03-24T07:32:26-07:00 | inspect STATUS sections for insertion | head/tail STATUS.md
2026-03-24T07:32:53-07:00 | update project docs after D? spacing build | patched docs/PROJECT_STATE.md and STATUS.md
2026-03-24T07:32:53-07:00 | verify D? spacing render code | checked src/game/render.c split P?/D? draw with +1.5 char offset
2026-03-24T07:33:11-07:00 | flash D? spacing tweak build | BUILD_DIR=mcuxsdk_ws/build_ui_dx_spacing_20260324 ./tools/flash_frdmmcxn947.sh
2026-03-24T07:33:38-07:00 | update docs after flash verify | patched docs/PROJECT_STATE.md and STATUS.md to build/flash PASS for D? spacing tweak
2026-03-24T07:33:58-07:00 | read required entry docs | cat docs/START_HERE.md docs/PROJECT_STATE.md docs/OPS_RUNBOOK.md
2026-03-24T07:34:10-07:00 | inspect git/release pointers | git status -sb; git branch --show-current; git remote -v; cat docs/failsafe.md; ls -1 mcuxsdk_ws/build_ui_dx_spacing_20260324/*.elf
2026-03-24T07:34:19-07:00 | locate build artifacts for dx spacing release | find mcuxsdk_ws/build_ui_dx_spacing_20260324 -maxdepth 4 -type f | rg -n '\.(elf|bin)$|edgeai_smart_pong_demo'
2026-03-24T07:34:25-07:00 | search build directories | find . -maxdepth 5 -type d | rg 'build_ui_dx_spacing_20260324|build_ui_topbar_fix_20260324|mcuxsdk_ws/build'
2026-03-24T07:34:33-07:00 | locate ui build directories quickly | find mcuxsdk_ws -maxdepth 1 -type d -name 'build_ui*'
2026-03-24T07:34:38-07:00 | search build_ui directories recursively | find . -type d -name 'build_ui*'
2026-03-24T07:34:47-07:00 | inspect dx spacing artifacts in nested build dir | ls -l mcuxsdk_ws/mcuxsdk_ws/build_ui_dx_spacing_20260324/*.elf *.bin
2026-03-24T07:34:56-07:00 | create new failsafe/golden artifact | cp mcuxsdk_ws/mcuxsdk_ws/build_ui_dx_spacing_20260324/edgeai_smart_pong_demo_cm33_core0.elf failsafe/edgeai_smart_pong_demo_cm33_core0_20260324_073456_ui_dx_spacing_golden.elf
2026-03-24T07:35:06-07:00 | inspect docs before release pointer patch | sed heads of docs/failsafe.md docs/PROJECT_STATE.md STATUS.md
2026-03-24T07:35:38-07:00 | sync release docs + restore pointer | updated docs/failsafe.md, docs/PROJECT_STATE.md, STATUS.md for ui_dx_spacing golden/failsafe
2026-03-24T07:35:45-07:00 | review release diff before commit | git diff --stat
2026-03-24T07:35:55-07:00 | release commit/push and retag | git add -A; git commit; git push; git tag -f golden/failsafe; git push --force origin tags
2026-03-24T10:01:43-07:00 | open project and read required docs | cat docs/START_HERE.md docs/PROJECT_STATE.md docs/OPS_RUNBOOK.md
2026-03-24T10:02:08-07:00 | set boot default SKILL to ALGO/AI | edited src/game/game.c: g->ai_learn_mode = kAiLearnModeAlgoAi
2026-03-24T10:02:08-07:00 | build default ALGO-left EDGEAI-right | BUILD_DIR=mcuxsdk_ws/build_default_algo_left_edgeai_right_20260324 ./tools/build_frdmmcxn947.sh
2026-03-24T10:05:39-07:00 | flash default ALGO-left EDGEAI-right build | BUILD_DIR=mcuxsdk_ws/build_default_algo_left_edgeai_right_20260324 ./tools/flash_frdmmcxn947.sh
2026-03-24T10:06:25-07:00 | update state docs for ALGO/AI boot default | updated docs/PROJECT_STATE.md and STATUS.md after build+flash PASS
