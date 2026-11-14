# WPPRedux (Water Pools Plus Redux)

A rebuild of **Water Pools Plus Redux** (originally by Sam Crosscat, Redux by Acxd)
to restore compatibility after a major Satisfactory engine/game update broke the
original release. Built against Unreal Engine 5.6.1-CSS with SML.

- **Mod version**: 1.0.8
- **Target game version**: Satisfactory build ≥ 491125
- **AI assistance**: this rebuild (debugging, blueprint fixes, and a new
  native code hook for the dismantle crash) was done with the help of
  Claude Code (Anthropic). All changes were tested in-game before being
  committed here.

## What it does

Lets you place a Water Extractor on a portable, paintable Water Pool (Large,
Small, or Modular/snap-together) instead of requiring natural deep water.

## Fixes and improvements over the original release

- **Compatibility**: rebuilt and recompiled against the current Satisfactory
  engine build; the original release no longer loaded at all.
- **FICSIT logo texture**: fixed a bug where the logo decal on the pool walls
  looped/duplicated across the surface instead of rendering once, correctly
  scaled.
- **Modular pool placement crash**: fixed a crash on placement caused by a
  missing Hologram Class reference.
- **Modular pool collision**:
  - Fixed water visually rendering but having no collision (player would fall
    through the floor).
  - Fixed missing collision at the seams and corners of connected
    (L-shaped, etc.) layouts.
  - Fixed a bug where walls correctly hid themselves at connected seams but
    kept blocking player movement (visibility and collision were previously
    tied together incorrectly).
- **Modular pool dismantle crash**: fixed an engine access-violation crash on
  dismantling a Modular pool, via a native code hook that correctly skips the
  dismantle effect for buildables that already opt out of the build effect
  (the engine only honored that flag for the build path, not dismantle).
- **Water Extractor snapping**: fixed the Water Extractor snapping slightly
  too low / off-center on all three pool sizes (Large, Small, Modular).
- **Performance**: reduced per-frame trace cost on Modular pools by tuning
  their tick interval, instead of running full neighbor-detection every frame.
- **Rubber Ducky (default)**: fixed the recipe not being unlocked by anything
  in the mod at all — it's now bundled into the same schematic that unlocks
  the pools, so it becomes available automatically.
- **Rubber Ducky (Feyko/secret variant)**: fixed the buildable being
  completely invisible when placed (missing static mesh assignment) and
  fixed its material (albedo/normal/MREO texture channels weren't wired up,
  causing it to render with the engine's default grey checkerboard instead
  of its intended skin). Also fixed missing quack sound variants in both
  ducks' randomized sound arrays.

## Usage

- Unlock the pools (Large/Small/Modular) through normal schematic progression
  as usual.
- The default **Rubber Ducky** unlocks automatically alongside the pools.
- The secret **Feyko Ducky** unlocks by typing the chat command `/quack`.
- Build with Alpakit and deploy to your mods folder as usual. If Alpakit
  fails with an "access denied" packaging error, fully close the game first —
  it locks the mod DLL while running.

## Building from source

This folder contains everything needed to rebuild from scratch: `Source/`,
`Content/`, `Config/`, `Resources/`, and `WPPRedux.uplugin`. Drop it into your
Satisfactory modding project's `Mods/` folder and build with Alpakit (requires
the Satisfactory Modding Unreal Engine fork and SML, per the version
constraints in `WPPRedux.uplugin`).

## License & attribution

This folder is a modified copy of **Water Pools Plus Redux**, originally
created by Sam Crosscat, with the Redux rebuild by Acxd. The original meshes,
textures, materials, and Blueprint assets in `Content/` remain the property
of their original authors — this repository does not claim ownership of
them, and the repo-level [MIT license](../LICENSE) does **not** extend to
that original content.

The MIT license applies only to the changes made in this rebuild: the new
C++ native hook in `Source/WaterPoolsPlus/WaterPoolsPlus.cpp`, the Access
Transformer config changes, and the specific Blueprint edits described above
(hologram/collision fixes, schematic unlock wiring, material node rewiring,
etc.).

This is a personal, non-commercial compatibility fix kept for private/backup
use. If you are the original author and want this taken down or handled
differently, open an issue on this repo.
