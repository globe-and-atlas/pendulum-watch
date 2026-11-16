---
generated_by: "OpenAI Codex (GPT-6; exact variant not exposed)"
timestamp: "2026-11-08T14:48:12-06:00"
---
# Pendulum

A compact analog clock over a swinging bob. Default tick-tock alternates sides each second. Optional smooth motion draws intermediate positions at125ms intervals. The bob can show numeric seconds.

Supports Pebble Time2 (Emery200×228) and Round2 (Gabbro260×260). Six palettes plus custom background/text/primary/secondary colors; watch-default/12/24numeric format; optionaldigital readout; optionaldateOff/ISO/US/European. Defaults: digitalon, dateoff. No network, Health, orlocation service.

Build: `python3 execution/build.py`; verify: `python3 execution/verify.py`; host tests: `python3 execution/build.py --host-only` or pytest. Output: dist/Pendulum-0.1.0.pbw.

Native fixtures: build_fixture.py followed by capture_native.py --platform emery/gabbro --reset-emulator, serialized after establishing exclusive emulator ownership. Flash is backed up before reset. Captures require identity/bounds markers and three stable complete LCD frames. Fixture captures are distinct from production/device behavior. Use a clean production build for release; fixture captures never replace dist/. build_preview.py assembles native images without resampling.

Physical-watch legibility and battery endurance remain unmeasured.

## Public release

[Pendulum on the Pebble Appstore](https://apps.repebble.com/0d992be1d6454c84a4842e12) — version 0.1.0. Both Time 2 and Round 2 galleries begin with a native motion/color GIF, followed by four screenshots. Public PBW and preview assets were verified against the staged release. Evidence is preserved in `release/`.
