# 🧲 Wi-Fi Layer 1 (PHY) — Frequency, Waves, QAM & Beamforming

> **How to use this note.** This is the radio layer only: how a wave is born, what 2.4 GHz means, how QAM packs bits onto that wave, how beamforming steers it, and **what PHY calibration actually fixes**. Every diagram has a short **How to read** line under it. Pairs with the PHY primer in the big 802.11 study guide.

---

## 🗺️ Map

1. Frequency is not power
2. How a 2.4 GHz wave is born *(+ TX/RX chain diagram)*
3. Why the wave has no fixed “end distance” *(+ fade vs distance)*
4. How current in copper becomes a radio wave
5. QAM: amplitude + phase on one carrier *(+ constellation diagrams)*
6. Why engineers say “phase,” not “time delay”
7. 64-QAM with a voice-call walkthrough
8. Beamforming: focusing the wave at your phone *(+ interference picture)*
9. How the AP finds you (phase difference)
10. A small numerical example (wavelength → angle)
11. **PHY calibration** — what L1 code calibrates, and what actually happens
12. Pocket card + self-check

---

## 1. Frequency is not power

When we say **2.4 GHz Wi-Fi**, we mean **frequency** — how fast the radio wave oscillates — **not** how strong it is.

| Word | What it means | Unit | Sound analogy |
|------|---------------|------|---------------|
| **Frequency** | How many cycles per second | Hz (GHz = billions/s) | **Pitch** (bass vs whistle) |
| **Power / energy** | How strong the signal is | Watts, mW, **dBm** | **Volume** (how loud) |

- **2.4 GHz** = the wave goes back and forth **2.4 billion times every second**. It tells you *where* that signal sits on the radio spectrum.
- **Power** (for example 100 mW ≈ 20 dBm at the antenna) tells you how hard that wave is pushed. Same pitch, louder or quieter.

> 🔑 A quiet 2.4 GHz phone and a loud 2.4 GHz router use the **same pitch**. Only the **volume** differs.

### 🖼️ Diagram — pitch vs volume on the same carrier

```text
  Frequency = how many wiggles / second          Power = how tall the wiggles are

  quiet 2.4 GHz:     ∿∿∿∿∿∿∿∿∿∿                  loud 2.4 GHz:     ∿∿∿∿∿∿∿∿∿∿
                     small height                                  tall height
                     same "speed" of wiggle                        SAME wiggle speed
```

**How to read:** count peaks per second → frequency. Measure peak height → power. Louder does **not** change the band.

---

## 2. How a 2.4 GHz wave is born

A 2.4 GHz Wi-Fi signal is made inside the chip and antenna by electronics + physics.

1. **Oscillator / synthesizer** — Makes (or derives) an alternating current at the carrier rate.
2. **Baseband → RF** — Digital I/Q samples become analog, get mixed up to the channel, then amplified.
3. **Antenna** — Current in copper launches the EM wave into the air.

### 🖼️ Diagram — simplified TX chain (what “Layer 1 hardware” actually is)

```text
  bits / symbols
       │
       ▼
  ┌─────────────┐    ┌──────────┐    ┌──────────┐    ┌─────────┐    ┌────────┐
  │ Digital PHY │ →  │ DAC (I/Q)│ →  │ Mixer +  │ →  │   PA    │ →  │Antenna │ → air
  │ (OFDM/QAM)  │    │  analog  │    │ LO (2.4G)│    │ amplify │    │        │
  └─────────────┘    └──────────┘    └──────────┘    └─────────┘    └────────┘
       ▲                  ▲               ▲               ▲
   L1 HW/FW            need cal        need cal        need cal
```

**How to read (left → right):**
- **Digital PHY** — builds OFDM symbols and QAM points (much of “L1 code / HW PHY”).
- **DAC** — digital I/Q numbers → voltages.
- **Mixer + LO** — slides baseband up to 2.4 GHz.
- **PA** — makes it loud enough to leave the antenna.
- **Antenna** — electricity → radio wave.

Calibration (section 11) mostly fixes **errors between these boxes**.

### Does it “have” 2.4 GHz right away? Does it travel a set distance?

- **Yes — frequency at birth.** The moment the wave leaves the antenna, it is already oscillating at 2.4 GHz.
- **No — no built-in odometer.** The wave radiates until it is too weak to decode.

### 🖼️ Diagram — fade with distance (why Wi-Fi “dies”)

```text
  AP ●━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━● far wall
     │ strong          medium           weak  │
     │ ████████        ████             ░░    │  ← signal power
     │ decode OK       OK / retries     fail  │
```

**How to read:** the wave can still exist farther out; the **receiver** just cannot tell constellation points apart (SNR too low). Indoors that often happens after tens of meters — room-dependent, not a hard odometer.

---

## 3. How the antenna “wiggle” becomes a wave

The wiggle starts the **instant** the high-frequency current enters the antenna.

1. **Back and forth** — Current races up and down the wire 2.4 billion times per second; electrons in the metal accelerate and decelerate.
2. **Ripples in the field** — Accelerating charges disturb the electromagnetic field around the wire.
3. **Wave detaches** — Each half-cycle launches a ripple. At 2.4 GHz those ripples leave as a continuous radio wave that wiggles in step with the current that made them.

> 🔑 Electricity in the wire ↔ radio wave in the air. Same rhythm. The antenna is the translator.

---

## 4. QAM — packing bits by height and timing

**QAM (Quadrature Amplitude Modulation)** puts data on the carrier by changing two things at once:

- **Amplitude** — how tall / how strong the wave is
- **Phase** — where in the cycle the wave sits (a controlled timing offset)

A raw “on/off” carrier would carry almost no data. QAM morphs each short pulse (**symbol**) into a specific height + offset so many bits ride in one pulse.

### Step-by-step: how one QAM symbol is built

1. **Twin carriers (I and Q)**  
   The transmitter takes the carrier (for example 2.4 GHz) and makes two copies. One is shifted by **90°** (a quarter cycle).  
   - **I** = In-phase  
   - **Q** = Quadrature (the delayed copy)  
   Because they are 90° apart, they can share the **same frequency** without destroying each other.

2. **Vary amplitude on each**  
   Your bits decide how strong the I copy and the Q copy should be for this symbol.

3. **Mix and combine**  
   The chip multiplies data onto I and Q and adds them. The result is **one** outgoing wave with a specific hybrid amplitude and phase.

4. **Constellation map**  
   Plot every allowed (I, Q) pair as a point on a grid:

| Modulation | Points on the grid | Bits per symbol |
|------------|--------------------|-----------------|
| BPSK | 2 | 1 |
| QPSK | 4 | 2 |
| **16-QAM** | 16 | **4** |
| **64-QAM** | 64 | **6** |
| 256-QAM | 256 | 8 |
| 1024-QAM | 1024 | 10 |

### 🖼️ Diagram — clean vs noisy constellation (why high QAM needs SNR)

```text
  CLEAN 16-QAM (high SNR)              NOISY (low SNR / bad I/Q cal)

       Q                                    Q
       │  ·  ·  ·  ·                        │  · ·· ·  ·
       │  ·  ·  ·  ·                        │ ··  · ·· ·
       │  ·  ·  ·  ·                        │  · ··  ··
       │  ·  ·  ·  ·                        │ ·  · · ··
       └──────────── I                      └──────────── I
       receiver lands near true points      cloud overlaps neighbors → bit errors
```

**How to read:**
- Ideal TX aims exactly at a grid point. RX measures a nearby cloud because of noise.
- **Dense grids** (64/256/1024-QAM) have small gaps → a small cloud already hits the wrong point.
- **Calibration** (I/Q imbalance, DC offset) keeps the *transmitted* points from being permanently skewed. Noise still exists; cal does not remove the air.

### Jumping-rope analogy (I and Q)

Two people jump the **same rope** (same frequency), but one starts a quarter cycle later.

- You can still watch person **I** and person **Q** separately.
- They do not crash into each other’s rhythm.
- Together they encode **one** rich gesture (one QAM symbol).

> ⚠️ **Important distinction.** I and Q are **two halves of one complex symbol** on **one** spatial stream. They are **not** the same thing as **MIMO spatial streams** (two antennas sending two independent bitstreams). MIMO = extra “decks.” I/Q = how one deck paints each snapshot.

---

## 5. Phase is a tiny time delay — why we still say “degrees”

Yes: a phase shift **is** a precise delay relative to another copy of the same wave.

At 2.4 GHz, **one full cycle** lasts:

\[
T = \frac{1}{2.4 \times 10^9} \approx 0.417\ \text{nanoseconds}
\]

Talking in raw seconds gets messy. Engineers instead measure the delay as a **fraction of one cycle** in degrees:

| Phase | Fraction of a cycle | Rough delay at 2.4 GHz |
|-------|---------------------|------------------------|
| 0° | none | 0 |
| 90° | 1/4 | ~0.104 ns |
| 180° | 1/2 | ~0.208 ns |
| 360° | full cycle | ~0.417 ns |

> 🔑 **Phase = time delay measured in “how far around the circle,”** so the same language works at 2.4 GHz, 5 GHz, or 6 GHz without rewriting every number.

---

## 6. 64-QAM and a Wi-Fi voice call

### What “64” means

- The constellation has **64** allowed spots.
- \(2^6 = 64\), so **each symbol carries 6 bits**.
- Same symbol duration as a simpler scheme, but **more bits per snapshot** — higher PHY rate when the link is clean.

### Walkthrough: WhatsApp / Zoom voice over Wi-Fi

Your phone does **not** pour raw audio into the antenna.

1. **Digitize** — Mic audio → codec → a stream of `0`/`1` bits.
2. **Group by 6** — Wi-Fi chip chops bits into 6-bit chunks (for 64-QAM).
3. **Pick a constellation point** — e.g. `110101` → “this amplitude, that phase.”
4. **Transmit** — Carrier is shaped to that point for one symbol time, across the tones you own.
5. **Receive** — Other end measures height + phase, maps back to `110101`, feeds the audio decoder.

### What voice actually needs

Voice hates **lag and jitter** more than it needs peak Mbps. 64-QAM helps only when SNR is good enough that symbols land on the right spots. If the signal is weak, rate control **drops** to QPSK or BPSK so packets still arrive. High QAM is a **tool for a clean link**, not a magic “voice mode.”

---

## 7. Beamforming — cupping your hands around the shout

**Beamforming** focuses energy toward a client instead of spraying equally in every direction.

### Multi-antenna idea

A beamforming AP has **several antennas**. It sends the **same** data from each, but with carefully chosen **phase (tiny delays)**.

### Constructive vs destructive interference

When those waves meet in space:

- **Out of sync** → they cancel (weaker in that direction)
- **In sync** → they add (**constructive interference** → stronger toward the phone)

By choosing the delays, the AP makes waves cancel in most directions and **add** toward your phone.

### 🖼️ Diagram — same power, steered vs not steered

```text
  NO beamforming (spray)              WITH beamforming (focus)

         ·  ·  ·  ·                          ·
      ·              ·                        ·
   AP ●·······●·······● phone              AP ●━━━━━━● phone
      ·              ·                        ·
         ·  ·  ·  ·                          ·

  energy wasted sideways                 energy adds on the path to the phone
```

**How to read:** total PA power can be similar; **direction** of constructive interference changes. Side lobes still exist in real arrays — the picture is the idea, not a perfect laser.

### Tracking you

When your phone transmits, the wave hits Antenna A a tiny bit before Antenna B (if you are off to one side). The chip measures that **phase difference**, estimates your angle, and uses the **opposite** delays on the way back so the outbound beam points at you — even as you walk (as long as it keeps updating).

> 🔑 Same “phase” word as QAM, **different job**. In QAM, phase encodes **bits**. In beamforming, phase steers **where the energy goes**.

---

## 8. Measuring angle from phase difference

### Setup

Antennas are a known few centimeters apart.

### Ear clap analogy

A clap from your right reaches the right ear slightly before the left. Your brain turns that gap into “sound came from the right.” The AP does the same with radio phases.

### Radio version

1. Phone transmits.
2. Wave hits Antenna A, then Antenna B a fraction of a nanosecond later.
3. That delay appears as a **phase lag** (for example 90°).
4. Chip converts phase lag → extra path length → angle (using speed of light and antenna spacing).

---

## 9. Numerical example — from 2.4 GHz to “30°”

### Wavelength

Radio waves travel at about the speed of light \(c = 3 \times 10^8\) m/s.

\[
\lambda = \frac{c}{f} = \frac{3 \times 10^8}{2.4 \times 10^9} = 0.125\ \text{m} = 12.5\ \text{cm}
\]

One full cycle occupies **12.5 cm** in space.

### Antenna spacing

Often about half a wavelength:

\[
d = \frac{\lambda}{2} = 6.25\ \text{cm}
\]

### Measured phase lag = 90°

Extra path length:

\[
\Delta x = \frac{90}{360} \times 12.5\ \text{cm} = 3.125\ \text{cm}
\]

### Angle of arrival (far-field approx.)

\[
\Delta x = d \cdot \sin(\theta)
\]

\[
3.125 = 6.25 \cdot \sin(\theta) \implies \sin(\theta) = 0.5 \implies \theta = 30^\circ
\]

The AP now knows “client is about 30° off-boresight,” and applies matching transmit phase weights so the beam points that way.

```text
  Phone ─── wave hits A first ───► Antenna A
              │ slightly later
              └──────────────────► Antenna B  (phase lag 90°)
                                      │
                                      ▼
                               chip: θ ≈ 30°
                                      │
                                      ▼
                         TX with conjugate phases
                         → energy peaks toward phone
```

> 📌 Real chips use more than two antennas, **calibration**, and often **sounding frames** (explicit beamforming). The 30° example is the **geometry idea**, not the full IEEE sounding exchange.

---

## 11. PHY calibration — what Layer 1 code fixes, and what actually happens

Silicon is not perfect. Temperature drifts. Antennas differ by a few millimeters of cable. The PA is not perfectly linear. **Calibration** measures those errors and writes **correction numbers** so the constellation and beams look like the textbook again.

> 🔑 Calibration does **not** change the laws of radio. It does **not** invent new Mbps by itself. It makes the **hardware behave like the model** the PHY math assumes. Without it, 256-QAM and beamforming fall apart first.

### Who runs calibration? (“Layer 1 code”)

| Layer | Typical name | What it does in cal |
|-------|--------------|---------------------|
| **ROM / boot FW** | chip bring-up | Runs factory + cold-boot cal before the first beacon |
| **Wi-Fi firmware** (on-chip MCU) | “L1 / PHY FW”, “radio FW” | Owns most cal: I/Q, DC, TX power, crystal, antenna phase |
| **Host driver** (Linux `mac80211`, `cfg80211`, vendor `.ko`) | SoftMAC / FullMAC glue | Triggers “please recalibrate,” loads cal blobs from NVM, rarely does the math itself |
| **Factory test station** | ATE | Measures golden TX/RX with instruments; burns tables into flash / OTP |

On ESP32-class chips you often see **PHY init / calibrate** in ROM or closed PHY lib called from `esp_wifi` / vendor bring-up — that *is* Layer 1 cal code, even if you never open the source.

### 🖼️ Diagram — the calibration loop

```text
  1. GENERATE a known signal
        │  (tone, chirp, or loopback pattern the chip already understands)
        ▼
  2. MEASURE what came back
        │  TX → internal loopback → RX
        │  or TX → connector → lab gear → RX path
        ▼
  3. COMPARE to ideal
        │  "I wanted Q=0, I measured Q=0.12" → error
        ▼
  4. COMPUTE correction
        │  gain/phase/offset/power numbers
        ▼
  5. WRITE into PHY registers / cal SRAM / NVM
        │
        ▼
  6. Later TX/RX paths APPLY those numbers automatically
```

**How to read:** calibrate = **measure once (or periodically), store coefficients, apply forever** until the next cal. Live packets during normal Wi-Fi use are not “being calibrated”; they ride a path that was already corrected.

### What can Layer 1 code calibrate? (the usual list)

| Calibration | Symptom if missing | What the code actually does |
|-------------|--------------------|------------------------------|
| **DC offset** | Blob at constellation center; carrier leak | Measure leftover I=0,Q=0 bias; subtract it in digital or analog |
| **I/Q imbalance** | Constellation skewed / mirrored; image spur on wrong side of LO | Measure gain mismatch and phase ≠ 90° between I and Q; apply a 2×2 correction matrix |
| **LO / crystal frequency** | CFO huge; packets hard to lock | Trim synthesizer / store ppm offset so your 2.4 GHz is really 2.4 GHz |
| **TX power** | Too quiet (range) or too loud (illegal / self-interference) | Send known pattern, measure (or use internal detector), set PA gain table so “MCS x @ 20 dBm” is true |
| **RX gain / LNA / AGC table** | Weak signals clip or drown in noise | Map ADC levels → correct dB steps so RSSI and AGC behave |
| **PA nonlinearity (DPD)** | Outer constellation points warp at high power | Measure compression; apply digital pre-distortion so the *air* wave looks linear |
| **Antenna / chain phase & delay** | Beamforming points the wrong way | Measure relative phase between RF chains; store per-antenna offsets |
| **Filter / IQ vs channel** | Some channels worse than others | Per-channel or per-band tables (2.4 vs 5 vs 6 GHz) |
| **Temperature compensation** | Fine at room temp, broken when hot | Re-run a subset of cal when temp sensor crosses a threshold |

### 🖼️ Diagram — I/Q imbalance before vs after cal

```text
  IDEAL (90°, equal gain)           BAD I/Q (no cal)              AFTER cal

       Q                                 Q                             Q
       │  ·                              │    ·                        │  ·
       │·   ·                            │  ·   ··                     │·   ·
       │  ·                              │·       ·                    │  ·
       └──── I                           └────── I                     └──── I
       square grid                       stretched / tilted            grid restored
```

**How to read:** the PHY still *aims* at ideal points in software. Analog I and Q paths were unequal, so the **air** wave was wrong. Cal measures that skew and applies the inverse in digital (or trims analog). Same idea for DC: a constant push that moves the whole cloud off-center is subtracted.

### What actually happens when we calibrate? (timeline)

```text
  Cold boot / wifi_start()
        │
        ├─► Load last NVM cal blob (if present)
        ├─► Run quick cal (DC, I/Q, TX power for current band)
        │      may mute the radio or use internal loopback
        │      SSID may be late for tens–hundreds of ms
        ├─► Store results in PHY registers
        └─► Enable TX/RX for real packets

  Later (runtime)
        │
        ├─► Periodic / temp-triggered partial cal
        ├─► Channel change → maybe new power / filter table
        └─► Beamforming sounding uses *already-calibrated* chains
            (sounding finds the *client*; cal fixed the *AP's own* antennas)
```

**Concrete example — TX power cal**
1. Firmware commands: “transmit a known tone / packet at target 16 dBm.”
2. An internal power detector (or factory meter) reports “you are actually 14.2 dBm.”
3. Firmware bumps the PA gain register by ~1.8 dB and retries until close enough.
4. That gain index is saved for “channel 6, MCS7, 20 MHz.”
5. Later, when the MAC asks for that rate, the PHY **loads the table** — it does not re-measure every frame.

**Concrete example — antenna phase cal (needed for beamforming)**
1. Inject the same tone into RF chain 0 and chain 1 (loopback or coupled path).
2. Measure phase difference at the ADCs.
3. Store “chain 1 is +17° relative to chain 0.”
4. When beamforming applies a steering vector, it **adds** that offset so the geometry math from section 9 is not lying.

### What Layer 1 code usually cannot “calibrate away”

- A neighbor blasting your channel (interference) — that is RRM / channel selection, not PHY cal.
- A user behind a thick wall — path loss; only more power / better MCS / another AP helps.
- Protocol bugs (wrong Duration, bad aggregation) — MAC, not PHY cal.
- Regulatory limits — cal *enforces* max power; it does not override the law.

### SoftMAC vs FullMAC (where the code lives)

```text
  SoftMAC (many Linux chips)          FullMAC (many phones / ESP-class)

  Host: mac80211 (MAC)                Host: thin driver
  Chip FW: PHY + cal + much MAC       Chip FW: MAC + PHY + cal
```

**How to read:** in both worlds, **calibration math almost always runs on the chip** (or at the factory). The host may only say `start` / `recal` / `load_blob`.

---

## 12. Pocket card — Layer 1 words

| Term | Plain meaning |
|------|----------------|
| **Frequency (GHz)** | How fast the wave wiggles; which band/channel neighborhood |
| **Power (W / dBm)** | How loud; reach and SNR potential |
| **Oscillator / LO** | Makes / derives the carrier rate |
| **TX chain** | Digital PHY → DAC → mixer → PA → antenna |
| **Tone / subcarrier** | One narrow frequency lane inside the channel |
| **Symbol** | One time snapshot of the constellation |
| **I / Q** | Two 90°-offset copies used to build one QAM symbol |
| **Constellation** | Allowed (amplitude, phase) points; more points = more bits |
| **Phase** | Position in the cycle = controlled tiny delay |
| **Beamforming** | Many antennas + phases so waves add toward the client |
| **AoA / phase difference** | Measure uplink lag across antennas to estimate angle |
| **Calibration** | Measure HW error → store correction → apply on every TX/RX |
| **I/Q cal / DC cal / TPC cal** | Fix skew, center blob, and true transmit power |

---

## ✅ What you should be able to explain out loud

1. Why “2.4 GHz” is pitch, not volume.  
2. Oscillator → TX chain → antenna → wave that already has that frequency.  
3. Why Wi-Fi fades with distance (attenuation), not a preset odometer.  
4. How I and Q + amplitude make a constellation point.  
5. Why 64-QAM = 6 bits/symbol, and why a weak link cannot keep it.  
6. How beamforming uses phase to aim energy.  
7. How \(\lambda = c/f\) and a phase lag turn into an angle.  
8. **What calibration is:** measure known error → write coefficients → PHY applies them.  
9. **Name three cals:** DC / I/Q imbalance / TX power (bonus: antenna phase for BF).  
10. **Who runs it:** chip PHY firmware (host only triggers / loads tables).

When you can walk through those without the notes, Layer 1 is sticking.
