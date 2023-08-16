## Quake3 Autoshoot - Using a Neural Net

### Notes
- Tested using ioQuake3 ([https://ioquake3.org/](https://ioquake3.org/))
- All modes continue to train the perceptrons apart from the DeepAim mode.
- Plays a simple beep tone from the console every time a key is pressed,
  although it may be desired to replace this with a better tone function.
- Videos on [the YouTube Channel.](https://www.youtube.com/channel/UCYe31SWsmK3X9H3r1WM6OKQ)
- I would suppose this would work on any game, I just play Quake 3.
- The "LI:" count is how many training iterations have taken place. I find ~200
  is the minimum 'sweet spot'.
- `a.wav` was made using the [Borg-ER2](https://github.com/mrbid/Borg-ER-2).
- It's usually better to use `r_vertexLight 0` (lightmaps) with the bright blue bones model as it creates a darker contrast between the character and the environment. You could also use a dark player model with `r_vertexLight 1` for the opposite effect.
- For best results set `r_picmip 16` & force models to blue bones `cg_forceModel 1` & `model "bones/default"` also set the crosshair that does not block the center of the screen `cg_drawCrosshair 7`
- You might need to manually install `aplay` and `espeak` via `sudo apt install` for example, however these do come pre-installed with Ubuntu.
- You will see the `compile.sh` script will also produces a `baim` binary. This is a simplified version which only targets the aqua blue bones player model using pre-computed Deep Aim weights.
- I've added a desperate version `desperate.c` compiled as `daim`, it runs more than one 'kernel' per scan depending on one of two configuations; confidence and desperation. A further simplification from `bones.c` which also targets only the aqua blue bones model. Nothing is stopping one from using the original `aim` binary to train their own weights for use in such *alternate applications of desire*.

### Linux Compile
```gcc aimbot.c -Ofast -lX11 -lm -o aim```

#### Key Mapping
```
Left CTRL + Left ALT - Enable/Disable Auto-Shoot

&& The following hotkey functions become enabled also;

F10 - Preset High Tollerance
UP - Preset Medium Tollerance
DOWN - Preset Low Tollerence

LEFT - Manual Lower Tollerance
RIGHT - Manual Higher Tollerance

F1 - Target Aqua Blue
F2 - Target Blue
F3 - Target Red
F4 - Target Red #2

H - Retrain/Target on current center screen colour
G - Same as H but uses an average of 9 surrounding colours

B - Deep Aim Only
N - Neural Aim Only (trains Neural Net)
M - Colour Aim Only (trains Neural Net)

K - Reduce Neural Firing Probability
L - Increase Neural Firing Probability

J - Randomise Perceptron Weights
```

#### Preferred Quake3 Client Settings
```
cg_oldRail "1"
cg_noProjectileTrail "1"
cg_forceModel "1"
cg_railTrailTime "100"
cg_crosshairSize "24"
cg_drawFPS "1"
cg_draw2D "1"
cg_gibs "1"
cg_fov "160"
cg_zoomfov "90"
cg_drawGun "1"
cg_brassTime "0"
cg_drawCrosshair "7"
cg_drawCrosshairNames "1"
cg_marks "0"
cg_crosshairPulse "1"
cg_stepTime "100"
cg_centertime "3"
xp_noParticles "1"
xp_noShotgunTrail "1"
xp_noMip "2047"
xp_ambient "1"
xp_modelJump "0"
xp_corpse "3"
xp_crosshairColor "7"
xp_improvePrediction "1"
cm_playerCurveClip "1"
com_maxfps "600"
com_blood "0"
cg_autoswitch "0"
rate "25000"
snaps "40"
model "bones/default"
headmodel "bones/default"
team_model "bones/default"
team_headmodel "bones/default"
color1 "6"
color2 "5"
cg_predictItems "1"
r_picmip "16"
r_overBrightBits "1"
r_mode "-2"
r_fullscreen "1"
r_customwidth "1920"
r_customheight "1080"
r_simpleMipMaps "1"
r_railWidth "16"
r_railCoreWidth "6"
r_railSegmentLength "32"
r_vertexLight "0"
cg_shadows "0"
com_zoneMegs "24"
com_hunkmegs "512"
```

#### Licence
Distributed under the MIT software license, see the accompanying
file COPYING or http://www.opensource.org/licenses/mit-license.php.

