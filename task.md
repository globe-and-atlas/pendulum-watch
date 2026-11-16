---
generated_by: "OpenAI Codex (GPT-6; exact variant not exposed)"
timestamp: "2026-11-08T14:39:57-06:00"
---
# Build Pendulum

Analog dial above a swinging seconds bob; optional smooth8fps swing, default1Hz tick-tock.

## Contract
- Directive: directives/build_watchface.md
- Execution: build.py, build_fixture.py, capture_native.py, verify.py
- Artifact: dist/Pendulum-0.1.0.pbw; media/native-comparison.png
- Targets: Emery200×228, Gabbro260×260. Original build scope excluded publication; the store publication section below records subsequent authorization. No commit or push requested. Ignore secrets andSDKlockfiles.

## Validation
- [x] Emery binary builds.
- [x] Gabbro binary builds.
- [x] Six palettes are selectable.
- [x] Custom background is selectable.
- [x] Custom text color is selectable.
- [x] Custom primary color is selectable.
- [x] Custom secondary color is selectable.
- [x] Numeric values support12-hour mode.
- [x] Numeric values support24-hour mode.
- [x] Watch-default format follows the watch preference.
- [x] Digital readout can be hidden.
- [x] Date supports Off/ISO/US/European.
- [x] Save updates the native face.
- [x] Cancel preserves settings.
- [x] Settings survive restart.
- [x] Independent host tests pass.
- [x] Actual Clay tests pass.
- [x] Native Emery renders are inspected.
- [x] Native Gabbro renders are inspected.
- [x] Production excludes fixture controls.
- [x] Independent final review passes.
- [x] Analog hour hand tracks time.
- [x] Analog minute hand tracks time.
- [x] Bob alternates sides on consecutive seconds.
- [x] Smooth swing is optional.
- [x] Live production smooth motion is observed.
- [x] Bob stays clear of the digital readout.
- [x] Bob stays within both screen shapes.

Completed: host/Clay tests, nativecaptures, cleanproduction andindependentfinal reviewPASS. Store publication is recorded below.

## Store publication — 2026-11-08
User authorized public release with animated motion/color GIF first and native screenshots on bothtargets.
- [x] Emery GIF shows mechanism motion.
- [x] Gabbro GIF shows mechanism motion.
- [x] Each GIF includes six palettes.
- [x] Emery public gallery begins with a GIF.
- [x] Gabbro public gallery begins with a GIF.
- [x] Emery public gallery includes four native stills.
- [x] Gabbro public gallery includes four native stills.
- [x] Public PBW matches reviewed production bytes.
- [x] Public preview assets match staged assets.
- [x] Independent release review passes.
