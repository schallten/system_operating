Here’s the **one-page checklist**. Print-friendly, no fluff.

---

# Pseudo-OS Roadmap — One Page Checklist

## Phase 0 — Structure First

* [ ] Define modules: `boot`, `shell`, `net`, `time`, `fs`, `apps`
* [ ] Enforce rule: **user interaction only via shell**
* [ ] Central system state struct

---

## Phase 1 — Shell Core (FOUNDATION)

* [ ] Command parser (input → tokens)
* [ ] Command registry (name, help, handler)
* [ ] `help` auto-generated
* [ ] Return codes (`OK`, `ERR`, `INVALID`)
* [ ] Serial = input, OLED = output only

**Required commands**

* [ ] `help`
* [ ] `clear`
* [ ] `reboot`
* [ ] `sysinfo`
* [ ] `uptime`

---

## Phase 2 — System Services

### Networking

* [ ] Wi-Fi service abstraction
* [ ] `net status`
* [ ] `net connect`
* [ ] `net ping`

### Time

* [ ] NTP sync
* [ ] Timezone offset
* [ ] `time now`
* [ ] `time sync`

---

## Phase 3 — Filesystem (LittleFS)

* [ ] Mount / format logic
* [ ] Error handling
* [ ] `ls`
* [ ] `cat`
* [ ] `rm`
* [ ] `touch`
* [ ] `mkdir`
* [ ] `/etc/system.conf` (Wi-Fi, TZ, boot options)

---

## Phase 4 — Applications

* [ ] App interface (init, run, exit)
* [ ] Brainfuck interpreter as app

  * [ ] `bf run file.bf`
* [ ] Weather app

  * [ ] `weather now`
  * [ ] Cache results

---

## Phase 5 — Polish & Stability

* [ ] OLED shows system state + errors
* [ ] Graceful failure modes
* [ ] Command history
* [ ] Simple task loop abstraction

---

## Rule to Remember

> **If it’s not reachable from the shell, it doesn’t exist.**

If you want, next step should be **designing the shell command registry API** — that decision locks everything else in place.
